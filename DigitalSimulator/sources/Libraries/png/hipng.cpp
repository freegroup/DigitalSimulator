#include <afx.h>
#include "png.h"
/*
	Library of high-level routines to write a .png file
	Copywrite 1999 Alan Algustyniak

						Version 1.1

						6 July 1999

	Acknowledgements

		Developers are co-authors to the extent to which they provide code
		which I implement in updates to hipng.

		Brian S. McCormick, P.E.
		U.S. Army Corps of Engineers
		- for the idea (and code) of allowing the lib to be linked with C code

		Stanley Sawyer
		Department of Mathematics
		Washington University
		St.Louis, MO 63130
		- for locating and explaining several serious bugs (see the bug report file)
		  and for providing code ideas to correct many of them.
/*

/************************************************************************
	See the file "doc.html" for the documentation.
*************************************************************************/

#include <setjmp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "png.h"
#include "hipng.h"

// for msg box
const	int	msg_info  = 0;
const	int	msg_error = 1;

//	Forward References
// static here means that the name is local to this file
static  BOOL	check_integrity_of_png_input(const HIPNG *pi);
static	BOOL	CreateRowPtrArray (const HIPNG_DIB *ps, png_bytepp *rows, PBYTE pixels);
static  BOOL	DIBValid (const HIPNG_DIB *ps);
static	char *  GetPngFilename (void);
static  BOOL	Handle16bpp (const HIPNG_DIB *ps, PBYTE *pPngPixels);
static  BOOL	Handle24bpp (const HIPNG_DIB *ps, PBYTE *pPngPixels);
static  BOOL	Handle32bpp (const HIPNG_DIB *ps, PBYTE *pPngPixels);
static  void	HiPngMsgBox	(int flag, char *szFormat, ...);
static  int		MaskToLShift (DWORD dwMask);
static  int		MaskToRShift (DWORD dwMask);

//---------------------------------------------------------------------------
//	If you already have a DIB, you can send it to this routine, and it will
//	be saved as a png file.
//	There are some restrictions on what DIBs are allowed. See the doc.

//	If this routine returns FALSE, the file wasn't created,
//	either because there was an error, or because the user cancelled.
//	If it returns TRUE, the file was created.

