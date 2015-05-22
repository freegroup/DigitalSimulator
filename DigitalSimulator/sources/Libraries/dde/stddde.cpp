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


#include "stdafx.h"
#include "Application\Debug\LogManager.h"
#include "stddde.h"

//
// Constants
//

#define DDE_TIMEOUT     5000 // 5 seconds

//
// Format lists
//

static WORD SysFormatList[] = {
    CF_TEXT,
    NULL};

//
// Structure used to hold a clipboard id and its text name
//

typedef struct _CFTAGNAME {
    WORD wFmt;
    char* pszName;
} CFTAGNAME, FAR *PCFTAGNAME;

//
// Standard format name lookup table
//

CFTAGNAME CFNames[] = {
    CF_TEXT,        SZCF_TEXT,       
    CF_BITMAP,      SZCF_BITMAP,     
    CF_METAFILEPICT,SZCF_METAFILEPICT,
    CF_SYLK,        SZCF_SYLK,       
    CF_DIF,         SZCF_DIF,        
    CF_TIFF,        SZCF_TIFF,       
    CF_OEMTEXT,     SZCF_OEMTEXT,    
    CF_DIB,         SZCF_DIB,        
    CF_PALETTE,     SZCF_PALETTE,    
    CF_PENDATA,     SZCF_PENDATA,    
    CF_RIFF,        SZCF_RIFF,       
    CF_WAVE,        SZCF_WAVE,       
    NULL,           NULL
    };

////////////////////////////////////////////////////////////////////////////////////
//
// ********** The Barfy bit *********************
//
// We only support one server per app right now
// sooooo: here's the global we use to find it in the
// hateful DDE callback routine
// Let's see if I can get away with this
static CDDEServer* pTheServer = NULL;
////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
//
// CDDECountedObject

IMPLEMENT_DYNCREATE(CDDECountedObject, CObject);

//----------------------------------------------------------------------------
CDDECountedObject::CDDECountedObject(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_iRefCount = 0;
}

//----------------------------------------------------------------------------
CDDECountedObject::~CDDECountedObject(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(m_iRefCount == 0);
}

//----------------------------------------------------------------------------
int CDDECountedObject::AddRef(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(m_iRefCount < 1000); // sanity check
    return ++m_iRefCount;
}

//----------------------------------------------------------------------------
int CDDECountedObject::Release(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    int i = --m_iRefCount;
    ASSERT(m_iRefCount >= 0);
    if (m_iRefCount == 0) {
        delete this;
    }
    return i;
}

////////////////////////////////////////////////////////////////////////////////////
//
// CHSZ

IMPLEMENT_DYNCREATE(CHSZ, CObject);

//----------------------------------------------------------------------------
CHSZ::CHSZ(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_hsz = NULL;
    m_dwDDEInstance = 0;
}

//----------------------------------------------------------------------------
CHSZ::CHSZ(CDDEServer* pServer, const char* szName){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_dwDDEInstance = pServer->m_dwDDEInstance;
    m_hsz = ::DdeCreateStringHandle(m_dwDDEInstance,
                                    (char*)szName,
                                    CP_WINANSI);
    ASSERT(m_hsz);
}

//----------------------------------------------------------------------------
void CHSZ::Create(CDDEServer* pServer, const char* szName){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_hsz) {
        ::DdeFreeStringHandle(pServer->m_dwDDEInstance, m_hsz);
    }    
    m_dwDDEInstance = pServer->m_dwDDEInstance;
    m_hsz = ::DdeCreateStringHandle(m_dwDDEInstance,
                                    (char*)szName,
                                    CP_WINANSI);
    ASSERT(m_hsz);
}

//----------------------------------------------------------------------------
CHSZ::~CHSZ(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_hsz) {
        ::DdeFreeStringHandle(m_dwDDEInstance, m_hsz);
    }    
}

////////////////////////////////////////////////////////////////////////////////////
//
// CDDEItem

IMPLEMENT_DYNCREATE(CDDEItem, CObject);

//----------------------------------------------------------------------------
CDDEItem::CDDEItem(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_pTopic = NULL;
}

//----------------------------------------------------------------------------
CDDEItem::~CDDEItem(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CDDEItem::Create(const char* pszName){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_strName = pszName;
}

//----------------------------------------------------------------------------
BOOL CDDEItem::Request(UINT wFmt, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return FALSE;
}

//----------------------------------------------------------------------------
BOOL CDDEItem::Poke(UINT wFmt, void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return FALSE;
}

//----------------------------------------------------------------------------
BOOL CDDEItem::IsSupportedFormat(WORD wFormat){
//----------------------------------------------------------------------------
	PROC_TRACE;

    WORD* pFmt = GetFormatList();
    if (!pFmt) return FALSE;
    while(*pFmt) {
        if (*pFmt == wFormat) return TRUE;
        pFmt++;
    }
    return FALSE;
}

//----------------------------------------------------------------------------
BOOL CDDEItem::CanAdvise(UINT wFmt){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return IsSupportedFormat(wFmt);
}

//----------------------------------------------------------------------------
void CDDEItem::PostAdvise(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_pTopic == NULL) return;
    m_pTopic->PostAdvise(this);
}

