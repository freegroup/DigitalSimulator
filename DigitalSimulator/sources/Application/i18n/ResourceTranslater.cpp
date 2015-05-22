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

#include "stdafx.h"
#pragma warning(disable : 4786)


#include <algorithm>

#include "Application\DigitalSimulatorApp.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Debug\LogManager.h"
#include "Application\JavaBinding\I18NProxy.h"

#include "ResourceTranslater.h"

/*
** strrepl: Replace OldStr by NewStr in CString Str contained in buffer
**          of size BufSiz.
**
** Str should have enough allocated space for the replacement - if not,
** NULL is returned. Str and OldStr/NewStr should not overlap.
**
** The empty CString ("") is found at the beginning of every CString.
**
** Returns: pointer to first location behind where NewStr was inserted.
**          Str if OldStr was not found.
**          NULL if replacement would overflow Str's buffer
**
** This is useful for multiple replacements, see example in main() below
** (be careful not to replace the empty CString this way !)
**
**  NOTE: The name of this funtion violates ANSI/ISO 9899:1990 sec. 7.1.3,
**        but this violation seems preferable to either violating sec. 7.13.8
**        or coming up with some hideous mixed-case or underscore infested
**        naming. Also, many SNIPPETS str---() functions duplicate existing
**        functions which are supported by various vendors, so the naming
**        violation may be required for portability.
*/
/*
char *strrepl(char *Str, size_t BufSiz, char *OldStr, char *NewStr){
      int OldLen, NewLen;
      char *p, *q;

      if(NULL == (p = strstr(Str, OldStr)))
            return Str;
      OldLen = strlen(OldStr);
      NewLen = strlen(NewStr);
      if ((strlen(Str) + NewLen - OldLen + 1) > BufSiz)
            return NULL;
      memmove(q = p+NewLen, p+OldLen, strlen(p+OldLen)+1);
      memcpy(p, NewStr, NewLen);
      return q;
}
*/

//----------------------------------------------------------------------------
RecourceTranslater& RecourceTranslater::Instance(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   static RecourceTranslater *m=NULL;

   if (m==NULL)
      m= new RecourceTranslater();

   return *m;
}


//----------------------------------------------------------------------------
RecourceTranslater::RecourceTranslater(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   m_languageNotifyee.setListener(this);
}

//----------------------------------------------------------------------------
RecourceTranslater::~RecourceTranslater(){
//----------------------------------------------------------------------------
	PROC_TRACE;
}

//----------------------------------------------------------------------------
void RecourceTranslater::Translate(CMenu *m){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if(m==NULL)
      return ;

   int i =m->GetMenuItemCount();

   CString menuString;
   CString menuUID;
   long    menuId;
   // Die jeweiligen Menuepunkte und deren Popupmenues
   // uebersetzten
   //
   while(i){
      m->GetMenuString(i-1,menuString,MF_BYPOSITION);
      if(menuString != CString("")){
         menuId = m->GetMenuItemID(i-1);
         menuUID.Format("%X_%d",m->m_hMenu,i);

         StringStringMap::iterator theIterator;
		   theIterator = m_menuEntryOriginalString.find(menuUID);
         // Dieses menu wurde bereits einmal übersetzt. Den original key aus 
         // einer Map holen.
		   if(theIterator != m_menuEntryOriginalString.end() ) {
            menuString = (*theIterator).second;
         }
         // Menu wurde noch nie übersetzt. Key merken falls das Menu nochmals übersetzt
         // werden muß (original key wird ja jetzt überschrieben!!!!)
         else{
		      m_menuEntryOriginalString.insert(StringStringMap::value_type(menuUID, menuString));
         }
         m->ModifyMenu(i-1,MF_BYPOSITION,menuId,Translate(menuString));
      }
      Translate(m->GetSubMenu(i-1));
      i--;
   }
}

//----------------------------------------------------------------------------
const char* RecourceTranslater::Translate(const char* msg){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CString trans= I18NProxy::get(CString(msg));
   trans.Replace("Ã„","Ä");
   trans.Replace("Ãœ","Ü");
   trans.Replace("Ã–","Ö");
   trans.Replace("Ã¤","ä");
   trans.Replace("Ã¼","ü");
   trans.Replace("Ã¶","ö");
   trans.Replace("ÃŸ","ß");


   m_catalogOrigToTrans.insert(StringStringMap::value_type(msg,trans));

   StringStringMap::iterator theIterator;
   theIterator = m_catalogOrigToTrans.find(CString(msg));
   if(theIterator != m_catalogOrigToTrans.end() )
	   return  (*theIterator).second;
   return msg;
}
