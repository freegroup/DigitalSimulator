#ifndef __net_sourceforge_jnipp_BaseException_H
#define __net_sourceforge_jnipp_BaseException_H

#include <string>

namespace de
{
	namespace freegroup
	{
		namespace jnipp
		{
			class BaseException
			{
			private:
				std::string msg;

			public:
				BaseException()
				{
				}

				BaseException(const std::string& msg)
					: msg( msg )
				{
				}

				std::string getMessage()
				{
					return msg;
				}
			};
		};
	};
};

#endif
