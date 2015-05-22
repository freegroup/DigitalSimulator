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

#include "stdafx.h"
#include "utils\global_defines.h"
#include "utils\DigitalTrainingStudio_version.h"
#include "ParameterManager.h"
#include "Application\Debug\LogManager.h"
#include "Application\Objects\plugin\java\JavaPluginManager.h"


#define PARAM_STORE_FILE "ParamStore.dat"
#include "JNIEnvHelper.h"


using namespace de::freegroup::jnipp;

extern CString int2string(int i);

std::string ParameterManager::className = "de/freegroup/digitalsimulator/Configuration";
jclass ParameterManager::objectClass = NULL;

//----------------------------------------------------------------------------
ParameterManager& ParameterManager::Instance(){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   static ParameterManager* m =new ParameterManager;

   if(objectClass==NULL &&  JavaPluginManager::isOk())
   {
 	   JNIStack jniStack;
	   objectClass = static_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( className.c_str() ) ) );
   }
   return *m;
}



//----------------------------------------------------------------------------
ParameterManager::ParameterManager(){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   char lpFilename[500];
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];


   Load();

   GetModuleFileName( GetModuleHandle(NULL),(char*) lpFilename, (DWORD)sizeof(lpFilename));
   _splitpath( (const char*)lpFilename, drive, dir, fname, ext );
   CString applicationPath = CString(drive) + dir;
   Set("ApplicationPath",applicationPath);

   // Init the path for the object icons
   //
   Set("WMFPath",applicationPath + "WMF\\");

   // Init the path for the script object bitmaps
   //
   Set("BMPPath",applicationPath + "BMP\\");

   // Init the path for the palettes
   //
   Set("PalettePath",applicationPath +"palettes\\");

   // Init the path for the string language catalog
   //
   Set("LanguagePath",applicationPath + "langCatalog\\");

   // Init the path for the plugin
   //
   Set("PluginPath",applicationPath + "plugins\\");

   // Init the path for the flags
   //
   Set("BannerPath",applicationPath + "banner\\");

   // Init the path for the logfiles
   //
   Set("LoggingPath",applicationPath + "logging\\");

   // Init the path for the basic circurits
   //
   Set("BasicPath",applicationPath + "basics\\");

   // Init the path for the scripts
   //
   Set("ScriptPath",applicationPath + "scripts\\");

   // Init the path for the plugins
   //
   Set("JavaPluginPath",applicationPath + "plugins\\");

   // Init the path for the plugins
   //
   Set("TempPath",applicationPath + "temp\\");

   // init the path for the JavaRuntime
   //
   Set("JREPath",applicationPath + "jdk\\jre\\");

   // init the path for the JavaRuntime
   //
   Set("JAVA_HOME",applicationPath + "jdk\\");

   // init the path for the java look&feel packages
   //
   Set("ThemesPath",applicationPath + "themes\\");

   putenv(CString("JAVA_HOME=")+Get("JAVA_HOME"));
   CString path= getenv("PATH");
   putenv(CString("PATH=")+path+";\""+Get("JAVA_HOME")+"\\bin\\\"");
   CString a= getenv("PATH");

   // Set the actuall build number in the property file. The java plugins
   // can now read the buildId. This is userfull for the LiveUpdate tool
   //
   Set("ApplicationBuildNumber",int2string(BUILD_NUM));
   Set("ApplicationVersion",PROGRAM_VERSION);
//   TRACE(path);
//   TRACE(a);
 
}


//----------------------------------------------------------------------------
ParameterManager::~ParameterManager(){
//----------------------------------------------------------------------------
//	PROC_TRACE;

}

//----------------------------------------------------------------------------
void ParameterManager::Load(){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   char lpFilename[500];
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];
   GetModuleFileName( GetModuleHandle(NULL),(char*) lpFilename, (DWORD)sizeof(lpFilename));
   _splitpath( (const char*)lpFilename, drive, dir, fname, ext );
   CString paramFile = CString(drive) + dir + "\\" + PARAM_STORE_FILE;

   std::string  valueName;
	std::string  value;
	std::ifstream inFile(paramFile);

	if(inFile.is_open()==true)	{
		while(!inFile.eof()){
			std::getline(inFile ,valueName,'\n');
			std::getline(inFile ,value,'\n');
			Set(valueName.c_str(),value.c_str());
		}
	}
	else{
		CString msg = CString("Parameterdatei [") + PARAM_STORE_FILE + "] nicht gefunden";
		AfxMessageBox(msg);
	}
}



//----------------------------------------------------------------------------
void ParameterManager::Save(){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   std::ofstream outFile(APPLICATION_PATH(PARAM_STORE_FILE));

   if(outFile.is_open()){
      ParamMap::iterator theIterator;

  	   theIterator = m_paramMap.begin();
      while(theIterator != m_paramMap.end()){
         outFile <<(LPCSTR)((*theIterator).first) << std::endl;
         outFile <<(LPCSTR)((*theIterator).second) << std::endl;
         theIterator++;
      }
   }
}


