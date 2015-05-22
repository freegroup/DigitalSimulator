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

#if !defined(AFX_PARAMETERMANAGER_H__90BBB7E1_A17A_11D2_8958_004F49031E0C__INCLUDED_)
#define AFX_PARAMETERMANAGER_H__90BBB7E1_A17A_11D2_8958_004F49031E0C__INCLUDED_
#pragma warning(disable : 4786)


#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include <string>
#include "ProxyArray.h"
#include "PrimitiveArray.h"
#include "JStringHelper.h"
#include "JStringHelperArray.h"
using namespace de::freegroup::jnipp;

#define WMF_PATH(file)         (ParameterManager::Instance().Get("WMFPath")+file )
#define BMP_PATH(file)         (ParameterManager::Instance().Get("BMPPath")+file )
#define PALETTE_PATH(file)     (ParameterManager::Instance().Get("PalettePath")+file) 
#define PLUGIN_PATH(file)      (ParameterManager::Instance().Get("PluginPath")+file) 
#define BASIC_PATH(file)       (ParameterManager::Instance().Get("BasicPath")+file)
#define SCRIPT_PATH(file)      (ParameterManager::Instance().Get("ScriptPath")+file)
#define LANGUAGE_PATH(file)    (ParameterManager::Instance().Get("LanguagePath")+file)
#define APPLICATION_PATH(file) (ParameterManager::Instance().Get("ApplicationPath")+file)
#define LOGGING_PATH(file)     (ParameterManager::Instance().Get("LoggingPath")+file)
#define JRE_PATH(file)         (ParameterManager::Instance().Get("JREPath")+file)
#define TEMP_PATH(file)        (ParameterManager::Instance().Get("TempPath")+file)

#define REGISTER_PARAMETER(listener) ParameterManager::Instance().RegisterForChange(listener)
#define UNREGISTER_PARAMETER(listener) ParameterManager::Instance().UnregisterForChange(listener)

#define SET_PARAMETER(name, wert) ParameterManager::Instance().Set(name, wert)
#define GET_PARAMETER(name) ParameterManager::Instance().Get(name)

//using namespace std ;

class ValueChangeNotifyee ;

typedef    std::map<CString, CString>     ParamMap;
typedef    std::set<ValueChangeNotifyee*> NotifyeeCollection;

class ParameterManager  
{
public:
   static ParameterManager& Instance();

   void    RegisterForChange(ValueChangeNotifyee *callback);
   void    UnregisterForChange(ValueChangeNotifyee *callback);

   void    Set(const CString& paramName, const CString& value);
   CString Get(const CString& paramName);
   void    Save();

   virtual ~ParameterManager();

   virtual char * const GetClassName(){return "ParameterManager";};
protected:
	ParameterManager();

   void    Load();
   void    BeforeChange(const CString& valueName, const CString& value);
   void    DuringChange(const CString& valueName, const CString& value);
   void    AfterChange(const CString& valueName, const CString& value);

   ParamMap           m_paramMap;
   NotifyeeCollection m_callbackObjects;

private:
	static std::string className;
	static jclass      objectClass;
//	jobject peerObject;

};

class ValueChangeNotifyee {
public:
   ValueChangeNotifyee(){
      REGISTER_PARAMETER(this);
   };
   virtual ~ValueChangeNotifyee(){
      UNREGISTER_PARAMETER(this);
   };
   virtual void BeforeChange(const CString &value);
   virtual void DuringChange(const CString& value);
   virtual void AfterChange(const CString& value);

   CString m_valueNameForNotifyee;

   virtual char * const GetClassName(){return "ValueChangeNotifyee";};
};


#endif // !defined(AFX_PARAMETERMANAGER_H__90BBB7E1_A17A_11D2_8958_004F49031E0C__INCLUDED_)
