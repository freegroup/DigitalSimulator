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

#pragma warning(disable : 4786)
#include "stdafx.h"
#include "SerialPluginManager.h"
#include "Application\Debug\LogManager.h"


DynamicLibraryMap   SerialPluginManager::m_pluginMap;

#pragma TODO("Einen Dialog anlegen welcher alle geladenen PlugIns anzeigt (mit Attribute)")
//----------------------------------------------------------------------------
void SerialPluginManager::registerPlugin(CString id, DynamicLibrary *lib){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   m_pluginMap[id]=lib;
}

//----------------------------------------------------------------------------
void SerialPluginManager::removePlugin(CString){
//----------------------------------------------------------------------------
	PROC_TRACE;

#pragma TODO("function 'SerialPluginManager::removePlugin(CString)' not implemented")

}

//----------------------------------------------------------------------------
StringArray SerialPluginManager::getAllPlugins(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   StringArray x;
   DynamicLibraryMap::iterator theIterator;

  	theIterator = m_pluginMap.begin();
   while(theIterator != m_pluginMap.end()){
      x.push_back((LPCSTR)(*theIterator).first);
      theIterator++;
   }
   return x;
}

//----------------------------------------------------------------------------
StringArray SerialPluginManager::getOutPlugins(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   StringArray x;
   DynamicLibraryMap::iterator theIterator;

  	theIterator = m_pluginMap.begin();
   while(theIterator != m_pluginMap.end()){
      IPluginBase* inter;
      if(NULL != (inter = createInstance((LPCSTR)(*theIterator).first,"IOutputContext"))) {
         x.push_back((LPCSTR)(*theIterator).first);
         inter->Destroy();
      }
      theIterator++;
   }
   return x;
}

//----------------------------------------------------------------------------
StringArray SerialPluginManager::getInPlugins(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   StringArray x;
   DynamicLibraryMap::iterator theIterator;

  	theIterator = m_pluginMap.begin();
   while(theIterator != m_pluginMap.end()){
      IPluginBase* inter;
      if(NULL != (inter = createInstance((LPCSTR)(*theIterator).first,"IInputContext"))) {
         x.push_back((LPCSTR)(*theIterator).first);
         inter->Destroy();
      }
      theIterator++;
   }
   return x;
}
//----------------------------------------------------------------------------
void SerialPluginManager::clear(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DynamicLibraryMap::iterator theIterator;

  	theIterator = m_pluginMap.begin();
   while(theIterator != m_pluginMap.end())
   {
      try
      {
         ((*theIterator).second)->Unload();
      }
      catch(...)
      {
         // Ignore possible exceptions of the DLL during the unload.
         // The Exception of the Plugin DLL should't influence
         // the main program
      }
      theIterator++;
   }
   m_pluginMap.clear();
}


//----------------------------------------------------------------------------
IPluginBase* SerialPluginManager::createInstance(CString contextName, CString inter/*face*/){
//----------------------------------------------------------------------------
	PROC_TRACE;

   IPluginBase *in  = NULL;;
   if(contextName != ""){
      DynamicLibrary     *lib = m_pluginMap[contextName];

      if(lib!=NULL){
         if (lib->CreateInterface(inter,reinterpret_cast<IPluginBase**>(&in))){
            // hipp
		   }
         else{
            in = NULL;
         }
      }
   }
   return in;
}
