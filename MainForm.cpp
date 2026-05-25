/*
 *   Copyright (C) 2023, 2026 Gene Gajewski WG5ENE
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

//---------------------------------------------------------------------------

// The only outside component used by this project is the is
// DbAware Labeled Components by Ethea - which is available
// on Ethea.it and source is also available on GitHub.
//
// TLabeledDBGrid provides a couple of enhancement over the
// stock DBGrid component as is freely avaialble to use.


#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"

#include <sysopen.h>

#include <System.ioutils.hpp>
#include <system.win.registry.hpp>
#include <System.dateutils.hpp>

#include <Vcl.HtmlHelpViewer.hpp>
#pragma link "Vcl.HtmlHelpViewer"

#include "Download.h"
#include "WinVersionQuery.h"
#include "about.h"
#include "preferences.h"
#include "xmlcheckin.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

// -- see https://github.com/EtheaDev for the following controls -----------
#pragma link "Vcl.LabeledDBCtrls"
#pragma link "Vcl.LabeledCtrls"
#pragma link "Vcl.LabeledDBCtrls"
#pragma resource "*.dfm"

TFormMain* FormMain;

#include <cctype>
#include <fstream>
#include <iostream>

#include "updateInfo.h"
#include "Log.h"

#include "FormActive.h"
#include "FormPast.h"

static const char* BaseUrl = "https://www.netlogger.org/api";

// -------- CodeSite Logger ------------------------------------------------------

// both WIN32 and WIN64x use .lib

// please note older WIN64 compilers uses CodeSiteExpressPkg.a, but we are preferring
// to use use the modern WIN64x compiler instead

#pragma comment(lib, "CodeSiteExpressPkg.lib")

#pragma link "CodeSiteLogging"

// Registry stuff -----------------------------------------------------------------

#define REG_ROOT "Software\\WG5ENE\\DASHBOARD"
static const char* PgmKey = REG_ROOT;
static const char* FieldKey = REG_ROOT "\\Columns";

// ------ An led font is included in the executable as a private windows resource -------------------

#define FONT_ID 1
#define HELPFILE "DASHBOARD.CHM"

// --- Export a CSV file of checkins ---------------------------------------------

void __fastcall TFormMain::ExportCSV(String Filename)
{
    static const char* comma = ",";
    static const char* quote = "\"";
    std::wfstream strm;

    TBookmark bm = FDMemTable1->Bookmark;

    // *retry* incase some other application unfortunately has this file open in a non-shared
    // mode

retry:
    strm.open(Filename.c_str(), strm.binary | strm.trunc | strm.in | strm.out);
    if (!strm.is_open())
    {
        LogWarn("Failed to open: " + Filename);
        String msg = "Unable to open file \"" + Filename + "\".";
        int result = MessageDlg(msg, mtError, mbAbortRetryIgnore, 0);

        if (result != mrRetry)
        {
            LogInfo("User aborts or ignores.");
            return;
        }
        LogInfo("User retries " + Filename);
        goto retry; // heh!
    }

    // write nicer Column Titles (instead of actual field names)

    for (int x = 0; x < DBGrid1->Columns->Count; x++)
    {
        if (x > 0)
            strm << comma;

        strm << quote << DBGrid1->Columns->Items[x]->Title->Caption << quote;
    }

    strm << std::endl;

    // write all records -----------

    FDMemTable1->BeginBatch();
    FDMemTable1->First();

    // write out fields in same TColumns ordering... ------------

    for (int x = 0; x < FDMemTable1->RecordCount; x++)
    {
        if (x > 0)
            strm << std::endl;

        for (int y = 0; y < DBGrid1->Columns->Count; y++)
        {
            if (y > 0)
                strm << comma;

            strm << quote << DBGrid1->Columns->Items[y]->Field->AsString.c_str() << quote;
        }

        FDMemTable1->Next();
    }
    strm.close();
    FDMemTable1->EndBatch();
    FDMemTable1->Bookmark = bm;
}
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner) {}


// ---- Once a second... ------------------------------------

void __fastcall TFormMain::MasterTick(TObject* Sender)
{
    UpdateClockDisplay();
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::UpdateClockDisplay()
{
    static const String DateFormat = "dddd, mmmm dd, yyyy";
    static const String TimeFormat12 = "h:mm:ss ampm";
    static const String TimeFormat24 = "hh:mm:ss";
    static const String UtcStr = "Universal Time Coordinated";

    TTimeSpan offset = UTC ? TTimeZone::Local->UtcOffset : 0;  // local or UTC TZ span
    TDateTime now = TDateTime::CurrentDateTime();

    PanelDate->Caption = (now - offset).FormatString(DateFormat);
    PanelClock->Caption = (now - offset).FormatString(AMPM ? TimeFormat12 : TimeFormat24);
    PanelZone->Caption = UTC ? UtcStr : TTimeZone::Local->DisplayName;
}

//  User clicked on an entry - show QRZ.com page -------------------------------------------

void __fastcall TFormMain::DBGrid1DblClick(TObject* Sender)
{
    String Callsign, Cmd;

    if (FDMemTable1->RecordCount > 0)
    {
        Callsign = FDMemTable1->FieldByName("Callsign")->AsString;

        if (Callsign.IsEmpty()) // huh?
        {
            LogInfo("Callsign field is empty.");
            return;
        }

        Cmd = "https://qrz.com/db/" + Callsign;
        Shell(Cmd);
    }
}

// ---- run a shell command ------------------------------------------------------

void __fastcall TFormMain::Shell(String cmd)
{
    LogInfo("Shell: " + cmd);
    ShellExecuteW(NULL, L"open", cmd.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

//---- save window layout ----------------------------------------------------------

void __fastcall TFormMain::SaveDefaults()
{
    std::unique_ptr<TRegistry> Reg;

    try
    {
        Reg = std::make_unique<TRegistry>(KEY_WRITE);
        Reg->RootKey = HKEY_CURRENT_USER;
        Reg->OpenKey(FieldKey, true);

        // lambda to write out a data column's particulars

        auto writefield = [&](TColumn* col) {
            Reg->OpenKey(FieldKey, false);
            Reg->OpenKey(col->FieldName, true);
            Reg->WriteBool("Visible", col->Visible);

            col->Visible = true; // need  to do this here since the col width is
            // incorrectly reported as -1 when col is not visible

            Reg->WriteInteger("Width", col->Width);
            Reg->WriteInteger("Index", col->Index);
            Reg->CloseKey();
        };

        for (int x = 0; x < DBGrid1->Columns->Count; x++)
            writefield(DBGrid1->Columns->Items[x]);

        // save window state

        Reg->OpenKey(PgmKey, true);
        Reg->WriteBool("Maximized", WindowState == TWindowState::wsMaximized);
        Reg->WriteInteger("Top", Top);
        Reg->WriteInteger("Left", Left);
        Reg->WriteInteger("Width", Width);
        Reg->WriteInteger("Height", Height);
        Reg->WriteBool("UTC", UTC);
        Reg->WriteBool("AMPM", AMPM);
        Reg->WriteInteger("PollRate", RefreshRate);
        Reg->WriteString("Style", Vcl::Themes::TStyleManager::ActiveStyle->Name);
        Reg->CloseKey();
    } catch (Exception* err)
    {
        LogExcept(err);
        // do nothing
    }
}

//---- load window layout ------------------------------------------------------------

void __fastcall TFormMain::LoadDefaults()
{
    std::unique_ptr<TRegistry> Reg;
    std::map<int, TColumn*> IndexingMap;

    try
    {
        Reg = std::make_unique<TRegistry>(KEY_READ);
        Reg->RootKey = HKEY_CURRENT_USER;
        Reg->OpenKeyReadOnly(FieldKey);

        // lambda to read column data and update an index/column map for
        // later use in a *second* pass

        auto readfield = [&](TColumn* Column) {
            Reg->OpenKeyReadOnly(FieldKey);

            if (!Reg->KeyExists(Column->FieldName)) // unlikely, but
                return;

            Reg->OpenKeyReadOnly(Column->FieldName);
            Column->Visible = Reg->ReadInteger("Visible");
            Column->Width = Reg->ReadInteger("Width");
            int Index = Reg->ReadInteger("Index");

            IndexingMap[Index] = Column;
            Reg->CloseKey();
        };

        for (int x = 0; x < DBGrid1->Columns->Count; x++)
            readfield(DBGrid1->Columns->Items[x]);

        // get stored window state

        if (Reg->OpenKeyReadOnly(PgmKey))
        {
            Vcl::Themes::TStyleManager::TrySetStyle(Reg->ReadString("Style"));

            if (Reg->ReadBool("Maximized"))
                WindowState = TWindowState::wsMaximized;

            Left = Reg->ReadInteger("Left");
            Top = Reg->ReadInteger("Top");
            Height = Reg->ReadInteger("Height");
            Width = Reg->ReadInteger("Width");
            UTC = Reg->ReadBool("UTC");
            AMPM = Reg->ReadBool("AMPM");
            RefreshRate = Reg->ReadInteger("PollRate");
        }
        Reg->CloseKey();

        // we must set the columns' display order indexes in an *ordinal* fashion
        // because of the 'swapping' method Delphi uses to reorder TColumns

        for (auto Item : IndexingMap)
            Item.second->Index = Item.first;

    } catch (Exception* err)
    {
        LogExcept(err);
    }
}

//--- close application properly -------------------------------------------------------

void __fastcall TFormMain::FormClose(TObject* Sender, TCloseAction& Action)
{
    RefreshTimer->Enabled = false;
    ClockTimer->Enabled = false;
    SaveDefaults();

    // don't leave font resource hanging..

    if (ClockFontHandle != INVALID_HANDLE_VALUE)
        RemoveFontMemResourceEx(ClockFontHandle);
}

//----pull checkin data for either active or past nets --------------------------------------

void __fastcall TFormMain::CheckinData()
{
    try
    {
        // set up REST objs

        RESTClient1->BaseURL = BaseUrl;
        RESTRequest1->Client = RESTClient1;
        RESTRequest1->Response = RESTResponse1;

        RESTRequest1->Params->Clear();
        RESTRequest1->Params->AddItem("ServerName", CurrentServer, pkGETorPOST);
        RESTRequest1->Params->AddItem("NetName", CurrentNet, pkGETorPOST);

        if (ActiveMode)
            RESTRequest1->Resource = "GetCheckins.php";
        else
        {
            RESTRequest1->Resource = "GetPastNetCheckins.php";
            RESTRequest1->Params->AddItem("NetID", CurrentNetID, pkGETorPOST); // required param for past nets
        }

        // Would like to run completion handler in background thread but can't - if grid control is resized
        // while we're updating then exceptions may occur to due data races....

        NewRecords = 0;
        Pointer = -1;
        LogInfo("REST: " + RESTRequest1->GetFullRequestURL(true));

        FDMemTable1->DisableControls();

        RESTRequest1->ExecuteAsync(
            [this]() {
                int Status = RESTResponse1->StatusCode;
                LogInfo("CompletionHandler StatusCode: " + IntToStr(Status));

                if (Status != 200)
                {
                    FDMemTable1->EnableControls();
                    return;
                }

                try
                {
                    // post records to the mem table

                    // aliases
                    using State = XML_Checkin_Machine::State;
                    using NamedValues = XML_Checkin_Machine::NamedValues;

                    // quick lambda to write record to mem table

                    auto callback = [&](State state, NamedValues& vals) {
                        if (state == State::Checkin)
                        {
                            if (NewRecords == 0) // only clear on new records
                                FDMemTable1->EmptyDataSet();

                            NewRecords++;

                            FDMemTable1->Append();
                            for (auto Item : vals)
                            {
                                TField* field = FDMemTable1->FieldByName(Item.first);

                                if (!field) // huh?
                                    continue;

                                if (field->DataType == TFieldType::ftBoolean)
                                    field->Value = (Item.second == "Y" ? true : false);
                                else
                                    field->Value = Item.second;
                            }
                            FDMemTable1->Post();
                        } else if (state == State::CheckinList)
                        {
                            auto iter = vals.find("Pointer");
                            if (iter != vals.end())
                            {
                                Pointer = StrToInt(iter->second);
//                                LogInfo("Pointer: " + iter->second);
                            } else
                                Pointer = -1;
                            for (auto Item : vals)
                            {
                                LogNameVal(Item.first, Item.second);
                            }
                        }
                    };

                    // declare our xml processor
                    XML_Checkin_Machine machine(callback);

                    // stash the currently selected record serialno
                    int Selected = FDMemTable1->FieldByName("SerialNo")->AsInteger;

                    // go and process it all
                    FDMemTable1->BeginBatch();
                    machine.Execute(RESTResponse1->RawBytes);
                    FDMemTable1->EndBatch();
                    FDMemTable1->First();

                    // reset cursor on previously stored serialno if found
                    while (!FDMemTable1->Eof)
                    {
                        if (FDMemTable1->FieldByName("SerialNo")->AsInteger == Selected)
                            break;
                        FDMemTable1->Next();
                    }

                } catch (Exception& e)
                {
                    LogExcept(&e);
                    FDMemTable1->Cancel();
                    FDMemTable1->EndBatch();
                }
                TThread::Queue(nullptr, [this]() { PostProcessing(); });
            },
            true, true,
            [this](TObject* AObject) { // should never get to completionerror handler here...
                Exception* e = dynamic_cast<Exception*>(AObject);
                LogError(e->Message);
            });

    } catch (Exception& e)
    {
        LogExcept(&e);
        FDMemTable1->EnableControls();
    }
}

void __fastcall TFormMain::PostProcessing()
{
    // set Grid column widths to match their content

    if (NewRecords == 0 && FDMemTable1->RecordCount > 0) // typical new or past "Test" net entry with 0 checkins...
    {
        FDMemTable1->EmptyDataSet(); // clear old stuff if needed
    } else
        for (int x = 0; x < DBGrid1->Columns->Count; x++)
            BestFitDBGridColumn(DBGrid1, DBGrid1->Columns->Items[x], 0, 24);

    LogInfo(UIntToStr(NewRecords) + " records.");
    FDMemTable1->EnableControls();
    DBGrid1->Enabled = true;

    if (ActiveMode) // active nets can suddenly close on us
    {
        if (NewRecords == 0)
        {
            StatusBar1->SimpleText = CurrentNet + " is now closed.";
            CurrentNet = "";  // clear this so we don't accidentally poll for data again
            Beep();
            return; // leave - do not reset timer
        }
        RefreshTimer->Interval = RefreshRate * 1000;
        RefreshTimer->Enabled = true; // ready for the time to next poll
    }

    StatusBar1->SimpleText = String().sprintf(L"%d Records", FDMemTable1->RecordCount);
    actExportCSV->Enabled = FDMemTable1->RecordCount ? true : false;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::FormShow(TObject* Sender)
{
    UpdateClockDisplay();
    ClockTimer->Enabled = true;
}

//--- called by refresh timer which is based on a poll rate (20-180sec) ----------------------

void __fastcall TFormMain::RefreshTimerTimer(TObject* Sender)
{
    ENTERFUNC;
    RefreshTimer->Enabled = false;  // avoid accidental reentrance

    if (!CurrentNet.IsEmpty())
        CheckinData();
    else                           // last poll was empty and so CurrentNet was blanked out
        LogInfo("Activenet is empty - no further refreshes.");
    EXITFUNC;
}
//---------------------------------------------------------------------------


// check for program updates -------------------------------------------------

bool __fastcall TFormMain::CheckUpdate(String& Url, String& VersionText, String& InfoText)
{
    std::unique_ptr<TXMLDocument> Document;
    Utility::WinVersionQuery wver;
    Utility::VerStr vstr;

    vstr = wver.GetStr("FileVersion");
    LogInfo(vstr);

    // REST request
    try
    {
        Document = std::make_unique<TXMLDocument>(this);
        RESTClient1->BaseURL = "https://gajewski.net/update";
        RESTRequest1->Client = RESTClient1;
        RESTRequest1->Resource = "Dashboard-Update.php";
        RESTRequest1->Response = RESTResponse1;
        RESTRequest1->Params->AddItem(L"maj", IntToStr(vstr.Major), pkGETorPOST);
        RESTRequest1->Params->AddItem(L"min", IntToStr(vstr.Minor), pkGETorPOST);
        RESTRequest1->Params->AddItem(L"rel", IntToStr(vstr.Release), pkGETorPOST);
        RESTRequest1->Params->AddItem(L"bld", IntToStr(vstr.Build), pkGETorPOST);

        RESTRequest1->Execute();

        if (RESTResponse1->StatusCode == 200)
        {
            _di_IXMLNode Node;

            Document->LoadFromXML(RESTResponse1->Content);
            Document->Active = true;
            Node = Document->DocumentElement;

            // Hat tip to the Notepad++ updater here
            if (Node->NodeName == "GUP")
            {
                String Answer, Location, Version, Filename, Info;

                Answer = Node->ChildValues["NeedToBeUpdated"];
                if (Answer == "yes")
                {
                    Url = Node->ChildValues["Location"];
                    VersionText = Node->ChildValues["Version"];
                    InfoText = Node->ChildValues["Info"];
                    LogInfo(Url);
                    LogInfo(VersionText);
                    LogInfo(InfoText);
                    return true;
                }
            } else
                LogWarn("Bad Node: " + Node->NodeName);
        } else
            LogWarn("Bad Status Code: " + IntToStr(RESTResponse1->StatusCode));
    } catch (Exception* err)
    {
        LogExcept(err);
    }
    return false; // update not needed
}

//----  form intialization --------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject* Sender)
{
    CodeSite->Clear();
    Application->OnException = CodeSite->ExceptionHandler;
    LogInfo("Starting Dashboard");
    Application->HelpFile = TPath::Combine(TPath::GetAppPath(), HELPFILE);

    // load led clock font from resource
    try
    {
        DWORD font_count;
        std::unique_ptr<TResourceStream> rs;

        rs = std::make_unique<TResourceStream>(THandle(HInstance), FONT_ID, RT_FONT);
        ClockFontHandle = AddFontMemResourceEx(rs->Memory, rs->Size, 0, &font_count);
    } catch (Exception& err)
    { /* failed to load clock resource */
        LogExcept(&err);
    }

    // Colmap allows access to a DBGrid column by name
    for (int x = 0; x < DBGrid1->Columns->Count; x++)
        ColMap.insert({ DBGrid1->Columns->Items[x]->FieldName, DBGrid1->Columns->Items[x] });

    LoadDefaults();
    FDMemTable1->Open();
}
//---------------------------------------------------------------------------

