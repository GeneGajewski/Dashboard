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
#pragma hdrstop

#include "WinVersionQuery.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace Utility
{
    // ctor for default executing module
    WinVersionQuery::WinVersionQuery() : pBlock(NULL), lp_size(0), lp(NULL)
    {
        const size_t MAXBUF = 1024;
        _TCHAR buffer[MAXBUF];

        memset(buffer, 0, sizeof(buffer));
		DWORD modulename_size = GetModuleFileName(NULL, buffer, MAXBUF - 1);
		modulename = buffer;
		GetpBlock();
	}

	// ctor for a specifically named file
	WinVersionQuery::WinVersionQuery(const wchar_t* _modulename) :
		pBlock(NULL), lp_size(0), lp(NULL)
	{
		modulename = _modulename;
		GetpBlock();
	}

	// get the version parameter block thingy we need for queries
	bool WinVersionQuery::GetpBlock(void)
	{
		DWORD block_size, dummy;
		block_size = GetFileVersionInfoSizeEx(
			FILE_VER_GET_NEUTRAL, modulename.c_str(), &dummy);
		if (block_size) {
			pBlock = new char[block_size];
			BOOL retval = GetFileVersionInfoEx(FILE_VER_GET_NEUTRAL,
				modulename.c_str(), NULL, block_size, pBlock);
			if (retval) {
				// get ptr to translation block array
				HRESULT result = VerQueryValue(pBlock,
					L"\\VarFileInfo\\Translation", (LPVOID*)&lp, &lp_size);
				if (SUCCEEDED(result)) {
					SetLCP(0); // default
					flags = GetFlags();
					return true;
				}
			}
			if (pBlock)
				delete pBlock;
			pBlock = NULL;
			lp = NULL;
			lp_size = 0;
		}
		return false;
	}
	// return a string value for current lang/codepge/stringname
	String WinVersionQuery::GetStr(String name)
	{
		if (pBlock) {
			UINT str_size;
			_TCHAR* str;

			HRESULT result = VerQueryValue(
				pBlock, Query(name).c_str(), (LPVOID*)&str, &str_size);
			if (SUCCEEDED(result) && str_size)
				return String(str);
		}
		return NULL;
	}

	// select lang/codepage array entry  0-based
	bool WinVersionQuery::SetLCP(unsigned index)
	{
		int count = LCPCount();

		if (count && index < count) {
			language = lp[index].wLanguage;
			codepage = lp[index].wCodePage;
			return true;
		}
		return false;
	}

	// number of language/codepage entries
	unsigned WinVersionQuery::LCPCount()
	{
		return lp != NULL ? lp_size / sizeof(LANGANDCODEPAGE) : 0;
	}

	// return windows fixedfileinfo struct. Struct contents not valid if
	// return result is false
	const bool WinVersionQuery::GetFixedInfo(VS_FIXEDFILEINFO &info)
	{
		if (pBlock) {
			UINT size;
			VS_FIXEDFILEINFO* vsfixed;
			HRESULT result =
				VerQueryValueW(pBlock, L"\\", (LPVOID*)&vsfixed, &size);

			if (SUCCEEDED(result) && vsfixed->dwSignature == magic_number)
				info = *vsfixed;
			return true;
		}
		return false;
	}

	// dtor
	WinVersionQuery::~WinVersionQuery()
	{
		if (pBlock)
			delete pBlock;
	}

    // build string for VerQueryValue string-value query
    String WinVersionQuery::Query(const String &name)
    {
        return String().sprintf(fmt, language, codepage) + name;
    }

    DWORD WinVersionQuery::GetFlags()
    {
	if (pBlock) {
	    VS_FIXEDFILEINFO info;
	   if(GetFixedInfo(info))
		   return (info.dwFileFlags & info.dwFileFlagsMask);
        }
        return 0;
    }

#define __MAKEDW(a, b) (DWORD)(((DWORD)a << 16) | b)

	String VerStr::makestr()
	{
		String s;
		s = String(FMajor) + dot + String(FMinor) + dot + String(FRelease) +
			dot + String(FBuild);
		return s;
	}

	void VerStr::set_string(const String &ver)
	{
		//	FMajor = FMinor = FRelease = FBuild = 0;
		TStringList* list = new TStringList;

		WORD maj, min, rel, bld;
		maj = min = rel = bld = 0;

		list->Delimiter = dot;
		list->DelimitedText = ver;

		int cnt = list->Count;

		try {
			if (list->Count >= 1)
				maj = StrToUInt(list->Strings[0]);

			if (list->Count >= 2)
				min = StrToUInt(list->Strings[1]);

			if (list->Count >= 3)
				rel = StrToUInt(list->Strings[2]);

			if (list->Count >= 4)
				bld = StrToUInt(list->Strings[3]);

			FMajor = maj;
			FMinor = min;
			FRelease = rel;
			FBuild = bld;
		} catch (EConvertError &e) {
			// bad string conversion - do nothing
		}
		if (list)
			delete list;
	}

	VerStr::VerStr() : FMajor(0), FMinor(0), FRelease(0), FBuild(0)
	{

	}

	VerStr::VerStr(const String &ref) :
		FMajor(0), FMinor(0), FRelease(0), FBuild(0)
	{
		set_string(ref);
	}

	VerStr::~VerStr() {}

	String VerStr::Shorter(unsigned num)
	{
		TStringList* list = new TStringList;
		String retval;

		list->Delimiter = dot;

		try {
			if (num >= 1)
				list->Add(UIntToStr((unsigned)FMajor));
			if (num >= 2)
				list->Add(UIntToStr((unsigned)FMinor));
			if (num >= 3)
				list->Add(UIntToStr((unsigned)FRelease));
			if (num >= 4)
				list->Add(UIntToStr((unsigned)FBuild));
			retval = list->DelimitedText;
		}

		catch (EConvertError &e)
		{
		}

		if (list)
			delete list;
		return retval;
	}

	unsigned __int64 VerStr::AsUnsigned64()
	{
		DWORD ms, ls;

		unsigned __int64 retval;

		ms = __MAKEDW(FMajor, FMinor);
		ls = __MAKEDW(FRelease, FBuild);

		retval = (unsigned __int64)ms << 32 | ls;

		return retval;
	}

	VerStr &VerStr::operator=(const String ref)
	{
		set_string(ref);
		return *this;
	}
} // namespace WG5ENE_Utility

