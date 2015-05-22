#ifdef WITH_JVM


// JavaPluginManager.cpp: Implementierung der Klasse JavaPluginManager.
//
//////////////////////////////////////////////////////////////////////

#pragma warning(disable : 4786)
#include <vector>
#include <CString>
#include <algorithm>
#include <stdio.h>
#include <io.h>
#include "stdafx.h"

// libryries/JNI
#include "JNIEnvHelper.h"
#include "JVM.h"

#include "Application\Debug\LogManager.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Objects\plugin\Java\Context\ElectricNodeContextJavaWrapper.h"

#include "Application\Dialogs\FileFinder\FindFileDlg.h"
#include "Application\Dialogs\FileFinder\FileFinder.h"
#include "Application\Dialogs\JavaPlugin\DialogSelectJVM.h"
#include "Application\JavaBinding\JNI_Painter.h"
#include "Application\JavaBinding\JNI_Trace.h"
#include "Application\JavaBinding\JNI_Configuration.h"
#include "Application\JavaBinding\JNI_PluginManager.h"
#include "Application\JavaBinding\JNI_ObjectPlugin.h"
#include "Application\JavaBinding\JNI_Document.h"
#include "Libraries\ZipArchive\ZipArchive.h"
#include "Libraries\ZipArchive\FileHeader.h"

#include "JavaPluginManager.h"

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else /* UNIX */
#define PATH_SEPARATOR ':'
#endif

using namespace de::freegroup::jnipp;


JavaPluginManager javaVM;


JNINativeMethod painter_methods[] = 
{
   {"n_drawLine"  ,"(IIII)V"                    ,Java_Painter_drawLine},
   {"n_drawLine"  ,"(IIIIIII)V"                 ,Java_Painter_drawLineRGB},
   {"n_drawOval"  ,"(IIII)V"                    ,Java_Painter_drawOval},
   {"n_drawOval"  ,"(IIIIIII)V"                 ,Java_Painter_drawOvalRGB},
   {"n_fillOval"  ,"(IIIIIIIIIII)V"             ,Java_Painter_fillOval},
   {"n_drawRect"  ,"(IIII)V"                    ,Java_Painter_drawRect},
   {"n_drawRect"  ,"(IIIIIII)V"                 ,Java_Painter_drawRectRGB},
   {"n_fillRect"  ,"(IIIIIIIIIII)V"             ,Java_Painter_fillRect},
   {"n_drawText"  ,"(Ljava/lang/String;III)V"     ,Java_Painter_drawText},
   {"n_drawText"  ,"(Ljava/lang/String;IIIIII)V"  ,Java_Painter_drawTextRGB}
};


JNINativeMethod trace_methods[] = 
{
   {"n_error"   , "(Ljava/lang/String;)V"   ,Java_Trace_error},
   {"n_warning" , "(Ljava/lang/String;)V"   ,Java_Trace_warning},
   {"n_info"    , "(Ljava/lang/String;)V"   ,Java_Trace_info}
};


JNINativeMethod configuration_methods[] = 
{
   {"n_getString",  "(Ljava/lang/String;)Ljava/lang/String;"  ,Java_Configuration_getString},
   {"n_setString",  "(Ljava/lang/String;Ljava/lang/String;)V" ,Java_Configuration_setString}
};


JNINativeMethod document_methods[] = 
{
   {"n_getCurrentAsXML",          "()Ljava/lang/String;"  ,Java_Document_getCurrentAsXML},
   {"n_setCurrentDocumentation",  "(Ljava/lang/String;)V" ,Java_Document_setCurrentDocumentation},
   {"n_getCurrentDocumentation",  "()Ljava/lang/String;"  ,Java_Document_getCurrentDocumentation}
};


JNINativeMethod plugin_methods[] = 
{
   {"n_registerPlugin",  "(Ljava/lang/String;)V"                     ,Java_PluginManager_registerPlugin},
   {"n_registerTool",    "(Ljava/lang/String;Ljava/lang/String;)V"   ,Java_PluginManager_registerTool},
   {"n_registerDialog",  "(Ljava/lang/String;Ljava/lang/String;)V"   ,Java_PluginManager_registerDialog}
};


JNINativeMethod objectPlugin_methods[] = 
{
   {"n_invertInput",      "(IZ)V"                 ,Java_ObjectPlugin_invertInput},
   {"n_invertOutput",     "(IZ)V"                 ,Java_ObjectPlugin_invertOutput},
   {"n_isObjectNameFree", "(Ljava/lang/String;)Z" ,Java_ObjectPlugin_isObjectNameFree}
};


