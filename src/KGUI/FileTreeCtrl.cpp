/*
Module : FileTreeCtrl.CPP
Purpose: Implementation for an MFC class which provides a tree control similiar 
         to the left hand side of explorer
Created: PJN / 25-12-1999
History: PJN / 11-01-2000 1. Added some asserts to HasGotSubEntries
                          2. Fixed a problem with calling OnDblclk when no tree item is selected
                          3. Removed an unused variable from SetSelectedPath
         PJN / 25-01-2000 1. Minor update to the code in CTreeFileCtrl::OnDblclk to only allow 
                          selected items to be opened.
         PJN / 31-01-2000 1. Fixed a problem when you right mouse click over a non - selected item.
                          The control now implements the same behavior as Explorer for this.
                          2. Removed check for keyboard invocation of the context menu in OnContextMenu
                          3. Now displays the context menu over the selected item when invoked via
                          the keyboard. Again this is the same bahavior as Explorer has.
                          4. Optimized the code in PreTranslateMessage
                          5. Fixed a bug in CTreeFileCtrl::OnEndlabeledit

Copyright (c) 1999 - 2000 by PJ Naughter.  
All rights reserved.

*/

/////////////////////////////////  Includes  //////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "FileTreeCtrl.h"
#include "SortedArray.h"


//////////////////////////////// Defines //////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int CSystemImageList::m_nRefCount=0;

const UINT WM_POPULATE_TREE = WM_APP + 1;

bool FocusInPack=false;

////////////////////////////// Implementation /////////////////////////////////

CSystemImageList::CSystemImageList()
{
  //We need to implement reference counting to 
  //overcome an MFC limitation whereby you cannot
  //have two CImageLists attached to the one underlyinh
  //HIMAGELIST. If this was not done then you would get 
  //an ASSERT in MFC if you had two or more CTreeFileCtrl's
  //in your program at the same time
  if (m_nRefCount == 0)
  {
    //Attach to the system image list
    SHFILEINFO sfi;
    HIMAGELIST hSystemImageList = (HIMAGELIST) SHGetFileInfo(_T("C:\\"), 0, &sfi, sizeof(SHFILEINFO),
                                                             SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
    VERIFY(m_ImageList.Attach(hSystemImageList));
  }  

  //Increment the reference count
  m_nRefCount++;
}

CSystemImageList::~CSystemImageList()
{
  //Decrement the reference count
  m_nRefCount--;  

  if (m_nRefCount == 0)
  {
    //Detach from the image list to prevent problems on 95/98 where
    //the system image list is shared across processes
    m_ImageList.Detach();
  }
}

CImageList& CSystemImageList::GetImageList()
{
  return m_ImageList;
}


/*
	ON_COMMAND(ID_FILE_PROPERTIES, OnFileProperties)
	ON_COMMAND(ID_FILE_RENAME, OnFileRename)
	ON_UPDATE_COMMAND_UI(ID_FILE_RENAME, OnUpdateFileRename)
	ON_COMMAND(ID_FILE_DELETE, OnFileDelete)
	ON_UPDATE_COMMAND_UI(ID_FILE_DELETE, OnUpdateFileDelete)
	ON_COMMAND(ID_VIEW_REFRESH, OnViewRefresh)
	ON_UPDATE_COMMAND_UI(ID_FILE_PROPERTIES, OnUpdateFileProperties)

    */

BEGIN_MESSAGE_MAP(CTreeFileCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeFileCtrl)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemexpanding)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_INITMENUPOPUP()
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	//}}AFX_MSG_MAP
	ON_WM_CONTEXTMENU()
  ON_MESSAGE(WM_POPULATE_TREE, OnPopulateTree)
END_MESSAGE_MAP()

CTreeFileCtrl::CTreeFileCtrl() : CTreeCtrl()
{
  m_bShowFiles = TRUE;
  m_pilDrag = NULL;
  m_hSelItem = NULL;
  m_hItemDrag = NULL;
  m_hItemDrop = NULL;
  m_TimerTicks = 0;
  m_bAllowDragDrop = FALSE;
  m_bAllowRename = FALSE;
  m_bAllowOpen = TRUE;
  m_bAllowProperties = TRUE;
  m_bAllowDelete = FALSE;

  CWinApp* pApp = AfxGetApp();
  /*
  m_NoDropCopyCursor = pApp->LoadCursor(IDR_TREEFILECTRL_NO_DROPCOPY);
  ASSERT(m_NoDropCopyCursor);
  m_DropCopyCursor = pApp->LoadCursor(IDR_TREEFILECTRL_DROPCOPY);
  ASSERT(m_DropCopyCursor);
  m_NoDropMoveCursor = pApp->LoadCursor(IDR_TREEFILECTRL_NO_DROPMOVE);
  ASSERT(m_NoDropMoveCursor);
  m_DropMoveCursor = pApp->LoadStandardCursor(IDC_ARROW);
  */
  m_NoDropCopyCursor = pApp->LoadStandardCursor(IDC_ARROW);
  ASSERT(m_NoDropCopyCursor);
  m_DropCopyCursor = pApp->LoadStandardCursor(IDC_ARROW);
  ASSERT(m_DropCopyCursor);
  m_NoDropMoveCursor = pApp->LoadStandardCursor(IDC_ARROW);
  ASSERT(m_NoDropMoveCursor);
  m_DropMoveCursor = pApp->LoadStandardCursor(IDC_ARROW);
  ASSERT(m_DropMoveCursor);
}

CTreeFileCtrl::~CTreeFileCtrl()
{
}

int CTreeFileCtrl::CompareByFilenameNoCase(CString& element1, CString& element2) 
{
  return element1.CompareNoCase(element2);
}

#ifdef _DEBUG
void CTreeFileCtrl::AssertValid() const
{
	CTreeCtrl::AssertValid();
}

void CTreeFileCtrl::Dump(CDumpContext& dc) const
{
	CTreeCtrl::Dump(dc);
}
#endif //_DEBUG

void CTreeFileCtrl::SetShowFiles(BOOL bFiles) 
{ 
	m_bShowFiles = bFiles; 
	if (IsWindow(GetSafeHwnd()))
		OnViewRefresh();
}

