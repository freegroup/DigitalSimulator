#include "stdafx.h"
#include "libraries/JNI/JVM.h"
#include "JNIEnvHelper.h"
#include "EnvironmentNotInitializedException.h"
#include "EnvironmentAlreadyInitializedException.h"
#include "JStringHelper.h"
#include "JVMException.h"
#include "Application\Debug\LogManager.h"

using namespace de::freegroup::jnipp;


std::map<pthread_t, JNIEnv*> JNIEnvHelper::interfaceMap;

void JNIEnvHelper::init(JNIEnv* jniEnv)
{
	pthread_t threadID = ::GetCurrentThreadId();
	std::map<pthread_t, JNIEnv*>::iterator it = interfaceMap.find( threadID );
	if ( it != interfaceMap.end() )
		throw EnvironmentAlreadyInitializedException();

	interfaceMap.insert( std::pair<pthread_t, JNIEnv*>( threadID, jniEnv ) );
}

void JNIEnvHelper::uninit()
{
	pthread_t threadID = ::GetCurrentThreadId();
	std::map<pthread_t, JNIEnv*>::iterator it = interfaceMap.find( threadID );
	if ( it != interfaceMap.end() )
		interfaceMap.erase( it );
}

JNIEnv* JNIEnvHelper::getEnv()
{
	pthread_t threadID = ::GetCurrentThreadId();

	std::map<pthread_t, JNIEnv*>::iterator it = interfaceMap.find( threadID );
	if ( it == interfaceMap.end() )
	{
		JVM::attachCurrentThread();
		it = interfaceMap.find( threadID );
		if ( it == interfaceMap.end() )
			throw EnvironmentNotInitializedException();
	}

	return it->second;
}

void JNIEnvHelper::exceptionCheck()
{
	if ( ExceptionCheck() == JNI_TRUE )
	{
		jthrowable exceptionObj = ExceptionOccurred();
		ExceptionClear();

		/*
		 * Get the class of the exception.
		 */
		jclass exceptionClass = JNIEnvHelper::GetObjectClass( exceptionObj );

		/*
		 * Get the method id of the getMessage() method.
		 */
		jmethodID mid = GetMethodID( exceptionClass, "getMessage", "()Ljava/lang/String;" );
		JStringHelper msg = CallStringMethod( exceptionObj, mid );

		std::string message = static_cast<const char*>(msg);
		throw JVMException( message );
	}
}

// wrapped methods
jint JNIEnvHelper::GetVersion()
{
	return getEnv()->GetVersion();
}

jclass JNIEnvHelper::DefineClass(const char *name, jobject loader, const jbyte *buf, jsize len)
{
	return getEnv()->DefineClass( name, loader, buf, len );
}

jclass JNIEnvHelper::FindClass(const char *name)
{
	return getEnv()->FindClass( name );
}

jmethodID JNIEnvHelper::FromReflectedMethod(jobject method)
{
	return getEnv()->FromReflectedMethod( method );
}

jfieldID JNIEnvHelper::FromReflectedField(jobject field)
{
	return getEnv()->FromReflectedField( field );
}

jobject JNIEnvHelper::ToReflectedMethod(jclass cls, jmethodID methodID, jboolean isStatic)
{
	return getEnv()->ToReflectedMethod( cls, methodID, isStatic );
}

jclass JNIEnvHelper::GetSuperclass(jclass sub)
{
	return getEnv()->GetSuperclass( sub );
}

jboolean JNIEnvHelper::IsAssignableFrom(jclass sub, jclass sup)
{
	return getEnv()->IsAssignableFrom( sub, sup );
}

jobject JNIEnvHelper::ToReflectedField(jclass cls, jfieldID fieldID, jboolean isStatic)
{
	return getEnv()->ToReflectedField( cls, fieldID, isStatic );
}

jint JNIEnvHelper::Throw(jthrowable obj)
{
	return getEnv()->Throw( obj );
}

jint JNIEnvHelper::ThrowNew(jclass clazz, const char *msg)
{
	return getEnv()->ThrowNew( clazz, msg );
}

jthrowable JNIEnvHelper::ExceptionOccurred()
{
	return getEnv()->ExceptionOccurred();
}

void JNIEnvHelper::ExceptionDescribe()
{
	getEnv()->ExceptionDescribe();
}

void JNIEnvHelper::ExceptionClear()
{
	getEnv()->ExceptionClear();
}

void JNIEnvHelper::FatalError(const char *msg)
{
	getEnv()->FatalError( msg );
}

jint JNIEnvHelper::PushLocalFrame(jint capacity)
{
	return getEnv()->PushLocalFrame( capacity );
}

jobject JNIEnvHelper::PopLocalFrame(jobject result)
{
	return getEnv()->PopLocalFrame( result );
}

jobject JNIEnvHelper::NewGlobalRef(jobject lobj)
{
	return getEnv()->NewGlobalRef( lobj );
}

