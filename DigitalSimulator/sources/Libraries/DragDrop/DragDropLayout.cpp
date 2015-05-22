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
#include "DragDropLayout.h"
#include "DragDropDocument.h"
#include "DragDropLink.h"
#include "DragDropPort.h"

//----------------------------------------------------------------------------
DragDropLayout::DragDropLayout(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
DragDropLayout::~DragDropLayout(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   for (POSITION pos = m_LayoutNodes.GetHeadPosition(); pos != NULL; ) {
        CObject* pObj = m_LayoutNodes.GetNext(pos);
        delete pObj;
    }
    for (int i=0; i<m_ColLayout.GetSize(); i++) {
        CObject* pObj = m_ColLayout.GetAt(i);
        delete pObj;
    }
}


//----------------------------------------------------------------------------// Gets a pointer to a layout node from the array.
DragDropLayoutNode* DragDropLayout::GetRowCol(int nRow, int nCol){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CObArray* pRowLayout = (CObArray*)m_ColLayout[nCol];
   DragDropLayoutNode* pLayoutNode = (DragDropLayoutNode*)(pRowLayout->GetAt(nRow));
   if (pLayoutNode != NULL)
       ASSERT(pLayoutNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
   return pLayoutNode;
}

//----------------------------------------------------------------------------
void DragDropLayout::SetRowCol(int nRow, int nCol, DragDropLayoutNode* pNode){
//----------------------------------------------------------------------------
	PROC_TRACE;

   ASSERT(pNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
   CObArray* pRowLayout = (CObArray*)m_ColLayout[nCol];
   pRowLayout->SetAt(nRow, pNode);
   pNode->SetRow(nRow);
   pNode->SetCol(nCol);
   m_nNodesToLayout--;
}

//----------------------------------------------------------------------------
int DragDropLayout::FindNextBlankRow(int nCol){
//----------------------------------------------------------------------------
	PROC_TRACE;

   for (int nRow=0; nRow<m_LayoutNodes.GetCount(); nRow++) {
        if (GetRowCol(nRow, nCol) == NULL)
            return nRow;
    }
    return -1;  // Error if we reach here
}

void DragDropLayout::LayoutDiagram(DragDropDocument* pGoDoc,
                                    int nDirection,
                                    int nNodeHeight,
                                    int nNodeWidth,
                                    int nSpacePrcnt,
                                    BOOL bBalanceLayout,
                                    BOOL bResizeNodes,
                                    int nHorizOffset,
                                    int nVertOffset){
    // Create a DragDropLayoutNode for each toplevel Go object
    // Start by deleting any existing Layout nodes
    for (POSITION pos = m_LayoutNodes.GetHeadPosition(); pos != NULL; ) {
        CObject* pObj = m_LayoutNodes.GetNext(pos);
        delete pObj;
    }
    // Now create new DragDropLayoutNodes
    for (pos = pGoDoc->GetFirstObjectPos(); pos != NULL; ) {
        DragDropObject* pGoObj = pGoDoc->GetNextObject(pos);
        if (pGoObj->GetParent() == NULL) {
            // This is a toplevel object
            if ((!pGoObj->IsNoLayout()) &&
                (!pGoObj->IsKindOf(RUNTIME_CLASS(DragDropLink))) &&
                (!pGoObj->IsKindOf(RUNTIME_CLASS(DragDropPort)))) {
                DragDropLayoutNode* pLayoutNode = new DragDropLayoutNode(pGoObj, this);
                m_LayoutNodes.AddTail(pLayoutNode);
            }
        }
    }

    // Initialize layout table with proper number of rows and columns
    // Start by deleting previous table
    for (int i=0; i<m_ColLayout.GetSize(); i++) {
        CObList* pRowLayout = (CObList*)m_ColLayout[i];
        ASSERT(pRowLayout->IsKindOf(RUNTIME_CLASS(CObList)));
        delete pRowLayout;
    }
    // Now Initialize layout table
    int nToplevelCount = m_LayoutNodes.GetCount();
    for (i=0; i<nToplevelCount; i++) {
        m_ColLayout.SetAtGrow(i, new CObArray());
        for (int j=0; j<nToplevelCount; j++) {
            ((CObArray*)(m_ColLayout[i]))->SetAtGrow(j, NULL);
        }
    }

    // Link together all DragDropLayoutNodes
    // Start by finding all links and updating the nodes they connect
    for (pos = pGoDoc->GetFirstObjectPos(); pos != NULL; ) {
        DragDropObject* pGoObj = pGoDoc->GetNextObject(pos);
        if (pGoObj->IsKindOf(RUNTIME_CLASS(DragDropLink))) {
            DragDropLink* pLink = (DragDropLink*)pGoObj;
            DragDropPort* pPort1 = pLink->GetFromPort();
            DragDropPort* pPort2 = pLink->GetToPort();
            // Allow user to override FromNode() and ToNode()
            DragDropLayoutNode* pFromNode = FromNode(pPort1, pPort2);
            DragDropLayoutNode* pToNode = ToNode(pPort1, pPort2);
            DragDropPort* pFromPort = NULL;
            if ((pFromNode != NULL) && (pToNode != NULL)) {
                if (pPort1->GetParent() == pFromNode->GetGoObject())
                    pFromPort = pPort1;
                else
                    pFromPort = pPort2;
                pFromNode->AddChild(pToNode, pFromPort, nDirection);
                pToNode->AddParent(pFromNode);
            }
        }
    }

    // Count ultimate predecessors
    for (pos = m_LayoutNodes.GetHeadPosition(); pos != NULL; ) {
        // Clear the "visited" flag
        for (POSITION pos2 = m_LayoutNodes.GetHeadPosition(); pos2 != NULL; ) {
            DragDropLayoutNode* pLayoutNode = (DragDropLayoutNode*)m_LayoutNodes.GetNext(pos2);
            ASSERT(pLayoutNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
            pLayoutNode->SetVisited(FALSE);
        }
        DragDropLayoutNode* pStartNode = (DragDropLayoutNode*)m_LayoutNodes.GetNext(pos);
        pStartNode->CountPredecessors();
    }

    // Find node with minimum ultimate predecessors and do Initial layout
    int nCurrentMaxRow = 0;
    m_nNodesToLayout = m_LayoutNodes.GetCount();
    while (m_nNodesToLayout != 0) {
        // Find node with minimum number of predecessors and lay it out
        int nCurrentMin = -1;
        DragDropLayoutNode* pStartNode = NULL;
        for (pos = m_LayoutNodes.GetHeadPosition(); pos != NULL; ) {
            DragDropLayoutNode* pNode = (DragDropLayoutNode*)(m_LayoutNodes.GetNext(pos));
            ASSERT(pNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
            // Make sure it's not already layed out
            if ((pNode->GetRow() == -1) && (pNode->GetCol() == -1))
                // Find the node with the least number of predecessors
                if ((nCurrentMin == -1) || (pNode->GetPredecessors() < nCurrentMin)) {
                    pStartNode = pNode;
                    nCurrentMin = pStartNode->GetPredecessors();
            }
        }
        SetRowCol(FindNextBlankRow(0), 0, pStartNode);
        pStartNode->SimpleLayout(1);
        // Balance the spacing of the nodes in each row
            nCurrentMaxRow = pStartNode->AssignRow(nCurrentMaxRow);
    }


    // Finally, place the nodes
    int nXNodeSpace = nNodeWidth * nSpacePrcnt/100;
    int nYNodeSpace = nNodeHeight * nSpacePrcnt/100;
    for (pos = m_LayoutNodes.GetHeadPosition(); pos != NULL; ) {
        DragDropLayoutNode* pNode = (DragDropLayoutNode*)(m_LayoutNodes.GetNext(pos));
        ASSERT(pNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
        DragDropObject* pGoObject = pNode->GetGoObject();
        int nRowsPerNode = 1;
        if (bBalanceLayout)
            nRowsPerNode = 2;
        int nXPos;
        int nYPos;
        if (nDirection == LAYOUT_HORIZ) {
            nXPos = nXNodeSpace + (nXNodeSpace + nNodeWidth) * pNode->GetCol();
            nYPos = -nYNodeSpace - (nYNodeSpace + nNodeHeight) * pNode->GetRow()/nRowsPerNode;
        }
        else {
            nXPos = nXNodeSpace + (nXNodeSpace + nNodeWidth) * pNode->GetRow()/nRowsPerNode;
            nYPos = -nYNodeSpace - (nYNodeSpace + nNodeHeight) * pNode->GetCol();
        }
        pGoObject->SetLocation(nHorizOffset + nXPos, nVertOffset + nYPos);
        if (bResizeNodes) {
            pGoObject->SetSize(nNodeWidth, nNodeHeight);
        }
    }
}

IMPLEMENT_DYNAMIC(DragDropLayoutNode, CObject)

//----------------------------------------------------------------------------
DragDropLayoutNode::DragDropLayoutNode(DragDropObject* pGoObj, DragDropLayout* pLayout){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_object = pGoObj;
   m_pLayout = pLayout;
   m_nCol = -1;
   m_nRow = -1;
   m_nUltimatePredecessors = -1;
   m_bVisited = FALSE;
   m_bVisited2 = FALSE;
}

//----------------------------------------------------------------------------
int DragDropLayoutNode::AssignRow(int nCurrentMax){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Leave a breadcrumb to indicate we've been here
    SetVisited2(TRUE);

    // Position your kids
    DragDropLayoutNode* pNode = NULL;
    DragDropLayoutNode* pFirstKid = NULL;
    DragDropLayoutNode* pLastKid = NULL;
    for (POSITION pos = m_Children.GetHeadPosition(); pos != NULL; ) {
        pNode = (DragDropLayoutNode*)m_Children.GetNext(pos);
        if (pNode->GetVisited2())
            continue;
        if (pNode->GetCol() != GetCol() + 1)
            continue;
        if (pFirstKid == NULL)
            pFirstKid = pNode;
        ASSERT(pNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
        nCurrentMax = pNode->AssignRow(nCurrentMax);
    }
    pLastKid = pNode;

    // If pFirstKid is still NULL, we have no kids we haven't previously visited
    // so position yourself at row nCurrentMax and leave
    if (pFirstKid==NULL) {
        SetRow(nCurrentMax);
        return (nCurrentMax + 2);
    }
        
    // Position yourself in the middle of your kids
    int nNewRow = (pLastKid->GetRow() + pFirstKid->GetRow()) / 2;
    SetRow(nNewRow);

    return nCurrentMax;
}

//----------------------------------------------------------------------------
void DragDropLayoutNode::SimpleLayout(int nCol){
//----------------------------------------------------------------------------
	PROC_TRACE;

   // Place your children (if not already placed).-- do this first to assure breadth first placement
   // Recurse on any child you placed
   CObList RecurseList;
   for (POSITION pos = m_Children.GetHeadPosition(); pos != NULL; ) {
        DragDropLayoutNode* pNode = (DragDropLayoutNode*)m_Children.GetNext(pos);
        ASSERT(pNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
        if ((pNode->GetRow() == -1) && (pNode->GetCol() == -1)) {
            GetLayout()->SetRowCol(GetLayout()->FindNextBlankRow(nCol), nCol, pNode);
            RecurseList.AddTail(pNode);
        }
    }

    // Now recurse on each of the children we placed
    for (pos = RecurseList.GetHeadPosition(); pos != NULL; ) {
        DragDropLayoutNode* pNode = (DragDropLayoutNode*)m_Children.GetNext(pos);
        ASSERT(pNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
        pNode->SimpleLayout(nCol + 1);
    }
}

//----------------------------------------------------------------------------
void DragDropLayoutNode::CountPredecessors(){
//----------------------------------------------------------------------------
	PROC_TRACE;

   if (GetVisited())
        return;
    SetVisited(TRUE);
    m_nUltimatePredecessors++;
    for (POSITION pos = m_Children.GetHeadPosition(); pos != NULL; ) {
        DragDropLayoutNode* pLayoutNode = (DragDropLayoutNode*)m_Children.GetNext(pos);
        ASSERT(pLayoutNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
        pLayoutNode->CountPredecessors();
    }
}

// Add child to child list, sorted by port position so that links don't cross to

//----------------------------------------------------------------------------// imediate children.
void DragDropLayoutNode::AddChild(DragDropLayoutNode* pNode, DragDropPort* pPort, int nDirection){
//----------------------------------------------------------------------------
	PROC_TRACE;

   POSITION pos1 = m_Children.GetHeadPosition();
    POSITION pos2 = m_ChildPorts.GetHeadPosition();
    while ((pos1 != NULL) && (pos2 != NULL)) {
        POSITION CurrentPos1 = pos1;
        POSITION CurrentPos2 = pos2;
        DragDropLayoutNode* pLayoutNode = (DragDropLayoutNode*)m_Children.GetNext(pos1);
        ASSERT(pLayoutNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
        DragDropPort* pGoPort = (DragDropPort*)m_ChildPorts.GetNext(pos2);
        ASSERT(pGoPort->IsKindOf(RUNTIME_CLASS(DragDropPort)));
        BOOL bInsertBefore = FALSE;
        if ((nDirection == LAYOUT_HORIZ) && (pPort->GetLocation().y > pGoPort->GetLocation().y))
            bInsertBefore = TRUE;
        if ((nDirection == LAYOUT_VERT) && (pPort->GetLocation().x < pGoPort->GetLocation().x))
            bInsertBefore = TRUE;
        if (bInsertBefore) {
            m_Children.InsertBefore(CurrentPos1, pNode);
            m_ChildPorts.InsertBefore(CurrentPos2, pPort);
            return;
        }
    }
    m_Children.AddTail(pNode);
    m_ChildPorts.AddTail(pPort);
}

//----------------------------------------------------------------------------
void DragDropLayoutNode::AddParent(DragDropLayoutNode* pNode){
//----------------------------------------------------------------------------
	PROC_TRACE;

   m_Parents.AddTail(pNode);
}

//----------------------------------------------------------------------------
DragDropLayoutNode* DragDropLayout::FromNode(DragDropPort* pPort1, DragDropPort* pPort2){
//----------------------------------------------------------------------------
	PROC_TRACE;

   DragDropObject* pParent = m_doc->FromPort(pPort1, pPort2)->GetParent();
    if (pParent != NULL){
        for (POSITION pos = m_LayoutNodes.GetHeadPosition(); pos != NULL; ) {
           DragDropLayoutNode* pLayoutNode = (DragDropLayoutNode*)(m_LayoutNodes.GetNext(pos));
           ASSERT(pLayoutNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
           if (pLayoutNode->GetGoObject() == pParent)
               return pLayoutNode;
        }
    }
    return NULL;
}

//----------------------------------------------------------------------------
DragDropLayoutNode* DragDropLayout::ToNode(DragDropPort* pPort1, DragDropPort* pPort2){
//----------------------------------------------------------------------------
	PROC_TRACE;

    DragDropObject* pParent = m_doc->ToPort(pPort1, pPort2)->GetParent();
    if (pParent != NULL){
        for (POSITION pos = m_LayoutNodes.GetHeadPosition(); pos != NULL; ) {
           DragDropLayoutNode* pLayoutNode = (DragDropLayoutNode*)(m_LayoutNodes.GetNext(pos));
           ASSERT(pLayoutNode->IsKindOf(RUNTIME_CLASS(DragDropLayoutNode)));
           if (pLayoutNode->GetGoObject() == pParent)
               return pLayoutNode;
        }
    }
    return NULL;
}

