#define  ALDUSKEY        0x9AC6CDD7

#ifndef _WIN32

/* placeable metafile header */
typedef struct {
        DWORD   key;
        HANDLE  hmf;
        RECT    bbox;
        WORD    inch;
        DWORD   reserved;
        WORD    checksum;
}ALDUSMFHEADER;

#else
//
//placeable metafile data definitions 
//
#pragma pack(1)
typedef struct tagOLDRECT
{
    short   left;
    short   top;
    short   right;
    short   bottom;
} OLDRECT;
//
//placeable metafile header 
//
typedef struct {
        DWORD   key;
        WORD    hmf;
        OLDRECT bbox;
        WORD    inch;
        DWORD   reserved;
        WORD    checksum;
}ALDUSMFHEADER;
#pragma pack()
#endif


/* Logical Brush (or Pattern) */
#pragma pack(1)
typedef struct tagLOGBRUSH16
  {
    WORD        lbStyle;    // was UINT
    COLORREF    lbColor;
    short       lbHatch;    // was int
  } LOGBRUSH16;

typedef struct tagPOINT16
{
    short  x;
    short  y;
} POINT16;

/* Logical Pen */
typedef struct tagLOGPEN16
  {
    WORD        lopnStyle;  // was UINT
    POINT16     lopnWidth;
    COLORREF    lopnColor;
  } LOGPEN16;
#pragma pack()

/* global vars for main module */

/*#ifdef MAIN*/

//HANDLE hInst;
//HINSTANCE hInst;



HANDLE hMem;
//MFENUMPROC  lpprocEnumMF;

//flags

BOOL bValidFile    = FALSE;
BOOL bMetaInRam    = FALSE;
BOOL bAldusMeta    = FALSE;

BOOL bEnhMeta = FALSE;  // 32 enhanced code 
//metafile related vars

HMETAFILE             hMF;

METAHEADER            mfHeader;
ALDUSMFHEADER         aldusMFHeader;

LPSTR                 lpMFBits = NULL;    // 16 too?

#ifdef _WIN32
//
//structure of ptrs to global memory for emf header and 
//description string
//
typedef struct tagEHNMETAMEMPTR  {
        LPENHMETAHEADER lpEMFHdr;
        LPTSTR          lpDescStr;
        LPPALETTEENTRY  lpPal;
        WORD            palNumEntries;
} EHNMETAMEMPTR, *PEHNMETAMEMPTR, *LPEHNMETAMEMPTR;

HENHMETAFILE          hemf;
EHNMETAMEMPTR EmfPtr;

#endif // _WIN32

/* function prototypes */

/* WMFMETA.C */

BOOL   RenderPlaceableMeta(CFile&);
void   SetPlaceableExts(HDC, ALDUSMFHEADER, CRect);
VOID   SetClipMetaExts(HDC, METAFILEPICT, int);
BOOL   ProcessFile(const CString&);
BOOL   PlayMetaFileToDest(HDC, const CString&, CRect, BOOL);
void   GetMetaFileAndEnum(HDC, const CString&, BOOL);
int CALLBACK  MetaEnumProc(HDC, LPHANDLETABLE, LPMETARECORD, int, LPARAM);

BOOL   ProcessWMF(const CString& lpFileName); //32
void MetafileCleanup();

#ifdef _WIN32
BOOL   ProcessEMF(const CString& lpFileName);
int    CALLBACK EnhMetaFileEnumProc(HDC, LPHANDLETABLE, LPENHMETARECORD, int, LPARAM);
BOOL   GetEMFCoolStuff(void);
int    EnumMFIndirect(HDC hDC, LPHANDLETABLE lpHTable, 
                      LPMETARECORD lpMFR, 
                      LPENHMETARECORD lpEMFR, 
                      int nObj, LPARAM lpData);

#endif
