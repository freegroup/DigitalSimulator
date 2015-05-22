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

#ifndef _DRAGDROPLAYOUT_H_
#define _DRAGDROPLAYOUT_H_

#include "DragDropobject.h"

const int LAYOUT_HORIZ = 0;
const int LAYOUT_VERT = 1;

class DragDropPort;
class DragDropLayoutNode;

class DragDropLayout : public CObject{
    typedef CObject inherited ;
public:
    DragDropLayout();
    virtual ~DragDropLayout();

    void LayoutDiagram(DragDropDocument* pGoDoc,
        int nDirection = LAYOUT_HORIZ,
        int nNodeHeight = 300,
        int nNodeWidth = 300,
        int nSpacePrcnt = 30,
        BOOL bBalanceLayout = TRUE,
        BOOL bResizeNodes = FALSE,
        int nHorizOffset = 0,
        int nVertOffset = 0);

private:
    CObArray m_ColLayout;
    CObList m_LayoutNodes;
    int m_nNodesToLayout;
protected:
    virtual DragDropLayoutNode* FromNode(DragDropPort* pPort1, DragDropPort* pPort2);
    virtual DragDropLayoutNode* ToNode(DragDropPort* pPort1, DragDropPort* pPort2);
    virtual void SetRowCol(int nRow, int nCol, DragDropLayoutNode* pNode);
    virtual DragDropLayoutNode* GetRowCol(int nRow, int nCol);
    virtual int FindNextBlankRow(int nCol);

	DragDropDocument* m_doc;
   friend class DragDropLayoutNode;
};

class DragDropLayoutNode : public CObject{
    typedef CObject inherited ;
    friend class DragDropLayout;
protected:
    DECLARE_DYNAMIC(DragDropLayoutNode)
    DragDropLayoutNode(DragDropObject* pGoObject, DragDropLayout* pLayout);
    virtual void AddChild(DragDropLayoutNode* pNode, DragDropPort* pPort, int nDirection);
    virtual void AddParent(DragDropLayoutNode* pNode);
    virtual DragDropObject* GetGoObject() {return m_object;}
    virtual BOOL GetVisited() {return m_bVisited;}
    virtual void SetVisited(BOOL bVisited) {m_bVisited = bVisited;}
    virtual BOOL GetVisited2() {return m_bVisited2;}
    virtual void SetVisited2(BOOL bVisited) {m_bVisited2 = bVisited;}
    virtual void CountPredecessors();
    virtual int GetPredecessors() {return m_nUltimatePredecessors;}
    virtual DragDropLayout* GetLayout() {return m_pLayout;}
    virtual void SetRow(int nRow) {m_nRow = nRow;}
    virtual int GetRow() {return m_nRow;}
    virtual void SetCol(int nCol) {m_nCol = nCol;}
    virtual int GetCol() {return m_nCol;}
    virtual void SimpleLayout(int nCol);
    virtual int AssignRow(int nCurrentMax);

private:
    DragDropObject* m_object;
    DragDropLayout* m_pLayout;
    CObList m_Children;
    CObList m_ChildPorts;
    CObList m_Parents;
    int m_nRow;
    int m_nCol;
    int m_nUltimatePredecessors;
    BOOL m_bVisited;
    BOOL m_bVisited2;
};

#endif 