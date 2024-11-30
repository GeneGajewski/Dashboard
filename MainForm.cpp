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

#include "Select.h"
#include "WinVersionQuery.h"
#include "about.h"
#include "preferences.h"
#include "Download.h"

//#pragma comment(lib, "CodeSiteExpressPkg.lib")
//#pragma link "CodeSiteLogging"
//#include "CodeSiteLogging.hpp"

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
#include <fstream>
#include <iostream>
#include "updateInfo.h"

void __fastcall TFormMain::ExportCSV(String Filename)
{
	const char* comma = ",";
	const char *quote = "\"";
	std::wfstream strm;

	int cur_rec = FDTable1->RecNo;

// in case some other process has our file opem in non-shared mode
retry:
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

	// write records

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
}
//---------------------------------------------------------------------------
__fastcall TFormMain::TFormMain(TComponent* Owner)
	: TForm(Owner)
{
	for (int x = 0; x < DBGrid1->Columns->Count; x++) {
		ColMap.insert({ DBGrid1->Columns->Items[x]->FieldName, DBGrid1->Columns->Items[x] });
	}
	LoadDefaults();
	OpenDatabase();
	FDConnection1->Connected = true;
	FDConnection1->ExecSQL(CreateTable);
	FDTable1->TableName = TableName;
	FDTable1->Active = true;
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
    int index = LEDOn ? 1 : 0;
    TCanvas* canvas = StatusBar->Canvas;
    ImageList1->Draw(canvas, Rect.Left, Rect.Top, index);
}
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
    RefreshTimer->Enabled = false;
    int selected;

    FormSelect->ShowModal();
    selected = FormSelect->ListBox1->ItemIndex;

    if (FormSelect->ModalResult == mrOk && selected != -1) {
        DataUpdate(FormSelect->ListBox1->Items->Strings[selected]);
    }

    ActiveControl = DBGrid1;
    RefreshTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Preferences1Click(TObject* Sender)
{
    String curstyle = Vcl::Themes::TStyleManager::ActiveStyle->Name;
    FormPrefs->CSpinEdit1->Value = RefreshRate;
    if (FormPrefs->ShowModal() == mrOk) {
        RefreshRate = FormPrefs->CSpinEdit1->Value;
    } else {
		if (Vcl::Themes::TStyleManager::ActiveStyle->Name != curstyle)
            Vcl::Themes::TStyleManager::TrySetStyle(curstyle);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Help1Click(TObject* Sender)
{
    using System::Ioutils::TPath;
    String Path, Filename;

    // pdf help will be in same dir as executable
    Path = TPath::GetAppPath();
    Filename = TPath::Combine(Path, "Dashboard.pdf");
    Shell(Filename);
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::DBGrid1DblClick(TObject* Sender)
{
    String Callsign, Cmd;
    if (FDTable1->RecordCount > 0) {
        Callsign = FDTable1->FieldValues["CallSign"];

        if (Callsign.IsEmpty())
            return;

        Cmd = "https://qrz.com/db/" + Callsign;
        Shell(Cmd);
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::Shell(String cmd)
{
    ShellExecuteW(NULL, L"open", cmd.c_str(), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
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

            col->Visible = true; // need this since col width is reported
                // as -1 when col not visible

            Reg->WriteInteger("Width", col->Width);
            Reg->WriteInteger("Index", col->Index);
            Reg->CloseKey();
        };

        for (int x = 0; x < DBGrid1->Columns->Count; x++)
            writefield(DBGrid1->Columns->Items[x]);

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
    } catch (ERegistryException&) {
    }
    if (Reg)
        delete Reg;
}

//
// restore saved columns order and widths from registry
//
void __fastcall TFormMain::LoadDefaults()
{
    TRegistry* Reg = NULL;
    std::map<int, TColumn*> IndexingMap;

    try {
        Reg = new TRegistry(KEY_READ);
        Reg->RootKey = HKEY_CURRENT_USER;
        Reg->OpenKeyReadOnly(fieldkey);

        // read column data.
		// save an index/column map for later use in a *second* pass

        auto readfield = [this, &Reg, &IndexingMap](TColumn* Column) {
            Reg->OpenKeyReadOnly(fieldkey);
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

        // we must set the columns' display order indexes in *ordinal* fashion
        // because of the left to right 'swapping' method Delphi uses to reorder
        // moved TColumns

        for (auto Item : IndexingMap)
            Item.second->Index = Item.first;

    } catch (ERegistryException& except) {
    }
    if (Reg)
        delete Reg;
}

void __fastcall TFormMain::FormClose(TObject* Sender, TCloseAction& Action)
{
    SaveDefaults();
}

//---------------------------------------------------------------------------

void __fastcall TFormMain::Exit1Click(TObject* Sender)
{
    RefreshTimer->Enabled = false;
    ClockTimer->Enabled = false;
    FDTable1->Active = false;
    FDConnection1->Connected = false;
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormMain::About1Click(TObject* Sender)
{
    AboutBox->ShowModal();
	}
//---------------------------------------------------------------------------

void __fastcall TFormMain::Export1Click(TObject* Sender)
{
    if (FDTable1->RecordCount == 0) {
        StatusBar1->Panels->Items[1]->Text = "Nothing to export.";
        return;
    }

    if (SaveDialog1->Execute())
        ExportCSV(SaveDialog1->FileName);
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::DataUpdate(const String& netname)
{
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
}

void __fastcall TFormMain::FormShow(TObject* Sender)
{
	UpdateClockDisplay();
	ClockTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormMain::OpenDatabase()
{
	String _userdb;

	_userdb = TPath::GetHomePath() + TPath::DirectorySeparatorChar + DBName;
	int index = FDConnection1->Params->IndexOfName("Database");

	FDConnection1->Params->ValueFromIndex[index] = _userdb;

	if (FileExists(_userdb)) {
		DeleteFile(_userdb);
	}
}

void __fastcall TFormMain::RefreshTimerTimer(TObject* Sender)
{
	DataUpdate(CurrentNet);
}
//---------------------------------------------------------------------------
// query the application's web update server

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
					text +=	" is available.\nDownload and install this update?";
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
	} catch (EXMLDocError &error) {
	}
	if (Response)
		delete Response;
	if (Request)
		delete Request;
	if (Client)
		delete Client;
	if (Document)
		delete Document;
}


