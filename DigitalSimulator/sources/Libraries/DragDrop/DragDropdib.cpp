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
#include "DragDropdib.h"
#include <windowsx.h> 



//----------------------------------------------------------------------------//----------------------------------------------------------------------------                                         
CDib::CDib(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_dwLength = 0L;
    m_nBits    = 0;
    m_lpBuf    = NULL;
}

//----------------------------------------------------------------------------    
CDib::CDib(CDC* pDC, int nBt, BOOL bCompr, CPalette* pPal){
//----------------------------------------------------------------------------
	PROC_TRACE;

    BITMAP bm;
    
    CBitmap* pEmptyBitmap = new CBitmap;
    pEmptyBitmap->CreateCompatibleBitmap(pDC, 0, 0);
    CBitmap* pBitmap = (CBitmap*) (pDC->SelectObject(pEmptyBitmap));  
    pBitmap->GetObject(sizeof(bm), &bm);
    if ((nBt == 1) || (nBt == 4) || (nBt == 8) || (nBt == 24)) {
        m_nBits = nBt;
    }
    else {   // nBt = 0
        m_nBits = bm.bmPlanes * bm.bmBitsPixel; // color bits per pixel
    }
    if (m_nBits == 1) {
        nPaletteSize = 2;
    }
    else {
        if (m_nBits == 4) {
            nPaletteSize = 16;
        }
        else {
            if (m_nBits == 8) {
                nPaletteSize = 256;
            }
            else {
                nPaletteSize = 0; // no palette for 24-bit display
            } 
        }
    }
    // fills out row to 4-byte boundary
    DWORD dwBytes = ((DWORD) bm.bmWidth * m_nBits) / 32;
    if (((DWORD) bm.bmWidth * m_nBits) % 32) {
        dwBytes ++;
    }
    dwBytes *= 4;

    m_dwLength = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                 sizeof(RGBQUAD) * nPaletteSize;
    if (!AllocateMemory()) return;
    
    m_lpBMIH->biSize = sizeof(BITMAPINFOHEADER);
    m_lpBMIH->biWidth = bm.bmWidth;
    m_lpBMIH->biHeight = bm.bmHeight;
    m_lpBMIH->biPlanes = 1;
    m_lpBMIH->biBitCount = m_nBits; // 1, 4, 8, or 24   
      
    if (bCompr && (m_nBits == 4)) {
        m_lpBMIH->biCompression = BI_RLE4;
    }
    else {
        if (bCompr && (m_nBits == 8)) { 
            m_lpBMIH->biCompression = BI_RLE8;
        }
        else {
            m_lpBMIH->biCompression = BI_RGB;
        } 
    }
    m_lpBMIH->biSizeImage = 0;
    m_lpBMIH->biXPelsPerMeter = 0;
    m_lpBMIH->biYPelsPerMeter = 0;
    m_lpBMIH->biClrUsed = nPaletteSize/*0*/;
    m_lpBMIH->biClrImportant = 0;

    // calls GetDIBits with null data pointer to get size of DIB
    ::GetDIBits(pDC->GetSafeHdc(), (HBITMAP) pBitmap->GetSafeHandle(),
                0, (WORD) bm.bmHeight, NULL, m_lpBMI, DIB_RGB_COLORS);

    if (m_lpBMIH->biSizeImage == 0) {
        m_dwLength += dwBytes * bm.bmHeight;
        m_lpBMIH->biCompression = BI_RGB;
        // escape route for device drivers that don't do compression
        TRACE(_T("Can't do compression\n"));
    }
    else {
        m_dwLength += m_lpBMIH->biSizeImage;
    }
    if (!AllocateMemory(TRUE)) {
        return;
    }
    m_lpData = (LPSTR) m_lpBMIH + sizeof(BITMAPINFOHEADER) +
               sizeof(RGBQUAD) * nPaletteSize;
    m_lpBMFH->bfType = 0x4d42; // 'BM'
    m_lpBMFH->bfSize = m_dwLength;
    m_lpBMFH->bfReserved1 = 0;
    m_lpBMFH->bfReserved2 = 0;
	
    
		m_lpBMFH->bfOffBits = (char *) m_lpData - m_lpBuf;
   
		    PALETTEENTRY pe[256];		
		    UINT iu;	    
		    pPal->GetPaletteEntries(0, 256, pe);   
		    for (iu = 0;  iu < (UINT)(nPaletteSize);  iu++){                                  	            
	           (m_lpBMI->bmiColors[iu]).rgbRed=pe[iu].peRed;
			   (m_lpBMI->bmiColors[iu]).rgbGreen=pe[iu].peGreen;
			   (m_lpBMI->bmiColors[iu]).rgbBlue=pe[iu].peBlue;
			   (m_lpBMI->bmiColors[iu]).rgbReserved=0;          
		    }                                              
    /////////////////////////////////////////////      	        
	           
    // second GetDIBits call to make DIB
    if (!::GetDIBits(pDC->GetSafeHdc(), (HBITMAP)
        pBitmap->GetSafeHandle(), 0, (WORD) bm.bmHeight, m_lpData,
        m_lpBMI, DIB_RGB_COLORS)) {
        m_dwLength = 0L;
    }
    delete pDC->SelectObject(pBitmap); // delete pEmptyBitmap
}     

