//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormPast.h"
#include "Logger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Vcl.LabeledDBCtrls"
#pragma link "Vcl.LabeledComCtrls"
#pragma link "Vcl.LabeledCtrls"
#pragma resource "*.dfm"
TFormPastNets* FormPastNets;

#include <map>
#include <vector>

#include <System.Ioutils.hpp>
#include <REST.Client.hpp>
#include <System.DateUtils.hpp>
#include "xmlnets.h"

using namespace LogSys;

// where to get REST data

static const char* BaseUrl = "https://www.netlogger.org/api";
static const char* ResourceStr = "GetPastNets.php";

//---------------------------------------------------------------------------
// make grid column width match content width + padding

void __fastcall TFormPastNets::BestFitDBGridColumn(
    TDBGrid* Grid, TColumn* Col, int MaxRowsToScan /*0 = all*/, int Padding /*pixels*/)
{
    if (!Grid || !Col || !Col->Field)
    {
        Log(logERROR, "Grid || Col || Col->Field is null");
        return;
    }

    TDataSet* DS = Col->Field->DataSet;
    if (!DS || !DS->Active)
    {
        Log(logERROR, "!DS || DS->Active = false");
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
            DS->EnableControls();
        }

        Col->Width = maxW + Padding;
    } __finally
    {
        Grid->Canvas->Font->Assign(oldFont.get());
    }
}

//---------------------------------------------------------------------------

__fastcall TFormPastNets::TFormPastNets(TComponent* Owner) : TForm(Owner) {}

//---------------------------------------------------------------------------

void __fastcall TFormPastNets::FormCreate(TObject* Sender)
{
    Log(logINFO, "Initializing TFormPastNets");
    FDMemTab->Open();
}
//---------------------------------------------------------------------------
// loads the DBgrid with the list of active nets given by the netlogger server

void __fastcall TFormPastNets::LoadPastNets(int Interval)
{
    try
    {
        Log(logINFO, String().sprintf(L"LoadPastNets: %d days", Interval));
        NetGrid->Enabled = false;
        ActivityIndicator1->Animate = true;

        // set REST request up

        RESTClient->BaseURL = BaseUrl;
        RESTRequest->Resource = ResourceStr;
        RESTRequest->Params->Clear();
        RESTRequest->Params->AddItem("Interval", IntToStr(Interval), pkGETorPOST);
        RESTRequest->Response = RESTResponse;

        // use separate thread for completion lambda to keep UI happy

        RESTRequest->ExecuteAsync([this]() {
            int Status = RESTResponse->StatusCode;
            if (Status != 200)
                return; // TODO: expound on this

            try
            {
                // post a record to the mem table

                auto callback = [&](XML_Nets_Machine::NamedValues& vals) {
                    FDMemTab->Append();
                    for (auto Item : vals)
                    {
                        TField* field = FDMemTab->FieldByName(Item.first);

                        if (!field) // huh?
                            continue;

                        if (field->DataType == TFieldType::ftBoolean)
                            field->Value = (Item.second == "Y" ? true : false);
                        else
                            field->Value = Item.second;
                    }
                    FDMemTab->Post();
                };

                // our xml processor
                XML_Nets_Machine machine(callback);

                // do it
                FDMemTab->BeginBatch();
                machine.Execute(RESTResponse->RawBytes);
                FDMemTab->EndBatch();

            } catch (Exception& e)
            {
                FDMemTab->Cancel();
                FDMemTab->EndBatch();
            }

            TThread::Queue(nullptr, [this]() { PostProcessing(); });
        }, false);

    } catch (Exception& e)
    {
        Log(logERROR, e.Message);
    }
}
//---------------------------------------------------------------------------
// set column widths based on content

void __fastcall TFormPastNets::PostProcessing()
{
    try
    {
        for (int x = 0; x < NetGrid->Columns->Count; x++)
            BestFitDBGridColumn(NetGrid, NetGrid->Columns->Items[x], 0, 24);

    } catch (Exception& e)
    {
        Log(logERROR, e.Message);
    }
    NetGrid->Enabled = true;
    ActivityIndicator1->Animate = false;
    FocusControl(NetGrid);
}
//---------------------------------------------------------------------------

void __fastcall TFormPastNets::FormShow(TObject* Sender)
{
    try
    {
        if (FDMemTab->IsEmpty())
            LoadPastNets(LabeledSpinEdit1->Value); // todo: store this value in registry...

    } catch (Exception& e)
    {
        Log(logERROR, e.Message);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormPastNets::BitBtnOkClick(TObject* Sender)
{
    ModalResult = mrOk;
}

//---------------------------------------------------------------------------

void __fastcall TFormPastNets::OLDNetGridDblClick(TObject* Sender)
{
    ModalResult = mrOk;
}

//---------------------------------------------------------------------------
// set the sort order for the clicked column

void __fastcall TFormPastNets::NetGridTitleClick(TColumn* Column)
{
    if (!Column || !Column->Field)
        return;
    if (Column->Field->FieldKind != fkData)
        return; // ignore calculated/lookup/etc.

    const String f = Column->Field->FieldName;
    SortField = f;
    const String fu = f.UpperCase();
    const String cur = FDMemTab->IndexFieldNames.UpperCase();

    // Toggle ASC <-> DESC for the same field; otherwise sort ASC by the new field
    if (cur == fu)
    {
        FDMemTab->IndexFieldNames = f + ":D"; // ASC -> DESC
        Ascending = false;
    } else
    {
        if (cur == (fu + ":D"))
            FDMemTab->IndexFieldNames = f; // DESC -> ASC
        else
            FDMemTab->IndexFieldNames = f; // new column -> ASC
        Ascending = true;
    }
}
//---------------------------------------------------------------------------
// set a column's graphical sort indicator

void __fastcall TFormPastNets::NetGridSortedField(
    TLabeledDbGrid* Sender, TField* Field, TCBSortOrder& Sorted)
{
    if (SameText(SortField, Field->DisplayName))
        Sorted = Ascending ? TCBSortOrder::soAscending : TCBSortOrder::soDescending;
    else
        Sorted = TCBSortOrder::soNone;
}
//---------------------------------------------------------------------------

void __fastcall TFormPastNets::BitBtnRefreshClick(TObject* Sender)
{
    FDMemTab->EmptyDataSet();
    LoadPastNets(LabeledSpinEdit1->Value);
}

//---------------------------------------------------------------------------
// create a simple filter string for the NetName field

String FilterString(String text)
{
    return "NetName LIKE '%" + text + "%'";
}

//---------------------------------------------------------------------------
// enable the filter

void __fastcall TFormPastNets::CheckBox1Click(TObject* Sender)
{
    if (CheckBox1->Checked)
    {
        FDMemTab->Filter = FilterString(FilterEdit->Text);
        FDMemTab->Filtered = true;

    } else
        FDMemTab->Filtered = false;
}

//---------------------------------------------------------------------------
// update the filter

void __fastcall TFormPastNets::FilterEditChange(TObject* Sender)
{
    FDMemTab->Filter = FilterString(FilterEdit->Text);
}
//---------------------------------------------------------------------------

