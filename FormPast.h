//---------------------------------------------------------------------------

#ifndef FormPastH
#define FormPastH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.DBGrids.hpp>
#include <Datasnap.DBClient.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Grids.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include "Vcl.LabeledDBCtrls.hpp"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.URLClient.hpp>
#include <Vcl.WinXCtrls.hpp>
#include "Vcl.LabeledComCtrls.hpp"
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include "Vcl.LabeledCtrls.hpp"
#include <Vcl.Samples.Spin.hpp>
//---------------------------------------------------------------------------
class TFormPastNets : public TForm
{
  __published: // IDE-managed Components
	TDataSource* DataSource4;
	TFDMemTable* FDMemTab;
	TPanel* Panel1;
	TPanel* Panel2;
	TPanel* Panel3;
	TPanel* Panel4;
	TBitBtn* BitBtnOk;
	TBitBtn* BitBtnCancel;
	TLabeledDbGrid* NetGrid;
	TRESTClient *RESTClient;
	TRESTRequest *RESTRequest;
	TRESTResponse *RESTResponse;
	TImageList *ImageList1;
	TPanel *Rightside;
	TLabeledSpinEdit *LabeledSpinEdit1;
	TBitBtn *BitBtnRefresh;
	TLabeledEditEx *FilterEdit;
	TCheckBox *CheckBox1;
	TStringField *FDMemTabNetName;
	TStringField *FDMemTabAltNetName;
	TStringField *FDMemTabFrequency;
	TStringField *FDMemTabLogger;
	TStringField *FDMemTabNetControl;
	TStringField *FDMemTabDate;
	TStringField *FDMemTabMode;
	TStringField *FDMemTabBand;
	TIntegerField *FDMemTabNetID;
	TBooleanField *FDMemTabAIM;
	TIntegerField *FDMemTabUpdateInterval;
	TStringField *FDMemTabsrcIP;
	TStringField *FDMemTabLastActivity;
	TIntegerField *FDMemTabInactivityTimer;
	TStringField *FDMemTabClosedAt;
	TBooleanField *FDMemTabAssassinated;
	TStringField *FDMemTabServer;
	TLabeledEditEx *edLike;
	TActivityIndicator *ActivityIndicator1;
	TLabel *Label1;
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall BitBtnOkClick(TObject* Sender);
	void __fastcall OLDNetGridDblClick(TObject* Sender);
	void __fastcall NetGridTitleClick(TColumn* Column);
	void __fastcall NetGridSortedField(TLabeledDbGrid* Sender, TField* Field, TCBSortOrder& Sorted);
	void __fastcall BitBtnRefreshClick(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
	void __fastcall FilterEditChange(TObject *Sender);
  private: // User declarations
	void __fastcall BestFitDBGridColumn(
		TDBGrid* Grid, TColumn* Col, int MaxRowsToScan, int Padding);
	void __fastcall LoadPastNets(int Interval);
	String SortField;
	bool Ascending;
	void __fastcall PostProcessing();
  public: // User declarations
    String SelectedNet, SelectedServer;
    __fastcall TFormPastNets(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPastNets* FormPastNets;
//---------------------------------------------------------------------------
#endif

