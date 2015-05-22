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

#define  ALDUSKEY        0x9AC6CDD7

#pragma pack(1)
typedef struct __OLDRECT{
   short   left;
   short   top;
   short   right;
   short   bottom;
} OLDRECT;

typedef struct __ALDUSMFHEADER{
   DWORD   key;
   WORD    hmf;
   OLDRECT bbox;
   WORD    inch;
   DWORD   reserved;
   WORD    checksum;
}ALDUSMFHEADER;
//#pragma pack()
//#pragma pack(1)

typedef struct __LOGBRUSH16{
   WORD        style; 
   COLORREF    color;
   short       hatch;  
} LOGBRUSH16;

typedef struct __POINT16{
   short  x;
   short  y;
} POINT16;

typedef struct __LOGPEN16{
   WORD        style;
   POINT16     width;
   COLORREF    color;
} LOGPEN16;

#pragma pack()


typedef struct __EHNMETAMEMPTR  {
   LPENHMETAHEADER EMFHdr;
   LPTSTR          descStr;
   LPPALETTEENTRY  pal;
   WORD            palNumEntries;
} EHNMETAMEMPTR, *PEHNMETAMEMPTR, *LPEHNMETAMEMPTR;

HANDLE         hMem;
BOOL           bValidFile    = FALSE;
BOOL           bMetaInRam    = FALSE;
BOOL           bAldusMeta    = FALSE;
BOOL           bEnhMeta      = FALSE;
HMETAFILE      hMF;
METAHEADER     mfHeader;
ALDUSMFHEADER  aldusMFHeader;
LPSTR          lpMFBits      = NULL;
HENHMETAFILE   hemf;
EHNMETAMEMPTR  EmfPtr;


BOOL           RenderPlaceableMeta(CFile&);
void           SetPlaceableExts(HDC, ALDUSMFHEADER, CRect);
VOID           SetClipMetaExts(HDC, METAFILEPICT, int);
BOOL           ProcessFile(const CString&);
BOOL           PlayMetaFileToDest(HDC, const CString&, CRect, BOOL);
void           GetMetaFileAndEnum(HDC, const CString&, BOOL);
int CALLBACK   MetaEnumProc(HDC, LPHANDLETABLE, LPMETARECORD, int, LPARAM);
BOOL           ProcessWMF(const CString& lpFileName); //32
void           MetafileCleanup();
int            EnumMFIndirect(HDC hDC, LPHANDLETABLE lpHTable, LPMETARECORD lpMFR,  LPENHMETARECORD lpEMFR, int nObj, LPARAM lpData);
