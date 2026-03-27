// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>

// ---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Preferences.cpp", FormPrefs);
USEFORM("MainForm.cpp", FormMain);
USEFORM("UpdateInfo.cpp", UpdInfo);
USEFORM("Select.cpp", FormSelect);
USEFORM("Download.cpp", DL);
USEFORM("ABOUT.cpp", AboutBox);
USEFORM("DataModule.cpp", DMod); /* TDataModule: File Type */
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int) {

	try {
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Windows11 Modern Light");
		Application->Title = "Dashboard";
		Application->HelpFile = "";
		Application->CreateForm(__classid(TDMod), &DMod);
		Application->CreateForm(__classid(TFormMain), &FormMain);
		Application->CreateForm(__classid(TFormPrefs), &FormPrefs);
		Application->CreateForm(__classid(TFormSelect), &FormSelect);
		Application->CreateForm(__classid(TAboutBox), &AboutBox);
		Application->CreateForm(__classid(TUpdInfo), &UpdInfo);
		Application->CreateForm(__classid(TDL), &DL);
		Application->Run();
	}

	catch (Exception &exception) {
		Application->ShowException(&exception);
	}

	catch (...) {
		try {
			throw Exception("");
		}
		catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}
	return 0;
}
// ---------------------------------------------------------------------------
