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
#include "defines.h"
#include "DragDropApp.h"
#include "DragDropClientApp.h"
#include "wmfdecode.h"   // for metafile routines
#include "mmsystem.h"   // for devicecaps Transparent stuff
#include "math.h"       // for aspect ratio calculations
#include "DragDropMetafile.h"
#include "DragDropObject.h"   
#include "DragDropDocument.h"
#include "DragDropView.h"

static BOOL bTransparentBM = TRUE;


#ifdef _WIN32

#define     GlobalPtrHandle(lp)         \
                ((HGLOBAL)GlobalHandle(lp))
#define     GlobalAllocPtr(flags, cb)        \
                (GlobalLock(GlobalAlloc((flags), (cb))))
#define     GlobalFreePtr(lp)                \
                (GlobalUnlockPtr(lp), (BOOL)GlobalFree(GlobalPtrHandle(lp)))
#define     GlobalLockPtr(lp)                \
                ((BOOL)GlobalLock(GlobalPtrHandle(lp)))
#define     GlobalUnlockPtr(lp)      \
                GlobalUnlock(GlobalPtrHandle(lp))
#define     GlobalSizePtr(lp)       \
                (GlobalUnlockPtr(lp), (BOOL)GlobalSize(GlobalPtrHandle(lp)))

#ifdef VERYLARGE

#pragma pack( push )
#pragma pack( 2 )
typedef struct{
	DWORD	  	dwKey;
	WORD		hmf;
	SMALL_RECT	bbox;
	WORD		wInch;
	DWORD		dwReserved;
	WORD		wCheckSum;
} PAPMHEADER, FAR *LPPAPMHEADER;

#pragma pack( pop )

#endif //VERYLARGE
#else      // WIN 16
/*
#define     GlobalPtrHandle(lp)         ((HGLOBAL)LOWORD(GlobalHandle(SELECTOROF(lp))))
#define     GlobalLockPtr(lp)           ((BOOL)SELECTOROF(GlobalLock(GlobalPtrHandle(lp))))
#define     GlobalUnlockPtr(lp)         GlobalUnlock(GlobalPtrHandle(lp))
#define     GlobalAllocPtr(flags, cb)   (GlobalLock(GlobalAlloc((flags), (cb))))
#define     GlobalFreePtr(lp)           (GlobalUnlockPtr(lp), (BOOL)GlobalFree(GlobalPtrHandle(lp)))
*/
#endif


IMPLEMENT_SERIAL(DragDropMetaFile, DragDropObject, 2)


//----------------------------------------------------------------------------
DragDropMetaFile::DragDropMetaFile(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_fileName       = _T("");
   m_bitmapDesc     = NULL;
   m_aspectRatio    = 1;
   m_maintainAspect = FALSE;
}


//----------------------------------------------------------------------------
DragDropMetaFile::DragDropMetaFile(CRect* pRect, const CString& pMetaFile) : DragDropObject(pRect){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_fileName   = _T("");
   m_aspectRatio    = 1.0F;
   m_bitmapDesc     = NULL;
   m_maintainAspect = FALSE;
   SetMetaFileName(pMetaFile);
}

DragDropMetaFile::DragDropMetaFile(CPoint location, CSize size, const CString& pMetaFile, BOOL bMaintainAspect) 
    : DragDropObject(location, size){                            
    m_fileName   = _T("");
    m_aspectRatio    = 1.0F;
    m_bitmapDesc     = NULL;
    m_maintainAspect = bMaintainAspect;
    SetMetaFileName(pMetaFile);

    
    if (size.cx == 0){
        // width is 0, use aspect ratio to set width from Height
        size.cx = int(size.cy * AspectRatio());
        SetSize(size);
    }                                                         
    else if (size.cy == 0){
        // height is 0, use aspect ratio to set Height from Width
        size.cy = int(size.cx * (1.0/AspectRatio()));
        SetSize(size);
    }
    else if (bMaintainAspect){
        // use the width and height as maximums and force the
        // biggest graphic possible within these bounds.
        int w = int(size.cy * AspectRatio());
        int h = int(size.cx * (1.0/AspectRatio()));
        if (w < size.cx){
            size.cx = w;
        }
        else{
            size.cy = h;
        }
        SetSize(size);
    }
}

//----------------------------------------------------------------------------
DragDropMetaFile::~DragDropMetaFile(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ClearBitmapCache(GetWidth(), GetHeight()); 
}