//----------------------------------------------------------------------------
void ParameterManager::RegisterForChange( ValueChangeNotifyee* callback){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   m_callbackObjects.insert(callback);
}


//----------------------------------------------------------------------------
void ParameterManager::UnregisterForChange(ValueChangeNotifyee* callback){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   int i= m_callbackObjects.erase(callback);
   if(i !=1 ){
      // ein Object welches sich nicht registriert hat will sich loeschen
      AfxMessageBox("Error during erase callback");
   }
   else{
   }
}

//----------------------------------------------------------------------------
CString ParameterManager::Get(const CString &valueName){
//----------------------------------------------------------------------------
//	PROC_TRACE;

  	return m_paramMap[valueName];
}

//----------------------------------------------------------------------------
void ParameterManager::Set(const CString& valueName,const  CString& value){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   if(valueName != ""){
      BeforeChange(valueName,value);
  	   m_paramMap[valueName]=value;
      DuringChange(valueName, value);
      AfterChange(valueName, value);
//      Save();
   }
}

//----------------------------------------------------------------------------
void ParameterManager::BeforeChange(const CString& valueName, const CString& value){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   NotifyeeCollection::iterator theIterator;

  	theIterator = m_callbackObjects.begin();
   while(theIterator != m_callbackObjects.end()){
      if((*theIterator)->m_valueNameForNotifyee==valueName)
         (*theIterator)->BeforeChange(value);
      theIterator++;
   }

   // notify the Java part for the changes
   //
   if(objectClass!=NULL &&  JavaPluginManager::isOk()){
	   JNIStack jniStack;
      de::freegroup::jnipp::JStringHelper p0 = valueName;
      de::freegroup::jnipp::JStringHelper p1 = value;
	   jmethodID mid = JNIEnvHelper::GetStaticMethodID( objectClass, "onBeforeChange", "(Ljava/lang/String;Ljava/lang/String;)V" );
	   JNIEnvHelper::CallStaticVoidMethod( objectClass, mid, static_cast<jobject>(p0),static_cast<jobject>(p1) );
   }
}

//----------------------------------------------------------------------------
void ParameterManager::DuringChange(const CString& valueName, const CString& value){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   NotifyeeCollection::iterator theIterator;

  	theIterator = m_callbackObjects.begin();
   while(theIterator != m_callbackObjects.end()){
      if((*theIterator)->m_valueNameForNotifyee==valueName)
         (*theIterator)->DuringChange(value);
      theIterator++;
   }
   // notify the Java part for the changes
   //
   if(objectClass!=NULL &&  JavaPluginManager::isOk()){
	   JNIStack jniStack;
      de::freegroup::jnipp::JStringHelper p0 = valueName;
      de::freegroup::jnipp::JStringHelper p1 = value;
	   jmethodID mid = JNIEnvHelper::GetStaticMethodID( objectClass, "onDuringChange", "(Ljava/lang/String;Ljava/lang/String;)V" );
	   JNIEnvHelper::CallStaticVoidMethod( objectClass, mid, static_cast<jobject>(p0),static_cast<jobject>(p1) );
   }
}

//----------------------------------------------------------------------------
void ParameterManager::AfterChange(const CString& valueName, const CString& value){
//----------------------------------------------------------------------------
//	PROC_TRACE;

   NotifyeeCollection::iterator theIterator;

  	theIterator = m_callbackObjects.begin();
   while(theIterator != m_callbackObjects.end()){
      if((*theIterator)->m_valueNameForNotifyee==valueName)
         (*theIterator)->AfterChange(value);
      theIterator++;
   }
   // notify the Java part for the changes
   //
   if(objectClass!=NULL &&  JavaPluginManager::isOk()){
	   JNIStack jniStack;
      de::freegroup::jnipp::JStringHelper p0 = valueName;
      de::freegroup::jnipp::JStringHelper p1 = value;
	   jmethodID mid = JNIEnvHelper::GetStaticMethodID( objectClass, "onAfterChange", "(Ljava/lang/String;Ljava/lang/String;)V" );
	   JNIEnvHelper::CallStaticVoidMethod( objectClass, mid, static_cast<jobject>(p0),static_cast<jobject>(p1) );
   }
}


//----------------------------------------------------------------------------
void ValueChangeNotifyee::BeforeChange(const CString &value){
//----------------------------------------------------------------------------
//	PROC_TRACE;

}


//----------------------------------------------------------------------------
void ValueChangeNotifyee::DuringChange(const CString& value){
//----------------------------------------------------------------------------
//	PROC_TRACE;

}

//----------------------------------------------------------------------------
void ValueChangeNotifyee::AfterChange(const CString& value){
//----------------------------------------------------------------------------
//	PROC_TRACE;

}

