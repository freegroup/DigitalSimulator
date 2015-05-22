#ifdef WIN32
#include "stdafx.h"
#else
#include <dlfcn.h>
typedef void* HMODULE;
#endif
#include "JVM.h"
#include "JNIEnvHelper.h"
#include "InitializationException.h"
#include "Application\Configuration\ParameterManager.h"

using namespace de::freegroup::jnipp;

const char JVM::pathSeparator = ';';

JavaVM* JVM::javaVM = NULL;
std::string JVM::classPath;
std::map<std::string, std::string> JVM::defines;
std::vector<NativeMethodData*> JVM::natives;

//----------------------------------------------------------------------------
jint (JNICALL y_fprintf)(FILE*, const char *format, va_list args)
//----------------------------------------------------------------------------
{
   static char buffer[10000];
	vsprintf(buffer,format,args);
	// remove the \n at the end
	//
//	buffer[strlen(buffer)-1]='\0';
	TRACE(buffer);
	return (strlen(buffer));
}

void JVM::load()
{
	load( SUN_JRE );
}

void JVM::load(EnumInstalledJRE jre)
{
	std::string baseKey;

	if ( jre == SUN_JRE )
		baseKey = "SOFTWARE\\JavaSoft\\Java Runtime Environment";
	else
		baseKey = "SOFTWARE\\IBM\\Java2 Runtime Environment";

	HKEY hKey;
	long err = RegOpenKeyEx( HKEY_LOCAL_MACHINE, baseKey.c_str(), 0, KEY_READ, &hKey );
	if ( err != ERROR_SUCCESS )
		throw InitializationException();

	unsigned long len = 1024;
	char parameterValue[1024];
	err = RegQueryValueEx( hKey, "CurrentVersion", NULL, NULL, reinterpret_cast<unsigned char*>( parameterValue ), &len );
	RegCloseKey( hKey );
	if ( err != ERROR_SUCCESS )
		throw InitializationException();

	baseKey += "\\";
	baseKey += parameterValue;
	err = RegOpenKeyEx( HKEY_LOCAL_MACHINE, baseKey.c_str(), 0, KEY_READ, &hKey );
	if ( err != ERROR_SUCCESS )
		throw InitializationException();

	len = 1024;
	err = RegQueryValueEx( hKey, "RuntimeLib", NULL, NULL, reinterpret_cast<unsigned char*>( parameterValue ), &len );
	RegCloseKey( hKey );
	if ( err != ERROR_SUCCESS )
		throw InitializationException();

	load( parameterValue );
}