//----------------------------------------------------------------------------
DragDropObject* DragDropMetaFile::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pObject = inherited::Clone();     // call the base class to create the object
   ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropMetaFile)));                  
   DragDropMetaFile* pMetaFile =(DragDropMetaFile*) pObject; 

   pMetaFile->m_maintainAspect = m_maintainAspect;
   pMetaFile->m_aspectRatio = m_aspectRatio;
   pMetaFile->SetMetaFileName(m_fileName);
   return pObject;
}
 

//----------------------------------------------------------------------------
void DragDropMetaFile::GeometryChange(CRect* pRectPrevious){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int w,h;
   w = abs(pRectPrevious->right - pRectPrevious->left);
   h = abs(pRectPrevious->bottom - pRectPrevious->top);
   if ((GetWidth() != w) || GetHeight() != h){
       ClearBitmapCache(w, h);         
   }
}

//----------------------------------------------------------------------------
CString DragDropMetaFile::MetaFileName() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

   return m_fileName;
}

//----------------------------------------------------------------------------
void DragDropMetaFile::SetMetaFileName(const CString& sNewMetaFileName){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_fileName != sNewMetaFileName){
      ClearBitmapCache(GetWidth(), GetHeight());
      m_fileName = sNewMetaFileName;
      m_aspectRatio = GetAspectRatio(sNewMetaFileName); 
      SetUpdateNeeded(TRUE);
   }
}

//----------------------------------------------------------------------------
BOOL DragDropMetaFile::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!isVisible()) 
       return TRUE;
    
    // allow for the MetaFileName() function to be overriden and actually
    // change the name behind our backs!
    
    CString sMetaFileName = MetaFileName();
    if (m_fileName != sMetaFileName) SetMetaFileName(sMetaFileName);

#ifdef VERYLARGE
	HENHMETAFILE henh = ReadEnhMetaFile(sMetaFileName);
	pDC->SetStretchBltMode(COLORONCOLOR );
	::PlayEnhMetaFile(pDC->m_hDC, henh, GetBoundingRect() );
	return TRUE;
#endif

    if (sMetaFileName.IsEmpty()){
        TRACE0("DragDropMetaFile with no Metafile\n");
        DragDropObject::paint(pDC); // call the base class default draw
        return TRUE;
    }
    
    DragDropView* pView;
    if (m_pDocument) 
       pView = m_pDocument->GetCurrentDrawView();
    else 
       pView = m_pView;
    int nScale =100;
    if (pView) 
       nScale = pView->GetScale();
    

    BOOL bReallyPrinting = pDC->IsPrinting();
    BOOL bPrintPreview = (pView && pView->IsPrintPreview());
    if (bPrintPreview) bReallyPrinting = FALSE;  
    
    if (CDragDropApp::GetMetafileUseBitmap() && !bReallyPrinting) {               
        if (DrawBitmap(pDC, nScale)) 
           return TRUE;               
    }

    CRect devRect = GetBoundingRect();
    if (bPrintPreview) {
        CDC* pATC = CDC::FromHandle(pDC->m_hAttribDC);
        pATC->LPtoDP(&devRect);
    } 
    else {
        pDC->LPtoDP(&devRect);
    }
    
    int saved = pDC->SaveDC();
                                 
    if (!ProcessFile(sMetaFileName.GetBuffer(0)))
        return FALSE; 
    if (!PlayMetaFileToDest(pDC->m_hDC, sMetaFileName, devRect, pDC->IsPrinting()))  // draw file to devRect area
        return FALSE;
    MetafileCleanup();

    pDC->RestoreDC(saved); 
        
    return TRUE;
}                                                                            

