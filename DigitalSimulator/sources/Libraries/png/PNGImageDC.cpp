// PNGImageDC.cpp: implementation of the PNGImageDC class.
//
//////////////////////////////////////////////////////////////////////

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#include "PNGImageDC.h"
#include "WINDOWSX.H"
#include "hipng.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PNGImageDC::PNGImageDC()
{
	cOldBitmap = NULL;
}

PNGImageDC::~PNGImageDC()
{
	if(cOldBitmap)
	{
		//delete the bitmap
		SelectObject(cOldBitmap);
		cBitmap.DeleteObject();
	}
}

BOOL PNGImageDC::Create(CSize &pImageSize)
{
	cImageSize = pImageSize;
	if(CreateCompatibleDC(NULL))
	{
		unsigned long width = pImageSize.cx;
		unsigned long height = pImageSize.cy;
		
		//set up a bitmap to receive the drawing
		int planes = GetDeviceCaps(PLANES);
		int bpp = GetDeviceCaps(BITSPIXEL);
		ASSERT(!(planes == 1 && bpp == 8)); //Can't support 256 ColorMode
		if(cBitmap.CreateBitmap(width,height,
			planes,bpp,NULL))
		{
			cOldBitmap = SelectObject(&cBitmap);
			return TRUE;
		}
		ASSERT(FALSE); //bitmap did not create
	}
	ASSERT(FALSE); //DC did not create
	return(FALSE); 
}

void PNGImageDC::Erase(COLORREF pColor)
{
	CRect clip;
	GetClipBox(clip);
	FillSolidRect(clip,pColor);
}


BOOL PNGImageDC::Save(CString &pFileName, BOOL pInterlaced, 
	BOOL pTransparent, COLORREF pTransparentColor)
{
	CFile file;
	if(!file.Open(pFileName, CFile::modeWrite | CFile::modeCreate))
	{
		return FALSE;
	}
	return BaseSave(file,pInterlaced,	pTransparent,pTransparentColor);
}

BOOL PNGImageDC::Stream(CMemFile * pMemFile, BOOL pInterlaced, 
	BOOL pTransparent, COLORREF pTransparentColor)
{
	return BaseSave(*pMemFile,pInterlaced,	pTransparent,pTransparentColor);
}


BOOL PNGImageDC::BaseSave(CFile &pFile, BOOL pInterlaced, 
	BOOL pTransparent, COLORREF pTransparentColor)
{
	// create a BITMAPINFO struct for the DIB
	BITMAPINFO *pbmi = 
	  (BITMAPINFO *) malloc (sizeof (BITMAPINFO) + (3*(sizeof(RGBQUAD)))); 
	if (pbmi == NULL)
	{
		return FALSE;
	}
	BITMAPINFOHEADER *pbmih = (BITMAPINFOHEADER *) pbmi;
	ZeroMemory (pbmi, (DWORD) sizeof (BITMAPINFOHEADER));
	pbmih->biSize = sizeof (BITMAPINFOHEADER);
	pbmih->biCompression = BI_RGB;

	// get the size of the buffer we need for the pixel bits
	GetDIBits (m_hDC, cBitmap, 0, 0, NULL, pbmi, DIB_RGB_COLORS);
	LPVOID p = new BYTE [pbmih->biSizeImage]; // allocate the buffer
	if (p == NULL)
	{
		free (pbmi);
		return FALSE;
	}
	//	copy the pixel bits from the DDB to the DIB
	GetDIBits (m_hDC, cBitmap, 0, (UINT) pbmih->biHeight,
		(LPVOID) p, pbmi, DIB_RGB_COLORS);

	//	we now have the image in the DIB
	//	fill in the HIPNG_DIB structure

	int color_type;
	switch (pbmih->biBitCount)
	{
	    case 1:
	    case 2:
	    case 4:
	    case 8:
			color_type = PNG_COLOR_TYPE_PALETTE;
		break;
	    case 16:
	    case 32:
	    case 24:
		default:
			color_type = PNG_COLOR_TYPE_RGB;
		break;
	}


	png_text_struct text_ptr[1];
	text_ptr[0].key = "www.FreeGroup.com";
	text_ptr[0].text = "PNGImageDC from FreeGroup / PNG";
	text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;  

	HIPNG_DIB	hp;
	hp.hbmi = pbmi;
	hp.pixels = (PBYTE) p;
	hp.color_type = color_type;
	hp.interlaced = pInterlaced;
	hp.gamma = -1.0;         // no gamma
	hp.num_text = 1;         // See num_text
	hp.pComment = text_ptr;  //   for the supporting code
	hp.current_time = TRUE;
	png_color_16 rgb24;
	if(pTransparent)
	{
		rgb24.index	= 0;
		rgb24.red	= GetRValue(pTransparentColor);
		rgb24.green	= GetGValue(pTransparentColor);
		rgb24.blue	= GetBValue(pTransparentColor);
		rgb24.gray	= 0;
		hp.transparent_palette = NULL; // no palette for this color type  
		hp.num_transparent = 1;
		hp.RGBtransparent_value = &rgb24;  // set transparent color
	}
	else
	{
		hp.transparent_palette = NULL; // no palette for this color type  
		hp.num_transparent = 0;
		hp.RGBtransparent_value = NULL;  // no transparent color
	}
	hp.row_callback_fn = NULL;         // no callback function

	BOOL result = write_dib_to_png (&hp, pFile);   // write the png file
	free(pbmi);
	delete p;
	return result;
}