// adjust TColumn width to content size ------------------------------------------

void __fastcall TFormMain::BestFitDBGridColumn(
    TDBGrid* Grid, TColumn* Col, int MaxRowsToScan /*0 = all*/, int Padding /*pixels*/)
{
    if (!Grid || !Col || !Col->Field)
    {
        LogWarn("Grid, Col, or Field is nulll.");
        return;
    }

    TDataSet* DS = Col->Field->DataSet;
    if (!DS || !DS->Active)
    {
        LogWarn("No DataSet or not active.");
        return;
    }

    // Use grid fonts for accurate measurement
    // Title font may differ from cell font

    // RAII
    std::unique_ptr<TFont> oldFont = std::make_unique<TFont>();

    try
    {
        oldFont->Assign(Grid->Canvas->Font);

        // 1) Measure title/header
        Grid->Canvas->Font->Assign(Col->Title->Font);
        int maxW = Grid->Canvas->TextWidth(Col->Title->Caption);

        // 2) Measure cell contents (DisplayText = what user sees)
        Grid->Canvas->Font->Assign(Grid->Font);

        TBookmark bm = DS->GetBookmark();
        DS->DisableControls();
        try
        {
            DS->First();
            int scanned = 0;

            while (!DS->Eof)
            {
                UnicodeString s = Col->Field->DisplayText; // formatted display text
                int w = Grid->Canvas->TextWidth(s);
                if (w > maxW)
                    maxW = w;

                scanned++;
                if (MaxRowsToScan > 0 && scanned >= MaxRowsToScan)
                    break;

                DS->Next();
            }
        } __finally
        {
            if (DS->BookmarkValid(bm))
                DS->GotoBookmark(bm);
            DS->FreeBookmark(bm);
            DS->EnableControls();
        }

        Col->Width = maxW + Padding;
    } __finally
    {
        Grid->Canvas->Font->Assign(oldFont.get());
    }
}
//---------------------------------------------------------------------------