//----------------------------------------------------------------------------
BOOL DragDropMetaFile::DrawBitmap(CDC* pDC, int nScale){
//----------------------------------------------------------------------------
	PROC_TRACE;

   BOOL status;
   if (!m_bitmapDesc || !m_bitmapDesc->IsValid()) {
        if (nScale < 100) 
            return FALSE;
        if (!CreateBitmap(pDC)) 
            return FALSE;
   }
   ASSERT(m_bitmapDesc != NULL);  
    
    
    CDC dcMemSrc, dcMemMask;
    CSize sizeLP (GetWidth(), -GetHeight());

    // set up the source
    CBitmap* pBitmapSrc = m_bitmapDesc->GetBitmapSrc();     // "source" bitmap
    ASSERT (pBitmapSrc != NULL);
    CPoint ptOffsetSrc =  m_bitmapDesc->GetBitmapSrcOffset();  // offset to start of source bitmap
    CSize sizeBitmapDP =   m_bitmapDesc->GetBitmapSize();    // size of both bitmaps (in pixels)
    
    status = dcMemSrc.CreateCompatibleDC(pDC);
    CBitmap* pbmOld = dcMemSrc.SelectObject(pBitmapSrc);
    int nmmOld = dcMemSrc.SetMapMode(MM_TEXT);  //! shall use pixels 

    // do the palette selection
    CPalette* pPal = CDragDropApp::GetCPalette();
    CPalette* pOldPal;
    if (pPal) {
        pOldPal = dcMemSrc.SelectPalette (pPal, TRUE);
    }   
    
    CRect rect = DragDropObject::GetBoundingRect();

	if (bTransparentBM) {
        CBitmap* pBitmapMask = m_bitmapDesc->GetBitmapMask();    // "mask" bitmap
        ASSERT (pBitmapMask != NULL);
        CPoint ptOffsetMask =  m_bitmapDesc->GetBitmapMaskOffset();  // offset to start of Mask bitmap
    
        status = dcMemMask.CreateCompatibleDC(pDC);
        CBitmap* pbmOldMask = dcMemMask.SelectObject(pBitmapMask);
        int nmmOldMask = dcMemMask.SetMapMode(MM_TEXT); //! shall use pixels 

        COLORREF oldBk = dcMemSrc.SetBkColor(RGB(255,255,255));     // set WHITE to be transparent color
        COLORREF oldTC = dcMemSrc.SetTextColor(RGB(0,0,0));     // set BLACK to be fg color

        ASSERT (ptOffsetSrc.y == 0);
        
        int saved2 = pDC->SaveDC();
    
        CPoint pt;
        pt.x = rect.left;
        pt.y = rect.top;         
        
        
         status = pDC->StretchBlt(pt.x, pt.y, sizeLP.cx, sizeLP.cy, &dcMemMask, 
              ptOffsetSrc.x, ptOffsetSrc.y, sizeBitmapDP.cx, sizeBitmapDP.cy, SRCAND);   
         status = pDC->StretchBlt(pt.x, pt.y, sizeLP.cx, sizeLP.cy, &dcMemSrc, 
              ptOffsetSrc.x, ptOffsetSrc.y, sizeBitmapDP.cx, sizeBitmapDP.cy, SRCPAINT); 
        pDC->RestoreDC(saved2);    // reset DC
        dcMemSrc.SetBkColor(oldBk);
        dcMemSrc.SetTextColor(oldTC); 
        
        dcMemMask.SetMapMode(nmmOldMask);
        dcMemMask.SelectObject(pbmOldMask);
    }
    else {
        status = pDC->StretchBlt(rect.left, rect.top, sizeLP.cx, sizeLP.cy, &dcMemSrc, 
             ptOffsetSrc.x, ptOffsetSrc.y, sizeBitmapDP.cx, sizeBitmapDP.cy, SRCCOPY);      
    }       
    if (pPal) dcMemSrc.SelectPalette (pOldPal, TRUE);
    dcMemSrc.SetMapMode(nmmOld);
    dcMemSrc.SelectObject(pbmOld);

    return TRUE;
}