jclass  JavaPluginManager::m_documentClass;
jclass  JavaPluginManager::m_configurationClass;
jclass  JavaPluginManager::m_painterClass;
jclass  JavaPluginManager::m_traceClass;
jclass  JavaPluginManager::m_pluginManagerClass;
jclass  JavaPluginManager::m_objectPluginClass;
bool    JavaPluginManager::m_isOk;

std::vector<CDynamicMenuExtension*> JavaPluginManager::m_toolMap;
std::vector<CDynamicMenuExtension*> JavaPluginManager::m_dialogMap;

#define _countof(array) (sizeof(array)/sizeof(array[0]))
// alles auspacken was in dem Archive vorhanden ist
//
void expandTool(CString fileName)
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];

   _splitpath( (LPCSTR)fileName, drive, dir, fname, ext );
   CZipArchive zip;
   zip.Open(fileName);
   try
   {
	   for(int i=0; i<zip.GetNoEntries();i++)
	   {
		   zip.ExtractFile(i,PLUGIN_PATH(""));
	   }
   }
   catch(...)
   {
   }
   zip.Close();
}
// alles auspacken was in dem Archive vorhanden ist
//
void expandExport(CString fileName)
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];

   _splitpath( (LPCSTR)fileName, drive, dir, fname, ext );
   CZipArchive zip;
   zip.Open(fileName);
   try
   {
	   for(int i=0; i<zip.GetNoEntries();i++)
	   {
		   zip.ExtractFile(i,PLUGIN_PATH(""));
	   }
   }
   catch(...)
   {
   }
   zip.Close();
}
// alles auspacken was in dem Archive vorhanden ist
//
void expandDialog(CString fileName)
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];

   _splitpath( (LPCSTR)fileName, drive, dir, fname, ext );
   CZipArchive zip;
   zip.Open(fileName);
   try
   {
	   for(int i=0; i<zip.GetNoEntries();i++)
	   {
		   zip.ExtractFile(i,PLUGIN_PATH(""));
	   }
   }
   catch(...)
   {
   }
   zip.Close();
}

// alles auspacken was mit .jar endet
//
void expandObject(CString fileName)
{
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];

   _splitpath( (LPCSTR)fileName, drive, dir, fname, ext );
   CZipArchive zip;
   zip.Open(fileName);
   try
   {
	   for(int i=0; i<zip.GetNoEntries();i++)
	   {
		   CFileHeader fileInfo;
		   if(zip.GetFileInfo(fileInfo,i) && fileInfo.m_szFileName.Find(".jar")>0)
			zip.ExtractFile(i,PLUGIN_PATH(""));
	   }
   }
   catch(...)
   {
   }
   zip.Close();
}

