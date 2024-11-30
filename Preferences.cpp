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

#include "Preferences.h"
#include "mainform.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
TFormPrefs *FormPrefs;
//---------------------------------------------------------------------------
__fastcall TFormPrefs::TFormPrefs(TComponent* Owner)
	: TForm(Owner)
{
	// combobox is sorted!!
	for(unsigned x=0; x < Vcl::Themes::TStyleManager::StyleNames.Length;x++)
		cbStyles->Items->Add(Vcl::Themes::TStyleManager::StyleNames[x]);

	// set combobox to show current system theme
	for(int x = 0; x < cbStyles->Items->Count; x++)
		if(cbStyles->Items->Strings[x] == Vcl::Themes::TStyleManager::ActiveStyle->Name)
		{
			cbStyles->ItemIndex = x;
			break;
		}


	// map checkboxes to their respective columns
	VisMap.insert(
		{
			{ ckbSerialNo, 		FormMain->ColMap["SerialNo"]		},
			{ ckbCall,  		FormMain->ColMap["Callsign"] 		},
			{ ckbState,     	FormMain->ColMap["State"]  			},
			{ ckbRemarks,   	FormMain->ColMap["Remarks"]     	},
			{ ckbInfo,   		FormMain->ColMap["QSLInfo"]     	},
			{ ckbCity, 			FormMain->ColMap["CityCountry"] 	},
			{ ckbName,          FormMain->ColMap["FirstName"]   	},
			{ ckbStatus,        FormMain->ColMap["Status"]      	},
			{ ckbCounty,        FormMain->ColMap["County"]      	},
			{ ckbGrid,          FormMain->ColMap["Grid"]        	},
			{ ckbStreet,        FormMain->ColMap["Street"]      	},
			{ ckbZip,           FormMain->ColMap["Zip"]         	},
			{ ckbMemberID,      FormMain->ColMap["MemberID"]    	},
			{ ckbCountry,       FormMain->ColMap["Country"]     	},
			{ ckbDXCC,          FormMain->ColMap["DXCC"]        	},
			{ ckbPreferred,     FormMain->ColMap["PreferredName"]	}
		}
	);
}
//---------------------------------------------------------------------------
void __fastcall TFormPrefs::cbStylesChange(TObject *Sender)
{
	Vcl::Themes::TStyleManager::TrySetStyle(cbStyles->Text);
}
//---------------------------------------------------------------------------
void __fastcall TFormPrefs::btnOkClick(TObject *Sender)
{
	for(auto Item : VisMap)
		Item.second->Visible = Item.first->Checked;

	ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrefs::btnCancelClick(TObject *Sender)
{
	FormMain->UTC = _utc;
	FormMain->AMPM = _ampm;
	ModalResult = mrCancel;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrefs::FormShow(TObject *Sender)
{

	for(auto Item : VisMap)
		Item.first->Checked = Item.second->Visible;

	_ampm = FormMain->AMPM;
	_utc = FormMain->UTC;

	if(_ampm)
		rb12->Checked = true;
	else
		rb24->Checked = true;

	ckbUTC->Checked = _utc;

}
//---------------------------------------------------------------------------
void __fastcall TFormPrefs::ckbUTCClick(TObject *Sender)
{
	FormMain->UTC = ((TCheckBox *) Sender)->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrefs::rb12Click(TObject *Sender)
{
	FormMain->AMPM = true;
}
//---------------------------------------------------------------------------
void __fastcall TFormPrefs::rb24Click(TObject *Sender)
{
	FormMain->AMPM = false;
}
//---------------------------------------------------------------------------



