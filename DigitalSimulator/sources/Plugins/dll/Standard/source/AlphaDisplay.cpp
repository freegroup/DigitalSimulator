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

#define BREITE        120
#define HOEHE         250

#define INPUT_COUNT   16

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
   return CSize(0,0);
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
   return INPUT_COUNT;
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getDescription(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "Alphanumerisches Display\r\n\r\n"
          "Simple and 'bad' design for a alphanumerisches display\r\n"
          ".....redesign this object please!!!!!!!!!!!!";
          
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getGroup(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECTGROUP.DISPLAY";
   // END_TODO
}

//----------------------------------------------------------------------------
char* Context::getKey(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "alphanumerische Anzeige";
   // END_TODO
}


//----------------------------------------------------------------------------
char* Context::getName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECT.ALPHADISPLAY";
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
   memcpy(param,input,inputCount);

   // return 1   => redraw of the object by the frame work
   // return 0   => no redraw neccessary
   //
   // if the new value equal to the old value => No redraw
   // neccessary
   return memcmp(input, lastInput,inputCount)==0?0:1;


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

   // BEGIN_TODO
   //

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

   pDC->Rectangle(location.x , location.y, location.x+ xSize, location.y-ySize);

   // A
   if(param[0])
      RECTANGLE(10,5,47,10);
   // b
   if(param[1])
      RECTANGLE(53,5,90,10);
   // c
   if(param[2])
      RECTANGLE(80,12,90,45);
   // d
   if(param[3])
      RECTANGLE(80,55,90,89);
   // e
   if(param[4])
      RECTANGLE(53,90,90,95);
   // f
   if(param[5])
      RECTANGLE(10,90,47,95);
   // g
   if(param[6])
      RECTANGLE(10,55,20,89);
   // h
   if(param[7])
      RECTANGLE(10,12,20,45);
   // i
   if(param[8]){
      pDC->MoveTo(XPOS(22),YPOS(12));   
      pDC->LineTo(XPOS(43),YPOS(40));
      pDC->LineTo(XPOS(43),YPOS(45));
      pDC->LineTo(XPOS(22),YPOS(17));
      pDC->LineTo(XPOS(22),YPOS(12));
   }
   // j
   if(param[9])
      RECTANGLE(43,12,55,45);
   // k
   if(param[10]){
      pDC->MoveTo(XPOS(57),YPOS(45));   
      pDC->LineTo(XPOS(57),YPOS(40));
      pDC->LineTo(XPOS(79),YPOS(12));
      pDC->LineTo(XPOS(79),YPOS(17));
      pDC->LineTo(XPOS(57),YPOS(45));
   }
   // l
   if(param[11])
      RECTANGLE(52,46,90,53);
   // m
   if(param[12]){
      pDC->MoveTo(XPOS(57),YPOS(60));   
      pDC->LineTo(XPOS(57),YPOS(55));
      pDC->LineTo(XPOS(79),YPOS(85));
      pDC->LineTo(XPOS(79),YPOS(90));
      pDC->LineTo(XPOS(57),YPOS(60));
   }
   // n
   if(param[13])
      RECTANGLE(45,55,55,89);
   // o
   if(param[14]){
      pDC->MoveTo(XPOS(43),YPOS(55));   
      pDC->LineTo(XPOS(43),YPOS(60));
      pDC->LineTo(XPOS(22),YPOS(90));
      pDC->LineTo(XPOS(22),YPOS(85));
      pDC->LineTo(XPOS(43),YPOS(55));
   }
   // p
   if(param[15])
      RECTANGLE(10,46,47,53);

   
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
