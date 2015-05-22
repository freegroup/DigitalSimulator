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

#ifdef WITH_JVM

// JavaPluginManager.h: Schnittstelle für die Klasse JavaPluginManager.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JAVAPLUGINMANAGER_H__20392100_D54D_11D4_B2C6_000000000000__INCLUDED_)
#define AFX_JAVAPLUGINMANAGER_H__20392100_D54D_11D4_B2C6_000000000000__INCLUDED_

#include <jni.h>
#include <map>
#include <vector>

class CDynamicMenuExtension
{
  public:
     CDynamicMenuExtension(CString menuEntry, CString id)
     {
		m_menuEntry = menuEntry;
		m_id        = id;
     };

	 CString getMenuEntry()
	 {
			return m_menuEntry;
	 }

	 CString getId()
	 {
		 return m_id;
	 }

	 int getCurrentMenuCommand()
	 {
		 return m_currentMenuCommand;
	 }

	 void setCurrentMenuCommand(int command)
	 {
		 m_currentMenuCommand = command;
	 }

	 int     m_currentMenuCommand;
	 CString m_menuEntry;
	 CString m_id;
};

class JavaPluginManager  
{
public:

	static void init();
	static void clear();

   static bool isOk(){return m_isOk;};

   static void registerPlugin(CString className);
   static void registerTool(CString menuEntry, CString className);
   static void registerDialog(CString menuEntry, CString className);

   static std::vector<CDynamicMenuExtension*> getTools();
   static std::vector<CDynamicMenuExtension*> getDialogs();
protected:


   static bool selectJVMLibrary();

   static void registerConfiguration();
   static void registerPainter();
   static void registerTrace();
   static void registerPluginManager();
   static void registerObjectPlugin();
   static void registerDocument();

   static void registerJarsInDirectory(CString directory);

   static bool    m_isOk;
   static jclass  m_i18nClass;
   static jclass  m_configurationClass;
   static jclass  m_documentClass;
   static jclass  m_painterClass;
   static jclass  m_traceClass;
   static jclass  m_pluginManagerClass;
   static jclass  m_objectPluginClass;

   static std::vector<CDynamicMenuExtension*>   m_toolMap;
   static std::vector<CDynamicMenuExtension*>   m_dialogMap;
};


#endif // !defined(AFX_JAVAPLUGINMANAGER_H__20392100_D54D_11D4_B2C6_000000000000__INCLUDED_)
extern JavaPluginManager javaVM ;


#endif /* INVOKE_JNI*/