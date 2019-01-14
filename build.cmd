@ECHO OFF
setlocal enabledelayedexpansion

@RD /S /Q x64_logs
mkdir x64_logs

@RD /S /Q x86_logs
mkdir x86_logs

set "VSPATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\BuildTools\Common7\Tools"

if %1.==. (
	set "SEARCH=*"
) else (
	set "SEARCH=%1"
)

rem 64-bit builds
call "%VSPATH%\VsDevCmd.bat" -arch=amd64 -host_arch=amd64
@RD /S /Q temp
mkdir temp
cd temp

CL.exe /std:c++17e /c /Zi /W3 /WX- /Ox /O2 /Oi /GL /D NO_ASM /D X64 /D _WINDLL /D _MBCS /Gm- /EHsc /MD /GS /Gy /fp:precise /Zc:wchar_t /Gd /TP /errorReport:queue /FS ../plugin_include/c8lib.cpp

for /R ..\plugin_source %%f in (%SEARCH%.c*) do (
  echo Building X64: %%f

  CL.exe /std:c++17 /I ..\plugin_include /c /Zi /W3 /WX- /Ox /O2 /Oi /GL /D NO_ASM /D X64 /D _WINDLL /D _MBCS /Gm- /EHsc /MD /GS /Gy /fp:precise /Zc:wchar_t /Gd /TP /errorReport:queue /FS %%f | ..\tools\wtee.exe ..\x64_logs\%%~nf.log.txt
  link.exe /ERRORREPORT:QUEUE /OUT:"%%~nf.dll" /NOLOGO kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /DEF:"../plugin_include/plugin.def" /MANIFEST:NO /DEBUG /PDB:"%%~nf.pdb" /OPT:REF /OPT:ICF /LTCG /TLBID:1 /DYNAMICBASE /NXCOMPAT /IMPLIB:"%%~nf.lib" /MACHINE:X64 /DLL c8lib.obj %%~nf.obj
  copy /Y %%~nf.dll ..\x64\%%~nf.x64.dll

  echo.
  echo.
)
cd ..

rem remove small files so it's just warnings/errors left
cd x64_logs
FOR %%F IN (*.txt) DO (
IF %%~zF LSS 100  DEL %%F
)

cd ..

rem 32-bit builds
call "%VSPATH%\VsDevCmd.bat" -arch=x86 -host_arch=x86
@RD /S /Q temp
mkdir temp
cd temp

CL.exe /std:c++17e /c /Zi /W3 /WX- /Ox /O2 /Oi /GL /D _WINDLL /D _MBCS /Gm- /EHsc /MD /GS /Gy /fp:precise /Zc:wchar_t /Gd /TP /errorReport:queue /FS ../plugin_include/c8lib.cpp

for /R ..\plugin_source %%f in (%SEARCH%.c*) do (   

  echo Building X86: %%f

  CL.exe /I ..\plugin_include /c /Zi /nologo /W3 /WX- /Ox /O2 /Oi /Oy- /GL /D _WINDLL /D _MBCS /Gm- /EHsc /MD /GS /Gy /fp:precise /Zc:wchar_t /Gd /TP /analyze- /errorReport:queue %%f > ..\x86_logs\%%~nf.log.txt | type ..\x86_logs\%%~nf.log.txt
  link.exe /ERRORREPORT:QUEUE /OUT:"%%~nf.dll" /NOLOGO kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /DEF:"../plugin_include/plugin.def" /MANIFEST:NO /DEBUG /PDB:"%%~nf.pdb" /OPT:REF /OPT:ICF /LTCG /TLBID:1 /DYNAMICBASE /NXCOMPAT /IMPLIB:"%%~nf.lib" /MACHINE:X86 /SAFESEH /DLL %%~nf.obj
  copy /Y %%~nf.dll ..\x86\%%~nf.x86.dll

  echo.
  echo.
)
cd ..

rem remove small files so it's just warnings/errors left
cd x86_logs
FOR %%F IN (*.txt) DO (
IF %%~zF LSS 100  DEL %%F
)

cd ..

@RD /S /Q temp
