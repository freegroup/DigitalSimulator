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
#include "DragDropApp.h"
#include "DragDropClientapp.h"
#include "DragDropPort.h"
#include <assert.h>

static CBitmap* m_pPortBitmap;

BOOL            DragDropAppMixIn::m_bMetafileUseBitmap;           // Metafile object bitmap cache on/off switch
CMapStringToOb  DragDropAppMixIn::m_mapBitmapDesc;                // name-> bitmap Descriptor map
CObList         DragDropAppMixIn::m_listBitmapStore;              // list of bitmap stores
CObList         DragDropAppMixIn::m_listFreeBitmapDesc;           // free bitmap descriptors  
CObList         DragDropAppMixIn::m_listFreeHandles;              // free DragDropHandle Objects  

COLORREF    DragDropAppMixIn::m_colorPrimary;             // Primary selection color
COLORREF    DragDropAppMixIn::m_colorSecondary;           // Secondary selection color
COLORREF    DragDropAppMixIn::m_colorBlack;               // index for Black
COLORREF    DragDropAppMixIn::m_colorWhite;               // index for White


DragDropPalette* DragDropAppMixIn::m_pPalette;
BOOL        DragDropAppMixIn::m_bUsingPalette;            // TRUE if Initialize is successful


CObList     DragDropAppMixIn::m_listPenCache;
CObList     DragDropAppMixIn::m_listBrushCache;
CGdiObject* DragDropAppMixIn::m_arrayGdiCache[255];
int         DragDropAppMixIn::m_nLastStockPen;
int         DragDropAppMixIn::m_nLastStockBrush;

//----------------------------------------------------------------------------
DragDropAppMixIn::DragDropAppMixIn(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   m_pPalette           = NULL;

}

//----------------------------------------------------------------------------
BOOL DragDropAppMixIn::Init(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Metrics::Init();
   Metrics::setPortGravity(100);

   m_bMetafileUseBitmap = TRUE;            // use metafile bitmap cache
   m_pPalette           = NULL;
   m_bUsingPalette      = FALSE;
   m_colorPrimary       = PRIMARY_RGB;
   m_colorSecondary     = SECONDARY_RGB;
   m_colorBlack         = RGB(0,0,0);              
   m_colorWhite         = RGB(255,255,255); 

   InvalidateStockCache();
   for (int i=0; i < 255; i++)
       m_arrayGdiCache[i] = NULL;

   return TRUE;
}

//----------------------------------------------------------------------------
int DragDropAppMixIn::stop(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropPort::AppRunDown();
    
   delete m_pPalette;
   m_pPalette = NULL;
    
   PurgeBitmapCaches();
   PurgePenAndBrushCaches();
   PurgeHandleCache();
   
   return 0;  
}


//----------------------------------------------------------------------------
BOOL DragDropAppMixIn::InitializePalette(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CWinApp* theapp = AfxGetApp();
   ASSERT (theapp->m_pMainWnd != NULL);    
    
   m_pPalette = new DragDropPalette();
   m_bUsingPalette = m_pPalette->Init (theapp->m_pMainWnd);

   // Convert the selection colors to palette indices.
    
   m_colorPrimary   = m_pPalette->GetPaletteIndex (m_colorPrimary);
   m_colorSecondary = m_pPalette->GetPaletteIndex (m_colorSecondary);
   m_colorBlack     = m_pPalette->GetPaletteIndex (RGB(0,0,0));               // index for Black
   m_colorWhite     = m_pPalette->GetPaletteIndex (RGB(255,255,255));         // index for White
    
   return m_bUsingPalette;
}

//----------------------------------------------------------------------------
DragDropPalette* DragDropAppMixIn::GetPalette(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_pPalette;
}
//----------------------------------------------------------------------------
CPalette* DragDropAppMixIn::GetCPalette(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   try{    
    if (m_bUsingPalette && m_pPalette != NULL) 
       return m_pPalette->GetPalette();
   }
   catch(...){
      // shit happens   :-(
      TRACE("Exception catched in 'CPalette* DragDropAppMixIn::GetCPalette()'");
   }
   return NULL;    
} 
//----------------------------------------------------------------------------
COLORREF DragDropAppMixIn::GetPaletteIndex (COLORREF color){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_bUsingPalette  && m_pPalette != NULL)
        return m_pPalette->GetPaletteIndex (color);
    else
        return color;
}


//----------------------------------------------------------------------------
void DragDropAppMixIn::SetPrimarySelectionColor (COLORREF color){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pPalette != NULL);

    m_colorPrimary = m_pPalette->GetPaletteIndex (color);
}
//----------------------------------------------------------------------------
void DragDropAppMixIn::UseSystemSelectionColor(){                                                    
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pPalette != NULL);

    m_colorPrimary = m_pPalette->GetPaletteIndex (::GetSysColor (COLOR_HIGHLIGHT));
}