// adjust *all* DBGrid TColumn widths --------------------------------------

void __fastcall TFormMain::BestFitAll(TDBGrid* Grid, int maxrow, int padding)
{
    for (int x = 0; x < Grid->Columns->Count; x++)
        BestFitDBGridColumn(Grid, Grid->Columns->Items[x], maxrow, padding);
}


//---export grid to universal *.csv file  ------------------------------------

void __fastcall TFormMain::ActionExport(TObject* Sender)
{
    // empty table?

    if (FDMemTable1->RecordCount == 0)
    {
        StatusBar1->SimpleText = "Nothing to export.";
        Beep();
        return;
    }

    // lambda to sanitize a suggested filename

    auto Legalize = [](String& ref) {
        using System::Ioutils::TPath;

        // pascal objects use 1-based indexes..

        for (int x = 1; x <= ref.Length(); x++)
        {
            if (!TPath::IsValidFileNameChar(ref[x]))
                ref[x] = ' ';
        }
        ref.Trim();
    };

    String fname = edNET->Text;
    Legalize(fname);

    SaveDialog1->FileName = fname;

    if (SaveDialog1->Execute())
        ExportCSV(SaveDialog1->FileName);
}

//----about box -----------------------------------------------------------

void __fastcall TFormMain::ActionAbout(TObject* Sender)
{
    AboutBox->ShowModal();
}