//----------------------------------------------------------------------------
void JavaPluginManager::init()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

	// extract the *.bsh_jar plugins in the same directory
	//
	struct _finddata_t c_file;
	long hFile;

	CString     palettePath=PLUGIN_PATH("");

	// Find *.tool files in current directory and extraced them
	//
	if( (hFile = _findfirst( (palettePath+"*.tool"), &c_file )) == -1L ){
	  //
	  // keine Plugins vorhanden
	  //
	 LM::log(LM::info,"no plugins (bsh_jar) in '%s' found",(LPCSTR)palettePath);
	}
	else {
	   LM::log(LM::info,"plugin (bsh_jar) '%s' found.",(palettePath+c_file.name));
	   expandTool(palettePath+c_file.name);

	 // Find the rest of the files 
	 while( _findnext( hFile, &c_file ) == 0 ){
	   LM::log(LM::info,"plugin (bsh_jar) '%s' found.",(palettePath+c_file.name));
	   expandTool(palettePath+c_file.name);
	 }

	 _findclose( hFile );
	}

	// Find *.export files in current directory and extraced them
	//
	if( (hFile = _findfirst( (palettePath+"*.export"), &c_file )) == -1L ){
	  //
	  // keine Plugins vorhanden
	  //
	 LM::log(LM::info,"no plugins (export) in '%s' found",(LPCSTR)palettePath);
	}
	else {
	   LM::log(LM::info,"plugin (export) '%s' found.",(palettePath+c_file.name));
	   expandTool(palettePath+c_file.name);

	 // Find the rest of the files 
	 while( _findnext( hFile, &c_file ) == 0 ){
	   LM::log(LM::info,"plugin (export) '%s' found.",(palettePath+c_file.name));
	   expandExport(palettePath+c_file.name);
	 }

	 _findclose( hFile );
	}

	// Find *.dialog files in current directory and extraced them
	//
	if( (hFile = _findfirst( (palettePath+"*.dialog"), &c_file )) == -1L ){
	  //
	  // keine Plugins vorhanden
	  //
	 LM::log(LM::info,"no plugins (dialog) in '%s' found",(LPCSTR)palettePath);
	}
	else {
	   LM::log(LM::info,"plugin (dialog) '%s' found.",(palettePath+c_file.name));
	   expandTool(palettePath+c_file.name);

	 // Find the rest of the files 
	 while( _findnext( hFile, &c_file ) == 0 ){
	   LM::log(LM::info,"plugin (dialog) '%s' found.",(palettePath+c_file.name));
	   expandDialog(palettePath+c_file.name);
	 }

	 _findclose( hFile );
	}


	// Find *.object files in current directory and extraced them
	//
	if( (hFile = _findfirst( (palettePath+"*.object"), &c_file )) == -1L ){
	  //
	  // keine Plugins vorhanden
	  //
	 LM::log(LM::info,"no plugins (bsh_jar) in '%s' found",(LPCSTR)palettePath);
	}
	else {
	   LM::log(LM::info,"plugin (bsh_jar) '%s' found.",(palettePath+c_file.name));
	   expandObject(palettePath+c_file.name);

	 // Find the rest of the files 
	 while( _findnext( hFile, &c_file ) == 0 ){
	   LM::log(LM::info,"plugin (bsh_jar) '%s' found.",(palettePath+c_file.name));
	   expandObject(palettePath+c_file.name);
	 }

	 _findclose( hFile );
	}
	
   // combine my classpath with system's
   //
   CString  pluginPath = GET_PARAMETER("JavaPluginPath");
   CString  appPath    = GET_PARAMETER("ApplicationPath");
   CString 	classPath = pluginPath;
   
   appPath.TrimRight('\\');

   // setting the class path
   registerJarsInDirectory(pluginPath);
   registerJarsInDirectory(appPath +"\\jars\\");

   m_isOk = false;

   // select and load the JVM
   //
   if(selectJVMLibrary())
   {
      // Native Wrapper laden
      //
      registerPainter();
      registerTrace();
      registerConfiguration();
      registerPluginManager();
      registerObjectPlugin();
      registerDocument();

      m_isOk = true;
   }
}

//----------------------------------------------------------------------------
void JavaPluginManager::registerPlugin(CString className){
//----------------------------------------------------------------------------
	PROC_TRACE;

   LM::log(LM::info,"loading object plugin '%s'",(LPCSTR)className);
   new CElectricNodeContextJavaWrapper((char*)(LPCSTR)className);
}

//----------------------------------------------------------------------------
void JavaPluginManager::registerTool(CString menuEntry, CString id){
//----------------------------------------------------------------------------
	PROC_TRACE;

//	m_toolMap[id]= new CDynamicMenuExtension(menuEntry,id);
	m_toolMap.push_back(new CDynamicMenuExtension(menuEntry,id));

    LM::log(LM::info,"loading tool plugin '%s'",(LPCSTR)menuEntry);
}

//----------------------------------------------------------------------------
void JavaPluginManager::registerDialog(CString menuEntry, CString id){
//----------------------------------------------------------------------------
	PROC_TRACE;

// 	m_dialogMap[id]= new CDynamicMenuExtension(menuEntry,id);
 	m_dialogMap.push_back( new CDynamicMenuExtension(menuEntry,id));

    LM::log(LM::info,"loading dialog plugin '%s'",(LPCSTR)menuEntry);
}


//----------------------------------------------------------------------------
std::vector<CDynamicMenuExtension*> JavaPluginManager::getTools(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   /*
	std::vector<CDynamicMenuExtension*> toolSet;
	std::map<CString, CDynamicMenuExtension*>::iterator theIterator;
	theIterator = m_toolMap.begin();
	while(theIterator != m_toolMap.end()){
		CString      id   = (*theIterator).first;
		CDynamicMenuExtension* tool = (*theIterator).second;
		toolSet.push_back(tool);
		theIterator++;
	}
	return toolSet;
   */
   return m_toolMap;
}


//----------------------------------------------------------------------------
std::vector<CDynamicMenuExtension*> JavaPluginManager::getDialogs(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   /*
	std::vector<CDynamicMenuExtension*> dialogSet;
	std::map<CString, CDynamicMenuExtension*>::iterator theIterator;
	theIterator = m_dialogMap.begin();
	while(theIterator != m_dialogMap.end()){
		CString      id   = (*theIterator).first;
		CDynamicMenuExtension* tool = (*theIterator).second;
		dialogSet.push_back(tool);
		theIterator++;
	}
	return dialogSet;
   */
   return m_dialogMap;
}