void JNIEnvHelper::DeleteGlobalRef(jobject gref)
{
	try
	{
		getEnv()->DeleteGlobalRef( gref );
	}
	catch(EnvironmentNotInitializedException&)
	{
	}
}

void JNIEnvHelper::DeleteLocalRef(jobject obj)
{
	getEnv()->DeleteLocalRef( obj );
}

jboolean JNIEnvHelper::IsSameObject(jobject obj1, jobject obj2)
{
	return getEnv()->IsSameObject( obj1, obj2 );
}

jobject JNIEnvHelper::NewLocalRef(jobject ref)
{
	return getEnv()->NewLocalRef( ref );
}

jint JNIEnvHelper::EnsureLocalCapacity(jint capacity)
{
	return getEnv()->EnsureLocalCapacity( capacity );
}

jobject JNIEnvHelper::AllocObject(jclass clazz)
{
	return getEnv()->AllocObject( clazz );
}

jobject JNIEnvHelper::NewObject(jclass clazz, jmethodID methodID, ...)
{
	jobject result;
	va_list args;
	va_start( args, methodID );
	result = NewObjectV( clazz, methodID, args );
	va_end( args );
	return result;
}

jobject JNIEnvHelper::NewObjectV(jclass clazz, jmethodID methodID, va_list args)
{
	jobject result = getEnv()->NewObjectV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jobject JNIEnvHelper::NewObjectA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jobject result = getEnv()->NewObjectA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jclass JNIEnvHelper::GetObjectClass(jobject obj)
{
	return getEnv()->GetObjectClass( obj );
}

jboolean JNIEnvHelper::IsInstanceOf(jobject obj, jclass clazz)
{
	return getEnv()->IsInstanceOf( obj, clazz );
}

jmethodID JNIEnvHelper::GetMethodID(jclass clazz, const char *name, const char *sig)
{
	return getEnv()->GetMethodID( clazz, name, sig );
}

jobject JNIEnvHelper::CallObjectMethod(jobject obj, jmethodID methodID, ...)
{
	jobject result;
	va_list args;
	va_start( args, methodID );
	result = CallObjectMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jobject JNIEnvHelper::CallObjectMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jobject result = getEnv()->CallObjectMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jobject JNIEnvHelper::CallObjectMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jobject result = getEnv()->CallObjectMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

jboolean JNIEnvHelper::CallBooleanMethod(jobject obj, jmethodID methodID, ...)
{
	jboolean result;
	va_list args;
	va_start( args, methodID );
	result = CallBooleanMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jboolean JNIEnvHelper::CallBooleanMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jboolean result = getEnv()->CallBooleanMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jboolean JNIEnvHelper::CallBooleanMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jboolean result = getEnv()->CallBooleanMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

jbyte JNIEnvHelper::CallByteMethod(jobject obj, jmethodID methodID, ...)
{
	jbyte result;
	va_list args;
	va_start( args, methodID );
	result = CallByteMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jbyte JNIEnvHelper::CallByteMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jbyte result = getEnv()->CallByteMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jbyte JNIEnvHelper::CallByteMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jbyte result = getEnv()->CallByteMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

jchar JNIEnvHelper::CallCharMethod(jobject obj, jmethodID methodID, ...)
{
	jchar result;
	va_list args;
	va_start( args, methodID );
	result = CallCharMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jchar JNIEnvHelper::CallCharMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jchar result = getEnv()->CallCharMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jchar JNIEnvHelper::CallCharMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jchar result = getEnv()->CallCharMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

jshort JNIEnvHelper::CallShortMethod(jobject obj, jmethodID methodID, ...)
{
	jshort result;
	va_list args;
	va_start( args, methodID );
	result = CallShortMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jshort JNIEnvHelper::CallShortMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jshort result = getEnv()->CallShortMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jshort JNIEnvHelper::CallShortMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jshort result = getEnv()->CallShortMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

jint JNIEnvHelper::CallIntMethod(jobject obj, jmethodID methodID, ...)
{
	jint result;
	va_list args;
	va_start( args, methodID );
	result = CallIntMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jint JNIEnvHelper::CallIntMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jint result = getEnv()->CallIntMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jint JNIEnvHelper::CallIntMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jint result = getEnv()->CallIntMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

jlong JNIEnvHelper::CallLongMethod(jobject obj, jmethodID methodID, ...)
{
	jlong result;
	va_list args;
	va_start( args, methodID );
	result = CallLongMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jlong JNIEnvHelper::CallLongMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jlong result = getEnv()->CallLongMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jlong JNIEnvHelper::CallLongMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jlong result = getEnv()->CallLongMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

jfloat JNIEnvHelper::CallFloatMethod(jobject obj, jmethodID methodID, ...)
{
	jfloat result;
	va_list args;
	va_start( args, methodID );
	result = CallFloatMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jfloat JNIEnvHelper::CallFloatMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jfloat result = getEnv()->CallFloatMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jfloat JNIEnvHelper::CallFloatMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jfloat result = getEnv()->CallFloatMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

jdouble JNIEnvHelper::CallDoubleMethod(jobject obj, jmethodID methodID, ...)
{
	jdouble result;
	va_list args;
	va_start( args, methodID );
	result = CallDoubleMethodV( obj, methodID, args );
	va_end( args );
	return result;
}

jdouble JNIEnvHelper::CallDoubleMethodV(jobject obj, jmethodID methodID, va_list args)
{
	jdouble result = getEnv()->CallDoubleMethodV( obj, methodID, args );
	exceptionCheck();
	return result;
}

jdouble JNIEnvHelper::CallDoubleMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	jdouble result = getEnv()->CallDoubleMethodA( obj, methodID, args );
	exceptionCheck();
	return result;
}

void JNIEnvHelper::CallVoidMethod(jobject obj, jmethodID methodID, ...)
{
	va_list args;
	va_start( args, methodID );
	CallVoidMethodV( obj, methodID, args );
	va_end( args );
}

void JNIEnvHelper::CallVoidMethodV(jobject obj, jmethodID methodID, va_list args)
{
	getEnv()->CallVoidMethodV( obj, methodID, args );
	exceptionCheck();
}

void JNIEnvHelper::CallVoidMethodA(jobject obj, jmethodID methodID, jvalue* args)
{
	getEnv()->CallVoidMethodA( obj, methodID, args );
	exceptionCheck();
}

jobject JNIEnvHelper::CallNonvirtualObjectMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jobject result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualObjectMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jobject JNIEnvHelper::CallNonvirtualObjectMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	jobject result = getEnv()->CallNonvirtualObjectMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jobject JNIEnvHelper::CallNonvirtualObjectMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	jobject result = getEnv()->CallNonvirtualObjectMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jboolean JNIEnvHelper::CallNonvirtualBooleanMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jboolean result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualBooleanMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jboolean JNIEnvHelper::CallNonvirtualBooleanMethodV(jobject obj, jclass clazz,  jmethodID methodID, va_list args)
{
	jboolean result = getEnv()->CallNonvirtualBooleanMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jboolean JNIEnvHelper::CallNonvirtualBooleanMethodA(jobject obj, jclass clazz,  jmethodID methodID, jvalue* args)
{
	jboolean result = getEnv()->CallNonvirtualBooleanMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jbyte JNIEnvHelper::CallNonvirtualByteMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jbyte result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualByteMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jbyte JNIEnvHelper::CallNonvirtualByteMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	jbyte result = getEnv()->CallNonvirtualByteMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jbyte JNIEnvHelper::CallNonvirtualByteMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	jbyte result = getEnv()->CallNonvirtualByteMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jchar JNIEnvHelper::CallNonvirtualCharMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jchar result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualCharMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jchar JNIEnvHelper::CallNonvirtualCharMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	jchar result = getEnv()->CallNonvirtualCharMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jchar JNIEnvHelper::CallNonvirtualCharMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	jchar result = getEnv()->CallNonvirtualCharMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jshort JNIEnvHelper::CallNonvirtualShortMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jshort result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualShortMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jshort JNIEnvHelper::CallNonvirtualShortMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	jshort result = getEnv()->CallNonvirtualShortMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jshort JNIEnvHelper::CallNonvirtualShortMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	jshort result = getEnv()->CallNonvirtualShortMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jint JNIEnvHelper::CallNonvirtualIntMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jint result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualIntMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jint JNIEnvHelper::CallNonvirtualIntMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	jint result = getEnv()->CallNonvirtualIntMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jint JNIEnvHelper::CallNonvirtualIntMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	jint result = getEnv()->CallNonvirtualIntMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jlong JNIEnvHelper::CallNonvirtualLongMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jlong result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualLongMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jlong JNIEnvHelper::CallNonvirtualLongMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	jlong result = getEnv()->CallNonvirtualLongMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jlong JNIEnvHelper::CallNonvirtualLongMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	jlong result = getEnv()->CallNonvirtualLongMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jfloat JNIEnvHelper::CallNonvirtualFloatMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jfloat result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualFloatMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jfloat JNIEnvHelper::CallNonvirtualFloatMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	jfloat result = getEnv()->CallNonvirtualFloatMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jfloat JNIEnvHelper::CallNonvirtualFloatMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	jfloat result = getEnv()->CallNonvirtualFloatMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jdouble JNIEnvHelper::CallNonvirtualDoubleMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jdouble result;
	va_list args;
	va_start( args, methodID );
	result = CallNonvirtualDoubleMethodV( obj, clazz, methodID, args );
	va_end( args );
	return result;
}

jdouble JNIEnvHelper::CallNonvirtualDoubleMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	jdouble result = getEnv()->CallNonvirtualDoubleMethodV( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

jdouble JNIEnvHelper::CallNonvirtualDoubleMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	jdouble result = getEnv()->CallNonvirtualDoubleMethodA( obj, clazz, methodID, args );
	exceptionCheck();
	return result;
}

void JNIEnvHelper::CallNonvirtualVoidMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	va_list args;
	va_start( args, methodID );
	CallNonvirtualVoidMethodV( obj, clazz, methodID, args );
	va_end( args );
}

void JNIEnvHelper::CallNonvirtualVoidMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args)
{
	getEnv()->CallNonvirtualVoidMethodV( obj, clazz, methodID, args );
	exceptionCheck();
}

void JNIEnvHelper::CallNonvirtualVoidMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args)
{
	getEnv()->CallNonvirtualVoidMethodA( obj, clazz, methodID, args );
	exceptionCheck();
}

jfieldID JNIEnvHelper::GetFieldID(jclass clazz, const char *name, const char *sig)
{
	return getEnv()->GetFieldID( clazz, name, sig );
}

jobject JNIEnvHelper::GetObjectField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetObjectField( obj, fieldID );
}

jboolean JNIEnvHelper::GetBooleanField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetBooleanField( obj, fieldID );
}

jbyte JNIEnvHelper::GetByteField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetByteField( obj, fieldID );
}

jchar JNIEnvHelper::GetCharField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetCharField( obj, fieldID );
}

jshort JNIEnvHelper::GetShortField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetShortField( obj, fieldID );
}

jint JNIEnvHelper::GetIntField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetIntField( obj, fieldID );
}