BOOL write_dib_to_png (const HIPNG_DIB *ps, CFile & file)
{
	HIPNG	hipng;
	int		num_colors;
	png_colorp	palettep = NULL;	// pointer to png palette, if any
	char	format[] = "Bit depth of %d is invalid\nfor color type %d.";
	PBYTE	pp		= NULL;	// byte pointer to png palette, if any
	PBYTE	pPngPixels	= NULL;	// pointer to new block of pixel bits
	PBYTE	pImage	= NULL;	// local pointer to pixel bits

	BITMAPINFOHEADER *pbmih = (BITMAPINFOHEADER *) ps->hbmi;

	if (!DIBValid (ps))
		return FALSE;

	// Set some values and do some err checking while we're at it
	int bc = pbmih->biBitCount;
	switch (ps->color_type)
	{
	case PNG_COLOR_TYPE_GRAY:
		if ((bc !=  1) && (bc !=  2) && (bc !=  4) &&
			(bc !=  8) && (bc != 16))
		{
			HiPngMsgBox (msg_error, format, bc, ps->color_type);
			return FALSE;
		}
		hipng.bit_depth	= pbmih->biBitCount;
		num_colors = 0;
		palettep = NULL;
		pImage = ps->pixels;
		break;
	case PNG_COLOR_TYPE_PALETTE:
	{
		if (	(bc != 1) && (bc != 2) &&
				(bc != 4) && (bc != 8))
		{
			HiPngMsgBox (msg_error, format, bc, ps->color_type);
			return FALSE;
		}
		if ((pbmih->biClrUsed < 0) || (pbmih->biClrUsed > (unsigned int) (1 << bc)))
		{
			HiPngMsgBox (msg_error, "Invalid biClrUsed field value: %d",
				pbmih->biClrUsed);
			return FALSE;
		}
		if (pbmih->biClrUsed == 0)
			num_colors = 1 << bc;
		else
			num_colors = pbmih->biClrUsed;

		// must convert from RGBQUADs to png_color's
		PBYTE	quad = (PBYTE) ps->hbmi->bmiColors;	// point to M$ palette
		palettep =  (png_colorp) new BYTE [3*num_colors]; // create png palette
		if (palettep == NULL)
		{
			HiPngMsgBox (msg_error, "Couldn't allocate enough memory");
			return FALSE;
		}
		pp = (BYTE *) palettep;
		// copy M$ palette to png palette
		// M$ stores colors as BRG, but we need RGB
		if ((num_colors > 0) && (num_colors <= (1 << bc)))
			for (int i = 0; i < num_colors; i++)
			{
				*(pp + 2) = *quad++;
				*(pp + 1) = *quad++;
				*pp = *quad++;
				*quad ++;	// skip reserved byte
				pp+=3;
			}
			else
			{
				HiPngMsgBox (msg_error,"Illegal num_colors: %d", num_colors);
				delete [] palettep;
				return FALSE;
			}
		hipng.bit_depth	= pbmih->biBitCount;
		pImage = ps->pixels;
		break;
	}
	case PNG_COLOR_TYPE_RGB:
	{
		switch (bc)
		{
		case 16:
			if (!Handle16bpp(ps, &pPngPixels))
				return FALSE;
			break;
		case 24:
			if (!Handle24bpp(ps, &pPngPixels))
				return FALSE;
			break;
		case 32:
			if (!Handle32bpp(ps, &pPngPixels))
				return FALSE;
			break;
		default:
			HiPngMsgBox (msg_error, format, bc, ps->color_type);
			return FALSE;
		}
		hipng.bit_depth	= 8;
		num_colors = 0;
		palettep = NULL;
		// Note: we need the extra var 'pPngPixels' in order to know whether to
		// 'delete' the block of memory later on.
		pImage = pPngPixels;
		break;
	}
	default:
		HiPngMsgBox (msg_error, "Invalid color type: %d", ps->color_type);
		return FALSE;
	}
	if (!CreateRowPtrArray (ps, &hipng.rows, pImage))
		return FALSE;

	// fill in the HIPNG struct
	//	NOTE: hipng.bit_depth and hipng.rows were filled in above
	hipng.width			= pbmih->biWidth;
	hipng.height		= pbmih->biHeight;
	hipng.color_type	= ps->color_type;
	hipng.interlaced	= ps->interlaced;
	hipng.num_colors	= num_colors;
	hipng.palettep		= palettep;
	hipng.gamma			= ps->gamma;
	hipng.num_text		= ps->num_text;
	hipng.pComment		= ps->pComment;
	hipng.current_time	= ps->current_time;
	hipng.transparent_palette	= ps->transparent_palette;
	hipng.num_transparent	= ps->num_transparent;
	hipng.RGBtransparent_value	= ps->RGBtransparent_value;
	hipng.row_callback_fn	= ps->row_callback_fn;
	hipng.image			= pImage;

	BOOL png_ret = write_standard_png (&hipng, file);

	delete	[] hipng.rows;
	if (palettep != NULL) delete [] palettep;
	if (pPngPixels != NULL) delete [] pPngPixels;
	return png_ret;
}
//---------------------------------------------------------------------------
static	BOOL	CreateRowPtrArray (const HIPNG_DIB *ps, png_bytepp *rows, PBYTE pImage)
{
	// The image bits are packed in rows
	// padded to a double word (32-bit) boundary
	// Make an array of ptrs to each row

	BITMAPINFOHEADER *pbmih = (BITMAPINFOHEADER *) ps->hbmi;
	 // Length = length of a row in bytes, including padding
	int BitsPerPixel = pbmih->biBitCount;
	if ((BitsPerPixel == 16) || (BitsPerPixel == 32))
		BitsPerPixel = 24; // we changed it in the HandleXXbpp() routine
	int Length = 4 * ((pbmih->biWidth * BitsPerPixel + 31)/32);
	png_uint_32 height = png_uint_32 (pbmih->biHeight);
	*rows = new BYTE *  [height];
	if ((*rows) == NULL)
	{
		HiPngMsgBox (msg_error, "Couldn't allocate enough memory");
		return FALSE;
	}
	// remember that bitmaps are stored bottom line first
	for (png_uint_32 y = 0; y < height; y++)
		(*rows) [y] = &pImage[(height - y -1) * Length];
	return TRUE;
}
//---------------------------------------------------------------------------
// convert the M$ formatted 16-bit image to a png style 24-bit image
// This routine does not handle compressed (color masked) bitmaps
//	 failure:	return FALSE
//	 success:	return TRUE, return pointer to png style image in pPngPixels
// Remember to "delete" the png-style image

