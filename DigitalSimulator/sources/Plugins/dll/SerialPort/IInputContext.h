#ifndef IINPUTCONTEXT_INCLUDE
#define IINPUTCONTEXT_INCLUDE

#include "../IPluginBase.h"

interface IInputContext : IPluginBase{

public:
   virtual char  read()  {return 0;}; // read one byte from the port

protected:
};

#endif
