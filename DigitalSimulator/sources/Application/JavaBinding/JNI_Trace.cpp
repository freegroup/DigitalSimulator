#include "stdafx.h"
#include "JNI_Trace.h"
#include "Application\Debug\LogManager.h"


/*
 * Class:     Trace
 * Method:    error
 * Signature: (Ljava/lang/String;)V
 */
void JNICALL Java_Trace_error  (JNIEnv *env, jclass, jstring jobj)
{
	PROC_TRACE;

	const char *str = env->GetStringUTFChars( (jstring)jobj, 0);
   LM::log(LM::error,(char*)str);
	env->ReleaseStringUTFChars( (jstring)jobj, str);
}

/*
 * Class:     Trace
 * Method:    warning
 * Signature: (Ljava/lang/String;)V
 */
void JNICALL Java_Trace_warning  (JNIEnv *env, jclass, jstring jobj)
{
	PROC_TRACE;

	const char *str = env->GetStringUTFChars( (jstring)jobj, 0);
   LM::log(LM::warning,(char*)str);
	env->ReleaseStringUTFChars( (jstring)jobj, str);
}

/*
 * Class:     Trace
 * Method:    info
 * Signature: (Ljava/lang/String;)V
 */
void JNICALL Java_Trace_info  (JNIEnv *env, jclass, jstring jobj)
{
	PROC_TRACE;

	const char *str = env->GetStringUTFChars( (jstring)jobj, 0);
   LM::log(LM::info,(char*)str);
	env->ReleaseStringUTFChars( (jstring)jobj, str);
}
