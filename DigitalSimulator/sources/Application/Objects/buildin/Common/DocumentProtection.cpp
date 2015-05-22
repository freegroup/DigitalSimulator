#include "stdafx.h"
#include "sha.h"

#include "DocumentProtection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(DocumentProtection, DragDropObject, 2)

//----------------------------------------------------------------------------
DocumentProtection::DocumentProtection() :inherited(CPoint(0,0)){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DocumentProtection::~DocumentProtection(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void  DocumentProtection::SetDigest(byte* digest, int len){
//----------------------------------------------------------------------------
	PROC_TRACE;

   
   m_digest.RemoveAll();
   for(int i=0; i<len; i++)
   {
      m_digest.Add(digest[i]);
   }

}

//----------------------------------------------------------------------------
byte* DocumentProtection::GetDigest(){
//----------------------------------------------------------------------------
	PROC_TRACE;


   return m_digest.GetData();
}

//----------------------------------------------------------------------------
void DocumentProtection::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   m_digest.Serialize(ar);
}
