#include "PrimitiveArray.h"

using namespace de::freegroup::jnipp;


template<> PrimitiveArray<jboolean>::PrimitiveArray(jboolean *array, size_t size) {
    items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(JNIEnvHelper::NewBooleanArray(size)));
    jboolean *native_items = JNIEnvHelper::GetBooleanArrayElements(static_cast<jbooleanArray>(items), NULL);
    for (size_t i = 0; i < size; i++)
        native_items[i] = array[i];
    JNIEnvHelper::ReleaseBooleanArrayElements(static_cast<jbooleanArray>(items), native_items, 0);
}

template<> PrimitiveArray<jbyte>::PrimitiveArray(jbyte *array, size_t size) {
    items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(JNIEnvHelper::NewByteArray(size)));
    jbyte *native_items = JNIEnvHelper::GetByteArrayElements(static_cast<jbyteArray>(items), NULL);
    for (size_t i = 0; i < size; i++)
        native_items[i] = array[i];
    JNIEnvHelper::ReleaseByteArrayElements(static_cast<jbyteArray>(items), native_items, 0);
}

template<> PrimitiveArray<jchar>::PrimitiveArray(jchar *array, size_t size) {
    items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(JNIEnvHelper::NewCharArray(size)));
    jchar *native_items = JNIEnvHelper::GetCharArrayElements(static_cast<jcharArray>(items), NULL);
    for (size_t i = 0; i < size; i++)
        native_items[i] = array[i];
    JNIEnvHelper::ReleaseCharArrayElements(static_cast<jcharArray>(items), native_items, 0);
}

template<> PrimitiveArray<jshort>::PrimitiveArray(jshort *array, size_t size) {
    items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(JNIEnvHelper::NewShortArray(size)));
    jshort *native_items = JNIEnvHelper::GetShortArrayElements(static_cast<jshortArray>(items), NULL);
    for (size_t i = 0; i < size; i++)
        native_items[i] = array[i];
    JNIEnvHelper::ReleaseShortArrayElements(static_cast<jshortArray>(items), native_items, 0);
}

template<> PrimitiveArray<jint>::PrimitiveArray(jint *array, size_t size) {
    items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(JNIEnvHelper::NewIntArray(size)));
    jint *native_items = JNIEnvHelper::GetIntArrayElements(static_cast<jintArray>(items), NULL);
    for (size_t i = 0; i < size; i++)
        native_items[i] = array[i];
    JNIEnvHelper::ReleaseIntArrayElements(static_cast<jintArray>(items), native_items, 0);
}

template<> PrimitiveArray<jlong>::PrimitiveArray(jlong *array, size_t size) {
    items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(JNIEnvHelper::NewLongArray(size)));
    jlong *native_items = JNIEnvHelper::GetLongArrayElements(static_cast<jlongArray>(items), NULL);
    for (size_t i = 0; i < size; i++)
        native_items[i] = array[i];
    JNIEnvHelper::ReleaseLongArrayElements(static_cast<jlongArray>(items), native_items, 0);
}

template<> PrimitiveArray<jfloat>::PrimitiveArray(jfloat *array, size_t size) {
    items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(JNIEnvHelper::NewFloatArray(size)));
    jfloat *native_items = JNIEnvHelper::GetFloatArrayElements(static_cast<jfloatArray>(items), NULL);
    for (size_t i = 0; i < size; i++)
        native_items[i] = array[i];
    JNIEnvHelper::ReleaseFloatArrayElements(static_cast<jfloatArray>(items), native_items, 0);
}

template<> PrimitiveArray<jdouble>::PrimitiveArray(jdouble *array, size_t size) {
    items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(JNIEnvHelper::NewDoubleArray(size)));
    jdouble *native_items = JNIEnvHelper::GetDoubleArrayElements(static_cast<jdoubleArray>(items), NULL);
    for (size_t i = 0; i < size; i++)
        native_items[i] = array[i];
    JNIEnvHelper::ReleaseDoubleArrayElements(static_cast<jdoubleArray>(items), native_items, 0);
}


template<> jboolean PrimitiveArray<jboolean>::get(int pos) {
   jboolean result;
   JNIEnvHelper::GetBooleanArrayRegion(static_cast<jbooleanArray>(items),pos,1,&result);
   return result;
}

template<> jbyte PrimitiveArray<jbyte>::get(int pos) {
   jbyte result;
   JNIEnvHelper::GetByteArrayRegion(static_cast<jbyteArray>(items),pos,1,&result);
   return result;
}

