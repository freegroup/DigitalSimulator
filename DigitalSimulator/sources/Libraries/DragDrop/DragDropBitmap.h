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

#ifndef _DRAGDROPBITMAP_H_
#define _DRAGDROPBITMAP_H_

#include "DragDropobject.h"

class CDib2 : public CBitmap{
   typedef CBitmap inherited ;

public:
    CDib2();
    virtual ~CDib2();
    virtual BOOL Load(HINSTANCE hInst, LPCTSTR lpResourceName);
    virtual BOOL Attach(HGDIOBJ hbm);
    BITMAP m_bm;

    DECLARE_DYNAMIC(CDib2)
};

/////////////////////////////////////////////////////////////////////////////
// class DragDropBitmap
//
class CDib;

class DragDropBitmap : public DragDropObject{
   typedef DragDropObject inherited ;
public:
   DragDropBitmap();
   DragDropBitmap(CRect* pRect);
   DragDropBitmap(CPoint location, CSize size);
   virtual ~DragDropBitmap();
   virtual long VerifyBitmap();

   virtual void Serialize(CArchive& ar);
   virtual BOOL paint(CDC* pDC);
   virtual CDib*	Dib();

   virtual CString FileName() const;
   virtual BOOL SetFileName(const CString& sNewFileName);
   virtual void SetResource(const CString& sResourceName, int nWidth, int nHeight)
     { m_sResourceName = sResourceName;
       m_nBitmapWidth = nWidth;
       m_nBitmapHeight = nHeight;}
   virtual CString GetMetaName(){return "Bitmap";};

   virtual DragDropObject* Clone() const;
protected:

   virtual void Init();
   virtual BOOL OpenDib(const CString& sNewFileName);
   virtual void Measure(CDC* pDC);                         // Calculate size
   virtual void Measure();

   CDib*	  m_pDib;	// the device independant bitmap 
   CDib2   m_Bitmap;
   CString m_sFileName;
   BOOL	  m_bScale;
   CString m_sResourceName;
   int     m_nBitmapWidth;
   int     m_nBitmapHeight;
   BOOL    m_bBitmapLoaded;
   DECLARE_SERIAL(DragDropBitmap)
};

#endif
