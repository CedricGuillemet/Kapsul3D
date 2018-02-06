// PathDropList.cpp : implementation file
//

#include "stdafx.h"
#include "PathDropList.h"
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathDropList

CPathDropList::CPathDropList()
{
	//OleInitialize(NULL);
}

CPathDropList::~CPathDropList()
{
}


BEGIN_MESSAGE_MAP(CPathDropList, CListBox)
	//{{AFX_MSG_MAP(CPathDropList)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	ON_WM_KEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathDropList message handlers

int CPathDropList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DragAcceptFiles(TRUE);
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

void CPathDropList::OnDropFiles(HDROP hDropInfo) 
{
	//MessageBox("Yop!");
	UINT nNumFilesDropped = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);

	//
	// Iterate through them and do some funky stuff
	//
	TCHAR szFilename[MAX_PATH + 1];
	for (UINT nFile = 0 ; nFile < nNumFilesDropped; nFile++)
	{
		//
		// Get the pathname
		//
		DragQueryFile(hDropInfo, nFile, szFilename, MAX_PATH + 1);
		
		struct _stat buf;
		int result = _tstat( szFilename, &buf );
		if( result == 0 )
		{
			//
			// Do we have a directory? (if we want dirs)
			//
			if ((buf.st_mode & _S_IFDIR) == _S_IFDIR)
			//
			// Do something with it...pretty useless, 
			// but only example
			//
			if (FindString(0,szFilename)==LB_ERR)
				AddString(szFilename);
		}
	}
	
	//
	// Windows allocates the memory for 
	// file information, so we must clean it up
	//
	DragFinish(hDropInfo);
	
	
	CListBox::OnDropFiles(hDropInfo);
}

void CPathDropList::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar==VK_DELETE)
	{
		DeleteFiles();
	}
	
	CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CPathDropList::DeleteFiles()
{
	int i;
	for (i=GetCount()-1;i>=0;i--)
	{
		if (GetSel(i))
		{
			DeleteString(i);
		}
	}

}

