#include "stdafx.h"
#include "JNI_Trace.h"
#include "Application\Objects\plugin\Java\JavaPluginManager.h"
#include "Application\JavaBinding\JNI_ToolManager.h"
#include "Application\Debug\LogManager.h"


/*
 * Class:     ToolManager
 * Method:    register
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
void JNICALL Java_ToolManager_register(JNIEnv *env, jclass, jstring jmenu, jstring jclassName)
{
	PROC_TRACE;

	
	const char *menu      = env->GetStringUTFChars( (jstring)jmenu, 0);
	const char *className = env->GetStringUTFChars( (jstring)jclassName, 0);
	try
	{
		JavaToolManager::registerTool((char*)menu,(char*)className);
	}
	catch(...)
	{
	}
	env->ReleaseStringUTFChars( (jstring)jmenu     , menu);
	env->ReleaseStringUTFChars( (jstring)jclassName, className);
}
