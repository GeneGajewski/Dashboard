//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("MainForm.cpp", FormMain);
USEFORM("Preferences.cpp", FormPrefs);
USEFORM("Select.cpp", FormSelect);
USEFORM("UpdateInfo.cpp", UpdInfo);
USEFORM("ABOUT.cpp", AboutBox);
USEFORM("DataModule.cpp", DMod); /* TDataModule: File Type */
USEFORM("Download.cpp", DL);
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
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
