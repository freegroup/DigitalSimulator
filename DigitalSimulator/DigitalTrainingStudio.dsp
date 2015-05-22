# Microsoft Developer Studio Project File - Name="DigitalTrainingStudio" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** NICHT BEARBEITEN **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=DigitalTrainingStudio - Win32 Debug
!MESSAGE Dies ist kein gültiges Makefile. Zum Erstellen dieses Projekts mit NMAKE
!MESSAGE verwenden Sie den Befehl "Makefile exportieren" und führen Sie den Befehl
!MESSAGE 
!MESSAGE NMAKE /f "DigitalTrainingStudio.mak".
!MESSAGE 
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "DigitalTrainingStudio.mak" CFG="DigitalTrainingStudio - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "DigitalTrainingStudio - Win32 Release" (basierend auf  "Win32 (x86) Application")
!MESSAGE "DigitalTrainingStudio - Win32 Debug" (basierend auf  "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "DigitalSimulator"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DigitalTrainingStudio - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "DigitalTrainingStudio___Win32_Release"
# PROP BASE Intermediate_Dir "DigitalTrainingStudio___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release\DigitalSimulator"
# PROP Intermediate_Dir "Release\DigitalSimulator"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /Od /I ".\sources\\" /I ".\sources\libraries\AVI" /I ".\sources\libraries\Crypto\\" /I ".\sources\libraries\DDE\\" /I ".\sources\libraries\DragDrop\\" /I ".\sources\libraries\JNI\\" /I ".\sources\libraries\PNG\\" /D "WITH_AVI" /D "WITH_JVM" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /FD /c
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /nologo /MD /W3 /GX /Od /I ".\\" /I ".\sources\\" /I ".\sources\libraries\AVI" /I ".\sources\libraries\Crypto\\" /I ".\sources\libraries\DDE\\" /I ".\sources\libraries\DragDrop\\" /I ".\sources\libraries\JNI\\" /I ".\sources\libraries\PNG\\" /D "WITH_AVI" /D "WITH_JVM" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 vfw32.lib /nologo /subsystem:windows /profile /machine:I386 /out:"bin/DigitalSimulator_release_java_avi.exe"
# SUBTRACT BASE LINK32 /debug
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /profile /machine:I386 /out:"bin/DigitalSimulator_release.exe"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "DigitalTrainingStudio - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "DigitalTrainingStudio___Win32_Debug"
# PROP BASE Intermediate_Dir "DigitalTrainingStudio___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug\DigitalSimulator"
# PROP Intermediate_Dir "Debug\DigitalSimulator"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /MDd /W3 /vd0 /GR /GX /ZI /Od /I ".\\" /I ".\DragDrop\include" /I ".\source\application" /I ".\source\libraries\\" /I ".\source\utils" /I ".\sources\\" /I ".\sources\libraries\AVI" /I ".\sources\libraries\Crypto\\" /I ".\sources\libraries\DDE\\" /I ".\sources\libraries\DragDrop\\" /I ".\sources\libraries\JNI\\" /I ".\sources\libraries\PNG\\" /D "WITH_AVI" /D "WITH_JVM" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /FD /c
# ADD CPP /MDd /W3 /vd0 /GR /GX /ZI /Od /I ".\\" /I ".\DragDrop\include" /I ".\source\application" /I ".\source\libraries\\" /I ".\source\utils" /I ".\sources\\" /I ".\sources\libraries\AVI" /I ".\sources\libraries\Crypto\\" /I ".\sources\libraries\DDE\\" /I ".\sources\libraries\DragDrop\\" /I ".\sources\libraries\JNI\\" /I ".\sources\libraries\PNG\\" /D "WITH_AVI" /D "WITH_JVM" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /FR /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 vfw32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"bin/DigitalSimulator_debug_java_avi.exe" /pdbtype:sept
# ADD LINK32 vfw32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /out:"bin/DigitalSimulator_debug.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DigitalTrainingStudio - Win32 Release"
# Name "DigitalTrainingStudio - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Application"

# PROP Default_Filter ""
# Begin Group "Configuration"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Configuration\ParameterManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Configuration\ParameterManager.h
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter ""
# Begin Group "ColorStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\ColorStatic\ColorStatic.h
# End Source File
# End Group
# Begin Group "DataTip"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\DataTip\Tfxdatatip.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\DataTip\Tfxdatatip.h
# End Source File
# End Group
# Begin Group "ImageStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\ImageStatic\TransparentImageStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\ImageStatic\TransparentImageStatic.h
# End Source File
# End Group
# Begin Group "MailStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\MailStatic\IMapi.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\MailStatic\IMapi.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\MailStatic\MailLink.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\MailStatic\MailLink.h
# End Source File
# End Group
# Begin Group "NumSpin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\NumSpin\NumEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\NumSpin\NumEdit.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\NumSpin\NumSpinCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\NumSpin\NumSpinCtrl.h
# End Source File
# End Group
# Begin Group "PrintfStatusBar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\PrintfStatusBar\PrintfStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\PrintfStatusBar\PrintfStatusBar.h
# End Source File
# End Group
# Begin Group "ResizeTabControlBar"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\ResizeTabControlBar\sizecbar.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\ResizeTabControlBar\sizecbar.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\ResizeTabControlBar\SizingTabCtrlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\ResizeTabControlBar\SizingTabCtrlBar.h
# End Source File
# End Group
# Begin Group "ShadeButton"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\ShadeButton\ShadeButton.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\ShadeButton\ShadeButton.h
# End Source File
# End Group
# Begin Group "SnakeStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\SnakeStatic\SnakeStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\SnakeStatic\SnakeStatic.h
# End Source File
# End Group
# Begin Group "SplashScreen"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\SplashScreen\SplashScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\SplashScreen\SplashScreen.h
# End Source File
# End Group
# Begin Group "URLStatic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Controls\URLStatic\URLStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Controls\URLStatic\URLStatic.h
# End Source File
# End Group
# End Group
# Begin Group "Debug"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Debug\ExceptionStackTrace.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Debug\ExceptionStackTrace.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Debug\LogManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Debug\LogManager.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Debug\StackLogObject.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Debug\StackLogObject.h
# End Source File
# End Group
# Begin Group "Dialogs"

# PROP Default_Filter ""
# Begin Group "ColorSpaceDialog"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ColorSpaceDialog\colorpickerdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ColorSpaceDialog\colorpickerdlg.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ColorSpaceDialog\Common.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ColorSpaceDialog\Common.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ColorSpaceDialog\DIB.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ColorSpaceDialog\DIB.h
# End Source File
# End Group
# Begin Group "CommonDialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\CommonDialogs\BmpFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\CommonDialogs\BmpFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\CommonDialogs\CustomFontDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\CommonDialogs\CustomFontDialog.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\CommonDialogs\TranslateFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\CommonDialogs\TranslateFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\CommonDialogs\TranslatePrintDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\CommonDialogs\TranslatePrintDialog.h
# End Source File
# End Group
# Begin Group "DocumentLock"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\DocumentLock\DialogLockDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\DocumentLock\DialogLockDocument.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\DocumentLock\DialogUnlockDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\DocumentLock\DialogUnlockDocument.h
# End Source File
# End Group
# Begin Group "Export"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\Export\DialogExport.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\Export\DialogExport.h
# End Source File
# End Group
# Begin Group "FileFinder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\FileFinder\FileFinder.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\FileFinder\FileFinder.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\FileFinder\findfiledlg.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\FileFinder\findfiledlg.h
# End Source File
# End Group
# Begin Group "generic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\generic\BitmapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\generic\BitmapDialog.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\generic\SnapDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\generic\SnapDialog.h
# End Source File
# End Group
# Begin Group "JavaPlugin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\JavaPlugin\DialogSelectJVM.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\JavaPlugin\DialogSelectJVM.h
# End Source File
# End Group
# Begin Group "ObjectDialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEExcelProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEExcelProperties.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEINCosivisProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEINCosivisProperties.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\dialogddeineasyportproperties.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\dialogddeineasyportproperties.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEINEndPage.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEINEndPage.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEINParamWizard.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEINParamWizard.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEINStartPage.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEINStartPage.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOUTCosivisProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOUTCosivisProperties.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOUTEasyPortProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOUTEasyPortProperties.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOUTEndPage.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOUTEndPage.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOUTParamWizard.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOUTParamWizard.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\dialogddeoutputparam.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\dialogddeoutputparam.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOutStartPage.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEOutStartPage.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEParam.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEParam.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDESelectApplication.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDESelectApplication.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEUnbekanntProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDDEUnbekanntProperties.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDemultiplexerParam.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\dialogdemultiplexerparam.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDividerParam.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogDividerParam.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogMultiplexerParam.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogMultiplexerParam.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogPluginObjectOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogPluginObjectOptions.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogPowerTasterParam.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogPowerTasterParam.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogPrimaryObjectOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogPrimaryObjectOptions.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\dialogsecondaryobjectoptions.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\dialogsecondaryobjectoptions.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogSerielInOption.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogSerielInOption.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogSerielOutOption.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogSerielOutOption.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogTaktParam.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogTaktParam.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogTasterParam.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\DialogTasterParam.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\GroupTreeControl.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\ObjectDialogs\GroupTreeControl.h
# End Source File
# End Group
# Begin Group "Vote"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Dialogs\Vote\DialogVoteForTheFuture.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\Vote\DialogVoteForTheFuture.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\Application\Dialogs\DialogOsziOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Dialogs\DialogOsziOptions.h
# End Source File
# End Group
# Begin Group "i18n"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\i18n\ResourceTranslater.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\i18n\ResourceTranslater.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\i18n\TranslateDocManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\i18n\TranslateDocManager.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\i18n\TranslateMultiDocTemplate.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\i18n\TranslateMultiDocTemplate.h
# End Source File
# End Group
# Begin Group "JavaBinding"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\ApplicationProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\ApplicationProxy.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\ApplicationProxyWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\ApplicationProxyWrapper.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\I18NProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\I18NProxy.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_Configuration.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_Configuration.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_Document.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_Document.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_ObjectPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_ObjectPlugin.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_Painter.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_Painter.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_PluginManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_PluginManager.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_Trace.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\JNI_Trace.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\SimulationDocumentManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\JavaBinding\SimulationDocumentManager.h
# End Source File
# End Group
# Begin Group "Objects"

# PROP Default_Filter ""
# Begin Group "buildin"

# PROP Default_Filter ""
# Begin Group "Analog"

# PROP Default_Filter ""
# End Group
# Begin Group "Common"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Common\DocumentDocumentation.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Common\DocumentDocumentation.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Common\DocumentProtection.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Common\DocumentProtection.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Common\ElectricBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Common\ElectricBitmap.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Common\ElectricText.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Common\ElectricText.h
# End Source File
# End Group
# Begin Group "Digital"

# PROP Default_Filter ""
# Begin Group "Context"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContext7Segment.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContext7Segment.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextAND.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextAND.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBCDCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBCDCounter.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBCDto7SEGMENT.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBCDto7SEGMENT.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBCDtoDEZ.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBCDtoDEZ.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBinaryCounter.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBinaryCounter.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBinaryDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextBinaryDisplay.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextD_R_T.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextD_R_T.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextD_SR_T.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextD_SR_T.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextD_T.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextD_T.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextDemultiplexer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextDemultiplexer.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextDivider.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextDivider.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextGenericGate.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextGenericGate.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextJK_R_T.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextJK_R_T.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextJK_SR_T.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextJK_SR_T.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextJK_T.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextJK_T.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextMultiplexer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextMultiplexer.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextNAND.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextNAND.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextNOR.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextNOR.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextNOT.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextNOT.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextOR.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextOR.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextPower.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextPower.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextPowerTaster.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextPowerTaster.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextRS.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextRS.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextRS_T.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextRS_T.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextSwitch.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextT.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextT.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextTakt.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextTakt.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextTaster.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextTaster.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextUM.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextUM.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextXNOR.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextXNOR.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextXOR.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\Context\ElectricNodeContextXOR.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\DDEInputNode.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\DDEInputNode.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\DDENode.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\DDENode.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\DDEOuputNode.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\DDEOuputNode.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ElectricNode.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ElectricNode.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ElectricNodeContext.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ElectricNodeContext.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ElectricPort.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ElectricPort.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ElectricPortLink.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ElectricPortLink.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\IconContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\IconContainer.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\LogicValue.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\LogicValue.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\PortContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\PortContainer.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ViewPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ViewPoint.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ViewPointText.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\buildin\Digital\ViewPointText.h
# End Source File
# End Group
# End Group
# Begin Group "plugin"

# PROP Default_Filter ""
# Begin Group "DLL"

# PROP Default_Filter ""
# Begin Group "SerialPort"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SerialPort\SerialInNode.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SerialPort\SerialInNode.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SerialPort\SerialOutNode.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SerialPort\SerialOutNode.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SerialPort\SerialPluginManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SerialPort\SerialPluginManager.h
# End Source File
# End Group
# Begin Group "SimpleType"

# PROP Default_Filter ""
# Begin Group "Context No. 1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SimpleType\Context\ElectricNodeContextPluginWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SimpleType\Context\ElectricNodeContextPluginWrapper.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SimpleType\ObjectPluginManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\SimpleType\ObjectPluginManager.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\DynamicLibrary.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\DLL\DynamicLibrary.h
# End Source File
# End Group
# Begin Group "Java"

# PROP Default_Filter ""
# Begin Group "Context No. 2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\Context\ElectricNodeContextJavaWrapper.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\Context\ElectricNodeContextJavaWrapper.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\JavaPluginManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\JavaPluginManager.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\ObjectPluginProxy.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\ObjectPluginProxy.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\ObjectPluginProxyExtender.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\ObjectPluginProxyExtender.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Objects\plugin\Java\ObjectPluginProxyForward.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Windows"

# PROP Default_Filter ""
# Begin Group "Oszi"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\OsziDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\OsziDoc.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\OsziDockingControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\OsziDockingControlBar.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\OsziStroke.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\OsziStroke.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\osziview.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\osziview.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\StrokeContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Oszi\StrokeContainer.h
# End Source File
# End Group
# Begin Group "Palette"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Windows\Palette\DockingPaletteDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Palette\DockingPaletteDoc.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Palette\ObjectDockingControlBar.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Palette\ObjectDockingControlBar.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Palette\ObjectDockingControlBarView.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Palette\ObjectDockingControlBarView.h
# End Source File
# End Group
# Begin Group "Workplace"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Application\Windows\Workplace\DigitalTraineeStudioDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Workplace\DigitalTraineeStudioDoc.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Workplace\DigitalTraineeStudioView.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\Workplace\DigitalTraineeStudioView.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\Application\Windows\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\MainToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\Windows\MainToolBar.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\sources\Application\DigitalSimulatorApp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Application\DigitalSimulatorApp.h
# End Source File
# End Group
# Begin Group "libraries"

# PROP Default_Filter ""
# Begin Group "AVI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\libraries\AVI\AVIFile.CPP
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\AVI\AVIFile.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\AVI\dib256.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\AVI\dib256.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\AVI\dibpal.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\AVI\dibpal.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\AVI\MemDC.h
# End Source File
# End Group
# Begin Group "Crypto"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\libraries\Crypto\3way.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\3way.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\aes.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\algebra.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\algebra.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\arc4.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\arc4.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\asn.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\asn.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\base64.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\base64.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\bench.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\bench.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\bfinit.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\blowfish.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\blumgold.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\blumgold.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\blumshub.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\blumshub.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\cast.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\cast.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\casts.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\cbc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\cbc.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\cbcmac.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\channels.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\channels.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\config.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\crc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\crc.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\cryptlib.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\cryptlib.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\crypto_adler32.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\crypto_adler32.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\default.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\default.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\des.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\des.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\dessp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\dh.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\dh.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\dh2.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\dh2.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\diamond.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\diamond.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\diamondt.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\dmac.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\dsa.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\dsa.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\ec2n.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\ec2n.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\eccrypto.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\eccrypto.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\ecp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\ecp.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\elgamal.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\elgamal.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\eprecomp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\eprecomp.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\files.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\files.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\filters.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\filters.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gf256.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gf256.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gf2_32.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gf2_32.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gf2n.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gf2n.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gost.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gost.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gzip.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\gzip.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\haval.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\haval.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\hex.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\hex.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\hmac.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\hrtimer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\hrtimer.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\ida.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\ida.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\idea.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\idea.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\integer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\integer.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\iterhash.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\iterhash.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\lubyrack.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\luc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\luc.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\mars.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\mars.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\marss.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\md2.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\md2.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\md5.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\md5.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\md5mac.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\md5mac.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\mdc.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\misc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\misc.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\modarith.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\modes.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\modes.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\modexppc.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\modexppc.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\mqueue.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\mqueue.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\mqv.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\mqv.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\nbtheory.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\nbtheory.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\network.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\network.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\nr.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\nr.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\oaep.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\oaep.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\oids.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\osrng.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\osrng.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\panama.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\panama.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\pch.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\pch.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\pkcspad.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\pkcspad.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\polynomi.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\polynomi.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\pssr.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\pubkey.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\pubkey.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\queue.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\queue.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rabin.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rabin.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\randpool.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\randpool.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rc2.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rc2.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rc5.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rc5.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rc6.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rc6.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rdtables.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rijndael.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rijndael.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\ripemd.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\ripemd.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rng.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rng.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rsa.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rsa.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rw.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\rw.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\safer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\safer.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\sapphire.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\sapphire.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\seal.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\seal.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\secshare.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\secshare.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\serpent.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\serpent.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\sha.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\sha.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\shark.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\shark.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\sharkbox.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\skipjack.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\skipjack.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\smartptr.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\socketft.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\socketft.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\square.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\square.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\squaretb.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\tea.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\tea.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\test.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\tftables.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\tiger.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\tiger.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\tigertab.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\twofish.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\twofish.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\validat1.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\validat2.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\validat3.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\validate.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\wake.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\wake.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\winpipes.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\winpipes.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\words.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\xormac.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\xtr.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\xtr.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\xtrcrypt.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\xtrcrypt.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\zdeflate.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\zdeflate.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\zinflate.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\zinflate.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\zlib.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\Crypto\zlib.h
# End Source File
# End Group
# Begin Group "DDE"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\libraries\DDE\DDEAdviceConv.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DDE\DDEAdviceConv.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DDE\STDDDE.CPP
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DDE\STDDDE.H
# End Source File
# End Group
# Begin Group "DragDrop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\defines.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDrop.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropApp.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropApp.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropArea.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropArea.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropBitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropBitmap.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropBitmapCach.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropBitmapCach.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropClientApp.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropCursorManager.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropCursorManager.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropdib.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropdib.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropDocument.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropDocument.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropDrawable.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropDrawable.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropEdit.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropGridView.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropGridView.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropHandle.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropLayout.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropLayout.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDroplib.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropLink.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropLink.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropMDIFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropMDIFrame.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropMetafile.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropMetafile.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropMetrics.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropMetrics.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropObject.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropObject.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropPalett.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropPalett.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropPort.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropPort.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropRect.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropRect.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropSelection.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropSelection.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropStdafx.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropStdafx.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropStroke.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropStroke.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropText.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropText.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropView.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\DragDropView.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\WMFDCODE.H
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\WmfDecode.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\DragDrop\wmfexint.h
# End Source File
# End Group
# Begin Group "JNI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\libraries\JNI\BaseException.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\ClassNotFoundException.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\EnvironmentAlreadyInitializedException.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\EnvironmentNotInitializedException.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\FieldNotFoundException.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\InitializationException.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JNIEnvHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JNIEnvHelper.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JStringHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JStringHelper.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JStringHelperArray.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JStringHelperArray.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JVM.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JVM.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\JVMException.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\MethodNotFoundException.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\ObjectProxyArray.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\PrimitiveArray.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\PrimitiveArray.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\JNI\ProxyArray.h
# End Source File
# End Group
# Begin Group "PNG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\libraries\PNG\adler32.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\compress.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\crc32.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\deflate.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\deflate.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\gzio.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\hipng.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\hipng.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\infblock.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\infblock.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\infcodes.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\infcodes.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\inffast.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\inffast.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\inffixed.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\inflate.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\inftrees.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\inftrees.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\infutil.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\infutil.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\minigzip.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\png.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\png.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\png_test.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngasmrd.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngconf.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngerror.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngget.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\PNGImageDC.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\PNGImageDC.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngmem.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngpread.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngread.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngrio.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngrtran.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngrutil.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngset.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngtrans.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngvcrd.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngwio.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngwrite.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngwtran.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\pngwutil.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\trees.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\trees.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\uncompr.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\zconf.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\zlib.h
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\zutil.c
# End Source File
# Begin Source File

SOURCE=.\sources\libraries\PNG\zutil.h
# End Source File
# End Group
# Begin Group "ZipArchive"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\AutoBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\AutoBuffer.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\BigFile.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\BigFile.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\CentralDir.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\CentralDir.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\FileHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\FileHeader.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\zconf.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\ZipArchive.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\ZipArchive.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\ZipException.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\ZipException.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\ZipInternalInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\ZipInternalInfo.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\ZipStorage.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\ZipStorage.h
# End Source File
# Begin Source File

SOURCE=.\sources\Libraries\ZipArchive\zlib.h
# End Source File
# End Group
# End Group
# Begin Group "Utils"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sources\Utils\AutoFont.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\AutoFont.h
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\DigitalTrainingStudio_version.h
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\global_defines.h
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\HelpIDs.h
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\process.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\process.h
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\SortableObArray.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\SortableObArray.h
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\ThreadMutex.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\Utils\ThreadMutex.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DigitalTrainingStudio.rc
# End Source File
# Begin Source File

SOURCE=.\sources\resource.h
# End Source File
# Begin Source File

SOURCE=.\sources\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\sources\StdAfx.h
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\res\backgrou.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00008.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00009.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00010.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00011.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00012.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00013.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00014.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00015.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00016.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00017.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00018.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00019.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00020.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00021.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00022.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00023.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00024.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CCHSB.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ccrgb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\connect_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\dde_prop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ddein_en.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ddein_st.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ddeout_c.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ddeout_u.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DigitalTraineeStudio.ico
# End Source File
# Begin Source File

SOURCE=.\res\DigitalTraineeStudioDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\dot_grid.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\line_gri.bmp
# End Source File
# Begin Source File

SOURCE=.\res\oszi_too.bmp
# End Source File
# Begin Source File

SOURCE=.\res\powertas.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ScriptDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\taster_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_disable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_enable.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar_hover.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\bin\langCatalog\languages.xls
# End Source File
# Begin Source File

SOURCE=.\plugins.xml
# End Source File
# End Target
# End Project
# Section DigitalTrainingStudio : {00000000-0001-0000-0000-000000000000}
# 	1:17:CG_IDS_DISK_SPACE:110
# 	1:19:CG_IDS_PHYSICAL_MEM:109
# 	1:25:CG_IDS_DISK_SPACE_UNAVAIL:111
# 	2:14:PhysicalMemory:CG_IDS_PHYSICAL_MEM
# 	2:9:DiskSpace:CG_IDS_DISK_SPACE
# 	2:16:SpaceUnavailable:CG_IDS_DISK_SPACE_UNAVAIL
# 	2:7:NewFunc:1
# 	2:10:SysInfoKey:1234
# End Section
# Section DigitalTrainingStudio : {00000000-002B-0000-2B00-0000443A5C50}
# 	1:24:CG_IDR_POPUP_CHILD_FRAME:106
# End Section
# Section DigitalTrainingStudio : {359703C9-0000-0000-6572-74656E20416E}
# 	1:17:IDB_SPLASH_SCREEN:105
# 	2:21:SplashScreenInsertKey:4.0
# End Section
# Section DigitalTrainingStudio : {00000001-0001-0000-0100-000001000000}
# 	1:28:CG_IDR_POPUP_OBJECT_TOOL_BAR:103
# End Section
