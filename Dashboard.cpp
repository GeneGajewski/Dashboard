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

// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "CodeSiteLogging.hpp"
// ---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("UpdateInfo.cpp", UpdInfo);
USEFORM("Preferences.cpp", FormPrefs);
USEFORM("MainForm.cpp", FormMain);
USEFORM("ABOUT.cpp", AboutBox);
USEFORM("FormPast.cpp", FormPastNets);
USEFORM("FormActive.cpp", FormActiveNets);
USEFORM("Download.cpp", DL);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {

	try {
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Wedgewood Light");
		Application->Title = "Dashboard";
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormPrefs), &FormPrefs);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TUpdInfo), &UpdInfo);
		Application->CreateForm(__classid(TDL), &DL);
		Application->CreateForm(__classid(TFormPastNets), &FormPastNets);
		Application->CreateForm(__classid(TFormActiveNets), &FormActiveNets);
		Application->Run();
	}

	catch (Exception &exception) {
		CodeSite->SendException("_tWinMain()", &exception);
		Application->ShowException(&exception);
	}
	return 0;
}
// ---------------------------------------------------------------------------
