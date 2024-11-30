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

#include "Select.h"
#include "datamodule.h"
#include "mainform.h"


#define NETLIST_SECONDS 60


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSelect *FormSelect;
//---------------------------------------------------------------------------
__fastcall TFormSelect::TFormSelect(TComponent* Owner)
	: TForm(Owner)
{
	NetList = new TStringList;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelect::FormShow(TObject *Sender)
{
	ModalResult = mrCancel;

    // refreshing the list is limited to once a minute
	if(NetList->Count == 0 || SecondsBetween(GetTime(),last_checked) > NETLIST_SECONDS)
	{
		FormMain->LED(true);
		Application->ProcessMessages();
		FormMain->LED(false);

		DMod->GetNetNames(NetList);
		last_checked = GetTime();
	}
	ListBox1->Items = NetList;
}
//---------------------------------------------------------------------------
void __fastcall TFormSelect::FormDestroy(TObject *Sender)
{
	if(NetList)
		delete NetList;
}
//---------------------------------------------------------------------------

void __fastcall TFormSelect::ListBox1DblClick(TObject *Sender)
{
        ModalResult = mrOk;
}
//---------------------------------------------------------------------------