//----------------------------------------------------------------------------
void JavaPluginManager::registerJarsInDirectory(CString directory)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   struct _finddata_t c_file;
   long hFile;


   // append all jars in the plugin directory to the class path
   //
   if( (hFile = _findfirst( (directory+"*.jar"), &c_file )) == -1L )
   {
      // no jars in this directory
   }
   else 
   {
      LM::log(LM::info,"add to class path :'%s'",(LPCSTR)(directory+c_file.name));
      JVM::appendClassPath((LPCSTR)(directory+c_file.name));
      /* Find the rest of the jars */
      while( _findnext( hFile, &c_file ) == 0 )
      {
         LM::log(LM::info,"add to class path :'%s'",(LPCSTR)(directory+c_file.name));
         JVM::appendClassPath((LPCSTR)(directory+c_file.name));
      }

      _findclose( hFile );
   }
}

//----------------------------------------------------------------------------
bool JavaPluginManager::selectJVMLibrary()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

	// try to load the JVM form the install package
	//
	LogManager::log(LogManager::info,"try to load JVM from the DigitalSimulator directory...");
	try
	{
		// Load the dedicated JavaVirtualMachine into system
		//
		CString jvm = JRE_PATH("bin\\classic\\jvm.dll");
		JVM::load((LPCSTR)jvm);

		if(JNIEnvHelper::getEnv()!=NULL)
			return true;
	}
	catch(...)
	{
		LogManager::log(LogManager::info,"no JDK installed from the DigitalSimulator setup. Searching JDK in windows registry");
	}


	// try to load the JVM from the registry information
	//
	LogManager::log(LogManager::info,"try to load JVM from the windows registry  information...");
	try
	{
		// Load the dedicated JavaVirtualMachine into system
		//
		JVM::load();

		if(JNIEnvHelper::getEnv()!=NULL)
			return true;
	}
	catch(...)
	{
		LogManager::log(LogManager::info,"no JVM entry in the windows registry found.");
	}

 
	// load the last JVM or search a valid in the c:/ directory and sub directories
    //
	LogManager::log(LogManager::info,"searching in the c:\\ drive for a JVM installation");
	try
	{
      // check if a virtual machine was loaded before
      //
      CString jvm = GET_PARAMETER("JavaVirtualMachine");
      if(jvm !="")
      {
         // check if the machione already exist
         //
         //mode Value Checks File For 
         //00 Existence only 
         //02  Write permission 
         //04 Read permission 
         //06 Read and write permission 
         if(_access((LPCSTR)jvm,00) == -1)
         {
            // jvm not already valid
            // 
            jvm = "";
         }
      }

      // try to find a valid jvm
      //
      if(jvm=="")
      {
         CFindFileDlg dlg;

         dlg.m_csRootFolder           = "C:\\";    // root folder of search
         dlg.m_csFindFile             = "jvm.dll"; // file to search for
         dlg.m_bRecurse               = true;      // search subfolders
         dlg.m_bFindSingleFile        = false;     // find multiple files
         dlg.m_bSearchNetworkDrives   = false;     // ignore network drives
         dlg.m_bSearchRemovableDrives = false;     // ignore removable drives
         dlg.m_bSearchCDROMDrives     = false;     // ignore CD-ROM drives
         dlg.m_csTitle                = "searching for Java Virtual Machine...";

         // do it. 
         int nResponse = dlg.DoModal();

         // done
         if (nResponse == IDOK)
         {
             CDialogSelectJVM jvmDlg;
          
             int size = dlg.m_csaFoundFiles.GetSize();
             while(size--)
             {
                TRACE("%s\n",(LPCSTR)dlg.m_csaFoundFiles.ElementAt(size));
                jvmDlg.m_jvms.Add((LPCSTR)dlg.m_csaFoundFiles.ElementAt(size));
             }

             if(jvmDlg.DoModal()==IDOK)
             {
                jvm =jvmDlg.m_jvm;
                SET_PARAMETER("JavaVirtualMachine",jvm);
             }
             else
             {
               // it makes no sense, that the DigitalSimulator-JavaExtended works without
               // a valid JVM. Use the the DigitalSimulator-StandartEdition instead!!!
               AfxMessageBox("You must select a JavaVirtualMachine Version 1.3. \r\nInstall the \"Java Runtime Enviroment 1.3\" from www.javasoft.com!!",MB_ICONSTOP );
               return false;
             }

         }
         else if (nResponse == IDCANCEL)
         {
            // it makes no sense, that the DigitalSimulator-JavaExtended works without
            // a valid JVM. Use the the DigitalSimulator-StandartEdition instead!!!
            AfxMessageBox("Can't load a JavaVirtualMachine Version 1.3. \r\nInstall the \"Java Runtime Enviroment 1.3\" from www.javasoft.com!!",MB_ICONSTOP );
            return false;
         }
      }

      try
      {
         // Load the dedicated JavaVirtualMachine into system
         //
         JVM::load((LPCSTR)jvm);
         if(JNIEnvHelper::getEnv()!=NULL)
            return true;
      }
      catch(...)
      {
      }
    }
	catch(...)
	{
	}

	SET_PARAMETER("JavaVirtualMachine","");
	AfxMessageBox("Can't load the selected JavaVirtualMachine. \r\nInstall the \"Java Runtime Enviroment 1.3\" from www.javasoft.com!!",MB_ICONSTOP );
	return false;
}


