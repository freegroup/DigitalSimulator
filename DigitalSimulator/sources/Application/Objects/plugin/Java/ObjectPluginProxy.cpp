#include "stdafx.h"
#include "ObjectPluginProxy.h"
#include "JNIEnvHelper.h"

#include "Application\Debug\LogManager.h"

using namespace de::freegroup::jnipp;


std::string ObjectPluginProxy::className = "de/freegroup/digitalsimulator/plugin/object/ObjectPlugin";
jclass ObjectPluginProxy::objectClass = NULL;

jclass ObjectPluginProxy::_getObjectClass()
{
	if ( objectClass == NULL )
		objectClass = static_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( className.c_str() ) ) );

	return objectClass;
}

jclass ObjectPluginProxy::getObjectClass()
{
	return _getObjectClass();
}

ObjectPluginProxy::operator jobject()
{
	return peerObject;
}

// constructors
ObjectPluginProxy::ObjectPluginProxy(jobject obj)
{
	peerObject = JNIEnvHelper::NewGlobalRef( obj );
}

ObjectPluginProxy::ObjectPluginProxy()
{
	PROC_TRACE;

}

// attribute getters
// attribute setters
// methods
de::freegroup::jnipp::JStringHelper ObjectPluginProxy::getName()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getName", "()Ljava/lang/String;" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

void ObjectPluginProxy::init(PrimitiveArray< jbyte >& p0)
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "init", "([B)V" );
	JNIEnvHelper::CallVoidMethod( getPeerObject(), mid, static_cast<jobject>( p0 ) );
}

void ObjectPluginProxy::init()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "init", "()V" );
	JNIEnvHelper::CallVoidMethod( getPeerObject(), mid );
}

de::freegroup::jnipp::JStringHelper ObjectPluginProxy::getKey()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getKey", "()Ljava/lang/String;" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

PrimitiveArray< jint > ObjectPluginProxy::getSize(jlong p0, jlong p1)
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getSize", "(JJ)[I" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid, p0, p1 );
}

jint ObjectPluginProxy::getVersion()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getVersion", "()I" );
	return JNIEnvHelper::CallIntMethod( getPeerObject(), mid );
}

jboolean ObjectPluginProxy::doConfigure(PrimitiveArray< jbyte >& p0)
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "doConfigure", "([B)Z" );
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid, static_cast<jobject>( p0 ) );
}

de::freegroup::jnipp::JStringHelper ObjectPluginProxy::getProgrammerName()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getProgrammerName", "()Ljava/lang/String;" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

de::freegroup::jnipp::JStringHelper ObjectPluginProxy::getProgrammerURL()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getProgrammerURL", "()Ljava/lang/String;" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

de::freegroup::jnipp::JStringHelper ObjectPluginProxy::getProgrammerMail()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getProgrammerMail", "()Ljava/lang/String;" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

de::freegroup::jnipp::JStringHelper ObjectPluginProxy::getLabel()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getLabel", "()Ljava/lang/String;" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

jint ObjectPluginProxy::getParamCount()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getParamCount", "()I" );
	return JNIEnvHelper::CallIntMethod( getPeerObject(), mid );
}

PrimitiveArray< jint > ObjectPluginProxy::getInputCountRange()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getInputCountRange", "()[I" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

PrimitiveArray< jint > ObjectPluginProxy::getOutputCountRange()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getOutputCountRange", "()[I" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

de::freegroup::jnipp::JStringHelper ObjectPluginProxy::getDescription()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getDescription", "()Ljava/lang/String;" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

de::freegroup::jnipp::JStringHelper ObjectPluginProxy::getGroup()
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "getGroup", "()Ljava/lang/String;" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid );
}

jboolean ObjectPluginProxy::calculate(PrimitiveArray< jint >& p0, PrimitiveArray< jint >& p1, PrimitiveArray< jint >& p2, PrimitiveArray< jbyte >& p3)
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "calculate", "([I[I[I[B)Z" );
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid, static_cast<jobject>( p0 ), static_cast<jobject>( p1 ), static_cast<jobject>( p2 ), static_cast<jobject>( p3 ) );
}

void ObjectPluginProxy::paint(jint p0, jint p1, PrimitiveArray< jbyte >& p2)
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "paint", "(II[B)V" );
	JNIEnvHelper::CallVoidMethod( getPeerObject(), mid, p0, p1, static_cast<jobject>( p2 ) );
}

void ObjectPluginProxy::onStartCalculate(PrimitiveArray< jbyte >& p0)
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onStartCalculate", "([B)V" );
	JNIEnvHelper::CallVoidMethod( getPeerObject(), mid, static_cast<jobject>( p0 ) );
}

void ObjectPluginProxy::onStopCalculate(PrimitiveArray< jbyte >& p0)
{
	PROC_TRACE;

	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onStopCalculate", "([B)V" );
	JNIEnvHelper::CallVoidMethod( getPeerObject(), mid, static_cast<jobject>( p0 ) );
}

jboolean ObjectPluginProxy::onButtonClick(jint p0, jint p1,PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onButtonClick", "(II[B)Z" );
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid,p0,p1, static_cast<jobject>( p2 )  );
}

jboolean ObjectPluginProxy::onButtonDblClick(jint p0, jint p1,PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onButtonDblClick", "(II[B)Z" );
   if(JNIEnvHelper::ExceptionOccurred()!=NULL)
   {
	   JNIEnvHelper::ExceptionDescribe();
   }
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid,p0,p1, static_cast<jobject>( p2 ) );
}

jboolean ObjectPluginProxy::onButtonDown(jint p0, jint p1,PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onButtonDown", "(II[B)Z" );
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid, p0,p1, static_cast<jobject>( p2 ) );
}

jboolean ObjectPluginProxy::onButtonUp(jint p0, jint p1,PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onButtonUp", "(II[B)Z" );
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid, p0,p1, static_cast<jobject>( p2 )  );
}

jboolean ObjectPluginProxy::onMouseOverStart(jint p0, jint p1,PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onMouseOverStart", "(II[B)Z" );
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid, p0,p1, static_cast<jobject>( p2 )  );
}

jboolean ObjectPluginProxy::onMouseOver(jint p0, jint p1,PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onMouseOver", "(II[B)Z" );
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid, p0,p1, static_cast<jobject>( p2 )  );
}

jboolean ObjectPluginProxy::onMouseOverEnd(jint p0, jint p1,PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "onMouseOverEnd", "(II[B)Z" );
	return JNIEnvHelper::CallBooleanMethod( getPeerObject(), mid, p0,p1, static_cast<jobject>( p2 )  );
}

PrimitiveArray< jint > ObjectPluginProxy::layoutOutput(jint p0, jint p1, PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "layoutOutput", "(II[B)[I" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid, p0, p1, static_cast<jobject>( p2 ) );
}

PrimitiveArray< jint > ObjectPluginProxy::layoutInput(jint p0, jint p1, PrimitiveArray< jbyte >& p2)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "layoutInput", "(II[B)[I" );
	return JNIEnvHelper::CallObjectMethod( getPeerObject(), mid, p0, p1, static_cast<jobject>( p2 ) );
}

void ObjectPluginProxy::invertInput(jint p0, jboolean p1)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "invertInput", "(IZ)V" );
	JNIEnvHelper::CallVoidMethod( getPeerObject(), mid, p0, p1 );
}

void ObjectPluginProxy::invertOutput(jint p0, jboolean p1)
{
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "invertOutput", "(IZ)V" );
	JNIEnvHelper::CallVoidMethod( getPeerObject(), mid, p0, p1 );
}

