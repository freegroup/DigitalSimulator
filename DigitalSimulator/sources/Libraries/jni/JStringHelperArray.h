#ifndef __net_sourceforge_jnipp_JStringHelperArray_H
#define __net_sourceforge_jnipp_JStringHelperArray_H

#ifdef WIN32
#pragma warning(disable:4251)
#pragma warning(disable:4786)
#endif

#include <vector>
#include <string>
#include "JStringHelper.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			class JStringHelperArray
			{
			private:
				std::vector<JStringHelper> stringVector;
				
			public:
				JStringHelperArray();
				JStringHelperArray(jobject obj);
				JStringHelperArray(jobjectArray nativeArray);
				JStringHelperArray(const std::vector<std::string>& strVector);
				JStringHelperArray(int argc, char **args);
				~JStringHelperArray();
				void addElement(const JStringHelper& newString);
				void addElement(const jstring newString);
				JStringHelperArray& operator=(JStringHelperArray& rhs);
				JStringHelperArray& operator=(const jobjectArray rhs);
				operator jobjectArray();
			};
		};
	};
};

#endif