//----preferences dialog ---------------------------------------------------

void __fastcall TFormMain::ActionPreferences(TObject* Sender)
{
    String curstyle = Vcl::Themes::TStyleManager::ActiveStyle->Name;
    FormPrefs->SpinEdit1->Value = RefreshRate;

    if (FormPrefs->ShowModal() == mrOk)
        RefreshRate = FormPrefs->SpinEdit1->Value;
    else
    {
        if (Vcl::Themes::TStyleManager::ActiveStyle->Name != curstyle)
            Vcl::Themes::TStyleManager::TrySetStyle(curstyle);
    }
}

//----force column widths for content size ------------------------------------

void __fastcall TFormMain::ActionAutoFit(TObject* Sender)
{
    BestFitAll(DBGrid1, 0, 24);
}

//------- check for program updates ------------------------------------------

void __fastcall TFormMain::actCheckUpdatesExecute(TObject* Sender)
{
    String Url, InfoText, VersionText, FileName;

    if (CheckUpdate(Url, VersionText, InfoText) == false)
    {
        Beep();
        ShowMessage("You have the latest version.");
        LogInfo("No update.");
        return;
    }

    String text = "An updated version ";
    text += VersionText;
    text += " is available.\nDownload and install this update?";
    UpdInfo->Label1->Caption = text;
    UpdInfo->RichEdit1->Text = InfoText;

    UpdInfo->ShowModal();

    if (UpdInfo->ModalResult == mrOk)
    {
        LogInfo("Will install updated program using: " + FileName);

        // download the update package
        DL->Show();
        DL->GetFile(Url, FileName);
        DL->Close();

        if (!FileName.IsEmpty()) // install new package
        {
            ShowMessage("Download complete. Application will close and update will proceed.");
            ShellExecute(NULL, L"open", FileName.c_str(), NULL, NULL, SW_SHOW);
            Close(); // program terminates here
        }
        LogWarn("Empty filename."); // huh? aborted somehow?
    } else
        LogInfo("Chose not to unstall update.");
}
//---------------------------------------------------------------------------

