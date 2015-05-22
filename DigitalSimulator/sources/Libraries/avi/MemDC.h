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

#ifndef _MEMDC_H_
#define _MEMDC_H_
class CMemDC : public CDC {
private:
   CBitmap m_bitmap; // Offscreen bitmap
   CBitmap* m_oldBitmap; // bitmap originally found in CMemDC
   CDC* m_pDC; // Saves CDC passed in constructor
   BOOL m_bMemDC; // TRUE if CDC really is a Memory DC.
public:
   CRect m_rect; // Rectangle of drawing area.
   
   CMemDC(CDC* pDC, CRect &rect) : CDC(), m_oldBitmap(NULL), m_pDC(pDC)
   {
           ASSERT(m_pDC != NULL); // If you asserted here, you passed in a NULL CDC.
           m_bMemDC = !pDC->IsPrinting();
           m_rect=rect;
           if (m_bMemDC){
                   // Create a Memory DC
                   CreateCompatibleDC(pDC);
                   pDC->GetClipBox(&m_rect);
                   m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
                   m_oldBitmap = SelectObject(&m_bitmap);
                   SetWindowOrg(m_rect.left, m_rect.top);
           } else {
                   // Make a copy of the relevent parts of the current DC for printing
                   m_bPrinting = pDC->m_bPrinting;
                   m_hDC = pDC->m_hDC;
                   m_hAttribDC = pDC->m_hAttribDC;
           }
   }
   ~CMemDC()
   {
           if (m_bMemDC) {
                   // Copy the offscreen bitmap onto the screen.
                   m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
                           this, m_rect.left, m_rect.top, SRCCOPY);
                   //Swap back the original bitmap.
                   SelectObject(m_oldBitmap);
           } else {
                   // All we need to do is replace the DC with an illegal value,
                   // this keeps us from accidently deleting the handles associated with
                   // the CDC that was passed to the constructor.
                   m_hDC = m_hAttribDC = NULL;
           }
   }
   // Allow usage as a pointer
   CMemDC* operator->() {return this;}
   // Allow usage as a pointer
   operator CMemDC*() {return this;}
};

#endif
