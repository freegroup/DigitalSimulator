#include "stdafx.h"
#include "FileFinder.h"
#include <direct.h>
#include <fcntl.h>
#include <io.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CRITICAL_SECTION g_findFileCritSection;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileFinder::CFileFinder(searchStruct *p)
{
	PROC_TRACE;

	ASSERT(p);
	m_pss = p;
}

//////////////////////////////////////////////////////////////////////

CFileFinder::~CFileFinder()
{
	PROC_TRACE;


}

//////////////////////////////////////////////////////////////////////

bool	CFileFinder::FindFile()
{
	PROC_TRACE;

	if (m_pss==NULL)
	{
		return false;
	}

	bool ok = true;

	// build the search folder list
	CStringArray csaSearchFolders;
	csaSearchFolders.SetSize(0,100);

	CString csSearchFolder = GET_SAFE(m_pss->m_csRootFolder);
	if (csSearchFolder.IsEmpty())
	{
		// this means use the roots of all drives

		CStringArray csaLocalDriveRoots;
		GetLocalDriveRoots(csaLocalDriveRoots);

		for (int i=0;i<csaLocalDriveRoots.GetSize();i++)
		{
			// find tree starting from inDir 
			if (GET_SAFE(m_pss->m_bRecurse))
			{
				ok = GetSubDirs(csaSearchFolders, csaLocalDriveRoots.GetAt(i));
				if (!ok)
				{
					break;
				}
			}
			else
			{
				csaSearchFolders.Add(csaLocalDriveRoots.GetAt(i));
			}
		}
	}
	else
	{
		// single folder search 

		// make sure we have parentPath\*.*
		if (csSearchFolder.GetAt(csSearchFolder.GetLength() - 1)!='\\')
		{
			csSearchFolder+='\\';
		}

		// find tree starting from csSearchFolder 
		if (GET_SAFE(m_pss->m_bRecurse))
		{
			ok = GetSubDirs(csaSearchFolders, csSearchFolder);
		}
		else
		{
			csaSearchFolders.Add(csSearchFolder);
		}
	}

	if (ok)
	{
		// now, search the folders for the filespec.

		//SortStringArray(csaSearchFolders); this might be nice...
		ok = FindFileInFolder(csaSearchFolders);
	}

	return ok;
}

//////////////////////////////////////////////////////////////////////

bool CFileFinder::FindFileInFolder(const CStringArray &csaSearchFolders)
{
	PROC_TRACE;

	if (m_pss==NULL)
	{
		return false;
	}

	CString csFileName;

	try 
	{
	
		for (int i=0; i < csaSearchFolders.GetSize(); i++) 
		{
			// bail on cancel
			if (GET_SAFE(m_pss->m_bCancel))
			{
				return false;
			}

			CString curDir = csaSearchFolders.GetAt(i);
	
			// chop trailing "\"
			if (curDir.GetAt(curDir.GetLength() - 1)=='\\')
				curDir = curDir.Left(curDir.GetLength() - 1);

			CString searchString = curDir + "\\";
			searchString+=GET_SAFE(m_pss->m_csFindFile);
			
			// find first file in current directory
			struct _finddata_t  c_file;
			long fhandle = -1;
			
			SET_SAFE(m_pss->m_csCurFolder, curDir);

			if ((fhandle=_findfirst( searchString, &c_file ))!=-1) 
			{
				if ((c_file.attrib & _A_SUBDIR)!=_A_SUBDIR) 
				{
					// found one!!

					csFileName=curDir + "\\";
					csFileName+=c_file.name;

					// stash it
					EnterCriticalSection(&g_findFileCritSection);
					m_pss->m_csaFoundFiles.Add(csFileName);
					LeaveCriticalSection(&g_findFileCritSection);

					// are we done?
					if (GET_SAFE(m_pss->m_bFindSingleFile))
					{
						_findclose(fhandle);
						return true;
					}
				}

				// find the rest of them
				while(_findnext( fhandle, &c_file ) == 0 ) 
				{
					if ((c_file.attrib & _A_SUBDIR)!=_A_SUBDIR) 
					{
						// found another one!!

						csFileName=curDir + "\\";
						csFileName+=c_file.name;

						// stash it
						EnterCriticalSection(&g_findFileCritSection);
						m_pss->m_csaFoundFiles.Add(csFileName);
						LeaveCriticalSection(&g_findFileCritSection);
					} 

					// bail on cancel
					if (GET_SAFE(m_pss->m_bCancel))
					{
						_findclose(fhandle);
						return false;
					}
				}
				_findclose(fhandle);
			}
		} // subdirs
		
	} 
	catch (CMemoryException *e) 
	{
		e->ReportError();
		e->Delete();

		return false;
	}
	catch (...) 
	{
		return false;
	}
	
	return true;
}

