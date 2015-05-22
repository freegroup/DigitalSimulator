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

#ifndef DIB256_h
#define DIB256_h


class CDIBitmap
{
	friend class CBmpPalette;

	BITMAPINFO *	m_pInfo;
	BYTE *			m_pPixels;
	CBmpPalette *	m_pPal;
	BOOL			m_bIsPadded;

	public:		//constructors
		CDIBitmap();
		virtual ~CDIBitmap();

	private:
		CDIBitmap( const CDIBitmap& dbmp );

	public:		// attributes
		BITMAPINFO *	GetHeaderPtr() const;
		BYTE *			GetPixelPtr() const;
		RGBQUAD *		GetColorTablePtr() const;
		int				GetWidth() const;
		int				GetHeight() const;
		CBmpPalette *	GetPalette() { return m_pPal; }

	public:		// operations
		BOOL			CreatePalette();	// auto. made by "Load()" and "CreateFromBitmap()"
		void			ClearPalette();		// destroy the palette associated with this image
		BOOL			CreateFromBitmap( CDC *, CBitmap * );
		BOOL			LoadResource(LPCTSTR ID);
		BOOL			LoadResource(UINT ID) { return LoadResource(MAKEINTRESOURCE(ID)); }
		BOOL			LoadBitmap(UINT ID) { return LoadResource(ID); }
		BOOL			LoadBitmap(LPCTSTR ID) { return LoadResource(ID); }
		void			DestroyBitmap();
		BOOL			DeleteObject() { DestroyBitmap(); return TRUE; }
		
	public:		// overridables
			// draw the bitmap at the specified location
		virtual void	DrawDIB( CDC * pDC, int x=0, int y=0 );

			// draw the bitmap and stretch/compress it to the desired size
		virtual void	DrawDIB( CDC * pDC, int x, int y, int width, int height );

			// draw parts of the dib into a given area of the DC
		virtual int		DrawDIB( CDC * pDC, CRect & rectDC, CRect & rectDIB );

			// load a bitmap from disk
		virtual BOOL	Load( CFile * pFile );
		virtual BOOL	Load( const CString & );

			// save the bitmap to disk
		virtual BOOL	Save( CFile * pFile );
		virtual BOOL	Save( const CString & );

	protected:
		int				GetPalEntries() const;
		int				GetPalEntries( BITMAPINFOHEADER& infoHeader ) const;
		DWORD			GetBitsPerPixel() const;
		DWORD			LastByte( DWORD BitsPerPixel, DWORD PixelCount ) const;
		DWORD			GetBytesPerLine( DWORD BitsPerPixel, DWORD Width ) const;
		BOOL			PadBits();
		BOOL			UnPadBits();
		WORD			GetColorCount() const;
};

#include "dibpal.h"

#endif	// DIB256_h