void CTreeFileCtrl::SetRootFolder(const CString& sPath)
{
	int nLength = sPath.GetLength();
	if (nLength)
	{
		if (sPath.GetAt(nLength-1) == _T('\\'))
			m_sRootFolder = sPath.Left(nLength-1);
	}
	else
		m_sRootFolder = sPath;
	if (IsWindow(GetSafeHwnd()))
		OnViewRefresh();
}

int CTreeFileCtrl::GetIconIndex(HTREEITEM hItem)
{
	TV_ITEM tvi;
	ZeroMemory(&tvi, sizeof(TV_ITEM));
	tvi.mask = TVIF_IMAGE;
	tvi.hItem = hItem;
	if (GetItem(&tvi))
		return tvi.iImage;
	else
		return -1;
}

int CTreeFileCtrl::GetIconIndex(const CString& sFilename)
{
	//Retreive the icon index for a specified file/folder
	SHFILEINFO sfi;
	if (SHGetFileInfo(sFilename, 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_SMALLICON) == 0)
		return -1;
	return sfi.iIcon;
}

int CTreeFileCtrl::GetSelIconIndex(const CString& sFilename)
{
	//Retreive the icon index for a specified file/folder
    //if (GetZipName(char *Path,char *Dest,char *ZipRep)
	SHFILEINFO sfi;
	if (SHGetFileInfo(sFilename, 0, &sfi, sizeof(SHFILEINFO), SHGFI_ICON | SHGFI_OPENICON | SHGFI_SMALLICON) == 0)
		return 0;
	return sfi.iIcon;
}

int CTreeFileCtrl::GetSelIconIndex(HTREEITEM hItem)
{
	TV_ITEM tvi;
	ZeroMemory(&tvi, sizeof(TV_ITEM));
	tvi.mask = TVIF_SELECTEDIMAGE;
	tvi.hItem = hItem;
	if (GetItem(&tvi))
		return tvi.iSelectedImage;
	else
		return -1;
}

HTREEITEM CTreeFileCtrl::FindSibling(HTREEITEM hParent, const CString& sItem)
{
	HTREEITEM hChild = GetChildItem(hParent);
	while (hChild)
	{
		CString sFound = GetItemText(hChild);
		if (sFound.CompareNoCase(sItem) == 0)
			return hChild;
		hChild = GetNextItem(hChild, TVGN_NEXT);
	}
	return NULL;
}

CString CTreeFileCtrl::GetSelectedPath()
{
	return ItemToPath(GetSelectedItem());
}

HTREEITEM CTreeFileCtrl::SetSelectedPath(const CString& sPath, BOOL bExpanded)
{
	CString sSearch(sPath);
	int nSearchLength = sSearch.GetLength();
	if (nSearchLength == 0)
	{
		TRACE(_T("Cannot select a empty path\n"));
		return NULL;
	}
	
	//Remove trailing "\" from the path
	if (nSearchLength > 3 && sSearch.GetAt(nSearchLength-1) == _T('\\'))
		sSearch = sSearch.Left(nSearchLength-1);
	
	//Remove initial part of path if the root folder is setup
	int nRootLength = m_sRootFolder.GetLength();
	if (nRootLength)
	{
		if (sSearch.Find(m_sRootFolder) != 0)
		{
			TRACE(_T("Could not select the path %s as the root has been configued as %s\n"), sPath, m_sRootFolder);
			return NULL;
		}
		sSearch = sSearch.Right(sSearch.GetLength() - 1 - nRootLength);
	}
	
	if (sSearch.IsEmpty())
		return NULL;
	
	//  SetRedraw(FALSE);
	
	HTREEITEM hItemFound = TVI_ROOT;
	int nFound = sSearch.Find(_T('\\'));
	BOOL bDriveMatch = m_sRootFolder.IsEmpty();
	while (nFound != -1)
	{
		CString sMatch;
		if (bDriveMatch)
		{
			sMatch = sSearch.Left(nFound + 1);
			bDriveMatch = FALSE;
		}
		else
			sMatch = sSearch.Left(nFound);
		hItemFound = FindSibling(hItemFound, sMatch);
		if (hItemFound == NULL)
			break;
		else
			Expand(hItemFound, TVE_EXPAND);
		
		sSearch = sSearch.Right(sSearch.GetLength() - nFound - 1);
		nFound = sSearch.Find(_T('\\'));
	};
	
	//The last item 
	if (hItemFound)
	{
		if (sSearch.GetLength())
			hItemFound = FindSibling(hItemFound, sSearch);
		SelectItem(hItemFound);
		
		if (bExpanded)
			Expand(hItemFound, TVE_EXPAND);
	}
	
	//  SetRedraw(TRUE);
	
	return hItemFound;
}

BOOL CTreeFileCtrl::Rename(HTREEITEM hItem)
{
	if (!IsDrive(hItem) && m_bAllowRename)
		return (EditLabel(hItem) != NULL);
	else
		return FALSE;
}

BOOL CTreeFileCtrl::ShowProperties(HTREEITEM hItem)
{
	BOOL bSuccess = FALSE;
	if (hItem && m_bAllowProperties)
	{
		//Show the "properties" for the selected file
		CString sFile = ItemToPath(hItem);
		SHELLEXECUTEINFO sei;
		ZeroMemory(&sei,sizeof(sei));
		sei.cbSize = sizeof(sei);
		sei.hwnd = AfxGetMainWnd()->GetSafeHwnd();
		sei.nShow = SW_SHOW;
		sei.lpFile = sFile.GetBuffer(sFile.GetLength());
		sei.lpVerb = _T("properties");
		sei.fMask  = SEE_MASK_INVOKEIDLIST;
		bSuccess = ShellExecuteEx(&sei);
		sFile.ReleaseBuffer();
	}
	return bSuccess;
}

