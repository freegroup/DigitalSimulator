#ifndef __net_sourceforge_jnipp_JVM_H
#define __net_sourceforge_jnipp_JVM_H

#ifdef WIN32
#pragma warning(disable:4251)
#pragma warning(disable:4786)
#endif

#include <string>
#include <map>
#include <vector>
#include "jni.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			enum EnumInstalledJRE { SUN_JRE, IBM_JRE };

			class NativeMethodData
			{
			public:
				std::string className;
				JNINativeMethod* methods;
				int numMethods;

				NativeMethodData(const std::string& className, JNINativeMethod methods[], int numMethods)
					: className( className ), methods( methods ), numMethods( numMethods )
				{
					this->className = className;
					this->numMethods = numMethods;
					this->methods = new JNINativeMethod[numMethods];
					memcpy( this->methods, methods, numMethods*sizeof( JNINativeMethod ) );
				}
			};

			class JVM
			{
			private:
				static const char pathSeparator;
				static JavaVM* javaVM;
			//	static JNIEnv* jniEnv;
				static std::string classPath;
				static std::map<std::string, std::string> defines;
				static std::vector<NativeMethodData*> natives;

			public:
				static void load();
				static void load(EnumInstalledJRE jre);
				static void load(const std::string& jvmLibraryPath);
				static void unload();
				static void appendClassPath(const std::string& classPath);
				static void clearClassPath();
				static void addDefine(const std::string &key, const std::string &value);
				static void clearDefines();
				static jint attachCurrentThread();
				static jint detachCurrentThread();
				static void registerNatives(const std::string& className, JNINativeMethod nativeMethods[], int numMethods);

			};
		};
	};
};

#endif
