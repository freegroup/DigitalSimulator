#include "stdafx.h"
#include "JNI_Document.h"
#include "Application\Configuration\ParameterManager.h"
#include "Application\Debug\LogManager.h"
#include "Application\Windows\Workplace\DigitalTraineeStudioView.h"

/*
 * Class:     Document
 * Method:    getCurrentAsXML()
 * Signature: (V)Ljava/lang/String
 */
jstring JNICALL Java_Document_getCurrentAsXML(JNIEnv *env, jclass)
{
	PROC_TRACE;


   CDigitalTraineeStudioView* view = CDigitalTraineeStudioView::GetActiveView();
   if(view!=NULL)
   {
      CDigitalTraineeStudioDoc* doc= (CDigitalTraineeStudioDoc*)view->GetDocument();
      if(doc!=NULL)
      {
         CString imageName = view->SaveTempCircuitImage();
         CString docName   = view->SaveTempCircuit();
         CString data= doc->ToXML(docName,imageName);
         
         return env->NewStringUTF((LPCSTR)data);
      }
   }

   return env->NewStringUTF((LPCSTR)"");
}

jstring JNICALL Java_Document_getCurrentDocumentation(JNIEnv *env, jclass)
{
	PROC_TRACE;


   CDigitalTraineeStudioView* view = CDigitalTraineeStudioView::GetActiveView();
   if(view!=NULL)
   {
      return env->NewStringUTF((LPCSTR)view->GetDocumentation());
   }

   return env->NewStringUTF((LPCSTR)"");
}

void JNICALL Java_Document_setCurrentDocumentation(JNIEnv *env, jclass, jstring jvalue)
{
	PROC_TRACE;

	const char *value = env->GetStringUTFChars( (jstring)jvalue, 0);

   CDigitalTraineeStudioView* view = CDigitalTraineeStudioView::GetActiveView();
   if(view!=NULL)
   {
      view->SetDocumentation(CString(value));
   }

   env->ReleaseStringUTFChars( (jstring)jvalue, value);
}

