//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include "CodeSiteLogging.hpp"
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Preferences.cpp", FormPrefs);
USEFORM("MainForm.cpp", FormMain);
USEFORM("UpdateInfo.cpp", UpdInfo);
USEFORM("Select.cpp", FormSelect);
USEFORM("ABOUT.cpp", AboutBox);
USEFORM("Download.cpp", DL);
USEFORM("DataModule.cpp", DMod); /* TDataModule: File Type */

//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Sky");
		Application->Title = "Dashboard";
		Application->CreateForm(__classid(TDMod), &DMod);
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormPrefs), &FormPrefs);
		Application->CreateForm(__classid(TFormSelect), &FormSelect);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TUpdInfo), &UpdInfo);
		Application->CreateForm(__classid(TDL), &DL);
		Application->Run();
	}
	catch (Exception &exception)
	{
		CodeSite->SendException("_tWinMain()", &exception);
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
            CodeSite->SendException("_TWinMain(...)",&exception);
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
