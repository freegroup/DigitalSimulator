#include "stdafx.h"
#include "JNI_Configuration.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Debug\LogManager.h"

/*
 * Class:     Trace
 * Method:    error
 * Signature: (Ljava/lang/String;)Ljava/lang/String
 */
jstring JNICALL Java_Configuration_getString(JNIEnv *env, jclass, jstring jobj)
{
	PROC_TRACE;

	const char *key = env->GetStringUTFChars( (jstring)jobj, 0);

   CString value = ParameterManager::Instance().Get(CString(key));

//   LogManager::log(LogManager::debug1 ,"Parameter '%s' from java-bindung requested",key);
	env->ReleaseStringUTFChars( (jstring)jobj, key);

   return env->NewStringUTF((LPCSTR)value);
}


void JNICALL Java_Configuration_setString(JNIEnv *env, jclass, jstring jkey, jstring jvalue)
{
	PROC_TRACE;

	const char *key   = env->GetStringUTFChars( (jstring)jkey, 0);
	const char *value = env->GetStringUTFChars( (jstring)jvalue, 0);

   ParameterManager::Instance().Set(CString(key), CString(value));

//   LogManager::log(LogManager::debug1 ,"set Parameter '%s' to '%s'",key, value);

   env->ReleaseStringUTFChars( (jstring)jvalue, value);
   env->ReleaseStringUTFChars( (jstring)jkey  , key);
}