BOOL Handle16bpp (const HIPNG_DIB *ps, PBYTE *pPngPixels)
{
	PBYTE	ppp;	// PtrPngPixels
	BITMAPINFOHEADER *pbmih = (BITMAPINFOHEADER *) ps->hbmi;

	// Make another block of pixels, so that what the calling routine sent
	// us remains unchanged.
	int width16; // length of a 16-bit / pixel row, in bytes, including padding
	if ((pbmih->biWidth % 2) == 0)	// if # of pixels is even
		width16 = 2 * pbmih->biWidth;
	else
		width16 = 2 * (pbmih->biWidth + 1);

	// width24 = length of a 24-bit / pixel row, in bytes, including padding
	int width24 = 4 * ((pbmih->biWidth * 24 + 31)/32);
	ppp = new BYTE  [width24*pbmih->biHeight];
	if (ppp == NULL)
	{
		HiPngMsgBox (msg_error, "Couldn't allocate enough memory");
		return FALSE;
	}
	// make sure the padding bits are zero.  I'm not sure it's necessary
	ZeroMemory (ppp, width24*pbmih->biHeight);
	PBYTE	pOld, pNew;

	// fill in the array of pointer to row
	switch (pbmih->biCompression)
	{
	case BI_RGB:
	{
		for (int y = 0; y < (int) pbmih->biHeight; y++)
		{
			pOld = ps->pixels + y * width16;	// point to next row of pixels
			pNew = ppp + y * width24;
			for (int i = 0; i < pbmih->biWidth; i++)
			{
				*pNew++ = (BYTE) (((0x7C00 & * (WORD *) pOld) >> 10) << 3);	// red
				*pNew++ = (BYTE) (((0x03E0 & * (WORD *) pOld) >>  5) << 3);	// green
				*pNew++ = (BYTE)  ((0x001F & * (WORD *) pOld)		 << 3);	// blue
				pOld += 2;
			}
		}
		break;
	}
	case BI_BITFIELDS:
	{
		int	iRShift[3], iLShift[3];
		DWORD	rm, gm, bm;

		int size = pbmih->biSize;
		// get the masks for the R, G and B bit fields
		rm = * (DWORD *) (((BYTE *) pbmih) + size);
		gm = * (DWORD *) (((BYTE *) pbmih) + size + 4);
		bm = * (DWORD *) (((BYTE *) pbmih) + size + 8);

		// find out how much to right- and left-shift the values
		iRShift[0] = MaskToRShift (rm);
		iRShift[1] = MaskToRShift (gm);
		iRShift[2] = MaskToRShift (bm);

		iLShift[0] = MaskToLShift (rm);
		iLShift[1] = MaskToLShift (gm);
		iLShift[2] = MaskToLShift (bm);
		
		for (int y = 0; y < (int) pbmih->biHeight; y++)
		{
			pOld = ps->pixels + y * width16;	// point to next row of pixels
			pNew = ppp + y * width24;
			for (int i = 0; i < pbmih->biWidth; i++)
			{
				*pNew++ = (BYTE) (((rm & * (WORD *) pOld) >> iRShift[0]) << iLShift[0]);	// red
				*pNew++ = (BYTE) (((gm & * (WORD *) pOld) >> iRShift[1]) << iLShift[1]);	// green
				*pNew++ = (BYTE) (((bm & * (WORD *) pOld) >> iRShift[2]) << iLShift[2]);	// blue
				pOld += 2;
			}
		}
		break;
	}
	default:
		HiPngMsgBox (msg_error, "Invalid DIB Compression Type: %d.",
			pbmih->biCompression);
		return FALSE;
	}
	*pPngPixels = ppp;
	return TRUE;
}
//---------------------------------------------------------------------------
// Convert the M$ formatted 24-bit image to a png style 24-bit image
//	 failure:	return FALSE
//	 success:	return TRUE, return pointer to png style image in pPngPixels
// Remember to "delete" the png-style image

