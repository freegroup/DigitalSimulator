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


#if !defined(AFX_FILEFINDER_H__43F5DBE6_5341_11D4_937A_0050DABB534C__INCLUDED_)
#define AFX_FILEFINDER_H__43F5DBE6_5341_11D4_937A_0050DABB534C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////
// safe data access for data shared between threads
extern CRITICAL_SECTION g_findFileCritSection;
template <class T> T GET_SAFE( T a ) {EnterCriticalSection(&g_findFileCritSection); T z = a; LeaveCriticalSection(&g_findFileCritSection); return z;}
template <class T> void SET_SAFE( T & a , T b) {EnterCriticalSection(&g_findFileCritSection); a = b; LeaveCriticalSection(&g_findFileCritSection);}

struct searchStruct
{
	searchStruct()
	{
		m_bFindSingleFile = false;	
		m_bRecurse = true;
		m_bCancel = false;
		
		m_bSearchNetworkDrives = false;
		m_bSearchRemovableDrives = false;
		m_bSearchCDROMDrives = false;

		m_bOk = true;
		m_bDone = false;
	}

	// set by caller
	CString	m_csFindFile;
	CString	m_csRootFolder;		
	bool	m_bFindSingleFile;	
	bool	m_bRecurse;
	bool	m_bCancel;
	bool	m_bSearchNetworkDrives;
	bool	m_bSearchRemovableDrives;
	bool	m_bSearchCDROMDrives;

	// set by callee
	CStringArray	m_csaFoundFiles;
	bool	m_bOk;
	bool	m_bDone;

	CString	m_csCurFolder;
	CString m_csCurOperation;

};


class CFileFinder  
{
public:
	CFileFinder(searchStruct *pss);
	virtual ~CFileFinder();

	bool	FindFile();

protected:
	bool	GetSubDirs(CStringArray &dir_array, CString path);

	bool	GetLocalDriveRoots(CStringArray &csaDrives);

	bool	FindFileInFolder(const CStringArray &csaSearchFolders);

	searchStruct *m_pss;
};

#endif // !defined(AFX_FILEFINDER_H__43F5DBE6_5341_11D4_937A_0050DABB534C__INCLUDED_)