BOOL CTreeFileCtrl::Delete(HTREEITEM hItem)
{
	BOOL bSuccess = FALSE;
	if (!IsDrive(hItem) && m_bAllowDelete)
	{
		//Create a Multi SZ string with the filename to delete
		CString sFileToDelete = ItemToPath(hItem);
		int nChars = sFileToDelete.GetLength() + 1;
		nChars++;
		SHFILEOPSTRUCT shfo;
		ZeroMemory(&shfo, sizeof(SHFILEOPSTRUCT));
		shfo.hwnd = AfxGetMainWnd()->GetSafeHwnd();
		shfo.wFunc = FO_DELETE;
		
		//Undo is not allowed if the SHIFT key is held down
		if (!(GetKeyState(VK_SHIFT) & 0x8000))
			shfo.fFlags = FOF_ALLOWUNDO;
		
		TCHAR* pszFrom = new TCHAR[nChars];
		TCHAR* pszCur = pszFrom;
		_tcscpy(pszCur, sFileToDelete);
		pszCur[nChars-1] = _T('\0');
		shfo.pFrom = pszFrom;
		
		//Let the shell perform the actual deletion
		if (SHFileOperation(&shfo) == 0 && shfo.fAnyOperationsAborted == FALSE)
		{
			//Delete the item from the view
			bSuccess = DeleteItem(hItem);
		}
		
		//Free up the memory we had allocated
		delete [] pszFrom;
	}
	return bSuccess;
}

BOOL CTreeFileCtrl::Open(HTREEITEM hItem)
{
	BOOL bSuccess = FALSE;
	if (hItem && m_bAllowOpen)
	{
		//Show the "properties" for the selected file
		CString sFile = ItemToPath(hItem);
		SHELLEXECUTEINFO sei;
		ZeroMemory(&sei,sizeof(sei));
		sei.cbSize = sizeof(sei);
		sei.hwnd = AfxGetMainWnd()->GetSafeHwnd();
		sei.nShow = SW_SHOW;
		sei.lpFile = sFile.GetBuffer(sFile.GetLength());
		sei.fMask  = SEE_MASK_INVOKEIDLIST;
		bSuccess = ShellExecuteEx(&sei);
		sFile.ReleaseBuffer();
	}
	return bSuccess;
}

void CTreeFileCtrl::SetFlags(DWORD dwFlags)
{
	SetShowFiles((dwFlags & TFC_SHOWFILES) != 0);
	SetAllowDragDrop((dwFlags & TFC_ALLOWDRAGDROP) != 0);
	SetAllowRename((dwFlags & TFC_ALLOWRENAME) != 0);  
	SetAllowOpen((dwFlags & TFC_ALLOWOPEN) != 0);    
	SetAllowProperties((dwFlags & TFC_ALLOWPROPERTIES) != 0);
	SetAllowDelete((dwFlags & TFC_ALLOWDELETE) != 0);
}

void CTreeFileCtrl::OnFileRename() 
{
	Rename(GetSelectedItem());
}

void CTreeFileCtrl::OnUpdateFileRename(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!IsDrive(GetSelectedItem()) && m_bAllowRename);
}

void CTreeFileCtrl::OnFileProperties() 
{
	ShowProperties(GetSelectedItem());
}

void CTreeFileCtrl::OnUpdateFileProperties(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetSelectedItem() && m_bAllowProperties);
}

void CTreeFileCtrl::OnFileOpen() 
{
	Open(GetSelectedItem());
}

void CTreeFileCtrl::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetSelectedItem() && m_bAllowOpen);	
}

void CTreeFileCtrl::OnFileDelete() 
{
	Delete(GetSelectedItem());
}

void CTreeFileCtrl::OnUpdateFileDelete(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!IsDrive(GetSelectedItem()) && m_bAllowDelete);
}

void CTreeFileCtrl::OnContextMenu(CWnd*, CPoint point)
{
/*
CMenu menu;
VERIFY(menu.LoadMenu(IDR_POPUP_TREEFILEVIEW));
CMenu* pPopup = menu.GetSubMenu(0);
ASSERT(pPopup != NULL);
pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,	this);
    */
}

HTREEITEM CTreeFileCtrl::InsertFileItem(const CString& sFile, const CString& sPath, HTREEITEM hParent)
{
	//Retreive the icon indexes for the specified file/folder
	int nIconIndex = GetIconIndex(sPath);
	int nSelIconIndex = GetSelIconIndex(sPath);
	if (nIconIndex == -1 || nSelIconIndex == -1)
	{
		nIconIndex = GetIconIndex("c:\\program files");
		nSelIconIndex = GetSelIconIndex("c:\\program files");
	}
	//Add the actual item
	CString sTemp(sFile);
	TV_INSERTSTRUCT tvis;
	ZeroMemory(&tvis, sizeof(TV_INSERTSTRUCT));
	tvis.hParent = hParent;
	tvis.hInsertAfter = TVI_LAST;
	tvis.item.mask = TVIF_CHILDREN | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	tvis.item.pszText = sTemp.GetBuffer(sTemp.GetLength());
	tvis.item.iImage = nIconIndex;
	tvis.item.iSelectedImage = nSelIconIndex;
	tvis.item.cChildren = HasGotSubEntries(sPath);
	HTREEITEM hItem = InsertItem(&tvis);
	sTemp.ReleaseBuffer();
	
	return hItem;
}

BOOL CTreeFileCtrl::GetChecked(HTREEITEM hItem) const
{
	ASSERT(::IsWindow(m_hWnd));
	TVITEM item;
	item.mask = TVIF_HANDLE | TVIF_STATE;
	item.hItem = hItem;
	item.stateMask = TVIS_STATEIMAGEMASK;
	VERIFY(::SendMessage(m_hWnd, TVM_GETITEM, 0, (LPARAM)&item));
	// Return zero if it's not checked, or nonzero otherwise.
	return ((BOOL)(item.state >> 12) -1);
}

BOOL CTreeFileCtrl::SetChecked(HTREEITEM hItem, BOOL fCheck)
{
	ASSERT(::IsWindow(m_hWnd));
	TVITEM item;
	item.mask = TVIF_HANDLE | TVIF_STATE;
	item.hItem = hItem;
	item.stateMask = TVIS_STATEIMAGEMASK;
	
	/*
	Since state images are one-based, 1 in this macro turns the check off, and
	2 turns it on.
	*/
	item.state = INDEXTOSTATEIMAGEMASK((fCheck ? 2 : 1));
	
	return (BOOL)::SendMessage(m_hWnd, TVM_SETITEM, 0, (LPARAM)&item);
}


