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

#include "DragDropstdafx.h"
#include "DragDrop.h"
#include "DragDropApp.h"
#include "DragDropClientApp.h"
#include "DragDropBitmapCach.h"
IMPLEMENT_DYNCREATE(DragDropBitmapCacheDesc, CObject)


//----------------------------------------------------------------------------
DragDropBitmapCacheDesc::DragDropBitmapCacheDesc(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropBitmapCacheDesc::DragDropBitmapCacheDesc(CDC* pDC, CSize sizeBitmapDP, BOOL bTransparentBM){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_nRefCnt = 0;
    m_bValid = FALSE;   // not valid until drawn into
    m_sizeBitmapDP.cx = sizeBitmapDP.cx;
    m_sizeBitmapDP.cy = sizeBitmapDP.cy;
    
    // allocate a hunk of bitmap storage, DragDropAppMixIn helps manage this storage
    
    m_pBitmapStore = CDragDropApp::AllocBitmapStore (pDC, this, sizeBitmapDP, bTransparentBM); 
    ASSERT (m_pBitmapStore);
}


//----------------------------------------------------------------------------
DragDropBitmapCacheDesc::~DragDropBitmapCacheDesc(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}


//----------------------------------------------------------------------------
int DragDropBitmapCacheDesc::DecrementRefCnt(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    --m_nRefCnt;
    return m_nRefCnt;
}  


//----------------------------------------------------------------------------
CBitmap* DragDropBitmapCacheDesc::GetBitmapSrc(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_pBitmapStore->m_pBitmapSrc;
}

//---------------------------------------------------------------------------- 
CPoint DragDropBitmapCacheDesc::GetBitmapSrcOffset(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_ptSrcOffset;
}

//----------------------------------------------------------------------------
CSize DragDropBitmapCacheDesc::GetBitmapSize(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_sizeBitmapDP;
}

//----------------------------------------------------------------------------
void DragDropBitmapCacheDesc::SetBitmapSize(CSize szBitmapDP){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_sizeBitmapDP.cx = szBitmapDP.cx;
    m_sizeBitmapDP.cy = szBitmapDP.cy; 
}

//----------------------------------------------------------------------------
void DragDropBitmapCacheDesc::ResetBitmapSize(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_sizeBitmapDP.cx = m_nWidthWhenAllocated;
   m_sizeBitmapDP.cy = m_pBitmapStore->GetHeight();    
}


//----------------------------------------------------------------------------    
CBitmap* DragDropBitmapCacheDesc::GetBitmapMask(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pBitmapStore->m_pBitmapMask;
}

//----------------------------------------------------------------------------
CPoint DragDropBitmapCacheDesc::GetBitmapMaskOffset(){   
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_ptMaskOffset;
}



IMPLEMENT_DYNCREATE(DragDropBitmapCacheStore, CObject)

//----------------------------------------------------------------------------
DragDropBitmapCacheStore::DragDropBitmapCacheStore(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropBitmapCacheStore::DragDropBitmapCacheStore (CDC* pDC, int nWidth, int nHeight, BOOL bTransparent){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_pBitmapMask = NULL;
    
    m_nSizeStorePixels.cx = nWidth;
    m_nSizeStorePixels.cy = nHeight; 
    
    m_nFreeMark = 0;
    
                      
    m_pBitmapSrc = new CBitmap();   // create the Bitmap object
    m_pBitmapSrc->CreateCompatibleBitmap (pDC, m_nSizeStorePixels.cx, m_nSizeStorePixels.cy);
    ASSERT(m_pBitmapSrc->m_hObject != NULL);
    
    if (!bTransparent) return;
        
    
    m_pBitmapMask = new CBitmap();
    m_pBitmapMask->CreateBitmap(m_nSizeStorePixels.cx, m_nSizeStorePixels.cy, 1, 1, NULL); 
    ASSERT(m_pBitmapMask->m_hObject != NULL);        
}


//----------------------------------------------------------------------------
DragDropBitmapCacheStore::~DragDropBitmapCacheStore(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    delete m_pBitmapSrc;          
    m_pBitmapSrc = NULL;
    delete m_pBitmapMask;
    m_pBitmapMask = NULL;
}

//----------------------------------------------------------------------------
BOOL DragDropBitmapCacheStore::AllocBitmaps (DragDropBitmapCacheDesc* pDesc,CSize sizeBitmapDP, BOOL bTransparentBM){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (sizeBitmapDP.cy > m_nSizeStorePixels.cy) 
       return FALSE;
    
    if (sizeBitmapDP.cx > (m_nSizeStorePixels.cx - m_nFreeMark)) 
       return FALSE;
    
    int nOldFreeMark = m_nFreeMark;
    pDesc->m_ptSrcOffset.y = 0;
    pDesc->m_ptSrcOffset.x = m_nFreeMark;
    pDesc->m_ptMaskOffset.y = 0;
    pDesc->m_ptMaskOffset.x = m_nFreeMark;
    
    m_nFreeMark = m_nFreeMark + sizeBitmapDP.cx;   // bump up the Free Mark
    m_nFreeMark = (m_nFreeMark + 7) & ~7;           // round off to byte boundary
    
    pDesc->m_nWidthWhenAllocated = m_nFreeMark - nOldFreeMark; // maximum width
    return TRUE;
}                    
