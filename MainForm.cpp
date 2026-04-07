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

#include "Download.h"
#include "Select.h"
#include "WinVersionQuery.h"
#include "about.h"
#include "preferences.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain* FormMain;

#include <Vcl.HtmlHelpViewer.hpp>
#pragma link "vcl.HtmlHelpViewer"

#include <cctype>
#include <fstream>
#include <iostream>

#include "updateInfo.h"
#include "Log.h"

#include "DashTypes.h"

void LogPairs(String msg, Vpairs list)
{
    CodeSite->Send(csmInfo, msg);
    CodeSite->AddSeparator();
    for (auto Entry : list)
    {
        String s1, s2;
        s1 = Entry.first;
        s2 = Entry.second;
        CodeSite->Send(csmInfo, s1 + " = " + s2);
    }
    CodeSite->AddSeparator();
}

#ifdef _WIN64
    #pragma comment(lib, "CodeSiteExpressPkg.a")
#endif

#ifdef __WIN32__
    #pragma comment(lib, "CodeSiteExpressPkg.lib")
#endif

#pragma link "CodeSiteLogging"

#define TABLENAME "DASH"

const char* TableDef = "CREATE TABLE " TABLENAME "( SerialNo VARCHAR(255), Callsign VARCHAR(255),"
                       "State VARCHAR(255), Remarks VARCHAR(255),"
                       "QSLInfo VARCHAR(255), CityCountry VARCHAR(255),"
                       "FirstName VARCHAR(255), Status VARCHAR(255),"
                       "County VARCHAR(255), Grid VARCHAR(255),"
                       "Street VARCHAR(255), Zip VARCHAR(255),"
                       "MemberID VARCHAR(255), Country VARCHAR(255),"
                       "DXCC VARCHAR(255),PreferredName VARCHAR(255))";

#define REG_ROOT "Software\\WG5ENE\\DASHBOARD"

static const char* PgmKey = REG_ROOT;
static const char* FieldKey = REG_ROOT "\\Columns";

#define FONT_ID 1




/// <summary> Removes the specified item from the collection
/// </summary>
/// <param name="Filename">The item to remove
/// </param>
/// <param name="Collection">The group containing the item
/// </param>
/// <remarks>
/// If parameter "Item" is null, an exception is raised.
/// <see cref="EArgumentNilException"/>
/// </remarks>
/// <returns>void True if the specified item is successfully removed;
/// otherwise False is returned.
/// </returns>