void CTreeFileCtrl::OnViewRefresh() 
{
	//SetRedraw(FALSE);
	
	//Get the item which is currently selected
	HTREEITEM hSelItem = GetSelectedItem();
	CString sItem  = ItemToPath(hSelItem);
	BOOL bExpanded = (GetChildItem(hSelItem) != NULL); 
	
	//Display the folder items in the tree
	if (m_sRootFolder.IsEmpty())
		DisplayDrives(TVI_ROOT, FALSE);
	else
		DisplayPath(m_sRootFolder, TVI_ROOT, FALSE);
	
	//Reselect the initially selected item
	if (sItem.GetLength())
		hSelItem = SetSelectedPath(sItem, bExpanded);
	
	//SetRedraw(TRUE);
}

void CTreeFileCtrl::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pDispInfo = (TV_DISPINFO*)pNMHDR;
	if (pDispInfo->item.hItem == 0)
		*pResult = TRUE;
	else
		*pResult = FALSE;
}

void CTreeFileCtrl::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pDispInfo = (TV_DISPINFO*)pNMHDR;
	if (pDispInfo->item.pszText)
	{
		SHFILEOPSTRUCT shfo;
		ZeroMemory(&shfo, sizeof(SHFILEOPSTRUCT));
		shfo.hwnd = AfxGetMainWnd()->GetSafeHwnd();
		shfo.wFunc = FO_RENAME;
		shfo.fFlags = FOF_ALLOWUNDO;
		
		CString sFrom = ItemToPath(pDispInfo->item.hItem);
		int nFromLength = sFrom.GetLength();
		TCHAR* pszFrom = new TCHAR[nFromLength + 2];
		_tcscpy(pszFrom, sFrom);
		pszFrom[nFromLength+1] = _T('\0');
		shfo.pFrom = pszFrom;
		HTREEITEM hParent = GetParentItem(pDispInfo->item.hItem);
		CString sParent = ItemToPath(hParent);
		CString sTo;
		if (IsDrive(sParent))
			sTo = sParent + pDispInfo->item.pszText;
		else
			sTo = sParent + _T("\\") + pDispInfo->item.pszText;
		
		int nToLength = _tcslen(sTo);
		TCHAR* pszTo = new TCHAR[nToLength + 2];
		_tcscpy(pszTo, sTo);
		pszTo[nToLength+1] = _T('\0');
		shfo.pTo = pszTo;
		
		//Let the shell perform the actual rename
		if (SHFileOperation(&shfo) == 0 && shfo.fAnyOperationsAborted == FALSE)
		{
			*pResult = TRUE;
			
			//Update its text  
			SetItemText(pDispInfo->item.hItem, pDispInfo->item.pszText);
			
			//Also update the icons for it
			CString sPath = ItemToPath(pDispInfo->item.hItem);
			SetItemImage(pDispInfo->item.hItem, GetIconIndex(sPath), GetSelIconIndex(sPath));
		}
		
		//Don't forget to free up the memory we allocated
		delete [] pszFrom;
		delete [] pszTo;
	}
	
	*pResult = 0;
}

BOOL CTreeFileCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// When an item is being edited make sure the edit control
	// receives certain important key strokes
	if (GetEditControl())
	{
		::TranslateMessage(pMsg);
		::DispatchMessage(pMsg);
		return TRUE; // DO NOT process further
	}
	
	//Context menu via the keyboard
	if ((((pMsg->message == WM_KEYDOWN || pMsg->message == WM_SYSKEYDOWN) && // If we hit a key and
		(pMsg->wParam == VK_F10) && (GetKeyState(VK_SHIFT) & ~1)) != 0) ||   // it's Shift+F10 OR
		(pMsg->message == WM_CONTEXTMENU))						                   	   // Natural keyboard key
	{
		CRect rect;
		GetItemRect(GetSelectedItem(), rect, TRUE);
		ClientToScreen(rect);
		OnContextMenu(NULL, rect.CenterPoint());
		return TRUE;
	}
	//Hitting the Escape key, Cancelling drag & drop
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE && IsDragging())
	{
		EndDragging(TRUE);
		return TRUE;
	}
	//Hitting the Alt-Enter key combination, show the properties sheet 
	else if (pMsg->message == WM_SYSKEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnFileProperties();
		return TRUE;
	}
	//Hitting the Enter key, open the item
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		OnFileOpen();
		return TRUE;
	}
	//Hitting the delete key, delete the item
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DELETE)
	{
		OnFileDelete();
		return TRUE;
	}
	//hitting the backspace key, go to the parent folder
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_BACK)
	{
		UpOneLevel();
		return TRUE;
	}
	//hitting the F2 key, being in-place editing of an item
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F2)
	{
		OnFileRename();
		return TRUE;
	}
	//hitting the F5 key, force a refresh of the whole tree
	else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_F5)
	{
		OnViewRefresh();
		return TRUE;
	}
	
	//Let the parent class do its thing
	return CTreeCtrl::PreTranslateMessage(pMsg);
}

void CTreeFileCtrl::UpOneLevel()
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
	{
		HTREEITEM hParent = GetParentItem(hItem);
		if (hParent)
			Select(hParent, TVGN_CARET);
	}
}

void CTreeFileCtrl::OnUpdateUpOneLevel(CCmdUI* pCmdUI)
{
	HTREEITEM hItem = GetSelectedItem();
	if (hItem)
		pCmdUI->Enable(GetParentItem(hItem) != NULL);
	else
		pCmdUI->Enable(FALSE);
}

BOOL CTreeFileCtrl::IsFile(HTREEITEM hItem)
{
	return IsFile(ItemToPath(hItem));
}

BOOL CTreeFileCtrl::IsFolder(HTREEITEM hItem)
{
	return IsFolder(ItemToPath(hItem));
}

BOOL CTreeFileCtrl::IsDrive(HTREEITEM hItem)
{
	return IsDrive(ItemToPath(hItem));
}

BOOL CTreeFileCtrl::IsFile(const CString& sPath)
{
	return ((GetFileAttributes(sPath) & FILE_ATTRIBUTE_DIRECTORY) == 0);
}

BOOL CTreeFileCtrl::IsFolder(const CString& sPath)
{
	return ((GetFileAttributes(sPath) & FILE_ATTRIBUTE_DIRECTORY) != 0);
}

BOOL CTreeFileCtrl::IsDrive(const CString& sPath)
{
	return (sPath.GetLength() == 3 && sPath.GetAt(1) == _T(':') && sPath.GetAt(2) == _T('\\'));
}

