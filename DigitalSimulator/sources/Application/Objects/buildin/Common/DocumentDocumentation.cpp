#include "stdafx.h"
#include "sha.h"

#include "DocumentDocumentation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(DocumentDocumentation, DragDropObject, 2)

//----------------------------------------------------------------------------
DocumentDocumentation::DocumentDocumentation() :inherited(CPoint(0,0)){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DocumentDocumentation::~DocumentDocumentation(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void  DocumentDocumentation::SetDocumentation(CString doc){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   m_documentation = doc;
}

//----------------------------------------------------------------------------
CString DocumentDocumentation::GetDocumentation(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_documentation;
}

//----------------------------------------------------------------------------
void DocumentDocumentation::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()){
       ar << m_documentation;
   }
   else{
       ar >> m_documentation;
   }
}
