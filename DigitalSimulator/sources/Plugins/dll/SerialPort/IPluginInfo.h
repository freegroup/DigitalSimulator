#ifndef IPLUGININFO_INCLUDE
#define IPLUGININFO_INCLUDE

#include "../IPluginBase.h"

interface IPluginInfo :IPluginBase{

public:
	virtual void getKey(char * ,long)           = 0;   // get the unique name of the Plugin
   virtual void getDeviceName(char * ,long)    = 0;
   virtual void getProducerName(char * ,long)  = 0;
   virtual void getProducerURL(char * ,long)   = 0;
   virtual void getProgrammerName(char * ,long)= 0;
   virtual void getProgrammerURL(char * ,long) = 0;
   virtual void getVersion(char*, long)        = 0;
   virtual void getLabel(char * ,long)         = 0;   // gets the label for the GUI object (e.g. "SchmidtInterface at COM:1" )
   virtual int  getPort()                      = 0;   // returns the COM-Port number
   virtual void Get(char * ,long)     = 0;   // returns all parameters for save/load of the object

   virtual void Set(const char*)      = 0;
   virtual void DoOption()                     = 0;   // start a dialog and configure this object


   virtual void onStart()                      = 0;   // event before the simulation starts
   virtual void onStop()                       = 0;   // event after the simulation ends

protected:
};

#endif
