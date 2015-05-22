#ifndef __net_sourceforge_jnipp_EnvironmentNotInitializedException_H
#define __net_sourceforge_jnipp_EnvironmentNotInitializedException_H

#include "BaseException.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			class EnvironmentNotInitializedException : public BaseException
			{
			public:
				EnvironmentNotInitializedException()
					: BaseException( "Environment not initialized" )
				{
				}
			};
		};
	};
};

#endif
