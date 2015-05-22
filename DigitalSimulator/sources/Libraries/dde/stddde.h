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

// stddde.h

#ifndef _STDDDE_
#define _STDDDE_

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <ddeml.h>

//
// String names for standard Windows Clipboard formats
//

#define SZCF_TEXT           "TEXT"        
#define SZCF_BITMAP         "BITMAP"      
#define SZCF_METAFILEPICT   "METAFILEPICT"
#define SZCF_SYLK           "SYLK"        
#define SZCF_DIF            "DIF"         
#define SZCF_TIFF           "TIFF"        
#define SZCF_OEMTEXT        "OEMTEXT"     
#define SZCF_DIB            "DIB"         
#define SZCF_PALETTE        "PALETTE"     
#define SZCF_PENDATA        "PENDATA"     
#define SZCF_RIFF           "RIFF"     
#define SZCF_WAVE           "WAVE"     
#define SZCF_UNICODETEXT    "UNICODETEXT" 
#define SZCF_ENHMETAFILE    "ENHMETAFILE" 

//
// String names for some standard DDE strings not
// defined in DDEML.H
//

#define SZ_READY            "Ready"
#define SZ_BUSY             "Busy"
#define SZ_TAB              "\t"
#define SZ_RESULT           "Result"
#define SZ_PROTOCOLS        "Protocols"
#define SZ_EXECUTECONTROL1  "Execute Control 1"

//
// Helpers
//

static CString GetFormatName(WORD wFmt);

//
// Generic counted object class
//

class CDDECountedObject : public CObject
{
    DECLARE_DYNCREATE(CDDECountedObject);
public:
    CDDECountedObject();
    virtual ~CDDECountedObject();
    virtual int AddRef();
    virtual int Release();

private:
    int m_iRefCount;
};
    
//
// String handle class
//

class CDDEServer;

class CHSZ : public CObject
{
    DECLARE_DYNCREATE(CHSZ);
public:
    CHSZ();
    CHSZ(CDDEServer* pServer, const char* szName);
    virtual ~CHSZ();
    void Create(CDDEServer* pServer, const char* szName);
    operator HSZ() {return m_hsz;}

    HSZ m_hsz;

protected:
    DWORD m_dwDDEInstance;
};

//
// DDE item class
//

class CDDETopic;

class CDDEItem : public CObject
{
    DECLARE_DYNCREATE(CDDEItem);
public:
    CDDEItem();
    virtual ~CDDEItem();
    void Create(const char* pszName);
    void PostAdvise();
    virtual BOOL Request(UINT wFmt, void** ppData, DWORD* pdwSize);
    virtual BOOL Poke(UINT wFmt, void* pData, DWORD dwSize);
    virtual BOOL IsSupportedFormat(WORD wFormat);
    virtual WORD* GetFormatList()
        {return NULL;}
    virtual BOOL CanAdvise(UINT wFmt);

    CString m_strName;          // name of this item
    CDDETopic* m_pTopic;        // pointer to the topic it belongs to

protected:
};

//
// String item class
//

class CDDEStringItem : public CDDEItem
{
    DECLARE_DYNCREATE(CDDEStringItem);
public:
    virtual void OnPoke(){;}
    virtual void SetData(const char* pszData);
    virtual const char* GetData()
        {return (const char*)m_strData;}
    operator const char*()
        {return (const char*)m_strData;}

protected:
    virtual BOOL Request(UINT wFmt, void** ppData, DWORD* pdwSize);
    virtual BOOL Poke(UINT wFmt, void* pData, DWORD dwSize);
    virtual WORD* GetFormatList();

    CString m_strData;
};

//
// Item list class
//

class CDDEItemList : public CObList
{
    DECLARE_DYNCREATE(CDDEItemList);
public:
    CDDEItemList();
    virtual ~CDDEItemList();
    CDDEItem* GetNext(POSITION& rPosition) const
        {return (CDDEItem*)CObList::GetNext(rPosition);}

};

//
// Topic class
//

class CDDEServer;

class CDDETopic : public CObject
{
    DECLARE_DYNCREATE(CDDETopic);
public:
    CDDETopic();
    virtual ~CDDETopic();
    void Create(const char* pszName);
    BOOL AddItem(CDDEItem* pItem);
    virtual BOOL Request(UINT wFmt, const char* pszItem,
                         void** ppData, DWORD* pdwSize);
    virtual BOOL Poke(UINT wFmt, const char* pszItem,
                      void* pData, DWORD dwSize);
    virtual BOOL Exec(void* pData, DWORD dwSize);
    virtual CDDEItem* FindItem(const char* pszItem);
    virtual BOOL CanAdvise(UINT wFmt, const char* pszItem);
    void PostAdvise(CDDEItem* pItem);

    CString m_strName;          // name of this topic
    CDDEServer* m_pServer;      // ptr to the server which owns this topic
    CDDEItemList m_ItemList;    // List of items for this topic

protected:
};

//
// Topic list class
//

class CDDETopicList : public CObList
{
    DECLARE_DYNCREATE(CDDETopicList);
public:
    CDDETopicList();
    virtual ~CDDETopicList();
    CDDETopic* GetNext(POSITION& rPosition) const
        {return (CDDETopic*)CObList::GetNext(rPosition);}

protected:

};

//
// Conversation class
//

