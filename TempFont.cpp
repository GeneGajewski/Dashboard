//---------------------------------------------------------------------------

#pragma hdrstop

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

#include "TempFont.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace Utility {

int TempFont::open()
{
    return num_added = AddFontResourceEx(FName.c_str(), FR_PRIVATE, 0);
}

TempFont::TempFont() { }

void TempFont::close()
{
    if (num_added)
        RemoveFontResourceEx(FName.c_str(), FR_PRIVATE, 0);
}

bool TempFont::Open(const String& filename)
{
    if (num_added)
        return false;
    FName = filename;
    open();
    return (num_added != 0);
}

TempFont::TempFont(const String& name)
    : FName(name)
    , num_added(0)
{
    open();
}

TempFont::~TempFont()
{
    close();
}

}