// set sort order for clicked TColumn header --------------------------------

void __fastcall TFormMain::DBGrid1TitleClick(TColumn* Column)
{
    if (!Column || !Column->Field)
        return;
    if (Column->Field->FieldKind != fkData)
        return; // ignore calculated/lookup/etc.

    const String f = Column->Field->FieldName;
    SortField = f;
    const String fu = f.UpperCase();
    const String cur = FDMemTable1->IndexFieldNames.UpperCase();

    // Toggle ASC <-> DESC for the same field; otherwise sort ASC by the new field
    if (cur == fu)
    {
        FDMemTable1->IndexFieldNames = f + ":D"; // ASC -> DESC
        Ascending = false;
    } else
    {
        if (cur == (fu + ":D"))
            FDMemTable1->IndexFieldNames = f; // DESC -> ASC
        else
            FDMemTable1->IndexFieldNames = f; // new column -> ASC
        Ascending = true;
    }
}


// set the sort indicator arrow (or not) for the current TColumn being drawn -----------

void __fastcall TFormMain::DBGrid1SortedField(
    TLabeledDbGrid* Sender, TField* Field, TCBSortOrder& Sorted)
{
    if (SameText(SortField, Field->DisplayName))
        Sorted = Ascending ? TCBSortOrder::soAscending : TCBSortOrder::soDescending;
    else
        Sorted = TCBSortOrder::soNone;
}