class CDDEConv : public CDDECountedObject
{
    DECLARE_DYNCREATE(CDDEConv);
public:
    CDDEConv();
    CDDEConv(CDDEServer* pServer);
    CDDEConv(CDDEServer* pServer, HCONV hConv, HSZ hszTopic);
    virtual ~CDDEConv();
    virtual BOOL ConnectTo(const char* pszService, const char* pszTopic);
    virtual BOOL Terminate();
    virtual BOOL AdviseData(UINT wFmt, const char* pszTopic, const char* pszItem,
                            void* pData, DWORD dwSize);
    virtual BOOL Request(const char* pszItem, void** ppData, DWORD* pdwSize);
    virtual BOOL Advise(const char* pszItem);
    virtual BOOL Exec(const char* pszCmd);
    virtual BOOL Poke(UINT wFmt, const char* pszItem, void* pData, DWORD dwSize);

    CDDEServer* m_pServer;
    HCONV   m_hConv;            // Conversation handle
    HSZ     m_hszTopic;         // Topic name

};

//
// Conversation list class
//

class CDDEConvList : public CObList
{
    DECLARE_DYNCREATE(CDDEConvList);
public:
    CDDEConvList();
    virtual ~CDDEConvList();
    CDDEConv* GetNext(POSITION& rPosition) const
        {return (CDDEConv*)CObList::GetNext(rPosition);}

    
protected:

};

//
// Topics and items used to support the 'system' topic in the server
//

class CDDESystemItem : public CDDEItem
{
    DECLARE_DYNCREATE(CDDESystemItem);
protected:
    virtual WORD* GetFormatList();
};

class CDDESystemItem_TopicList : public CDDESystemItem
{
    DECLARE_DYNCREATE(CDDESystemItem_TopicList);
protected:
    virtual BOOL Request(UINT wFmt, void** ppData, DWORD* pdwSize);
};

class CDDESystemItem_ItemList : public CDDESystemItem
{
    DECLARE_DYNCREATE(CDDESystemItem_ItemList);
protected:
    virtual BOOL Request(UINT wFmt, void** ppData, DWORD* pdwSize);
};

class CDDESystemItem_FormatList : public CDDESystemItem
{
    DECLARE_DYNCREATE(CDDESystemItem_FormatList);
protected:
    virtual BOOL Request(UINT wFmt, void** ppData, DWORD* pdwSize);
};

class CDDEServerSystemTopic : public CDDETopic
{
    DECLARE_DYNCREATE(CDDEServerSystemTopic);
protected:
    virtual BOOL Request(UINT wFmt, const char* pszItem,
                         void** ppData, DWORD* pdwSize);

};


//
// Server class
// Note: this class is for a server which supports only one service
//

class CDDEServer : public CObject
{
    DECLARE_DYNCREATE(CDDEServer);
public:
    CDDEServer();
    virtual ~CDDEServer();
    BOOL Create(const char* pszServiceName,
                DWORD dwFilterFlags = 0,
                DWORD* pdwDDEInst = NULL);
    void Shutdown();
    virtual BOOL OnCreate() {return TRUE;}
    virtual UINT GetLastError()
        {return ::DdeGetLastError(m_dwDDEInstance);}
    virtual HDDEDATA CustomCallback(WORD wType,
                                    WORD wFmt,
                                    HCONV hConv,
                                    HSZ hsz1,
                                    HSZ hsz2,
                                    HDDEDATA hData,
                                    DWORD dwData1,
                                    DWORD dwData2)
        {return NULL;}

    virtual BOOL Request(UINT wFmt, const char* pszTopic, const char* pszItem,
                         void** ppData, DWORD* pdwSize);
    virtual BOOL Poke(UINT wFmt, const char* pszTopic, const char* pszItem,
                      void* pData, DWORD dwSize);
    virtual BOOL AdviseData(UINT wFmt, HCONV hConv, const char* pszTopic, const char* pszItem,
                      void* pData, DWORD dwSize);
    virtual BOOL Exec(const char* pszTopic, void* pData, DWORD dwSize);
    virtual void Status(const char* pszFormat, ...) {;}
    virtual BOOL AddTopic(CDDETopic* pTopic);
    CString StringFromHsz(HSZ hsz);
    virtual BOOL CanAdvise(UINT wFmt, const char* pszTopic, const char* pszItem);
    void PostAdvise(CDDETopic* pTopic, CDDEItem* pItem);
    CDDEConv*  AddConversation(HCONV hConv, HSZ hszTopic);
    CDDEConv* AddConversation(CDDEConv* pNewConv);
    BOOL RemoveConversation(HCONV hConv);
    CDDEConv*  FindConversation(HCONV hConv);

    DWORD       m_dwDDEInstance;        // DDE Instance handle
    CDDETopicList m_TopicList;          // topic list

protected:
    BOOL        m_bInitialized;         // TRUE after DDE init complete
    CString     m_strServiceName;       // Service name
    CHSZ        m_hszServiceName;       // String handle for service name
    CDDEConvList m_ConvList;            // Conversation list

    HDDEDATA DoWildConnect(HSZ hszTopic);
    BOOL DoCallback(WORD wType,
                WORD wFmt,
                HCONV hConv,
                HSZ hsz1,
                HSZ hsz2,
                HDDEDATA hData,
                HDDEDATA *phReturnData);
    CDDETopic* FindTopic(const char* pszTopic);

private:
    static HDDEDATA CALLBACK StdDDECallback(WORD wType,
                                            WORD wFmt,
                                            HCONV hConv,
                                            HSZ hsz1,
                                            HSZ hsz2,
                                            HDDEDATA hData,
                                            DWORD dwData1,
                                            DWORD dwData2);

    CDDEServerSystemTopic m_SystemTopic;
    CDDESystemItem_TopicList m_SystemItemTopics;
    CDDESystemItem_ItemList m_SystemItemSysItems;
    CDDESystemItem_ItemList m_SystemItemItems;
    CDDESystemItem_FormatList m_SystemItemFormats;
};          


#endif // _STDDDE_

