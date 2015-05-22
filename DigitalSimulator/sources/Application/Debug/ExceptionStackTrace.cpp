#include "stdafx.h"
#include <windows.h>
#include <tchar.h>
#include <imagehlp.h>
#include "utils\global_defines.h"
#include "utils\process.h"
#include "Application\Debug\LogManager.h"
#include "Application\Debug\ExceptionStackTrace.h"
#include "Application\DigitalSimulatorApp.h"

std::stack<CString>  GlobalExceptionHandler::s_functionStack;
char GlobalExceptionHandler::s_szLogFileName[MAX_PATH];
LPTOP_LEVEL_EXCEPTION_FILTER GlobalExceptionHandler::s_previousFilter;
FILE* GlobalExceptionHandler::s_stream;

static GlobalExceptionHandler g_ExceptionHandler;

//CString StackTrace( HANDLE hThread, LPCTSTR lpszMessage );


//----------------------------------------------------------------------------
GlobalExceptionHandler::GlobalExceptionHandler( ){
//----------------------------------------------------------------------------
    LM::log(LM::info,"Initialize the exception handler");
    LM::log(LM::info,"-------------------------------");

    // Install the unhandled exception filter function
    s_previousFilter = SetUnhandledExceptionFilter(UnhandledExceptionFilter);

    // Figure out what the report file will be named, and store it away
    GetModuleFileName( 0, s_szLogFileName, MAX_PATH );

    // Look for the '.' before the "EXE" extension.  Replace the extension
    // with "RPT"
    PTSTR pszDot = _tcsrchr( s_szLogFileName, _T('.') );
    if ( pszDot )
    {
        pszDot++;   // Advance past the '.'
        if ( _tcslen(pszDot) >= 3 )
            _tcscpy( pszDot, _T("RPT") );   // "RPT" -> "Report"
    }

    LM::log(LM::info,"");
}

//----------------------------------------------------------------------------
GlobalExceptionHandler::~GlobalExceptionHandler( ){
//----------------------------------------------------------------------------
   /*
   if(s_previousFilter)
      SetUnhandledExceptionFilter( s_previousFilter );
    s_previousFilter= NULL;
    */
}

//----------------------------------------------------------------------------
LONG WINAPI GlobalExceptionHandler::UnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo ){
//----------------------------------------------------------------------------
    s_stream = fopen( (LPCSTR)s_szLogFileName, "w+" );

    if ( s_stream ) {
        GenerateExceptionReport( pExceptionInfo );
        fclose( s_stream );
        s_stream = 0;
    }

    // display the error report with the notepad
    //
    startProcess("notepad ", s_szLogFileName, FALSE);

    if(s_previousFilter)
      SetUnhandledExceptionFilter( s_previousFilter );
    s_previousFilter = NULL;
    return EXCEPTION_CONTINUE_SEARCH;
}

//----------------------------------------------------------------------------
void GlobalExceptionHandler::GenerateExceptionReport( PEXCEPTION_POINTERS pExceptionInfo ){
//----------------------------------------------------------------------------

   // Start out with a banner
   //
    write( "+============================================================+\n" );
    write( "|           -- THE DIGITAL-SIMULATOR CRASHED --              |\n" );
    write( "|                                                            |\n" );
    write( "|                            SHIT                            |\n" );
    write( "|                                                            |\n" );
    write( "|                                                            |\n" );
    write( "|     PLEASE send this text for additional analyse to the    |\n" );
    write( "|     developer (mail adress see below)                      |\n" );
    write( "|                                                            |\n" );
    write( "|    ....or see in the source code and fix the problem.      |\n" );
    write( "+============================================================+\n" );

    PEXCEPTION_RECORD pER = pExceptionInfo->ExceptionRecord;

    if(pER){
       // Art des Fehlers ausgeben
       //
       write("Exception code: %08X %s\n",pER->ExceptionCode,GetExceptionString(pER->ExceptionCode) );

    
       // 'Stolperadresse' ausgeben
       //
       TCHAR szFaultingModule[MAX_PATH];
       DWORD section, offset;
       GetLogicalAddress(  pER->ExceptionAddress,
                           szFaultingModule,
                           sizeof( szFaultingModule ),
                           section, offset );

       write( "Fault address:  %08X %02X:%08X %s\n",
                 pER->ExceptionAddress,
                 section, offset, szFaultingModule );
    }

    // Programm und Libraryversionen ausgeben
    //
    write("\nProgram build informations\n");
    write("==========================\n");
    write("MFC-Version:            %X\n",_MFC_VER);
    write("Program build date:     %s\n",__DATE__);
    write("Program version:        %s\n",PROGRAM_VERSION);
    write("Program version string: %s\n",VERSION_STRING);
    write("Contact person:         %s\n",CONTACT_STRING);

    // CallStack ausgeben
    //
    write( "\nCallstack generated from trace utility:\n" );
    write( "==========\n" );
    write( "%03d>        ...CRASH....\n",s_functionStack.size() +1);
    
    while (!s_functionStack.empty())
    {
       const CString& t=s_functionStack.top();
       write( "%03d> %s\n", s_functionStack.size(),(LPCSTR)t);
       s_functionStack.pop();
    }
}