BOOL CTreeFileCtrl::HasGotSubEntries(const CString& sDirectory)
{
	/*
	ASSERT(sDirectory.GetLength());
	CFileFind find;
	CString sFile;
	CString ZipName,ZipRep;
	
	// archive
	
	CString daff=sDirectory;
	
	CKPlugin *daGen=daLib->GetSupportedResManager(daff,ZipName,ZipRep);
	if (daGen!=NULL)
	{
		// archive
		daGen->Process(KM_SETRESOURCE,(UINT)ZipName.GetBuffer(0),0);
		if (ZipRep.GetLength()>0) ZipRep+="\\";
		bool value=(daGen->Process(KM_CONTAINSUBDIR,(UINT)ZipRep.GetBuffer(0),0)!=0);
		daGen->Process(KM_CLOSERESOURCE);
		return value;
	}
	
	// file/folder
	if (sDirectory.GetAt(sDirectory.GetLength()-1) == _T('\\'))
		sFile = sDirectory + _T("*.*");
	else
		sFile = sDirectory + _T("\\*.*");
	BOOL bFind = find.FindFile(sFile);  
	while (bFind)
	{
		bFind = find.FindNextFile();
		if (find.IsDirectory() && !find.IsDots())
			return TRUE;
	}
	*/
	return FALSE;
}

void CTreeFileCtrl::PreSubclassWindow() 
{
	//Let the parent class do its thing	
	CTreeCtrl::PreSubclassWindow();
	
	//Post a message to populate the tree view with the drive letters
	PostMessage(WM_POPULATE_TREE);
}

LRESULT CTreeFileCtrl::OnPopulateTree(WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	//attach the image list to the tree control
	SetImageList(&m_SysImageList.GetImageList(), TVSIL_NORMAL);
	
	//Force a refresh
	OnViewRefresh();
	
	return 0L;
}

void CTreeFileCtrl::DisplayDrives(HTREEITEM hParent, BOOL bUseSetRedraw)
{
  CWaitCursor c;

  //Speed up the job by turning off redraw
  /*
  if (bUseSetRedraw)
    SetRedraw(FALSE);
*/
  //Remove any items currently in the tree
  DeleteAllItems();

  //Enumerate the drive letters and add them to the tree control
  DWORD dwDrives = GetLogicalDrives();
  DWORD dwMask = 1;
  for (int i=0; i<32; i++)
  {
    if (dwDrives & dwMask)
    {
      CString sDrive,sDrive3;
      sDrive.Format(_T("%c:\\"), i + _T('A'));
	  /*
	  sDrive3.Format(_T("%c:"), i + _T('A'));

	  CString sDrive2;
	if (GetVolumeInformation(sDrive,RootName,128,NULL,NULL,NULL,NULL,0))
	{
		sDrive2=RootName;
		sDrive2+=" ("+sDrive3+")";
	}
	else
		sDrive2=sDrive3;
		*/
      InsertFileItem(sDrive, sDrive, hParent);
    }
    dwMask <<= 1;
  }
/*
  if (bUseSetRedraw)
    SetRedraw(TRUE);
    */
}

void CTreeFileCtrl::DisplayPath(const CString& sPath, HTREEITEM hParent, BOOL bUseSetRedraw)
{
	/*
	CWaitCursor c;
	CString ZipName,ZipRep;
	
	
	//Speed up the job by turning off redraw

	//Remove all the items currently under hParent
	HTREEITEM hChild = GetChildItem(hParent);
	while (hChild)
	{
		DeleteItem(hChild);
		hChild = GetChildItem(hParent);
	}
	
	//Find all the directories and files underneath sPath
	CSortedArray<CString, CString&> DirectoryPaths;
	CSortedArray<CString, CString&> FilePaths;
	CFileFind find;
	CString sFile;
	if (sPath.GetAt(sPath.GetLength()-1) == _T('\\'))
		sFile = sPath + _T("*.*");
	else
		sFile = sPath + _T("\\*.*");
	
	CKPlugin *daGen=daLib->GetSupportedResManager(sPath,ZipName,ZipRep);
	if (daGen!=NULL)
	{
		// archive
		daGen->Process(KM_SETRESOURCE,(UINT)ZipName.GetBuffer(0),0);
		////CString httg=ZipRep+"\\";
		if (ZipRep.GetLength()!=0) ZipRep+="\\";
		int getents=daGen->Process(KM_LISTFILES,(UINT)ZipRep.GetBuffer(0),0);
		for (int jop=0;jop<getents;jop++)
		{
			PackListFiles *KEnts;
			KEnts=(PackListFiles *)daGen->Process(KM_LISTFILEENTRY,jop,1);
			CString sPath2 = ZipName;
			sPath2+="\\";
			sPath2+=ZipRep;
			//sPath2+="\\";
			sPath2+=KEnts->FileName;
			if (!KEnts->IsFile)
				InsertFileItem( KEnts->FileName,sPath2, hParent);

		}
		daGen->Process(KM_CLOSERESOURCE);
		

        return;
  }
  else
  {
      
    BOOL bFind = find.FindFile(sFile);  
    while (bFind)
    {
        bFind = find.FindNextFile();
        if (find.IsDirectory())
        {
        if (!find.IsDots())
        {
            CString sPath = find.GetFilePath();
            DirectoryPaths.Add(sPath);
        }
        }
        else
        {
            CString daff=find.GetFileName();
            char *tmp=daff.GetBuffer(1);
            char *tmp2=strstr(tmp,".zip");
            if (tmp2!=NULL)
            {
                CString sPath = find.GetFilePath();
                DirectoryPaths.Add(sPath);
            }
        }

    }
    
  }
  //Now sort the 2 arrays prior to added to the tree control
  DirectoryPaths.SetCompareFunction(CompareByFilenameNoCase);
  FilePaths.SetCompareFunction(CompareByFilenameNoCase);
  DirectoryPaths.Sort();
  FilePaths.Sort();

  //Now add all the directories to the tree control
  for (int i=0; i<DirectoryPaths.GetSize(); i++)
  {
    CString& sPath = DirectoryPaths.ElementAt(i);
    TCHAR path_buffer[_MAX_PATH];
    TCHAR fname[_MAX_FNAME];
    TCHAR ext[_MAX_EXT];
    _tsplitpath(sPath, NULL, NULL, fname, ext);
    _tmakepath(path_buffer, NULL, NULL, fname, ext);
    InsertFileItem(path_buffer, sPath, hParent);
  }

  //And the files to the tree control (if required)
  for (i=0; i<FilePaths.GetSize(); i++)
  {
    CString& sPath = FilePaths.ElementAt(i);
    TCHAR path_buffer[_MAX_PATH];
    TCHAR fname[_MAX_FNAME];
    TCHAR ext[_MAX_EXT];
    _tsplitpath(sPath, NULL, NULL, fname, ext);
    _tmakepath(path_buffer, NULL, NULL, fname, ext);
    InsertFileItem(path_buffer, sPath, hParent);
  }

  //Turn back on the redraw flag
  /*
  if (bUseSetRedraw)
    SetRedraw(TRUE);
    */
}

