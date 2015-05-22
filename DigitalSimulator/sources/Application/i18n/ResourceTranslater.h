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

#if !defined(AFX_STRINGTRANSLATER_H__38E4C1E1_A551_11D2_99FD_0080C7304F8F__INCLUDED_)
#define AFX_STRINGTRANSLATER_H__38E4C1E1_A551_11D2_99FD_0080C7304F8F__INCLUDED_
#pragma warning(disable : 4786)


#include <fstream>
#include <iostream>
#include <CString>
#include <map>
#include "Application\Configuration\ParameterManager.h"

typedef    std::map<CString, CString> StringStringMap;

class RecourceTranslater {
public:
   static RecourceTranslater& Instance();

   void Clear(){ m_catalogOrigToTrans.clear();}

   const char * Translate(const char* msg);
   void         Translate(CMenu *);
 //  const char * Translate(long id);

   virtual char * const GetClassName(){return "RecourceTranslater";};
protected:
   RecourceTranslater();
   ~RecourceTranslater();

   StringStringMap m_catalogOrigToTrans;
   StringStringMap m_menuEntryOriginalString;

   //-------------------------------------------------------------------------
   // Callback Objects
   //-------------------------------------------------------------------------
   class LanguageNotifyee : public ValueChangeNotifyee{
   public: 
      LanguageNotifyee(){
         m_listener = NULL;
         m_valueNameForNotifyee = "Language";
      };
      virtual void DuringChange(const CString& value){
         if(m_listener !=NULL){
            m_listener->Clear();
         }
      }
      void setListener(RecourceTranslater*l){
         m_listener=l;
      }
   protected:
      RecourceTranslater* m_listener;
   } m_languageNotifyee;

};

#define TRANSLATE(txt)  RecourceTranslater::Instance().Translate(txt)
#define TRANSLATE_DIALOG_ITEM(id)   {CString text;if(GetDlgItem(id)!=NULL){GetDlgItem(id)->GetWindowText(text);GetDlgItem(id)->SetWindowText(TRANSLATE(text));}}
#define SET_DIALOG_ITEM(id,text)    {if(GetDlgItem(id)!=NULL){GetDlgItem(id)->SetWindowText(TRANSLATE(text));}}

#endif // !defined(AFX_STRINGTRANSLATER_H__38E4C1E1_A551_11D2_99FD_0080C7304F8F__INCLUDED_)
