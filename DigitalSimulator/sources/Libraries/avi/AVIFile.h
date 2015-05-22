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
#ifdef  WITH_AVI

#include <vfw.h>

class CAVIFile
{
public:
   CAVIFile() ;
   ~CAVIFile();

   bool Open(CBitmap& referenzImage);
   void Close();
   void Add(CBitmap& image);

protected:

   long               m_currentImage;
   bool               m_isOpen;
   LPBITMAPINFOHEADER m_lpbi; 
   PAVIFILE           m_pfile; 
   PAVISTREAM         m_ps;
   PAVISTREAM         m_psCompressed; 
   int                m_frameRate; 

private:
   HANDLE  MakeDib( HBITMAP hbitmap, UINT bits );
   BOOL Init();
   BOOL FileOpenWrite(PAVIFILE * pfile, char *filename);
   BOOL CreateStream(PAVIFILE pfile,PAVISTREAM * ps, int rate,unsigned long buffersize, int rectwidth,   int rectheight);
   BOOL SetOptions(PAVISTREAM * ps,PAVISTREAM * psCompressed,LPBITMAPINFOHEADER lpbi);
   BOOL SetText(PAVIFILE pfile,PAVISTREAM psText,char *szText,int width,int height, int TextHeight);
   BOOL AddFrame(PAVISTREAM psCompressed,int time, LPBITMAPINFOHEADER lpbi);
   BOOL AddText(PAVISTREAM psText, int time, char *szText);
   BOOL CloseStream(PAVISTREAM ps, PAVISTREAM psCompressed, PAVISTREAM psText);
   BOOL CloseFile(PAVIFILE pfile);
   BOOL Exit();
};

#endif