@echo off
echo *
echo *
echo *
echo *
echo *****************************************************
echo build of [%1.dll ]
echo *****************************************************
set DLL_FILE=%1.dll

echo removing temporary files
del /F /Q .\Release\*
del .\Context.dll

echo copy source files
copy ..\source\%1.cpp              ..\build\context.cpp
copy ..\source\%1.rc               ..\build\context.rc
copy ..\source\%1_ConfigDialog.c   ..\build\ConfigDialog.cpp
copy ..\source\%1_ConfigDialog.h   ..\build\ConfigDialog.h
copy ..\source\%1_resource.h       ..\build\resource.h

echo compiling files
nmake /C /D -f context.mak CFG="Context - Win32 Release"

echo copy file '.\Context.dll' '..\..\..\..\..\bin\plugins\%DLL_FILE%'
copy .\Context.dll ..\..\..\..\..\bin\plugins\%DLL_FILE%


