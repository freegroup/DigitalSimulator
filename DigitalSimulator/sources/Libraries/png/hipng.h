/*
	Library of high-level routines to write a .png file
	Copywrite 1999 Alan Algustyniak
/*

/************************************************************************
	See the Doc.html file for necessary documentation.

changes:

June 1999 - Allow this file to be compiled by C as well as C++ compilers
	Idea and code from:
	Brian S. McCormick, P.E.
	U.S. Army Corps of Engineers
*************************************************************************/

#include	<windows.h>
#include	"png.h"


//  BOOL is defined to be an int, which, in win32, is always 32-bits


typedef	struct	typeHIPNG
{
	png_uint_32	width;		// of the image, in pixels
	png_uint_32	height;		//	"	"	"
	int			bit_depth;	// See documentation
	int			color_type;	// See documentation
	BOOL		interlaced;	// TRUE if you want the file interlaced
	int			num_colors;	// # of colors in the palette
					// Set to 0 if there is no palette
	png_colorp	palettep;	// pointer to the palette (if there is one)
	double		gamma;		// Set to < 0.0 if you don't know
	int			num_text;	// # of text entries
	png_textp	pComment;	// pntr to an array of ptrs to text
					// See documentation
	BOOL		current_time;	// put creation time (GMT) in the file
		// pointer to array of transparent entries for images with a palette
	png_bytep	transparent_palette;
	int		num_transparent;	// # of entries in the transparent_palette
		// transparent pixel for non-paletted images
	png_color_16p	RGBtransparent_value;
	png_bytepp	rows;		// See documentation
	void		(*row_callback_fn) (png_structp, png_uint_32, int);
				// Set = NULL if you don't have a routine
				// Set = address of your callback routine which will be
				// called after each row is written
				// ex: pi.row_callback_fn = &my_fn;
	png_byte	*image;		// See documentation
} HIPNG;


typedef	struct	typeHIPNGDIB
{
	char		*file_name;	// the filename (and path) to write to
					// NULL means:  Ask the user for the filename
	BITMAPINFO	*hbmi;		// pointer to the filled BITMAPINFO struct
					// this includes the palette (if the DIB has one)
	PBYTE		pixels;		// pointer to the pixel bits
	int			color_type;	// so the routine can tell gray-scale from color
	BOOL		interlaced;	// TRUE if you want the file interlaced
	double		gamma;		// Set to < 0.0 if you don't know
	int			num_text;	// # of text entries
	png_textp	pComment;	// pntr to an array of ptrs to text
					// See documentation
	BOOL		current_time;	// put creation time (GMT) in the file
		// pointer to array of transparent entries for images with a palette
	png_bytep	transparent_palette;
	int		num_transparent;	// # of entries in the transparent_palette
		// transparent pixel for non-paletted images
	png_color_16p	RGBtransparent_value;
	void		(*row_callback_fn) (png_structp, png_uint_32, int);
				// Set = NULL if you don't have a routine
				// Set = address of your callback routine which will be
				// called after each row is written
				// ex: pi.row_callback_fn = &my_fn;
} HIPNG_DIB;


//	Function Declarations
#ifdef __cplusplus
extern "C" {
#endif

BOOL	write_standard_png (const HIPNG *pi, CFile & file);
BOOL	write_dib_to_png (const HIPNG_DIB *pidib, CFile & file);

#ifdef __cplusplus
}
#endif
