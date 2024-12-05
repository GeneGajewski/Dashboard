//---------------------------------------------------------------------------

#ifndef TempFontH
#define TempFontH

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

namespace Utility {


// simple class to load/unload a font file for the current process
//
// this obviates the need to globally install the font

class TempFont
{
	String FName;
	int num_added;

	int open();
	void close();

	public:

	TempFont(const String &name);
	TempFont();

	// no copy/assign - allocated system resources are used
	TempFont(const TempFont &) = delete;
	TempFont& operator=(const TempFont &) = delete;

	~TempFont();

	bool Open(const String &filename);
};

}   // namespace
#endif