jlong JNIEnvHelper::GetLongField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetLongField( obj, fieldID );
}

jfloat JNIEnvHelper::GetFloatField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetFloatField( obj, fieldID );
}

jdouble JNIEnvHelper::GetDoubleField(jobject obj, jfieldID fieldID)
{
	return getEnv()->GetDoubleField( obj, fieldID );
}

void JNIEnvHelper::SetObjectField(jobject obj, jfieldID fieldID, jobject val)
{
	getEnv()->SetObjectField( obj, fieldID, val );
}

void JNIEnvHelper::SetBooleanField(jobject obj, jfieldID fieldID, jboolean val)
{
	getEnv()->SetBooleanField( obj, fieldID, val );
}

void JNIEnvHelper::SetByteField(jobject obj, jfieldID fieldID, jbyte val)
{
	getEnv()->SetByteField( obj, fieldID, val );
}

void JNIEnvHelper::SetCharField(jobject obj, jfieldID fieldID, jchar val)
{
	getEnv()->SetCharField( obj, fieldID, val );
}

void JNIEnvHelper::SetShortField(jobject obj, jfieldID fieldID, jshort val)
{
	getEnv()->SetShortField( obj, fieldID, val );
}

void JNIEnvHelper::SetIntField(jobject obj, jfieldID fieldID, jint val)
{
	getEnv()->SetIntField( obj, fieldID, val );
}

