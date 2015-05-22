#ifndef IOUTPUTCONTEXT_INCLUDE
#define IOUTPUTCONTEXT_INCLUDE

#include "../IPluginBase.h"

interface IOutputContext : IPluginBase{

public:
   virtual int  write(char value) {return 0;}; // read one byte from the port

protected:
};

#endif
