
//---------------------------------------------------------------------------

#ifndef MainFormH
#define MainFormH
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
#include "datamodule.h"
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.SQLite.hpp>
#include <FireDAC.Phys.SQLiteDef.hpp>
#include <FireDAC.Phys.SQLiteWrapper.Stat.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.ExprFuncs.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.Stan.StorageBin.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <System.Classes.hpp>
#include <System.DateUtils.hpp>
#include <System.ImageList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.DBGrids.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ImageCollection.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.WinXCtrls.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <Soap.WebServExp.hpp>
#include <Soap.WSDLBind.hpp>
#include <Soap.WSDLPub.hpp>
#include <System.TypInfo.hpp>
#include <Xml.XMLSchema.hpp>
#include <System.Skia.hpp>
#include <Vcl.Skia.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ActnMan.hpp>
#include <Vcl.PlatformDefaultStyleActnCtrls.hpp>
#include <Vcl.ActnCtrls.hpp>
#include <Vcl.ActnMenus.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.StdActns.hpp>
#include <map>
//---------------------------------------------------------------------------
class TFormMain : public TForm
{
  __published: // IDE-managed Components
	TTimer* ClockTimer;
	TPanel* PanelTop;
	TPanel* PanelLeft;
	TLabel* Label1;
	TLabel* Label2;
	TLabel* Label3;
	TLabel* Label4;
	TLabel* Label5;
	TLabel* Label6;
	TLabel* Label7;
	TEdit* edFreq;
	TEdit* edBand;
	TEdit* edMode;
	TEdit* edNetControl;
	TEdit* edLogger;
	TEdit* edSubscribe;
	TButton* btnNets;
	TDBGrid* DBGrid1;
	TDataSource* DataSource1;
	TEdit* edNET;
	TPanel* PanelRight;
	TPanel* PanelDate;
	TPanel* PanelZone;
	TSaveDialog* SaveDialog1;
	TPanel* panClockBorder;
	TPanel* PanelClock;
	TFDConnection* FDConnection1;
	TTimer* RefreshTimer;
	TFDTable* FDTable1;
	TStatusBar* StatusBar1;
	TRESTClient* RESTClient1;
	TRESTRequest* RESTRequest1;
	TRESTResponse* RESTResponse1;
	TActionMainMenuBar *ActionMainMenuBar1;
	TActionManager *ActionManager1;
	TAction *ActionExportCSV;
	TAction *ActAbout;
	TAction *ActPrefs;
	TAction *ActFit;
	THelpContents *HelpContents1;
	TFileExit *ActionFileExit1;
	THelpOnHelp *HelpOnHelp1;
	void __fastcall MasterTick(TObject* Sender);
	void __fastcall btnNetsClick(TObject* Sender);
	void __fastcall DBGrid1DblClick(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall RefreshTimerTimer(TObject* Sender);
	void __fastcall nmUpdatesClick(TObject* Sender);
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall ActionExport(TObject *Sender);
	void __fastcall ActionAbout(TObject *Sender);
	void __fastcall ActionPreferences(TObject *Sender);
	void __fastcall ActionAutoFit(TObject *Sender);
  private: // User declarations
	void __fastcall UpdateClockDisplay();
	bool LEDOn = false;
	void __fastcall OpenDatabase();
	String CurrentNet;
	void __fastcall SetGrid(const CheckinList* clist);
	void __fastcall SaveDefaults();
	void __fastcall LoadDefaults();
	void __fastcall DataUpdate(const String& netname);
	int RefreshRate = 20;
	void __fastcall Shell(String cmd);
	void __fastcall ExportCSV(String Filename);
	void __fastcall LoadFontFromResource(String ResourceName);
	bool __fastcall CheckUpdate(String& url, String& versiontext, String& infotext);
	HANDLE ClockFontHandle;
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

