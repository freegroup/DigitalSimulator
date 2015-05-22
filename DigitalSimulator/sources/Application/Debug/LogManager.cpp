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
#include "stdafx.h"
#include <afx.h>
#include <tchar.h>
#include <imagehlp.h>
#include <strstream>
#include <stack>

#include "Application\Configuration\ParameterManager.h"

#include "ExceptionStackTrace.h"
#include "Application\Debug\LogManager.h"

FILE * stream;

int      LogManager::s_spacing  = 0;
LogManager::LogLevel LogManager::s_currentLogLevel = LogManager::LogLevel::none;
static LogManager logManager;

#define TRACEWND_CLASSNAME _T("FreeGroupTraceWindow")
#define ID_COPYDATA_TRACEMSG MAKELONG(MAKEWORD('t','w'),MAKEWORD('i','n'))



//----------------------------------------------------------------------------
LogManager::LogManager(){
//----------------------------------------------------------------------------
   CString level = GET_PARAMETER("LogLevel");

//   EXTENDEDTRACEINITIALIZE( NULL );

   CString filename=LOGGING_PATH("trace.txt");
   stream = fopen((LPCSTR)filename, "w+" );

   if(level == CString("none"))
      s_currentLogLevel=none;
   else if(level == CString("error"))
      s_currentLogLevel=error;
   else if(level == CString("warning"))
      s_currentLogLevel=warning;
   else if(level == CString("info"))
      s_currentLogLevel=info;
   else if(level == CString("debug1"))
      s_currentLogLevel=debug1;
   else if(level == CString("debug2"))
      s_currentLogLevel=debug2;
   else if(level == CString("debug3"))
      s_currentLogLevel=debug3;
   else
      s_currentLogLevel=none;
}


//----------------------------------------------------------------------------
void LogManager::log(LogManager::LogLevel level ,TCHAR* formatString, ...){
//----------------------------------------------------------------------------
   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   // Don't trace this.....stack overflow during recursion!!
   // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//PROC_TRACE;

   static char buffer1[20000];
   static char buffer2[20000];

   static char *levelText;

   if(s_currentLogLevel<level)
      return;

   switch(level)
   {
      case none:
         return;
      case error:
         levelText ="error  : ";
         break;
      case warning:
         levelText ="warning: ";
         break;
      case info:
         levelText ="info   : ";
         break;
      case debug1:
         levelText ="debug1 : ";
         break;
      case debug2:
         levelText ="debug2 : ";
         break;
      case debug3:
         levelText ="debug3 : ";
         break;
   }
	va_list argList;
	va_start(argList, formatString);
 	vsprintf(buffer1,formatString,argList);
 	sprintf(buffer2,"%s%s\n",levelText,buffer1);

   // trace to the file
   //
   //00 Existence only 
   //02 Write permission 
   //04 Read permission 
   //06 Read and write permission 
//   fprintf(stream,buffer2);
//	fclose(stream); 

   // trace to the Tracewin
   {
	   HWND hTraceWnd = ::FindWindow(TRACEWND_CLASSNAME, NULL);
	   if (hTraceWnd)
      {
		   COPYDATASTRUCT cds;
		   cds.dwData    = ID_COPYDATA_TRACEMSG;
		   cds.cbData    = strlen(buffer2);
		   cds.lpData    = buffer2;
		   CWinApp* pApp = AfxGetApp();
		   HWND hWnd = pApp ? pApp->m_pMainWnd->GetSafeHwnd() : NULL;
		   ::SendMessage(hTraceWnd, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);
	   }
   }
   
   // trace to the debug console
   //
   // cut the String to the max of 512 characters
   //
   if(strlen(buffer2)>512)
	   buffer2[512]='\0';
   TRACE1("%s",buffer2);
}


