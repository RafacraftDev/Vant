; Script generado para el instalador oficial de Vant Engine
; Engine: Vant Engine
; Platform: Windows x64

#define MyAppName "Vant Engine"
#define MyAppVersion "1.0.0-Native"
#define MyAppPublisher "Vant Team"
#define MyAppURL "https://tu-repositorio-vant.com"
#define MyAppExeName "Vant.exe"
#define MyAppAssocName "Vant Script"
#define MyAppAssocExt ".vant"
#define MyAppAssocKey "VantEngineScript"

[Setup]
; new id
AppId={{A1B2C3D4-E5F6-4789-9123-B0C0D609E782}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\VantEngine
DisableDirPage=yes
ChangesAssociations=yes
DisableProgramGroupPage=yes
ChangesEnvironment=true
LicenseFile=D:\Code\Vant\LICENSE
OutputDir=D:\Code\Vant\Releases\Vant-Installer
OutputBaseFilename=Vant-Setup-x64
SetupIconFile=D:\Code\Vant\vant_logo.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Tasks]
Name: modifypath; Description: "Añadir Vant al PATH (Permite usar 'Vant' en la terminal)"; Flags: unchecked

[Code]
const
    ModPathName = 'modifypath';
    ModPathType = 'system';

function ModPathDir(): TArrayOfString;
begin
    setArrayLength(Result, 1)
    Result[0] := ExpandConstant('{app}');
end;
#include "modpath.iss"

[Languages]
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"

[Files]
; Ejecutable Principal
Source: "D:\Code\Vant\Releases\Vant_Win_Native\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
; Dependencias de SDL2 y Gráficos
Source: "D:\Code\Vant\Releases\Vant_Win_Native\SDL2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Code\Vant\Releases\Vant_Win_Native\SDL2_image.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Code\Vant\Releases\Vant_Win_Native\SDL2_ttf.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Code\Vant\Releases\Vant_Win_Native\zlib1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Code\Vant\Releases\Vant_Win_Native\libpng16-16.dll"; DestDir: "{app}"; Flags: ignoreversion
; Agrega aquí otras DLLs necesarias que use tu compilación de Vant

[Registry]
; Asociación de archivos .vant
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocExt}\OpenWithProgids"; ValueType: string; ValueName: "{#MyAppAssocKey}"; ValueData: ""; Flags: uninsdeletevalue
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppAssocName}"; Flags: uninsdeletekey
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"
Root: HKA; Subkey: "Software\Classes\{#MyAppAssocKey}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
