
//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
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
#include "Vcl.LabeledCtrls.hpp"
#include "Vcl.LabeledDBCtrls.hpp"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.URLClient.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.XPStyleActnCtrls.hpp>
#include <Vcl.ControlList.hpp>
#include <Vcl.DBCtrls.hpp>
#include <map>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
  __published: // IDE-managed Components
	TTimer* ClockTimer;
	TPanel* PanelTop;
	TPanel* PanelLeft;
	TLabel* Label6;
	TDataSource* DataSource1;
	TPanel* PanelRight;
	TPanel* PanelDate;
	TPanel* PanelZone;
	TSaveDialog* SaveDialog1;
	TPanel* panClockBorder;
	TPanel* PanelClock;
	TTimer* RefreshTimer;
	TStatusBar* StatusBar1;
	TRESTClient* RESTClient1;
	TRESTRequest* RESTRequest1;
	TRESTResponse* RESTResponse1;
	TActionMainMenuBar *ActionMainMenuBar1;
	TActionManager *ActionManager1;
	TAction *actExportCSV;
	TAction *actAbout;
	TAction *actPreferences;
	TAction *actAutoFit;
	THelpContents *actContents;
	TFileExit *actExit;
	THelpOnHelp *actHelpOnHelp;
	TAction *actCheckUpdates;
	TAction *actLiveNet;
	TFDMemTable *FDMemTable1;
	TLabeledDbGrid *DBGrid1;
	TAction *ActPastNets;
	TLabeledEditEx *edNET;
	TLabeledEditEx *edFreq;
	TLabeledEditEx *edBand;
	TLabeledEditEx *edMode;
	TLabeledEditEx *edNetControl;
	TLabeledEditEx *edLogger;
	TLabeledEditEx *edStart;
	TLabeledEditEx *edClosed;
	TLabeledEditEx *edNetID;
	TLabeledEditEx *edSourceIP;
	TLabeledEditEx *edLastActivity;
	TLabeledEditEx *edInactivity;
	TLabeledEditEx *edAIMUpdate;
	TCheckBox *cbAIM;
	TDBCheckBox *dbcbAsassinated;
	void __fastcall MasterTick(TObject* Sender);
	void __fastcall DBGrid1DblClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall RefreshTimerTimer(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall ActionExport(TObject *Sender);
	void __fastcall ActionAbout(TObject *Sender);
	void __fastcall ActionPreferences(TObject *Sender);
	void __fastcall ActionAutoFit(TObject *Sender);
	void __fastcall actCheckUpdatesExecute(TObject *Sender);
	void __fastcall ActionLiveNet(TObject *Sender);
	void __fastcall DBGrid1TitleClick(TColumn *Column);
	void __fastcall DBGrid1SortedField(TLabeledDbGrid *Sender, TField *Field, TCBSortOrder &Sorted);
	void __fastcall DBGrid1DrawColumnCell(TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State);
	void __fastcall ActPastNetsExecute(TObject *Sender);

  private: // User declarations
	void __fastcall UpdateClockDisplay();

    String CurrentNet;
    String CurrentServer;
    String CurrentNetID;
    bool ActiveMode;

	void __fastcall PostProcessing();
	void __fastcall SaveDefaults();
	void __fastcall LoadDefaults();
	void __fastcall CheckinData();
    void __fastcall PastDataUpdate();
	int RefreshRate = 20;
	void __fastcall Shell(String cmd);
	void __fastcall ExportCSV(String Filename);
	void __fastcall LoadFontFromResource(String ResourceName);
	bool __fastcall CheckUpdate(String& url, String& versiontext, String& infotext);
    void __fastcall BestFitDBGridColumn(
    TDBGrid* Grid, TColumn* Col, int MaxRowsToScan /*0 = all*/, int Padding /*pixels*/);
    void __fastcall BestFitAll(TDBGrid* Grid, int maxrows = 0, int padding = 0);
    void __fastcall ShowNetInfo();


	HANDLE ClockFontHandle;
    String SortField;
    bool Ascending;
    unsigned NewRecords;
    int Pointer;
  public: // User declarations
	__fastcall TFormMain(TComponent* Owner);
	std::map<String, TColumn*> ColMap;
	bool UTC = false;
	bool AMPM = false;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormMain* FormMain;
//---------------------------------------------------------------------------
#endif

