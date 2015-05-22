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


CWinApp theApp;
#define LINKAGE		__declspec(dllexport)


//----------------------------------------------------------------------------
int Context::doConfigure(HWND view, char*  param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // 0  => display the generic DigitalSimulator Dialog
   // 1  => no display neccessary......you have display our own
   return 0;
}


//----------------------------------------------------------------------------
CSize Context::getInputCountRange(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(3,3);
   // END_TODO
}; 


//----------------------------------------------------------------------------
CSize Context::getOutputCountRange(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(10,10);
   // END_TODO
}; 


//----------------------------------------------------------------------------
CSize Context::getSize(long inputCount, long outputCount){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(200,70+20+70*outputCount);
   // END_TODO
}; 

//----------------------------------------------------------------------------
long Context::getParamCount(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return 1;
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getDescription(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "Dezimal counter\r\n\r\n"
          "Counts from 0-9 and sets the corresponding output\r\n"
          "to HIGH. Only one output will be set to HIGH.";
         
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getGroup(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECTGROUP.COUNTER";
   // END_TODO
}

//----------------------------------------------------------------------------
char* Context::getKey(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "Dezimal Zähler";
   // END_TODO
}

//----------------------------------------------------------------------------
char* Context::getName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECT.DECIMALCOUNTER";
   // END_TODO
}

//----------------------------------------------------------------------------
char * Context::getProgrammerName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "Andreas Herz";
   // END_TODO
}


//----------------------------------------------------------------------------
char * Context::getProgrammerURL(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "http://www.FreeGroup.de";
   // END_TODO
}

//----------------------------------------------------------------------------
char * Context::getProgrammerMail(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "A.Herz@FreeGroup.de";
   // END_TODO
}

//----------------------------------------------------------------------------
char * Context::getVersion(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "0.3";
   // END_TODO
}

//----------------------------------------------------------------------------
char * Context::getLabel(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return  "unused";
   // END_TODO
}


//----------------------------------------------------------------------------
void Context::onStartCalculate(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
  
   // BEGIN_TODO
   //

   // END_TODO
}


//----------------------------------------------------------------------------
void Context::onStopCalculate(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   
   // BEGIN_TODO
   //

   // END_TODO
}


//----------------------------------------------------------------------------
void Context::initParam(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //

   // END_TODO
}


//----------------------------------------------------------------------------
void Context::cleanupParam(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //

   // END_TODO
}



//----------------------------------------------------------------------------
int Context::calculate(char *input ,char* lastInput,long inputCount, 
                       char* output, long outputCount,
                       char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   /*
   CSize s = getInputCountRange();
   if( inputCount<s.cx || inputCount>s.cy )
      return 0;
	*/

   // BEGIN_TODO
   //

   // ist gerade das Reset aktiv?
   //
   if(input[0]==0){
      // positive Flanke
      //
      if( (input[1]==1) && (input[1]!=lastInput[1]) ){
         if(input[2]!=1){
            // Hoch Zählen
            param[0]++;
            if(param[0]<0 || param[0]>=outputCount)
               param[0]=0;
         }
         else{
            // runter Zählen
            param[0]--;
            if(param[0]<0 || param[0]>=outputCount)
               param[0]=(outputCount-1);
         }
         // runter Zählen
         memset(output, 0,outputCount);
         output[param[0]]=1;
      }
   }
   else{
      // Reset
      memset(output, 0,outputCount);
      output[0] = 1;
      param[0]  = 0;
   }

   return 0;
   // END_TODO
}


//----------------------------------------------------------------------------
void Context::layoutOutput(long*  xPositions, 
                           long*  yPositions,
                           long   inputCount, 
                           long   outputCount,
                           char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //

   float  yOffset = 70;

   for(long loop=0 ;loop <outputCount ; loop++)   {
      xPositions[loop] = getSize(inputCount, outputCount).cx;
      yPositions[loop] = -(70+20+35) -yOffset*loop;
   }

   // END_TODO
}

//----------------------------------------------------------------------------
void Context::layoutInput(long*  xPositions, 
                          long*  yPositions,
                          long   inputCount, 
                          long   outputCount,
                          char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
//   float  yOffset = getSize(inputCount, outputCount).cy / (inputCount+1);

   xPositions[0] = -16;
   yPositions[0] = -15;

   xPositions[1] = -16;
   yPositions[1] = -35;

   xPositions[2] = -16;
   yPositions[2] = -55;
   // END_TODO
}


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
   long yOffset=0;
   long xSize  =getSize(inputCount,outputCount).cx;
   long ySize  =getSize(inputCount,outputCount).cy;
   pDC->SetBkMode(TRANSPARENT);

   pDC->Rectangle(location.x      , location.y-yOffset , location.x+ xSize  , location.y- yOffset-72);
   yOffset+=70;
   pDC->Rectangle(location.x + 10 , location.y-yOffset, location.x+ xSize-10, location.y- yOffset-20);
   yOffset+=20;

   // für jeden Ausgang ein eigenes Feld zeichnen
   //
   for(int loop=0; loop<outputCount; loop++){
      pDC->Rectangle(location.x,location.y-yOffset,location.x+ xSize,location.y-yOffset-70);
      yOffset+=70;
   }

   CFont*oldFont=pDC->SelectObject(&m_bigFont);
   pDC->TextOut( location.x+ 48, location.y-5,"Dezimal" );

   pDC->SelectObject(&m_smallFont);
   pDC->TextOut( location.x+ 8, location.y,"R"     );
   pDC->TextOut( location.x+ 8, location.y-22,"CL"     );
   pDC->TextOut( location.x+ 8, location.y-43,"+/-" );


   pDC->SelectObject(oldFont);

// return true;    // The parent object draw nothing (no ports, .....)
                   // You must handle all the painting here.

   return false;   // the parent object draw additional objects like the ports.

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
