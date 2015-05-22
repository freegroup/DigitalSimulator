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

#ifndef _DRAGDROPMETA_H_
#define _DRAGDROPMETA_H_

#include "DragDropObject.h" 
#include "DragDropBitmapCach.h"

class DragDropMetaFile : public DragDropObject{
    typedef DragDropObject inherited ;
public:
    DragDropMetaFile();
    DragDropMetaFile(CRect* pRect, const CString& pMetaFile);
    DragDropMetaFile(CPoint location, CSize size, const CString& pMetaFile, BOOL bMaintainAspect);
    virtual ~DragDropMetaFile();
    
    virtual CString MetaFileName() const;
    virtual void    SetMetaFileName(const CString& sNewMetaFileName);

    virtual float AspectRatio() {return m_aspectRatio;}

    virtual BOOL paint(CDC* pDC);
    virtual void GeometryChange(CRect* pRectPrevious);
    virtual void Serialize(CArchive& ar);
    static float GetAspectRatio(const CString& lpFileName);
    virtual DragDropObject* Clone() const;

protected:
    virtual BOOL            DrawBitmap(CDC* pDC, int nScale);
    virtual BOOL            CreateBitmap(CDC* pDC);
    virtual void            ClearBitmapCache(int width, int height);


    CString                  m_fileName;  
    DragDropBitmapCacheDesc *m_bitmapDesc; 
    float                    m_aspectRatio;   
    BOOL                     m_maintainAspect;

    DECLARE_SERIAL(DragDropMetaFile)
};
 
#endif
