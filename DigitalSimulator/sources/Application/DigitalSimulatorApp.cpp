/* NO WARRANTY
 *
 *    BECAUSE THE PROGRAM IS IN THE PUBLIC DOMAIN, THERE IS NO
 *    WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE
 *    LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE AUTHORS
 *    AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 *    AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO
 *    THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD
 *    THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL
 *    NECESSARY SERVICING, REPAIR OR CORRECTION.
 *
 *    IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN
 *    WRITING WILL ANY AUTHOR, OR ANY OTHER PARTY WHO MAY MODIFY
 *    AND/OR REDISTRIBUTE THE PROGRAM, BE LIABLE TO YOU FOR DAMAGES,
 *    INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 *    DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM
 *    (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING
 *    RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES
 *    OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
 *    PROGRAMS), EVEN IF SUCH AUTHOR OR OTHER PARTY HAS BEEN ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGES.
 */

#pragma warning(disable : 4786)
#include <vector>
#include <CString>
#include <algorithm>
#include <stdio.h>
#include <io.h>
#include <time.h>
#include <dos.h>
#include <direct.h>

#include "stdafx.h"

//libs
#include "DragDropLib.h"

// utils
#include "utils\process.h"
#include "utils\global_defines.h"
#include "utils\DigitalTrainingStudio_version.h"

// application
#include "DigitalSimulatorApp.h"
#include "Application\Controls\URLStatic\URLStatic.h"
#include "Application\Windows\MainFrm.h"
#include "Application\Windows\ChildFrm.h"
#include "Application\Windows\Workplace\DigitalTraineeStudioDoc.h"
#include "Application\Windows\Workplace\DigitalTraineeStudioView.h"
#include "Application\Windows\Palette\ObjectDockingControlBarView.h"
#include "Application\Dialogs\ObjectDialogs\DialogSecondaryObjectOptions.h"
#include "Application\Dialogs\Vote\DialogVoteForTheFuture.h"
#include "Application\i18n\TranslateMultiDocTemplate.h"
#include "Application\Controls\SplashScreen\SplashScreen.h"
#include "Application\Controls\ShadeButton\ShadeButton.h"
#include "Application\JavaBinding\ApplicationProxyWrapper.h"

// for the Plugins
//

#include "Application\Objects\Plugin\DLL\DynamicLibrary.h"
#include "Application\Objects\Plugin\DLL\SerialPort\SerialPluginManager.h"
#include "Application\Objects\Plugin\DLL\SimpleType\ObjectPluginManager.h"
#include "Application\Objects\Plugin\DLL\SimpleType\Context\ElectricNodeContextPluginWrapper.h"
#include "Application\Objects\Plugin\Java\JavaPluginManager.h"

DigitalSimulatorApp theApp;

HANDLE DigitalSimulatorApp::m_mainThread=NULL;


BEGIN_MESSAGE_MAP(DigitalSimulatorApp, CWinApp)
	//{{AFX_MSG_MAP(DigitalSimulatorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Dateibasierte Standard-Dokumentbefehle
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard-Druckbefehl "Seite einrichten"
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND( ID_HELP, OnHelp )
	// Version 1.1: 
	// (ID_POPUP_DynCmd01 value is defined in DynamicMenu.h)
	// Range value for all dynamic items in the menu
END_MESSAGE_MAP()



