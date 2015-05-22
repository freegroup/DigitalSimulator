# Microsoft Developer Studio Project File - Name="FischerTechnik_InteliFace" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=FischerTechnik_InteliFace - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FischerTechnik_InteliFace.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FischerTechnik_InteliFace.mak" CFG="FischerTechnik_InteliFace - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FischerTechnik_InteliFace - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FischerTechnik_InteliFace - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FischerTechnik_InteliFace - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release/FischerTechnik_InteliFace"
# PROP Intermediate_Dir "Release/FischerTechnik_InteliFace"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDLL" /D "_AFXDLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386 /out:"bin\plugins\FischerTechnik_InteliFace.dll"

!ELSEIF  "$(CFG)" == "FischerTechnik_InteliFace - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug/FischerTechnik_InteliFace"
# PROP Intermediate_Dir "Debug/FischerTechnik_InteliFace"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDLL" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "FischerTechnik_InteliFace - Win32 Release"
# Name "FischerTechnik_InteliFace - Win32 Debug"
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\FischerTechnik_InteliFace\DialogOption.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\FischerTechnik_InteliFace\DialogOption.h
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\FischerTechnik_InteliFace\FischerTechnik_InteliFace.rc
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\IInputContext.h
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\IOutputContext.h
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\IPluginInfo.h
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\PluginInterface.h
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\FischerTechnik_InteliFace\resource.h
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\SerialPort.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\SerialPort.h
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\FischerTechnik_InteliFace\SerialPortContext.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\SysColorStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Plugins\DLL\SerialPort\SysColorStatic.h
# End Source File
# End Target
# End Project