void JNIEnvHelper::SetLongField(jobject obj, jfieldID fieldID, jlong val)
{
	getEnv()->SetLongField( obj, fieldID, val );
}

void JNIEnvHelper::SetFloatField(jobject obj, jfieldID fieldID, jfloat val)
{
	getEnv()->SetFloatField( obj, fieldID, val );
}

void JNIEnvHelper::SetDoubleField(jobject obj, jfieldID fieldID, jdouble val)
{
	getEnv()->SetDoubleField( obj, fieldID, val );
}

jmethodID JNIEnvHelper::GetStaticMethodID(jclass clazz, const char *name, const char *sig)
{
	return getEnv()->GetStaticMethodID( clazz, name, sig );
}

jobject JNIEnvHelper::CallStaticObjectMethod(jclass clazz, jmethodID methodID, ...)
{
	jobject result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticObjectMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jobject JNIEnvHelper::CallStaticObjectMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jobject result = getEnv()->CallStaticObjectMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jobject JNIEnvHelper::CallStaticObjectMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jobject result = getEnv()->CallStaticObjectMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jboolean JNIEnvHelper::CallStaticBooleanMethod(jclass clazz, jmethodID methodID, ...)
{
	jboolean result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticBooleanMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jboolean JNIEnvHelper::CallStaticBooleanMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jboolean result = getEnv()->CallStaticBooleanMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jboolean JNIEnvHelper::CallStaticBooleanMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jboolean result = getEnv()->CallStaticBooleanMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jbyte JNIEnvHelper::CallStaticByteMethod(jclass clazz, jmethodID methodID, ...)
{
	jbyte result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticByteMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jbyte JNIEnvHelper::CallStaticByteMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jbyte result = getEnv()->CallStaticByteMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jbyte JNIEnvHelper::CallStaticByteMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jbyte result = getEnv()->CallStaticByteMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jchar JNIEnvHelper::CallStaticCharMethod(jclass clazz, jmethodID methodID, ...)
{
	jchar result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticCharMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jchar JNIEnvHelper::CallStaticCharMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jchar result = getEnv()->CallStaticCharMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jchar JNIEnvHelper::CallStaticCharMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jchar result = getEnv()->CallStaticCharMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jshort JNIEnvHelper::CallStaticShortMethod(jclass clazz, jmethodID methodID, ...)
{
	jshort result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticShortMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jshort JNIEnvHelper::CallStaticShortMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jshort result = getEnv()->CallStaticShortMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jshort JNIEnvHelper::CallStaticShortMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jshort result = getEnv()->CallStaticShortMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jint JNIEnvHelper::CallStaticIntMethod(jclass clazz, jmethodID methodID, ...)
{
	jint result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticIntMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jint JNIEnvHelper::CallStaticIntMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jint result = getEnv()->CallStaticIntMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jint JNIEnvHelper::CallStaticIntMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jint result = getEnv()->CallStaticIntMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jlong JNIEnvHelper::CallStaticLongMethod(jclass clazz, jmethodID methodID, ...)
{
	jlong result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticLongMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jlong JNIEnvHelper::CallStaticLongMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jlong result = getEnv()->CallStaticLongMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jlong JNIEnvHelper::CallStaticLongMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jlong result = getEnv()->CallStaticLongMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jfloat JNIEnvHelper::CallStaticFloatMethod(jclass clazz, jmethodID methodID, ...)
{
	jfloat result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticFloatMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jfloat JNIEnvHelper::CallStaticFloatMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jfloat result = getEnv()->CallStaticFloatMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jfloat JNIEnvHelper::CallStaticFloatMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jfloat result = getEnv()->CallStaticFloatMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jdouble JNIEnvHelper::CallStaticDoubleMethod(jclass clazz, jmethodID methodID, ...)
{
	jdouble result;
	va_list args;
	va_start( args, methodID );
	result = CallStaticDoubleMethodV( clazz, methodID, args );
	va_end( args );
	return result;
}

jdouble JNIEnvHelper::CallStaticDoubleMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	jdouble result = getEnv()->CallStaticDoubleMethodV( clazz, methodID, args );
	exceptionCheck();
	return result;
}

jdouble JNIEnvHelper::CallStaticDoubleMethodA(jclass clazz, jmethodID methodID, jvalue *args)
{
	jdouble result = getEnv()->CallStaticDoubleMethodA( clazz, methodID, args );
	exceptionCheck();
	return result;
}

void JNIEnvHelper::CallStaticVoidMethod(jclass clazz, jmethodID methodID, ...)
{
	va_list args;
	va_start( args, methodID );
	CallStaticVoidMethodV( clazz, methodID, args );
	va_end( args );
}

void JNIEnvHelper::CallStaticVoidMethodV(jclass clazz, jmethodID methodID, va_list args)
{
	getEnv()->CallStaticVoidMethodV( clazz, methodID, args );
	exceptionCheck();
}

void JNIEnvHelper::CallStaticVoidMethodA(jclass clazz, jmethodID methodID, jvalue* args)
{
	getEnv()->CallStaticVoidMethodA( clazz, methodID, args );
	exceptionCheck();
}

jfieldID JNIEnvHelper::GetStaticFieldID(jclass clazz, const char *name, const char *sig)
{
	return getEnv()->GetStaticFieldID( clazz, name, sig );
}

jobject JNIEnvHelper::GetStaticObjectField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticObjectField( clazz, fieldID );
}

jboolean JNIEnvHelper::GetStaticBooleanField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticBooleanField( clazz, fieldID );
}

jbyte JNIEnvHelper::GetStaticByteField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticByteField( clazz, fieldID );
}

jchar JNIEnvHelper::GetStaticCharField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticCharField( clazz, fieldID );
}

jshort JNIEnvHelper::GetStaticShortField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticShortField( clazz, fieldID );
}

jint JNIEnvHelper::GetStaticIntField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticIntField( clazz, fieldID );
}

jlong JNIEnvHelper::GetStaticLongField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticLongField( clazz, fieldID );
}