//----------------------------------------------------------------------------
CDib::~CDib(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_lpBuf) {
        GlobalFreePtr(m_lpBuf);  // free the DIB memory
    }
}


//----------------------------------------------------------------------------
BOOL CDib::Read(CFile* pFile){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // file assumed to be open
    ASSERT(m_dwLength == 0L); // DIB must be empty
    m_dwLength = pFile->GetLength();
    if (!AllocateMemory()) {
        return FALSE;       
    }
    DWORD dwCount = pFile->ReadHuge(m_lpBuf, m_dwLength);
    if (dwCount != m_dwLength) {
        AfxMessageBox(_T("Bitmap file read error"));
        return FALSE;
    }
    if (m_lpBMFH->bfType != 0x4d42) {
        AfxMessageBox(_T("Invalid bitmap file"));
        return FALSE;
    }
    ASSERT((m_lpBMIH->biBitCount == 1) || (m_lpBMIH->biBitCount == 4) ||
           (m_lpBMIH->biBitCount == 8) || (m_lpBMIH->biBitCount == 24));
    m_lpData = (LPSTR) m_lpBMFH + m_lpBMFH->bfOffBits;
    m_nBits = m_lpBMIH->biBitCount;
    return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDib::Write(CFile* pFile){
//----------------------------------------------------------------------------
	PROC_TRACE;

    TRY {
        pFile->WriteHuge(m_lpBuf, m_dwLength);
    }
    CATCH (CException, e) {
        AfxMessageBox(_T("Write error--possible disk full condition"));
        return FALSE;
    }
    END_CATCH
    return TRUE;
}


//----------------------------------------------------------------------------
BOOL CDib::Display(CDC* pDC, CPoint origin){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // direct to device--bypass the GDI bitmap
    if (!m_lpBuf) {
        return FALSE; // nothing to display
    }
    if (!::SetDIBitsToDevice(pDC->GetSafeHdc(),
     origin.x,
     origin.y,
     (WORD) m_lpBMIH->biWidth, 
     (WORD) m_lpBMIH->biHeight, 
     0, 
     0, 
     0,
     (WORD) m_lpBMIH->biHeight, 
     m_lpData, 
     m_lpBMI,
       DIB_RGB_COLORS)) {
        return FALSE;
    }
    return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDib::Stretch(CDC* pDC, CPoint origin, CSize size){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // direct to device--bypass the GDI bitmap
    if (!m_lpBuf) {
        return FALSE; // nothing to display
    }
    if (!::StretchDIBits(pDC->GetSafeHdc(), origin.x, origin.y,
        size.cx, size.cy, 0, 0, (WORD) m_lpBMIH->biWidth,
        (WORD) m_lpBMIH->biHeight, m_lpData, m_lpBMI,
        DIB_RGB_COLORS, SRCCOPY)) {
        return FALSE;
    }
    return TRUE;
}

//----------------------------------------------------------------------------
int CDib::GetColorBits(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_nBits;
}

//----------------------------------------------------------------------------
DWORD CDib::GetLength(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return m_dwLength;
}

//----------------------------------------------------------------------------
CSize CDib::GetSize(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return CSize((int) m_lpBMIH->biWidth, (int) m_lpBMIH->biHeight);
}

//----------------------------------------------------------------------------
BOOL CDib::AllocateMemory(BOOL bRealloc){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (bRealloc) {         
			m_lpBuf = (char *) GlobalReAllocPtr(m_lpBuf, m_dwLength, GHND);
    }
    else {		
			m_lpBuf = (char *) GlobalAllocPtr(GHND, m_dwLength);
    }
    if (!m_lpBuf) {
        AfxMessageBox(_T("Unable to allocate DIB memory"));
        m_dwLength = 0L;
        m_nBits = 0;
        return FALSE;
    }
    m_lpBMFH = (LPBITMAPFILEHEADER) m_lpBuf;
    m_lpBMIH = (LPBITMAPINFOHEADER) (m_lpBuf + sizeof(BITMAPFILEHEADER));
    m_lpBMI = (LPBITMAPINFO) m_lpBMIH;
    return TRUE;
}
