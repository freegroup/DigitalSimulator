#ifndef __net_sourceforge_jnipp_JStringHelper_H
#define __net_sourceforge_jnipp_JStringHelper_H

#ifdef WIN32
#pragma warning(disable:4251)
#pragma warning(disable:4786)
#endif

#include <string>
#include "jni.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			class JStringHelper
			{
			private:
				std::string str;
				static jclass stringClass;

			public:
				JStringHelper();
				JStringHelper(const JStringHelper &rhs);
				JStringHelper(const char *p);
				JStringHelper(jobject obj);
				~JStringHelper();
				JStringHelper& operator=(const JStringHelper &rhs);
				JStringHelper& operator=(const char *rhs);
				JStringHelper& operator=(jobject rhs);
				operator jstring() const;
				operator jobject() const;
				operator const char*() const;
				static jclass getClass();
			};
		};
	};
};

#endif
