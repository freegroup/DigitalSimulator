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
#include "Application\DigitalSimulatorApp.h"

#include "ElectricNode.h"
#include "Application\Dialogs\ObjectDialogs\DialogPrimaryObjectOptions.h"
#include "ElectricNodeContext.h"



#define TITLE_TEXT_RGB          RGB(0,0,0)
#define LABEL_OFFSET    5

CMapStringToNodeContext* g_contextMap=NULL;

IMPLEMENT_REGISTER(CElectricNodeContext);

//-----------------------------------------------------------------------------
CElectricNodeContext::CElectricNodeContext(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   static bool isInit = false;

   if(isInit == false) {
      g_contextMap = new CMapStringToNodeContext;
   }
   isInit = true;
}


//-----------------------------------------------------------------------------
CElectricNodeContext* CElectricNodeContext::GetContext(CString metaName){
//-----------------------------------------------------------------------------
	PROC_TRACE;


   CElectricNodeContext *context;
   context =  (*g_contextMap)[metaName];
   if(context == NULL){
      context = (*g_contextMap)["OBJ_GENERIC"];
      TRACE("Konnte keinen gültigen ObjektContext für `%s` finden......Generic wird genommen\n",(LPCSTR)metaName);
   }

   assert(context!= NULL);

   return context;
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::SetInputCount( CElectricNode::CElectricNodeDokument& data, long count){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   // keine weitere Prüfung nötig (Prüfungen sind z.B. beim Demultiplex nötig)
   //
   data.inCount= count;
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::SetOutputCount(CElectricNode::CElectricNodeDokument& data, long count){
//-----------------------------------------------------------------------------
	PROC_TRACE;


   // keine weitere Prüfung nötig (Prüfungen sind z.B. beim Demultiplex nötig)
   //
   data.outCount= count;
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::Initialize(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.pOwner != NULL);

   data.size     = GetSize(data);

   data.pOwner->SetResizable(FALSE);
//   data.description = TRANSLATE (data.metaName+CString("_DESCRIPTION"));

   if(data.param==NULL && GetParamCount()!=0){
      data.param = new char[GetParamCount()];
   }

   SetInputCount (data, data.inCount );
   SetOutputCount(data, data.outCount);

   InitInputPorts(data);
   InitOutputPorts(data);
   InitIcon(data);   
//   InitLabel(data);
   Layout(data);
}

//-----------------------------------------------------------------------------
void CElectricNodeContext::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   for(long loop=0 ;loop <data.outPorts.GetSize() ; loop++) {
      data.outPorts[loop]->SetValue(data.logicState);
   }
}

//-----------------------------------------------------------------------------
void CElectricNodeContext::OnStartCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}

//-----------------------------------------------------------------------------
void CElectricNodeContext::OnStopCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}

//-----------------------------------------------------------------------------
void CElectricNodeContext::Layout(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


   LayoutInput(data);
   LayoutOutput(data);
//   LayoutLabel(data);
}

