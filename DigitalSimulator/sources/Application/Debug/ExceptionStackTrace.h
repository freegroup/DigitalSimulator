#ifndef __MSJEXHND_H__
#define __MSJEXHND_H__
#pragma warning(disable : 4786)

#include <stack>
#include <CString>
//using namespace std;


class GlobalExceptionHandler
{
public:
      GlobalExceptionHandler( );
      ~GlobalExceptionHandler( );
     
      static void push(CString functionName);
      static void pop();

      
protected:

      static LONG WINAPI UnhandledExceptionFilter( PEXCEPTION_POINTERS pExceptionInfo );

      static void   GenerateExceptionReport( PEXCEPTION_POINTERS pExceptionInfo );
      static LPTSTR GetExceptionString( DWORD dwCode );
      static BOOL   GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset );
      static int    write(const char * format, ...);
          
      static std::stack<CString>           s_functionStack;
      static char                          s_szLogFileName[MAX_PATH];
      static LPTOP_LEVEL_EXCEPTION_FILTER  s_previousFilter;
      static FILE                         *s_stream;
};



#endif
