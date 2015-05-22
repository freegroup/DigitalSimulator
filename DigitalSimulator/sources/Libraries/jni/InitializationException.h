#ifndef __net_sourceforge_jnipp_InitializationException_H
#define __net_sourceforge_jnipp_InitializationException_H

#include "BaseException.h"

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			class InitializationException : public BaseException
			{
			public:
				InitializationException()
					: BaseException( "Failed to initialize JVM" )
				{
				}
			};
		};
	};
};

#endif
