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

#define NOGDI
#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <windows.h>

#include "Application\Debug\LogManager.h"

#include "DynamicLibrary.h"

//----------------------------------------------------------------------------
DynamicLibrary::DynamicLibrary(const char *libName)	: libHandle(0){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Load( libName );
}

//----------------------------------------------------------------------------
DynamicLibrary::~DynamicLibrary( void ){
//----------------------------------------------------------------------------
	PROC_TRACE;

	Unload();
}

//----------------------------------------------------------------------------
bool DynamicLibrary::Load(const char *libName){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (libName != NULL && ::strlen(libName) > 0){
		if (libHandle == NULL){
			libHandle = ::LoadLibrary( libName );
         if(libHandle == NULL){
            LPVOID lpMsgBuf;

            FormatMessage( 
                FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                GetLastError(),
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                (LPTSTR) &lpMsgBuf,
                0,
                NULL 
            );
            // Display the CString.
            MessageBox( NULL, (LPTSTR)lpMsgBuf, "GetLastError", MB_OK|MB_ICONINFORMATION );
            // Free the buffer.
            LocalFree( lpMsgBuf );
 
         }
		}
	}

	return (libHandle != NULL);
}

//----------------------------------------------------------------------------
bool DynamicLibrary::Unload( void ){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (libHandle != NULL){
		::FreeLibrary( libHandle );
	}

	libHandle = NULL;

	cache.clear();

	return true;
}


//----------------------------------------------------------------------------
bool DynamicLibrary::CreateInterface(const char *iid, IPluginBase **iface){
//----------------------------------------------------------------------------
	PROC_TRACE;

	*iface = NULL;

	bool(*f)(const char *, IPluginBase **) =
		reinterpret_cast<bool(*)(const char *, IPluginBase**)>(
		GetProcAddr( "cf_create_interface" ) );

	if (f)
		return f(iid, iface);

	return false;
}


//----------------------------------------------------------------------------
DLPROC DynamicLibrary::GetProcAddr(const char *procName) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	DLPROC proc = NULL;

	if (libHandle != NULL){
		proc = (DLPROC) ::GetProcAddress(libHandle, procName);
	}

	return proc;
}

//----------------------------------------------------------------------------
DLPROC DynamicLibrary::GetProcAddrCached(const char *procName, unsigned int procId){
//----------------------------------------------------------------------------
	PROC_TRACE;

	DLPROC proc = NULL;

	if (libHandle != NULL){
		if ((procId >= cache.size()) || (cache.size() < 1))
			cache.resize(procId + 1, cache_info());

		cache_info &ci = cache[ procId ];

		if (ci.procAddr == NULL && !ci.testFlag){
			ci.testFlag = true;
			ci.procAddr = GetProcAddr(procName);
		}

		proc = ci.procAddr;
	}

	return proc;
}

//----------------------------------------------------------------------------
DLPROC DynamicLibrary::GetProcAddr(int ordinal) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

	DLPROC proc = NULL;

	if (libHandle != NULL){
		proc = (DLPROC) ::GetProcAddress(libHandle, MAKEINTRESOURCE(ordinal));
	}

	return proc;
}

//----------------------------------------------------------------------------
DLPROC DynamicLibrary::GetProcAddrCached(int ordinal){
//----------------------------------------------------------------------------

	PROC_TRACE;

	return GetProcAddrCached(MAKEINTRESOURCE(ordinal), ordinal);
}

