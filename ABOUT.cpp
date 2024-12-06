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

//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "About.h"
#include "winversionquery.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TAboutBox* AboutBox;
//---------------------------------------------------------------------
__fastcall TAboutBox::TAboutBox(TComponent* AOwner)
    : TForm(AOwner)
{
    Utility::WinVersionQuery ver;
    Utility::VerStr verstr(ver.GetStr("FileVersion"));
    lblVersion->Caption = "Version " + verstr.Shorter(3);
}
//---------------------------------------------------------------------
void __fastcall TAboutBox::LinkLabel1Click(TObject* Sender)
{
    ShellExecute(NULL, L"open", L"http://www.gnu.org/licenses/", NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

