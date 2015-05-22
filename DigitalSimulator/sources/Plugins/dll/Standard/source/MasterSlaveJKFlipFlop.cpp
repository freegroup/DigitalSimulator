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
#include <math.h>


#include "stdafx.h"
#include "Autofont.h"
#include "Context.h"


CWinApp theApp;
#define LINKAGE		__declspec(dllexport)

#define BREITE        115
#define HOEHE         200

#define INPUT_COUNT   3
#define OUTPUT_COUNT  2

#define PROZENT(x,y)  ((x/100.0)*y)
#define RECTANGLE(l,t,r,b)   pDC->Rectangle(location.x+PROZENT(xSize,l) , location.y - PROZENT(ySize,t), location.x+ PROZENT(xSize,r), location.y-PROZENT(ySize,b));
#define XPOS(value)  (location.x+ PROZENT(xSize,value))
#define YPOS(value)  (location.y- PROZENT(ySize,value))

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
   return CSize(INPUT_COUNT,INPUT_COUNT);
   // END_TODO
}; 


//----------------------------------------------------------------------------
CSize Context::getOutputCountRange(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(OUTPUT_COUNT,OUTPUT_COUNT);
   // END_TODO
}; 


//----------------------------------------------------------------------------
CSize Context::getSize(long inputCount, long outputCount){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(BREITE,HOEHE);
   // END_TODO
}; 


//----------------------------------------------------------------------------
long Context::getParamCount(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   // to save the last J and K state at the rising C
   return 2; 
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getDescription(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "MasterSlave JK-FlipFlop\r\n\r\n"
          "The MasterSlave JK-FlipFlop will bee triggered\r\n"
          "with the high and low flank of the clock input 1C.";
          
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getGroup(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECTGROUP.FLIPFLOP";
   // END_TODO
}

//----------------------------------------------------------------------------
char* Context::getKey(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "MasterSlave JK-FlipFlop";
   // END_TODO
}


//----------------------------------------------------------------------------
char* Context::getName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECT.FLIPFLOP.MASTERSLAVE.JK";
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
   return "0.2";
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

   // BEGIN_TODO
   //

   // rising flank on the clock input
   // detection
   //
   if(input[1] && !lastInput[1]) {
      param[0] = input[0]; // save the current J state
      param[1] = input[2]; // save the current K state
   }

   // falling flank on the clock input
   // detection
   //
   if(!input[1] && lastInput[1]){
      // there are four possible case to change the state 
      // of the FlipFlop
      // 

      // 1. J=LOW  K=LOW   -> Q = Qn     (no change)
      if((!input[0] && (input[0] == param[0])) && (!input[2] && (input[2] == param[1]))){
         return 0;
      }

      // 2. J=HIGH K=LOW   -> Q = HIGH
      if((input[0] && (input[0] == param[0])) && (!input[2] && (input[2] == param[1]))){
         output[0] = 1;
         output[1] = 0;
         return 0;
      }

      // 3. J=LOW K=HIGH   -> Q = LOW
      if((!input[0] && (input[0] == param[0])) && (input[2] && (input[2] == param[1]))){
         output[0] = 0;
         output[1] = 1;
         return 0;
      }

      // 4. J=HIGH K=HIGH   -> Q = HIGH
      if((input[0] && (input[0] == param[0])) && (input[2] && (input[2] == param[1]))){
         output[0] = !output[0];
         output[1] = !output[0];
         return 0;
      }
   }

   // return 1   => redraw of the object by the frame work
   // return 0   => no redraw neccessary
   //
   // if the new value equal to the old value => No redraw
   // neccessary
   return 0;


   // END_TODO
}


//----------------------------------------------------------------------------
void Context::layoutOutput(long*  xPositions, 
                           long*  yPositions,
                           long   inputCount, 
                           long   outputCount,
                           char*  param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   float yBegin;
   float yOffset;
   int   loop;
   // BEGIN_TODO
   //

   yOffset = HOEHE/ (outputCount+1);
   yBegin  = yOffset;
   for( loop=0; loop <outputCount; loop++)   {
      int xPos = BREITE;
      int yPos = yBegin + yOffset*(loop);
      xPositions[loop] =  xPos;
      yPositions[loop] = -yPos;
   }
   // END_TODO
}

//----------------------------------------------------------------------------
void Context::layoutInput(long* xPositions, 
                          long* yPositions,
                          long  inputCount, 
                          long  outputCount,
                          char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   float yBegin;
   float yOffset;
   int   loop;
   // BEGIN_TODO
   //

   yOffset = HOEHE/ (inputCount+1);
   yBegin  = yOffset;
   for( loop=0; loop <inputCount; loop++)   {
      int xPos = -15;
      int yPos = yBegin + yOffset*(loop);
      xPositions[loop] =  xPos;
      yPositions[loop] = -yPos;
   }
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
   long xSize  = getSize(inputCount,outputCount).cx;
   long ySize  = getSize(inputCount,outputCount).cy;
   pDC->SetBkMode(TRANSPARENT);
   pDC->SelectObject(&m_smallFont);

   pDC->Rectangle(location.x , location.y, location.x+ xSize, location.y-ySize);

   //  >
   //
   pDC->MoveTo(XPOS( 0), YPOS(45));   
   pDC->LineTo(XPOS(20), YPOS(50));   
   pDC->LineTo(XPOS( 0), YPOS(55));   

   // Q
   //
   pDC->MoveTo(XPOS(80), YPOS(15));   
   pDC->LineTo(XPOS(90), YPOS(15));   
   pDC->LineTo(XPOS(90), YPOS(25));   

   // Qnot
   //
   pDC->MoveTo(XPOS(80), YPOS(75));   
   pDC->LineTo(XPOS(90), YPOS(75));   
   pDC->LineTo(XPOS(90), YPOS(85));   

   pDC->TextOut( location.x+ 18 , YPOS(10)                  , "J" );
   pDC->TextOut( location.x+ 28, YPOS(50) + (SMALL_FONT/2) , "1C");
   pDC->TextOut( location.x+ 18 , YPOS(90) + SMALL_FONT     , "K" );

   
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