BOOL Handle24bpp (const HIPNG_DIB *ps, PBYTE *pPngPixels)
{
	PBYTE	ppp;	// PtrPngPixels
	BITMAPINFOHEADER *pbmih = (BITMAPINFOHEADER *) ps->hbmi;

	// M$ stores RGB values as BGR, so we must exchange the 1st + 3rd channel
	// Make another block of pixels, so that what the calling routine sent
	// us remains unchanged.

	 // Length = length of a row in bytes, including padding
	int Length = 4 * ((pbmih->biWidth * 24 + 31)/32);
	ppp = new BYTE  [Length*pbmih->biHeight];
	if (ppp == NULL)
	{
		HiPngMsgBox (msg_error, "Couldn't allocate enough memory");
		return FALSE;
	}
	// make sure the padding bits are zero.  I'm not sure it's necessary
	ZeroMemory (ppp, Length*pbmih->biHeight);
	PBYTE	pOld, pNew;
	// fill in the array of pointer to row
	for (int y = 0; y < (int) pbmih->biHeight; y++)
	{
		pOld = ps->pixels + y * Length;	// point to next row of pixels
		pNew = ppp + y * Length;
		for (int i = 0; i < pbmih->biWidth; i++)
		{
			*pNew++ = *(pOld + 2);
			*pNew++ = *(pOld + 1);
			*pNew++ = *pOld;
			 pOld += 3;
		}
	}
	*pPngPixels = ppp;
	return TRUE;
}
//---------------------------------------------------------------------------
// convert the M$ formatted 32-bit image to a png style 24-bit image
// This routine does not handle compressed (color masked) bitmaps
//	 failure:	return FALSE
//	 success:	return TRUE, return pointer to png style image in pPngPixels
// Remember to "delete" the png-style image

