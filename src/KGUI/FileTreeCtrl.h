/*
Module : FileTreeCtrl.H
Purpose: Interface for an MFC class which provides a tree control similiar 
         to the left hand side of explorer

Copyright (c) 1999 - 2000 by PJ Naughter.  
All rights reserved.

*/


//#include "PakFile.h"
////////////////////////////////// Macros / Defines  ///////////////////////

#ifndef __FILETREECTRL_H__
#define __FILETREECTRL_H__



//flags used to control how the DDX_FileTreeControl routine works

const DWORD TFC_SHOWFILES       = 0x0001;   //Control will show files aswell as show folders
const DWORD TFC_ALLOWDRAGDROP   = 0x0002;   //Control allows drag / drop
const DWORD TFC_ALLOWRENAME     = 0x0004;   //Control allows renaming of items
const DWORD TFC_ALLOWOPEN       = 0x0008;   //Control allows items to be "opened" by the shell
const DWORD TFC_ALLOWPROPERTIES = 0x0010;   //Control allows the "Properties" dialog to be shown
const DWORD TFC_ALLOWDELETE     = 0x0020;   //Control allows items to be deleted




/////////////////////////// Classes /////////////////////////////////


//Class which encapsulates access to the System image list which contains
//all the icons used by the shell to represent the file system

class CSystemImageList
{
public:
//Constructors / Destructors
  CSystemImageList();
  ~CSystemImageList();

//Methods
  CImageList& GetImageList();

protected:
  CImageList m_ImageList;
  static int m_nRefCount;
};



//Class which implements the tree control representation of the file system

class KAPSUL_DESC CTreeFileCtrl : public CTreeCtrl
{
public:
//Constructors / Destructors
	CTreeFileCtrl();
	virtual ~CTreeFileCtrl();

//Public methods
  void      SetRootFolder(const CString& sPath);
  CString   GetRootFolder() const { return m_sRootFolder; };
  CString   ItemToPath(HTREEITEM hItem);
  CString   GetSelectedPath();
  HTREEITEM SetSelectedPath(const CString& sPath, BOOL bExpanded=FALSE);
  void      SetShowFiles(BOOL bFiles);
  BOOL      GetShowFiles() const { return m_bShowFiles; };
  void      SetAllowDragDrop(BOOL bAllowDragDrop) { m_bAllowDragDrop = bAllowDragDrop; };
  BOOL      GetAllowDragDrop() const { return m_bAllowDragDrop; };
  void      SetAllowRename(BOOL bAllowRename) { m_bAllowRename = bAllowRename; };
  BOOL      GetAllowRename() const { return m_bAllowRename; };
  void      SetAllowOpen(BOOL bAllowOpen) { m_bAllowOpen = bAllowOpen; };
  BOOL      GetAllowOpen() const { return m_bAllowOpen; };
  void      SetAllowProperties(BOOL bAllowProperties) { m_bAllowProperties = bAllowProperties; };
  BOOL      GetAllowProperties() const { return m_bAllowProperties; };
  void      SetAllowDelete(BOOL bAllowDelete) { m_bAllowDelete = bAllowDelete; };
  BOOL      GetAllowDelete() const { return m_bAllowDelete; };
  BOOL      IsFile(HTREEITEM hItem);
  BOOL      IsFolder(HTREEITEM hItem);
  BOOL      IsDrive(HTREEITEM hItem);
  BOOL      IsFile(const CString& sPath);
  BOOL      IsFolder(const CString& sPath);
  BOOL      IsDrive(const CString& sPath);
  BOOL      Rename(HTREEITEM hItem);
  BOOL      ShowProperties(HTREEITEM hItem);
  BOOL      Delete(HTREEITEM hItem);
  BOOL      Open(HTREEITEM hItem);
  void      SetFlags(DWORD dwFlags);
  BOOL      GetChecked(HTREEITEM hItem) const;
  BOOL      SetChecked(HTREEITEM hItem, BOOL fCheck);



//Debug / Assert help
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	//{{AFX_MSG(CTreeFileCtrl)
	afx_msg void OnFileProperties();
	afx_msg void OnFileRename();
	afx_msg void OnUpdateFileRename(CCmdUI* pCmdUI);
	afx_msg void OnFileOpen();
	afx_msg void OnFileDelete();
	afx_msg void OnUpdateFileDelete(CCmdUI* pCmdUI);
	afx_msg void OnViewRefresh();
	afx_msg void OnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateFileProperties(CCmdUI* pCmdUI);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateFileOpen(CCmdUI* pCmdUI);
	//}}AFX_MSG
  afx_msg LRESULT OnPopulateTree(WPARAM wParam, LPARAM lParam); 
  void UpOneLevel();
  void OnUpdateUpOneLevel(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

protected:
	//{{AFX_VIRTUAL(CTreeFileCtrl)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

  void      DisplayPath(const CString& sPath, HTREEITEM hParent, BOOL bUseSetRedraw=TRUE);
  void      DisplayDrives(HTREEITEM hParent, BOOL bUseSetRedraw=TRUE);
  HTREEITEM InsertDriveItem(CString& sDrive, HTREEITEM hParent);
  int       GetIconIndex(const CString& sFilename);
  int       GetIconIndex(HTREEITEM hItem);
  int       GetSelIconIndex(const CString& sFilename);
  int       GetSelIconIndex(HTREEITEM hItem);
  BOOL      HasGotSubEntries(const CString& sDirectory);
  BOOL      HasChildWithText(HTREEITEM hParent, const CString& sText);
  HTREEITEM InsertFileItem(const CString& sFile, const CString& sPath, HTREEITEM hParent);
  HTREEITEM FindSibling(HTREEITEM hParent, const CString& sItem);
  BOOL      IsDropSource(HTREEITEM hItem);
  BOOL      IsDragging();
  HTREEITEM GetDropTarget(HTREEITEM hItem);
  void      EndDragging(BOOL bCancel);
  HTREEITEM CopyItem(HTREEITEM hItem, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST);
  HTREEITEM CopyBranch(HTREEITEM htiBranch, HTREEITEM htiNewParent, HTREEITEM htiAfter = TVI_LAST);
  static int CompareByFilenameNoCase(CString& element1, CString& element2) ;

  CSystemImageList m_SysImageList;
  CString          m_sRootFolder;
  BOOL             m_bShowFiles;
  HTREEITEM        m_hItemDrag;
  HTREEITEM        m_hItemDrop;
  CImageList*      m_pilDrag;
  UINT             m_nTimerID;
  HCURSOR          m_DropCopyCursor;
  HCURSOR          m_NoDropCopyCursor;
  HCURSOR          m_DropMoveCursor;
  HCURSOR          m_NoDropMoveCursor;
  UINT             m_TimerTicks;
  BOOL             m_bAllowDragDrop;
  BOOL             m_bAllowRename;
  BOOL             m_bAllowOpen;
  BOOL             m_bAllowProperties;
  BOOL             m_bAllowDelete;
  HTREEITEM        m_hSelItem;
};



//MFC Data exchange routines

void DDX_FileTreeControl(CDataExchange* pDX, int nIDC, CTreeFileCtrl& ctrlFileTree, DWORD dwFlags);
void DDX_FileTreeValue(CDataExchange* pDX, CTreeFileCtrl& ctrlFileTree, CString& sItem);



#endif //__FILETREECTRL_H__
