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
#include "Application\DigitalSimulatorApp.h"
#include "Application\i18n\ResourceTranslater.h"
#include "Application\Configuration\ParameterManager.h"

#include "DialogDDEINParamWizard.h"
#include "DialogDDEINStartPage.h"
#include "DialogDDESelectApplication.h"
#include "DialogDDEExcelProperties.h"
#include "DialogDDEINCosivisProperties.h"
#include "DialogDDEINEasyPortProperties.h"
#include "DialogDDEUnbekanntProperties.h"
#include "DialogDDEINEndPage.h"

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
CDialogDDEINParamWizard::CDialogDDEINParamWizard(){
//----------------------------------------------------------------------------
	PROC_TRACE;


	CDialogDDEINStartPage          *page1 = new CDialogDDEINStartPage(this);
	CDialogDDESelectApplication    *page2 = new CDialogDDESelectApplication(this);
	CDialogDDEExcelProperties      *page3 = new CDialogDDEExcelProperties(this);
	CDialogDDEINEasyPortProperties *page4 = new CDialogDDEINEasyPortProperties(this);
	CDialogDDEINCosivisProperties  *page5 = new CDialogDDEINCosivisProperties(this);
	CDialogDDEUnbekanntProperties  *page6 = new CDialogDDEUnbekanntProperties(this);
	CDialogDDEINEndPage            *page7 = new CDialogDDEINEndPage(this);


	AddPage(TRANSLATE("DDE Assistent"), page1, CDialogDDEINStartPage::IDD);
	AddPage(TRANSLATE("Geben Sie die Application an, von der Sie Daten empfangen wollen"), page2, CDialogDDESelectApplication::IDD);
	AddPage(TRANSLATE("Einstellungen f�r Excel"), page3, CDialogDDEExcelProperties::IDD);
	AddPage(TRANSLATE("Einstellungen f�r EasyPort"), page4, CDialogDDEINEasyPortProperties::IDD);
	AddPage(TRANSLATE("Einstellungen f�r Cosivis"), page5, CDialogDDEINCosivisProperties::IDD);
	AddPage(TRANSLATE("Einstellungen f�r unbekannte Application"), page6, CDialogDDEUnbekanntProperties::IDD);
	AddPage(TRANSLATE("Fertig"), page7, CDialogDDEINEndPage::IDD);
}

//----------------------------------------------------------------------------
CDialogDDEINParamWizard::~CDialogDDEINParamWizard(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}
