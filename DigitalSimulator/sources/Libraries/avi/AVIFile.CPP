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

#ifdef WITH_AVI

#include "stdafx.h"

#define AVIIF_KEYFRAME  0x00000010L // this frame is a key frame.

#include <windows.h>
#include <windowsx.h>
#include <memory.h>
#include <mmsystem.h>
#include <vfw.h>
#include "AVIFile.h"


//----------------------------------------------------------------------------
CAVIFile::CAVIFile()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   m_isOpen = false;
   m_pfile        = NULL; 
   m_ps           = NULL;
   m_psCompressed = NULL; 
   m_frameRate    = 25; 
   m_lpbi         = NULL;
   m_currentImage = 0;
}


//----------------------------------------------------------------------------
CAVIFile::~CAVIFile()
//----------------------------------------------------------------------------
{
 	PROC_TRACE;

  Close();
}


//----------------------------------------------------------------------------
bool CAVIFile::Open(CBitmap& referenzBitmap)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   static char BASED_CODE szFilter[] = "Video AVI (*.avi)|*.avi||"; 

   CFileDialog m_File(FALSE, ".avi", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter); 

   if (m_File.DoModal() == IDOK) 
   { 
      CString file = m_File.GetFileName(); 

      Init(); 
      FileOpenWrite(&m_pfile,(char*) (LPCSTR)file); 
      m_lpbi = (LPBITMAPINFOHEADER)GlobalLock(MakeDib(referenzBitmap,8)); 

      CreateStream(m_pfile, &m_ps, m_frameRate,(unsigned long) m_lpbi->biSizeImage, 
                       (int) m_lpbi->biWidth, 
                       (int) m_lpbi->biHeight); 

      SetOptions(&m_ps, &m_psCompressed, m_lpbi); 
      GlobalUnlock(m_lpbi); 
      m_isOpen=true;
   }

   return m_isOpen;
}


//----------------------------------------------------------------------------
void CAVIFile::Close()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(!m_isOpen)
      return;

   // The end... 
   m_isOpen       = false;

   CloseStream(m_ps, m_psCompressed, NULL); 
   CloseFile(m_pfile); 
   Exit(); 
   m_pfile        = NULL; 
   m_ps           = NULL;
   m_psCompressed = NULL; 
   m_frameRate    = 25; 
   m_lpbi         = NULL;
   m_currentImage = 0;
}

//----------------------------------------------------------------------------
void CAVIFile::Add(CBitmap& image)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

   if(!m_isOpen)
      return;
   
   m_lpbi = (LPBITMAPINFOHEADER)GlobalLock(MakeDib(image,8)); 
   AddFrame(m_psCompressed, m_currentImage, m_lpbi); 
   GlobalUnlock(m_lpbi); 
   m_currentImage++;
}

