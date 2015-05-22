#ifndef __net_sourceforge_jnipp_MethodNotFoundException_H
#define __net_sourceforge_jnipp_MethodNotFoundException_H

#include "BaseException.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			class MethodNotFoundException : public BaseException
			{
			public:
				MethodNotFoundException(const std::string& methodName)
					: BaseException( "Could not find method " + methodName )
				{
				}
			};
		};
	};
};

#endif