// Init group
//-----------------------------------------------------------------------------
void CElectricNodeContext::InitInputPorts(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.pOwner != NULL);
   int cx = GetInputCountRange().cx;
   int cy = GetInputCountRange().cy;

   data.inCount  = min(max(data.inCount ,cx) ,cy);

   long loop=0;
   if(data.inPorts.GetSize()==0 && data.inCount==0) {
       CElectricPort *m_tmpPort;
       for( loop=0; loop< cx;loop++) {
          m_tmpPort = new CElectricPort(data.location, PSLeft, PSLeft);
          m_tmpPort->Init(); 
          data.pOwner->AddChildAtTail(m_tmpPort);
          data.inPorts.Add(m_tmpPort);
       }
       data.inCount = data.inPorts.GetSize();
    }
    // data.inCount = die vom dialog (Benutzter) gewuenschte Anzahl
    // von Eingaengen
    //
    else if(data.inPorts.GetSize()> data.inCount){
       int start = data.inPorts.GetSize();
       for( loop=start; loop>data.inCount;loop--){
          delete data.inPorts[loop-1];   // free the object...
          data.inPorts.RemoveAt(loop-1); //       ...and the pointer in the array
       }
    }
    // data.inCount = die vom dialog (Benutzter) gewuenschte Anzahl
    // von Eingaengen
    //
    else if(data.inPorts.GetSize()< data.inCount)    {
       CElectricPort *m_tmpPort;
       for( loop=data.inPorts.GetSize(); loop<data.inCount;loop++)       {
          m_tmpPort = new CElectricPort(data.location, PSLeft, PSLeft);
          m_tmpPort->Init(); 
          data.pOwner->AddChildAtTail(m_tmpPort);
          data.inPorts.Add(m_tmpPort);
       }
    }


   for(loop=0 ;loop <data.inPorts.GetSize() ; loop++){
      data.inPorts[loop]->SetInverter(false);
      data.inPorts[loop]->SetInput(true);
      data.inPorts[loop]->SetOutput(false);
      data.inPorts[loop]->SetValue(CLogicValue::High);
   }
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::InitOutputPorts(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.pOwner != NULL);

   data.outCount = min(max(data.outCount,GetOutputCountRange().cx),GetOutputCountRange().cy);

    long loop=0;
    // Es wurden zuvor keine Ports erzeugt und es wurde auch 
    // in keinem Dialog eine Anzahl angegeben
    //
    if(data.outPorts.GetSize()==0 && data.outCount==0)    {
       CElectricPort *m_tmpPort;
       for( loop=0; loop<GetOutputCountRange().cx;loop++){ // cx = die mindest Anzahl von Eingaengen
          m_tmpPort = new CElectricPort(data.location, PSRight, PSRight);
          m_tmpPort->Init(); 
          data.pOwner->AddChildAtTail(m_tmpPort);
          data.outPorts.Add(m_tmpPort);
       }
       data.outCount = data.outPorts.GetSize();
    }
    // data.outCount = die vom dialog (Benutzter) gewuenschte Anzahl
    // von Eingaengen ist kleiner als die momentane Anzahl -> Ports entfernen
    //
    else if(data.outPorts.GetSize()> data.outCount){
       int start = data.outPorts.GetSize();
       for( loop=start; loop>data.outCount;loop--){
          delete data.outPorts[loop-1];   // free the object...
          data.outPorts.RemoveAt(loop-1); //       ...and the pointer in the array
       }
    }

    // data.outCount = die vom dialog (Benutzter) gewuenschte Anzahl
    // von Eingaengen ist groesser als die momentane Anzahl -> Ports erzeugen
    //
    else if(data.outPorts.GetSize()< data.outCount){
       CElectricPort *m_tmpPort;
       for( loop=data.outPorts.GetSize(); loop<data.outCount;loop++){
          m_tmpPort = new CElectricPort(data.location, PSRight, PSRight);
          m_tmpPort->Init(); 
          data.pOwner->AddChildAtTail(m_tmpPort);
          data.outPorts.Add(m_tmpPort);
       }

    }


   for(loop=0 ;loop <data.outPorts.GetSize() ; loop++){
      data.outPorts[loop]->SetInverter(false);
      data.outPorts[loop]->SetInput(false);
      data.outPorts[loop]->SetOutput(true);
   }
}

/*

//-----------------------------------------------------------------------------
void CElectricNodeContext::InitLabel(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   if(data.pLabel)
       delete data.pLabel;
    data.pLabel = NULL;
    
//    CPoint botleft = data.icons[0]->GetSpotLocation(DragDropObject::spotBottomCenter);
//    data.pLabel = new DragDropText(CPoint(botleft.x, botleft.y-LABEL_OFFSET), 
//                          CSize(0,50), data.metaName,DragDropText::DefaultFaceName,
//                          FW_NORMAL, FALSE, FALSE, TextTopMiddle);
//    data.pLabel->SetTextColor(TITLE_TEXT_RGB);
//    data.pLabel->SetBkMode(TRANSPARENT);
//    data.pLabel->SetSelectable(FALSE);
//    data.pOwner->AddChildAtTail(data.pLabel);
   
}
*/
//-----------------------------------------------------------------------------
void CElectricNodeContext::InitIcon(CElectricNode::CElectricNodeDokument& data) {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.pOwner != NULL);

   // Alle zuvor angelegten Icons erst einmal loeschen
   //
   for(int loop=0 ;loop <data.icons.GetSize() ; loop++) {
      delete data.icons[loop];
   }
   data.icons.RemoveAll();
 
   // jetzt die benoetigten Icons wieder anlegen
   //
   data.icons.SetAtGrow(0, new DragDropMetaFile(data.location, data.size, GetIconName(data), TRUE));
   data.icons[0]->SetSelectable(FALSE);
   data.pOwner->AddChildAtHead(data.icons[0]); 
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::InitParam(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   memset(data.param, 0, GetParamCount());
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::CleanupParam(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}


//-----------------------------------------------------------------------------
void CElectricNodeContext::selectIcon(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.icons[0] != NULL);

   data.icons[0]->SetMetaFileName(GetIconName(data));
}


