#ifndef __net_sourceforge_jnipp_JNIEnvHelper_H
#define __net_sourceforge_jnipp_JNIEnvHelper_H


#ifdef WIN32
#pragma warning(disable:4251)
#pragma warning(disable:4786)
#endif

#ifdef WIN32
typedef unsigned pthread_t;
#else
#include <pthread.h>
#endif

#include <map>
#include "jni.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			class JNIEnvHelper
			{
			private:
				static void exceptionCheck();

				// each thread has its own interface pointer
				static std::map<pthread_t, JNIEnv*> interfaceMap;
            //    static JNIEnv* env;
			public:
				static void init(JNIEnv* jniEnv);
				static void uninit();
				static JNIEnv* getEnv();

				// wrapped methods
				static jint GetVersion();
				static jclass DefineClass(const char *name, jobject loader, const jbyte *buf, jsize len);
				static jclass FindClass(const char *name);
				static jmethodID FromReflectedMethod(jobject method);
				static jfieldID FromReflectedField(jobject field);
				static jobject ToReflectedMethod(jclass cls, jmethodID methodID, jboolean isStatic);
				static jclass GetSuperclass(jclass sub);
				static jboolean IsAssignableFrom(jclass sub, jclass sup);
				static jobject ToReflectedField(jclass cls, jfieldID fieldID, jboolean isStatic);
				static jint Throw(jthrowable obj);
				static jint ThrowNew(jclass clazz, const char *msg);
				static jthrowable ExceptionOccurred();
				static void ExceptionDescribe();
				static void ExceptionClear();
				static void FatalError(const char *msg);
				static jint PushLocalFrame(jint capacity);
				static jobject PopLocalFrame(jobject result);
				static jobject NewGlobalRef(jobject lobj);
				static void DeleteGlobalRef(jobject gref);
				static void DeleteLocalRef(jobject obj);
				static jboolean IsSameObject(jobject obj1, jobject obj2);
				static jobject NewLocalRef(jobject ref);
				static jint EnsureLocalCapacity(jint capacity);
				static jobject AllocObject(jclass clazz);
				static jobject NewObject(jclass clazz, jmethodID methodID, ...);
				static jobject NewObjectV(jclass clazz, jmethodID methodID, va_list args);
				static jobject NewObjectA(jclass clazz, jmethodID methodID, jvalue *args);
				static jclass GetObjectClass(jobject obj);
				static jboolean IsInstanceOf(jobject obj, jclass clazz);
				static jmethodID GetMethodID(jclass clazz, const char *name, const char *sig);
				static jobject CallObjectMethod(jobject obj, jmethodID methodID, ...);
				static jobject CallObjectMethodV(jobject obj, jmethodID methodID, va_list args);
				static jobject CallObjectMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static jboolean CallBooleanMethod(jobject obj,  jmethodID methodID, ...);
				static jboolean CallBooleanMethodV(jobject obj, jmethodID methodID, va_list args);
				static jboolean CallBooleanMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static jbyte CallByteMethod(jobject obj, jmethodID methodID, ...);
				static jbyte CallByteMethodV(jobject obj, jmethodID methodID, va_list args);
				static jbyte CallByteMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static jchar CallCharMethod(jobject obj, jmethodID methodID, ...);
				static jchar CallCharMethodV(jobject obj, jmethodID methodID, va_list args);
				static jchar CallCharMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static jshort CallShortMethod(jobject obj, jmethodID methodID, ...);
				static jshort CallShortMethodV(jobject obj, jmethodID methodID, va_list args);
				static jshort CallShortMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static jint CallIntMethod(jobject obj, jmethodID methodID, ...);
				static jint CallIntMethodV(jobject obj, jmethodID methodID, va_list args);
				static jint CallIntMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static jlong CallLongMethod(jobject obj, jmethodID methodID, ...);
				static jlong CallLongMethodV(jobject obj, jmethodID methodID, va_list args);
				static jlong CallLongMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static jfloat CallFloatMethod(jobject obj, jmethodID methodID, ...);
				static jfloat CallFloatMethodV(jobject obj, jmethodID methodID, va_list args);
				static jfloat CallFloatMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static jdouble CallDoubleMethod(jobject obj, jmethodID methodID, ...);
				static jdouble CallDoubleMethodV(jobject obj, jmethodID methodID, va_list args);
				static jdouble CallDoubleMethodA(jobject obj, jmethodID methodID, jvalue* args);
				static void CallVoidMethod(jobject obj, jmethodID methodID, ...);
				static void CallVoidMethodV(jobject obj, jmethodID methodID,  va_list args);
				static void CallVoidMethodA(jobject obj, jmethodID methodID,  jvalue* args);
				static jobject CallNonvirtualObjectMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jobject CallNonvirtualObjectMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static jobject CallNonvirtualObjectMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static jboolean CallNonvirtualBooleanMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jboolean CallNonvirtualBooleanMethodV(jobject obj, jclass clazz,  jmethodID methodID, va_list args);
				static jboolean CallNonvirtualBooleanMethodA(jobject obj, jclass clazz,  jmethodID methodID, jvalue* args);
				static jbyte CallNonvirtualByteMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jbyte CallNonvirtualByteMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static jbyte CallNonvirtualByteMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static jchar CallNonvirtualCharMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jchar CallNonvirtualCharMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static jchar CallNonvirtualCharMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static jshort CallNonvirtualShortMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jshort CallNonvirtualShortMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static jshort CallNonvirtualShortMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static jint CallNonvirtualIntMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jint CallNonvirtualIntMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static jint CallNonvirtualIntMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static jlong CallNonvirtualLongMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jlong CallNonvirtualLongMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static jlong CallNonvirtualLongMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static jfloat CallNonvirtualFloatMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jfloat CallNonvirtualFloatMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static jfloat CallNonvirtualFloatMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static jdouble CallNonvirtualDoubleMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jdouble CallNonvirtualDoubleMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static jdouble CallNonvirtualDoubleMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static void CallNonvirtualVoidMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static void CallNonvirtualVoidMethodV(jobject obj, jclass clazz, jmethodID methodID, va_list args);
				static void CallNonvirtualVoidMethodA(jobject obj, jclass clazz, jmethodID methodID, jvalue* args);
				static jfieldID GetFieldID(jclass clazz, const char *name, const char *sig);
				static jobject GetObjectField(jobject obj, jfieldID fieldID);
				static jboolean GetBooleanField(jobject obj, jfieldID fieldID);
				static jbyte GetByteField(jobject obj, jfieldID fieldID);
				static jchar GetCharField(jobject obj, jfieldID fieldID);
				static jshort GetShortField(jobject obj, jfieldID fieldID);
				static jint GetIntField(jobject obj, jfieldID fieldID);
				static jlong GetLongField(jobject obj, jfieldID fieldID);
				static jfloat GetFloatField(jobject obj, jfieldID fieldID);
				static jdouble GetDoubleField(jobject obj, jfieldID fieldID);
				static void SetObjectField(jobject obj, jfieldID fieldID, jobject val);
				static void SetBooleanField(jobject obj, jfieldID fieldID, jboolean val);
				static void SetByteField(jobject obj, jfieldID fieldID, jbyte val);
				static void SetCharField(jobject obj, jfieldID fieldID, jchar val);
				static void SetShortField(jobject obj, jfieldID fieldID, jshort val);
				static void SetIntField(jobject obj, jfieldID fieldID, jint val);
				static void SetLongField(jobject obj, jfieldID fieldID, jlong val);
				static void SetFloatField(jobject obj, jfieldID fieldID, jfloat val);
				static void SetDoubleField(jobject obj, jfieldID fieldID, jdouble val);
				static jmethodID GetStaticMethodID(jclass clazz, const char *name, const char *sig);
				static jobject CallStaticObjectMethod(jclass clazz, jmethodID methodID, ...);
				static jobject CallStaticObjectMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jobject CallStaticObjectMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static jboolean CallStaticBooleanMethod(jclass clazz, jmethodID methodID, ...);
				static jboolean CallStaticBooleanMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jboolean CallStaticBooleanMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static jbyte CallStaticByteMethod(jclass clazz, jmethodID methodID, ...);
				static jbyte CallStaticByteMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jbyte CallStaticByteMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static jchar CallStaticCharMethod(jclass clazz, jmethodID methodID, ...);
				static jchar CallStaticCharMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jchar CallStaticCharMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static jshort CallStaticShortMethod(jclass clazz, jmethodID methodID, ...);
				static jshort CallStaticShortMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jshort CallStaticShortMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static jint CallStaticIntMethod(jclass clazz, jmethodID methodID, ...);
				static jint CallStaticIntMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jint CallStaticIntMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static jlong CallStaticLongMethod(jclass clazz, jmethodID methodID, ...);
				static jlong CallStaticLongMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jlong CallStaticLongMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static jfloat CallStaticFloatMethod(jclass clazz, jmethodID methodID, ...);
				static jfloat CallStaticFloatMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jfloat CallStaticFloatMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static jdouble CallStaticDoubleMethod(jclass clazz, jmethodID methodID, ...);
				static jdouble CallStaticDoubleMethodV(jclass clazz, jmethodID methodID, va_list args);
				static jdouble CallStaticDoubleMethodA(jclass clazz, jmethodID methodID, jvalue *args);
				static void CallStaticVoidMethod(jclass clazz, jmethodID methodID, ...);
				static void CallStaticVoidMethodV(jclass clazz, jmethodID methodID, va_list args);
				static void CallStaticVoidMethodA(jclass clazz, jmethodID methodID, jvalue* args);
				static jfieldID GetStaticFieldID(jclass clazz, const char *name, const char *sig);
				static jobject GetStaticObjectField(jclass clazz, jfieldID fieldID);
				static jboolean GetStaticBooleanField(jclass clazz, jfieldID fieldID);
				static jbyte GetStaticByteField(jclass clazz, jfieldID fieldID);
				static jchar GetStaticCharField(jclass clazz, jfieldID fieldID);
				static jshort GetStaticShortField(jclass clazz, jfieldID fieldID);
				static jint GetStaticIntField(jclass clazz, jfieldID fieldID);
				static jlong GetStaticLongField(jclass clazz, jfieldID fieldID);
				static jfloat GetStaticFloatField(jclass clazz, jfieldID fieldID);
				static jdouble GetStaticDoubleField(jclass clazz, jfieldID fieldID);
				static void SetStaticObjectField(jclass clazz, jfieldID fieldID, jobject value);
				static void SetStaticBooleanField(jclass clazz, jfieldID fieldID, jboolean value);
				static void SetStaticByteField(jclass clazz, jfieldID fieldID, jbyte value);
				static void SetStaticCharField(jclass clazz, jfieldID fieldID, jchar value);
				static void SetStaticShortField(jclass clazz, jfieldID fieldID, jshort value);
				static void SetStaticIntField(jclass clazz, jfieldID fieldID, jint value);
				static void SetStaticLongField(jclass clazz, jfieldID fieldID, jlong value);
				static void SetStaticFloatField(jclass clazz, jfieldID fieldID, jfloat value);
				static void SetStaticDoubleField(jclass clazz, jfieldID fieldID, jdouble value);
				static jstring NewString(const jchar *unicode, jsize len);
				static jsize GetStringLength(jstring str);
				static const jchar *GetStringChars(jstring str, jboolean *isCopy);
				static void ReleaseStringChars(jstring str, const jchar *chars);
				static jstring NewStringUTF(const char *utf);
				static jsize GetStringUTFLength(jstring str);
				static const char* GetStringUTFChars(jstring str, jboolean *isCopy);
				static void ReleaseStringUTFChars(jstring str, const char* chars);
				static jsize GetArrayLength(jarray array);
				static jobjectArray NewObjectArray(jsize len, jclass clazz, jobject init);
				static jobject GetObjectArrayElement(jobjectArray array, jsize index);
				static void SetObjectArrayElement(jobjectArray array, jsize index, jobject val);
				static jbooleanArray NewBooleanArray(jsize len);
				static jbyteArray NewByteArray(jsize len);
				static jcharArray NewCharArray(jsize len);
				static jshortArray NewShortArray(jsize len);
				static jintArray NewIntArray(jsize len);
				static jlongArray NewLongArray(jsize len);
				static jfloatArray NewFloatArray(jsize len);
				static jdoubleArray NewDoubleArray(jsize len);
				static jboolean* GetBooleanArrayElements(jbooleanArray array, jboolean *isCopy);
				static jbyte* GetByteArrayElements(jbyteArray array, jboolean *isCopy);
				static jchar* GetCharArrayElements(jcharArray array, jboolean *isCopy);
				static jshort* GetShortArrayElements(jshortArray array, jboolean *isCopy);
				static jint* GetIntArrayElements(jintArray array, jboolean *isCopy);
				static jlong* GetLongArrayElements(jlongArray array, jboolean *isCopy);
				static jfloat* GetFloatArrayElements(jfloatArray array, jboolean *isCopy);
				static jdouble* GetDoubleArrayElements(jdoubleArray array, jboolean *isCopy);
				static void ReleaseBooleanArrayElements(jbooleanArray array, jboolean *elems, jint mode);
				static void ReleaseByteArrayElements(jbyteArray array, jbyte *elems, jint mode);
				static void ReleaseCharArrayElements(jcharArray array, jchar *elems, jint mode);
				static void ReleaseShortArrayElements(jshortArray array, jshort *elems, jint mode);
				static void ReleaseIntArrayElements(jintArray array, jint *elems, jint mode);
				static void ReleaseLongArrayElements(jlongArray array, jlong *elems, jint mode);
				static void ReleaseFloatArrayElements(jfloatArray array, jfloat *elems, jint mode);
				static void ReleaseDoubleArrayElements(jdoubleArray array, jdouble *elems, jint mode);
				static void GetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len, jboolean *buf);
				static void GetByteArrayRegion(jbyteArray array, jsize start, jsize len, jbyte *buf);
				static void GetCharArrayRegion(jcharArray array, jsize start, jsize len, jchar *buf);
				static void GetShortArrayRegion(jshortArray array, jsize start, jsize len, jshort *buf);
				static void GetIntArrayRegion(jintArray array, jsize start, jsize len, jint *buf);
				static void GetLongArrayRegion(jlongArray array, jsize start, jsize len, jlong *buf);
				static void GetFloatArrayRegion(jfloatArray array, jsize start, jsize len, jfloat *buf);
				static void GetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len, jdouble *buf);
				static void SetBooleanArrayRegion(jbooleanArray array, jsize start, jsize len, jboolean *buf);
				static void SetByteArrayRegion(jbyteArray array, jsize start, jsize len, jbyte *buf);
				static void SetCharArrayRegion(jcharArray array, jsize start, jsize len, jchar *buf);
				static void SetShortArrayRegion(jshortArray array, jsize start, jsize len, jshort *buf);
				static void SetIntArrayRegion(jintArray array, jsize start, jsize len, jint *buf);
				static void SetLongArrayRegion(jlongArray array, jsize start, jsize len, jlong *buf);
				static void SetFloatArrayRegion(jfloatArray array, jsize start, jsize len, jfloat *buf);
				static void SetDoubleArrayRegion(jdoubleArray array, jsize start, jsize len, jdouble *buf);
				static jint RegisterNatives(jclass clazz, const JNINativeMethod *methods, jint nMethods);
				static jint UnregisterNatives(jclass clazz);
				static jint MonitorEnter(jobject obj);
				static jint MonitorExit(jobject obj);
				static jint GetJavaVM(JavaVM **vm);
				static void GetStringRegion(jstring str, jsize start, jsize len, jchar *buf);
				static void GetStringUTFRegion(jstring str, jsize start, jsize len, char *buf);
				static void* GetPrimitiveArrayCritical(jarray array, jboolean *isCopy);
				static void ReleasePrimitiveArrayCritical(jarray array, void *carray, jint mode);
				static const jchar* GetStringCritical(jstring string, jboolean *isCopy);
				static void ReleaseStringCritical(jstring string, const jchar *cstring);
				static jweak NewWeakGlobalRef(jobject obj);
				static void DeleteWeakGlobalRef(jweak ref);
				static jboolean ExceptionCheck();

				// helpers
				static jstring CallStringMethod(jobject obj, jmethodID methodID, ...);
				static jstring CallNonvirtualStringMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jstring CallStaticStringMethod(jclass clazz, jmethodID methodID, ...);
				static jclass CallClassMethod(jobject obj, jmethodID methodID, ...);
				static jclass CallNonvirtualClassMethod(jobject obj, jclass clazz, jmethodID methodID, ...);
				static jclass CallStaticClassMethod(jclass clazz, jmethodID methodID, ...);
			};
		};
	};
};

using namespace de::freegroup::jnipp;

class  JNIStack
{
public:

   JNIStack(int size)
   {
      JNIEnvHelper::PushLocalFrame(size);
   }

   JNIStack()
   {
      JNIEnvHelper::PushLocalFrame(128);
   }

   ~JNIStack()
   {
      JNIEnvHelper::PopLocalFrame(NULL);
   }
};

#endif