BOOL Handle32bpp (const HIPNG_DIB *ps, PBYTE *pPngPixels)
{
	PBYTE	ppp;	// PtrPngPixels
	BITMAPINFOHEADER *pbmih = (BITMAPINFOHEADER *) ps->hbmi;
	// Make another block of pixels, so that what the calling routine sent
	// us remains unchanged.
	int width32 = 4 * pbmih->biWidth;	// # of bytes in a row of 32-bit M$ pixels

	// width24 = length of a 24-bit / pixel row, in bytes, including padding
	int width24 = 4 * ((pbmih->biWidth * 24 + 31)/32);
	ppp = new BYTE  [width24*pbmih->biHeight];
	if (ppp == NULL)
	{
		HiPngMsgBox (msg_error, "Couldn't allocate enough memory");
		return FALSE;
	}
	// make sure the padding bits are zero.  I'm not sure it's necessary
	ZeroMemory (ppp, width24*pbmih->biHeight);
	PBYTE	pOld, pNew;

	// fill in the array of pointer to row
	// remember that bitmaps are stored bottom line first
	switch (pbmih->biCompression)
	{
	case BI_RGB:
	{
		for (int y = 0; y < (int) pbmih->biHeight; y++)
		{
			pOld = ps->pixels + y * width32;	// point to next row of pixels
			pNew = ppp + y * width24;
			for (int i = 0; i < pbmih->biWidth; i++)
			{
				*pNew++ = (BYTE) ((0x00FF0000 & * (DWORD *) pOld) >> 16);	// red
				*pNew++ = (BYTE) ((0x0000FF00 & * (DWORD *) pOld) >>  8);	// green
				*pNew++ = (BYTE)  (0x000000FF & * (DWORD *) pOld);			// blue
				pOld += 4;
			}
		}
		break;
	}
	case BI_BITFIELDS:
	{
		int	iRShift[3], iLShift[3];
		DWORD	rm, gm, bm;

		int size = pbmih->biSize;
		rm = * (DWORD *) (((BYTE *) pbmih) + size);
		gm = * (DWORD *) (((BYTE *) pbmih) + size + 4);
		bm = * (DWORD *) (((BYTE *) pbmih) + size + 8);

		iRShift[0] = MaskToRShift (rm);
		iRShift[1] = MaskToRShift (gm);
		iRShift[2] = MaskToRShift (bm);

		iLShift[0] = MaskToLShift (rm);
		iLShift[1] = MaskToLShift (gm);
		iLShift[2] = MaskToLShift (bm);
		
		for (int y = 0; y < (int) pbmih->biHeight; y++)
		{
			pOld = ps->pixels + y * width32;	// point to next row of pixels
			pNew = ppp + y * width24;
			for (int i = 0; i < pbmih->biWidth; i++)
			{
				*pNew++ = (BYTE) (((rm & * (DWORD *) pOld) >> iRShift[0]) << iLShift[0]);	// red
				*pNew++ = (BYTE) (((gm & * (DWORD *) pOld) >> iRShift[1]) << iLShift[1]);	// green
				*pNew++ = (BYTE) (((bm & * (DWORD *) pOld) >> iRShift[2]) << iLShift[2]);	// blue
				pOld += 4;
			}
		}
		break;
	}
	default:
		HiPngMsgBox (msg_error, "Invalid DIB Compression Type: %d.",
			pbmih->biCompression);
		return FALSE;
	}
	*pPngPixels = ppp;
	return TRUE;
}
//---------------------------------------------------------------------------
// Do some checking here which isn't done automatically in the main routine
BOOL	DIBValid (const HIPNG_DIB *ps)
{
	BITMAPINFOHEADER *pbmih = (BITMAPINFOHEADER *) ps->hbmi;
	if (pbmih->biSize == sizeof (BITMAPCOREHEADER))
	{
		HiPngMsgBox (msg_error, 
			"DIB has BITMAPCOREHEADER.\n\rUnsupported DIB type.");
		return FALSE;
	}
	// At this point, I would like to allow a V5 BITMAPINFOHEADER also,
	// as I think the code works for it, but I don't know its size,
	// so I can't test for it.
	// And, since I think the V5 header is rarely, if ever, used,
	// including the following check is better than leaving it out.
	if ((pbmih->biSize != sizeof (BITMAPINFOHEADER)) &&
		(pbmih->biSize != sizeof (BITMAPV4HEADER)))
	{
		HiPngMsgBox (msg_error, "Invalid DIB BITMAPINFOHEADER");
		return FALSE;
	}
	if ((pbmih->biCompression == BI_RLE4) ||
		(pbmih->biCompression == BI_RLE8))
	{
		HiPngMsgBox (msg_error, "DIB Compression Type: %d, not supported.",
			pbmih->biCompression);
		return FALSE;
	}
	if ((ps->num_transparent < 0) || (ps->num_transparent > 256))
	{
		HiPngMsgBox (msg_error,
			"Illegal # of transparent entries in palette: %d.",
			ps->num_transparent);
		return FALSE;
	}

	return TRUE;
}
//---------------------------------------------------------------------------
//	There are a lot of params that could/should be handled, but aren't

//	If this routine returns FALSE, the file wasn't created,
//	either because there was an error, or because the user cancelled.
//	If it returns TRUE, the file was created.