//----------------------------------------------------------------------------
void DragDropAppMixIn::SetSecondarySelectionColor (COLORREF color){
//----------------------------------------------------------------------------
	PROC_TRACE;

   assert(m_pPalette != NULL);

    m_colorSecondary = m_pPalette->GetPaletteIndex (color);
}
//----------------------------------------------------------------------------
COLORREF DragDropAppMixIn::GetPrimarySelectionColor(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_colorPrimary;
}

//----------------------------------------------------------------------------
COLORREF DragDropAppMixIn::GetSecondarySelectionColor(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_colorSecondary;
}

    
    
//----------------------------------------------------------------------------
DragDropBitmapCacheDesc* DragDropAppMixIn::AllocBitmapDesc (CDC* pDC, const CString& sName,
                                                            CSize sizeBitmapDP, BOOL bTransparentBM){
//----------------------------------------------------------------------------

    // GetBitmapDesc returns a pointer to a DragDropBitmapCacheDesc object.
                          
    DragDropBitmapCacheDesc* pDesc;                        
    if (m_mapBitmapDesc.Lookup (sName, (CObject*&)pDesc)) {
        pDesc->IncrementRefCnt();
        return pDesc;
    }
    
    // Check the free list of Descriptors to see if there is one that fits.
    // The algorithm is best fit.
    
    DragDropBitmapCacheDesc* pDescCur;
    CSize szBitmapCur;
    CSize szBitmapBest; 
    pDesc = NULL;
    
    POSITION pos;
    for( pos = m_listFreeBitmapDesc.GetHeadPosition(); pos != NULL; )   {                   
        pDescCur = (DragDropBitmapCacheDesc*)m_listFreeBitmapDesc.GetNext(pos);
        szBitmapCur = pDescCur->GetBitmapSize();    // size of bitmap on free list
        if ((szBitmapCur.cx >= sizeBitmapDP.cx) && 
            (szBitmapCur.cy >= sizeBitmapDP.cy))       {
            // it fits.  see if this one is better than "best", if one exists yet
            if (pDesc)           {            
                if ((szBitmapCur.cx < szBitmapBest.cx) && (szBitmapCur.cy < szBitmapBest.cy)){ 
                    pDesc = pDescCur;               
                    szBitmapBest = pDesc->GetBitmapSize();    // size of bitmap on free list
                    }
            }
            else {
                pDesc = pDescCur;
                szBitmapBest = pDesc->GetBitmapSize();    // size of bitmap on free list
                }           
        }
    } // for loop
    
    // if pDesc in non-null, the loop found a bitmap that is big enough
    
    if (pDesc) {
        ASSERT (pDesc->RefCnt() == 0);
        pos = m_listFreeBitmapDesc.Find (pDesc);// find its position again
        m_listFreeBitmapDesc.RemoveAt (pos);    // pull pDesc out of Free list
        pDesc->SetBitmapSize(sizeBitmapDP);     // set the size of the requestor
        
    }
    else {
        // the cache didn't exist, it is time to create it      
        pDesc = new DragDropBitmapCacheDesc(pDC, sizeBitmapDP, bTransparentBM);  // create the object
    }

    m_mapBitmapDesc.SetAt (sName, pDesc);       // save it in the map
    pDesc->IncrementRefCnt();                   // increment the reference count
    return pDesc;
    
}


//----------------------------------------------------------------------------
void DragDropAppMixIn::DeallocBitmapDesc (const CString& sName){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropBitmapCacheDesc* pDesc;   
    if (m_mapBitmapDesc.Lookup (sName, (CObject*&)pDesc)) {
        if (pDesc->DecrementRefCnt() == 0){
            // count has gone to zero
            m_mapBitmapDesc.RemoveKey (sName);
            pDesc->ResetBitmapSize();                           // reset size to max on free
            m_listFreeBitmapDesc.AddHead (pDesc);               // add to free list         
        }                   
    }
}

//----------------------------------------------------------------------------
void DragDropAppMixIn::InvalidateBitmapDesc(const CString& sName){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // call this function when the contents of a metafile.wmf file have changed
    // and you want to invalidate all of the bitmap caches created from the
    // old file contents.  
           
    DragDropBitmapCacheDesc* pDesc;
    CString key;
    for (POSITION pos = m_mapBitmapDesc.GetStartPosition(); pos != NULL; ) {
        m_mapBitmapDesc.GetNextAssoc(pos, key, (CObject*&)pDesc);
        if (key.Find(sName) >= 0) 
            pDesc->Invalidate();  
    }
}

