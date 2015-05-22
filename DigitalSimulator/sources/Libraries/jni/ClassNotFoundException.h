#ifndef __net_sourceforge_jnipp_ClassNotFoundException_H
#define __net_sourceforge_jnipp_ClassNotFoundException_H

#include "BaseException.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			class ClassNotFoundException : public BaseException
			{
			public:
				ClassNotFoundException(const std::string& className)
					: BaseException( "Could not find class " + className )
				{
				}
			};
		};
	};
};

#endif