//----------------------------------------------------------------------------
BOOL DragDropMetaFile::CreateBitmap(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CRect rectDP = GetBoundingRect();
    CSize sizeBitmapLP (rectDP.right-rectDP.left, abs(rectDP.bottom-rectDP.top));  // rect still LP here
    pDC->LPtoDP (&rectDP);            // size in pixels                            // now rect is DP
    CSize sizeBitmapDP (rectDP.right-rectDP.left, abs(rectDP.bottom-rectDP.top));

    CString sMetaFileName = MetaFileName();
    
    if (!m_bitmapDesc) {
        CString sName;
        sName.Format(_T("%d %d %s"), sizeBitmapLP.cx, sizeBitmapLP.cy, sMetaFileName); 
    
        m_bitmapDesc = CDragDropApp::AllocBitmapDesc (pDC, sName, sizeBitmapDP, bTransparentBM); 
        if (!m_bitmapDesc) 
           return FALSE;
    
        if (m_bitmapDesc->RefCnt() > 1) 
           return TRUE;
    }

    CBitmap* pBitmapSrc = m_bitmapDesc->GetBitmapSrc();     // "source" bitmap
    ASSERT (pBitmapSrc != NULL);
    CPoint ptOffsetSrc =  m_bitmapDesc->GetBitmapSrcOffset();  // offset to start of source bitmap
                  
    // setup and save the source bitmap DC
    CDC dcMemSrc;
    dcMemSrc.CreateCompatibleDC(pDC);
    int saved = dcMemSrc.SaveDC();

    CBitmap* pOldBitmap = dcMemSrc.SelectObject(pBitmapSrc);
    dcMemSrc.SetMapMode(MM_TEXT);
    // do the palette selection
    CPalette* pPal = CDragDropApp::GetCPalette();
    CPalette* pOldPal;
    if (pPal) {
        pOldPal = dcMemSrc.SelectPalette (pPal, TRUE);
    }   

    CRect rectSrc(ptOffsetSrc.x, ptOffsetSrc.y, 
                    sizeBitmapDP.cx + ptOffsetSrc.x, 
                    sizeBitmapDP.cy + ptOffsetSrc.y);


    CBrush brBackground;  
    brBackground.CreateStockObject(WHITE_BRUSH);  // fill source bitmap with WHITE 
    
    dcMemSrc.FillRect(rectSrc, &brBackground);
    
    // play the metafile into the bitmap
    if (!ProcessFile(sMetaFileName.GetBuffer(0)))
        return FALSE;
    int saved_for_meta = dcMemSrc.SaveDC();
    
    // draw file to rect area in bitmap 
    if (!PlayMetaFileToDest(dcMemSrc.m_hDC, sMetaFileName, rectSrc, FALSE)) {  
        MetafileCleanup();
        return FALSE;
    }
    dcMemSrc.RestoreDC(saved_for_meta);

    if (!bTransparentBM) 
    {
        if (pPal) dcMemSrc.SelectPalette (pOldPal, TRUE);
        dcMemSrc.SelectObject(pOldBitmap);
        dcMemSrc.RestoreDC(saved);
        m_bitmapDesc->Validate();      // signal the bitmap is OK to use 
        MetafileCleanup(); 
        return TRUE;
    }
    
    CBitmap* pBitmapMask = m_bitmapDesc->GetBitmapMask();    // "mask" bitmap
    ASSERT (pBitmapMask != NULL);
    CPoint ptOffsetMask =  m_bitmapDesc->GetBitmapMaskOffset();  // offset to start of Mask bitmap
    
    // setup the mask bitmap DC
    CDC dcMemMask;
    dcMemMask.CreateCompatibleDC(pDC);
    CBitmap* pbmOldMask = dcMemMask.SelectObject(pBitmapMask);
    int nmmOldMask = dcMemMask.SetMapMode(MM_TEXT);         //! shall use pixels 

    COLORREF oldBk = dcMemMask.SetBkColor(RGB(255,255,255));    // set WHITE to be transparent color
    COLORREF oldTC = dcMemMask.SetTextColor(RGB(0,0,0));        // set BLACK to be fg color
    int status = dcMemMask.BitBlt(rectSrc.left, rectSrc.top, sizeBitmapDP.cx, sizeBitmapDP.cy, 
            &dcMemSrc, ptOffsetMask.x, ptOffsetMask.y, SRCCOPY); // create mask
    dcMemMask.SetBkColor(oldBk);
    dcMemMask.SetTextColor(oldTC);
                                                                       
    CBrush brBackgroundBlack(RGB (0,0,0));  // fill source bitmap with BLACK
    dcMemSrc.FillRect(rectSrc, &brBackgroundBlack);
    if (!PlayMetaFileToDest(dcMemSrc.m_hDC, sMetaFileName, rectSrc, FALSE)) {
        MetafileCleanup();
        return FALSE;
    }
            
    dcMemMask.SetMapMode(nmmOldMask);
    dcMemMask.SelectObject(pbmOldMask);
                            
    if (pPal) dcMemSrc.SelectPalette (pOldPal, TRUE);
    dcMemSrc.SelectObject(pOldBitmap);
    dcMemSrc.RestoreDC(saved);
    m_bitmapDesc->Validate();      // signal the bitmap is OK to use 
    MetafileCleanup(); 
    return TRUE;
} 

//----------------------------------------------------------------------------
void DragDropMetaFile::ClearBitmapCache(int width, int height){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (m_bitmapDesc == NULL) 
       return;
    
    CString sMetaFileName = MetaFileName();
    
    CString sName;
    sName.Format(_T("%d %d %s"), width, height, sMetaFileName); 

    CDragDropApp::DeallocBitmapDesc (sName);
    m_bitmapDesc = NULL;
}


//----------------------------------------------------------------------------
void DragDropMetaFile::Serialize(CArchive& ar){   
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);
   if (ar.IsStoring()) {
       ar << MetaFileName();
       ARC_BOOL(m_maintainAspect);
   }
   else{
       CString sMetaFileName;
       ar >> sMetaFileName;
       DEARC_BOOL(m_maintainAspect);
       SetMetaFileName(sMetaFileName);
   }
}



