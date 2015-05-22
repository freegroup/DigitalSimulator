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

#define BREITE        200
#define ADDRESS       500
#define BIT_ELEMENT   70
#define ZWISCHEN      20

#define ADDRESS_COUNT 4
#define BIT_COUNT     4

#define HOEHE         ADDRESS+ZWISCHEN+(BIT_ELEMENT*BIT_COUNT)

#define INPUT_COUNT   (ADDRESS_COUNT+(2*BIT_COUNT)+1+1)
#define OUTPUT_COUNT  8


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
   return 0;
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getDescription(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "ALU (ArithmeticLogicUnit)\r\n\r\n"
          "This Object implements the function of the 4 Bit ALU 74181";
          
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getGroup(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECTGROUP.ALU";
   // END_TODO
}

//----------------------------------------------------------------------------
char* Context::getKey(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "74181";
   // END_TODO
}


//----------------------------------------------------------------------------
char* Context::getName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECT.74181";
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
int Context::calculate(char *input , char* lastInput,long inputCount, 
                       char* output, long  outputCount,
                       char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));
   
   // BEGIN_TODO
   //
   int a0,a1,a2,a3,b0,b1,b2,b3,s0,s1,s2,s3,ba,cn,
       i01,i02,i03,i04,i05,i06,i07,i08,i09,i10,
       i11,i12,i13,i14,i15,i16,i17,i18,i19,i20,
       i21,i22,i23,i24,i25,i26,i27,i28,i29,i30,
       i31,i32,i33,i34,i35,i36,i37,i38,i39,i40,
       i41,i42,i43,i44,i45,i46,i47,i48,i49,i50,
       i51,i52,i53,i54,i55,i56,i57,i58,i59,i60,
       i61,i62,i63;
   
   
   // zuerst kommen die a-Eingänge, dann die b-Eingänge, schließlich
   // die Steuereingänge s0 bis cn
   //
   a0=input[0];
   a1=input[1];
   a2=input[2];
   a3=input[3];
   b0=input[4];
   b1=input[5];
   b2=input[6];
   b3=input[7];
   s0=input[8];
   s1=input[9];
   s2=input[10];
   s3=input[11];
   ba=input[12];
   cn=input[13];
   // erste Reihe
   i01=1-ba;
   i02=1-b0;
   i03=1-b1;
   i04=1-b2;
   i05=1-b3;
   i06=a0;
   i07=b0 & s0;
   i08=i02 & s1;
   i09=i02 & s2 & a0;
   i10=a0 & s3 & b0;
   i11=a1;
   i12=b1 & s0;
   i13=s1 & i03;
   i14=i03 & s2 & a1;
   i15=a1 & b1 & s3;
   i16=a2;
   i17=b2 & s0;
   i18=s1 & i04;
   i19=i04 & s2 & a2;
   i20=a2 & s3 & b2;
   i21=a3;
   i22=b3 & s0;
   i23=s1 & i05;
   i24=i05 & s2 & a3;
   i25=a3 & s3 & b3;
   // zweite Reihe
   i26=1-(i06 | i07 | i08);
   i27=1-(i09 | i10);
   i28=1-(i11 | i12 | i13);
   i29=1-(i14 | i15);
   i30=1-(i16 | i17 | i18);
   i31=1-(i19 | i20);
   i32=1-(i21 | i22 | i23);
   i33=1-(i24 | i25);
   // dritte Reihe
   i34=(i26 & (1-i27)) | (i27 & (1-i26));
   i35=(i28 & (1-i29)) | (i29 & (1-i28));
   i36=(i30 & (1-i31)) | (i31 & (1-i30));
   i37=(i32 & (1-i33)) | (i33 & (1-i32));
   // vierte Reihe
   i38=1-(i01 & cn);
   i39=i01 & i26;
   i40=i01 & i27 & cn;
   i41=i01 & i28;
   i42=i01 & i26 & i29;
   i43=i01 & i29 & i27 & cn;
   i44=i01 & i30;
   i45=i01 & i28 & i31;
   i46=i01 & i26 & i31 & i29;
   i47=i01 & i31 & i29 & i27 & cn;
   i48=i27 & i29 & i31 & i33;
   i49=cn & i27 & i29 & i31 & i33;
   i50=i26 & i29 & i31 & i33;
   i51=i28 & i31 & i33;
   i52=i30 & i33;
   i53=i32;
   // fünfte Reihe
   i54=1-(i39 | i40);
   i55=1-(i41 | i42 | i43);
   i56=1-(i44 | i45 | i46 | i47);
   i57=1-(i50 | i51 | i52 | i53);
   // sechste Reihe
   i58=(i38 & (1-i34)) | (i34 & (1-i38));
   i59=(i54 & (1-i35)) | (i35 & (1-i54));
   i60=(i55 & (1-i36)) | (i36 & (1-i55));
   i61=(i56 & (1-i37)) | (i37 & (1-i56));
   i62=1-(i49 & i57);
   i63=i58 & i59 & i60 & i61;
   // nun die Ausgabe
   // zuerst die 4 Funktionsausgänge:	
   output[0] = i58;
   output[1] = i59;
   output[2] = i60;
   output[3] = i61;
   // P
   output[4] = i48;
   // G
   output[5] = i57;
   // A=B
   output[6] = i63;
   // CYn+4
   output[7] = i62;

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

   // BEGIN_TODO
   //

   // OUTPUT Q0-Q3
   //
   float yBegin;
   float yOffset;
   int   xOffset = getSize(inputCount,outputCount).cx-5;
   yBegin  = ADDRESS + ZWISCHEN + (BIT_ELEMENT/2);
   yOffset = BIT_ELEMENT;
   for(int loop=0; loop <4; loop++)   {
      int yPos = yBegin + yOffset*loop;
      xPositions[loop] =  xOffset;
      yPositions[loop] = -yPos;
   }

   // P, G, A=B, CYn+4
   //
   yOffset = ADDRESS / 5;
   for( loop=0; loop < 4; loop++)   {
      int xPos = BREITE;
      int yPos = yOffset*(loop+1);
      xPositions[loop+4] =  xPos;
      yPositions[loop+4] = -yPos;
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
   // INPUT A
   //
   yBegin  = ADDRESS + ZWISCHEN + (BIT_ELEMENT/4);
   yOffset = BIT_ELEMENT;
   for( loop=0; loop <4; loop++)   {
      int xPos = -20;
      int yPos = yBegin + yOffset*(loop);
      xPositions[loop] =  xPos;
      yPositions[loop] = -yPos;
   }

   // INPUT B
   //
   yBegin  = ADDRESS + ZWISCHEN + ((BIT_ELEMENT/4.0)*3.0);
   yOffset = BIT_ELEMENT;
   for( loop=4; loop <8; loop++)   {
      int xPos = -20;
      int yPos = yBegin + yOffset*(loop-4);
      xPositions[loop] =  xPos;
      yPositions[loop] = -yPos;
   }

   // Addressleitungen, BA, CYn
   //
   yOffset = ADDRESS/ (ADDRESS_COUNT+3);
   for( loop=8; loop <inputCount; loop++)   {
      int xPos = -15;
      int yPos = yOffset*(loop-7);
      xPositions[loop] =  xPos;
      yPositions[loop] = -yPos;
   }

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

   // für jedes EingangsBit ein eigenes Feld zeichnen
   //
   for(int loop=0; loop<BIT_COUNT; loop++){
      pDC->Rectangle(location.x,location.y-yOffset,location.x+ xSize,location.y-yOffset-BIT_ELEMENT);
      yOffset+=BIT_ELEMENT;
   }

   CFont*oldFont=pDC->SelectObject(&m_bigFont);
   pDC->TextOut( location.x+ 60, location.y-5,"ALU" );
   pDC->TextOut( location.x+ 40, location.y-15-BIG_FONT,"74181" );

   // Addressleitungen 0-3
   float yDiff = (ADDRESS / (ADDRESS_COUNT +3))*(ADDRESS_COUNT-1);
   yOffset = ADDRESS/(ADDRESS_COUNT+3);
   pDC->TextOut( location.x+35, location.y-yOffset-(yDiff/2)+(BIG_FONT/2),"S0-S3" );
   pDC->MoveTo(location.x+10,location.y-yOffset);   
   pDC->LineTo(location.x+20,location.y-yOffset-20);   
   pDC->LineTo(location.x+20,location.y-yOffset-(yDiff/2-20));   
   pDC->LineTo(location.x+30,location.y-yOffset-(yDiff/2));   
   pDC->LineTo(location.x+20,location.y-yOffset-(yDiff/2+20));   
   pDC->LineTo(location.x+20,location.y-yOffset-yDiff+20);   
   pDC->LineTo(location.x+10,location.y-yOffset-yDiff);   

   pDC->SelectObject(&m_smallFont);

   // BA
   float y;
   y = ADDRESS/(ADDRESS_COUNT+3)*(ADDRESS_COUNT+1)- SMALL_FONT/2;
   pDC->TextOut( location.x+8, location.y-y,"BA");


   // CYn
   y = ADDRESS/(ADDRESS_COUNT+3)*(ADDRESS_COUNT+2)- SMALL_FONT/2;
   pDC->TextOut( location.x+8, location.y-y,"CYn");

   // OUT P
   y = ((ADDRESS/5)*1)- SMALL_FONT/2;
   pDC->TextOut( location.x+BREITE-35, location.y-y,"P");

   // OUT G
   y = ((ADDRESS/5)*2)- SMALL_FONT/2;
   pDC->TextOut( location.x+BREITE-35, location.y-y,"G");

   // OUT A=B
   y = ((ADDRESS/5)*3)- SMALL_FONT/2;
   pDC->TextOut( location.x+BREITE-75, location.y-y,"A=B");

   // OUT CYn+4
   y = ((ADDRESS/5)*4)- SMALL_FONT/2;
   pDC->TextOut( location.x+BREITE-100, location.y-y,"CYn+4");

   pDC->SelectObject(oldFont);   // END_TODO

   
// return true;    // The parent object draw nothing (no ports, .....)
                   // You must handle all the painting here.

   return false;   // the parent object draw additional objects like the ports.
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
