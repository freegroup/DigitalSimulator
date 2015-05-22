// ElectricNodeContextJavaWrapper.cpp: Implementierung der Klasse CElectricNodeContextJavaWrapper.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "JNIEnvHelper.h"

#include "Application\Objects\plugin\java\JavaPluginManager.h"
#include "Application\Objects\plugin\Java\Context\ElectricNodeContextJavaWrapper.h"
//#include "Application\JavaBinding\JNI_PluginManager.h"
#include "Application\JavaBinding\JNI_ObjectPlugin.h"


using namespace de::freegroup::jnipp;

extern CDC* javaPaintDC;

extern CString int2string(int i);



//-----------------------------------------------------------------------------
CElectricNodeContextJavaWrapper::CElectricNodeContextJavaWrapper(char* cls){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack; // automatic cleanup of the java stack after return

   peer = new ObjectPluginProxyExtender(cls);
   paramCount = peer->getParamCount();
  	g_contextMap->SetAt(GetKey(), this);
}

//-----------------------------------------------------------------------------
CElectricNodeContextJavaWrapper::~CElectricNodeContextJavaWrapper(){
//-----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
CSize CElectricNodeContextJavaWrapper::GetSize(CElectricNode::CElectricNodeDokument& data) const{
//----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jint> result = peer->getSize(data.inCount ,data.outCount );

   return CSize(result.get(0),result.get(1));
}


//----------------------------------------------------------------------------
CSize CElectricNodeContextJavaWrapper::GetInputCountRange() const {
//----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack; // automatic cleanup of the java stack after return

   PrimitiveArray<jint> result = peer->getInputCountRange( );

   return CSize(result.get(0),result.get(1));
}


//----------------------------------------------------------------------------
CSize CElectricNodeContextJavaWrapper::GetOutputCountRange() const {
//----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack; // automatic cleanup of the java stack after return

   PrimitiveArray<jint> result = peer->getOutputCountRange( );

   return CSize(result.get(0),result.get(1));
}


//----------------------------------------------------------------------------
DWORD CElectricNodeContextJavaWrapper::GetParamCount() const{
//----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack; // automatic cleanup of the java stack after return

	return peer->getParamCount();
}


//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::DoCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   jint *_input     = new jint[data.inCount];
   jint *_lastInput = new jint[data.inCount];
   jint *_output    = new jint[data.outCount];

   // Daten in eine Struktur für die DLL übertragen
   //
   for(int loop=0 ;loop <data.inPorts.GetSize() ; loop++) {
      _input[loop]= data.inPorts[loop]->GetValue().IsHigh();
   }
   for( loop=0 ;loop <data.inPorts.GetSize() ; loop++) {
      _lastInput[loop]= data.inPorts[loop]->GetLastValue().IsHigh();
   }
   for(loop=0 ;loop <data.outPorts.GetSize() ; loop++) {
      _output[loop]= data.outPorts[loop]->GetValue().IsHigh();
   }

   PrimitiveArray<jint> input(_input, data.inPorts.GetSize());
   PrimitiveArray<jint> lastInput(_lastInput, data.inPorts.GetSize());
   PrimitiveArray<jint> output(_output, data.outPorts.GetSize());

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->calculate(input, lastInput, output, param))
      data.pOwner->SetUpdateNeeded(TRUE);

   param.fill((jbyte*)data.param,paramCount);

   // Berechnete Daten in die Ports übertragen
   //
   for(loop=0 ;loop <data.outPorts.GetSize() ; loop++) {
      data.outPorts[loop]->SetValue(output.get(loop)==0?CLogicValue::Low:CLogicValue::High);
   }

   delete[] _input;
   delete[] _lastInput;
   delete[] _output;
}


//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnStartCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   peer->onStartCalculate(param);
   param.fill((jbyte*)data.param,paramCount);

}

//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnStopCalculate(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   peer->onStopCalculate(param);
   param.fill((jbyte*)data.param,paramCount);
}


//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnLButtonDblClk(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->onButtonDblClick(data.mousePos.x, data.mousePos.y, param))
   {
      data.pOwner->SetUpdateNeeded(TRUE);
      param.fill((jbyte*)data.param,paramCount);
	  // reeinit the object. It is possible that the count of ports has been
	  // changed (in/out) or that the object has been resized.
	  //
      Initialize(data);
   }
}


//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnLButtonClick(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->onButtonClick(data.mousePos.x, data.mousePos.y, param))
      data.pOwner->SetUpdateNeeded(TRUE);

   param.fill((jbyte*)data.param,paramCount);
}


//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnLButtonUp(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->onButtonUp(data.mousePos.x, data.mousePos.y, param))
      data.pOwner->SetUpdateNeeded(TRUE);

   param.fill((jbyte*)data.param,paramCount);
}


//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnLButtonDown(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->onButtonDown(data.mousePos.x, data.mousePos.y, param))
      data.pOwner->SetUpdateNeeded(TRUE);

   param.fill((jbyte*)data.param,paramCount);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnMouseOverStart(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->onMouseOverStart(data.mousePos.x, data.mousePos.y, param))
      data.pOwner->SetUpdateNeeded(TRUE);

   param.fill((jbyte*)data.param,paramCount);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnMouseOver(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->onMouseOver(data.mousePos.x, data.mousePos.y, param))
      data.pOwner->SetUpdateNeeded(TRUE);

   param.fill((jbyte*)data.param,paramCount);
}