void __fastcall TFormMain::ExportCSV(String Filename)
{
    ENTERFUNC;

    const char* comma = ",";
    const char* quote = "\"";
    std::wfstream strm;

    int cur_rec = FDTable1->RecNo;

    // retry in case some other application has the file open in some non-shared
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

    for (int x = 0; x < FDTable1->Fields->Count; x++)
    {
        if (x > 0)
            strm << comma;

        strm << quote << FDTable1->Fields->Fields[x]->FieldName.c_str() << quote;
    }

    strm << std::endl;

    // write records

    FDTable1->BeginBatch();
    FDTable1->First();

    for (int x = 0; x < FDTable1->RecordCount; x++)
    {
        if (x > 0)
            strm << std::endl;

        for (int y = 0; y < FDTable1->FieldCount; y++)
        {
            if (y > 0)
                strm << comma;

            strm << quote
                 << FDTable1->FieldByName(FDTable1->Fields->Fields[y]->FieldName)->AsString.c_str()
                 << quote;
        }

        FDTable1->Next();
    }

    strm.close();
    FDTable1->RecNo = cur_rec;
    FDTable1->EndBatch();
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
void __fastcall TFormMain::SetGrid(CheckinList* clist)
{
    ENTERFUNC;

    if (!clist) // huh?
    {
        LogInfo("clist is null.");
        EXITFUNC;
        return;
    }

    LogInfo("Chkins size: " + IntToStr((int)clist->Checkins.size()));

    // simple lambda to insert a a check-in record to the table

    auto addrec = [this](const Vpairs& list) mutable {
        FDTable1->Append();
        FDTable1->Edit();

        for (auto Item : list)
            FDTable1->FieldByName(Item.first)->AsString = Item.second;

        FDTable1->Post();
        FDTable1->Next();
    };

    FDTable1->BeginBatch(); // prevent gui updating until all done

    int recno = -1;
    int Pointer = StrToInt(clist->Data[ND_POINTER]);
    FDTable1->First();
    FDTable1->EmptyDataSet();

    for (auto Item : clist->Checkins)
    {
        addrec(Item);
        if (Pointer == StrToInt(Item[ND_SERIALNO]))
        { // The NC's currently highlighted record
            recno = FDTable1->RecNo;
        }
    }

    if (recno >= 0)
    {
        FDTable1->RecNo = recno;
    }
    FDTable1->EndBatch();

    String msg = IntToStr(FDTable1->RecordCount) + " records retrieved.";
    StatusBar1->SimpleText = msg;
    EXITFUNC;
};
//---------------------------------------------------------------------------
void __fastcall TFormMain::DBGrid1DblClick(TObject* Sender)
{
    ENTERFUNC;
    String Callsign, Cmd;

    if (FDTable1->RecordCount > 0)
    {
        Callsign = FDTable1->FieldValues["CallSign"];

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
    ENTERFUNC;
    LogInfo("Shell: " + cmd);
    ShellExecuteW(NULL, L"open", cmd.c_str(), NULL, NULL, SW_SHOWNORMAL);
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SaveDefaults()
{
    ENTERFUNC;
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
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::LoadDefaults()
{
    ENTERFUNC;
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
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormClose(TObject* Sender, TCloseAction& Action)
{
    ENTERFUNC;
    SaveDefaults();

    // don't leave font resource hanging..

    if (ClockFontHandle != INVALID_HANDLE_VALUE)
        RemoveFontMemResourceEx(ClockFontHandle);
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DataUpdate(const String& netname)
{
    ENTERFUNC;
    Vpairs netinfo;

    if (!netname.IsEmpty())
    {
        LogInfo(netname);
        Application->ProcessMessages();
        CurrentNet = netname;
        if (DMod->GetNetData(netname, netinfo))
        {
            CheckinList* chklist = DMod->GetLiveCheckins(netname);
            if (chklist != nullptr)
            {
                actExportCSV->Enabled = true;

                edNET->Text = netinfo[ND_NETNAME];
                edFreq->Text = netinfo[ND_FREQ];
                edBand->Text = netinfo[ND_BAND];
                edMode->Text = netinfo[ND_MODE];
                edNetControl->Text = netinfo[ND_NETCONTROL];
                edLogger->Text = netinfo[ND_LOGGER];
                edSubscribe->Text = netinfo[ND_SUBCOUNT];
                SetGrid(chklist);
            } else
            {
                StatusBar1->SimpleText = CurrentNet + " is now closed.";
                CurrentNet = "";
                LogInfo(StatusBar1->SimpleText);
            }
        } else
            LogInfo("Failed to get net data.");
    } else
        LogInfo("No net given.");
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormShow(TObject* Sender)
{
    ENTERFUNC;
    UpdateClockDisplay();
    ClockTimer->Enabled = true;
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenDatabase()
{
    ENTERFUNC;
    try
    {
        int index = FDConnection1->Params->IndexOfName("Database");

        // use empty database name to default to an in-memory db

        FDConnection1->Params->ValueFromIndex[index] = "";
        FDConnection1->Connected = true;
        FDConnection1->ExecSQL(TableDef);
        FDTable1->TableName = TABLENAME;
        FDTable1->Active = true;
        LogInfo("Database opened.");

    } catch (Exception* err)
    {
        LogExcept(err);
    }

    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::RefreshTimerTimer(TObject* Sender)
{
    ENTERFUNC;
    DataUpdate(CurrentNet);
    EXITFUNC;
}
//---------------------------------------------------------------------------
bool __fastcall TFormMain::CheckUpdate(String& Url, String& VersionText, String& InfoText)
{
    ENTERFUNC;

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
    EXITFUNC;
    return false;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::FormCreate(TObject* Sender)
{
    CodeSite->Clear();

    ENTERFUNC;

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

    OpenDatabase();

    // ColMap lets us reference a TColumn directly by its field name

    for (int x = 0; x < DBGrid1->Columns->Count; x++)
    {
        DBGrid1->Columns->Items[x]->Width = 64;
        ColMap.insert({ DBGrid1->Columns->Items[x]->FieldName, DBGrid1->Columns->Items[x] });
    }
    LoadDefaults();
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall BestFitDBGridColumn(
    TDBGrid* Grid, TColumn* Col, int MaxRowsToScan /*0 = all*/, int Padding /*pixels*/)
{
    ENTERFUNC;
    LogInfo(Col->Title->Caption);

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
        LogInfo("New col width  = " + IntToStr(Col->Width));
    } __finally
    {
        Grid->Canvas->Font->Assign(oldFont.get());
    }
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall BestFitAll(TDBGrid* Grid, int maxrows = 0, int padding = 0)
{
    ENTERFUNC;
    for (int x = 0; x < Grid->Columns->Count; x++)
        BestFitDBGridColumn(Grid, Grid->Columns->Items[x], maxrows, padding);
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionExport(TObject* Sender)
{
    ENTERFUNC;

    // empty table?

    if (FDTable1->RecordCount == 0)
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
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionAbout(TObject* Sender)
{
    ENTERFUNC;
    AboutBox->ShowModal();
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionPreferences(TObject* Sender)
{
    ENTERFUNC;
    String curstyle = Vcl::Themes::TStyleManager::ActiveStyle->Name;
    FormPrefs->SpinEdit1->Value = RefreshRate;

    if (FormPrefs->ShowModal() == mrOk)
        RefreshRate = FormPrefs->SpinEdit1->Value;
    else
    {
        if (Vcl::Themes::TStyleManager::ActiveStyle->Name != curstyle)
            Vcl::Themes::TStyleManager::TrySetStyle(curstyle);
    }
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::ActionAutoFit(TObject* Sender)
{
    ENTERFUNC;
    BestFitAll(DBGrid1, 0, 10);
    EXITFUNC;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::actCheckUpdatesExecute(TObject* Sender)
{
    ENTERFUNC;
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
    EXITFUNC;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::ActionLiveNet(TObject* Sender)
{
    ENTERFUNC;
    Cursor = crHourGlass;
    RefreshTimer->Enabled = false;
    int selected;
    FormSelect->ShowModal();
    selected = FormSelect->ListBox1->ItemIndex;

    if (FormSelect->ModalResult == mrOk && selected != -1)
    {
        DataUpdate(FormSelect->ListBox1->Items->Strings[selected]);
    }

    ActiveControl = DBGrid1;
    Cursor = crDefault;
    RefreshTimer->Enabled = true;
    EXITFUNC;
}
//---------------------------------------------------------------------------

