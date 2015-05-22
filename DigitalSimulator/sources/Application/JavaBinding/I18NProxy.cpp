#include "stdafx.h"
#include "I18NProxy.h"
#include "JNIEnvHelper.h"


using namespace de::freegroup::jnipp;


std::string I18NProxy::className = "de/freegroup/digitalsimulator/I18N";
jclass I18NProxy::objectClass = NULL;

jclass I18NProxy::_getObjectClass()
{
	PROC_TRACE;

   if ( objectClass == NULL )
		objectClass = static_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( className.c_str() ) ) );

	return objectClass;
}

CString I18NProxy::get(CString p0)
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetStaticMethodID( _getObjectClass(), "get", "(Ljava/lang/String;)Ljava/lang/String;" );
   if(mid==NULL){
      return CString("");
   }
   de::freegroup::jnipp::JStringHelper data((LPCSTR)p0); 
	de::freegroup::jnipp::JStringHelper result = JNIEnvHelper::CallStaticObjectMethod( _getObjectClass(), mid, static_cast<jobject>( data ));

   return result;
}