//----------------------------------------------------------------------------
void DragDropAppMixIn::PurgeBitmapCaches(){           
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Purges all of the bitmap caches

   if (!m_mapBitmapDesc.IsEmpty())
       TRACE0("DragDropAppMixIn::PurgeBitmapCaches, BitmapDesc Map not empty\n"); // assume that the in-use list in empty

   // Now go through the Free Descriptor list and delete them.

   DragDropBitmapCacheDesc* pDesc;
   while (!m_listFreeBitmapDesc.IsEmpty()){
       pDesc =(DragDropBitmapCacheDesc*)m_listFreeBitmapDesc.RemoveHead();
       delete pDesc;     // delete it
   }

   // Finally, delete the bitmap Stores.

   DragDropBitmapCacheStore* pStore;
   while (!m_listBitmapStore.IsEmpty()){
       pStore =(DragDropBitmapCacheStore*)m_listBitmapStore.RemoveHead();
       delete pStore;     // delete it
   }
}


//----------------------------------------------------------------------------
DragDropBitmapCacheStore* DragDropAppMixIn::AllocBitmapStore (CDC* pDC, DragDropBitmapCacheDesc* pDesc,CSize sizeBitmapDP, BOOL bTransparent){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Look down the list of existing Bitmap Stores to see if there is a 
   // chunk of bitmap that can be allocated from an existing one.
    
   DragDropBitmapCacheStore* pStore;
   POSITION pos;
    
   for( pos = m_listBitmapStore.GetHeadPosition(); pos != NULL; ){
       pStore =  (DragDropBitmapCacheStore*)m_listBitmapStore.GetNext(pos);
       if (pStore->AllocBitmaps (pDesc, sizeBitmapDP, bTransparent)) return pStore;
   }
    
   // If we fall through to here, there was no existing Store with bitmaps 
   // to allocate.  Create a new one and add it to the list.

   int nHeight = (sizeBitmapDP.cy + 7) & ~7;  // round height up to even 8
   int nWidth =  (sizeBitmapDP.cx + 7) & ~7;  // round width up to even 8
   nWidth = nWidth * BITMAP_CACHE_WIDTH_MULTIPLIER;    // wide enough for n of these bitmaps
    
   pStore = new DragDropBitmapCacheStore (pDC, nWidth, nHeight, bTransparent);
   ASSERT(pStore != NULL);
    
   m_listBitmapStore.AddHead (pStore); // add to list
    
   BOOL status = pStore->AllocBitmaps (pDesc, sizeBitmapDP, bTransparent); // should not fail
   if (status) 
      return pStore;
   ASSERT (status);
   return NULL;

}



//----------------------------------------------------------------------------
void DragDropAppMixIn::InvalidateStockCache(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_nLastStockPen   = 9999;
   m_nLastStockBrush = 9999;
}

//----------------------------------------------------------------------------
CPen* DragDropAppMixIn::AllocPen(int wStockIndex){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (wStockIndex != DragDropNoStock){
        if (wStockIndex == m_nLastStockPen) return (CPen*) NULL; // if the last one was the same, already set in DC
        
        ASSERT (wStockIndex <= 16 /*STOCK_LAST*/);  // until Go Stock objects are supported
        if (m_arrayGdiCache[wStockIndex] == NULL){
            ASSERT (wStockIndex >= WHITE_PEN && wStockIndex <= NULL_PEN);
            m_arrayGdiCache[wStockIndex] = new CPen();
            m_arrayGdiCache[wStockIndex]->CreateStockObject(wStockIndex);
        }
        ASSERT (m_arrayGdiCache[wStockIndex]->IsKindOf(RUNTIME_CLASS(CPen)));
        
        m_nLastStockPen = wStockIndex;
        return  (CPen*)m_arrayGdiCache[wStockIndex];
    }


    if (m_listPenCache.IsEmpty()){
        return new CPen();
    }
    else{
        return  (CPen*) m_listPenCache.RemoveHead();
    }
}

//----------------------------------------------------------------------------
void DragDropAppMixIn::DeallocPen(CPen* pPen, int wStockIndex){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (wStockIndex != DragDropNoStock) 
       return;
    ASSERT (pPen != NULL);
    pPen->DeleteObject();
    m_listPenCache.AddHead(pPen);
}

//----------------------------------------------------------------------------
CBrush* DragDropAppMixIn::AllocBrush(int wStockIndex){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (wStockIndex != DragDropNoStock) {
        if (wStockIndex == m_nLastStockBrush)
           return (CBrush*) NULL; 

        ASSERT (wStockIndex <= STOCK_LAST); 
        if (m_arrayGdiCache[wStockIndex] == NULL){
            ASSERT (wStockIndex >= WHITE_BRUSH && wStockIndex <= NULL_BRUSH);
            m_arrayGdiCache[wStockIndex] = new CBrush();
            m_arrayGdiCache[wStockIndex]->CreateStockObject(wStockIndex);
        }
        ASSERT (m_arrayGdiCache[wStockIndex]->IsKindOf(RUNTIME_CLASS(CBrush)));

        m_nLastStockBrush = wStockIndex;
        return  (CBrush*)m_arrayGdiCache[wStockIndex];
    }

    if (m_listBrushCache.IsEmpty()) {
        return new CBrush();
    }
    else{
        return  (CBrush*) m_listBrushCache.RemoveHead();
    }
}