jfloat JNIEnvHelper::GetStaticFloatField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticFloatField( clazz, fieldID );
}

jdouble JNIEnvHelper::GetStaticDoubleField(jclass clazz, jfieldID fieldID)
{
	return getEnv()->GetStaticDoubleField( clazz, fieldID );
}

void JNIEnvHelper::SetStaticObjectField(jclass clazz, jfieldID fieldID, jobject value)
{
	getEnv()->SetStaticObjectField( clazz, fieldID, value );
}

void JNIEnvHelper::SetStaticBooleanField(jclass clazz, jfieldID fieldID, jboolean value)
{
	getEnv()->SetStaticBooleanField( clazz, fieldID, value );
}

void JNIEnvHelper::SetStaticByteField(jclass clazz, jfieldID fieldID, jbyte value)
{
	getEnv()->SetStaticByteField( clazz, fieldID, value );
}

void JNIEnvHelper::SetStaticCharField(jclass clazz, jfieldID fieldID, jchar value)
{
	getEnv()->SetStaticCharField( clazz, fieldID, value );
}

void JNIEnvHelper::SetStaticShortField(jclass clazz, jfieldID fieldID, jshort value)
{
	getEnv()->SetStaticShortField( clazz, fieldID, value );
}

void JNIEnvHelper::SetStaticIntField(jclass clazz, jfieldID fieldID, jint value)
{
	getEnv()->SetStaticIntField( clazz, fieldID, value );
}