extern "C" void read_fn(png_struct * pn, unsigned char * buffer, unsigned int bytestoread)
{
	CFile * file = (CFile*)(pn->io_ptr);
	file->Read(buffer,bytestoread);
}

extern "C" void write_fn(png_struct * pn, unsigned char * buffer, unsigned int bytestoread)
{
	CFile * file = (CFile*)(pn->io_ptr);
	file->Write(buffer,bytestoread);
}

extern "C" void flush_fn(png_struct * pn)
{
	return;
}


BOOL write_standard_png (const HIPNG *pi, CFile & file)
{

	png_structp	png_ptr;
	png_infop	info_ptr;
	unsigned int	sig_read = 0;
	int		interlace_type;

	// Start calling libpng routines
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
		(png_voidp) NULL, (png_error_ptr) NULL,
		(png_error_ptr) NULL);	// use default png error handlers

	if (png_ptr == NULL)
	{
		return FALSE;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL)
	{
		png_destroy_write_struct(&png_ptr,  (png_infopp)NULL);
		HiPngMsgBox (msg_error, "Pnglib couldn't create an info structure.");
		return FALSE;
	}
	// Set error handling.
	if (setjmp (png_ptr->jmpbuf))
	{
		// setjmp() saves "the environment at this point" into
		// the struct png_ptr->jmpbuf, and then returns FALSE.
		// Now, if an error occurs in the png library, it will
		// jump back here with a non-zero (TRUE) return value,
		// and the following code will be executed.

		// get here when png lib detects an error
		;
		png_destroy_write_struct(&png_ptr, &info_ptr);
		HiPngMsgBox (msg_error, "Pnglib error [from setjmp()].");
		return FALSE;
	}

//	// set up the output control using standard C streams
//	png_init_io(png_ptr, file);
	png_set_write_fn(png_ptr, &file, write_fn, flush_fn);

	// Set the callback function, if there is one
	if (pi->row_callback_fn != NULL)
		png_set_write_status_fn(png_ptr, pi->row_callback_fn);

	// Set the image information
	if (pi->interlaced)
			interlace_type = PNG_INTERLACE_ADAM7;
	else	interlace_type = PNG_INTERLACE_NONE;
	png_set_IHDR(png_ptr, info_ptr, pi->width, pi->height, pi->bit_depth,
		pi->color_type, interlace_type,
		// the params below have required values
		PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	// set the palette if there is one
	if ((pi->num_colors > 0) &&
		(pi->color_type != PNG_COLOR_TYPE_GRAY) &&
		(pi->color_type != PNG_COLOR_TYPE_GRAY_ALPHA))
			png_set_PLTE(png_ptr, info_ptr, pi->palettep, pi->num_colors);

	// Handle gamma value
	if (pi->gamma > 0.0)
		png_set_gAMA(png_ptr, info_ptr, pi->gamma);
	// Handle comments
	if (pi->num_text > 0)
		png_set_text(png_ptr, info_ptr, pi->pComment, pi->num_text);
	//	Handle date/time
	if (pi->current_time)
	{				// put file creation time in the file
		time_t	ltime;		// local time
		struct	tm	*gmt;	// Greenwich Mean Time
		png_time	ttime;	// png format

		time (&ltime);	// get the local time
		gmt = gmtime (&ltime);	// convert to gmt
		png_convert_from_struct_tm (&ttime, gmt);  // convert to png format
		png_set_tIME (png_ptr, info_ptr, &ttime);
	}
	// Handle transparency
	if ((pi->RGBtransparent_value != NULL) ||
		((pi->num_transparent > 0 ) && (pi->transparent_palette != NULL)))
			png_set_tRNS(png_ptr, info_ptr, pi->transparent_palette,
				pi->num_transparent, pi->RGBtransparent_value);

	png_write_info(png_ptr, info_ptr);	// write file header info

	// finally, write out the image
	if (pi->rows != NULL)
	{	// The caller is suppying an array of rows
		int number_passes;
		if (pi->interlaced)
				number_passes = png_set_interlace_handling(png_ptr);
		else	number_passes = 1;
		for (int pass = 0; pass < number_passes; pass++)
		{
			PBYTE bp;
			for (png_uint_32 y = 0; y < pi->height; y++)
			{
				bp = *(pi->rows + y);
				png_write_row(png_ptr, bp);
			}
		}
	}
	else
	{	// we must make our own array of row pointers
		png_bytepp ppRows = new png_bytep [pi->height];
		if (ppRows == NULL)
		{
			HiPngMsgBox (msg_error, "Couldn't allocate enough memory");
			png_destroy_write_struct (&png_ptr, &info_ptr);
			;
			return FALSE;
		}
		// fill in the array of pointer to row
		for (png_uint_32 y = 0; y < pi->height; y++)
			ppRows [y] = pi->image + y * pi->width;

		png_write_image (png_ptr, ppRows);
		delete ppRows;
	};
	png_write_end (png_ptr, info_ptr);
	png_destroy_write_struct (&png_ptr, &info_ptr);
	;
	return TRUE;	// success
}
//---------------------------------------------------------------------------