//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::OnMouseOverEnd(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->onMouseOverEnd(data.mousePos.x, data.mousePos.y, param))
      data.pOwner->SetUpdateNeeded(TRUE);

   param.fill((jbyte*)data.param,paramCount);
}

//-----------------------------------------------------------------------------
CString CElectricNodeContextJavaWrapper::GetIconName(CElectricNode::CElectricNodeDokument& data) const {
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   return  WMF_PATH( "empty.wmf");
}

//-----------------------------------------------------------------------------
CString CElectricNodeContextJavaWrapper::GetKey() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack; // automatic cleanup of the java stack after return

   return  peer->getKey();
}


//-----------------------------------------------------------------------------
CString CElectricNodeContextJavaWrapper::GetDescriptionText() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack; // automatic cleanup of the java stack after return
   CString desc =  peer->getDescription();
   desc.Replace("\n","\r\n");
   return desc +
           "\r\n"+
           "\r\n"+
           "\r\nObject type\t: JAVA-plugin object"+
           "\r\nVersion\t\t: "  + int2string(peer->getVersion())+
           "\r\nName\t\t: "     + TRANSLATE(peer->getName())+
           "\r\nProgrammer\t: " + peer->getProgrammerName()+
           "\r\nMail\t\t: "     + peer->getProgrammerMail()+
           "\r\nLink\t\t: "     + peer->getProgrammerURL()
           ;
}

//-----------------------------------------------------------------------------
CString CElectricNodeContextJavaWrapper::GetGroup() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack; // automatic cleanup of the java stack after return

   return  peer->getGroup();
}

//-----------------------------------------------------------------------------
CString CElectricNodeContextJavaWrapper::GetName() const {
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack; // automatic cleanup of the java stack after return

   return  peer->getName();
}

//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::InitIcon(CElectricNode::CElectricNodeDokument& data) {
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   inherited::InitIcon(data);
   data.icons[0]->SetSize(GetSize(data));
}

//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::Initialize(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   // create the required ports (in/out) and setup the data structure
   // for the new object
   inherited::Initialize(data);

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   peer->init(param);
   param.fill((jbyte*)data.param,paramCount);

   // Normaly the method 'Initialize(data)' do the layout.
   // BUT: The 'init(..)' in the Java object can change the preconditions 
   // for the layout information. So call the layout method after the post init.
   //
   inherited::Layout(data);
}


//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::InitParam(CElectricNode::CElectricNodeDokument& data) {
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   


}


//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::CleanupParam(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   // wird in dem JAVA plugin nicht benötigt, da diese keinen Speicher
   // freigeben kann......macht nur bei den DLL-Plugins Sinn.
   // Diese geben einen EVENTUELL angelegten Speicher frei dessen Zeiger
   // sie in dem data.param Parameter abgelegt haben
   //
}


//----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::LayoutOutput(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   PrimitiveArray<jint> result = peer->layoutOutput(data.inCount ,data.outCount ,param);
   param.fill((jbyte*)data.param,paramCount);

   for(int loop=0; loop< (data.outCount*2);loop+=2)
   {
      int x = data.location.x + result.get(loop);
      int y = data.location.y + result.get(loop+1);
      data.outPorts[loop/2]->SetSpotLocation(DragDropObject::spotLeftCenter,x,y);
   }
}

//----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::LayoutInput(CElectricNode::CElectricNodeDokument& data){
//----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);
   PrimitiveArray<jint> result = peer->layoutInput(data.inCount ,data.outCount,param );
   param.fill((jbyte*)data.param,paramCount);
   for(int loop=0; loop< (data.inCount*2);loop+=2)
   {
      int x = data.location.x + result.get(loop);
      int y = data.location.y + result.get(loop+1);
      data.inPorts[loop/2]->SetSpotLocation(DragDropObject::spotRightCenter,x,y);
   }
}


//----------------------------------------------------------------------------
bool CElectricNodeContextJavaWrapper::paint(CElectricNode::CElectricNodeDokument& data, CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   javaPaintDC=pDC;

   pDC->SetBkMode(TRANSPARENT);
   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);
   peer->paint(data.location.x, data.location.y, param );
   param.fill((jbyte*)data.param,paramCount);

   javaPaintDC=NULL;

	return false;

}

//-----------------------------------------------------------------------------
void CElectricNodeContextJavaWrapper::onOption(CElectricNode::CElectricNodeDokument& data){
//-----------------------------------------------------------------------------
	PROC_TRACE;
   JNIStack stack;        // automatic cleanup of the java stack after return
   TRANSFER_OBJECT_DATA;  // enable the access to the object data via JNI   

   PrimitiveArray<jbyte> param((jbyte*)data.param, paramCount);

   if(peer->doConfigure(param))
   {
      data.pOwner->SetUpdateNeeded(TRUE);
      param.fill((jbyte*)data.param,paramCount);
	  // reeinit the object. It is possible that the count of ports has been
	  // changed (in/out) or that the object has been resized.
	  //
      Initialize(data);
   }

}