void JNIEnvHelper::SetStaticLongField(jclass clazz, jfieldID fieldID, jlong value)
{
	getEnv()->SetStaticLongField( clazz, fieldID, value );
}

void JNIEnvHelper::SetStaticFloatField(jclass clazz, jfieldID fieldID, jfloat value)
{
	getEnv()->SetStaticFloatField( clazz, fieldID, value );
}

void JNIEnvHelper::SetStaticDoubleField(jclass clazz, jfieldID fieldID, jdouble value)
{
	getEnv()->SetStaticDoubleField( clazz, fieldID, value );
}

jstring JNIEnvHelper::NewString(const jchar *unicode, jsize len)
{
	return getEnv()->NewString( unicode, len );
}

jsize JNIEnvHelper::GetStringLength(jstring str)
{
	return getEnv()->GetStringLength( str );
}

const jchar* JNIEnvHelper::GetStringChars(jstring str, jboolean *isCopy)
{
	return getEnv()->GetStringChars( str, isCopy );
}

void JNIEnvHelper::ReleaseStringChars(jstring str, const jchar *chars)
{
	getEnv()->ReleaseStringChars( str, chars );
}

jstring JNIEnvHelper::NewStringUTF(const char *utf)
{
	return getEnv()->NewStringUTF( utf );
}

jsize JNIEnvHelper::GetStringUTFLength(jstring str)
{
	return getEnv()->GetStringUTFLength( str );
}

const char* JNIEnvHelper::GetStringUTFChars(jstring str, jboolean *isCopy)
{
	return getEnv()->GetStringUTFChars( str, isCopy );
}

void JNIEnvHelper::ReleaseStringUTFChars(jstring str, const char* chars)
{
	getEnv()->ReleaseStringUTFChars( str, chars );
}

jsize JNIEnvHelper::GetArrayLength(jarray array)
{
	return getEnv()->GetArrayLength( array );
}

jobjectArray JNIEnvHelper::NewObjectArray(jsize len, jclass clazz, jobject init)
{
	jobjectArray result = getEnv()->NewObjectArray( len, clazz, init );
	exceptionCheck();
	return result;
}

jobject JNIEnvHelper::GetObjectArrayElement(jobjectArray array, jsize index)
{
	return getEnv()->GetObjectArrayElement( array, index );
}

void JNIEnvHelper::SetObjectArrayElement(jobjectArray array, jsize index, jobject val)
{
	getEnv()->SetObjectArrayElement( array, index, val );
}

jbooleanArray JNIEnvHelper::NewBooleanArray(jsize len)
{
	return getEnv()->NewBooleanArray( len );
}

jbyteArray JNIEnvHelper::NewByteArray(jsize len)
{
	return getEnv()->NewByteArray( len );
}

jcharArray JNIEnvHelper::NewCharArray(jsize len)
{
	return getEnv()->NewCharArray( len );
}

jshortArray JNIEnvHelper::NewShortArray(jsize len)
{
	return getEnv()->NewShortArray( len );
}

jintArray JNIEnvHelper::NewIntArray(jsize len)
{
	return getEnv()->NewIntArray( len );
}

jlongArray JNIEnvHelper::NewLongArray(jsize len)
{
	return getEnv()->NewLongArray( len );
}

jfloatArray JNIEnvHelper::NewFloatArray(jsize len)
{
	return getEnv()->NewFloatArray( len );
}

jdoubleArray JNIEnvHelper::NewDoubleArray(jsize len)
{
	return getEnv()->NewDoubleArray( len );
}

jboolean* JNIEnvHelper::GetBooleanArrayElements(jbooleanArray array, jboolean *isCopy)
{
	return getEnv()->GetBooleanArrayElements( array, isCopy );
}

jbyte* JNIEnvHelper::GetByteArrayElements(jbyteArray array, jboolean *isCopy)
{
	return getEnv()->GetByteArrayElements( array, isCopy );
}

jchar* JNIEnvHelper::GetCharArrayElements(jcharArray array, jboolean *isCopy)
{
	return getEnv()->GetCharArrayElements( array, isCopy );
}

