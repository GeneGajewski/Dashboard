; -- Example3.iss --
; Same as Example1.iss, but creates some registry entries too and allows the end
; use to choose the install mode (administrative or non administrative).

; SEE THE DOCUMENTATION FOR DETAILS ON CREATING .ISS SCRIPT FILES!



[Setup]

SetupArchitecture=x64

; don't change this ever
AppId={{258CA839-4023-4DC9-A722-7D62E44918F8}}

AppName=Dashboard
AppPublisher=WG5ENE
AppVersion=1.1.0.0
OutputBaseFilename = "Dashboard Installer"
WizardStyle=modern dynamic includetitlebar
DefaultDirName={autopf}\WG5ENE\Dashboard
DefaultGroupName=Dashboard
UninstallDisplayIcon={app}\Dashboard.exe
Compression=lzma2
SolidCompression=yes
OutputDir="..\Intall"
ChangesAssociations=yes
UserInfoPage=yes
PrivilegesRequiredOverridesAllowed=dialog  
SignTool=CustomSign

[Files]
Source: "..\Win64\Release\Dashboard.exe"; DestDir: "{app}";   Flags: sign
Source: "..\Win64\Release\Dashboard.chm"; DestDir: "{app}"; 

; these will need to be changed if using a different version compiler
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\borlndmm.dll" ; DestDir: "{app}"
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\cc64290mt.dll"; DestDir: "{app}"
Source: "C:\Program Files (x86)\Embarcadero\Studio\23.0\bin64\sk4d.dll"; DestDir: "{app}"

Source: "Readme.txt"; DestDir: "{app}"; Flags: isreadme

[Icons]
Name: "{group}\Dashboard"; Filename: "{app}\Dashboard.exe"
Name: "{group}\Uninstall Dashboard"   ; Filename: "{uninstallexe}"


[Code]
function ShouldSkipPage(PageID: Integer): Boolean;
begin
  Result := IsAdminInstallMode and (PageID = wpUserInfo);
end;
