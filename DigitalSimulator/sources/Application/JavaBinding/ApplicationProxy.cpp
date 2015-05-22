#include "stdafx.h"
#include "ApplicationProxy.h"
#include "JNIEnvHelper.h"


using namespace de::freegroup::jnipp;


std::string ApplicationProxy::className = "de/freegroup/digitalsimulator/Application";
jclass ApplicationProxy::objectClass = NULL;

jclass ApplicationProxy::_getObjectClass()
{
	PROC_TRACE;

   if ( objectClass == NULL )
		objectClass = static_cast<jclass>( JNIEnvHelper::NewGlobalRef( JNIEnvHelper::FindClass( className.c_str() ) ) );

	return objectClass;
}

jclass ApplicationProxy::getObjectClass()
{
	PROC_TRACE;

	return _getObjectClass();
}

ApplicationProxy::operator jobject()
{
	PROC_TRACE;

	return peerObject;
}

// constructors
ApplicationProxy::ApplicationProxy(jobject obj)
{
	PROC_TRACE;

	peerObject = JNIEnvHelper::NewGlobalRef( obj );
}

ApplicationProxy::ApplicationProxy()
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetMethodID( getObjectClass(), "<init>", "()V" );
	peerObject = JNIEnvHelper::NewGlobalRef( JNIEnvHelper::NewObject( getObjectClass(), mid ) );
}

// attribute getters
// attribute setters
// methods
void ApplicationProxy::onInit()
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetStaticMethodID( _getObjectClass(), "onInit", "()V" );
	JNIEnvHelper::CallStaticVoidMethod( _getObjectClass(), mid );
}

void ApplicationProxy::onExit()
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetStaticMethodID( _getObjectClass(), "onExit", "()V" );
	JNIEnvHelper::CallStaticVoidMethod( _getObjectClass(), mid );
}

void ApplicationProxy::onHelpAbout()
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetStaticMethodID( _getObjectClass(), "onHelpAbout", "()V" );
	JNIEnvHelper::CallStaticVoidMethod( _getObjectClass(), mid );
}

void ApplicationProxy::onExport(de::freegroup::jnipp::JStringHelper& p0)
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetStaticMethodID( _getObjectClass(), "onExport", "(Ljava/lang/String;)V" );
	JNIEnvHelper::CallStaticVoidMethod( _getObjectClass(), mid, static_cast<jobject>( p0 ) );
}

void ApplicationProxy::onToolCall(de::freegroup::jnipp::JStringHelper& p0)
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetStaticMethodID( _getObjectClass(), "onToolCall", "(Ljava/lang/String;)V" );
	JNIEnvHelper::CallStaticVoidMethod( _getObjectClass(), mid, static_cast<jobject>( p0 ) );
}


void ApplicationProxy::onDialogCall(de::freegroup::jnipp::JStringHelper& p0)
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetStaticMethodID( _getObjectClass(), "onDialogCall", "(Ljava/lang/String;)V" );
	JNIEnvHelper::CallStaticVoidMethod( _getObjectClass(), mid, static_cast<jobject>( p0 ) );
}


void ApplicationProxy::setProxy(de::freegroup::jnipp::JStringHelper& p0, jint p1)
{
	PROC_TRACE;

	JNIStack jniStack;
	jmethodID mid = JNIEnvHelper::GetStaticMethodID( _getObjectClass(), "setProxy", "(Ljava/lang/String;I)V" );
	JNIEnvHelper::CallStaticVoidMethod( _getObjectClass(), mid, static_cast<jobject>( p0 ), p1 );
}

