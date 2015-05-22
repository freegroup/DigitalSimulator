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

#ifndef _DRAGDROPAPP_H_
#define _DRAGDROPAPP_H_ 

#include "DragDropBitmapCach.h"   // bitmap cache
#include "DragDropPalett.h"   // palette 
#include "DragDropMetrics.h"
#include "DragDropCursorManager.h"

class DragDropHandle;        // forward declaration

const COLORREF PRIMARY_RGB   = RGB(0,255,0);
const COLORREF SECONDARY_RGB = RGB(0,255,255);

const int BITMAP_CACHE_WIDTH_MULTIPLIER = 10;

#define WM_DOREFRESH   (WM_USER + 0)

class DragDropAppMixIn{
public:
    DragDropAppMixIn();

    static void SetPrimarySelectionColor (COLORREF color);
    static void UseSystemSelectionColor();
    static void SetSecondarySelectionColor (COLORREF color);
    static COLORREF GetPrimarySelectionColor();    
    static COLORREF GetSecondarySelectionColor();

                             
    static BOOL InitializePalette();                             
    static DragDropPalette* GetPalette();
    static CPalette* GetCPalette();
    static COLORREF GetPaletteIndex (COLORREF color);
    static COLORREF GetPaletteIndexBlack () {return m_colorBlack;} 
    static COLORREF GetPaletteIndexWhite () {return m_colorWhite;}
    static BOOL OnQueryNewPalette();
    
                                
    static void SetMetafileUseBitmap(BOOL flag) {m_bMetafileUseBitmap = flag;}
    static BOOL GetMetafileUseBitmap() {return m_bMetafileUseBitmap;}
    
    static DragDropBitmapCacheDesc* AllocBitmapDesc (CDC* pDC, const CString& sName, CSize sizeBitmapDP, BOOL bTransparent); 
    static void DeallocBitmapDesc (const CString& sName);

    static DragDropBitmapCacheStore* AllocBitmapStore (CDC* pDC, DragDropBitmapCacheDesc* pDesc, 
                CSize sizeBitmapDP, BOOL bTransparentBM);
    
    static void PurgeBitmapCaches();
    static void InvalidateBitmapDesc(const CString& sName);    
    
    static void InvalidateStockCache();
    static CPen* AllocPen(int wStockIndex);
    static void DeallocPen(CPen* pPen, int wStockIndex);
    static CBrush* AllocBrush(int wStockIndex);
    static void DeallocBrush(CBrush* pBrush, int wStockIndex);    
    static void PurgePenAndBrushCaches();  

    static DragDropHandle* AllocHandle();
    static void DeallocHandle(DragDropHandle* pHandle);
    static void PurgeHandleCache();

    static void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo, int nScale);
    
    virtual BOOL Init();
    virtual int  stop();

protected:
    static CBitmap* m_pPortBitmap;
    
    static BOOL            m_bMetafileUseBitmap;           // Metafile object bitmap cache on/off switch
    static CMapStringToOb  m_mapBitmapDesc;                // name-> bitmap Descriptor map
    static CObList         m_listBitmapStore;              // list of bitmap stores
    static CObList         m_listFreeBitmapDesc;           // free bitmap descriptors  
    static CObList         m_listFreeHandles;              // free DragDropHandle Objects  
    
    static COLORREF    m_colorPrimary;             // Primary selection color
    static COLORREF    m_colorSecondary;           // Secondary selection color
    static COLORREF    m_colorBlack;               // index for Black
    static COLORREF    m_colorWhite;               // index for White
    
   
    static DragDropPalette* m_pPalette;
    static BOOL        m_bUsingPalette;            // TRUE if Initialize is successful
    
    
    static CObList     m_listPenCache;
    static CObList     m_listBrushCache;
    static CGdiObject* m_arrayGdiCache[255];
    static int         m_nLastStockPen;
    static int         m_nLastStockBrush;
    
};

#endif 