//----------------------------------------------------------------------------
HANDLE  CAVIFile::MakeDib( HBITMAP hbitmap, UINT bits )
//----------------------------------------------------------------------------
{
	PROC_TRACE;

	HANDLE              hdib ;
	HDC                 hdc ;
	BITMAP              bitmap ;
	UINT                wLineLen ;
	DWORD               dwSize ;
	DWORD               wColSize ;
	LPBITMAPINFOHEADER  lpbi ;
	LPBYTE              lpBits ;
	
	GetObject(hbitmap,sizeof(BITMAP),&bitmap) ;

	//
	// DWORD align the width of the DIB
	// Figure out the size of the colour table
	// Calculate the size of the DIB
	//
	wLineLen = (bitmap.bmWidth*bits+31)/32 * 4;
	wColSize = sizeof(RGBQUAD)*((bits <= 8) ? 1<<bits : 0);
	dwSize = sizeof(BITMAPINFOHEADER) + wColSize +
		(DWORD)(UINT)wLineLen*(DWORD)(UINT)bitmap.bmHeight;

	//
	// Allocate room for a DIB and set the LPBI fields
	//
	hdib = GlobalAlloc(GHND,dwSize);
	if (!hdib)
		return hdib ;

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hdib) ;

	lpbi->biSize = sizeof(BITMAPINFOHEADER) ;
	lpbi->biWidth = bitmap.bmWidth ;
	lpbi->biHeight = bitmap.bmHeight ;
	lpbi->biPlanes = 1 ;
	lpbi->biBitCount = (WORD) bits ;
	lpbi->biCompression = BI_RGB ;
	lpbi->biSizeImage = dwSize - sizeof(BITMAPINFOHEADER) - wColSize ;
	lpbi->biXPelsPerMeter = 0 ;
	lpbi->biYPelsPerMeter = 0 ;
	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;
	lpbi->biClrImportant = 0 ;

	//
	// Get the bits from the bitmap and stuff them after the LPBI
	//
	lpBits = (LPBYTE)(lpbi+1)+wColSize ;

	hdc = CreateCompatibleDC(NULL) ;

	GetDIBits(hdc,hbitmap,0,bitmap.bmHeight,lpBits,(LPBITMAPINFO)lpbi, DIB_RGB_COLORS);

	// Fix this if GetDIBits messed it up....
	lpbi->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	DeleteDC(hdc) ;
	GlobalUnlock(hdib);

	return hdib ;
}

//----------------------------------------------------------------------------
BOOL CAVIFile::Init()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

        /* first let's make sure we are running on 1.1 */
        WORD wVer = HIWORD(VideoForWindowsVersion());
        if (wVer < 0x010a){
                 /* oops, we are too old, blow out of here */
                MessageBeep(MB_ICONHAND);
                MessageBox(NULL, "Sorry, Cant't init AVI File !", "Error", MB_OK|MB_ICONSTOP);
                return FALSE;
        }

        AVIFileInit();

        return TRUE;
}


//----------------------------------------------------------------------------
BOOL CAVIFile::FileOpenWrite(PAVIFILE * pfile,  char *filename)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

        HRESULT hr = AVIFileOpen(pfile,             // returned file pointer
                       filename,                            // file name
                       OF_WRITE | OF_CREATE,        // mode to open file with
                       NULL);                                           // use handler determined
                                                                                        // from file extension....
        if (hr != AVIERR_OK)
                return FALSE;

        return TRUE;
}

//----------------------------------------------------------------------------
BOOL CAVIFile::CreateStream(PAVIFILE pfile, 
                                          PAVISTREAM * ps, 
                                          int rate,                             // sample/second
                                          unsigned long buffersize,
                                          int rectwidth,
                                          int rectheight)
//----------------------------------------------------------------------------
{
	PROC_TRACE;


        AVISTREAMINFO strhdr;

        _fmemset(&strhdr, 0, sizeof(strhdr));
        strhdr.fccType                = streamtypeVIDEO;// stream type
        strhdr.fccHandler             = 0;
        strhdr.dwScale                = 1;
        strhdr.dwRate                 = rate;               // rate fps
        strhdr.dwSuggestedBufferSize  = buffersize;
        SetRect(&strhdr.rcFrame, 0, 0,              // rectangle for stream
            (int) rectwidth,
            (int) rectheight);

        // And create the stream;
        HRESULT hr = AVIFileCreateStream(pfile,             // file pointer
                                 ps,                // returned stream pointer
                                 &strhdr);          // stream header
        if (hr != AVIERR_OK) {
                return FALSE;
        }

        return TRUE;
}

