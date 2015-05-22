# Microsoft Developer Studio Generated NMAKE File, Based on context.dsp
!IF "$(CFG)" == ""
CFG=Context - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Context - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Context - Win32 Release" && "$(CFG)" != "Context - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "context.mak" CFG="Context - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Context - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Context - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Context - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : ".\Context.dll"


CLEAN :
	-@erase "$(INTDIR)\AutoFont.obj"
	-@erase "$(INTDIR)\BitmapDialog.obj"
	-@erase "$(INTDIR)\ConfigDialog.obj"
	-@erase "$(INTDIR)\Context.obj"
	-@erase "$(INTDIR)\context.res"
	-@erase "$(INTDIR)\dib256.obj"
	-@erase "$(INTDIR)\dibpal.obj"
	-@erase "$(INTDIR)\SnapDialog.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SysColorStatic.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xShadeButton.obj"
	-@erase "$(OUTDIR)\Context.exp"
	-@erase "$(OUTDIR)\Context.lib"
	-@erase ".\Context.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDLL" /D "_AFXDLL" /D "AUTOBUILD" /Fp"$(INTDIR)\context.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\context.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\context.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Context.pdb" /machine:I386 /out:"Context.dll" /implib:"$(OUTDIR)\Context.lib" 
LINK32_OBJS= \
	"$(INTDIR)\AutoFont.obj" \
	"$(INTDIR)\BitmapDialog.obj" \
	"$(INTDIR)\ConfigDialog.obj" \
	"$(INTDIR)\Context.obj" \
	"$(INTDIR)\dib256.obj" \
	"$(INTDIR)\dibpal.obj" \
	"$(INTDIR)\SnapDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SysColorStatic.obj" \
	"$(INTDIR)\xShadeButton.obj" \
	"$(INTDIR)\context.res"

".\Context.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Context - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : ".\Context.dll" "$(OUTDIR)\context.bsc"


CLEAN :
	-@erase "$(INTDIR)\AutoFont.obj"
	-@erase "$(INTDIR)\AutoFont.sbr"
	-@erase "$(INTDIR)\BitmapDialog.obj"
	-@erase "$(INTDIR)\BitmapDialog.sbr"
	-@erase "$(INTDIR)\ConfigDialog.obj"
	-@erase "$(INTDIR)\ConfigDialog.sbr"
	-@erase "$(INTDIR)\Context.obj"
	-@erase "$(INTDIR)\context.res"
	-@erase "$(INTDIR)\Context.sbr"
	-@erase "$(INTDIR)\dib256.obj"
	-@erase "$(INTDIR)\dib256.sbr"
	-@erase "$(INTDIR)\dibpal.obj"
	-@erase "$(INTDIR)\dibpal.sbr"
	-@erase "$(INTDIR)\SnapDialog.obj"
	-@erase "$(INTDIR)\SnapDialog.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\SysColorStatic.obj"
	-@erase "$(INTDIR)\SysColorStatic.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xShadeButton.obj"
	-@erase "$(INTDIR)\xShadeButton.sbr"
	-@erase "$(OUTDIR)\context.bsc"
	-@erase "$(OUTDIR)\Context.exp"
	-@erase "$(OUTDIR)\Context.lib"
	-@erase "$(OUTDIR)\Context.pdb"
	-@erase ".\Context.dll"
	-@erase ".\Context.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDLL" /D "_AFXDLL" /D "AUTOBUILD" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\context.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\context.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\context.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AutoFont.sbr" \
	"$(INTDIR)\BitmapDialog.sbr" \
	"$(INTDIR)\ConfigDialog.sbr" \
	"$(INTDIR)\Context.sbr" \
	"$(INTDIR)\dib256.sbr" \
	"$(INTDIR)\dibpal.sbr" \
	"$(INTDIR)\SnapDialog.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\SysColorStatic.sbr" \
	"$(INTDIR)\xShadeButton.sbr"

"$(OUTDIR)\context.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Context.pdb" /debug /machine:I386 /out:"Context.dll" /implib:"$(OUTDIR)\Context.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AutoFont.obj" \
	"$(INTDIR)\BitmapDialog.obj" \
	"$(INTDIR)\ConfigDialog.obj" \
	"$(INTDIR)\Context.obj" \
	"$(INTDIR)\dib256.obj" \
	"$(INTDIR)\dibpal.obj" \
	"$(INTDIR)\SnapDialog.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SysColorStatic.obj" \
	"$(INTDIR)\xShadeButton.obj" \
	"$(INTDIR)\context.res"

".\Context.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("context.dep")
!INCLUDE "context.dep"
!ELSE 
!MESSAGE Warning: cannot find "context.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Context - Win32 Release" || "$(CFG)" == "Context - Win32 Debug"
SOURCE=.\AutoFont.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\AutoFont.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\AutoFont.obj"	"$(INTDIR)\AutoFont.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BitmapDialog.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\BitmapDialog.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\BitmapDialog.obj"	"$(INTDIR)\BitmapDialog.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ConfigDialog.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\ConfigDialog.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\ConfigDialog.obj"	"$(INTDIR)\ConfigDialog.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Context.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\Context.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\Context.obj"	"$(INTDIR)\Context.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\dib256.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\dib256.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\dib256.obj"	"$(INTDIR)\dib256.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\dibpal.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\dibpal.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\dibpal.obj"	"$(INTDIR)\dibpal.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SnapDialog.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\SnapDialog.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\SnapDialog.obj"	"$(INTDIR)\SnapDialog.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SysColorStatic.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\SysColorStatic.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\SysColorStatic.obj"	"$(INTDIR)\SysColorStatic.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\xShadeButton.cpp

!IF  "$(CFG)" == "Context - Win32 Release"


"$(INTDIR)\xShadeButton.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "Context - Win32 Debug"


"$(INTDIR)\xShadeButton.obj"	"$(INTDIR)\xShadeButton.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\context.rc

"$(INTDIR)\context.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

