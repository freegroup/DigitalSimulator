#ifndef IOBJECTCONTEXT_INCLUDE
#define IOBJECTCONTEXT_INCLUDE



#include "Autofont.h"
#include "IObjectContext.h"

#define SMALL_FONT    35
#define BIG_FONT      45

interface Context : IObjectContext {
public:
	Context();

   // You can popup our own Dialog to configure
   // the object. Store your configuration data in the
   // `param' data block. 
   //
   virtual int doConfigure(HWND view,char*  param);

   // implementation of the IObjectInfo-interface
   // ( see in IObjectInfo.h for documentation )
   //
   // unique hash key for the DigitalSimulator.....this string
   // will be display in the 'extended Option' dialog
   //
	virtual char *  getKey();

   // ....
   virtual char *  getName();

   // Return the name of the developer of this plugIn.
   // This name will be display in the generic option dialog
   //
   virtual char *  getProgrammerName();

   // Return your homepage
   //
   virtual char *  getProgrammerURL();


   // Return your the Developer Address. In the generic configuration
   // dialog is a mail-link.
   //
   virtual char *  getProgrammerMail();


   // Return the PlugInVersion 
   // At the Moment will not be checked againts 
   // saved objects.....planed for the future
   // The Version will be display in the generic configuration
   // dialog
   // 
   virtual char *  getVersion();


   // return the Label which is displayd under the object
   // (NOT SUPPORTED AT THE MOMENT)
   //
   virtual char *  getLabel();


   // Returns the DigitalSimulator the possible count of 
   // input pins
   //
   virtual CSize getInputCountRange(); 


   // ......
   //
   virtual CSize getOutputCountRange(); 


   // Return the size in Pixel wich the object needs
   // Required for the DragDrop operation of the framework
   //
   virtual CSize getSize(long inputCount, long outputCount); 

   // Return the size of persistend memory which the object 
   // additional needs. This memory will be saved with the document.
   // The allocated memory will be hand over all functions.
   // ( char* param )
   //
   // If you return 0 the hand over parameter 'param' in the other
   // functions are always NULL
   //
   virtual long  getParamCount()   ;

   // short discription what the object do. Will be display in the
   // extenden configuration dialog
   //
   virtual char *  getDescription();

   // returns the name of the object group (e.g. Gatter, FlipFlop). 
   // The object will be stored in the extenden dialog in this sub-tree of
   // the group name. Is the group does not exist it will be created.
   //
   virtual char *  getGroup();

   // calculate the values of the output pins
   // return 0 for NO redraw neccessary
   // return 1 for redraw neccessary
   //
	virtual int calculate(char *input ,char* lastInput,long inputCount,
                         char* output, long outputCount,
                         char* param);


   // before the simulator start the calculation of the circuit
   // all objects will be received a message. You can open
   // a file (e.g. report objects) or open a hardware interface 
   // (e.g. parallel port)
   //
   virtual void onStartCalculate(char* param);


   // After the calculation is done all objects will received a
   // message. You can close all handles or free some temp memory
   //
   virtual void onStopCalculate(char* param);


   // layout the output pins. The origin (0/0) are at the top left corner
   // x INCREASED to the right and y DECREASE to the bottom.
   //
   virtual void layoutOutput(long*  xPositions, 
                             long*  yPositions,
                             long   inputCount, 
                             long   outputCount,
                             char* param);

   // layout the input pins. The origin (0/0) are at the top left corner
   // x increased to the right and y decreased to the bottom.
   //
   virtual void layoutInput(long*  xPositions, 
                            long*  yPositions,
                            long   inputCount, 
                            long   outputCount,
                            char* param);

   // draws the object
   //
   // return true  => the framework draws nothing 
   // return false => the framework draws the input/output ports
   //
   virtual bool paint(CDC* pDC,
                      CPoint location, 
                      long inputCount, 
                      long outputCount, 
                      char* param);

   // After the allocation of the persitent buffer 'param' this
   // function will be called from the framework. Its your turn to
   // init the data. ....memset(....)
   //
   virtual void initParam(char* param);


   // delete/free all data which are stored in the 
   // param buffer. e.g. free pointers to stucts/classes
   //
   virtual void cleanupParam(char* param);

   //  DON`T TOUCH THIS CODE
   //
   // implementation of the PluginBase-interface
   // 
   virtual char* getBuildDate(){
      return __DATE__;
   }

	virtual bool QueryInterface(const char *iid, IPluginBase **iface);
	virtual void Destroy(void);

protected:
   CAutoFont m_bigFont;
   CAutoFont m_smallFont;
};


#endif
