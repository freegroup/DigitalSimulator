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
#include "DragDroppalett.h"

const int PALSIZE = 256;
const int MaxFreeIndex = PALSIZE-10;    // -10 (Windows taks the top 10.)
const int MinFreeIndex = 10;
IMPLEMENT_DYNCREATE(DragDropPalette, CObject)


//----------------------------------------------------------------------------
DragDropPalette::DragDropPalette(){
//----------------------------------------------------------------------------
	PROC_TRACE;
   
   m_pPalette       = new CPalette;
   m_nNextFreeIndex = 0;
   m_bPaletteDevice = FALSE;
}


//----------------------------------------------------------------------------
DragDropPalette::~DragDropPalette(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   delete m_pPalette;
   m_pPalette = NULL;
}

//----------------------------------------------------------------------------
BOOL DragDropPalette::Init (CWnd* pWnd){   
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (!pWnd) 
      return FALSE;
   CWindowDC dc(pWnd);
   if ((dc.GetDeviceCaps (RASTERCAPS) & RC_PALETTE) == 0) {
        m_bPaletteDevice = FALSE;
        return FALSE;
    }                        
    
    m_bPaletteDevice = TRUE;
    ASSERT (m_nNextFreeIndex == 0);

    BOOL status = m_pPalette->CreateHalftonePalette(&dc);
    m_nNextFreeIndex = PALSIZE;


    return status;
    
} 

//----------------------------------------------------------------------------
COLORREF DragDropPalette::GetPaletteIndex (COLORREF color){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (( (color & PALETTEINDEX(0)) >  0) | !m_bPaletteDevice)
        return color;
                                                                
    UINT nPalIndex = m_pPalette->GetNearestPaletteIndex (color);
                                        
    if ((m_nNextFreeIndex <= nPalIndex) && (nPalIndex < MaxFreeIndex)) {
        m_nNextFreeIndex = nPalIndex + 1;
    }    
    
                                                            
    PALETTEENTRY PalEntry;                                                      
    int nReturn = m_pPalette->GetPaletteEntries (nPalIndex, 1, &PalEntry);
    ASSERT (nReturn == 1);
    
    if ((GetRValue(color) == PalEntry.peRed) &
        (GetGValue(color) == PalEntry.peGreen) &
        (GetBValue(color) == PalEntry.peBlue)) 
        return PALETTEINDEX(nPalIndex);

    if (m_nNextFreeIndex >= MaxFreeIndex) 
       return PALETTEINDEX(nPalIndex);
    
    PalEntry.peRed   = GetRValue(color);
    PalEntry.peGreen = GetGValue(color);
    PalEntry.peBlue  = GetBValue(color);
    nPalIndex = m_nNextFreeIndex;
    m_nNextFreeIndex++;
    nReturn = m_pPalette->SetPaletteEntries (nPalIndex, 1, &PalEntry);
    ASSERT (nReturn == 1);
    
    GoQueryNewPalette();
    
    return PALETTEINDEX(nPalIndex);  
}


//----------------------------------------------------------------------------
BOOL DragDropPalette::GoQueryNewPalette(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CClientDC appDC(AfxGetApp()->m_pMainWnd);

    CPalette* oldPalette = appDC.SelectPalette(m_pPalette, FALSE);

    if (oldPalette != NULL) {
        UINT nColorsChanged = appDC.RealizePalette();
        appDC.SelectPalette(oldPalette, TRUE);
    }
    return TRUE;    
}


 
