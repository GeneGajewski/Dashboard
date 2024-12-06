//---------------------------------------------------------------------------

#ifndef UpdateInfoH
#define UpdateInfoH
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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
//---------------------------------------------------------------------------
class TUpdInfo : public TForm {
__published: // IDE-managed Components
    TButton* Button1;
    TButton* Button2;
    TLabel* Label1;
    TLabel* Label2;
    TRichEdit* RichEdit1;

private: // User declarations
public: // User declarations
    __fastcall TUpdInfo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUpdInfo* UpdInfo;
//---------------------------------------------------------------------------
#endif

