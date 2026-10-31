/*
 *   Copyright (C) 2026 Gene Gajewski WG5ENE
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

#include "FormActive.h"
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
#include "log.h"

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
        LogError("Grid || Col || Col->Field is null");
        return;
    }

    TDataSet* DS = Col->Field->DataSet;
    if (!DS || !DS->Active)
    {
        LogError("!DS || DS->Active = false");
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
    LogInfo("Initializing TActiveNets form.");
    FDMemTab->Open();
    LastCheck = GetTime();
}

//---------------------------------------------------------------------------

// loads the FDMemTable with a list of active nets from the net logger server

void TFormActiveNets::LoadActiveNets()
{
    Application->ProcessMessages();
    try
    {
        // set REST stuff all up
        RESTClient->BaseURL = BaseUrl;
        RESTRequest->Client = RESTClient;
        RESTRequest->Response = RESTResponse;
        RESTRequest->Resource = ResourceStr;

        LogInfo("FrmActive ExecuteAsync");

        // run request in a background thread - let completion handler run in bg also
        RESTRequest->ExecuteAsync(
            [this]() {
                LogInfo("FrmActive CompletionHandler");
                int Status = RESTResponse->StatusCode;
                if (Status != 200)
                {
                    LogWarn("REST Status Code: " + IntToStr(Status));
                    return;
                }

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
                            {
                                LogError(Item.first + " field is unknown.");
                                continue;
                            }

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
                    LogExcept(&e);
                    FDMemTab->Cancel();
                    FDMemTab->EndBatch();
                }

                // do final gui stuff in the main thread
                TThread::Queue(nullptr, [this]() { PostProcessActive(); });
            },
            false, true,
            [this](TObject* AObject) { // completion_error handler ...
                Exception* e = dynamic_cast<Exception*>(AObject);
                LogError(e->Message);
                TThread::Queue(nullptr, [this]() {
                    Close();
                    Beep();
                });
            });

    } catch (Exception& e)
    {
        LogExcept(&e);
    }
}

// adjust columns and re-enable grid after LoadActiveNets thread runs

void __fastcall TFormActiveNets::PostProcessActive()
{
    LogInfo("FrmActive Post Process");
    // set DBGrid column widths to match content
    for (int x = 0; x < NetGrid->Columns->Count; x++)
        BestFitDBGridColumn(NetGrid, NetGrid->Columns->Items[x], 0, 24);

    FDMemTab->EnableControls();
    ActivityIndicator1->Animate = false;
    NetGrid->Visible = true;
    NetGrid->Enabled = true;
    FocusControl(NetGrid);
}

void __fastcall TFormActiveNets::FormShow(TObject* Sender)
{
    // do I need to refresh?

    try
    { // get new data
        if (FDMemTab->RecordCount == 0 || SecondsBetween(GetTime(), LastCheck) > NETLIST_SECONDS)
        {
            ActivityIndicator1->Animate = true;

            NetGrid->Visible = false;
            NetGrid->Enabled = false;

            LoadActiveNets();
            LastCheck = GetTime(); // note the time
        } else
            FocusControl(NetGrid); // keep using current data
    } catch (Exception& e)
    {
        LogExcept(&e);
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
    {
        LogWarn("!Column || !Column->Field.");
        return;
    }

    if (Column->Field->FieldKind != fkData)
    {
        LogWarn("FieldKind != fkData");
        return; // ignore calculated/lookup/etc.
    }

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

void __fastcall TFormActiveNets::CenterIndicator()
{
    int _Left, _Top;
    _Left = (ClientWidth / 2) - (ActivityIndicator1->Width / 2);
    _Top = (ClientHeight / 2) - (ActivityIndicator1->Height / 2);

    ActivityIndicator1->Left = _Left;
    ActivityIndicator1->Top = _Top;
}

//---------------------------------------------------------------------------

void __fastcall TFormActiveNets::FormResize(TObject* Sender)
{
    CenterIndicator();
}
//---------------------------------------------------------------------------