//----------------------------------------------------------------------------
float DragDropMetaFile::GetAspectRatio(const CString& lpFileName){
//----------------------------------------------------------------------------
	PROC_TRACE;

   int        wBytesRead;
   DWORD      dwIsAldus;

    float fAspectRatio = 1.0F;

    CFile file;

    if (file.Open(lpFileName, CFile::modeRead))  {
        wBytesRead = file.Read((void*)&dwIsAldus, sizeof(dwIsAldus));

        if (wBytesRead < sizeof(dwIsAldus)){
            TRACE0("GoMeta::GetAspectRatio, Unable to read file\n");
            return (fAspectRatio);
        }
        if (dwIsAldus == ALDUSKEY) {
            file.Seek(0, CFile::begin);
            wBytesRead = file.Read((void*)&aldusMFHeader, sizeof(ALDUSMFHEADER));
            if(wBytesRead < sizeof(ALDUSMFHEADER) ){
                TRACE0("DragDropMetaFile::GetAspectRatio, Unable to read file header\n");
                return (fAspectRatio);
            }

            int div = aldusMFHeader.bbox.right - aldusMFHeader.bbox.left;
            if (div != 0)  {
               // TODO: possible division by zero
               fAspectRatio =  float(fabs (double(div)   / double(aldusMFHeader.bbox.top - aldusMFHeader.bbox.bottom)));
            }
        }
    }
    return fAspectRatio;
}


#ifdef VERYLARGE

