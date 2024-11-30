//---------------------------------------------------------------------------

#ifndef SelectH
#define SelectH
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
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TFormSelect : public TForm
{
__published:	// IDE-managed Components
	TListBox *ListBox1;
	TButton *btnOk;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall ListBox1DblClick(TObject *Sender);
private:	// User declarations
	bool NeedUpdate = true;
	TStringList *NetList;
	String Selection;
    TDateTime last_checked = 0;
public:		// User declarations
	__fastcall TFormSelect(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSelect *FormSelect;
//---------------------------------------------------------------------------
#endif
