#include "stdafx.h"
#include "JNI_Trace.h"
#include "Application\Objects\plugin\Java\JavaPluginManager.h"
#include "Application\JavaBinding\JNI_PluginManager.h"
#include "Application\Debug\LogManager.h"


/*
 * Class:     PluginManager
 * Method:    registerPlugin
 * Signature: (Ljava/lang/String;)V
 */
void JNICALL Java_PluginManager_registerPlugin  (JNIEnv *env, jclass, jstring jobj)
{
	PROC_TRACE;

	const char *str = env->GetStringUTFChars( (jstring)jobj, 0);
	try
	{
		JavaPluginManager::registerPlugin((char*)str);
	}
	catch(...)
	{
	}
	env->ReleaseStringUTFChars( (jstring)jobj, str);
}


/*
 * Class:     PluginManager
 * Method:    registerTool
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
void JNICALL Java_PluginManager_registerTool  (JNIEnv *env, jclass, jstring jmenu, jstring jclassName)
{
	PROC_TRACE;

	
	const char *menu      = env->GetStringUTFChars( (jstring)jmenu, 0);
	const char *className = env->GetStringUTFChars( (jstring)jclassName, 0);
	try
	{
		JavaPluginManager::registerTool((char*)menu,(char*)className);
	}
	catch(...)
	{
	}
	env->ReleaseStringUTFChars( (jstring)jmenu     , menu);
	env->ReleaseStringUTFChars( (jstring)jclassName, className);
}

/*
 * Class:     PluginManager
 * Method:    registerDialog
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
void JNICALL Java_PluginManager_registerDialog (JNIEnv *env, jclass, jstring jmenu, jstring jclassName)
{
	PROC_TRACE;

	
	const char *menu      = env->GetStringUTFChars( (jstring)jmenu, 0);
	const char *className = env->GetStringUTFChars( (jstring)jclassName, 0);
	try
	{
		JavaPluginManager::registerDialog((char*)menu,(char*)className);
	}
	catch(...)
	{
	}
	env->ReleaseStringUTFChars( (jstring)jmenu     , menu);
	env->ReleaseStringUTFChars( (jstring)jclassName, className);
}