void JVM::load(const std::string& jvmLibraryPath)
{
	JavaVMInitArgs vmArgs;
	vmArgs.version = JNI_VERSION_1_2;

	HMODULE hModule = LoadLibrary( jvmLibraryPath.c_str() );
	if ( hModule == NULL )
		throw InitializationException();

	#ifdef WIN32
	jint (JNICALL *pJNI_GetDefaultJavaVMInitArgs)(void*) = (jint (JNICALL *)(void*)) GetProcAddress( hModule, "JNI_GetDefaultJavaVMInitArgs" );
	#else
	jint (JNICALL *pJNI_GetDefaultJavaVMInitArgs)(void*) = (jint (JNICALL *)(void*)) dlsym( hModule, "JNI_GetDefaultJavaVMInitArgs" );
	#endif
	if ( pJNI_GetDefaultJavaVMInitArgs == NULL )
		throw InitializationException();

	jint res = pJNI_GetDefaultJavaVMInitArgs( reinterpret_cast<void*>( &vmArgs ) );

	bool showJVMMessages = GET_PARAMETER("showJVMMessages").CompareNoCase("true")==0;

	int numOptions = defines.size() + showJVMMessages?3:2;	// add 3 for the classpath, tracing and verbose
	JavaVMOption* options = new JavaVMOption[numOptions];
	std::map<std::string, std::string>::iterator it = defines.begin();

	// set the classpath
	std::string* optionStrings = new std::string[numOptions];
	if ( classPath == "" )
		classPath = getenv( "CLASSPATH" );
	optionStrings[0] = ("-Djava.class.path=" + classPath).c_str();
	options[0].optionString = const_cast<char *>( optionStrings[0].c_str() );

   optionStrings[1] = "-verbose:class,jni";
	options[1].optionString ="-verbose:class,jni";

	if(showJVMMessages)
	{
		optionStrings[2] = "vfprintf";
		options[2].optionString ="vfprintf";
		options[2].extraInfo    = y_fprintf;
	}

	// set the defines
	for ( int i = showJVMMessages?3:2; it != defines.end(); ++it, ++i )
	{
		optionStrings[i] = ("-D" + it->first + "=" + it->second).c_str();
		options[i].optionString = const_cast<char *>( optionStrings[i].c_str() );
	}

	vmArgs.options   = options;
	vmArgs.nOptions  = numOptions;

	JNIEnv* jniEnv = NULL;

	#ifdef WIN32
	jint (JNICALL *pJNI_CreateJavaVM)(JavaVM**, void**, void*) = (jint (JNICALL *)(JavaVM**, void**, void*)) GetProcAddress( hModule, "JNI_CreateJavaVM" );
	#else
	jint (JNICALL *pJNI_CreateJavaVM)(JavaVM**, void**, void*) = (jint (JNICALL *)(JavaVM**, void**, void*)) dlsym( hModule, "JNI_CreateJavaVM" );
	#endif
	if ( pJNI_CreateJavaVM == NULL )
		throw InitializationException();

	res = pJNI_CreateJavaVM( &javaVM, reinterpret_cast<void**>( &jniEnv ), &vmArgs );
	JNIEnvHelper::init( jniEnv );

	std::vector<NativeMethodData*>::iterator it2 = natives.begin();
	for ( ; it2 != natives.end(); ++it2 )
	{
		jclass cls = reinterpret_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( (*it2)->className.c_str() ) ) );
		JNIEnvHelper::RegisterNatives( cls, (*it2)->methods, (*it2)->numMethods );
		JNIEnvHelper::DeleteGlobalRef( reinterpret_cast<jobject>(cls) );
	}

	delete[] optionStrings;
}

void JVM::unload()
{
	JNIEnvHelper::uninit();
	javaVM->DestroyJavaVM();
	std::vector<NativeMethodData*>::iterator it = natives.begin();
	for ( ; it != natives.end(); ++it )
		delete *it;
}

void JVM::appendClassPath(const std::string& classPath)
{
	if ( JVM::classPath == "" )
   {
      if(getenv( "CLASSPATH" )!=NULL)
      {
		   JVM::classPath = getenv( "CLASSPATH" );
      }
      else
         JVM::classPath="";
   }

   if(JVM::classPath.length()!=0)
      JVM::classPath += pathSeparator;
	JVM::classPath += classPath;
}

void JVM::clearClassPath()
{
	classPath = "";
}

void JVM::addDefine(const std::string& key, const std::string& value)
{
	defines.insert( std::pair<std::string, std::string>( key, value ) );
}

void JVM::clearDefines()
{
	defines.clear();
}

jint JVM::attachCurrentThread()
{
	JNIEnv* jniEnv = NULL;
	jint retVal = javaVM->AttachCurrentThread( reinterpret_cast<void**>( &jniEnv ), NULL );
	JNIEnvHelper::init( jniEnv );
	return retVal;
}

jint JVM::detachCurrentThread()
{
	JNIEnvHelper::uninit();
	return javaVM->DetachCurrentThread();
}

void JVM::registerNatives(const std::string& className, JNINativeMethod nativeMethods[], int numMethods)
{
	natives.push_back( new NativeMethodData( className, nativeMethods, numMethods ) );
}