//----------------------------------------------------------------------------
void JavaPluginManager::registerPainter()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   // WindowsGDI-Wrapper laden und native methoden registrieren
   //
   LM::log(LM::info,"loading Windows-GDI wrapper 'Painter'");
   m_painterClass = (jclass)JNIEnvHelper::NewGlobalRef(JNIEnvHelper::FindClass("de/freegroup/digitalsimulator/Painter"));
   JNIEnvHelper::RegisterNatives(m_painterClass, painter_methods, _countof(painter_methods));
}

//----------------------------------------------------------------------------
void JavaPluginManager::registerConfiguration()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   // Configuration-Wrapper laden und native methoden registrieren
   //
   LM::log(LM::info,"loading application configuration wrapper 'Configuration'");
   m_configurationClass = (jclass)JNIEnvHelper::NewGlobalRef(JNIEnvHelper::FindClass("de/freegroup/digitalsimulator/Configuration"));
   if(JNIEnvHelper::ExceptionOccurred()!=NULL)
   {
	   JNIEnvHelper::ExceptionDescribe();
   }
   JNIEnvHelper::RegisterNatives(m_configurationClass, configuration_methods, _countof(configuration_methods));
}


//----------------------------------------------------------------------------
void JavaPluginManager::registerDocument()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   // Document-Wrapper laden und native methoden registrieren
   //
   LM::log(LM::info,"loading application document wrapper 'Document'");
   m_documentClass = (jclass)JNIEnvHelper::NewGlobalRef(JNIEnvHelper::FindClass("de/freegroup/digitalsimulator/Document"));
   if(JNIEnvHelper::ExceptionOccurred()!=NULL)
   {
	   JNIEnvHelper::ExceptionDescribe();
   }
   JNIEnvHelper::RegisterNatives(m_documentClass, document_methods, _countof(document_methods));
}


//----------------------------------------------------------------------------
void JavaPluginManager::registerTrace()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   // Trace laden und native methoden registrieren
   //
	LM::log(LM::info,"loading debug interface 'Trace'");
   m_traceClass = (jclass)JNIEnvHelper::NewGlobalRef(JNIEnvHelper::FindClass("de/freegroup/digitalsimulator/Trace"));
   JNIEnvHelper::RegisterNatives(m_traceClass, trace_methods, _countof(trace_methods));
}


//----------------------------------------------------------------------------
void JavaPluginManager::registerPluginManager()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   // Trace laden und native methoden registrieren
   //
	LM::log(LM::info,"loading plugin helper 'PluginManager'");
   m_pluginManagerClass = (jclass)JNIEnvHelper::NewGlobalRef(JNIEnvHelper::FindClass("de/freegroup/digitalsimulator/plugin/PluginManager"));
   jthrowable exc= JNIEnvHelper::ExceptionOccurred();
   if(exc!=NULL)
   {
	   JNIEnvHelper::ExceptionDescribe();
	   JNIEnvHelper::ExceptionClear();
   }
   JNIEnvHelper::RegisterNatives(m_pluginManagerClass, plugin_methods, _countof(plugin_methods));
}

//----------------------------------------------------------------------------
void JavaPluginManager::registerObjectPlugin()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   // Trace laden und native methoden registrieren
   //
	LM::log(LM::info,"loading native methods of 'ObjectPlugin'");
   m_objectPluginClass = (jclass)JNIEnvHelper::NewGlobalRef(JNIEnvHelper::FindClass("de/freegroup/digitalsimulator/plugin/object/ObjectPlugin"));
   JNIEnvHelper::RegisterNatives(m_objectPluginClass, objectPlugin_methods, _countof(objectPlugin_methods));
}

//----------------------------------------------------------------------------
void JavaPluginManager::clear()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

} 


#endif