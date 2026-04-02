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

#pragma comment(lib, "CodeSiteExpressPkg.lib")
#pragma link "CodeSiteLogging"
#include "CodeSiteLogging.hpp"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMain* FormMain;

const String DBName("Dashboard.sdb");
const String TableName("NETLOGGER");

const String CreateTable("CREATE TABLE NETLOGGER"
                         "( SerialNo VARCHAR(255), Callsign VARCHAR(255),"
                         "State VARCHAR(255), Remarks VARCHAR(255),"
                         "QSLInfo VARCHAR(255), CityCountry VARCHAR(255),"
                         "FirstName VARCHAR(255), Status VARCHAR(255),"
                         "County VARCHAR(255), Grid VARCHAR(255),"
                         "Street VARCHAR(255), Zip VARCHAR(255),"
                         "MemberID VARCHAR(255), Country VARCHAR(255),"
                         "DXCC VARCHAR(255),PreferredName VARCHAR(255))");

//---------------------------------------------------------------------------
#include "updateInfo.h"
#include <fstream>
#include <iostream>
<<<<<<< Updated upstream

void __fastcall TFormMain::ExportCSV(String Filename)
{
	const char* comma = ",";
	const char* quote = "\"";
	std::wfstream strm;
=======
#include <cctype>

#include <Vcl.HtmlHelpViewer.hpp>
#pragma link "vcl.HtmlHelpViewer"

#ifdef _WIN64
    #pragma comment(lib, "CodeSiteExpressPkg.a")
#endif

#pragma link "CodeSiteLogging"
#include "CodeSiteLogging.hpp"

#define ENTERFUNC CodeSite->EnterMethod(__FUNC__)
#define EXITFUNC CodeSite->ExitMethod(__FUNC__)
#define LogInfo(str) CodeSite->Send(csmInfo, (UnicodeString)str)
#define LogWarn(str) CodeSite->Send(csmWarning, (UnicodeString)str)
#define LogExcept(ex) CodeSite->SendException(ex);

#define TABLENAME "NETLOGGER"
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

//---------------------------------------------------------------------------
// Save the grid table to a comma delimited file

void __fastcall TFormMain::ExportCSV(String Filename)
{
    ENTERFUNC;

    const char* comma = ",";
    const char* quote = "\"";
    std::wfstream strm;
>>>>>>> Stashed changes

	int cur_rec = FDTable1->RecNo;

// in case some other process has our file opem in non-shared mode
retry:
<<<<<<< Updated upstream
	strm.open(Filename.c_str(), strm.binary | strm.trunc | strm.in | strm.out);
	if (!strm.is_open()) {
		String msg = "Unable to open file \"" + Filename + "\".";
		int result = MessageDlg(msg, mtError, mbAbortRetryIgnore, 0);
		if (result != mrRetry)
			return;
		goto retry;
	}

	// write field names
	for (int x = 0; x < FDTable1->Fields->Count; x++) {
		if (x > 0)
			strm << comma;
		strm << quote << FDTable1->Fields->Fields[x]->FieldName.c_str() << quote;
	}

	strm << std::endl;
=======
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
>>>>>>> Stashed changes

	// write records

<<<<<<< Updated upstream
	FDTable1->BeginBatch();
	FDTable1->First();
	for (int x = 0; x < FDTable1->RecordCount; x++) {
		if (x > 0)
			strm << std::endl;
		for (int y = 0; y < FDTable1->FieldCount; y++) {
			if (y > 0)
				strm << comma;
			strm << quote << FDTable1->FieldByName(FDTable1->Fields->Fields[y]->FieldName)->AsString.c_str() << quote;
		}
		FDTable1->Next();
	}
	strm.close();
	FDTable1->RecNo = cur_rec;
	FDTable1->EndBatch();
=======
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
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------

// *IMPORTANT*
//
// Make sure that both FDConection1->Active and FDTable1->Active are set
// to false in the degsin-time editors BEFORE building a release.
//
// Otherwise, the database runtime will throw an exception and die trying to
// open a database that doesn't exist yet!

#define LEDFONT "alarm clock.ttf"

__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
}
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

	panDate->Caption = (now - offset).FormatString(DateFormat);
	panClock->Caption = (now - offset).FormatString(TimeFormat);
	panZone->Caption = UTC ? "Universal Time Coordinated" : TTimeZone::Local->DisplayName;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::StatusBar1DrawPanel(TStatusBar* StatusBar,
	TStatusPanel* Panel,
	const TRect& Rect)
{
<<<<<<< Updated upstream
	int index = LEDOn ? 1 : 0;
	TCanvas* canvas = StatusBar->Canvas;
	ImageList1->Draw(canvas, Rect.Left, Rect.Top, index);
}
=======
    ENTERFUNC;

    if (!clist) // huh?
    {
        LogInfo("clist is null.");
        return;
    }

    // simple lambda to insert a a check-in record to the table

    auto addrec = [this](const NLCheckin& ck) mutable {
        FDTable1->Append();
        FDTable1->Edit();
        FDTable1->FieldByName("SerialNo")->AsString = ck.SerialNo;
        FDTable1->FieldByName("CallSign")->AsString = ck.Callsign;
        FDTable1->FieldByName("State")->AsString = ck.State;
        FDTable1->FieldByName("Remarks")->AsString = ck.Remarks;
        FDTable1->FieldByName("QSLInfo")->AsString = ck.QSLInfo;
        FDTable1->FieldByName("CityCountry")->AsString = ck.CityCountry;
        FDTable1->FieldByName("FirstName")->AsString = ck.FirstName;
        FDTable1->FieldByName("Status")->AsString = ck.Status;
        FDTable1->FieldByName("County")->AsString = ck.County;
        FDTable1->FieldByName("Grid")->AsString = ck.Grid;
        FDTable1->FieldByName("Street")->AsString = ck.Street;
        FDTable1->FieldByName("Zip")->AsString = ck.Zip;
        FDTable1->FieldByName("MemberID")->AsString = ck.MemberID;
        FDTable1->FieldByName("Country")->AsString = ck.Country;
        FDTable1->FieldByName("DXCC")->AsString = ck.DXCC;
        FDTable1->FieldByName("PreferredName")->AsString = ck.PreferredName;
        FDTable1->Post();
        FDTable1->Next();
    };

    FDTable1->BeginBatch(); // prevent gui updating until all done

    int recno = -1;
    FDTable1->First();
    FDTable1->EmptyDataSet();

    for (auto Item : clist->Checkins)
    {
        addrec(Item);

        if (clist->Pointer == Item.SerialNo)
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
    LogInfo(IntToStr(FDTable1->RecordCount) + " recs.");
    StatusBar1->SimpleText = msg;
    EXITFUNC;
};

>>>>>>> Stashed changes
//---------------------------------------------------------------------------
void __fastcall TFormMain::LED(bool state)
{
	LEDOn = state;
	StatusBar1->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::SetGrid(CheckinList* clist)
{

	if (!clist)
		return;

	auto addrec = [this](const NLCheckin& ck) mutable {
		FDTable1->Append();
		FDTable1->Edit();
		FDTable1->FieldByName("SerialNo")->AsString = ck.SerialNo;
		FDTable1->FieldByName("CallSign")->AsString = ck.Callsign;
		FDTable1->FieldByName("State")->AsString = ck.State;
		FDTable1->FieldByName("Remarks")->AsString = ck.Remarks;
		FDTable1->FieldByName("QSLInfo")->AsString = ck.QSLInfo;
		FDTable1->FieldByName("CityCountry")->AsString = ck.CityCountry;
		FDTable1->FieldByName("FirstName")->AsString = ck.FirstName;
		FDTable1->FieldByName("Status")->AsString = ck.Status;
		FDTable1->FieldByName("County")->AsString = ck.County;
		FDTable1->FieldByName("Grid")->AsString = ck.Grid;
		FDTable1->FieldByName("Street")->AsString = ck.Street;
		FDTable1->FieldByName("Zip")->AsString = ck.Zip;
		FDTable1->FieldByName("MemberID")->AsString = ck.MemberID;
		FDTable1->FieldByName("Country")->AsString = ck.Country;
		FDTable1->FieldByName("DXCC")->AsString = ck.DXCC;
		FDTable1->FieldByName("PreferredName")->AsString = ck.PreferredName;
		FDTable1->Post();
		FDTable1->Next();
	};

	FDTable1->BeginBatch(); // prevent gui updating until all done
	FDTable1->First();
	int recno = -1;
	FDTable1->EmptyDataSet();
	for (auto Item : clist->Checkins) {
		addrec(Item);
		if (clist->Pointer == Item.SerialNo) {
			recno = FDTable1->RecNo;
		}
	}
	if (recno >= 0) {
		FDTable1->RecNo = recno;
	}
	FDTable1->EndBatch();
	String msg = IntToStr(FDTable1->RecordCount) + " records retrieved.";
	StatusBar1->Panels->Items[1]->Text = msg;
};
//---------------------------------------------------------------------------
void __fastcall TFormMain::btnNetsClick(TObject* Sender)
{
<<<<<<< Updated upstream
	RefreshTimer->Enabled = false;
	int selected;
=======
    ENTERFUNC;
    RefreshTimer->Enabled = false;
    int selected;
>>>>>>> Stashed changes

	FormSelect->ShowModal();
	selected = FormSelect->ListBox1->ItemIndex;

	if (FormSelect->ModalResult == mrOk && selected != -1) {
		DataUpdate(FormSelect->ListBox1->Items->Strings[selected]);
	}

<<<<<<< Updated upstream
	ActiveControl = DBGrid1;
	RefreshTimer->Enabled = true;
=======
    ActiveControl = DBGrid1;
    RefreshTimer->Enabled = true;
    EXITFUNC;
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Preferences1Click(TObject* Sender)
{
<<<<<<< Updated upstream
	String curstyle = Vcl::Themes::TStyleManager::ActiveStyle->Name;
	FormPrefs->CSpinEdit1->Value = RefreshRate;
	if (FormPrefs->ShowModal() == mrOk) {
		RefreshRate = FormPrefs->CSpinEdit1->Value;
	} else {
		if (Vcl::Themes::TStyleManager::ActiveStyle->Name != curstyle)
			Vcl::Themes::TStyleManager::TrySetStyle(curstyle);
	}
=======
    ENTERFUNC;
    String curstyle = Vcl::Themes::TStyleManager::ActiveStyle->Name;
    FormPrefs->SpinEdit1->Value = RefreshRate;

    if (FormPrefs->ShowModal() == mrOk)
    {
        RefreshRate = FormPrefs->SpinEdit1->Value;

    } else
    {
        if (Vcl::Themes::TStyleManager::ActiveStyle->Name != curstyle)
            Vcl::Themes::TStyleManager::TrySetStyle(curstyle);
    }
    EXITFUNC;
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Help1Click(TObject* Sender)
{
<<<<<<< Updated upstream
	using System::Ioutils::TPath;
	String Path, Filename;

	// pdf help will be in same dir as executable
	Path = TPath::GetAppPath();
	Filename = TPath::Combine(Path, "Dashboard.pdf");
	Shell(Filename);
=======
    ENTERFUNC;
    Application->HelpKeyword("Introduction");
    EXITFUNC;
>>>>>>> Stashed changes
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::DBGrid1DblClick(TObject* Sender)
{
<<<<<<< Updated upstream
	String Callsign, Cmd;
	if (FDTable1->RecordCount > 0) {
		Callsign = FDTable1->FieldValues["CallSign"];
=======
    ENTERFUNC;
    String Callsign, Cmd;
>>>>>>> Stashed changes

		if (Callsign.IsEmpty())
			return;

<<<<<<< Updated upstream
		Cmd = "https://qrz.com/db/" + Callsign;
		Shell(Cmd);
	}
=======
        if (Callsign.IsEmpty()) // huh?
        {
            LogInfo("Callsign field is empty.");
            return;
        }

        Cmd = "https://qrz.com/db/" + Callsign;
        Shell(Cmd);
    }
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Shell(String cmd)
{
<<<<<<< Updated upstream
	ShellExecuteW(NULL, L"open", cmd.c_str(), NULL, NULL, SW_SHOWNORMAL);
=======
    ENTERFUNC;
    LogInfo("Shell: " + cmd);
    ShellExecuteW(NULL, L"open", cmd.c_str(), NULL, NULL, SW_SHOWNORMAL);
    EXITFUNC;
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------
<<<<<<< Updated upstream
//
// save each grid column's visibility, width, and index to the Registry
//
static const char* fieldkey = "Software\\WG5ENE\\DASHBOARD\\Columns";
static const char* pgmkey = "Software\\WG5ENE\\DASHBOARD";

void __fastcall TFormMain::SaveDefaults()
{
	TRegistry* Reg = 0;
	try {
		Reg = new TRegistry(KEY_WRITE);
		Reg->RootKey = HKEY_CURRENT_USER;
		Reg->OpenKey(fieldkey, true);

		auto writefield = [this, &Reg](TColumn* col) {
			Reg->OpenKey(fieldkey, false);
			Reg->OpenKey(col->FieldName, true);
			Reg->WriteBool("Visible", col->Visible);
=======

//---------------------------------------------------------------------------
// save each grid column's visibility, width, and index to the Registry

void __fastcall TFormMain::SaveDefaults()
{
    ENTERFUNC;
    std::unique_ptr<TRegistry> Reg;

    try
    {
        Reg = std::make_unique<TRegistry>(KEY_WRITE);
        Reg->RootKey = HKEY_CURRENT_USER;
        Reg->OpenKey(FieldKey, true);
>>>>>>> Stashed changes

			col->Visible = true; // need this since col width is reported
				// as -1 when col not visible

<<<<<<< Updated upstream
			Reg->WriteInteger("Width", col->Width);
			Reg->WriteInteger("Index", col->Index);
			Reg->CloseKey();
		};

		for (int x = 0; x < DBGrid1->Columns->Count; x++)
			writefield(DBGrid1->Columns->Items[x]);
=======
        auto writefield = [this, &Reg](TColumn* col) {
            Reg->OpenKey(FieldKey, false);
            Reg->OpenKey(col->FieldName, true);
            Reg->WriteBool("Visible", col->Visible);

            col->Visible = true; // need  to do this here since the col width is
            // incorrectly reported as -1 when col is not visible
>>>>>>> Stashed changes

		// save window state
		Reg->OpenKey(pgmkey, true);
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
	} catch (Exception* err) {

<<<<<<< Updated upstream
		CodeSite->SendException(__FUNC__, err);
    }
    if (Reg)
        delete Reg;
=======
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
>>>>>>> Stashed changes
}

//
// restore saved columns order and widths from registry
//
void __fastcall TFormMain::LoadDefaults()
{
<<<<<<< Updated upstream
    TRegistry* Reg = NULL;
=======
    ENTERFUNC;
    std::unique_ptr<TRegistry> Reg;
>>>>>>> Stashed changes
    std::map<int, TColumn*> IndexingMap;

    try {
        Reg = new TRegistry(KEY_READ);
        Reg->RootKey = HKEY_CURRENT_USER;
        Reg->OpenKeyReadOnly(FieldKey);

        // read column data.
        // save an index/column map for later use in a *second* pass

        auto readfield = [this, &Reg, &IndexingMap](TColumn* Column) {
<<<<<<< Updated upstream
            Reg->OpenKeyReadOnly(fieldkey);
=======
            Reg->OpenKeyReadOnly(FieldKey);

>>>>>>> Stashed changes
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

		// get window state

		if (Reg->OpenKeyReadOnly(pgmkey)) {

<<<<<<< Updated upstream
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
=======
        if (Reg->OpenKeyReadOnly(PgmKey))
        {
            Vcl::Themes::TStyleManager::TrySetStyle(Reg->ReadString("Style"));
>>>>>>> Stashed changes

		// we must set the columns' display order indexes in *ordinal* fashion
		// because of the left to right 'swapping' method Delphi uses to reorder
		// moved TColumns

		for (auto Item : IndexingMap)
			Item.second->Index = Item.first;

	} catch (Exception* err) {

<<<<<<< Updated upstream
		CodeSite->SendException(__FUNC__, err);
	}
	if (Reg)
		delete Reg;
=======
        for (auto Item : IndexingMap)
            Item.second->Index = Item.first;

    } catch (Exception* err)
    {
        LogExcept(err);
        // do nothing
    }
    EXITFUNC;
>>>>>>> Stashed changes
}

void __fastcall TFormMain::FormClose(TObject* Sender, TCloseAction& Action)
{
<<<<<<< Updated upstream
	CodeSite->SendMsg(csmInfo, String("Dashboard exited:  ") + TDateTime::CurrentDateTime().DateTimeString());
	SaveDefaults();
=======
    ENTERFUNC;
    SaveDefaults();

    // don't leave font resource hanging..

    if (ClockFontHandle != INVALID_HANDLE_VALUE)
        RemoveFontMemResourceEx(ClockFontHandle);
    EXITFUNC;
>>>>>>> Stashed changes
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::Exit1Click(TObject* Sender)
{
<<<<<<< Updated upstream
	RefreshTimer->Enabled = false;
	ClockTimer->Enabled = false;
	FDTable1->Active = false;
	FDConnection1->Connected = false;
	Close();
=======
    ENTERFUNC;
    RefreshTimer->Enabled = false;
    ClockTimer->Enabled = false;
    FDTable1->Active = false;
    FDConnection1->Connected = false;
    Close();
    EXITFUNC;
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::About1Click(TObject* Sender)
{
<<<<<<< Updated upstream
	AboutBox->ShowModal();
=======
    ENTERFUNC;
    AboutBox->ShowModal();
    EXITFUNC;
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Export1Click(TObject* Sender)
{
<<<<<<< Updated upstream
	if (FDTable1->RecordCount == 0) {
		StatusBar1->Panels->Items[1]->Text = "Nothing to export.";
		return;
	}

	if (SaveDialog1->Execute())
		ExportCSV(SaveDialog1->FileName);
=======
    ENTERFUNC;
    // empty table?

    if (FDTable1->RecordCount == 0)
    {
        StatusBar1->SimpleText = "Nothing to export.";
        Beep();
        LogInfo(" 0 recs");
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
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DataUpdate(const String& netname)
{
<<<<<<< Updated upstream
	CheckinList* CList = NULL;
	NLNet net;

	if (!netname.IsEmpty()) {
		LED(true);
		Application->ProcessMessages();
		CurrentNet = netname;
		if (DMod->GetNetData(netname, net)) {
			CList = DMod->GetCheckins(netname);
			if (CList != NULL) {
				edNET->Text = net.NetName;
				edFreq->Text = net.Frequency;
				edBand->Text = net.Band;
				edMode->Text = net.Mode;
				edNetControl->Text = net.NetControl;
				edLogger->Text = net.Logger;
				edSubscribe->Text = net.SubscriberCount;
				SetGrid(CList);
			} else {
				StatusBar1->Panels->Items[1]->Text = CurrentNet + " closed.";
				CurrentNet = "";
			}
		}
		LED(false);
	}
=======
    ENTERFUNC;
    CheckinList* CList = NULL;
    NLNet net;

    if (!netname.IsEmpty())
    {
        LogInfo(netname);
        Application->ProcessMessages();
        CurrentNet = netname;
        if (DMod->GetNetData(netname, net))
        {
            CList = DMod->GetCheckins(netname);
            if (CList != NULL)
            {
                edNET->Text = net.NetName;
                edFreq->Text = net.Frequency;
                edBand->Text = net.Band;
                edMode->Text = net.Mode;
                edNetControl->Text = net.NetControl;
                edLogger->Text = net.Logger;
                edSubscribe->Text = net.SubscriberCount;
                SetGrid(CList);
            } else
            {
                StatusBar1->SimpleText = CurrentNet + " is now closed.";
                CurrentNet = "";
                LogInfo(StatusBar1->SimpleText);
            }
        } else
            LogInfo("Failed to get net data.");
    } else
        LogInfo("No net.");
    EXITFUNC;
>>>>>>> Stashed changes
}

void __fastcall TFormMain::FormShow(TObject* Sender)
{
<<<<<<< Updated upstream
	UpdateClockDisplay();
	ClockTimer->Enabled = true;
=======
    ENTERFUNC;
    UpdateClockDisplay();
    ClockTimer->Enabled = true;
    EXITFUNC;
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenDatabase()
{
<<<<<<< Updated upstream
	String _userdb;

	_userdb = TPath::GetHomePath() + TPath::DirectorySeparatorChar + DBName;
	int index = FDConnection1->Params->IndexOfName("Database");

	FDConnection1->Params->ValueFromIndex[index] = _userdb;

	if (FileExists(_userdb)) {
		DeleteFile(_userdb);
	}
=======
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
>>>>>>> Stashed changes
}

void __fastcall TFormMain::RefreshTimerTimer(TObject* Sender)
{
<<<<<<< Updated upstream
	DataUpdate(CurrentNet);
=======
    ENTERFUNC;
    DataUpdate(CurrentNet);
    EXITFUNC;
>>>>>>> Stashed changes
}
//---------------------------------------------------------------------------
// query the Dashboard application's web update server

<<<<<<< Updated upstream
void __fastcall TFormMain::nmUpdatesClick(TObject* Sender)
{
	TRESTClient* Client = NULL;
	TRESTRequest* Request = NULL;
	TRESTResponse* Response = NULL;
	TXMLDocument* Document = NULL;

	Utility::WinVersionQuery wver;
	Utility::VerStr vstr;
	vstr = wver.GetStr("FileVersion");

	try {

		Client = new TRESTClient(this);
		Client->BaseURL = "https://gajewski.net/update";
		Response = new TRESTResponse(this);
		Request = new TRESTRequest(this);
		Request->Client = Client;
		Request->Resource = "Dashboard-Update.php";
		Request->Response = Response;
		Request->Params->AddItem(L"maj", IntToStr(vstr.Major), pkGETorPOST);
		Request->Params->AddItem(L"min", IntToStr(vstr.Major), pkGETorPOST);
		Request->Params->AddItem(L"rel", IntToStr(vstr.Release), pkGETorPOST);
		Request->Params->AddItem(L"bld", IntToStr(vstr.Build), pkGETorPOST);
		Document = new TXMLDocument(this);

		Request->Execute();

		if (Response->StatusCode == 200) {
			_di_IXMLNode Node;

			Document->LoadFromXML(Response->Content);
			Document->Active = true;
			Node = Document->DocumentElement;

			// Hat tip to the Notepad++ updater here
			if (Node->NodeName == "GUP") {
				String Answer, Location, Version, Filename, Info;

				Answer = Node->ChildValues["NeedToBeUpdated"];
				if (Answer == "yes") {
					Location = Node->ChildValues["Location"];
					Version = Node->ChildValues["Version"];
					Info = Node->ChildValues["Info"];
					UpdInfo->RichEdit1->Text = Info;

					String text = "An updated version ";
					text += Version;
					text += " is available.\nDownload and install this update?";
					UpdInfo->Label1->Caption = text;
					UpdInfo->ShowModal();

					if (UpdInfo->ModalResult == mrOk) {
						DL->Show();
						DL->GetFile(Location, Filename);
						DL->Close();
						if (!Filename.IsEmpty()) {
							ShowMessage(
								"Download complete. Application will close and update will proceed.");
							ShellExecute(NULL, L"open", Filename.c_str(), NULL,
								NULL, SW_SHOW);
							Close();
						}
					}
				} else
					ShowMessage("You have the latest version.");
			}
		}
	} catch (Exception* err) {

		CodeSite->SendException(__FUNC__,err);
	}
	if (Response)
		delete Response;
	if (Request)
		delete Request;
	if (Client)
		delete Client;
	if (Document)
		delete Document;
=======
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
// check Dashboard application's web update server

void __fastcall TFormMain::nmUpdatesClick(TObject* Sender)
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
        LogInfo("Choose not to unstall update.");
    EXITFUNC;
>>>>>>> Stashed changes
}

#define _LOGFILE_

void __fastcall TFormMain::FormCreate(TObject* Sender)
{
<<<<<<< Updated upstream
#ifdef _LOGFILE_
	TCodeSiteDestination* dest = new TCodeSiteDestination(this);
	dest->LogFile->Active = true;
	dest->LogFile->FileName = "DASHBOARD.csl";
	String fpath = TPath::GetTempPath();
	dest->LogFile->FilePath = fpath;
	CodeSite->Destination = dest;
#endif

	CodeSite->SendMsg(csmInfo, String("Dashboard started:  ") + TDateTime::CurrentDateTime().DateTimeString());
	String filename = TPath::GetAppPath();
	filename = TPath::Combine(filename, LEDFONT);
	ledfont.Open(filename);

	OpenDatabase();
	FDConnection1->Connected = true;
	FDConnection1->ExecSQL(CreateTable);
	FDTable1->TableName = TableName;
	FDTable1->Active = true;

    for (int x = 0; x < DBGrid1->Columns->Count; x++) {
        DBGrid1->Columns->Items[x]->Width = 64;
        ColMap.insert({ DBGrid1->Columns->Items[x]->FieldName, DBGrid1->Columns->Items[x] });
    }

    LoadDefaults();
}
=======
    CodeSite->Clear();
    ENTERFUNC;

    try
	{
		DWORD font_count;
		std::unique_ptr<TResourceStream> rs;

		rs = std::make_unique<TResourceStream>(THandle(HInstance), "RESOURCE_1", RT_RCDATA);
		ClockFontHandle = AddFontMemResourceEx(rs->Memory, rs->Size, 0, &font_count);
		LogInfo("Clock font Loaded.");

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

void __fastcall CheckGridFont(TDBGrid* Grid)
{
	TColumn* col = nullptr;
	for (int x = 0; x < Grid->Columns->Count; x++, CodeSite->AddSeparator())
	{
		col = Grid->Columns->Items[x];
		LogInfo("Col: " + col->Title->Caption);
		LogInfo("Title Font: " + col->Title->Font->Name);
		LogInfo("Title Font size: " + col->Title->Font->Size);
	}
}

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
	TFont* oldFont = new TFont();
	LogInfo("OldFont: " + oldFont->Name);
	LogInfo("Size: " + IntToStr(oldFont->Size));
	LogInfo("TitleFont: " + Grid->TitleFont->Name);
	LogInfo("Size: " + IntToStr(Grid->TitleFont->Size));

	try
	{
		oldFont->Assign(Grid->Canvas->Font);

		// 1) Measure title/header


		Grid->Canvas->Font->Assign(Grid->TitleFont);
		int maxW = Grid->Canvas->TextWidth(Col->Title->Caption);

		LogInfo("Title Width = " + IntToStr(maxW));

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
		Grid->Canvas->Font->Assign(oldFont);
		delete oldFont;
	}
	EXITFUNC;
}

void __fastcall BestFitAll(TDBGrid* Grid, int maxrows, int padding)
{
	ENTERFUNC;

	LogInfo("Grid Font: " + Grid->Font->Name);
	LogInfo("GridFont Size: " + IntToStr(Grid->Font->Size));
	CodeSite->AddSeparator();
//	CheckGridFont(Grid);


	for (int x = 0; x < Grid->Columns->Count; x++)
		BestFitDBGridColumn(Grid, Grid->Columns->Items[x], maxrows, padding);
	EXITFUNC;
}

void __fastcall TFormMain::Fit1Click(TObject* Sender)
{
	ENTERFUNC;
	BestFitAll(DBGrid1, 0, 15);
	EXITFUNC;
}
>>>>>>> Stashed changes
//---------------------------------------------------------------------------