//----------------------------------------------------------------------------
void DragDropAppMixIn::DeallocBrush(CBrush* pBrush, int wStockIndex){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (wStockIndex != DragDropNoStock)
      return;
   ASSERT (pBrush != NULL);
   pBrush->DeleteObject();
   m_listBrushCache.AddHead(pBrush);
}

//----------------------------------------------------------------------------
void DragDropAppMixIn::PurgePenAndBrushCaches(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Delete all of the Pens and Brushes in the lookaside lists.
    
   CPen* pPen;
   while (!m_listPenCache.IsEmpty()){
       pPen =(CPen*)m_listPenCache.RemoveHead();
       delete pPen;
   }

   CBrush* pBrush;
   while (!m_listBrushCache.IsEmpty()){
       pBrush =(CBrush*)m_listBrushCache.RemoveHead();
       delete pBrush;
   }
    
   for (int i=0; i < 255; i++){
       if (m_arrayGdiCache[i]){
            delete m_arrayGdiCache[i];
            m_arrayGdiCache[i] = NULL;
       }
   }
}




//----------------------------------------------------------------------------
DragDropHandle* DragDropAppMixIn::AllocHandle() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_listFreeHandles.IsEmpty()) {
        return NULL;
    }
    else{
        return  (DragDropHandle*) m_listFreeHandles.RemoveHead();
    }
}

//----------------------------------------------------------------------------
void DragDropAppMixIn::DeallocHandle(DragDropHandle* pHandle){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_listFreeHandles.AddHead((CObject*)pHandle);    
}


//----------------------------------------------------------------------------
void DragDropAppMixIn::PurgeHandleCache(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   while (!m_listFreeHandles.IsEmpty()) {
        delete m_listFreeHandles.RemoveHead();
    }
}



//----------------------------------------------------------------------------
void DragDropAppMixIn::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo, int nScale){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // In this application I want the x and y dimentions to be equal, so i could use MM_ISOTROPIC
    // however, since I calc the sizes myself , I use MM_ANISOTROPIC.

    static double PixelsPerUnit_x,PixelsPerUnit_y;
        
    pDC->SetMapMode(MM_ANISOTROPIC) ;  
    pDC->SetWindowExt(Metrics::getPixelsPerUnit(), Metrics::getPixelsPerUnit()) ;         
    int cxx;
    int cyy;    
                        
    if (pInfo != NULL){

        // We are printing or print previewing
        // So we must recalc the PixelsPerUni to be accurate on the device...
        PixelsPerUnit_x =  10.0 * pDC->GetDeviceCaps(HORZRES) / pDC->GetDeviceCaps(HORZSIZE);
        PixelsPerUnit_y =  10.0 * pDC->GetDeviceCaps(VERTRES) / pDC->GetDeviceCaps(VERTSIZE);  
        // Do not allow scaling of print views...
        cxx = (int) (PixelsPerUnit_x);
        cyy = (int) (-PixelsPerUnit_y) ;  
    }
    else{    

        CSize szRes = Metrics::getPixelsPerCM();
        PixelsPerUnit_x = (double)szRes.cx;
        PixelsPerUnit_y = (double)szRes.cy;
        cxx = (int) (PixelsPerUnit_x * nScale / 100 ) ;
        cyy = (int) (-PixelsPerUnit_y * nScale / 100 ) ;  
    }

    pDC->SetViewportExt(cxx , cyy ) ;
}   

 

//----------------------------------------------------------------------------//----------------------------------------------------------------------------
BOOL DragDropAppMixIn::OnQueryNewPalette(){ 
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC appDC(AfxGetApp()->m_pMainWnd);

    if (!m_bUsingPalette) 
       return FALSE;
    ASSERT (m_pPalette);
    CPalette *pPal       = m_pPalette->GetPalette();
    CPalette *oldPalette = appDC.SelectPalette(pPal, FALSE);

    if (oldPalette != NULL)    {
        UINT nColorsChanged = appDC.RealizePalette();
        if (nColorsChanged > 0){
          CWinApp* theapp = AfxGetApp();
          theapp->m_pMainWnd->SendMessageToDescendants (WM_DOREFRESH);    
        }
        appDC.SelectPalette(oldPalette, TRUE);
    }
    return TRUE;
}
