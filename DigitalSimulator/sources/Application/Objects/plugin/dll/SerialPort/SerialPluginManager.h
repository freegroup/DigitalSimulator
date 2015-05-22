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

#if !defined(AFX_SerialPluginManager_H__C9453031_8207_11D3_B6E8_000629C18114__INCLUDED_)
#define AFX_SerialPluginManager_H__C9453031_8207_11D3_B6E8_000629C18114__INCLUDED_
#pragma warning(disable : 4786)

#include <fstream>
#include <iostream>
#include <CString>
#include <vector>
#include <map>

#include "Application\Objects\plugin\DLL\DynamicLibrary.h"

#include "Plugins\DLL\SerialPort\IOutputContext.h"
#include "Plugins\DLL\SerialPort\IInputContext.h"
#include "Plugins\DLL\SerialPort\IPluginInfo.h"

//using namespace std ;


class SerialPluginManager {
public:
	static IPluginBase* createInstance(CString contextName, CString inter/*face*/);
   static void         removePlugin(CString);
	static void         registerPlugin(CString, DynamicLibrary*);
   static StringArray  getAllPlugins();
   static StringArray  getOutPlugins();
   static StringArray  getInPlugins();
   static void         clear();

   virtual char * const GetClassName(){return "SerialPluginManager";};
protected:
   static DynamicLibraryMap   m_pluginMap;
};

#endif // !defined(AFX_SerialPluginManager_H__C9453031_8207_11D3_B6E8_000629C18114__INCLUDED_)