//----------------------------------------------------------------------------
DigitalSimulatorApp::DigitalSimulatorApp(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

// hooks for your initialization code
BOOL DigitalSimulatorApp::InitApplication()
{
   LM::log(LM::info,"InitApplication %s",__DATE__);
	LM::log(LM::info,"--------------------------------------------------\n");
	return TRUE;
}

//----------------------------------------------------------------------------
BOOL DigitalSimulatorApp::InitInstance(){
//----------------------------------------------------------------------------
   PROC_TRACE;

   LM::log(LM::info,"Starting DigitalSimulator with build from %s",__DATE__);
   LM::log(LM::info,"--------------------------------------------------\n");

   // Init the SplashScreen
   //
   if(GET_PARAMETER("ViewSplashScreen")=="TRUE"){
	   CSplashScreenWnd::EnableSplashScreen(TRUE);
   }
   else{
      LM::log(LM::debug1,"'ViewSplashScreen' disabled");
   }


   // cleanup temp directory
   //
   struct _finddata_t c_file;
   long hFile;
   CString  tempPath=TEMP_PATH("");

   /* Find first .gop file in current directory */
   if( (hFile = _findfirst( (tempPath+"*.*"), &c_file )) != -1L ){
	   if(!(c_file.attrib&_A_SUBDIR))
		   CFile::Remove(tempPath+c_file.name);

      /* Find the rest of the files */
      while( _findnext( hFile, &c_file ) == 0 ){
	   if(!(c_file.attrib&_A_SUBDIR))
         try
         {
		      CFile::Remove(tempPath+c_file.name);
         }
         catch(...)
         {
         }
      }
      _findclose( hFile );
   }


   m_mainThread= GetCurrentThread();
   
   // start the trace window for the startup monitoring of the application
   //
   if(GET_PARAMETER("OpenTraceWin").CompareNoCase("true")==0)
      startProcess("TraceWin.exe","",FALSE);

   // init the java envirorment
   //
   JavaPluginManager::init();

   // Init the language translation support
   //
   RecourceTranslater::Instance();

   
   // Init the socket stuff
   //
   if (!AfxSocketInit())	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

#ifdef _AFXDLL
	Enable3dControls();			// Diese Funktion bei Verwendung von MFC in gemeinsam genutzten DLLs aufrufen
#else
	Enable3dControlsStatic();	// Diese Funktion bei statischen MFC-Anbindungen aufrufen
#endif


   // Init the DragDrop Application stuff
   //
   if (!Init())
      return FALSE;


	SetRegistryKey(REGISTRY_KEY);
	LoadStdProfileSettings();  // Standard-INI-Dateioptionen einlesen (einschließlich MRU)


    // register all DLL-Plugins
    //
    RegisterAllPlugins();



   // call the Java Application Wrapper for the Java side init handling
   // Note: must be called before loading the palette files. The palette uses
   // object plugins which will be loaded in the onInit() method
   //
   ApplicationProxyWrapper::onInit();

   
   // Dokumentvorlagen der Anwendung registrieren. Dokumentvorlagen
	//  dienen als Verbindung zwischen Dokumenten, Rahmenfenstern und Ansichten.
   m_pDocManager = new CTranslateDocManager;

	CTranslateMultiDocTemplate* pDocTemplateDigital;
   pDocTemplateDigital = new CTranslateMultiDocTemplate(IDR_DIGITATYPE,
		                                  RUNTIME_CLASS(CDigitalTraineeStudioDoc),
		                                  RUNTIME_CLASS(CChildFrame),
		                                  RUNTIME_CLASS(CDigitalTraineeStudioView));
   m_pDocManager->AddDocTemplate(pDocTemplateDigital);
   RegisterShellFileTypes();

	// Init the main window
   //
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME_FREE))
		return FALSE;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	m_pMainWnd = pMainFrame;
   // Translate the G_UI without any client window
   //
   pMainFrame->TranslateGUI();

   InitializePalette();

	CCommandLineInfo cmdInfo;
   if (m_lpCmdLine[0] == '\0')   {
      pDocTemplateDigital->OpenDocumentFile(NULL);
   }
   else  {
      // Open an existing document.
      OpenDocumentFile(m_lpCmdLine);
   }
   // translate the GUI with an opend client window
   // In this case the top menu bar has different entries
   //
   pMainFrame->TranslateGUI();



   // Init the last working directory
   //
   CString path = GET_PARAMETER("WorkingDirectory");
   if(path != CString("")){
      _chdir((LPCSTR)path);
   }


   if(GET_PARAMETER("OpenTraceWin").CompareNoCase("true")==0)
   {
      #define TRACEWND_CLASSNAME _T("FreeGroupTraceWindow")
	   HWND hTraceWnd = ::FindWindow(TRACEWND_CLASSNAME, NULL);
	   if (hTraceWnd)
      {
		   COPYDATASTRUCT cds;
//		   cds.dwData    = ID_COPYDATA_TRACEMSG;
//		   cds.cbData    = strlen(buffer2);
//		   cds.lpData    = buffer2;
		   CWinApp* pApp = AfxGetApp();
		   HWND hWnd = pApp ? pApp->m_pMainWnd->GetSafeHwnd() : NULL;
		   ::SendMessage(hTraceWnd, WM_CLOSE, (WPARAM)hWnd, (LPARAM)&cds);
	   }
   }

   return TRUE;
}