void CTreeFileCtrl::OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
  if (pNMTreeView->action == TVE_EXPAND)
  {
    //Add the new items to the tree if it does not have any child items
    //already
    if (!GetChildItem(pNMTreeView->itemNew.hItem))
    {
      CString sPath = ItemToPath(pNMTreeView->itemNew.hItem);
      DisplayPath(sPath, pNMTreeView->itemNew.hItem);
    }
  }

  *pResult = 0;
}

CString CTreeFileCtrl::ItemToPath(HTREEITEM hItem)
{
  CString sPath;
  
  //Create the full string of the tree item
  HTREEITEM hParent = hItem;
  while (hParent)
  {
    CString sItem = GetItemText(hParent);
    int nLength = sItem.GetLength();
    ASSERT(nLength);
    hParent = GetParentItem(hParent);

    if (sItem.GetAt(nLength-1) == _T('\\'))
      sPath = sItem + sPath;
    else
    {
      if (sPath.GetLength())
        sPath = sItem + _T('\\') + sPath;
      else
        sPath = sItem;
    }
  }

  //Add the root folder if there is one
  if (m_sRootFolder.GetLength())
    sPath = m_sRootFolder + _T('\\') + sPath;

  return sPath;
}

void CTreeFileCtrl::OnRclick(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
  //Remember the old selected item
  HTREEITEM hOldSelItem = GetSelectedItem();

  //Work out the position of where the context menu should be
  CPoint p(GetCurrentMessage()->pt);
  CPoint pt(p);
  ScreenToClient(&pt);
  Select(HitTest(pt), TVGN_CARET);
	OnContextMenu(NULL, p);

  //Reselect the old selected item
  Select(hOldSelItem, TVGN_CARET);
	
	*pResult = 0;
}

void CTreeFileCtrl::OnDblclk(NMHDR* /*pNMHDR*/, LRESULT* pResult) 
{
  HTREEITEM hItem = GetSelectedItem();
  CPoint pt = GetCurrentMessage()->pt;
  ScreenToClient(&pt);

	if (hItem && (hItem == HitTest(pt)))
	{
		TV_ITEM tvi;
		ZeroMemory(&tvi, sizeof(TVITEM));
		tvi.mask = TVIF_CHILDREN;
		tvi.hItem = hItem;
		if (GetItem(&tvi) && tvi.cChildren == 0)
			OnFileOpen();
	}
	
	*pResult = 0;
}

//Copied from CFrameWnd::OnInitMenuPopup to provide OnUpdateCmdUI functionality
//in the tree control
void CTreeFileCtrl::OnInitMenuPopup(CMenu* pMenu, UINT /*nIndex*/, BOOL bSysMenu) 
{
	//AfxCancelModes(m_hWnd);

	if (bSysMenu)
		return;     // don't support system menu

	ASSERT(pMenu != NULL);
	// check the enabled state of various menu items

	CCmdUI state;
	state.m_pMenu = pMenu;
	ASSERT(state.m_pOther == NULL);
	ASSERT(state.m_pParentMenu == NULL);

	// determine if menu is popup in top-level menu and set m_pOther to
	//  it if so (m_pParentMenu == NULL indicates that it is secondary popup)
	HMENU hParentMenu;
	if (AfxGetThreadState()->m_hTrackingMenu == pMenu->m_hMenu)
		state.m_pParentMenu = pMenu;    // parent == child for tracking popup
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL)
	{
		CWnd* pParent = GetTopLevelParent();
			// child windows don't have menus -- need to go to the top!
		if (pParent != NULL &&
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL)
		{
			int nIndexMax = ::GetMenuItemCount(hParentMenu);
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++)
			{
				if (::GetSubMenu(hParentMenu, nIndex) == pMenu->m_hMenu)
				{
					// when popup is found, m_pParentMenu is containing menu
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu);
					break;
				}
			}
		}
	}

	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		state.m_nID = pMenu->GetMenuItemID(state.m_nIndex);
		if (state.m_nID == 0)
			continue; // menu separator or invalid cmd - ignore it

		ASSERT(state.m_pOther == NULL);
		ASSERT(state.m_pMenu != NULL);
		if (state.m_nID == (UINT)-1)
		{
			// possibly a popup menu, route to first item of that popup
			state.m_pSubMenu = pMenu->GetSubMenu(state.m_nIndex);
			if (state.m_pSubMenu == NULL ||
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 ||
				state.m_nID == (UINT)-1)
			{
				continue;       // first item of popup can't be routed to
			}
			state.DoUpdate(this, FALSE);    // popups are never auto disabled
		}
		else
		{
			// normal menu item
			// Auto enable/disable if frame window has 'm_bAutoMenuEnable'
			//    set and command is _not_ a system command.
			state.m_pSubMenu = NULL;
			//state.DoUpdate(this, m_bAutoMenuEnable && state.m_nID < 0xF000);
      state.DoUpdate(this, TRUE && state.m_nID < 0xF000);
		}

		// adjust for menu deletions and additions
		UINT nCount = pMenu->GetMenuItemCount();
		if (nCount < state.m_nIndexMax)
		{
			state.m_nIndex -= (state.m_nIndexMax - nCount);
			while (state.m_nIndex < nCount &&
				pMenu->GetMenuItemID(state.m_nIndex) == state.m_nID)
			{
				state.m_nIndex++;
			}
		}
		state.m_nIndexMax = nCount;
	}
}

void CTreeFileCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	*pResult = 0;

  SelectItem(pNMTreeView->itemNew.hItem);
  if (!IsDropSource(pNMTreeView->itemNew.hItem) || !m_bAllowDragDrop)
    return;

  m_pilDrag = CreateDragImage(pNMTreeView->itemNew.hItem);
  if (!m_pilDrag)
    return;

  m_hItemDrag = pNMTreeView->itemNew.hItem;
  m_hItemDrop = NULL;

  // Calculate the offset to the hotspot
  CPoint offsetPt(8,8);   // Initialize a default offset

  CPoint dragPt = pNMTreeView->ptDrag;    // Get the Drag point
  UINT nHitFlags = 0;
  HTREEITEM htiHit = HitTest(dragPt, &nHitFlags);
  if (htiHit != NULL)
  {
    // The drag point has Hit an item in the tree
    CRect itemRect;
    if (GetItemRect(htiHit, &itemRect, FALSE))
    {
      // Count indent levels
      HTREEITEM htiParent = htiHit;
      int nIndentCnt = 0;
      while (htiParent != NULL)
      {
        htiParent = GetParentItem(htiParent);
        nIndentCnt++;
      }

      if (!(GetStyle() & TVS_LINESATROOT)) 
        nIndentCnt--;

      // Calculate the new offset
      offsetPt.y = dragPt.y - itemRect.top;
      offsetPt.x = dragPt.x - (nIndentCnt * GetIndent()) + GetScrollPos(SB_HORZ);
    }
  }

  //Begin the dragging  
  m_pilDrag->BeginDrag(0, offsetPt);
  POINT pt = pNMTreeView->ptDrag;
  ClientToScreen(&pt);
  m_pilDrag->DragEnter(NULL, pt);
  SetCapture();

  m_nTimerID = SetTimer(1, 300, NULL);
}

void CTreeFileCtrl::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (IsDragging())
  {
    CRect clientRect;
    GetClientRect(&clientRect);

    //Draw the drag
    POINT pt = point;
    ClientToScreen(&pt);
    CImageList::DragMove(pt);

    //Only select the drop item if we are in the client area
    HTREEITEM hItem = NULL;
    if (clientRect.PtInRect(point))
    {
      UINT flags;
      hItem = HitTest(point, &flags);
      if (m_hItemDrop != hItem)
      {
        CImageList::DragShowNolock(FALSE);
        SelectDropTarget(hItem);
        m_hItemDrop = hItem;
        CImageList::DragShowNolock(TRUE);
      }
    }
    
    if (hItem)
      hItem = GetDropTarget(hItem);

    //Change the cursor to give feedback
    if (hItem)
    {
      if ((GetKeyState(VK_CONTROL) & 0x8000))
        SetCursor(m_DropCopyCursor);
      else
        SetCursor(m_DropMoveCursor);
    }
    else
    {
      if ((GetKeyState(VK_CONTROL) & 0x8000))
        SetCursor(m_NoDropCopyCursor);
      else
        SetCursor(m_NoDropMoveCursor);
    }
  }

  //Let the parent class do its thing	
	CTreeCtrl::OnMouseMove(nFlags, point);
}

HTREEITEM CTreeFileCtrl::GetDropTarget(HTREEITEM hItem)
{
  if (!IsFile(hItem) && hItem != m_hItemDrag && hItem != GetParentItem(m_hItemDrag))
  {
    HTREEITEM htiParent = hItem;
    while ((htiParent = GetParentItem(htiParent)) != NULL)
    {
      if (htiParent == m_hItemDrag)
        return NULL;
    }
    return hItem;
  }
  return NULL;
}

BOOL CTreeFileCtrl::IsDropSource(HTREEITEM hItem)
{
  return !IsDrive(hItem);
}

BOOL CTreeFileCtrl::IsDragging()
{
  return (m_pilDrag != NULL);
}

void CTreeFileCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
  CRect clientRect;
  GetClientRect(&clientRect);

  if (clientRect.PtInRect(point))
    EndDragging(FALSE);
  else
    EndDragging(TRUE);
	 
  //Let the parent class do its thing	
	CTreeCtrl::OnLButtonUp(nFlags, point);
}

void CTreeFileCtrl::EndDragging(BOOL bCancel)
{
  if (IsDragging())
  {
    KillTimer(m_nTimerID);

    CImageList::DragLeave(this);
    CImageList::EndDrag();
    ReleaseCapture();

    delete m_pilDrag;
    m_pilDrag = NULL;

    //Remove drop target highlighting
    SelectDropTarget(NULL);

    m_hItemDrop = GetDropTarget(m_hItemDrop);
    if (m_hItemDrop == NULL)
      return;

    if (!bCancel)
    {
      //Also need to make the change on disk
      CString sFromPath = ItemToPath(m_hItemDrag);
      CString sToPath = ItemToPath(m_hItemDrop);

      int nFromLength = sFromPath.GetLength();
      int nToLength = sToPath.GetLength();
      SHFILEOPSTRUCT shfo;
      ZeroMemory(&shfo, sizeof(SHFILEOPSTRUCT));
      shfo.hwnd = GetSafeHwnd();

      if ((GetKeyState(VK_CONTROL) & 0x8000))
        shfo.wFunc = FO_COPY;
      else
        shfo.wFunc = FO_MOVE;

      shfo.fFlags = FOF_SILENT | FOF_NOCONFIRMMKDIR;
      //Undo is not allowed if the SHIFT key is held down
      if (!(GetKeyState(VK_SHIFT) & 0x8000))
        shfo.fFlags |= FOF_ALLOWUNDO;

      TCHAR* pszFrom = new TCHAR[nFromLength + 2];
      _tcscpy(pszFrom, sFromPath);
      pszFrom[nFromLength+1] = _T('\0');
      shfo.pFrom = pszFrom;

      TCHAR* pszTo = new TCHAR[nToLength + 2];
      _tcscpy(pszTo, sToPath);
      pszTo[nToLength+1] = _T('\0');
      shfo.pTo = pszTo;

      //Let the shell perform the actual deletion
      BOOL bSuccess = ((SHFileOperation(&shfo) == 0) && (shfo.fAnyOperationsAborted == FALSE));

      //Free up the memory we had allocated
      delete [] pszFrom;
      delete [] pszTo;

      if (bSuccess)
      {
        //Only copy the item in the tree if there is not an item with the same
        //text under m_hItemDrop
        CString sText = GetItemText(m_hItemDrag);
        if (!HasChildWithText(m_hItemDrop, sText))
        {
          //Do the actual copy
          BOOL bHadChildren = (GetChildItem(m_hItemDrop) != NULL);
          CopyBranch(m_hItemDrag, m_hItemDrop);

          //Update the children indicator for the folder we just dropped into
          if (!bHadChildren)
          {
            TV_ITEM tvItem;
            tvItem.hItem = m_hItemDrop;
            tvItem.mask = TVIF_CHILDREN;  
            tvItem.cChildren = 1;
            SetItem(&tvItem);
          }
        }

        BOOL bExpanded = (GetChildItem(m_hItemDrop) != NULL); 
        if (shfo.wFunc == FO_MOVE)
        {
          //Get the parent of the item we moved prior to deleting it
          HTREEITEM hParent = GetParentItem(m_hItemDrag);

          //Delete the item we just moved
          DeleteItem(m_hItemDrag);

          //Update the children indicator for the item we just dragged from
          BOOL bHasChildren = (GetChildItem(hParent) != NULL);
          if (hParent && !bHasChildren)
          {
            TV_ITEM tvItem;
            tvItem.hItem = hParent;
            tvItem.mask = TVIF_CHILDREN;  
            tvItem.cChildren = 0;
            SetItem(&tvItem);
          }
        }
        SetSelectedPath(sToPath, bExpanded);
      }
    }
  }
}