//----------------------------------------------------------------------------
LPTSTR GlobalExceptionHandler::GetExceptionString( DWORD dwCode ){
//----------------------------------------------------------------------------

    #define EXCEPTION( x ) case EXCEPTION_##x: return _T(#x);

    switch ( dwCode )
    {
        EXCEPTION( ACCESS_VIOLATION )
        EXCEPTION( DATATYPE_MISALIGNMENT )
        EXCEPTION( BREAKPOINT )
        EXCEPTION( SINGLE_STEP )
        EXCEPTION( ARRAY_BOUNDS_EXCEEDED )
        EXCEPTION( FLT_DENORMAL_OPERAND )
        EXCEPTION( FLT_DIVIDE_BY_ZERO )
        EXCEPTION( FLT_INEXACT_RESULT )
        EXCEPTION( FLT_INVALID_OPERATION )
        EXCEPTION( FLT_OVERFLOW )
        EXCEPTION( FLT_STACK_CHECK )
        EXCEPTION( FLT_UNDERFLOW )
        EXCEPTION( INT_DIVIDE_BY_ZERO )
        EXCEPTION( INT_OVERFLOW )
        EXCEPTION( PRIV_INSTRUCTION )
        EXCEPTION( IN_PAGE_ERROR )
        EXCEPTION( ILLEGAL_INSTRUCTION )
        EXCEPTION( NONCONTINUABLE_EXCEPTION )
        EXCEPTION( STACK_OVERFLOW )
        EXCEPTION( INVALID_DISPOSITION )
        EXCEPTION( GUARD_PAGE )
        EXCEPTION( INVALID_HANDLE )
    }

    // If not one of the "known" exceptions, try to get the CString
    // from NTDLL.DLL's message table.

    static TCHAR szBuffer[512] = { 0 };

    FormatMessage(  FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
                    GetModuleHandle( _T("NTDLL.DLL") ),
                    dwCode, 0, szBuffer, sizeof( szBuffer ), 0 );

    return szBuffer;
}

//----------------------------------------------------------------------------
BOOL GlobalExceptionHandler::GetLogicalAddress(PVOID addr, PTSTR szModule, DWORD len, DWORD& section, DWORD& offset ){
//----------------------------------------------------------------------------

    MEMORY_BASIC_INFORMATION mbi;

    if ( !VirtualQuery( addr, &mbi, sizeof(mbi) ) )
        return FALSE;

    DWORD hMod = (DWORD)mbi.AllocationBase;

    if ( !GetModuleFileName( (HMODULE)hMod, szModule, len ) )
        return FALSE;

    // Point to the DOS header in memory
    PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;

    // From the DOS header, find the NT (PE) header
    PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);

    PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION( pNtHdr );

    DWORD rva = (DWORD)addr - hMod; // RVA is offset from module load address

    // Iterate through the section table, looking for the one that encompasses
    // the linear address.
    for (   unsigned i = 0;
            i < pNtHdr->FileHeader.NumberOfSections;
            i++, pSection++ )
    {
        DWORD sectionStart = pSection->VirtualAddress;
        DWORD sectionEnd = sectionStart
                    + max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

        // Is the address in this section???
        if ( (rva >= sectionStart) && (rva <= sectionEnd) )
        {
            // Yes, address is in the section.  Calculate section and offset,
            // and store in the "section" & "offset" params, which were
            // passed by reference.
            section = i+1;
            offset = rva - sectionStart;
            return TRUE;
        }
    }

    return FALSE;   // Should never get here!
}


//----------------------------------------------------------------------------
int GlobalExceptionHandler::write(const char* format, ...){
//----------------------------------------------------------------------------

    int retValue;
    va_list argptr;
          
    va_start( argptr, format );
    retValue = vfprintf(s_stream, format, argptr );
    va_end( argptr );

    return retValue;
}



//----------------------------------------------------------------------------
void GlobalExceptionHandler::push(CString functionName){
//----------------------------------------------------------------------------
   s_functionStack.push(functionName);
}

//----------------------------------------------------------------------------
void GlobalExceptionHandler::pop(){
//----------------------------------------------------------------------------
   s_functionStack.pop();
}
