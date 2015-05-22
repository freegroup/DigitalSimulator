#ifndef __ObjectProxyArray_H
#define __ObjectProxyArray_H

#include <vector>
#include "ObjectProxy.h"

template<class T>
class ObjectProxyArray
{
private:
	JNIEnv *jniEnv;
	std::vector<T *> proxyVector;
	
public:
	ObjectProxyArray();
	ObjectProxyArray(jobjectArray nativeArray);
	~ObjectProxyArray();
	void addElement(const T &newObject);
	void addElement(const jobject newObject);
	ObjectProxyArray& operator=(ObjectProxyArray &rhs);
	ObjectProxyArray& operator=(const jobjectArray rhs);
	T& operator[](int index);
	operator jobjectArray();
};

template<class T>
ObjectProxyArray<T>::ObjectProxyArray()
{
	jniEnv = JVMWrapper::getJVMWrapper().getEnv();
}

template<class T>
ObjectProxyArray<T>::ObjectProxyArray(jobjectArray nativeArray)
{
	jniEnv = JVMWrapper::getJVMWrapper().getEnv();

	jsize numElems = jniEnv->GetArrayLength( nativeArray );

	for ( int i = 0; i < numElems; ++i )
		proxyVector.push_back( new T( jniEnv->GetObjectArrayElement( nativeArray, i ) ) );
}

template<class T>
ObjectProxyArray<T>::~ObjectProxyArray()
{
	for ( std::vector<T *>::iterator it = proxyVector.begin(); it != proxyVector.end(); ++it )
		delete (*it);
	proxyVector.clear();
}

template<class T>
void ObjectProxyArray<T>::addElement(const T &newObject)
{
	proxyVector.push_back( new T( newObject ) );
}


template<class T>
void ObjectProxyArray<T>::addElement(const jobject newObject)
{
	proxyVector.push_back( new T( newObject ) );
}


template<class T>
ObjectProxyArray<T>& ObjectProxyArray<T>::operator=(ObjectProxyArray &rhs)
{
	for ( std::vector<T *>::iterator it = proxyVector.begin(); it != proxyVector.end(); ++it )
		delete (*it);
	proxyVector.clear();

	for ( it = rhs.proxyVector.begin(); it != rhs.proxyVector.end(); ++it )
		proxyVector.push_back( new T( *(*it) ) );

	return *this;
}

template<class T>
ObjectProxyArray<T>& ObjectProxyArray<T>::operator=(const jobjectArray rhs)
{
	jsize numElems = jniEnv->GetArrayLength( rhs );

	for ( int i = 0; i < numElems; ++i )
		proxyVector.push_back( new T( jniEnv->GetObjectArrayElement( rhs, i ) ) );

	return *this;
}

template<class T>
T& ObjectProxyArray<T>::operator[](int index)
{
//	return *proxyVector[index];

}

template<class T>
ObjectProxyArray<T>::operator jobjectArray()
{
	jobjectArray retVal;
	jsize numElems = proxyVector.size();

	if ( numElems == 0 )
		return NULL;

	// create new array, all NULLs by default
	retVal = jniEnv->NewObjectArray( numElems, proxyVector[0]->getClass(), NULL );

	// copy the elements of the vector into the newly-created array
	jsize index = 0;
	for ( std::vector<T *>::iterator it = proxyVector.begin(); it != proxyVector.end(); ++it, ++index )
		jniEnv->SetObjectArrayElement( retVal, index, *(*it) );

	return retVal;
}

#endif