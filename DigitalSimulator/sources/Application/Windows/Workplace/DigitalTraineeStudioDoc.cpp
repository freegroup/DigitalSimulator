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

#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Windows\Oszi\OsziView.h"

#include "Application\Objects\buildin\common\ElectricText.h"
#include "Application\Objects\buildin\common\ElectricBitmap.h"
#include "Application\Objects\buildin\digital\DDENode.h"
#include "Application\Objects\buildin\digital\DDEOuputNode.h"
#include "Application\Objects\buildin\digital\DDEInputNode.h"
#include "Application\Objects\plugin\DLL\SerialPort\SerialOutNode.h"
#include "Application\Objects\plugin\DLL\SerialPort\SerialInNode.h"

#include "DigitalTraineeStudioView.h"
#include "DigitalTraineeStudioDoc.h"

/////////////////////////////////////////////////////////////////////////////
// CDigitalTraineeStudioDoc


CString int2string(int i) {
   int j=i,k=1;
   CString s;
   if(i<0)
   {
	   s="-";
	   j=i= (-1)*i;
   }
   while (j>9) { j/=10; k*=10; }
   while (k>0) { s+=i/k+48; i-=k*(i/k); k/=10; }
   return s;
 };


IMPLEMENT_DYNCREATE(CDigitalTraineeStudioDoc, DragDropDocument)
//----------------------------------------------------------------------------
CDigitalTraineeStudioDoc::CDigitalTraineeStudioDoc(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CDigitalTraineeStudioDoc::~CDigitalTraineeStudioDoc(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
BOOL CDigitalTraineeStudioDoc::OnNewDocument(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!inherited::OnNewDocument())
		return FALSE;

   SetMinSize (CSize(21*m_nUnit/4,28*m_nUnit/4));   // half of the default size in default minimum
   SetDocumentSize (CSize(2*21*m_nUnit,2*28*m_nUnit));       // 2* (21 cm X 27) cm (sort of 8.5 x 11)

	return TRUE;
}


//----------------------------------------------------------------------------
void CDigitalTraineeStudioDoc::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Alle Objecte Einlesen....eventuell sind auch ein
   // paar ViewPoint darunter. Dise muessen dann `von Hand` mit
   // dem OsziView verbunden werden
   //
   inherited::Serialize(ar);

   if (ar.IsLoading()){
      // den ersten View finden ....und den einzigsten
      //
      POSITION pos = GetFirstViewPosition();
      if(pos != NULL){
         CView* pView = GetNextView(pos);
         if(pView && pView->IsKindOf(RUNTIME_CLASS(CDigitalTraineeStudioView))) {
            CDigitalTraineeStudioView *dragDropView = (CDigitalTraineeStudioView *)pView;

            // Alle OsziStrokes finden
            //
            POSITION objPos = GetFirstObjectPos();
            while(objPos!= NULL){
               DragDropObject* obj = (DragDropObject*)GetNextObject( objPos );
               if(obj->IsKindOf(RUNTIME_CLASS(CElectricPortLink))){
                  CElectricPortLink* link = (CElectricPortLink*)obj;
                  COsziStroke*       stroke = link->GetOsziStroke();
                  if(stroke !=NULL){
                     dragDropView->m_osziView->Add(stroke);
                  }
               }
            }
         }
      }   
   }
}


//----------------------------------------------------------------------------
CString CDigitalTraineeStudioDoc::ToXML(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return ToXML("","");
}