//----------------------------------------------------------------------------
HENHMETAFILE DragDropMetaFile::ReadEnhMetaFile(const CString& sFileName){
//----------------------------------------------------------------------------
	PROC_TRACE;

   HENHMETAFILE	hTemp;
	HMETAFILE		hOld;
	DWORD			dwSize;
	METAFILEPICT	mp;
	LPBYTE			pBits;
	HDC				hDC;
	HANDLE			hFile;

	// First try to read it as an enhanced metafile
	// If it DoCalculates, simply return the handle
	if( (hTemp = ::GetEnhMetaFile( sFileName )) != NULL )
		return hTemp;
	if( (hOld = ::GetMetaFile( sFileName )) != NULL ){
		if( (dwSize = ::GetMetaFileBitsEx( hOld, 0, NULL )) == 0 ){
			DeleteMetaFile( hOld );
			TRACE0(_T("Failed to Get MetaFile Bits Size -- Error Reading MetaFile\n"));
			return NULL;
		}
		if( (pBits = (LPBYTE)malloc( dwSize )) == NULL ) {
         ::DeleteMetaFile( hOld );
			TRACE0(_T("Failed to Allocate Memory for Metafile Bits -- Error Reading MetaFile\n"));
			return NULL;
		}
		// Get the metafile bits
		if( ::GetMetaFileBitsEx( hOld, dwSize, pBits ) == 0 )
		{
			free( pBits );
			::DeleteMetaFile( hOld );
			TRACE0(_T("Failed to Get MetaFile Bits -- Error Reading MetaFile\n"));
			return NULL;
		}
		// Fill out a METAFILEPICT structure
		mp.mm = MM_ANISOTROPIC;
		mp.xExt = 1000;
		mp.yExt = 1000;
		mp.hMF = NULL;
		// Get a reference DC
		hDC = ::GetDC( NULL );
		// Make an enhanced metafile from the windows metafile
		hTemp = ::SetWinMetaFileBits( dwSize, pBits, hDC, &mp );
		// Clean up
		::ReleaseDC( NULL, hDC );
		::DeleteMetaFile( hOld );
		free( pBits );
		if( hTemp == NULL )
			TRACE0(_T("Failed to Create MetaFile from Bits -- Error Reading MetaFile\n"));
		return hTemp;
	}
	// If we got here, the file of interest is neither an enhanced metafile nor a
	// 16bit windows metafile. Let's assume it's a placeable metafile and move on.
	// First, open the file for reading
	hFile = CreateFile( sFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if( hFile == INVALID_HANDLE_VALUE ){
		TRACE1(_T("Error Opening File: %s\n", sFileName));
		return NULL;
	}
	// How big is the file?
	dwSize = GetFileSize( hFile, NULL );
	// Allocate enough memory to hold it
	pBits = (LPBYTE)malloc( dwSize );
	// Read it in
	ReadFile( hFile, pBits, dwSize, &dwSize, NULL );
	// Close the file
	CloseHandle( hFile );
	// Is it a placeable metafile? (check the key)
	if( ((LPPAPMHEADER)pBits)->dwKey != 0x9ac6cdd7l ){
		// Not a metafile that we know how to recognise - bail out
		free( pBits );
		TRACE1(_T("Not a Valid Metafile: %s\n", sFileName));
		return NULL;
	}
	// Ok, its a placeable metafile
	// Fill out a METAFILEPICT structure
	mp.mm = MM_ANISOTROPIC;
	mp.xExt = ((LPPAPMHEADER)pBits)->bbox.Right - ((LPPAPMHEADER)pBits)->bbox.Left;
	mp.xExt = ( mp.xExt * 2540l ) / (DWORD)(((LPPAPMHEADER)pBits)->wInch);
	mp.yExt = ((LPPAPMHEADER)pBits)->bbox.Bottom - ((LPPAPMHEADER)pBits)->bbox.Top;
	mp.yExt = ( mp.yExt * 2540l ) / (DWORD)(((LPPAPMHEADER)pBits)->wInch);
	mp.hMF = NULL;
	// Get a reference DC
	hDC = ::GetDC( NULL );
	// Create an enhanced metafile from the bits
	hTemp = ::SetWinMetaFileBits( dwSize, &(pBits[sizeof(PAPMHEADER)]), hDC, &mp );
	// Clean up
	::ReleaseDC( NULL, hDC );
	free( pBits );
	if( hTemp == NULL )
		TRACE0(_T("Failed to Create MetaFile from Bits -- Error Reading MetaFile\n"));
	return hTemp;
}

#endif // VERYLARGE

//----------------------------------------------------------------------------
BOOL PlayMetaFileToDest(HDC hDC, const CString& OpenName, CRect rect, BOOL bPrinting){
//----------------------------------------------------------------------------

      
  /* if the file opened contained a valid metafile */
  if (bValidFile) {

    /* placeable metafile */
    if (bAldusMeta) {
        SetPlaceableExts(hDC, aldusMFHeader, rect);
    }   
    else {   
        SetViewportOrgEx(hDC, rect.left, rect.top, NULL);
        SetViewportExtEx(hDC, rect.right-rect.left, rect.bottom-rect.top, NULL);
    
    }

    GetMetaFileAndEnum(hDC, OpenName, bPrinting);
    return TRUE;
  }

  return FALSE;
}

 

//----------------------------------------------------------------------------
void GetMetaFileAndEnum(HDC hDC, const CString& OpenName, BOOL bPrinting){
//----------------------------------------------------------------------------


   if (hMF) {  
      EnumMetaFile(hDC, hMF, (MFENUMPROC)MetaEnumProc, (LPARAM) bPrinting);
      if (!bMetaInRam) {
         DeleteMetaFile(hMF);
      }
   }
}


//----------------------------------------------------------------------------
int CALLBACK MetaEnumProc(HDC hDC, LPHANDLETABLE lpHTable,
    LPMETARECORD lpMFR, int nObj, LPARAM lpClientData){
//----------------------------------------------------------------------------

    BOOL bPrinting = (BOOL)(WORD)lpClientData;
 
    
    BOOL bPlay = TRUE;
    if (!bPrinting) { 
       switch (lpMFR->rdFunction)  {
       case META_ESCAPE:
           if (!bPrinting) bPlay = FALSE;
           break;  
       case META_CREATEPALETTE: 
           bPlay = TRUE;        
           break;
    
       case META_REALIZEPALETTE:
           bPlay = FALSE;       
           break;      

       case META_SELECTPALETTE:
           bPlay = FALSE;
           break;
    
       case META_CREATEBRUSHINDIRECT:
           {
           LOGBRUSH16* pLB = (LOGBRUSH16*)&lpMFR->rdParm[0];
           pLB->color = CDragDropApp::GetPaletteIndex(pLB->color);       
           break;
           }
         
       case META_CREATEPENINDIRECT:
           {
           LOGPEN16* pLP = (LOGPEN16*)&lpMFR->rdParm[0];
           pLP->color = CDragDropApp::GetPaletteIndex(pLP->color);       
           break;
           }
    
       case META_SETTEXTCOLOR: 
       case META_SETBKCOLOR:
           {
           COLORREF color = (COLORREF)lpMFR->rdParm[0];  //** bug here?  Why don't I call GetPaletteIndex?
           break;
           }

       case META_RECTANGLE:
           {
           int bottom = (short)lpMFR->rdParm[0];
           int right =  (short)lpMFR->rdParm[1];
           int top =    (short)lpMFR->rdParm[2];
           int left =   (short)lpMFR->rdParm[3];
           if ((aldusMFHeader.bbox.left >= left) && (aldusMFHeader.bbox.top >= top) && 
               (aldusMFHeader.bbox.right <= right) && (aldusMFHeader.bbox.bottom <= bottom))
               {
                   bPlay = FALSE; 
               }
           break;
           }
         
       default:
           break;
   
      }
   }
   if (bPlay)
      PlayMetaFileRecord(hDC, lpHTable, lpMFR, (WORD)nObj);

   return(1);
}
 

//----------------------------------------------------------------------------
BOOL ProcessFile(const CString& lpFileName){
//----------------------------------------------------------------------------

    CString strFileName(lpFileName);

    // Upcase the file name
    strFileName.MakeUpper();
    //
    //if the file is a Windows metafile or a Windows or placeable metafile
    //as per the normal naming conventions 
    //
    if (strFileName.Find(_T(".WMF")) >= 0) 
        return ProcessWMF(lpFileName);

    // something went wrong, one of the ifs above should have matched
    TRACE0("DragDropMetafile::ProcessFile, did not recognize file extension\n");
    return FALSE;
}

//----------------------------------------------------------------------------
void MetafileCleanup(){
//----------------------------------------------------------------------------

    bEnhMeta = FALSE;

    if (lpMFBits){
        GlobalFreePtr(lpMFBits);    
        lpMFBits = NULL;
        hMF = NULL;
        hemf = NULL;
    }

    if (EmfPtr.EMFHdr)
        GlobalFreePtr(EmfPtr.EMFHdr);
    if (EmfPtr.descStr)
        GlobalFreePtr(EmfPtr.descStr);

}

//----------------------------------------------------------------------------
BOOL ProcessWMF(const CString& lpFileName){
//----------------------------------------------------------------------------

    int        wBytesRead;
    DWORD      dwIsAldus;

    // try to open the file.  It's existence has already been
    // checked by OpenFileDialog 
    CFile file;

    // if opened successfully
    if (file.Open(lpFileName, CFile::modeRead))  
    {
      //
      // read the first dword of the file to see if it is a placeable wmf 
      //
      wBytesRead = file.Read((void*)&dwIsAldus, sizeof(dwIsAldus));

      if (wBytesRead < sizeof(dwIsAldus)){
        TRACE0("GoMeta::ProcessWMF, Unable to read file\n");
        return (FALSE);

      }
      if (dwIsAldus != ALDUSKEY){
        hMF = GetMetaFile(lpFileName);
        file.Seek(0, CFile::begin);
        wBytesRead = file.Read((void*)&mfHeader, sizeof(METAHEADER));
        if (wBytesRead < sizeof(dwIsAldus)){
          TRACE0("GoMeta::ProcessWMF, Unable to read metafile header\n");
          return (FALSE);
        }
      }
      else {
        RenderPlaceableMeta(file);
      }
      if ( (mfHeader.mtType != 1) && (mfHeader.mtType != 2) )  {
        //
        //set the program flags appropriately 
        //
        bValidFile = FALSE;
        //
        //let the user know that this is an invalid metafile 
        //
        TRACE0("GoMeta::ProcessWMF, this file is not a valid metafile\n");
      }
      else{
        bValidFile = TRUE;

        if (dwIsAldus != ALDUSKEY){
          bAldusMeta = FALSE;
          bMetaInRam = TRUE;
        }
        else{
          bAldusMeta = TRUE;
          bMetaInRam = TRUE;
        }
      }
      return (TRUE);

    } 
    else{
        TRACE1("GoMeta::ProcessWMF, unable to open metafile %s\n",lpFileName);
        return (FALSE);
    }  
}


//----------------------------------------------------------------------------
void SetPlaceableExts(HDC hDC, ALDUSMFHEADER ahdr, CRect rect){
//----------------------------------------------------------------------------

    SetMapMode(hDC, MM_ANISOTROPIC);

    // set the windows origin to correspond to the bounding box origin
    //   contained in the placeable header 
    SetWindowOrgEx(hDC, ahdr.bbox.left, ahdr.bbox.top, NULL);

    // set the window extents based on the abs value of the bbox coords
    SetWindowExtEx(hDC,abs(ahdr.bbox.left) + abs(ahdr.bbox.right),
                   abs(ahdr.bbox.top) + abs(ahdr.bbox.bottom), NULL);

    // place the metafile in the desired location

    // rect is the device coordinates locating the metafile.  Note that the
    // double buffering code can make rect look really strange here.

    SetViewportOrgEx(hDC, rect.left, rect.top, NULL);
    SetViewportExtEx(hDC, rect.right-rect.left, rect.bottom-rect.top, NULL);
}




//----------------------------------------------------------------------------
BOOL RenderPlaceableMeta(CFile& file){
//----------------------------------------------------------------------------

  int      wBytesRead;
  long     lBytesRead;
  //
  //if there is currently a metafile loaded, get rid of it 
  //
  if (bMetaInRam && hMF && !bEnhMeta)
    DeleteMetaFile(hMF);
  //
  //seek to beginning of file and read aldus header 
  //
  file.Seek(0, CFile::begin);
  //
  //read the placeable header 
  //
  wBytesRead = file.Read((void*)&aldusMFHeader, sizeof(ALDUSMFHEADER));
  //
  //if there is an error, return 
  //
  if (wBytesRead < sizeof(ALDUSMFHEADER) )  {
        TRACE0("DragDropMetafile::RenderPlaceableMeta, Unable to read placeable header\n");
        return(FALSE);
  }
  //
  //return to read metafile header 
  //
  file.Seek(sizeof(aldusMFHeader), CFile::begin);
  //
  //read the metafile header 
  //
  wBytesRead = file.Read((void*)&mfHeader, sizeof(METAHEADER));
  //
  //if there is an error return 
  //
  if(wBytesRead < sizeof(METAHEADER) )  {
        TRACE0("DragDropMetafile::RenderPlaceableMeta, Unable to read metafile header\n");
        return(FALSE);
  }
  //
  //allocate memory for the metafile bits 
  //
  if (!(lpMFBits = (char*)GlobalAllocPtr(GHND, (mfHeader.mtSize * 2L)))){
        TRACE0("DragDropMetafile::RenderPlaceableMeta, Unable to allocate memory for metafile\n");
        return(FALSE);
  }
  file.Seek(sizeof(aldusMFHeader), CFile::begin);
  lBytesRead = file.Read(lpMFBits, (WORD)(mfHeader.mtSize * 2));
  if( lBytesRead == -1 ){
    TRACE0("DragDropMetafile::RenderPlaceableMeta, Unable to read metafile bits\n");
    GlobalFreePtr(lpMFBits);
    return(FALSE);
  }

    DWORD dwSize = GlobalSizePtr(lpMFBits);
    if (!(hMF = SetMetaFileBitsEx(dwSize, (BYTE*)lpMFBits)))       //** (byte*) ??
        return(FALSE);
  return(TRUE);
}


/***********************************************************************

  FUNCTION   : EnumMFIndirect

  PARAMETERS : HDC             hDC
               LPHANDLETABLE   lpHTable
               LPMETARECORD    lpMFR
               LPENHMETARECORD lpEMFR
               int             nObj
               LPARAM          lpData


  PURPOSE    : called by EnumMetaFile and EnumEnhMetaFile.  Handles the stepping of
               each metafile record.

  MESSAGES   : none

  RETURNS    : int

  COMMENTS   : ENUMMFSTEP is used whenever records are to be played,
               regardless of whether you are playing records from the
               list, stepping all, or stepping a range.

               ENUMMFLIST is used when you need to add strings to a listbox
               that describe the type of reocrd.

  HISTORY    : created 7/1/93 - denniscr

************************************************************************/

int EnumMFIndirect(HDC hDC, LPHANDLETABLE lpHTable, 
                            LPMETARECORD lpMFR, 
                            LPENHMETARECORD lpEMFR, 
                            int nObj, LPARAM lpClientData){
    BOOL bPrinting = (BOOL)(WORD)lpClientData;
 
    BOOL bPlay = TRUE;    
    switch (lpMFR->rdFunction)  {
    
    case META_ESCAPE:       // escape is for printers only
        if (!bPrinting) bPlay = FALSE;
        break;  

    case META_CREATEPALETTE: 
        bPlay = TRUE;           // must be played to create a record in the HandleTable
        break;
    
    case META_REALIZEPALETTE:
        bPlay = FALSE;          // ignore the palette that is created...
        break;      

    case META_SELECTPALETTE:
        bPlay = FALSE;
        break;
    
    case META_CREATEBRUSHINDIRECT:
        {
        LOGBRUSH* pLB = (LOGBRUSH*)&lpMFR->rdParm[0];
        pLB->lbColor = CDragDropApp::GetPaletteIndex(pLB->lbColor);       
        break;
        }
         
    case META_CREATEPENINDIRECT:
        {
        LOGPEN* pLP = (LOGPEN*)&lpMFR->rdParm[0];
        pLP->lopnColor = CDragDropApp::GetPaletteIndex(pLP->lopnColor);       
        break;
        }
    
    case META_SETTEXTCOLOR: 
    case META_SETBKCOLOR:
        {
        COLORREF color = (COLORREF)lpMFR->rdParm[0];  //** bug here?  Why don't I call GetPaletteIndex?
        break;
        }
        
    default:
        // default is to play record
        break;
   
    }  // end switch


    if (bPlay)
     if (bEnhMeta)
       return PlayEnhMetaFileRecord(hDC, lpHTable, lpEMFR, (UINT)nObj);
     else
       return PlayMetaFileRecord(hDC, lpHTable, lpMFR, (UINT)nObj);

    // some error
    TRACE0("DragDropMetafile::EnumMFIndirect, did not play record\n");
    return FALSE;
}