BOOL check_integrity_of_png_input(const HIPNG *pi)
{
//	These tests are NOT exhaustive!

	char	format[] = "Bit depth of %d is invalid\nfor color type %d";

	if ((pi->width <1 ) || (pi->height < 1))
	{
		HiPngMsgBox (msg_error, "Invalid PNG image dimension.\n \
			width: %d\nHeight: %d", pi->width, pi->height);
		return FALSE;
	}
	if ((pi->bit_depth < 1) || (pi->bit_depth > 16))
	{
		HiPngMsgBox (msg_error, "Invalid PNG bit depth.");
		return FALSE;
	}
	switch (pi->color_type)
	{
	case PNG_COLOR_TYPE_GRAY:
		if (	(pi->bit_depth !=  1) &&
			(pi->bit_depth !=  2) &&
			(pi->bit_depth !=  4) &&
			(pi->bit_depth !=  8) &&
			(pi->bit_depth != 16))
		{
			HiPngMsgBox (msg_error, format, pi->bit_depth, pi->color_type);
			return FALSE;
		}
		break;
	case PNG_COLOR_TYPE_PALETTE:
		if (	(pi->bit_depth != 1) &&
			(pi->bit_depth != 2) &&
			(pi->bit_depth != 4) &&
			(pi->bit_depth != 8))
		{
			HiPngMsgBox (msg_error, format, pi->bit_depth, pi->color_type);
			return FALSE;
		}
		break;
	case PNG_COLOR_TYPE_GRAY_ALPHA:
	case PNG_COLOR_TYPE_RGB:
	case PNG_COLOR_TYPE_RGB_ALPHA:
		if (	(pi->bit_depth != 8) &&
			(pi->bit_depth != 16))
		{
			HiPngMsgBox (msg_error, format, pi->bit_depth, pi->color_type);
			return FALSE;
		}
		break;
	default:
		HiPngMsgBox (msg_error, "Invalid PNG color type %d.", pi->color_type);
		return FALSE;
	}
	if ((pi->num_colors < 0) || (pi->num_colors > 256))
	{
		HiPngMsgBox (msg_error,
			"PNG error: Invalid number of colors in palette: %d",
			pi->num_colors);
		return FALSE;
	}
	return TRUE;	// seems ok
}


//----------------------------------------------------------------
int MaskToRShift (DWORD dwMask)
{
	int iShift;
	if (dwMask == 0)	return 0;
	for (iShift=0; !(dwMask & 1); iShift++)	dwMask >>= 1;
	return iShift;
}

int MaskToLShift (DWORD dwMask)
{
	int iShift;
	if (dwMask == 0)	return 0;
	while ( !(dwMask & 1))	dwMask >>= 1;
	for (iShift=0; dwMask & 1; iShift++)	dwMask >>= 1;
	return 8 - iShift;
}
//----------------------------------------------------------------

void HiPngMsgBox (int flag, char *szFormat, ...)
{
	return; //we don't allow this
}
