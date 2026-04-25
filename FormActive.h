//---------------------------------------------------------------------------

#ifndef FormActiveH
#define FormActiveH
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
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.XmlTransform.hpp>
#include <map>
#include <vector>

//---------------------------------------------------------------------------
class TFormActiveNets : public TForm
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
	TLabeledDbGrid *NetGrid;
	TRESTClient *RESTClient;
	TRESTRequest *RESTRequest;
	TRESTResponse *RESTResponse;
	TActivityIndicator *ActivityIndicator1;
	TStringField *FDMemTabNetName;
	TStringField *FDMemTabAltNetName;
	TStringField *FDMemTabFrequency;
	TStringField *FDMemTabLogger;
	TStringField *FDMemTabNetControl;
	TStringField *FDMemTabDate;
	TStringField *FDMemTabMode;
	TStringField *FDMemTabBand;
	TIntegerField *FDMemTabSubscriberCount;
	TStringField *FDMemTabServer;
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormShow(TObject* Sender);
	void __fastcall BitBtnOkClick(TObject* Sender);
	void __fastcall NetGridDblClick(TObject* Sender);
	void __fastcall NetGridTitleClick(TColumn *Column);
	void __fastcall NetGridSortedField(TLabeledDbGrid *Sender, TField *Field, TCBSortOrder &Sorted);
  private: // User declarations
	void __fastcall BestFitDBGridColumn(
		TDBGrid* Grid, TColumn* Col, int MaxRowsToScan, int Padding);
	void __fastcall LoadActiveNets();
    void __fastcall PostProcessing();
	TDateTime LastCheck = 0;
	String SortField;
	bool Ascending;


  public: // User declarations
    String SelectedNet, SelectedServer;
    __fastcall TFormActiveNets(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormActiveNets* FormActiveNets;
//---------------------------------------------------------------------------
#endif