// --- hilite current 'pointer' record in MoneyGreen color ----------------------

// TODO: make color a config dialog item

void __fastcall TFormMain::DBGrid1DrawColumnCell(
    TObject* Sender, const TRect& Rect, int DataCol, TColumn* Column, TGridDrawState State)

{
    if (State.Empty() && !(DBGrid1->HighlightCurrRow && DBGrid1->DrawingCurrentRecord))
    {
        TField* field = FDMemTable1->FieldByName("SerialNo");
        if (field)
        {
            if (field->AsInteger == Pointer)
                DBGrid1->Canvas->Brush->Color = clMoneyGreen;
        }
    }
    DBGrid1->DefaultDrawColumnCell(Rect, DataCol, Column, State);
}

// ---- update gobal display data -------------------------------------------

void __fastcall TFormMain::ShowNetInfo()
{
    if (ActiveMode)    // active nets
    {
        CurrentNet = FormActiveNets->FDMemTabNetName->AsString;
        CurrentServer = FormActiveNets->FDMemTabServer->AsString;

        edFreq->Text = FormActiveNets->FDMemTabFrequency->AsString;
        edBand->Text = FormActiveNets->FDMemTabBand->AsString;
        edMode->Text = FormActiveNets->FDMemTabMode->AsString;
        edNetControl->Text = FormActiveNets->FDMemTabNetControl->AsString;
        edLogger->Text = FormActiveNets->FDMemTabLogger->AsString;
        edStart->Text = FormActiveNets->FDMemTabDate->AsString;

    } else  // past nets
    {
        CurrentNet = FormPastNets->FDMemTabNetName->AsString;
        CurrentServer = FormPastNets->FDMemTabServer->AsString;
        CurrentNetID = FormPastNets->FDMemTabNetID->AsString;

        edFreq->Text = FormPastNets->FDMemTabFrequency->AsString;
        edBand->Text = FormPastNets->FDMemTabBand->AsString;
        edMode->Text = FormPastNets->FDMemTabMode->AsString;
        edNetControl->Text = FormPastNets->FDMemTabNetControl->AsString;
        edLogger->Text = FormPastNets->FDMemTabLogger->AsString;
        edStart->Text = FormPastNets->FDMemTabDate->AsString;

        edClosed->Text = FormPastNets->FDMemTabClosedAt->AsString;
        edInactivity->Text = FormPastNets->FDMemTabInactivityTimer->AsString;
        dbcbAsassinated->Checked = FormPastNets->FDMemTabAssassinated->AsBoolean;
        edAIMUpdate->Text = FormPastNets->FDMemTabUpdateInterval->AsString;
        cbAIM->Checked = FormPastNets->FDMemTabAIM->AsBoolean;
        edLastActivity->Text = FormPastNets->FDMemTabLastActivity->AsString;
        edSourceIP->Text = FormPastNets->FDMemTabsrcIP->AsString;
    }
    edNET->Text = CurrentNet;
    edNetID->Text = CurrentNetID;

    // following fields only used by past nets - hide if in active mode

    edClosed->Visible = !ActiveMode;
    edNetID->Visible = !ActiveMode;
    edInactivity->Visible = !ActiveMode;
    edAIMUpdate->Visible = !ActiveMode;
    edLastActivity->Visible = !ActiveMode;
    cbAIM->Visible = !ActiveMode;
    dbcbAsassinated->Visible = !ActiveMode;
    edSourceIP->Visible = !ActiveMode;

    PanelLeft->Invalidate();
}

//---- user selects an active net to display ------------------------------------

void __fastcall TFormMain::ActionLiveNet(TObject* Sender)
{
    RefreshTimer->Enabled = false; // todo: is this needed?
    FormActiveNets->ShowModal();

    if (FormActiveNets->ModalResult == mrOk)
    {
        ActiveMode = true;
        ShowNetInfo();
        CheckinData();
    } else if (!CurrentNet.IsEmpty() && ActiveMode)
        RefreshTimer->Enabled = true;
}

//---- user selects a 'past' net to display ------------------------------------

void __fastcall TFormMain::ActPastNetsExecute(TObject* Sender)
{
    RefreshTimer->Enabled = false;  // always

    FormPastNets->ShowModal();
    if (FormPastNets->ModalResult == mrOk)
    {
        ActiveMode = false;
        ShowNetInfo();
        CheckinData();
    } else if (ActiveMode && !CurrentNet.IsEmpty())  // user backed out and so stays on prior active net
        RefreshTimer->Enabled = true;
}