//----------------------------------------------------------------------------
BOOL CAVIFile::SetOptions(PAVISTREAM * ps, PAVISTREAM * psCompressed, LPBITMAPINFOHEADER lpbi)
//----------------------------------------------------------------------------
{
 	PROC_TRACE;

        
        AVICOMPRESSOPTIONS opts;
        AVICOMPRESSOPTIONS FAR * aopts[1] = {&opts};

        _fmemset(&opts, 0, sizeof(opts));

        if (!AVISaveOptions(NULL, 0, 1, ps, (LPAVICOMPRESSOPTIONS FAR *) &aopts))
            return FALSE;

        HRESULT hr = AVIMakeCompressedStream(psCompressed, *ps, &opts, NULL);
        if (hr != AVIERR_OK) {
                return FALSE;
        }

        hr = AVIStreamSetFormat(*psCompressed, 0,
                               lpbi,                    // stream format
                               lpbi->biSize             // format size
                                   + lpbi->biClrUsed * sizeof(RGBQUAD)
                                   );
        if (hr != AVIERR_OK) {
        return FALSE;
        }

        return TRUE;
}


//----------------------------------------------------------------------------
BOOL CAVIFile::SetText(PAVIFILE pfile, PAVISTREAM psText, char *szText, int width, int height, int TextHeight)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

        // Fill in the stream header for the text stream....
        AVISTREAMINFO strhdr;
        DWORD dwTextFormat;
        // The text stream is in 60ths of a second....

        _fmemset(&strhdr, 0, sizeof(strhdr));
        strhdr.fccType                = streamtypeTEXT;
        strhdr.fccHandler             = mmioFOURCC('D', 'R', 'A', 'W');
        strhdr.dwScale                = 1;
        strhdr.dwRate                 = 60;
        strhdr.dwSuggestedBufferSize  = sizeof(szText);
        SetRect(&strhdr.rcFrame, 0, (int) height,
            (int) width, (int) height + TextHeight); // #define TEXT_HEIGHT 20

        // ....and create the stream.
        HRESULT hr = AVIFileCreateStream(pfile, &psText, &strhdr);
        if (hr != AVIERR_OK) {
                return FALSE;
        }

        dwTextFormat = sizeof(dwTextFormat);
        hr = AVIStreamSetFormat(psText, 0, &dwTextFormat, sizeof(dwTextFormat));
        if (hr != AVIERR_OK) {
                return FALSE;
        }

        return TRUE;
}


//----------------------------------------------------------------------------
BOOL CAVIFile::AddFrame(PAVISTREAM psCompressed, int time, LPBITMAPINFOHEADER lpbi)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

        HRESULT hr = AVIStreamWrite(psCompressed,       // stream pointer
                time,                                                                   // time of this frame
                1,                                                                              // number to write
                (LPBYTE) lpbi +                                                 // pointer to data
                        lpbi->biSize + 
                        lpbi->biClrUsed * sizeof(RGBQUAD),
                        lpbi->biSizeImage,                                      // size of this frame
                AVIIF_KEYFRAME,                                                 // flags....
                NULL,
                NULL);
        if (hr != AVIERR_OK)
                return FALSE;
        
        return TRUE;
}


//----------------------------------------------------------------------------
BOOL CAVIFile::AddText(PAVISTREAM psText, int time, char *szText)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

        int iLen = strlen(szText);

        HRESULT hr = AVIStreamWrite(psText,
                        time,
                        1,
                        szText,
                        iLen + 1,
                        AVIIF_KEYFRAME,
                        NULL,
                        NULL);
        if (hr != AVIERR_OK)
                return FALSE;

        return TRUE;
}


//----------------------------------------------------------------------------
BOOL CAVIFile::CloseStream(PAVISTREAM ps, PAVISTREAM psCompressed, PAVISTREAM psText)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

        if (ps)
                AVIStreamClose(ps);

        if (psCompressed)
                AVIStreamClose(psCompressed);

        if (psText)
                AVIStreamClose(psText);



        return TRUE;
}


//----------------------------------------------------------------------------
BOOL CAVIFile::CloseFile(PAVIFILE pfile)
//----------------------------------------------------------------------------
{
	PROC_TRACE;

        if (pfile)
                AVIFileClose(pfile);
        
        return TRUE;
}


//----------------------------------------------------------------------------
BOOL CAVIFile::Exit()
//----------------------------------------------------------------------------
{
	PROC_TRACE;

        AVIFileExit();

        return TRUE;
}


#endif