BOOL CTreeFileCtrl::HasChildWithText(HTREEITEM hParent, const CString& sText)
{
  HTREEITEM hChild = GetChildItem(hParent);
  while (hChild)
  {
    CString sItemText = GetItemText(hChild);
    if (sItemText.CompareNoCase(sText) == 0)
      return TRUE;
    hChild = GetNextSiblingItem(hChild);
  }
  return FALSE;
}

HTREEITEM CTreeFileCtrl::CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
  //Get the details of the item to copy
  TV_INSERTSTRUCT tvstruct;
  tvstruct.item.hItem = hItem;
  tvstruct.item.mask = TVIF_CHILDREN | TVIF_HANDLE | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM | TVIF_STATE;
  GetItem(&tvstruct.item);
  CString sText = GetItemText(hItem);
  tvstruct.item.cchTextMax = sText.GetLength();
  tvstruct.item.pszText = sText.GetBuffer(tvstruct.item.cchTextMax);

  //Insert the item at the proper location
  tvstruct.hParent = htiNewParent;
  tvstruct.hInsertAfter = htiAfter;
  tvstruct.item.mask |= TVIF_TEXT;
  HTREEITEM hNewItem = InsertItem(&tvstruct);

  //Don't forget to release the CString buffer  
  sText.ReleaseBuffer();

  return hNewItem;
}

HTREEITEM CTreeFileCtrl::CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter)
{
  HTREEITEM hNewItem = CopyItem(htiBranch, htiNewParent, htiAfter);
  HTREEITEM hChild = GetChildItem(htiBranch);
  while (hChild != NULL)
  {
    //recursively transfer all the items
    CopyBranch(hChild, hNewItem);
    hChild = GetNextSiblingItem(hChild);
  }
  return hNewItem;
}

void CTreeFileCtrl::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent != m_nTimerID)
  {
	  CTreeCtrl::OnTimer(nIDEvent);
    return;
  }

  //Show the dragging effect
  POINT pt;
  GetCursorPos(&pt);
  RECT rect;
  GetClientRect(&rect);
  ClientToScreen(&rect);
  CImageList::DragMove(pt);

  HTREEITEM hFirstItem = GetFirstVisibleItem();
  CRect ItemRect;
  GetItemRect(hFirstItem, &ItemRect, FALSE);
  if (pt.y < (rect.top + (ItemRect.Height()*2)) && pt.y > rect.top)
  {
    //we need to scroll up
    CImageList::DragShowNolock(FALSE);
    SendMessage(WM_VSCROLL, SB_LINEUP);
    EnsureVisible(hFirstItem);
    SelectDropTarget(hFirstItem);
    m_hItemDrop = hFirstItem;
    CImageList::DragShowNolock(TRUE);
  }
  else if (pt.y > (rect.bottom - (ItemRect.Height()*2)) && pt.y < rect.bottom)
  {
    //we need to scroll down
    CImageList::DragShowNolock(FALSE);
    SendMessage(WM_VSCROLL, SB_LINEDOWN);
    HTREEITEM hLastItem = hFirstItem;
    int nCount = GetVisibleCount();
    for (int i=0; i<(nCount-1); i++)
      hLastItem = GetNextVisibleItem(hLastItem);
    SelectDropTarget(hLastItem);
    EnsureVisible(hLastItem);
    m_hItemDrop = hLastItem;
    CImageList::DragShowNolock(TRUE);
  }

  //Expand the item if the timer ticks has expired
  if (m_TimerTicks == 3)
  {
    m_TimerTicks = 0;
    Expand(m_hItemDrop, TVE_EXPAND);
  }

  //Expand the selected item if it is collapsed and
  //the timeout has occurred
  TV_ITEM tvItem;
  tvItem.hItem = m_hItemDrop;
  tvItem.mask = TVIF_HANDLE | TVIF_CHILDREN | TVIF_STATE;
  tvItem.stateMask = TVIS_EXPANDED;
  GetItem(&tvItem);
  if (tvItem.cChildren && ((tvItem.state & TVIS_EXPANDED) == 0))
  {
    m_TimerTicks++;
  }
}



void DDX_FileTreeControl(CDataExchange* pDX, int nIDC, CTreeFileCtrl& ctrlFileTree, DWORD dwFlags)
{
  HWND hWndCtrl = pDX->PrepareCtrl(nIDC);
  if (!pDX->m_bSaveAndValidate && ctrlFileTree.m_hWnd == NULL) // not subclassed yet
  {
    if (!ctrlFileTree.SubclassWindow(hWndCtrl))
    {
      ASSERT(FALSE);      // possibly trying to subclass twice ?
      AfxThrowNotSupportedException();
    }
  }
  ctrlFileTree.SetFlags(dwFlags);
}

void DDX_FileTreeValue(CDataExchange* pDX, CTreeFileCtrl& ctrlFileTree, CString& sItem)
{
  if (pDX->m_bSaveAndValidate)
    sItem = ctrlFileTree.GetSelectedPath();
  else
    ctrlFileTree.SetSelectedPath(sItem);
}