//----------------------------------------------------------------------------
CString CDigitalTraineeStudioDoc::ToXML(CString pathToCircuit, CString pathToCircuitImage){
//----------------------------------------------------------------------------
	PROC_TRACE;
   POSITION pos;
   char id[100];
   char fanOut[100];
   CString xmlDocument;


   xmlDocument = CString("<circuit name=\"")+GetTitle()+"\">\n";

   if(GetPathName()!=""){
      xmlDocument = xmlDocument+CString("\t<circuitPath>")+GetPathName()+"</circuitPath>\n";
   }

   if(pathToCircuit!=""){
      xmlDocument = xmlDocument+CString("\t<tmpCircuitPath>")+pathToCircuit+"</tmpCircuitPath>\n";
   }

   if(pathToCircuitImage!=""){
      xmlDocument = xmlDocument+CString("\t<imagePath>")+pathToCircuitImage+"</imagePath>\n";
   }


   xmlDocument += "\t<objects>\n";
   for( pos = GetFirstObjectPos(); pos != NULL; )
   {
      DragDropObject  *obj    = (DragDropObject*)GetNextObject(pos);

      if (obj->GetParent()==NULL && obj->IsKindOf(RUNTIME_CLASS(CElectricNode)))
      {
         CElectricNode  *eobj  = (CElectricNode*)obj;
         int i;
         sprintf(id,"%08X",obj);

         xmlDocument = xmlDocument + "\t\t<object" +
			                            " id=\""+CString(id)+"\""+
												 " group=\""+obj->GetGroup()+"\""+
												 " type=\""+obj->GetKey()+eobj->GetMetaNameSuffix()+"\""+
												 " version=\""+obj->GetVersion()+"\""+
												 " positionX=\""+ int2string(obj->GetLocation().x) + "\""+
												 " positionY=\""+ int2string(-obj->GetLocation().y) + "\""+
												 " width=\""+ int2string(obj->GetWidth())+"\""+
												 " height=\""+int2string(obj->GetHeight())+"\""+
												 ">\n";

         // add all the inport to the object
         //
         xmlDocument += "\t\t\t<input>\n";
//         eobj    = (CElectricNode*)obj;
         for(i = 0 ;i<eobj->GetInputCount(); i++)
         {

            sprintf(id,"%08X",eobj->GetInput(i));
            xmlDocument = xmlDocument + "\t\t\t\t<port id=\""+CString(id)+"\"/>\n";
         }
         xmlDocument += "\t\t\t</input>\n";

         // add all the outport to the object
         //
         xmlDocument += "\t\t\t<output>\n";
//         eobj    = (CElectricNode*)obj;
         for(i = 0 ;i<eobj->GetOutputCount(); i++)
         {
            CElectricPort* output = eobj->GetOutput(i); 
            sprintf(id,"%08X",output);
			if(output->GetLinks()!=NULL)
	            sprintf(fanOut,"%d",output->GetLinks()->GetCount());
			else
	            sprintf(fanOut,"0");

            xmlDocument = xmlDocument + "\t\t\t\t<port id=\""+CString(id)+"\" fanOut=\""+CString(fanOut)+"\"/>\n";
         }
         xmlDocument += "\t\t\t</output>\n";

         xmlDocument += "\t\t</object>\n";
      }
      else if (obj->GetParent()==NULL && obj->IsKindOf(RUNTIME_CLASS(DocumentDocumentation)))
      {
         DocumentDocumentation  *eobj  = (DocumentDocumentation*)obj;
         xmlDocument = xmlDocument+CString("\t<documentation>")+eobj->GetDocumentation()+"</documentation>\n";
      }
  	   else if(obj->GetParent()==NULL && obj->IsKindOf(RUNTIME_CLASS(CSerialInNode)))
      {
         CSerialInNode  *eobj  = (CSerialInNode*)obj;
         int i;
         sprintf(id,"%08X",obj);

         xmlDocument = xmlDocument + "\t\t<object" +
			                                     " id=\""+CString(id)+"\""+
												 " group=\""+eobj->GetGroup()+"\""+
												 " type=\"I_INTERFACE\""+
												 " positionX=\""+ int2string(eobj->GetLocation().x) + "\""+
												 " positionY=\""+ int2string(-eobj->GetLocation().y) + "\""+
												 " width=\""+ int2string(eobj->GetWidth())+"\""+
												 " height=\""+int2string(eobj->GetHeight())+"\""+
												 ">\n";
         //xmlDocument = xmlDocument + "\t\t<object id=\""+CString(id)+"\" group=\""+eobj->GetGroup()+"\" type=\"I_INTERFACE\">\n";

         // add all the inport to the object
         //
         xmlDocument += "\t\t\t<input>\n";
         xmlDocument += "\t\t\t</input>\n";

         // add all the outport to the object
         //
         xmlDocument += "\t\t\t<output>\n";
         for(i = 0 ;i<eobj->GetOutputCount(); i++)
         {
            CElectricPort* output = eobj->GetOutput(i); 
            sprintf(id,"%08X",output);
			if(output->GetLinks()!=NULL)
	            sprintf(fanOut,"%d",output->GetLinks()->GetCount());
			else
	            sprintf(fanOut,"0");

            xmlDocument = xmlDocument + "\t\t\t\t<port id=\""+CString(id)+"\" fanOut=\""+CString(fanOut)+"\"/>\n";
         }
         xmlDocument += "\t\t\t</output>\n";

         xmlDocument += "\t\t</object>\n";

	  }
	  else if(obj->GetParent()==NULL && obj->IsKindOf(RUNTIME_CLASS(CSerialOutNode)))
	  {
         CSerialOutNode  *eobj  = (CSerialOutNode*)obj;
         int i;
         sprintf(id,"%08X",obj);

         xmlDocument = xmlDocument + "\t\t<object" +
			                                     " id=\""+CString(id)+"\""+
												 " group=\""+eobj->GetGroup()+"\""+
												 " type=\"O_INTERFACE\""+
												 " positionX=\""+ int2string(eobj->GetLocation().x) + "\""+
												 " positionY=\""+ int2string(-eobj->GetLocation().y) + "\""+
												 " width=\""+ int2string(eobj->GetWidth())+"\""+
												 " height=\""+int2string(eobj->GetHeight())+"\""+
												 ">\n";
         //xmlDocument = xmlDocument + "\t\t<object id=\""+CString(id)+"\" group=\""+eobj->GetGroup()+"\" type=\"O_INTERFACE\">\n";

         // add all the inport to the object
         //
         xmlDocument += "\t\t\t<input>\n";
         for(i = 0 ;i<eobj->GetInputCount(); i++)
         {

            sprintf(id,"%08X",eobj->GetInput(i));
            xmlDocument = xmlDocument + "\t\t\t\t<port id=\""+CString(id)+"\"/>\n";
         }
         xmlDocument += "\t\t\t</input>\n";

         // add all the outport to the object
         //
         xmlDocument += "\t\t\t<output>\n";
         xmlDocument += "\t\t\t</output>\n";

         xmlDocument += "\t\t</object>\n";

	  }
   }
   xmlDocument += "\t</objects>\n";


   xmlDocument += "\t<links>\n";
   for( pos = GetFirstObjectPos(); pos != NULL; )
   {
      DragDropObject  *obj    = (DragDropObject*)GetNextObject(pos);

      if (obj->GetParent()==NULL && obj->IsKindOf(RUNTIME_CLASS(CElectricPortLink)))
      {
         CElectricPortLink *link     =(CElectricPortLink*)obj;
         DragDropPort      *toPort   = link->GetToPort();
         DragDropPort      *fromPort = link->GetFromPort();
         char toId[100];
         char fromId[100];

         sprintf(id,"%08X",link);
         sprintf(toId,"%08X",toPort);
         sprintf(fromId,"%08X",fromPort);

         xmlDocument = xmlDocument + "\t\t<link id=\""+CString(id)+"\" port1=\""+CString(toId)+"\" port2=\""+CString(fromId)+"\">\n";
		
		 
		 for(int loop = (link->NumPoints()-1) ; loop >=0; loop--)
		 {
			CPoint fulkrum  = link->GetPoint(loop);
			xmlDocument = xmlDocument + "\t\t\t<point positionX=\""+int2string(fulkrum.x)+"\" positionY=\""+int2string(-fulkrum.y)+"\" />\n";
		 }

		 xmlDocument = xmlDocument + "\t\t</link>\n";
      }
   }
   xmlDocument += "\t</links>\n";



   xmlDocument += "</circuit>\n";

   return xmlDocument;
}

//----------------------------------------------------------------------------
BOOL CDigitalTraineeStudioDoc::SaveModified(){
//----------------------------------------------------------------------------
	PROC_TRACE;

	if (!IsModified())
		return TRUE;        // ok to continue

	// get name/title of document
	CString name;
	if (m_strPathName.IsEmpty())	{
		// get name based on caption
		name = m_strTitle;
		if (name.IsEmpty())
			name = TRANSLATE("Unbekannt");
	}
	else	{
		// get name based on file title of path name
		name = m_strPathName;
	}


	char  prompt[2000];
	sprintf(prompt, TRANSLATE("COMMON.MESSAGE.WANTSAVEFILE"), name);
	switch (AfxMessageBox(prompt, MB_YESNOCANCEL, AFX_IDP_ASK_TO_SAVE))
	{
	case IDCANCEL:
		return FALSE;       // don't continue

	case IDYES:
		// If so, either Save or Update, as appropriate
		if (!DoFileSave())
			return FALSE;       // don't continue
		break;

	case IDNO:
		// If not saving changes, revert the document
		break;

	default:
		ASSERT(FALSE);
		break;
	}
	return TRUE;    // keep going
}
