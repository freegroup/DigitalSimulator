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
#include "Context.h"


CWinApp theApp;
#define LINKAGE		__declspec(dllexport)

#define BREITE        200
#define ADDRESS       500
#define BIT_ELEMENT   50
#define ZWISCHEN      20


#define ADDRESS_COUNT 14
#define BIT_COUNT     8
#define MEMORY_COUNT  16384  


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
   return CSize(ADDRESS_COUNT+BIT_COUNT+2,ADDRESS_COUNT+BIT_COUNT+2);
   // END_TODO
}; 


//----------------------------------------------------------------------------
CSize Context::getOutputCountRange(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(BIT_COUNT,BIT_COUNT);
   // END_TODO
}; 


//----------------------------------------------------------------------------
CSize Context::getSize(long inputCount, long outputCount){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return CSize(BREITE,ADDRESS+ZWISCHEN+(BIT_ELEMENT*BIT_COUNT));
   // END_TODO
}; 


//----------------------------------------------------------------------------
long Context::getParamCount(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return MEMORY_COUNT;
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getDescription(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "RAM\r\n\r\n"
          "This is a RAM with 16k. This is only a demostration of\r\n"
          "the usage/creation of PlugIn-Objects. For more information\r\n"
          "see on www.digital-simulator.de";
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getGroup(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECTGROUP.MEMORY";
   // END_TODO
}

//----------------------------------------------------------------------------
char * Context::getKey(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "RAM 16k 8 bit";
   // END_TODO
}


//----------------------------------------------------------------------------
char * Context::getName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECT.MEMORY.16K.8.BIT";
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
   // Adresse auf die zugegriffen werden soll bestimmen
   //
   if(input[ADDRESS_COUNT]){     // chipSelect
      if(input[ADDRESS_COUNT+1]){  // read or write
         // read
         int loop;
         long address=0;
	      for (loop =0; loop<ADDRESS_COUNT; loop++)   {
            if(input[loop]){
               address += pow(2,loop);
            }
         }
         output[0] = param[address] & 1;
         output[1] = param[address] & 2;
         output[2] = param[address] & 4;
         output[3] = param[address] & 8;
         output[4] = param[address] & 16;
         output[5] = param[address] & 32;
         output[6] = param[address] & 64;
         output[7] = param[address] & 128;
      }
      else{
         // write
         int  loop;
         long address=0;
	      for (loop =0; loop<ADDRESS_COUNT; loop++){
            if(input[loop]){
               address += pow(2,loop);
            }
         }

         long value=0;
	      for (loop =ADDRESS_COUNT+2; loop<(ADDRESS_COUNT+BIT_COUNT+2); loop++){
            if(input[loop]){
               value += pow(2,loop-(ADDRESS_COUNT+2));
            }
         }
         param[address]=value;
      }
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
   float yBegin;
   float yOffset;
   int   xOffset = getSize(inputCount,outputCount).cx-5;
   yBegin  = ADDRESS + ZWISCHEN + (BIT_ELEMENT/2);
   yOffset = BIT_ELEMENT;
   for(int loop=0; loop <outputCount; loop++)   {
      int yPos = yBegin + yOffset*loop;
      xPositions[loop] =  xOffset;
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

   // Addressleitungen, CS, R/W
   //
   yBegin    = 0;
   yOffset = ADDRESS/ (ADDRESS_COUNT+3);
   for( loop=0; loop <(ADDRESS_COUNT+2); loop++)   {
      int xPos = -10;
      int yPos = yBegin + yOffset*(loop+1);
      xPositions[loop] =  xPos;
      yPositions[loop] = -yPos;
   }

   // INPUT
   //
   yBegin    = ADDRESS + ZWISCHEN + (BIT_ELEMENT/2);
   yOffset = BIT_ELEMENT;
   for( loop=(ADDRESS_COUNT+2); loop <inputCount; loop++)   {
      int xPos = -20;
      int yPos = yBegin + yOffset*(loop-(ADDRESS_COUNT+2));
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
   long yOffset=0;
   long xSize  =getSize(inputCount,outputCount).cx;
   long ySize  =getSize(inputCount,outputCount).cy;
   pDC->SetBkMode(TRANSPARENT);


   pDC->Rectangle(location.x      , location.y-yOffset , location.x+ xSize  , location.y- yOffset-ADDRESS);
   yOffset+=ADDRESS;
   pDC->Rectangle(location.x + 10 , location.y-yOffset, location.x+ xSize-10, location.y- yOffset-ZWISCHEN);
   yOffset+=ZWISCHEN;

   // für jeden Ausgang ein eigenes Feld zeichnen
   //
   for(int loop=0; loop<outputCount; loop++){
      pDC->Rectangle(location.x,location.y-yOffset,location.x+ xSize,location.y-yOffset-BIT_ELEMENT);
      yOffset+=BIT_ELEMENT;
   }

   CFont*oldFont=pDC->SelectObject(&m_bigFont);
   pDC->TextOut( location.x+ 60, location.y-5,"RAM" );
   pDC->TextOut( location.x+ 40, location.y-15-BIG_FONT,"16k 8bit" );

   // Addressleitungen 0-13
   float yDiff = (ADDRESS / (ADDRESS_COUNT +2))*(ADDRESS_COUNT-2);
   yOffset = ADDRESS/(ADDRESS_COUNT+3);
   pDC->TextOut( location.x+35, location.y-yOffset-(yDiff/2)+(BIG_FONT/2),"A0-A13" );
   pDC->MoveTo(location.x+10,location.y-yOffset);   
   pDC->LineTo(location.x+20,location.y-yOffset-20);   
   pDC->LineTo(location.x+20,location.y-yOffset-(yDiff/2-20));   
   pDC->LineTo(location.x+30,location.y-yOffset-(yDiff/2));   
   pDC->LineTo(location.x+20,location.y-yOffset-(yDiff/2+20));   
   pDC->LineTo(location.x+20,location.y-yOffset-yDiff+20);   
   pDC->LineTo(location.x+10,location.y-yOffset-yDiff);   

   pDC->SelectObject(&m_smallFont);

   // ChipSelect   14
   float y;
   y = ADDRESS/(ADDRESS_COUNT+3)*(ADDRESS_COUNT+1)- SMALL_FONT/2;
   pDC->TextOut( location.x+8, location.y-y,"CS");


   // READ/WRITE   15
   y = ADDRESS/(ADDRESS_COUNT+3)*(ADDRESS_COUNT+2)- SMALL_FONT/2;
   pDC->TextOut( location.x+8, location.y-y,"R / W");


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
