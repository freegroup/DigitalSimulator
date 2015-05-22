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

class CDib : public CObject{
   typedef CObject inherited ;
public:
    CDib();
    CDib(CDC* pDC, int nBt = 0, BOOL bCompr = FALSE, CPalette* = 0);
    virtual ~CDib();

    virtual BOOL      Read(CFile* pFile);
    virtual BOOL      Write(CFile* pFile);
    virtual BOOL      Display(CDC*, CPoint origin);
    virtual BOOL      Stretch(CDC*, CPoint origin, CSize size);
    virtual int       GetColorBits();
    virtual DWORD     GetLength();
    virtual CSize     GetSize();


    char              *m_lpBuf;   
    DWORD              m_dwLength; 
    int                m_nBits;    
    LPBITMAPFILEHEADER m_lpBMFH;
    LPBITMAPINFOHEADER m_lpBMIH;
    LPBITMAPINFO       m_lpBMI;
    LPSTR              m_lpData;    
    int				    nPaletteSize;       

private:
    virtual BOOL AllocateMemory(BOOL bRealloc = FALSE);
};