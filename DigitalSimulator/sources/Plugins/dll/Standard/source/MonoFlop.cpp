/* NO WARRANTY
 *
 *    BECAUSE THE PROGRAM IS IN THE PUBLIC DOMAIN, THERE IS NO
 *    WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE
 *    LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE AUTHORS
 *    AND/OR OTHER PARTIES PROVIDE THE PROGRAM "AS IS" WITHOUT
 *    WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *    BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 *    AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS TO
 *    THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD
 *    THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL
 *    NECESSARY SERVICING, REPAIR OR CORRECTION.
 *
 *    IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN
 *    WRITING WILL ANY AUTHOR, OR ANY OTHER PARTY WHO MAY MODIFY
 *    AND/OR REDISTRIBUTE THE PROGRAM, BE LIABLE TO YOU FOR DAMAGES,
 *    INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL
 *    DAMAGES ARISING OUT OF THE USE OR INABILITY TO USE THE PROGRAM
 *    (INCLUDING BUT NOT LIMITED TO LOSS OF DATA OR DATA BEING
 *    RENDERED INACCURATE OR LOSSES SUSTAINED BY YOU OR THIRD PARTIES
 *    OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
 *    PROGRAMS), EVEN IF SUCH AUTHOR OR OTHER PARTY HAS BEEN ADVISED
 *    OF THE POSSIBILITY OF SUCH DAMAGES.
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <iomanip>


#include "stdafx.h"
#include "Autofont.h"
#include "Context.h"
#include "ConfigDialog.h"
#include <time.h>

#define  MS_VALUE        (*((long*)param))
#define  UNIT_VALUE      (*((long*)param+1))
#define  UNIT            (*((long*)param+2))
#define  START_TIME      (*((long*)param+3))
#define  TRIGGER         (*((long*)param+4))

#define  IN_TRIGGER      (input[0])
#define  IN_RESET        (input[1])

#define  LAST_IN_TRIGGER (lastInput[0])
#define  LAST_IN_RESET   (lastInput[1])

CWinApp theApp;
#define LINKAGE		__declspec(dllexport)

//----------------------------------------------------------------------------
int Context::doConfigure(HWND view, char*  param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // 0  => display the generic DigitalSimulator Dialog
   // 1  => no display neccessary.....display your own dialog in this function
   CConfigDialog dlg;

   dlg.m_value   = UNIT_VALUE;
   dlg.m_unit    = UNIT;
   dlg.m_trigger = TRIGGER;

   if(dlg.DoModal()==IDOK)
   {
      long value = 0;
      switch(dlg.m_unit)
      {
      case 0: // milli seconds
         value = dlg.m_value ;
         break;
      case 1: // seconds
         value = dlg.m_value * 1000;
         break;
      case 2: // minutes
         value = dlg.m_value * 1000 * 60;
         break;

      }
      memcpy(&MS_VALUE    ,&value         ,sizeof(long));
      memcpy(&UNIT_VALUE  ,&dlg.m_value   ,sizeof(long));
      memcpy(&UNIT        ,&dlg.m_unit    ,sizeof(long));
      memcpy(&TRIGGER     ,&dlg.m_trigger ,sizeof(long));
   }

   return 1;
}


// return the min/max of possible input pins
//
//----------------------------------------------------------------------------
CSize Context::getInputCountRange(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(2,2);
   // END_TODO
}; 


// return the min/max of the possible output pins
//
//----------------------------------------------------------------------------
CSize Context::getOutputCountRange(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(2,2);
   // END_TODO
}; 


// Return the dimension of the object.
// This is required for the DragDrap actions and painting
//
//----------------------------------------------------------------------------
CSize Context::getSize(long inputCount, long outputCount){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(115,70*max(outputCount,inputCount));
   // END_TODO
}; 

// Return the bytes of additional persistent memory. This memory array will
// be saved/loaded with the object itself
//
//----------------------------------------------------------------------------
long Context::getParamCount(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   // 1   = configured milli seconds for delay
   // 2   = configured value for delay, required for the dialog. This
   // 3   = time unit for "value". 
   //       0 -> milli seconds
   //       1 -> seconds
   //       2 -> minutes
   // 4   = elapsed time since the last trigger
   // 5   = flank trigger (positiv / negative )
   //
   return 5*sizeof(long);

   // END_TODO
}

// Return a short description of this object
//
//----------------------------------------------------------------------------
char*  Context::getDescription(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "MonoFlop\r\n\r\n"
          "Erhält das Monoflop für den eingestellten Zeitraum\r\n"
          "kein HIGH am Eingang, so erscheint am Ausgang ein \r\n"
          "LOW. Das Monoflop mißt hier gewissermaßen den Zeit-\r\n"
          "raum zwischen der fallenden Flanke des Eingangssignals\r\n"
          "und der steigenden Flnke des folgenden Impulses.\r\n";
   // END_TODO
}

// Return the name of the group in which this object will
// be insert (see in extended dialog)
//
//----------------------------------------------------------------------------
char*  Context::getGroup(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECTGROUP.FLIPFLOP";
   // END_TODO
}

// Unique key for the internal hash map
//
//----------------------------------------------------------------------------
char* Context::getKey(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "MonoFlop (edge triggered)";
   // END_TODO
}

// Display name of this object
//
//----------------------------------------------------------------------------
char* Context::getName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECT.MONOFLOP.EDGETRIGGER";
   // END_TODO
}


// .....****...
//
//----------------------------------------------------------------------------
char * Context::getProgrammerName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "Andreas Herz";
   // END_TODO
}


// .....****...
//
//----------------------------------------------------------------------------
char * Context::getProgrammerURL(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "http://www.FreeGroup.de";
   // END_TODO
}


// .....****...
//
//----------------------------------------------------------------------------
char * Context::getProgrammerMail(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "A.Herz@FreeGroup.de";
   // END_TODO
}

//  Version of this DLL/PlugIn
//
//----------------------------------------------------------------------------
char * Context::getVersion(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "0.3";
   // END_TODO
}

// unused at this moment
//
//----------------------------------------------------------------------------
char * Context::getLabel(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return  "unused";
   // END_TODO
}


// called befor the simulation starts. This is usefull to allocate/block
// some resources (like COM-Ports or somthing else)
//
//----------------------------------------------------------------------------
void Context::onStartCalculate(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
  
   // BEGIN_TODO
   //

   // END_TODO
}


// Called after the simulation has stoped
// Release the resources which are allocated in onStartCalculation(...)
//
//----------------------------------------------------------------------------
void Context::onStopCalculate(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   
   // BEGIN_TODO
   //

   // END_TODO
}

// Initial call of a new object. You can init your additial memory
// (see on getPAramCount() )
//
//----------------------------------------------------------------------------
void Context::initParam(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //

   // END_TODO
}

// If you have stored some pointers in this memory array is this the time
// to release them. DON'T delete 'param' this will done by the framework
//
//----------------------------------------------------------------------------
void Context::cleanupParam(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //

   // END_TODO
}


// calculate your output values
//
//----------------------------------------------------------------------------
int Context::calculate(char *input ,char* lastInput,long inputCount, 
                       char* output, long outputCount,
                       char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   
   CSize s = getInputCountRange();
   if( inputCount<s.cx || inputCount>s.cy )
      return 0;

   // BEGIN_TODO
   //
   long t= GetTickCount();
   
   // check the reset 
   //
   if(IN_RESET)
   {
      output[0] = false;
      output[1] = true;
   }
   // check if a current pulse timed out
   //
   else if((START_TIME+MS_VALUE) < t)
   {
      output[0] = false;
      output[1] = true;
      START_TIME = t;
   }
   // check if a trigger possible
   //
   // condition: negative/positive trigger flank and no pulse should be active
   //
   else if(((!LAST_IN_TRIGGER && IN_TRIGGER && TRIGGER)||(LAST_IN_TRIGGER&& !IN_TRIGGER && !TRIGGER)) && !output[0])
   {
      START_TIME = t;
      output[0]  = true;
      output[1]  = false;
   }

   return 0; // if no redraw of the object are necessary
   //return 1; // if a redraw of the object necessary return 1
   // END_TODO
}

// layout our output pins
// the left/top point of the object is 0/0 
// x increases to the left
// y decreases to the bottom
//
//----------------------------------------------------------------------------
void Context::layoutOutput(long*  xPositions, 
                           long*  yPositions,
                           long   inputCount, 
                           long   outputCount,
                           char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   float yBegin;
   float yOffset;
   int   loop;
   CSize size = getSize(inputCount, outputCount);
   // BEGIN_TODO
   //

   yOffset = size.cy/outputCount;
   yBegin  = yOffset/2;
   for( loop=0; loop <outputCount; loop++)   {
      int xPos = size.cx;
      int yPos = yBegin + yOffset*(loop);
      xPositions[loop] =  xPos;
      yPositions[loop] = -yPos;
   }
   // END_TODO
}

// layout our input pins
// the left/top point of the object is 0/0 
// x increases to the left
// y decreases to the bottom
//
//----------------------------------------------------------------------------
void Context::layoutInput(long*  xPositions, 
                          long*  yPositions,
                          long   inputCount, 
                          long   outputCount,
                          char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));


   float yBegin;
   float yOffset;
   int   loop;
   CSize size = getSize(inputCount, outputCount);

   // BEGIN_TODO
   //
   yOffset = size.cy/ inputCount;
   yBegin  = yOffset/2;
   for( loop=0; loop <inputCount; loop++)   {
      int xPos = -15;
      int yPos = yBegin + yOffset*(loop);
      xPositions[loop] =  xPos;
      yPositions[loop] = -yPos;
   }
   // END_TODO

}

// draw the object to the device context
// the left/top point of the object is 0/0 
// x increases to the left
// y decreases to the bottom
//
//----------------------------------------------------------------------------
bool Context::paint(CDC* pDC,
                    CPoint location,
                    long inputCount, 
                    long outputCount,
                    char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));


   m_bigFont.SetDC(pDC->m_hDC);
   m_smallFont.SetDC(pDC->m_hDC);

   // BEGIN_TODO
   //
   long xSize      = getSize(inputCount,outputCount).cx;
   long ySize      = getSize(inputCount,outputCount).cy;
   long yOffsetOut = ySize/outputCount;
   long yOffsetIn  = ySize/inputCount;
   long yBegin     = 0;

   pDC->SetBkMode(TRANSPARENT);

   // paint the frame
   //
   pDC->Rectangle(location.x,location.y,location.x + xSize,location.y- ySize);

   // paint the pulse 
   //
   long xAdd = location.x + xSize/2-40;
   long yAdd = location.y - ySize/2;
   if(TRIGGER)
   {
      pDC->MoveTo(xAdd   , yAdd   );
      pDC->LineTo(xAdd+20, yAdd  );
      pDC->LineTo(xAdd+20, yAdd+20);
      pDC->LineTo(xAdd+55, yAdd+20);
   }
   else
   {
      pDC->MoveTo(xAdd+20, yAdd+20);
      pDC->LineTo(xAdd+55, yAdd+20);
      pDC->LineTo(xAdd+55, yAdd   );
      pDC->LineTo(xAdd+80, yAdd   );
   }

   // select the small font
   //
   CFont*oldFont=pDC->SelectObject(&m_smallFont);

   // write output labels
   //
   yBegin  = location.y-(yOffsetOut/2)+(m_smallFont.GetHeight()/2);
   pDC->TextOut( location.x-33+xSize, yBegin            , " Q");
   pDC->TextOut( location.x-33+xSize, yBegin-yOffsetOut , "-Q");

   // write input labels
   //
   yBegin  = location.y-(yOffsetIn/2)+(m_smallFont.GetHeight()/2);
   pDC->TextOut( location.x+10, yBegin                     ,"A");
   pDC->TextOut( location.x+10, yBegin-yOffsetIn           ,"R");

   // restore the old font
   //
   pDC->SelectObject(oldFont);

// return true;    // The parent object draw nothing (no ports, .....)
                   // You must handle all the painting here.
   return false;   // the parent object draw additional objects like the ports.

   //
   // END_TODO
}



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//                           DON'T TOUCH THIS CODE                            //
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
extern "C" bool LINKAGE cf_create_interface(const char *iid,IPluginBase **iface){
//----------------------------------------------------------------------------

	*iface = NULL;

	Context *ptr;

	try	{
		ptr = new Context;

      ptr->QueryInterface(iid, iface);
		ptr->Destroy();
	}
	catch(...){
		(*iface )  = NULL;
	}

	return (*iface ) != NULL;
}

//----------------------------------------------------------------------------
Context::Context(void): m_bigFont("Arial"), m_smallFont("Arial") {
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   m_bigFont.SetHeight(BIG_FONT);
   m_smallFont.SetHeight(SMALL_FONT);

   m_refCount  = 1;
}



//----------------------------------------------------------------------------
bool Context::QueryInterface(const char *iid, IPluginBase **iface){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   *iface = NULL;

	if (::strcmp(iid, "IObjectInfo") == 0)
		*iface = static_cast<IObjectInfo*>(this);
	else if (::strcmp(iid, "IObjectWorker") == 0)
		*iface = static_cast<IObjectWorker*>(this);
	else if (::strcmp(iid, "IObjectContext") == 0)
		*iface = (IPluginBase*)(IObjectInfo*)this;
	else if (::strcmp(iid, "IPluginBase") == 0)
		*iface = static_cast<IObjectInfo*>(this);

	if (*iface != NULL)
		m_refCount++;

	return *iface != NULL;
}

//----------------------------------------------------------------------------
void Context::Destroy(void){
//----------------------------------------------------------------------------
  AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

	if (--m_refCount == 0){
      delete this;
	}
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
