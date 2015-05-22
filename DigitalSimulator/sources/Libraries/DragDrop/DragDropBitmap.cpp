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
#include <afxwin.h>
#include "DragDropBitmap.h"
#include "DragDropDib.h"


IMPLEMENT_SERIAL(DragDropBitmap, DragDropObject, 2)

//----------------------------------------------------------------------------
DragDropBitmap::DragDropBitmap(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init();
}

//----------------------------------------------------------------------------
DragDropBitmap::DragDropBitmap(CPoint location, CSize size) : inherited (location, size){
//----------------------------------------------------------------------------
	PROC_TRACE;

   Init();
}


//----------------------------------------------------------------------------
DragDropBitmap::~DragDropBitmap() {
//----------------------------------------------------------------------------
	PROC_TRACE;

    delete m_pDib;
    m_pDib = NULL;
    if (m_bBitmapLoaded)
        m_Bitmap.DeleteObject();
}

//----------------------------------------------------------------------------
void DragDropBitmap::Init() {
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_sFileName     = _T("");
    m_pDib          = NULL;
    m_bScale        = TRUE;
    m_sResourceName = _T("");
    m_nBitmapWidth  = 0;
    m_nBitmapHeight = 0;
    m_bBitmapLoaded = FALSE;
}

//----------------------------------------------------------------------------                                                 
DragDropObject* DragDropBitmap::Clone() const{   
//----------------------------------------------------------------------------
	PROC_TRACE;

    DragDropObject* pObject = inherited::Clone();
    ASSERT(pObject->IsKindOf(RUNTIME_CLASS(DragDropBitmap)));                  
    DragDropBitmap* pNewBM =(DragDropBitmap*) pObject;

    pNewBM->m_pDib = NULL;
    if (m_sResourceName == _T("")) {
        pNewBM->OpenDib(FileName());
    }
    else {
        pNewBM->m_sResourceName = m_sResourceName;
        pNewBM->m_nBitmapWidth  = m_nBitmapWidth;
        pNewBM->m_nBitmapHeight = m_nBitmapHeight;
    }

    return pObject;
}

//----------------------------------------------------------------------------
CDib*   DragDropBitmap::Dib() {
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_pDib == NULL) {
        m_pDib = new CDib();
    }
    return m_pDib;
}

//----------------------------------------------------------------------------
CString DragDropBitmap::FileName() const{
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_sFileName;
}

//----------------------------------------------------------------------------
BOOL DragDropBitmap::SetFileName(const CString& sNewFileName){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_sFileName != sNewFileName){
        if(OpenDib(sNewFileName)){
            Measure();
            SetUpdateNeeded(TRUE);
            return TRUE;
        }
        return FALSE;
    }
    return TRUE;
}

//----------------------------------------------------------------------------
BOOL DragDropBitmap::OpenDib(const CString& sNewFileName){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_sFileName = sNewFileName;
    CFile file;
    if (!file.Open(m_sFileName, CFile::modeRead | CFile::shareDenyNone)) 
       return FALSE;
    return Dib()->Read(&file);
}

//----------------------------------------------------------------------------
void DragDropBitmap::Measure(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
    CClientDC dc(AfxGetApp()->m_pMainWnd);
    DragDropAppMixIn::OnPrepareDC(&dc, NULL, 100);
    Measure(&dc);
}

//----------------------------------------------------------------------------
void DragDropBitmap::Measure(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CPoint size(Dib()->GetSize());
    pDC->DPtoLP(&size);
    SetSize(size.x, abs(size.y));
}

