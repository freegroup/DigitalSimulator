#ifndef __net_sourceforge_jnipp_PrimitiveArray_H
#define __net_sourceforge_jnipp_PrimitiveArray_H

#include "JNIEnvHelper.h"

#ifdef WIN32
#pragma warning(disable:4251)
#pragma warning(disable:4786)
#endif

#include <vector>

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
         template<class T>
         class PrimitiveArray {
         private:
             jarray items;

         private:
             PrimitiveArray();

         public:
             PrimitiveArray(jobject obj) :
                 items(static_cast<jarray>(JNIEnvHelper::NewGlobalRef(obj)))
             {;}

             PrimitiveArray(T *arr, size_t size);

             PrimitiveArray(const PrimitiveArray<T> &obj) :
                 items(static_cast<jarray>(JNIEnvHelper::NewGlobalRef(obj.items)))
             {;}

             virtual ~PrimitiveArray() {
                 JNIEnvHelper::DeleteGlobalRef(items);
             }

             PrimitiveArray<T> & operator = (const PrimitiveArray<T> &obj) {
                 if (&obj != this) {
                     items = static_cast<jarray>(JNIEnvHelper::NewGlobalRef(obj.items));
                 }
                 return *this;
             }

             T get(int index);
             void set(int index, T value);
             void fill(T* array,int count);

             operator jobject () {
                 return items;
             }

             jsize size() const {
                 return JNIEnvHelper::GetArrayLength(items);
             }
         };
		};
	};
};

#endif
