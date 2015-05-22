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
#include  <io.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <iomanip>
#include <math.h>
#include <list>


#include "stdafx.h"
#include "Autofont.h"
#include "Context.h"

#pragma warning(disable : 4786)
#include <fstream>
#include <string>


CWinApp theApp;
#define LINKAGE		__declspec(dllexport)

#define BREITE        115
#define HOEHE         400

#define INPUT_COUNT   2
#define OUTPUT_COUNT  16

#define PROZENT(x,y)  ((x/100.0)*y)
#define RECTANGLE(l,t,r,b)   pDC->Rectangle(location.x+PROZENT(xSize,l) , location.y - PROZENT(ySize,t), location.x+ PROZENT(xSize,r), location.y-PROZENT(ySize,b));
#define XPOS(value)  (location.x+ PROZENT(xSize,value))
#define YPOS(value)  (location.y- PROZENT(ySize,value))

typedef std::list<char*> ByteSequenze;

//----------------------------------------------------------------------------
int Context::doConfigure(HWND view, char*  param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // 0  => display the generic DigitalSimulator Dialog
   // 1  => no display neccessary......you have display our own
   char        *defExtension;
   char        *InitialFileName;
   char        *filter;
   static char  fileName[10000];

   defExtension     = ".bit";
   InitialFileName  = "*.bit";
   filter           = "*.bit";

   CFileDialog  dlg( TRUE, defExtension,InitialFileName,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter );

   if(dlg.DoModal()==IDOK){
      CString path = dlg.GetPathName();
      sprintf(param,(LPCSTR)path);
      initParam(param);
   }


   return 1;
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
   // 
   return _MAX_PATH + 2*sizeof(void*); 
   // END_TODO
}

//----------------------------------------------------------------------------
char*  Context::getDescription(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "16-Bit Sequenzer\r\n\r\n"
          "This is a 'bit-sequenzer' which reads the 16 bits from a \r\n"
          "external file and redirect them to the output.\r\n"
          "At every high impulse of the clock the next line in the\r\n"
          "file will be selected for the output.\r\n"
          "\r\n"
          "Example of the fileformat which can read from this object are:\r\n"
          "0000000000000000\r\n"
          "0100000000000000\r\n"
          "0000100000000000\r\n"
          "0000000000000000\r\n"
          "0000100000000000\r\n"
          "# this line will be ignored\r\n"
          "00100000\r\n"
          "# and the next lines will be filled up with the missing '0'\r\n"
          "01\r\n"
          "00000000\r\n"
          "000000\r\n"
          "\r\n"
          "\r\n"
          "Douple click to the bit-reader object and select in the file-open\r\n"
          "dialog the file with the explained format.";
          
          
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
char* Context::getKey(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "file to output (16-bit)";
   // END_TODO
}


//----------------------------------------------------------------------------
char* Context::getName(){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   return "OBJECT.FILEOUTPUT.16.BIT";
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
   if(param==NULL || strlen(param)==0)
      return;

   int outcount = getOutputCountRange().cx;
   memset(param +getParamCount()-  sizeof(void*),0,2*sizeof(void*));

   // Check for existence 
   //
   if( (_access( param, 0 )) != -1 ){
      // Check for write permission
      //
      if( (_access( param, 4 )) != -1 ){
	      std::string   line;
	      std::ifstream inFile(param);

	      if(inFile.is_open()==true)	{
            ByteSequenze *sequenz        = new ByteSequenze();
            ByteSequenze::iterator *iter = new ByteSequenze::iterator;
            memcpy((param+getParamCount()-   sizeof(void*)),(void*)&sequenz,sizeof(void*));
            memcpy((param+getParamCount()- 2*sizeof(void*)),(void*)&iter,sizeof(void*));

            // read all lines in the file
            //
		      while(!inFile.eof())
            {
			      std::getline(inFile ,line,'\n');
               if(line.length() >0)
               {
                  if(line[0]!='#')
                  {
                     // scann all characters of a line
                     //
                     char *buffer= new char[outcount];
                     memset(buffer,0,outcount);
                     for(int i=0; i< min(outcount,line.length());i++)
                     {
                        buffer[i]=min(1,max(0,line[i]-'0')); // trim the chararaters to 0 and 1
                     }
                     sequenz->insert(sequenz->end(),buffer);
                  }
                  else
                  {
                     // commend
                  }
               }
		      }
            *iter=  sequenz->begin();
	      }
         else{
            // can't open the file
            memset(param,0,getParamCount());
         }
      }
      else{
         // no read permission
         memset(param,0,getParamCount());
      }
   }
   else {
      // file does't exist
      memset(param,0,getParamCount());
   }
   // END_TODO
}



//----------------------------------------------------------------------------
void Context::cleanupParam(char* param){
//----------------------------------------------------------------------------
   AFX_MANAGE_STATE(AfxGetStaticModuleState( ));

   // BEGIN_TODO
   //
   if(param ==NULL)
      return;

   ByteSequenze *sequenz        = NULL;
   ByteSequenze::iterator *iter = NULL;

   memcpy(&sequenz,(param+getParamCount()-   sizeof(void*)),sizeof(void*));
   memcpy(&iter   ,(param+getParamCount()- 2*sizeof(void*)),sizeof(void*));


   if(iter && sequenz){
      for ((*iter) = sequenz->begin(); (*iter) != sequenz->end(); ++(*iter)){
           delete *(*iter);
      }
      delete iter;
      delete sequenz;
   }

   memset(param,0,getParamCount());
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
   if(param==NULL)
      return 0;

   ByteSequenze *sequenz        = NULL;
   ByteSequenze::iterator *iter = NULL;
   int outcount = getOutputCountRange().cx;

   memcpy(&sequenz,(param+getParamCount()-   sizeof(void*)),sizeof(void*));
   memcpy(&iter   ,(param+getParamCount()- 2*sizeof(void*)),sizeof(void*));


   if(iter && sequenz){
      // falls der Reseteingang gesetzt ist wird das
      // erste Bitmuster an den Ausgang gelegt
      //
      if(input[1]){
         *iter=sequenz->begin();
         memcpy(output,(void*)(**iter),outcount);
         return 0;
      }
      // Nur bei einer ansteigenden Taktflanke 
      // wird das nächste Bitmuster gelesen und übertragen
      //
      if(input[0] && lastInput[0]==0){
         if((*iter)==sequenz->end()){
            *iter=sequenz->begin();
         }
         memcpy(output,(void*)(**iter),outcount);

         ++(*iter);
      }
   }

   // return 1   => redraw of the object by the framework
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

   pDC->Rectangle(location.x , location.y, location.x+ xSize, location.y-ySize);

   pDC->SelectObject(&m_bigFont);
   pDC->TextOut( XPOS(15), YPOS(0)            , "File to");
   pDC->TextOut( XPOS(12), YPOS(0)- (BIG_FONT), "output");

   // Clock
   //
   pDC->SelectObject(&m_smallFont);
   pDC->TextOut( location.x+ 28, YPOS(33) + (SMALL_FONT/2) , "1C");
   pDC->MoveTo(XPOS( 0), YPOS(28));   
   pDC->LineTo(XPOS(20), YPOS(33));   
   pDC->LineTo(XPOS( 0), YPOS(38));   
   
   // Reset
   //
   pDC->TextOut( location.x+ 28, YPOS(67) + (SMALL_FONT/2) , "R");

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
