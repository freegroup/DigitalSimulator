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

#include "stdafx.h"
#include <assert.h>
#include "Application\DigitalSimulatorApp.h"
#include "DialogSecondaryObjectOptions.h"

#include "Application\Objects\buildin\digital\ElectricNodeContext.h"

BEGIN_MESSAGE_MAP(CDialogSecondaryObjectOptions, CSnapDialog)
	//{{AFX_MSG_MAP(CDialogSecondaryObjectOptions)
	ON_NOTIFY(TVN_SELCHANGED, IDC_OBJECT_TREE, OnClickObjectTree)
	ON_EN_VSCROLL(IDC_DESCRIPTION_EDIT, OnVscrollDescriptionEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//----------------------------------------------------------------------------
CDialogSecondaryObjectOptions::CDialogSecondaryObjectOptions(CWnd* pParent, CElectricNode::CElectricNodeDokument& data)
   : inherited(CDialogSecondaryObjectOptions::IDD, pParent),
     m_data(data){
//----------------------------------------------------------------------------
	PROC_TRACE;

   //{{AFX_DATA_INIT(CDialogSecondaryObjectOptions)
	//}}AFX_DATA_INIT
	m_inputCount  = 0;
	m_outputCount = 0;
}


//----------------------------------------------------------------------------
void CDialogSecondaryObjectOptions::DoDataExchange(CDataExchange* pDX){
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogSecondaryObjectOptions)
	DDX_Control(pDX, IDOK, m_okButton);
	DDX_Control(pDX, IDCANCEL, m_cancelButton);
	DDX_Control(pDX, IDC_OBJECT_TREE, m_objectTree);
	DDX_Control(pDX, IDC_DESCRIPTION_EDIT, m_descriptionEdit);
	//}}AFX_DATA_MAP
}



//----------------------------------------------------------------------------
BOOL CDialogSecondaryObjectOptions::OnInitDialog() {
//----------------------------------------------------------------------------
	PROC_TRACE;

   inherited::OnInitDialog();
   HTREEITEM selectItem;

   SetWindowText(TRANSLATE("COMMON.DIALOGHEADER.EXTOBJECTPROPERTIES"));
   TRANSLATE_DIALOG_ITEM(IDC_OBJEKTID_STATIC);	
   TRANSLATE_DIALOG_ITEM(IDOK);	
   TRANSLATE_DIALOG_ITEM(IDCANCEL);	

   m_okButton.SetShaded();
   m_cancelButton.SetShaded();

   m_metaNameString = m_data.key;
  

   // Alle registrierten Objektkontexte in den objectTree
   // eintragen
   //

   CElectricNodeContext* pContext;
   CString item;
//   CString group;
   POSITION pos = g_contextMap->GetStartPosition();
   while( pos != NULL ) {
      g_contextMap->GetNextAssoc( pos, item, pContext );
      if(pContext && item!=CString("OBJ_GENERIC")){
      //   group = pContext->GetGroup();
         if(item == m_metaNameString)
            selectItem=m_objectTree.InsertItem(pContext);   
         else
            m_objectTree.InsertItem(pContext);   
      }
   }


   UpdateGUI(m_data.key);
   m_objectTree.EnsureVisible(selectItem);
   m_objectTree.SelectItem(selectItem);
   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX-Eigenschaftenseiten sollten FALSE zurückgeben
}


//----------------------------------------------------------------------------
void CDialogSecondaryObjectOptions::UpdateGUI( CString key){
//----------------------------------------------------------------------------
	PROC_TRACE;

   CString desc = "";
   if(key !="")
   {
      CSize   inRange;
      CSize   outRange;
   
      CElectricNodeContext* context =CElectricNodeContext::GetContext(key);
      m_metaNameString = key;
      assert( context != NULL);

      // Man darf in dem Dialog nur moegliche Werte eintragen koennen
      // Z.B. ein 'Power'-Objekt hat genau EINEN Eingang.
      // Dieser Wert wird nun eingestellt.
      // m_obj->GetOutputCountRange() : Geforderte Mindest- und
      //                                Hoechstanzahl von Ausgaengen.
      // SetPos(max(.....))           : Wert darf die geforderte Mindestanzahl
      //                                nicht uebersteigen, und den Wert Einstellen
      // SetPos(min(.....))           : Wert darf die geforderte Hoechstanzahl 
      //                                nicht uebersteigen.
      //
      outRange  = context->GetOutputCountRange();
      m_outputCount = min(m_data.outPorts.GetSize(),outRange.cy);
      m_outputCount = max(m_outputCount            ,outRange.cx);

      inRange  = context->GetInputCountRange();
      m_inputCount = min(m_data.inPorts.GetSize(),inRange.cy);
      m_inputCount = max(m_inputCount            ,inRange.cx);
      context->AdjustInputOutputCount(m_inputCount, m_outputCount);

      desc = context->GetDescriptionText();
   }
   
   m_descriptionEdit.ShowWindow(SW_HIDE);
   m_descriptionEdit.SetWindowText(desc);
   m_descriptionEdit.ShowWindow(SW_SHOW);
   m_descriptionEdit.RedrawWindow();
}


//----------------------------------------------------------------------------
void CDialogSecondaryObjectOptions::OnClickObjectTree(NMHDR* pNMHDR, LRESULT* pResult) {
//----------------------------------------------------------------------------
	PROC_TRACE;

	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

   // es wurde eine Gruppe selektiert -> nichts tun
   //
   if(m_objectTree.ItemHasChildren(pNMTreeView->itemNew.hItem)){
      UpdateGUI("");
   }
   // Es wurde ein Blatt selektiert
   //
   else{
	  CElectricNodeContext* context = (CElectricNodeContext*) m_objectTree.GetItemData(pNMTreeView->itemNew.hItem) ;
      UpdateGUI(context->GetKey());
   }

	*pResult = 0;
}

void CDialogSecondaryObjectOptions::OnVscrollDescriptionEdit() 
{
	// TODO: Code für die Behandlungsroutine der Steuerelement-Benachrichtigung hier einfügen
//   Invalidate();
//   m_descriptionEdit.Invalidate();	
   // repaint the descriptionEdit editWindow
   //
}
