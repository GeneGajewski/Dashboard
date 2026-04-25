/*
 *   Copyright (C) 2023 Gene Gajewski WG5ENE
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

#include <vcl.h>
#pragma hdrstop

#include "MainForm.h"

#include <sysopen.h>

#include <System.ioutils.hpp>
#include <system.win.registry.hpp>

#include <Vcl.HtmlHelpViewer.hpp>
#pragma link "Vcl.HtmlHelpViewer"

#include "Download.h"
#include "Select.h"
#include "WinVersionQuery.h"
#include "about.h"
#include "preferences.h"
#include "xmlcheckin.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Vcl.LabeledDBCtrls"
#pragma resource "*.dfm"

TFormMain* FormMain;

#include <cctype>
#include <fstream>
#include <iostream>

#include "updateInfo.h"
#include "Log.h"

#include "DashTypes.h"
#include "FormActive.h"

static const char* BaseUrl = "https://www.netlogger.org/api";


// WIN32 and WIN64x
#pragma comment(lib, "CodeSiteExpressPkg.lib")

#pragma link "CodeSiteLogging"

#define REG_ROOT "Software\\WG5ENE\\DASHBOARD"
static const char* PgmKey = REG_ROOT;
static const char* FieldKey = REG_ROOT "\\Columns";

#define FONT_ID 1

#define HELPFILE "DASHBOARD.CHM"



// Export a CSV file

void __fastcall TFormMain::ExportCSV(String Filename)
{
    ENTERFUNC;

    const char* comma = ",";
    const char* quote = "\"";
    std::wfstream strm;

    TBookmark bm = FDMemTable1->Bookmark;

    // retry in case another application has this file open in some non-shared
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
            EXITFUNC;
            return;
        }
        LogInfo("User retries.");
        goto retry; // heh!
    }

    // write field names

    for (int x = 0; x < FDMemTable1->Fields->Count; x++)
    {
        if (x > 0)
            strm << comma;

        strm << quote << FDMemTable1->Fields->Fields[x]->FieldName.c_str() << quote;
    }

    strm << std::endl;

    // write records

    FDMemTable1->BeginBatch();
    FDMemTable1->First();

    for (int x = 0; x < FDMemTable1->RecordCount; x++)
    {
        if (x > 0)
            strm << std::endl;

        for (int y = 0; y < FDMemTable1->FieldCount; y++)
        {
            if (y > 0)
                strm << comma;

            strm << quote
                 << FDMemTable1->FieldByName(FDMemTable1->Fields->Fields[y]->FieldName)
                        ->AsString.c_str()
                 << quote;
        }

        FDMemTable1->Next();
    }

    strm.close();
    FDMemTable1->Bookmark = bm;
    FDMemTable1->EndBatch();
    EXITFUNC;
}
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------

void __fastcall TFormMain::MasterTick(TObject* Sender)
{
    UpdateClockDisplay();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::UpdateClockDisplay()
{
    const String DateFormat = "dddd, mmmm, dd, yyyy";
    const String TimeFormat = AMPM ? "h:mm:ss ampm" : "hh:mm:ss";

    TTimeSpan offset = UTC ? TTimeZone::Local->UtcOffset : 0;
    TDateTime now = TDateTime::CurrentDateTime();

    PanelDate->Caption = (now - offset).FormatString(DateFormat);
    PanelClock->Caption = (now - offset).FormatString(TimeFormat);
    PanelZone->Caption = UTC ? "Universal Time Coordinated" : TTimeZone::Local->DisplayName;
}

//---------------------------------------------------------------------------
void __fastcall TFormMain::DBGrid1DblClick(TObject* Sender)
{
    ENTERFUNC;
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
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Shell(String cmd)
{
    LogInfo("Shell: " + cmd);
    ShellExecuteW(NULL, L"open", cmd.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SaveDefaults()
{
    std::unique_ptr<TRegistry> Reg;

    try
    {
        Reg = std::make_unique<TRegistry>(KEY_WRITE);
        Reg->RootKey = HKEY_CURRENT_USER;
        Reg->OpenKey(FieldKey, true);

        // lambda to write out a data column's particulars

        auto writefield = [this, &Reg](TColumn* col) {
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
//---------------------------------------------------------------------------
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

        auto readfield = [this, &Reg, &IndexingMap](TColumn* Column) {
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
        // do nothing
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClose(TObject* Sender, TCloseAction& Action)
{
    SaveDefaults();

    // don't leave font resource hanging..

    if (ClockFontHandle != INVALID_HANDLE_VALUE)
        RemoveFontMemResourceEx(ClockFontHandle);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActiveDataUpdate()
{
    Application->ProcessMessages();
    try
    {
        // set it all up
        RESTClient1->BaseURL = BaseUrl;
        RESTRequest1->Client = RESTClient1;
        RESTRequest1->Response = RESTResponse1;
        RESTRequest1->Resource = "GetCheckins.php";
        RESTRequest1->Params->Clear();
        RESTRequest1->Params->AddItem("ServerName", ActiveServer, pkGETorPOST);
        RESTRequest1->Params->AddItem("NetName", ActiveNet, pkGETorPOST);

        // run in background thread

        RESTRequest1->ExecuteAsync(
            [this]() {
                int Status = RESTResponse1->StatusCode;
                if (Status != 200)
                    return; // TODO: expound on this

                try
                {
                    FDMemTable1->DisableControls();
                    FDMemTable1->EmptyDataSet();
                    // post a record to the mem table

                    auto callback = [&](XML_Checkin_Machine::State state,
                                        XML_Checkin_Machine::NamedValues& vals) {
                        if (state == XML_Checkin_Machine::State::Checkin)
                        {
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
                        }
                    };

                    // our xml processor
                    XML_Checkin_Machine machine(callback);

                    String inspect = RESTResponse1->Content;

                    // do it
                    FDMemTable1->BeginBatch();
                    machine.Execute(RESTResponse1->RawBytes);
                    FDMemTable1->EndBatch();
                } catch (Exception& e)
                {
                    FDMemTable1->Cancel();
                    FDMemTable1->EndBatch();
                }
           TThread::Queue(nullptr, [this]() { PostProcessing(); });
            },
            false);

    } catch (Exception& e)
    {
//        Log(logERROR, e.Message);
    }
}

void __fastcall TFormMain::PostProcessing()
{
    // set DBGrid column widths to match content
    for (int x = 0; x < DBGrid1->Columns->Count; x++)
        BestFitDBGridColumn(DBGrid1, DBGrid1->Columns->Items[x], 0, 24);

    FDMemTable1->EnableControls();
    StatusBar1->SimpleText = String().sprintf(L"%d Records", FDMemTable1->RecordCount);
    DBGrid1->Enabled = true;
    actExportCSV->Enabled = FDMemTable1->RecordCount ? true : false;
    RefreshTimer->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormShow(TObject* Sender)
{
    UpdateClockDisplay();
    ClockTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RefreshTimerTimer(TObject* Sender)
{
    RefreshTimer->Enabled = false;
    ActiveDataUpdate();
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::CheckUpdate(String& Url, String& VersionText, String& InfoText)
{
    std::unique_ptr<TXMLDocument> Document;
    Utility::WinVersionQuery wver;
    Utility::VerStr vstr;

    vstr = wver.GetStr("FileVersion");
    LogInfo(vstr);

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

        String inspect = RESTResponse1->Content;

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
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject* Sender)
{
    CodeSite->Clear();
    Application->HelpFile = TPath::Combine(TPath::GetAppPath(), HELPFILE);
    try
    {
        DWORD font_count;
        std::unique_ptr<TResourceStream> rs;

        rs = std::make_unique<TResourceStream>(THandle(HInstance), FONT_ID, RT_FONT);
        ClockFontHandle = AddFontMemResourceEx(rs->Memory, rs->Size, 0, &font_count);
    } catch (Exception* err)
    { /* failed to load clock resource */
        LogExcept(err);
    }

    for (int x = 0; x < DBGrid1->Columns->Count; x++)
        ColMap.insert({ DBGrid1->Columns->Items[x]->FieldName, DBGrid1->Columns->Items[x] });

    LoadDefaults();
    FDMemTable1->Open();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::BestFitDBGridColumn(
    TDBGrid* Grid, TColumn* Col, int MaxRowsToScan /*0 = all*/, int Padding /*pixels*/)
{
    if (!Grid || !Col || !Col->Field)
    {
        LogWarn("Grid, Col, or Field is nulll.");
        EXITFUNC;
        return;
    }

    TDataSet* DS = Col->Field->DataSet;
    if (!DS || !DS->Active)
    {
        LogWarn("No DataSet or not active.");
        EXITFUNC;
        return;
    }

    // Use grid fonts for accurate measurement
    // Title font may differ from cell font

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
void __fastcall TFormMain::BestFitAll(TDBGrid* Grid, int maxrow, int padding)
{
    for (int x = 0; x < Grid->Columns->Count; x++)
        BestFitDBGridColumn(Grid, Grid->Columns->Items[x], maxrow, padding);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionExport(TObject* Sender)
{
    // empty table?

    if (FDMemTable1->RecordCount == 0)
    {
        StatusBar1->SimpleText = "Nothing to export.";
        Beep();
        EXITFUNC;
        return;
    }

    // lambda to create and sanitize a suggested filename

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
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionAbout(TObject* Sender)
{
    AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionAutoFit(TObject* Sender)
{
    BestFitAll(DBGrid1, 0, 24);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::actCheckUpdatesExecute(TObject* Sender)
{
    String Url, InfoText, VersionText, FileName;

    if (CheckUpdate(Url, VersionText, InfoText) == false)
    {
        Beep();
        ShowMessage("You have the latest version.");
        LogInfo("No update.");
        EXITFUNC;
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
        DL->Show();
        DL->GetFile(Url, FileName);
        DL->Close();
        if (!FileName.IsEmpty())
        {
            ShowMessage("Download complete. Application will close and update will proceed.");
            ShellExecute(NULL, L"open", FileName.c_str(), NULL, NULL, SW_SHOW);
            Close();
        }
        LogWarn("Empty filename.");
    } else
        LogInfo("Chose not to unstall update.");
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionLiveNet(TObject* Sender)
{
    RefreshTimer->Enabled = false;
    FormActiveNets->ShowModal();
    if (FormActiveNets->ModalResult == mrOk)
    {
        ActiveNet = FormActiveNets->FDMemTabNetName->AsString;
        ActiveServer = FormActiveNets->FDMemTabServer->AsString;
        edNET->Text = ActiveNet;
        edFreq->Text = FormActiveNets->FDMemTabFrequency->AsString;
        edBand->Text = FormActiveNets->FDMemTabBand->AsString;
        edMode->Text = FormActiveNets->FDMemTabMode->AsString;
        edNetControl->Text = FormActiveNets->FDMemTabNetControl->AsString;
        edLogger->Text = FormActiveNets->FDMemTabLogger->AsString;
        edSubscribe->Text = FormActiveNets->FDMemTabSubscriberCount->AsString;
        ActiveDataUpdate();
    }
}
//---------------------------------------------------------------------------


void __fastcall TFormMain::DBGrid1TitleClick(TColumn *Column)
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
//---------------------------------------------------------------------------

void __fastcall TFormMain::DBGrid1SortedField(TLabeledDbGrid *Sender, TField *Field, TCBSortOrder &Sorted)
{
    if (SameText(SortField, Field->DisplayName))
        Sorted = Ascending ? TCBSortOrder::soAscending : TCBSortOrder::soDescending;
    else
        Sorted = TCBSortOrder::soNone;

}
//---------------------------------------------------------------------------