//----------------------------------------------------------------------------
void DigitalSimulatorApp::OnAppAbout(){
//----------------------------------------------------------------------------
	PROC_TRACE;


   ApplicationProxyWrapper::onHelpAbout();
}


//----------------------------------------------------------------------------
void DigitalSimulatorApp::RegisterAllPlugins(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   LM::log(LM::info,"Loading native object extensions ");
   LM::log(LM::info,"--------------------------------");

   if(GET_PARAMETER("LoadingPlugIns")=="TRUE"){
      struct _finddata_t c_file;
      long hFile;
      std::vector<CString> files;
      std::vector<CString>::iterator it ;

      CString     palettePath=PLUGIN_PATH("");

      // Find first .dll file in current directory 
      if( (hFile = _findfirst( (palettePath+"*.dll"), &c_file )) == -1L ){
	      //
	      // keine Plugins vorhanden
	      //
         LM::log(LM::info,"no plugins (DLL) in '%s' found",(LPCSTR)palettePath);
      }
      else {
         files.push_back(palettePath+c_file.name);

         // Find the rest of the files 
         while( _findnext( hFile, &c_file ) == 0 ){
		   files.push_back(palettePath+c_file.name);
         }

         _findclose( hFile );
 	      std::sort(files.begin(), files.end());
         for(it = files.begin(); it != files.end(); it++){
            RegisterPlugin((*it));
         }
      }
   }
   else{
      LM::log(LM::debug1,"LoadingPlugIns disabled.....");
   }

   LM::log(LM::info,"");
}


//----------------------------------------------------------------------------
BOOL DigitalSimulatorApp::RegisterPlugin(CString fileName){
//----------------------------------------------------------------------------
	PROC_TRACE;


   DynamicLibrary *cf= new DynamicLibrary((LPCSTR)fileName );
   if (cf->IsLoaded()){ 
		// create the Initial interface pointer
      IPluginInfo    *pi;
      IObjectContext *oc;
      if (cf->CreateInterface("IPluginInfo",reinterpret_cast<IPluginBase**>(&pi))){
         char buffer[200];
         pi->getKey(buffer,sizeof(buffer));
         SerialPluginManager::registerPlugin(CString(buffer),cf);
         pi->Destroy();
         LM::log(LM::info, "PlugIn '%s' loaded successfull",(LPCSTR)fileName);
		}
      else if (cf->CreateInterface("IObjectContext",reinterpret_cast<IPluginBase**>(&oc))){
         new CElectricNodeContextPluginWrapper(oc);
         ObjectPluginManager::registerPlugin(oc->getKey(),cf);
         LM::log(LM::info, "PlugIn '%s' loaded successfull",(LPCSTR)fileName);
      }
      else{
         LM::log(LM::warning, "can't load PlugIn '%s'",(LPCSTR)fileName );
      }
   }
   else{
      LM::log(LM::warning, "can't load PlugIn '%s'",(LPCSTR)fileName );
   }

   return TRUE;
}


//----------------------------------------------------------------------------
void DigitalSimulatorApp::OnHelp( ){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // wird im CDigitalTraineeStudioView abgearbeitet
   //
}

//----------------------------------------------------------------------------
int DigitalSimulatorApp::ExitInstance(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // letzten Arbeitpfad speichern und bei einem erneuten Start verwenden
   //
   char buffer[_MAX_PATH];
   /* Get the current working directory: */
   if( _getcwd( buffer, _MAX_PATH ) == NULL ){
      //perror( "_getcwd error" );
   }
   else{
      SET_PARAMETER("WorkingDirectory",CString( buffer));

   }

   // Allgemeine Contexte für die grafischen Objekte
   // freigeben
   //
   CElectricNodeContext* pContext;
   CString item;
   POSITION pos = g_contextMap->GetStartPosition();
   while( pos != NULL ) {
      g_contextMap->GetNextAssoc( pos, item, pContext );
      if(pContext)
         delete pContext;
   }
   g_contextMap->RemoveAll();



   // Seriell Plugins freigeben
   //
   SerialPluginManager::clear();
   
   // ObjectPlugIn freigeben
   //
   ObjectPluginManager::clear();

   // configurationsdaten speichern
   //
   ParameterManager::Instance().Save();


   ApplicationProxyWrapper::onExit();

   // temp-directory clean up
   //

   return CWinApp::ExitInstance();
} 
