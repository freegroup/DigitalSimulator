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

#include "StdAfx.h"

#include "TransparentImageStatic.h"


//******************************************************************************
//
// Debugging
//
//******************************************************************************

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__ ;
#endif


BEGIN_MESSAGE_MAP( CTransparentImageStatic, CStatic )

	//{{AFX_MSG_MAP( CTransparentImageStatic )
	ON_WM_PAINT()
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

CTransparentImageStatic::CTransparentImageStatic()
{
	PROC_TRACE;

}


CTransparentImageStatic::~CTransparentImageStatic()
{
	PROC_TRACE;

}




void CTransparentImageStatic::OnPaint() 
{
	PROC_TRACE;

	HBITMAP l_hbmpBitmap = GetBitmap() ;

	if( l_hbmpBitmap == NULL )
	{
		Default() ;

		return ;
	}

	CPaintDC l_PaintDC( this ) ;

	////////////////////////////////////////////////////////////////////////////
	// Prepare everything for drawing
	////////////////////////////////////////////////////////////////////////////

	CRect l_rcClient ;

	GetClientRect( &l_rcClient ) ;

	CDC		 l_BufferDC ;
			 l_BufferDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap  l_BufferBitmap ;
			 l_BufferBitmap.CreateCompatibleBitmap( &l_PaintDC, l_rcClient.Width(), l_rcClient.Height() ) ;
	CBitmap* l_pOldBufferBitmap = l_BufferDC.SelectObject( &l_BufferBitmap ) ;
	CDC		 l_MaskDC ;
			 l_MaskDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap  l_MaskBitmap ;
			 l_MaskBitmap.CreateBitmap( l_rcClient.Width(), l_rcClient.Height(), 1, 1, NULL ) ;
	CBitmap* l_pOldMaskBitmap = l_MaskDC.SelectObject( &l_MaskBitmap ) ;

	#define ROP4_TRANSPARENTBLIT		0xCCAA0020
	#define SRCMASK						0x00220326

	////////////////////////////////////////////////////////////////////////////
	// Fill with transparent color
	////////////////////////////////////////////////////////////////////////////

	l_BufferDC.FillSolidRect( &l_rcClient, RGB( 255, 0, 255 ) ) ;

	////////////////////////////////////////////////////////////////////////////
	// Blit the bitmap to the buffer
	////////////////////////////////////////////////////////////////////////////

	CDC		 l_MemoryDC ;
			 l_MemoryDC.CreateCompatibleDC( &l_PaintDC ) ;
	CBitmap* l_pOldMemoryBitmap = l_MemoryDC.SelectObject( CBitmap::FromHandle( l_hbmpBitmap ) ) ;

	l_BufferDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MemoryDC, 0, 0, SRCCOPY ) ;

	l_MemoryDC.SelectObject( l_pOldMemoryBitmap ) ;

	////////////////////////////////////////////////////////////////////////////
	// Create the mask.
	////////////////////////////////////////////////////////////////////////////

	COLORREF l_crOldBack = l_BufferDC.SetBkColor( RGB( 255, 0, 255 ) ) ;

	l_MaskDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_BufferDC, 0, 0, SRCCOPY ) ;

	l_BufferDC.SetBkColor( l_crOldBack ) ;

	////////////////////////////////////////////////////////////////////////////
	// Draw the bitmap transparently now, since not all devices support this
	// and Windows 98 does not (duh?), if this fails, we do it the long way.
	////////////////////////////////////////////////////////////////////////////

	if( ! l_PaintDC.MaskBlt( 0, 
							 0, 
					   		 l_rcClient.Width(),
					   		 l_rcClient.Height(),
					   		 &l_BufferDC,
					   		 0,
					   		 0,
					   		 l_MaskBitmap,
					   		 0,
					   		 0,
					   		 ROP4_TRANSPARENTBLIT ) )
	{
		CDC		 l_CopyDC ;
				 l_CopyDC.CreateCompatibleDC( &l_PaintDC ) ;
		CBitmap  l_CopyBitmap ;
				 l_CopyBitmap.CreateCompatibleBitmap( &l_PaintDC, l_rcClient.Width(), l_rcClient.Height() ) ;
		CBitmap* l_pOldCopyBitmap = l_CopyDC.SelectObject( &l_CopyBitmap ) ;

		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_PaintDC,  0, 0, SRCCOPY  ) ;
		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MaskDC,   0, 0, SRCAND   ) ;
		l_BufferDC.BitBlt( 0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_MaskDC,   0, 0, SRCMASK  ) ;
		l_CopyDC.BitBlt(   0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_BufferDC, 0, 0, SRCPAINT ) ;
		l_PaintDC.BitBlt(  0, 0, l_rcClient.Width(), l_rcClient.Height(), &l_CopyDC,   0, 0, SRCCOPY  ) ;

		l_CopyDC.SelectObject( l_pOldCopyBitmap ) ;
	}

	////////////////////////////////////////////////////////////////////////////
	// Clean up.
	////////////////////////////////////////////////////////////////////////////

	l_MaskDC.SelectObject( l_pOldMaskBitmap ) ;
	l_BufferDC.SelectObject( l_pOldBufferBitmap ) ;
}
