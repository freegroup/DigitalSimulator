#include "stdafx.h"

#include "Application\Objects\buildin\digital\ElectricNode.h"
#include "Application\Dialogs\ObjectDialogs\DialogPluginObjectOptions.h"

#include "ElectricNodeContextPluginWrapper.h"


//-----------------------------------------------------------------------------
CElectricNodeContextPluginWrapper::CElectricNodeContextPluginWrapper(IObjectContext* pluginContext){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   m_pluginContext = pluginContext;
  	g_contextMap->SetAt(pluginContext->getKey(), this);
}



//-----------------------------------------------------------------------------
CElectricNodeContextPluginWrapper::~CElectricNodeContextPluginWrapper(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   // Falls das Objekt zerstört wird muss dieses auch seine Referenze 
   // auf den DLL-Context fallen lassen.
   //
   ((IObjectWorker*)m_pluginContext)->Destroy();
}

//----------------------------------------------------------------------------
CSize CElectricNodeContextPluginWrapper::GetSize(CElectricNode::CElectricNodeDokument& data) const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pluginContext->getSize( data.inPorts.GetSize(),data.outPorts.GetSize());
}

//----------------------------------------------------------------------------
CSize CElectricNodeContextPluginWrapper::GetInputCountRange() const {
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   return m_pluginContext->getInputCountRange();
}

//----------------------------------------------------------------------------
CSize CElectricNodeContextPluginWrapper::GetOutputCountRange() const {
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pluginContext->getOutputCountRange();
}

//----------------------------------------------------------------------------
DWORD CElectricNodeContextPluginWrapper::GetParamCount() const{
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   return m_pluginContext->getParamCount();
}

//-----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   char  *lastInputValues = new char[data.inPorts.GetSize()];
   char  *inputValues     = new char[data.inPorts.GetSize()];
   char  *outputValues    = new char[data.outPorts.GetSize()];
   long loop;

   // Daten in eine Struktur für die DLL übertragen
   //
   for(loop=0 ;loop <data.inPorts.GetSize() ; loop++) {
      inputValues[loop]= data.inPorts[loop]->GetValue().IsHigh();
   }
   for(loop=0 ;loop <data.inPorts.GetSize() ; loop++) {
      lastInputValues[loop]= data.inPorts[loop]->GetLastValue().IsHigh();
   }
   for(loop=0 ;loop <data.outPorts.GetSize() ; loop++) {
      outputValues[loop]= data.outPorts[loop]->GetValue().IsHigh();
   }


   // DLL für die Berechnung aufrufen
   //
   int update = m_pluginContext->calculate(inputValues, 
                              lastInputValues, 
                              data.inPorts.GetSize(), 
                              outputValues, 
                              data.outPorts.GetSize(), 
                              data.param);
   if(update)
      data.pOwner->SetUpdateNeeded(TRUE);

   // Berechnete Daten in die Ports übertragen
   //
   for(loop=0 ;loop <data.outPorts.GetSize() ; loop++) {
      data.outPorts[loop]->SetValue(outputValues[loop]==0?CLogicValue::Low:CLogicValue::High);
   }

   // alte Datenbereiche löschen
   //
   delete [] lastInputValues;
   delete [] inputValues;
   delete [] outputValues;
}


//-----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::OnStartCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   m_pluginContext->onStartCalculate(data.param);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::OnStopCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   m_pluginContext->onStopCalculate(data.param);
}


//-----------------------------------------------------------------------------
CString CElectricNodeContextPluginWrapper::GetIconName(CElectricNode::CElectricNodeDokument& data) const {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   return  WMF_PATH( "empty.wmf");
}


//-----------------------------------------------------------------------------
CString CElectricNodeContextPluginWrapper::GetDescriptionText() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   return  CString(m_pluginContext->getDescription())+
           "\r\n"+
           "\r\n"+
           "\r\nObject type\t: DLL-plugin object"+
           "\r\nVersion\t\t: "  + m_pluginContext->getVersion()+
           "\r\nBuild date\t\t: " + m_pluginContext->getBuildDate()+
           "\r\nName\t\t: "     + m_pluginContext->getName()+
           "\r\nProgrammer\t: " + m_pluginContext->getProgrammerName()+
           "\r\nMail\t\t: "     + m_pluginContext->getProgrammerMail()+
           "\r\nLink\t\t: "     + m_pluginContext->getProgrammerURL()
           ;
}

//-----------------------------------------------------------------------------
CString CElectricNodeContextPluginWrapper::GetGroup() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pluginContext->getGroup();
}


//-----------------------------------------------------------------------------
CString CElectricNodeContextPluginWrapper::GetName() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pluginContext->getName();
}

//-----------------------------------------------------------------------------
CString CElectricNodeContextPluginWrapper::GetKey() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pluginContext->getKey();
}

//----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::Initialize(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Initialize(data);

   // wird in der Basis nicht getan.....folgen nicht bekannt
   // falls dies in die Basis verschoben wird
   #pragma TODO("InitParam ist an dieser stelle eigentlich falsch...sollte in der Basis passieren")
   InitParam(data);
}


//-----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::InitIcon(CElectricNode::CElectricNodeDokument& data) {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::InitIcon(data);
   data.icons[0]->SetSize(GetSize(data));
}

//-----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::InitParam(CElectricNode::CElectricNodeDokument& data) {
//-----------------------------------------------------------------------------
	PROC_TRACE;

   m_pluginContext->initParam(data.param);
}


//-----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::CleanupParam(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   m_pluginContext->cleanupParam(data.param);
}


//----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::LayoutOutput(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   long  elements = data.outPorts.GetSize();
   long  *x       = new long[elements];
   long  *y       = new long[elements];
   long loop;


   m_pluginContext->layoutOutput(x, y,
                                 data.inPorts.GetSize(), 
                                 elements, 
                                 data.param);

   for( loop=0 ;loop <elements ; loop++)   {
      int xPos = x[loop] + data.location.x;
      int yPos = y[loop] + data.location.y;

      data.outPorts[loop]->SetSpotLocation(DragDropObject::spotLeftCenter,xPos,yPos);
   }

   delete[] x;
   delete[] y;
}

//----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::LayoutInput(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   long  elements = data.inPorts.GetSize();
   long  *x       = new long[elements];
   long  *y       = new long[elements];
   long   loop;


   m_pluginContext->layoutInput(x, y, 
                                data.inPorts.GetSize(),
                                data.outPorts.GetSize(), 
                                data.param);

   for( loop=0 ;loop <elements ; loop++)   {
      int xPos = x[loop] + data.location.x;
      int yPos = y[loop] + data.location.y;

      data.inPorts[loop]->SetSpotLocation(DragDropObject::spotLeftCenter,xPos,yPos);
   }

   delete[] x;
   delete[] y;
}


//----------------------------------------------------------------------------
bool CElectricNodeContextPluginWrapper::paint(CElectricNode::CElectricNodeDokument& data, CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pluginContext->paint(pDC, 
                          data.location , 
                          data.inPorts.GetSize(), 
                          data.outPorts.GetSize(), 
                          data.param);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextPluginWrapper::onOption(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;

   assert(data.pOwner != NULL);

   // Falls das Plugin-Object selbst keine Dialog
   // angezeigen kann, wird der Standartdialog angezeigt
   //
   if(m_pluginContext->doConfigure((HWND)AfxGetMainWnd() ,data.param)){
   }
   else{
      CDialogPluginObjectOptions d(NULL,data);

      if(d.DoModal()==IDOK)   {
         Initialize(data);
      }
   }
}

