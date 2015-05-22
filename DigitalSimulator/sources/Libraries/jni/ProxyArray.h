#ifndef __net_sourceforge_jnipp_ProxyArray_H
#define __net_sourceforge_jnipp_ProxyArray_H

#ifdef WIN32
#pragma warning(disable:4251)
#pragma warning(disable:4786)
#endif

#include <vector>
#include "JNIEnvHelper.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			template<class T>
			class ProxyArray
			{
			private:
				std::vector<T *> proxyVector;
				
			public:
				ProxyArray()
				{
				}

				ProxyArray(jobject obj)
				{
					ProxyArray( reinterpret_cast<jobjectArray>( obj ) );
				}

				ProxyArray(jobjectArray nativeArray)
				{
					jsize numElems = JNIEnvHelper::GetArrayLength( nativeArray );

					for ( int i = 0; i < numElems; ++i )
						proxyVector.push_back( new T( JNIEnvHelper::GetObjectArrayElement( nativeArray, i ) ) );
				}

				~ProxyArray()
				{
					for ( std::vector<T *>::iterator iter = proxyVector.begin(); iter != proxyVector.end(); ++iter )
						delete (*iter);
					proxyVector.clear();
				}

				void addElement(const T &newObject)
				{
					proxyVector.push_back( new T( newObject ) );
				}

				void addElement(const jobject newObject)
				{
					proxyVector.push_back( new T( newObject ) );
				}
				
				ProxyArray& operator=(ProxyArray &rhs)
				{
					for ( std::vector<T*>::iterator iter = proxyVector.begin(); iter != proxyVector.end(); ++iter )
						delete (*iter);
					proxyVector.clear();

					for ( std::vector<T*>::iterator iter = rhs.proxyVector.begin(); iter != rhs.proxyVector.end(); ++iter )
						proxyVector.push_back( new T( *(*iter) ) );

					return *this;
				}
				
				ProxyArray& operator=(const jobjectArray rhs)
				{
					jsize numElems = JNIEnvHelper::GetArrayLength( rhs );

					for ( int i = 0; i < numElems; ++i )
						proxyVector.push_back( new T( JNIEnvHelper::GetObjectArrayElement( rhs, i ) ) );

					return *this;
				}
				
				T& operator[](int index)
				{
				}

				operator jobjectArray()
				{
					jobjectArray retVal;
					jsize numElems = proxyVector.size();

					if ( numElems == 0 )
						return NULL;

					// create new array, all NULLs by default
					retVal = JNIEnvHelper::NewObjectArray( numElems, proxyVector[0]->getObjectClass(), NULL );

					// copy the elements of the vector into the newly-created array
					jsize index = 0;
					for ( std::vector<T *>::iterator iter = proxyVector.begin(); iter != proxyVector.end(); ++iter, ++index )
						JNIEnvHelper::SetObjectArrayElement( retVal, index, *(*iter) );

					return retVal;
				}
				
				operator jobject()
				{
					return static_cast<jobjectArray>( *this );
				}
			};
		};
	};
};

#endif
