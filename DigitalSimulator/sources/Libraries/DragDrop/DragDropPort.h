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

#ifndef _DRAGDROPPORT_H_
#define _DRAGDROPPORT_H_

#include "DragDropObject.h"


class  CImageList;

class DragDropPort : public DragDropObject{
    typedef DragDropObject inherited ;

public:
    DragDropPort();
    DragDropPort(CPoint pPoint, int nBitMapId, int nToSide, int nFromSide);
    virtual void Init();
       
    virtual ~DragDropPort();
    virtual DragDropObject* Clone() const;
    static void DragDropPort::AppRunDown();

	 BOOL EnableImageList(UINT nResId, int cx);


    virtual int PortMax();             // Must be overriden
    virtual int GetPortWidth();        // default is 16
    virtual int GetPortHeight();       // default is 16
    virtual int GetPortOffset();       // default is 16*m_nBitmapId

    virtual int GetBitmapId();
    virtual void SetBitmapId (int nBitmapId);

    virtual BOOL IsValidLink();
    virtual void SetValidLink(BOOL bValid);
    virtual CObList* GetLinks() {return &m_oblistLinks;}
    virtual BOOL paint(CDC* pDC);
    
    virtual CPoint GetLinkPoint(int nSide);
    virtual CPoint GetFromLinkPoint();
    virtual CPoint GetToLinkPoint();
    
    virtual int GetLinkDir(int nSide);
    virtual int GetFromLinkDir();
    virtual int GetToLinkDir();
    virtual int GetMinXOffset() {return 0;}
    virtual CString GetMetaName(){return "Port";};
    
    virtual int GetFromSide() {return m_nFromSide;}
    virtual int GetToSide() {return m_nToSide;}
    virtual int SetFromSide(int nNewSide);
    virtual int SetToSide(int nNewSide);

    virtual BOOL GetUserCreatedLinks() {return m_bUserCreatedLinks;}
    virtual void SetUserCreatedLinks(BOOL bCan) {m_bUserCreatedLinks = bCan;}
    
    virtual void GeometryChange(CRect* pRectPrevious);      // called when object moved/resized

    virtual void AddLink(DragDropObject* pLink);       // should only be called from Link, should this be a friend class?
    virtual void RemoveLink(DragDropObject* pLink);    // ditto

    virtual void Serialize(CArchive& ar);

protected:

   virtual void InitSize();
   virtual void Measure(CDC* pDC);                         // Calculate size
   virtual void Measure();
   virtual void PortChanged();

   static CImageList*  m_pImglist;

   int         m_nFromSide;            // determines Initial direction an link takes (inbound or outbound)
   int         m_nToSide;
   int         m_nBitmapId;

   int         m_nWidth;
   int         m_nHeight;

   CObList     m_oblistLinks;          // list of associated links

   BOOL        m_bValidLink;           // not archived - set on each mouse down on a source port
   BOOL        m_bUserCreatedLinks;    // mouse down starts link if TRUE
   static  int m_nScaleNoDraw;
   static  int m_nScaleFakeDraw;

   DECLARE_SERIAL(DragDropPort)
};

#endif 