jshort* JNIEnvHelper::GetShortArrayElements(jshortArray array, jboolean *isCopy)
{
	return getEnv()->GetShortArrayElements( array, isCopy );
}

jint* JNIEnvHelper:: GetIntArrayElements(jintArray array, jboolean *isCopy)
{
	return getEnv()->GetIntArrayElements( array, isCopy );
}

jlong* JNIEnvHelper::GetLongArrayElements(jlongArray array, jboolean *isCopy)
{
	return getEnv()->GetLongArrayElements( array, isCopy );
}

jfloat* JNIEnvHelper::GetFloatArrayElements(jfloatArray array, jboolean *isCopy)
{
	return getEnv()->GetFloatArrayElements( array, isCopy );
}

jdouble* JNIEnvHelper::GetDoubleArrayElements(jdoubleArray array, jboolean *isCopy)
{
	return getEnv()->GetDoubleArrayElements( array, isCopy );
}

void JNIEnvHelper::ReleaseBooleanArrayElements(jbooleanArray array, jboolean *elems, jint mode)
{
	getEnv()->ReleaseBooleanArrayElements( array, elems, mode );
}

void JNIEnvHelper::ReleaseByteArrayElements(jbyteArray array, jbyte *elems, jint mode)
{
	getEnv()->ReleaseByteArrayElements( array, elems, mode );
}

void JNIEnvHelper::ReleaseCharArrayElements(jcharArray array, jchar *elems, jint mode)
{
	getEnv()->ReleaseCharArrayElements( array, elems, mode );
}

void JNIEnvHelper::ReleaseShortArrayElements(jshortArray array, jshort *elems, jint mode)
{
	getEnv()->ReleaseShortArrayElements( array, elems, mode );
}

void JNIEnvHelper::ReleaseIntArrayElements(jintArray array, jint *elems, jint mode)
{
	getEnv()->ReleaseIntArrayElements( array, elems, mode );
}

void JNIEnvHelper::ReleaseLongArrayElements(jlongArray array, jlong *elems, jint mode)
{
	getEnv()->ReleaseLongArrayElements( array, elems, mode );
}

void JNIEnvHelper::ReleaseFloatArrayElements(jfloatArray array, jfloat *elems, jint mode)
{
	getEnv()->ReleaseFloatArrayElements( array, elems, mode );
}

void JNIEnvHelper::ReleaseDoubleArrayElements(jdoubleArray array, jdouble *elems, jint mode)
{
	getEnv()->ReleaseDoubleArrayElements( array, elems, mode );
}