//----------------------------------------------------------------------------
long DragDropBitmap::VerifyBitmap(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   long nMagicNumber = 0;
    if (m_sResourceName != _T("")) {
        if (!m_bBitmapLoaded) {
            if (!m_Bitmap.Load(AfxGetApp()->m_hInstance, m_sResourceName)) {
                 TRACE0("DragDropBitmap::VerifyBitmap: Couldn't load the bitmap");
                 return 0;
            }
        }
        m_bBitmapLoaded = TRUE;

        BITMAP Bitmap;
        m_Bitmap.GetObject(sizeof(BITMAP), &Bitmap);
        long nNumBytes = Bitmap.bmHeight * Bitmap.bmWidthBytes;
        short* pByteArray = new short[nNumBytes];
        long bytes = m_Bitmap.GetBitmapBits(nNumBytes, pByteArray);
        for (int i=0; i<bytes; i++) {
            nMagicNumber = nMagicNumber ^ pByteArray[i];
        }
        delete pByteArray;
    }
    return nMagicNumber;
}

//----------------------------------------------------------------------------
BOOL DragDropBitmap::paint(CDC* pDC){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (!isVisible())
       return TRUE;

    if (m_sResourceName != _T("")) {
        if (!m_bBitmapLoaded) {
            if (!m_Bitmap.Load(AfxGetApp()->m_hInstance, m_sResourceName)) {
                TRACE0("DragDropBitmap::paint: Couldn't load the bitmap\n");
                CRect Rect = GetBoundingRect();
                pDC->FillRect(Rect, CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));
                return TRUE;
            }
            m_bBitmapLoaded = TRUE;
        }
        CDC dcMem;
        if (!dcMem.CreateCompatibleDC(pDC)) {
            TRACE0("DragDropBitmap::paint: Couldn't CreateCompatibleDC\n");
            CRect Rect = GetBoundingRect();
            pDC->FillRect(Rect, CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));
            return TRUE;
        }
        if (!dcMem.SelectObject(&m_Bitmap)) {
            TRACE0("DragDropBitmap::paint: Couldn't SelectObject\n");
            CRect Rect = GetBoundingRect();
            pDC->FillRect(Rect, CBrush::FromHandle((HBRUSH)GetStockObject(LTGRAY_BRUSH)));
            return TRUE;

        }
        CSize size(GetSize());
        size.cy = -size.cy;
        BOOL bStatus = pDC->StretchBlt(GetTopLeft().x, GetTopLeft().y, size.cx, size.cy,
            &dcMem, 0, 0, m_nBitmapWidth, m_nBitmapHeight,
            SRCCOPY);
        return TRUE;
    }

    if (!m_bScale && !pDC->IsPrinting()) {
        Dib()->Display(pDC, GetTopLeft());
    }
    else
    {
        CSize size(GetSize());
        size.cy = -size.cy;
        Dib()->Stretch(pDC, GetTopLeft(), size);
    }
    return TRUE;
}

//----------------------------------------------------------------------------
void DragDropBitmap::Serialize(CArchive& ar){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::Serialize(ar);

   if (ar.IsStoring()) {
      ar << m_sFileName;
      ARC_BOOL(m_bScale);
      ar << m_sResourceName;
      ar << m_nBitmapWidth;
      ar << m_nBitmapHeight;
   }
   else {
      CString sFileName;
      ar >> sFileName;
      DEARC_BOOL(m_bScale);
      OpenDib(sFileName);
      ar >> m_sResourceName;
      ar >> m_nBitmapWidth;
      ar >> m_nBitmapHeight;
   }
}
    
IMPLEMENT_DYNAMIC(CDib2, CBitmap)

//----------------------------------------------------------------------------
CDib2::CDib2(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    memset(&m_bm, 0, sizeof(m_bm));
}

//----------------------------------------------------------------------------
CDib2::~CDib2(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    DeleteObject();
}

//----------------------------------------------------------------------------
BOOL CDib2::Load(HINSTANCE hInst, LPCTSTR lpResourceName){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return Attach(::LoadImage(hInst, lpResourceName, IMAGE_BITMAP, 0, 0, 
        LR_CREATEDIBSECTION | LR_DEFAULTSIZE));
}

//----------------------------------------------------------------------------
BOOL CDib2::Attach(HGDIOBJ hbm){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (inherited::Attach(hbm)) {
        if (!GetBitmap(&m_bm))
            return FALSE;
        return TRUE;
    }
    return FALSE;
}
