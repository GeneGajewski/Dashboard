//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormActive.h"
#include "Logger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Vcl.LabeledDBCtrls"
#pragma resource "*.dfm"
TFormActiveNets* FormActiveNets;

#include <map>
#include <vector>

#include <System.Ioutils.hpp>
#include <REST.Client.hpp>
#include "xmlnets.h"
#include <System.dateutils.hpp>

using namespace LogSys;

#define NETLIST_SECONDS 60 // check for new nets no more than once a minute

// where to get REST data

static const char* BaseUrl = "https://www.netlogger.org/api";
static const char* ResourceStr = "GetActiveNets.php";


// make grid column width match content width + padding

void __fastcall TFormActiveNets::BestFitDBGridColumn(
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
__fastcall TFormActiveNets::TFormActiveNets(TComponent* Owner) : TForm(Owner) {}
//---------------------------------------------------------------------------

void __fastcall TFormActiveNets::FormCreate(TObject* Sender)
{
    Log(logINFO, "Initializing TActiveNets");
    FDMemTab->Open();
    LastCheck = GetTime();
}

//---------------------------------------------------------------------------

// loads the DBgrid with the list of active nets given by the net logger server

void TFormActiveNets::LoadActiveNets()
{
    Application->ProcessMessages();
    try
    {
        // set it all up
        RESTClient->BaseURL = BaseUrl;
        RESTRequest->Client = RESTClient;
        RESTRequest->Response = RESTResponse;
        RESTRequest->Resource = ResourceStr;

        // run in background thread

        RESTRequest->ExecuteAsync([this]() {
            int Status = RESTResponse->StatusCode;
            if (Status != 200)
                return; // TODO: expound on this

            try
            {
                FDMemTab->DisableControls();
                FDMemTab->EmptyDataSet();

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
        });

    } catch (Exception& e)
    {
        Log(logERROR, e.Message);
    }
}

// adjust columns and re-enable grid

void __fastcall TFormActiveNets::PostProcessing()
{
    // set DBGrid column widths to match content
    for (int x = 0; x < NetGrid->Columns->Count; x++)
        BestFitDBGridColumn(NetGrid, NetGrid->Columns->Items[x], 0, 24);

    FDMemTab->EnableControls();
    ActivityIndicator1->Animate = false;

    NetGrid->Enabled = true;
    FocusControl(NetGrid);
}

void __fastcall TFormActiveNets::FormShow(TObject* Sender)
{
    // need to refresh?

    try
    {
        if (FDMemTab->RecordCount == 0 || SecondsBetween(GetTime(), LastCheck) > NETLIST_SECONDS)
        {
            ActivityIndicator1->Animate = true;
            NetGrid->Enabled = false;
            LoadActiveNets();
            LastCheck = GetTime(); // note the time
        }
        else
            FocusControl(NetGrid);
    } catch (Exception& e)
    {
        Log(logERROR, e.Message);
    }
}
//---------------------------------------------------------------------------

void __fastcall TFormActiveNets::BitBtnOkClick(TObject* Sender)
{
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormActiveNets::NetGridDblClick(TObject* Sender)
{
    ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TFormActiveNets::NetGridTitleClick(TColumn* Column)
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

void __fastcall TFormActiveNets::NetGridSortedField(
    TLabeledDbGrid* Sender, TField* Field, TCBSortOrder& Sorted)
{
    if (SameText(SortField, Field->DisplayName))
        Sorted = Ascending ? TCBSortOrder::soAscending : TCBSortOrder::soDescending;
    else
        Sorted = TCBSortOrder::soNone;
}
//---------------------------------------------------------------------------