//-----------------------------------------------------------------------------
CString CElectricNodeContext::GetIconName(CElectricNode::CElectricNodeDokument& data) const {
//-----------------------------------------------------------------------------
	PROC_TRACE;


   return  WMF_PATH( (LPCSTR)data.key +".wmf");
}

//-----------------------------------------------------------------------------
CString CElectricNodeContext::GetDescriptionText() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   return  CString(TRANSLATE(GetKey()+ "_DESCRIPTION"))+
           "\r\n"+
           "\r\n"+
           "\r\nObject type\t: buildin object"+
           "\r\nVersion\t\t: "+GetVersion()+
           "\r\nName\t\t: "+TRANSLATE(GetName())+
           "\r\nProgrammer\t: Andreas Herz"+
           "\r\nCompany\t\t: FreeGroup"+
           "\r\nLink\t\t: http://www.FreeGroup.de"
           ;
}

/*
//-----------------------------------------------------------------------------
void CElectricNodeContext::LayoutLabel(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   if(data.pLabel)   {
      CPoint p = data.icons[data.icons.GetSize()-1]->GetSpotLocation(DragDropObject::spotBottomCenter);
      data.pLabel->SetSpotLocation(DragDropObject::spotTopCenter,p.x ,p.y-5);
   }
}
*/

//-----------------------------------------------------------------------------
void CElectricNodeContext::LayoutOutput(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.icons.GetSize() >= 1);

   long   elements  = data.outPorts.GetSize();
//   CPoint topRight  = data.icons[0]->GetBoundingRect().TopLeft() + CPoint( data.icons[0]->GetBoundingRect().Width(),0);
   CPoint topRight  = data.location + CPoint(GetSize(data).cx,0);
   float  yOffset = data.icons[0]->GetBoundingRect().Height() / (float)(elements+1);

   for(long loop=0 ;loop <elements ; loop++)   {
      int xPos = topRight.x;
      int yPos = (int)(topRight.y+(yOffset*(loop+1)));

      data.outPorts[loop]->SetSpotLocation(DragDropObject::spotLeftCenter,xPos,yPos);
   }
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::LayoutInput(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.icons.GetSize() >= 1);

   long elements      = data.inPorts.GetSize();
//   CPoint  topLeft    = data.icons[0]->GetBoundingRect().TopLeft();
   CPoint  topLeft    = data.location;
   float   yOffset = data.icons[0]->GetBoundingRect().Height() / (float)(elements+1);


   for(long loop=0 ;loop <elements ; loop++)   {
      int xPos = topLeft.x;
      int yPos = (int)(topLeft.y+(yOffset*(loop+1)));

      data.inPorts[loop]->SetSpotLocation(DragDropObject::spotRightCenter,xPos,yPos);
   }
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::OnLButtonDblClk(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   
   onOption(data);
}


//-----------------------------------------------------------------------------
void CElectricNodeContext::OnLButtonClick(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


}


//-----------------------------------------------------------------------------
void CElectricNodeContext::OnLButtonUp(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


}


//-----------------------------------------------------------------------------
void CElectricNodeContext::OnLButtonDown(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


}

//-----------------------------------------------------------------------------
void CElectricNodeContext::OnGeometryChange(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


}

//-----------------------------------------------------------------------------
void CElectricNodeContext::OnMouseOverStart(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


}

//-----------------------------------------------------------------------------
void CElectricNodeContext::OnMouseOver(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


}

//-----------------------------------------------------------------------------
void CElectricNodeContext::OnMouseOverEnd(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;


}

//-----------------------------------------------------------------------------
void CElectricNodeContext::onOption(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.pOwner != NULL);

   CRect rect =data.pOwner->GetBoundingRect();
   rect.top    = -rect.top;
   rect.bottom = -rect.bottom;

   
   CDialogPrimaryObjectOptions d(NULL,data,rect);

   if(d.DoModal()==IDOK)   {
       Initialize(data);
   }
}