////////////////////////////////////////////////////////////////////////////////////
//
// CDDEStringItem

IMPLEMENT_DYNCREATE(CDDEStringItem, CDDEItem);

//----------------------------------------------------------------------------
WORD* CDDEStringItem::GetFormatList(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return SysFormatList; // CF_TEXT
}

//----------------------------------------------------------------------------
BOOL CDDEStringItem::Request(UINT wFmt, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(wFmt == CF_TEXT);
    ASSERT(ppData);
    *ppData = (void*)(const char*)m_strData;
    *pdwSize = m_strData.GetLength() + 1; // allow for the null
    return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDDEStringItem::Poke(UINT wFmt, void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(wFmt == CF_TEXT);
    ASSERT(pData);
    m_strData = (char*)pData;
    OnPoke();
    return TRUE;
}

//----------------------------------------------------------------------------
void CDDEStringItem::SetData(const char* pszData){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(pszData);
    m_strData = pszData;
    PostAdvise();
}

////////////////////////////////////////////////////////////////////////////////////
//
// CDDEItemList

IMPLEMENT_DYNCREATE(CDDEItemList, CObList);

//----------------------------------------------------------------------------
CDDEItemList::CDDEItemList(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CDDEItemList::~CDDEItemList(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

////////////////////////////////////////////////////////////////////////////////////
//
// CDDETopic

IMPLEMENT_DYNCREATE(CDDETopic, CObject);

//----------------------------------------------------------------------------
CDDETopic::CDDETopic(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CDDETopic::~CDDETopic(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
void CDDETopic::Create(const char* pszName){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_strName = pszName;
}

//----------------------------------------------------------------------------
BOOL CDDETopic::AddItem(CDDEItem* pNewItem){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(pNewItem);

    // 
    // See if we already have this item
    //

    POSITION pos = m_ItemList.Find(pNewItem);
    if (pos) return TRUE; // already have it

    //
    // Add the new item
    //

    m_ItemList.AddTail(pNewItem);
    pNewItem->m_pTopic = this;

    return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDDETopic::Request(UINT wFmt, const char* pszItem, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we have this item
    //

    CDDEItem* pItem = FindItem(pszItem);
    if (!pItem) return FALSE;

    return pItem->Request(wFmt, ppData, pdwSize);
}

//----------------------------------------------------------------------------
BOOL CDDETopic::Poke(UINT wFmt, const char* pszItem,void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we have this item
    //

    CDDEItem* pItem = FindItem(pszItem);
    if (!pItem) return FALSE;

    return pItem->Poke(wFmt, pData, dwSize);
}

//----------------------------------------------------------------------------
BOOL CDDETopic::Exec(void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return FALSE;
}

//----------------------------------------------------------------------------
CDDEItem* CDDETopic::FindItem(const char* pszItem){
//----------------------------------------------------------------------------
	PROC_TRACE;

    POSITION pos = m_ItemList.GetHeadPosition();
    while (pos) {
        CDDEItem* pItem = m_ItemList.GetNext(pos);
        if (pItem->m_strName.CompareNoCase(pszItem) == 0) return pItem;
    }
    return NULL;
}

//----------------------------------------------------------------------------
BOOL CDDETopic::CanAdvise(UINT wFmt, const char* pszItem){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we have this item
    //

    CDDEItem* pItem = FindItem(pszItem);
    if (!pItem) return FALSE;

    return pItem->CanAdvise(wFmt);
}

//----------------------------------------------------------------------------
void CDDETopic::PostAdvise(CDDEItem* pItem){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(m_pServer);
    ASSERT(pItem);
    m_pServer->PostAdvise(this, pItem);
}

////////////////////////////////////////////////////////////////////////////////////
//
// CDDETopicList

IMPLEMENT_DYNCREATE(CDDETopicList, CObList);

//----------------------------------------------------------------------------
CDDETopicList::CDDETopicList(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CDDETopicList::~CDDETopicList(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

////////////////////////////////////////////////////////////////////////////////////
//
// CDDEConv

IMPLEMENT_DYNCREATE(CDDEConv, CDDECountedObject);

//----------------------------------------------------------------------------
CDDEConv::CDDEConv(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_pServer  = NULL;
    m_hConv    = NULL;
    m_hszTopic = NULL;
}

//----------------------------------------------------------------------------
CDDEConv::CDDEConv(CDDEServer* pServer){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_pServer  = pServer;
    m_hConv    = NULL;
    m_hszTopic = NULL;
}

//----------------------------------------------------------------------------
CDDEConv::CDDEConv(CDDEServer* pServer, HCONV hConv, HSZ hszTopic){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_pServer = pServer;
    m_hConv = hConv;
    m_hszTopic = hszTopic;
}

//----------------------------------------------------------------------------
CDDEConv::~CDDEConv(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    Terminate();
}

//----------------------------------------------------------------------------
BOOL CDDEConv::Terminate(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_hConv) {

        //
        // Terminate this conversation
        //

        ::DdeDisconnect(m_hConv);

        //
        // Tell the server
        //

        ASSERT(m_pServer);
        m_pServer->RemoveConversation(m_hConv);

        m_hConv = NULL;

        return TRUE;
    }

    return FALSE; // wasn't active
}

//----------------------------------------------------------------------------
BOOL CDDEConv::ConnectTo(const char* pszService, const char* pszTopic){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(pszService);
    ASSERT(pszTopic);
    ASSERT(m_pServer);
    ASSERT(!m_hConv);

    if(strlen(pszService)==0)
       return FALSE;
    if(strlen(pszTopic)==0)
       return FALSE;

    CHSZ hszService (m_pServer, pszService);
    CHSZ hszTopic(m_pServer, pszTopic);

    //
    // Try to connect
    //
    DWORD dwErr = 0;
    m_hConv = ::DdeConnect(m_pServer->m_dwDDEInstance,
                           hszService,
                           hszTopic,
                           NULL);

    if (!m_hConv) {
        dwErr = GetLastError();

    }

    if (!m_hConv) {
        m_pServer->Status("Failed to connect to %s|%s. Error %u",
                          (const char*) pszService,
                          (const char*) pszTopic,
                          dwErr);
        return FALSE;
    }

    //
    // Add this conversation to the server list
    //
    m_pServer->AddConversation(this);
    return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDDEConv::AdviseData(UINT wFmt, const char* pszTopic, const char* pszItem, void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return FALSE;
}

//----------------------------------------------------------------------------
BOOL CDDEConv::Request(const char* pszItem, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(m_pServer);
    ASSERT(pszItem);
    ASSERT(ppData);
    ASSERT(pdwSize);

    if(strlen(pszItem)==0)
       return FALSE;

    CHSZ hszItem (m_pServer, pszItem);
    HDDEDATA hData = ::DdeClientTransaction(NULL,
                                            0,
                                            m_hConv,
                                            hszItem,
                                            CF_TEXT,
                                            XTYP_REQUEST,
                                            DDE_TIMEOUT,
                                            NULL);

    if (!hData) {
        // Failed
        *pdwSize = 0;
        *ppData  = NULL;
        return FALSE;
    }

    //
    // Copy the result data
    //

    BYTE* pData = ::DdeAccessData(hData, pdwSize);
    ASSERT(*pdwSize);
    *ppData = new char[*pdwSize];
    ASSERT(*ppData);
    memcpy(*ppData, pData, *pdwSize);
    ::DdeUnaccessData(hData);

    return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDDEConv::Advise(const char* pszItem){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(m_pServer);
    ASSERT(pszItem);

    CHSZ hszItem (m_pServer, pszItem);
    HDDEDATA hData = ::DdeClientTransaction(NULL,
                                            0,
                                            m_hConv,
                                            hszItem,
                                            CF_TEXT,
                                            XTYP_ADVSTART,
                                            DDE_TIMEOUT,
                                            NULL);

    if (!hData) {
        // Failed
        return FALSE;
    }
    return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDDEConv::Exec(const char* pszCmd){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // Send the command
    //

    HDDEDATA hData = ::DdeClientTransaction((BYTE*)pszCmd,
                                            strlen(pszCmd) + 1,
                                            m_hConv,
                                            0,
                                            CF_TEXT,
                                            XTYP_EXECUTE,
                                            DDE_TIMEOUT,
                                            NULL);

    if (!hData) {
        // Failed
        return FALSE;
    }
    return TRUE;
}

//----------------------------------------------------------------------------
BOOL CDDEConv::Poke(UINT wFmt, const char* pszItem, void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // Send the command
    //

    CHSZ hszItem (m_pServer, pszItem);
    HDDEDATA hData = ::DdeClientTransaction((BYTE*)pData,
                                            dwSize,
                                            m_hConv,
                                            hszItem,
                                            wFmt,
                                            XTYP_POKE,
                                            DDE_TIMEOUT,
                                            NULL);

    if (!hData) {
        // Failed
        return FALSE;
    }
    return TRUE;
}

////////////////////////////////////////////////////////////////////////////////////
//
// CDDEConvList

IMPLEMENT_DYNCREATE(CDDEConvList, CObList);

//----------------------------------------------------------------------------
CDDEConvList::CDDEConvList(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

//----------------------------------------------------------------------------
CDDEConvList::~CDDEConvList(){
//----------------------------------------------------------------------------
	PROC_TRACE;

}

////////////////////////////////////////////////////////////////////////////////////
//
// Topics and items to support the 'system' topic

//
// Generic system topic items
//

IMPLEMENT_DYNCREATE(CDDESystemItem, CDDEItem);

//----------------------------------------------------------------------------
WORD* CDDESystemItem::GetFormatList(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    return SysFormatList;
}

//
// Specific system topic items
//

IMPLEMENT_DYNCREATE(CDDESystemItem_TopicList, CDDESystemItem);

//----------------------------------------------------------------------------
BOOL CDDESystemItem_TopicList::Request(UINT wFmt, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // 
    // Return the list of topics for this service
    //

    static CString strTopics;
    strTopics = "";
    ASSERT(m_pTopic);
    CDDEServer* pServer = m_pTopic->m_pServer;
    ASSERT(pServer);
    POSITION pos = pServer->m_TopicList.GetHeadPosition();
    int items = 0;
    while (pos) {
        
        CDDETopic* pTopic = pServer->m_TopicList.GetNext(pos);

        //
        // put in a tab delimiter unless this is the first item
        //

        if (items != 0) strTopics += SZ_TAB;

        //
        // Copy the string name of the item
        //

        strTopics += pTopic->m_strName;

        items++;
    }
    
    //
    // Set up the return info
    //

    *ppData = (void*)(const char*)strTopics;
    *pdwSize = strTopics.GetLength() + 1; // include room for the NULL
    return TRUE;
}

IMPLEMENT_DYNCREATE(CDDESystemItem_ItemList, CDDESystemItem);

//----------------------------------------------------------------------------
BOOL CDDESystemItem_ItemList::Request(UINT wFmt, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // 
    // Return the list of items in this topic
    //

    static CString strItems;
    strItems = "";
    ASSERT(m_pTopic);
    POSITION pos = m_pTopic->m_ItemList.GetHeadPosition();
    int items = 0;
    while (pos) {
        
        CDDEItem* pItem = m_pTopic->m_ItemList.GetNext(pos);

        //
        // put in a tab delimiter unless this is the first item
        //

        if (items != 0) strItems += SZ_TAB;

        //
        // Copy the string name of the item
        //

        strItems += pItem->m_strName;

        items++;
    }
    
    //
    // Set up the return info
    //

    *ppData = (void*)(const char*)strItems;
    *pdwSize = strItems.GetLength() + 1; // include romm for the NULL
    return TRUE;
}

IMPLEMENT_DYNCREATE(CDDESystemItem_FormatList, CDDESystemItem);

//----------------------------------------------------------------------------
BOOL CDDESystemItem_FormatList::Request(UINT wFmt, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    // 
    // Return the list of formats in this topic
    //

    static CString strFormats;
    strFormats = "";
    ASSERT(m_pTopic);
    POSITION pos = m_pTopic->m_ItemList.GetHeadPosition();
    int iFormats = 0;
    WORD wFmtList[100];
    while (pos) {
        
        CDDEItem* pItem = m_pTopic->m_ItemList.GetNext(pos);

        //
        // get the format list for this item
        //

        WORD* pItemFmts = pItem->GetFormatList();
        if (pItemFmts) {

            //
            // Add each format to the list if we don't have it already
            //

            while (*pItemFmts) {

                //
                // See if we have it
                //

                int i;
                for (i = 0; i < iFormats; i++) {
                    if (wFmtList[i] == *pItemFmts) break; // have it already
                }

                if (i == iFormats) {

                    //
                    // This is a new one
                    //

                    wFmtList[iFormats] = *pItemFmts;

                    //
                    // Add the string name to the list
                    //

                    //
                    // put in a tab delimiter unless this is the first item
                    //

                    if (iFormats != 0) strFormats += SZ_TAB;

                    //
                    // Copy the string name of the item
                    //

                    strFormats += ::GetFormatName(*pItemFmts);

                    iFormats++;
                }

                pItemFmts++;
            }
        }
    }

    //
    // Set up the return info
    //

    *ppData = (void*)(const char*)strFormats;
    *pdwSize = strFormats.GetLength() + 1; // include romm for the NULL
    return TRUE;
}

IMPLEMENT_DYNCREATE(CDDEServerSystemTopic, CDDETopic);

//----------------------------------------------------------------------------
BOOL CDDEServerSystemTopic::Request(UINT wFmt, const char* pszItem, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_pServer->Status("System topic request: %s", pszItem);
    return CDDETopic::Request(wFmt, pszItem, ppData, pdwSize);
}

////////////////////////////////////////////////////////////////////////////////////
//
// CDDEServer

IMPLEMENT_DYNCREATE(CDDEServer, CObject);

//----------------------------------------------------------------------------
CDDEServer::CDDEServer(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    m_bInitialized = FALSE;
    //m_strServiceName = AfxGetAppName();
    m_dwDDEInstance = 0;
}

//----------------------------------------------------------------------------
CDDEServer::~CDDEServer(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    Shutdown();
}

//----------------------------------------------------------------------------
void CDDEServer::Shutdown(){
//----------------------------------------------------------------------------
	PROC_TRACE;

    if (m_bInitialized) {

        //
        // Terminate all conversations
        //

        POSITION pos = m_ConvList.GetHeadPosition();
        while (pos) {

            CDDEConv* pConv = m_ConvList.GetNext(pos);
            ASSERT(pConv);
            pConv->Terminate();
        }

        //
        // Unregister the service name
        //

        ::DdeNameService(m_dwDDEInstance, 
                         m_hszServiceName,
                         NULL,
                         DNS_UNREGISTER);

        //
        // Release DDEML
        //

        ::DdeUninitialize(m_dwDDEInstance);

        m_bInitialized = FALSE;
    }
    pTheServer = NULL;
}

//----------------------------------------------------------------------------
BOOL CDDEServer::Create(const char* pszServiceName,DWORD dwFilterFlags/* = 0 */,DWORD* pdwDDEInst/* = NULL */){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // make sure we are alone in the world
    //

    if (pTheServer != NULL) {
        TRACE("Already got a server!\n");
        ASSERT(0);
        return FALSE;
    } else {
        pTheServer = this;
    }

    //
    // Make sure the application hasn't requested any filter options 
    // which will prevent us from working correctly.
    //

    dwFilterFlags &= !( CBF_FAIL_CONNECTIONS 
                      | CBF_SKIP_CONNECT_CONFIRMS
                      | CBF_SKIP_DISCONNECTS);

    //
    // Initialize DDEML.  Note that DDEML doesn't make any callbacks
    // during initialization so we don't need to worry about the
    // custom callback yet.
    //

    UINT uiResult;
    uiResult = ::DdeInitialize(&m_dwDDEInstance,
                               (PFNCALLBACK)&StdDDECallback,
                               dwFilterFlags,
                               0);

    if (uiResult != DMLERR_NO_ERROR) return FALSE;

    //
    // Return the DDE instance id if it was requested
    //

    if (pdwDDEInst) {
        *pdwDDEInst = m_dwDDEInstance;
    }

    //
    // Copy the service name and create a DDE name handle for it
    //

    m_strServiceName = pszServiceName;
    m_hszServiceName.Create(this, m_strServiceName);

    //
    // Add all the system topic to the service tree
    //

    //
    // Create a system topic
    //

    m_SystemTopic.Create(SZDDESYS_TOPIC);
    AddTopic(&m_SystemTopic);

    //
    // Create some system topic items
    //

    m_SystemItemTopics.Create(SZDDESYS_ITEM_TOPICS);
    m_SystemTopic.AddItem(&m_SystemItemTopics);

    m_SystemItemSysItems.Create(SZDDESYS_ITEM_SYSITEMS);
    m_SystemTopic.AddItem(&m_SystemItemSysItems);

    m_SystemItemItems.Create(SZDDE_ITEM_ITEMLIST);
    m_SystemTopic.AddItem(&m_SystemItemItems);

    m_SystemItemFormats.Create(SZDDESYS_ITEM_FORMATS);
    m_SystemTopic.AddItem(&m_SystemItemFormats);

    //
    // Register the name of our service
    //

    ::DdeNameService(m_dwDDEInstance, 
                     m_hszServiceName,
                     NULL,
                     DNS_REGISTER);

    m_bInitialized = TRUE;

    //
    // See if any derived class wants to add anything
    //

    return OnCreate();
}

//
// Callback function 
// Note: this is a static
//

//----------------------------------------------------------------------------
HDDEDATA CALLBACK CDDEServer::StdDDECallback(WORD wType,WORD wFmt, HCONV hConv, HSZ hsz1,HSZ hsz2,HDDEDATA hData, DWORD dwData1, DWORD dwData2){
//----------------------------------------------------------------------------
	PROC_TRACE;

    HDDEDATA hDdeData = NULL;
    UINT ui = 0;
    DWORD dwErr = 0;

    //
    // get a pointer to the server
    //

    CDDEServer* pServ = pTheServer; // BARF BARF BARF
    ASSERT(pServ);
    pServ->Status("Callback %4.4XH", wType);

    switch (wType) {
    case XTYP_CONNECT_CONFIRM:

        //
        // Add a new conversation to the list
        //

        pServ->Status("Connect to %s", (const char*)pServ->StringFromHsz(hsz1));
        pServ->AddConversation(hConv, hsz1);
        break;

    case XTYP_DISCONNECT:

        //
        // get some info on why it disconnected
        //

        CONVINFO ci;
        memset(&ci, 0, sizeof(ci));
        ci.cb = sizeof(ci);
        ui = ::DdeQueryConvInfo(hConv, wType, &ci);
        dwErr = pServ->GetLastError();

        //
        // Remove a conversation from the list
        //

        pServ->Status("Disconnect");
        pServ->RemoveConversation(hConv);
        break;

    case XTYP_WILDCONNECT:

        //
        // We only support wild connects to either a NULL service
        // name or to the name of our own service.
        //

        if ((hsz2 == NULL)
        || !::DdeCmpStringHandles(hsz2, pServ->m_hszServiceName)) {
            pServ->Status("Wild connect to %s", (const char*)pServ->StringFromHsz(hsz1));
            return pServ->DoWildConnect(hsz1);

        }
        break;

        //
        // For all other messages we see if we want them here
        // and if not, they get passed on to the user callback
        // if one is defined.
        //

    case XTYP_ADVSTART:
    case XTYP_CONNECT:
    case XTYP_EXECUTE:
    case XTYP_REQUEST:
    case XTYP_ADVREQ:
    case XTYP_ADVDATA:
    case XTYP_POKE:

        //
        // Try and process them here first.
        //

        if (pServ->DoCallback(wType,
                       wFmt,
                       hConv,
                       hsz1,
                       hsz2,
                       hData,
                       &hDdeData)) {

            return hDdeData;
        }

        //
        // Fall Through to allow the custom callback a chance
        //

    default:

        return pServ->CustomCallback(wType,  
                                      wFmt, 
                                      hConv, 
                                      hsz1, 
                                      hsz2, 
                                      hData,
                                      dwData1, 
                                      dwData2);
    }

    return (HDDEDATA) NULL;
}                                                                            

//----------------------------------------------------------------------------
CDDEConv* CDDEServer::AddConversation(HCONV hConv, HSZ hszTopic){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // create a new conversation object
    //

    CDDEConv* pConv = new CDDEConv(this, hConv, hszTopic);
    ASSERT(pConv);
    pConv->AddRef();

    //
    // Add it into the list
    //

    m_ConvList.AddTail(pConv);

    return pConv;
}

//----------------------------------------------------------------------------
CDDEConv* CDDEServer::AddConversation(CDDEConv* pNewConv){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(pNewConv);
    pNewConv->AddRef();

    //
    // Add it into the list
    //

    m_ConvList.AddTail(pNewConv);

    return pNewConv;
}

//----------------------------------------------------------------------------
BOOL CDDEServer::RemoveConversation(HCONV hConv){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // Try to find the conversation in the list
    //

    CDDEConv* pConv = NULL;
    POSITION pos = m_ConvList.GetHeadPosition();
    while (pos) {
        pConv = m_ConvList.GetNext(pos);
        if (pConv->m_hConv == hConv) {
            m_ConvList.RemoveAt(m_ConvList.Find(pConv));
            pConv->Release();
            return TRUE;
        }
    }

    //
    // Not in the list
    //

    return FALSE;
}

//----------------------------------------------------------------------------
HDDEDATA CDDEServer::DoWildConnect(HSZ hszTopic){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See how many topics we will be returning
    //

    int iTopics = 0;
    CString strTopic = "<null>";
    if (hszTopic == NULL) {

        //
        // Count all the topics we have
        //

        iTopics = m_TopicList.GetCount();

    } else {

        //
        // See if we have this topic in our list
        //

        strTopic = StringFromHsz(hszTopic);
        CDDETopic* pTopic = FindTopic(strTopic);
        if(pTopic) {
            iTopics++;
        }
    }

    //
    // If we have no match or no topics at all, just return
    // NULL now to refuse the connect
    //

    if (!iTopics) {
        Status("Wild connect to %s refused", (const char*)strTopic);
        return (HDDEDATA) NULL;
    }

    //
    // Allocate a chunk of DDE data big enough for all the HSZPAIRS
    // we'll be sending back plus space for a NULL entry on the end
    //

    HDDEDATA hData = ::DdeCreateDataHandle(m_dwDDEInstance,
                                  NULL,
                                  (iTopics + 1) * sizeof(HSZPAIR),
                                  0,
                                  NULL,
                                  0,
                                  0);

    //
    // Check we actually got it.
    //

    if (!hData) return (HDDEDATA) NULL;

    HSZPAIR* pHszPair = (PHSZPAIR) DdeAccessData(hData, NULL);

    //
    // Copy the topic data
    //

    if (hszTopic == NULL) {

        //
        // Copy all the topics we have (includes the system topic)
        //

        POSITION pos = m_TopicList.GetHeadPosition();
        while (pos) {

            CDDETopic* pTopic = m_TopicList.GetNext(pos);
            pHszPair->hszSvc = ::DdeCreateStringHandle(m_dwDDEInstance,
                                                       (char*)(const char*)m_strServiceName,
                                                       CP_WINANSI);
            pHszPair->hszTopic = ::DdeCreateStringHandle(m_dwDDEInstance,
                                                         (char*)(const char*)pTopic->m_strName,
                                                         CP_WINANSI);

            pHszPair++;
        }

    } else {

        //
        // Just copy the one topic asked for
        //

        pHszPair->hszSvc = m_hszServiceName;
        pHszPair->hszTopic = hszTopic;

        pHszPair++;

    }

    //
    // Put the terminator on the end
    //

    pHszPair->hszSvc = NULL;
    pHszPair->hszTopic = NULL;

    //
    // Finished with the data block
    //

    ::DdeUnaccessData(hData);

    //
    // Return the block handle
    //

    return hData;
}

//----------------------------------------------------------------------------
CDDETopic* CDDEServer::FindTopic(const char* pszTopic){
//----------------------------------------------------------------------------
	PROC_TRACE;

    POSITION pos = m_TopicList.GetHeadPosition();
    while (pos) {
        CDDETopic* pTopic = m_TopicList.GetNext(pos);
        if (pTopic->m_strName.CompareNoCase(pszTopic) == 0) return pTopic;
    }
    return NULL;
}

//----------------------------------------------------------------------------
BOOL CDDEServer::DoCallback(WORD wType,WORD wFmt,HCONV hConv,HSZ hszTopic,HSZ hszItem, HDDEDATA hData, HDDEDATA *phReturnData){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we know the topic
    //

    CString strTopic = StringFromHsz(hszTopic);

    //
    // See if this is an execute request
    //

    if (wType == XTYP_EXECUTE) {

        //
        // Call the exec function to process it
        //

        Status("Exec");
        DWORD dwLength = 0;
        void* pData = ::DdeAccessData(hData, &dwLength);
        BOOL b = Exec(strTopic, pData, dwLength);
        ::DdeUnaccessData(hData);
        
        if (b) {

            *phReturnData = (HDDEDATA) DDE_FACK;
            return FALSE;

        }

        //
        // Either no handler or it didn't get handled by the function
        //

        Status("Exec failed");
        *phReturnData = (HDDEDATA) DDE_FNOTPROCESSED;
        return FALSE;
    }

    //
    // See if this is a connect request. Accept it if it is.
    //

    if (wType == XTYP_CONNECT) {

        if (!FindTopic(strTopic)) return FALSE; // unknown topic
        *phReturnData = (HDDEDATA) TRUE;
        return TRUE;
    }

    //
    // For any other transaction we need to be sure this is an
    // item we support and in some cases, that the format requested
    // is supported for that item.
    //

    CString strItem = StringFromHsz(hszItem);

    //
    // Now just do whatever is required for each specific transaction
    //

    BOOL b = FALSE;
    DWORD dwLength = 0;
    void* pData = NULL;

    switch (wType) {
    case XTYP_ADVSTART:

        //
        // Confirm that the supported topic/item pair is OK and
        // that the format is supported

        if (!CanAdvise(wFmt, strTopic, strItem)) {

            Status("Can't advise on %s|%s", (const char*)strTopic, (const char*)strItem);
            return FALSE;
        }

        //
        // Start an advise request.  Topic/item and format are ok.
        //

        *phReturnData = (HDDEDATA) TRUE;
        break;

    case XTYP_POKE:

        //
        // Some data for one of our items. 
        //

        pData = ::DdeAccessData(hData, &dwLength);
        b = Poke(wFmt, strTopic, strItem, pData, dwLength);
        ::DdeUnaccessData(hData);

        if (!b) {

            //
            // Nobody took the data.
            // Maybe its not a supported item or format
            //

            Status("Poke %s|%s failed", (const char*)strTopic, (const char*)strItem); 
            return FALSE;

        }

        //
        // Data at the server has changed.  See if we
        // did this ourself (from a poke) or if it's from
        // someone else.  If it came from elsewhere then post
        // an advise notice of the change.
        //

        CONVINFO ci;
        ci.cb = sizeof(CONVINFO);
        if (::DdeQueryConvInfo(hConv, (DWORD)QID_SYNC, &ci)) {

            if (! (ci.wStatus & ST_ISSELF)) {

                //
                // It didn't come from us
                //

                ::DdePostAdvise(m_dwDDEInstance,
                              hszTopic,
                              hszItem);
            }
        }

        *phReturnData = (HDDEDATA) DDE_FACK; // say we took it
        break;

    case XTYP_ADVDATA:

        //
        // A server topic/item has changed value
        //

        pData = ::DdeAccessData(hData, &dwLength);
        b = AdviseData(wFmt, hConv, strTopic, strItem, pData, dwLength);
        ::DdeUnaccessData(hData);

        if (!b) {

            //
            // Nobody took the data.
            // Maybe its not of interrest
            //

            Status("AdviseData %s|%s failed", (const char*)strTopic, (const char*)strItem); 
            *phReturnData = (HDDEDATA) DDE_FNOTPROCESSED;

        } else {

            *phReturnData = (HDDEDATA) DDE_FACK; // say we took it
        }
        break;

    case XTYP_ADVREQ:
    case XTYP_REQUEST:

        //
        // Attempt to start an advise or get the data on a topic/item
        // See if we have a request function for this item or
        // a generic one for the topic
        //

        Status("Request %s|%s", (const char*)strTopic, (const char*)strItem); 
        dwLength = 0;
        if (!Request(wFmt, strTopic, strItem, &pData, &dwLength)) {

            // 
            // Nobody accepted the request
            // Maybe unsupported topic/item or bad format
            //

            Status("Request %s|%s failed", (const char*)strTopic, (const char*)strItem); 
            *phReturnData = NULL;
            return FALSE;

        }

        // 
        // There is some data so build a DDE data object to return
        //

        *phReturnData = ::DdeCreateDataHandle(m_dwDDEInstance,
                                              (unsigned char*)pData,
                                              dwLength,
                                              0,
                                              hszItem,
                                              wFmt,
                                              0);
 
        break;

    default:
        break;
    }

    //
    // Say we processed the transaction in some way
    //

    return TRUE;

}

//----------------------------------------------------------------------------
BOOL CDDEServer::AddTopic(CDDETopic* pNewTopic){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(pNewTopic);

    // 
    // See if we already have this topic
    //

    POSITION pos = m_TopicList.Find(pNewTopic);
    if (pos) return TRUE; // already have it

    //
    // Add the new topic
    //

    m_TopicList.AddTail(pNewTopic);
    pNewTopic->m_pServer = this;

    pNewTopic->AddItem(&m_SystemItemItems);
    pNewTopic->AddItem(&m_SystemItemFormats);

    return TRUE;
}

//----------------------------------------------------------------------------
CString CDDEServer::StringFromHsz(HSZ hsz){
//----------------------------------------------------------------------------
	PROC_TRACE;

    CString str = "<null>";

    //
    // Get the length of the string
    //

    DWORD dwLen = ::DdeQueryString(m_dwDDEInstance,
                                   hsz,
                                   NULL,
                                   0,
                                   CP_WINANSI);

    if (dwLen == 0) return str;

    //
    // get the text
    //

    char* pBuf = str.GetBufferSetLength(dwLen+1);
    ASSERT(pBuf);

    //
    // Get the string text
    //

    DWORD dw = ::DdeQueryString(m_dwDDEInstance,
                                 hsz,
                                 pBuf,
                                 dwLen+1,
                                 CP_WINANSI);

    //
    // Tidy up
    //

    str.ReleaseBuffer();

    if (dw == 0) str = "<error>";

    return str;
}

//----------------------------------------------------------------------------
BOOL CDDEServer::Request(UINT wFmt, const char* pszTopic, const char* pszItem, void** ppData, DWORD* pdwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we have a topic that matches
    //

    CDDETopic* pTopic = FindTopic(pszTopic);
    if (!pTopic) return FALSE;

    return pTopic->Request(wFmt, pszItem, ppData, pdwSize);
}

//----------------------------------------------------------------------------
BOOL CDDEServer::Poke(UINT wFmt, const char* pszTopic, const char* pszItem, void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we have a topic that matches
    //

    CDDETopic* pTopic = FindTopic(pszTopic);
    if (!pTopic) return FALSE;

    return pTopic->Poke(wFmt, pszItem, pData, dwSize);
}

//----------------------------------------------------------------------------
BOOL CDDEServer::Exec(const char* pszTopic, void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we have a topic that matches
    //

    CDDETopic* pTopic = FindTopic(pszTopic);
    if (!pTopic) return FALSE;

    return pTopic->Exec(pData, dwSize);
}

//----------------------------------------------------------------------------
BOOL CDDEServer::CanAdvise(UINT wFmt, const char* pszTopic, const char* pszItem){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we have a topic that matches
    //

    CDDETopic* pTopic = FindTopic(pszTopic);
    if (!pTopic) return FALSE;

    return pTopic->CanAdvise(wFmt, pszItem);
}

//----------------------------------------------------------------------------
void CDDEServer::PostAdvise(CDDETopic* pTopic, CDDEItem* pItem){
//----------------------------------------------------------------------------
	PROC_TRACE;

    ASSERT(pTopic);
    ASSERT(pItem);

    ::DdePostAdvise(m_dwDDEInstance,
                    ::DdeCreateStringHandle(m_dwDDEInstance,
                                            (char*)(const char*)pTopic->m_strName,
                                            CP_WINANSI),
                    ::DdeCreateStringHandle(m_dwDDEInstance,
                                            (char*)(const char*)pItem->m_strName,
                                            CP_WINANSI));

}

//----------------------------------------------------------------------------
CString GetFormatName(WORD wFmt){
//----------------------------------------------------------------------------

    CString strName = "";
    PCFTAGNAME pCTN;

    //
    // Try for a standard one first
    //

    pCTN = CFNames;
    while (pCTN->wFmt) {
        if (pCTN->wFmt == wFmt) {
            strName = pCTN->pszName;
            return strName;
        }
        pCTN++;
    }

    //
    // See if it's a registered one
    //

    char buf[256];
    if (::GetClipboardFormatName(wFmt, buf, sizeof(buf))) {
        strName = buf;
    }

    return strName;
}

//----------------------------------------------------------------------------
CDDEConv* CDDEServer::FindConversation(HCONV hConv){
//----------------------------------------------------------------------------
	PROC_TRACE;

    POSITION pos = m_ConvList.GetHeadPosition();
    while (pos) {

        CDDEConv* pConv = m_ConvList.GetNext(pos);
        ASSERT(pConv);
        if (pConv->m_hConv == hConv) return pConv;
    }
    return NULL;
}

//----------------------------------------------------------------------------
BOOL CDDEServer::AdviseData(UINT wFmt, HCONV hConv, const char* pszTopic, const char* pszItem, void* pData, DWORD dwSize){
//----------------------------------------------------------------------------
	PROC_TRACE;

    //
    // See if we know this conversation
    //

    CDDEConv* pConv = FindConversation(hConv);
    if (!pConv) 
       return FALSE;

    return pConv->AdviseData(wFmt, pszTopic, pszItem, pData, dwSize);
}