template<> jchar PrimitiveArray<jchar>::get(int pos) {
   jchar result;
   JNIEnvHelper::GetCharArrayRegion(static_cast<jcharArray>(items),pos,1,&result);
   return result;
}

template<> jshort PrimitiveArray<jshort>::get(int pos) {
   jshort result;
   JNIEnvHelper::GetShortArrayRegion(static_cast<jshortArray>(items),pos,1,&result);
   return result;
}

template<> jint PrimitiveArray<jint>::get(int pos) {
   jint result;
   JNIEnvHelper::GetIntArrayRegion(static_cast<jintArray>(items),pos,1,&result);
   return result;
}

template<> jlong  PrimitiveArray<jlong>::get(int pos) {
   jlong result;
   JNIEnvHelper::GetLongArrayRegion(static_cast<jlongArray>(items),pos,1,&result);
   return result;
}

template<> jfloat PrimitiveArray<jfloat>::get(int pos) {
   jfloat result;
   JNIEnvHelper::GetFloatArrayRegion(static_cast<jfloatArray>(items),pos,1,&result);
   return result;
}

template<> jdouble PrimitiveArray<jdouble>::get(int pos) {
   jdouble result;
   JNIEnvHelper::GetDoubleArrayRegion(static_cast<jdoubleArray>(items),pos,1,&result);
   return result;
}


void PrimitiveArray<jboolean>::fill(jboolean* array, int count) {
   JNIEnvHelper::GetBooleanArrayRegion(static_cast<jbooleanArray>(items),0,count,array);
}

void PrimitiveArray<jbyte>::fill(jbyte* array,int count) {
   JNIEnvHelper::GetByteArrayRegion(static_cast<jbyteArray>(items),0,count,array);
}

void PrimitiveArray<jchar>::fill(jchar* array,int count) {
   JNIEnvHelper::GetCharArrayRegion(static_cast<jcharArray>(items),0,count,array);
}

void PrimitiveArray<jshort>::fill(jshort* array,int count) {
   JNIEnvHelper::GetShortArrayRegion(static_cast<jshortArray>(items),0,count,array);
}

void PrimitiveArray<jint>::fill(jint* array,int count) {
   JNIEnvHelper::GetIntArrayRegion(static_cast<jintArray>(items),0,count,array);
}

void  PrimitiveArray<jlong>::fill(jlong* array,int count) {
   JNIEnvHelper::GetLongArrayRegion(static_cast<jlongArray>(items),0,count,array);
}

void PrimitiveArray<jfloat>::fill(jfloat* array,int count) {
   JNIEnvHelper::GetFloatArrayRegion(static_cast<jfloatArray>(items),0,count,array);
}

void PrimitiveArray<jdouble>::fill(jdouble* array,int count) {
   JNIEnvHelper::GetDoubleArrayRegion(static_cast<jdoubleArray>(items),0,count,array);
}




void PrimitiveArray<jboolean>::set(int pos, jboolean value) {
   JNIEnvHelper::SetBooleanArrayRegion(static_cast<jbooleanArray>(items),pos,1,&value);
}

void PrimitiveArray<jbyte>::set(int pos, jbyte value) {
   JNIEnvHelper::SetByteArrayRegion(static_cast<jbyteArray>(items),pos,1,&value);
}

void PrimitiveArray<jchar>::set(int pos, jchar value) {
   JNIEnvHelper::SetCharArrayRegion(static_cast<jcharArray>(items),pos,1,&value);
}

void PrimitiveArray<jshort>::set(int pos, jshort value) {
   JNIEnvHelper::SetShortArrayRegion(static_cast<jshortArray>(items),pos,1,&value);
}

void PrimitiveArray<jint>::set(int pos, jint value) {
   JNIEnvHelper::SetIntArrayRegion(static_cast<jintArray>(items),pos,1,&value);
}

void  PrimitiveArray<jlong>::set(int pos, jlong value) {
   JNIEnvHelper::SetLongArrayRegion(static_cast<jlongArray>(items),pos,1,&value);
}

void PrimitiveArray<jfloat>::set(int pos, jfloat value) {
   JNIEnvHelper::SetFloatArrayRegion(static_cast<jfloatArray>(items),pos,1,&value);
}

void PrimitiveArray<jdouble>::set(int pos, jdouble value) {
   JNIEnvHelper::SetDoubleArrayRegion(static_cast<jdoubleArray>(items),pos,1,&value);
}