void JNIEnvHelper::GetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len, jboolean *buf)
{
	getEnv()->GetBooleanArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::GetByteArrayRegion(jbyteArray array, jsize start, jsize len, jbyte *buf)
{
	getEnv()->GetByteArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::GetCharArrayRegion(jcharArray array, jsize start, jsize len, jchar *buf)
{
	getEnv()->GetCharArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::GetShortArrayRegion(jshortArray array, jsize start, jsize len, jshort *buf)
{
	getEnv()->GetShortArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::GetIntArrayRegion(jintArray array, jsize start, jsize len, jint *buf)
{
	getEnv()->GetIntArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::GetLongArrayRegion(jlongArray array, jsize start, jsize len, jlong *buf)
{
	getEnv()->GetLongArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::GetFloatArrayRegion(jfloatArray array, jsize start, jsize len, jfloat *buf)
{
	getEnv()->GetFloatArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::GetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len, jdouble *buf)
{
	getEnv()->GetDoubleArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::SetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len, jboolean *buf)
{
	getEnv()->SetBooleanArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::SetByteArrayRegion(jbyteArray array, jsize start, jsize len, jbyte *buf)
{
	getEnv()->SetByteArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::SetCharArrayRegion(jcharArray array, jsize start, jsize len, jchar *buf)
{
	getEnv()->SetCharArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::SetShortArrayRegion(jshortArray array, jsize start, jsize len, jshort *buf)
{
	getEnv()->SetShortArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::SetIntArrayRegion(jintArray array, jsize start, jsize len, jint *buf)
{
	getEnv()->SetIntArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::SetLongArrayRegion(jlongArray array, jsize start, jsize len, jlong *buf)
{
	getEnv()->SetLongArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::SetFloatArrayRegion(jfloatArray array, jsize start, jsize len, jfloat *buf)
{
	getEnv()->SetFloatArrayRegion( array, start, len, buf );
}

void JNIEnvHelper::SetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len, jdouble *buf)
{
	getEnv()->SetDoubleArrayRegion( array, start, len, buf );
}

jint JNIEnvHelper::RegisterNatives(jclass clazz, const JNINativeMethod *methods, jint nMethods)
{
	jint returnValue = getEnv()->RegisterNatives( clazz, methods, nMethods );
   switch(returnValue)
   {
   case JNI_OK:
      //LogManager::log(LogManager::info,"/* success */");
      break;
   case JNI_ERR:
      LogManager::log(LogManager::warning,"JNI_ERR /* unknown error */");
      break;
   case JNI_EDETACHED:
      LogManager::log(LogManager::warning,"JNI_EDETACHED /* thread detached from the VM */");
      break;
   case JNI_EVERSION:
      LogManager::log(LogManager::warning,"JNI_EVERSION /* JNI version error */");
      break;
   case JNI_ENOMEM:
      LogManager::log(LogManager::warning,"JNI_ENOMEM /* not enough memory */");
      break;
   case JNI_EEXIST:
      LogManager::log(LogManager::warning,"JNI_EEXIST /* VM already created */");
      break;
   case JNI_EINVAL:
      LogManager::log(LogManager::warning,"JNI_EINVAL /* invalid arguments */");
      break;
   default:
      break;
   }
   return returnValue;

}

jint JNIEnvHelper::UnregisterNatives(jclass clazz)
{
	return getEnv()->UnregisterNatives( clazz );
}

jint JNIEnvHelper::MonitorEnter(jobject obj)
{
	return getEnv()->MonitorEnter( obj );
}

jint JNIEnvHelper::MonitorExit(jobject obj)
{
	return getEnv()->MonitorExit( obj );
}

jint JNIEnvHelper::GetJavaVM(JavaVM **vm)
{
	return getEnv()->GetJavaVM( vm );
}

void JNIEnvHelper::GetStringRegion(jstring str, jsize start, jsize len, jchar *buf)
{
	getEnv()->GetStringRegion( str, start, len, buf );
}

void JNIEnvHelper::GetStringUTFRegion(jstring str, jsize start, jsize len, char *buf)
{
	getEnv()->GetStringUTFRegion( str, start, len, buf );
}

void* JNIEnvHelper::GetPrimitiveArrayCritical(jarray array, jboolean *isCopy)
{
	return getEnv()->GetPrimitiveArrayCritical( array, isCopy );
}

void JNIEnvHelper::ReleasePrimitiveArrayCritical(jarray array, void *carray, jint mode)
{
	getEnv()->ReleasePrimitiveArrayCritical( array, carray, mode );
}

const jchar* JNIEnvHelper::GetStringCritical(jstring string, jboolean *isCopy)
{
	return getEnv()->GetStringCritical( string, isCopy );
}

void JNIEnvHelper::ReleaseStringCritical(jstring string, const jchar *cstring)
{
	getEnv()->ReleaseStringCritical( string, cstring );
}

jweak JNIEnvHelper::NewWeakGlobalRef(jobject obj)
{
	return getEnv()->NewWeakGlobalRef( obj );
}

void JNIEnvHelper::DeleteWeakGlobalRef(jweak ref)
{
	getEnv()->DeleteWeakGlobalRef( ref );
}

jboolean JNIEnvHelper::ExceptionCheck()
{
	return getEnv()->ExceptionCheck();
}

jstring JNIEnvHelper::CallStringMethod(jobject obj, jmethodID methodID, ...)
{
	jstring result;
	va_list args;
	va_start( args, methodID );
	result = reinterpret_cast<jstring>( CallObjectMethodV( obj, methodID, args ) );
	va_end( args );
	return result;
}

jstring JNIEnvHelper::CallNonvirtualStringMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jstring result;
	va_list args;
	va_start( args, methodID );
	result = reinterpret_cast<jstring>( CallNonvirtualObjectMethodV( obj, clazz, methodID, args ) );
	va_end( args );
	return result;
}

jstring JNIEnvHelper::CallStaticStringMethod(jclass clazz, jmethodID methodID, ...)
{
	jstring result;
	va_list args;
	va_start( args, methodID );
	result = reinterpret_cast<jstring>( CallStaticObjectMethodV( clazz, methodID, args ) );
	va_end( args );
	return result;
}

jclass JNIEnvHelper::CallClassMethod(jobject obj, jmethodID methodID, ...)
{
	jclass result;
	va_list args;
	va_start( args, methodID );
	result = reinterpret_cast<jclass>( CallObjectMethodV( obj, methodID, args ) );
	va_end( args );
	return result;
}

jclass JNIEnvHelper::CallNonvirtualClassMethod(jobject obj, jclass clazz, jmethodID methodID, ...)
{
	jclass result;
	va_list args;
	va_start( args, methodID );
	result = reinterpret_cast<jclass>( CallNonvirtualObjectMethodV( obj, clazz, methodID, args ) );
	va_end( args );
	return result;
}

jclass JNIEnvHelper::CallStaticClassMethod(jclass clazz, jmethodID methodID, ...)
{
	jclass result;
	va_list args;
	va_start( args, methodID );
	result = reinterpret_cast<jclass>( CallStaticObjectMethodV( clazz, methodID, args ) );
	va_end( args );
	return result;
}
