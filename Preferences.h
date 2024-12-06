//---------------------------------------------------------------------------

#ifndef PreferencesH
#define PreferencesH
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
#include "cspin.h"
#include <Data.Bind.Components.hpp>
#include <Data.Bind.DBScope.hpp>
#include <Data.Bind.EngExt.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <Vcl.Bind.DBEngExt.hpp>
#include <Vcl.Bind.Editors.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.DbGrids.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.StdCtrls.hpp>
#include <map>
//---------------------------------------------------------------------------
class TFormPrefs : public TForm {
__published: // IDE-managed Components
    TGroupBox* GroupBox1;
    TCheckBox* ckbSerialNo;
    TCheckBox* ckbCall;
    TCheckBox* ckbState;
    TCheckBox* ckbRemarks;
    TCheckBox* ckbInfo;
    TCheckBox* ckbCity;
    TCheckBox* ckbName;
    TCheckBox* ckbStatus;
    TCheckBox* ckbPreferred;
    TCheckBox* ckbDXCC;
    TCheckBox* ckbCountry;
    TCheckBox* ckbMemberID;
    TCheckBox* ckbZip;
    TCheckBox* ckbStreet;
    TCheckBox* ckbGrid;
    TCheckBox* ckbCounty;
    TComboBox* cbStyles;
    TGroupBox* GroupBox2;
    TRadioButton* rb12;
    TRadioButton* rb24;
    TCheckBox* ckbUTC;
    TButton* btnOk;
    TButton* btnCancel;
    TLabel* label;
    TCSpinEdit* CSpinEdit1;
    TLabel* Label1;
    void __fastcall cbStylesChange(TObject* Sender);
    void __fastcall btnOkClick(TObject* Sender);
    void __fastcall btnCancelClick(TObject* Sender);
    void __fastcall FormShow(TObject* Sender);
    void __fastcall ckbUTCClick(TObject* Sender);
    void __fastcall rb12Click(TObject* Sender);
    void __fastcall rb24Click(TObject* Sender);

private: // User declarations
    std::map<TCheckBox*, TColumn*> VisMap;
    bool _utc, _ampm;
    int _styleindex;
    String cur_style;

public: // User declarations
    __fastcall TFormPrefs(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPrefs* FormPrefs;
//---------------------------------------------------------------------------
#endif