//////////////////////////////////////////////////////////////////////

bool CFileFinder::GetSubDirs(CStringArray &csaFolders, CString path)
{
	PROC_TRACE;

	if (path.IsEmpty())
	{
		return false;
	}

	if (m_pss==NULL)
	{
		return false;
	}

	struct _finddata_t  c_file;
	long fhandle = 0;
	int dirs=0;
	
	CString searchString;
	if (path.GetAt(path.GetLength() - 1)=='\\')
		path = path.Left(path.GetLength() - 1);
	
	searchString = path + "\\*.*";

	// bail on cancel
	if (GET_SAFE(m_pss->m_bCancel))
	{
		return false;
	}
	
	try 
	{
		// folders can have .'s in their name

		if ((fhandle=_findfirst( searchString, &c_file ))!=-1) 
		{
			
			// we only care about subdirs
			if ((c_file.attrib & _A_SUBDIR)==_A_SUBDIR) 
			{
				// add c_file.name to the string array
				
				// ignore parents 
				if ((strcmp(c_file.name, ".")!=0) && (strcmp(c_file.name, "..")!=0)) 
				{
					CString newPath = path + "\\";
					newPath+= c_file.name;
					GetSubDirs(csaFolders, newPath);
					csaFolders.Add(newPath);
				}
			}
			
			// find the rest of them	
			while(_findnext( fhandle, &c_file ) == 0 ) 
			{
				
				// bail on cancel
				if (GET_SAFE(m_pss->m_bCancel))
				{
					_findclose(fhandle);
					return false;
				}

				if ((c_file.attrib & _A_SUBDIR)==_A_SUBDIR) 
				{
					// ignore parents 
					if ((strcmp(c_file.name, ".")!=0) && (strcmp(c_file.name, "..")!=0)) 
					{
						CString newPath = path + "\\";
						newPath+= c_file.name;
						GetSubDirs(csaFolders, newPath);
						csaFolders.Add(newPath);
					}
				}
			}

			_findclose(fhandle);
		}
	} 
	catch (CMemoryException *e) 
	{
		e->ReportError();
		e->Delete();
		return false;
	}
	catch (...) 
	{
		return false;
	}

	return true;
}

//////////////////////////////////////////////////////////////////////

bool	CFileFinder::GetLocalDriveRoots(CStringArray &csaDrives)
{
	PROC_TRACE;

	csaDrives.RemoveAll();

	CString t;

	for (int i='A'; i<'Z'; i++)
	{
		char buf[4];
		buf[0]=i;
		buf[1]=':';
		buf[2]='\\';
		buf[3]=0;
		UINT dt = GetDriveType(buf);
		switch (dt)
		{
		case DRIVE_FIXED:
			t = buf;		
			t+="\\";
			csaDrives.Add(t);
			break;
		case DRIVE_REMOTE:
			if (GET_SAFE(m_pss->m_bSearchNetworkDrives))
			{
				t = buf;		
				t+="\\";
				csaDrives.Add(t);
			}
			break;
		case DRIVE_REMOVABLE:
			if (GET_SAFE(m_pss->m_bSearchRemovableDrives))
			{
				t = buf;		
				t+="\\";
				csaDrives.Add(t);
			}
			break;
		case DRIVE_CDROM:
			if (GET_SAFE(m_pss->m_bSearchCDROMDrives))
			{
				t = buf;		
				t+="\\";
				csaDrives.Add(t);
			}
			break;

		default:
			break;
		}

		
	}

	return true;
}

