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

#ifndef DYNAMICLIBRARY_H_INCLUDED
#define DYNAMICLIBRARY_H_INCLUDED
#pragma warning(disable : 4786)

#include <CString>
#include <vector>
#include <map>
#include "Plugins\DLL\IPluginBase.h"

//using namespace std ;

typedef void(*DLPROC)();

class cache_info
{
public:
	DLPROC	procAddr;
	bool	testFlag;

public:
	cache_info(void) : procAddr(0), testFlag(false) {};
	const bool operator==(const cache_info& s) const{
		if(this==&s)   {
   			return true;
		}

		if(procAddr== s.procAddr)
			return true;
		return false;
	};
	const bool operator<(const cache_info& s) const{
		return(procAddr< s.procAddr);
	};

   virtual char * const GetClassName(){return "cache_info";};
};


class DynamicLibrary  
{
private:
	std::vector<cache_info>		cache;

public:

	DynamicLibrary(void) : libHandle(0) {};
	DynamicLibrary(const char *libName);
	virtual ~DynamicLibrary(void);

	bool Load(const char *libName);
	bool Unload(void);
	bool IsLoaded(void) const { return (libHandle != 0); };

    bool CreateInterface(const char *iid, IPluginBase **iface);

	DLPROC GetProcAddr(const char *procName) const;
	DLPROC GetProcAddrCached(const char *procName,
							 unsigned int procId);
	DLPROC GetProcAddr(int ordinal) const;
	DLPROC GetProcAddrCached(int ordinal);


	struct HINSTANCE__ *	libHandle;

   virtual char * const GetClassName(){return "DynamicLibrary";};
};

typedef    std::map<CString, DynamicLibrary*>     DynamicLibraryMap;
typedef    std::vector<CString>   StringArray;

#endif

