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

#ifndef _DRAGDROPBITMAPCACH_H_
#define _DRAGDROPBITMAPCACH_H_

#include "DragDrop.h"
class DragDropBitmapCacheStore; // forward declaration
          
class DragDropBitmapCacheDesc : public CObject{ 
   typedef CObject inherited ;

public:
   DragDropBitmapCacheDesc();
   DragDropBitmapCacheDesc(CDC* pDC, CSize sizeBitmapDP, BOOL bTransparentBM);
   virtual ~DragDropBitmapCacheDesc();

   virtual CBitmap*    GetBitmapSrc(); 
   virtual CPoint      GetBitmapSrcOffset();       // offset to start of source bitmap
   virtual CSize       GetBitmapSize();            // size of both bitmaps (in pixels)
   virtual void        ResetBitmapSize();          // reset to maximum, originally allocated size
   virtual void        SetBitmapSize(CSize szBitmapDP);   // size of both bitmaps (in pixels)   

   virtual CBitmap*    GetBitmapMask();            // "mask" bitmap
   virtual CPoint      GetBitmapMaskOffset();      // offset to start of Mask bitmap

   virtual int         RefCnt() {return m_nRefCnt;}    // return current reference count
   virtual void        IncrementRefCnt() {m_nRefCnt++;}
   virtual int         DecrementRefCnt();

   virtual void        Invalidate()    {m_bValid = FALSE;}
   virtual void        Validate()      {m_bValid = TRUE;}
   virtual BOOL        IsValid()       {return m_bValid;}
protected:


   int                 m_nRefCnt;              // number of objects with pointers to this object
   int                 m_nWidthWhenAllocated;  // Original width
   CSize               m_sizeBitmapDP;         // Size of both bitmaps
   CPoint              m_ptSrcOffset;          // offset in m_pBitmapSrc
   CPoint              m_ptMaskOffset;         // offset in m_pBitmapMask
   DragDropBitmapCacheStore*    m_pBitmapStore;     // pointer to Bitmap Store
   BOOL                m_bValid;               // valid bit  

   friend class DragDropBitmapCacheStore;
   DECLARE_DYNCREATE(DragDropBitmapCacheDesc)
};


class DragDropBitmapCacheStore : public CObject{
   typedef CObject inherited ;
public:
   DragDropBitmapCacheStore();
   DragDropBitmapCacheStore(CDC* pDC, int nWidth, int nHeight, BOOL bTransparent);
   virtual ~DragDropBitmapCacheStore();

   virtual BOOL AllocBitmaps (DragDropBitmapCacheDesc* pDesc, CSize sizeBitmapDP, BOOL bTransparentBM);
   virtual int  GetHeight() {return m_nSizeStorePixels.cy;} // return height of bitmap store;
   CBitmap*    m_pBitmapSrc;           
   CBitmap*    m_pBitmapMask;          

protected:
   CSize               m_nSizeStorePixels;
   int                 m_nFreeMark;       
   DECLARE_DYNCREATE(DragDropBitmapCacheStore)
};
 
#endif
