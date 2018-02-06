//////////////////////////////////////////////////////////////////////////
// Office2000Dlg.cpp : implementation file
// 
// Windows 2000 / Office 2000 style file dialog.
// 
// This WILL work on Win 95 / 98 / NT 4 / NT 5 (2000) / WinME
// 
// Original code by Norm Almond []
//					David Wulff [dwulff@battleaxesoftware.com]
// 
// Update History:
//    07 Sep 2000 - David Wulff, Opps, I lost the previous update history.
//    08 Sep 2000 - David Wulff, Lots of changes, most significant is the
//                  .. addition of an optional preview panel, allowing you
//                  .. to preview bitmap images before opening/saving.
//    14 Oct 2000 - Joel Bernard, Provided a better CenterWindow function.
//                  David Wulff, Fixed memory leaks, added support for
//                  .. previewing non-bitmap images. (code by Wes Rogers)
//                  Other misc. changes.
//                  Anatoly Danekin, Shortcut path resolution.
//    13 Dec 2000 - David Wulff, Added Visual Studio .NET look
//    24 Mar 2001 - David Wulff, miscellaneous drawing updates
//                  Tak^Shoran, working sizing support for Win 98/2000
//                  Identified very bad flickering problem
//    31 Mar 2001 - David Wulff, Fixed resizing so it will work for dialogs
//                  .. with preview panels.  Tidied up all of the code (it
//                  .. was a big mess) and added standard function headers.
//                  .. Removed compile-time only modification of sizing
//                  .. support and VS.NET style
//    27 Jul 2001 - David Wulff, now when you select a non-image file, or
//                  .. a folder, the preview pane is cleared.  Added a
//                  .. handler for the CDN_TYPECHANGE message, so you can
//                  .. customise the OK button's drop-down menu.
//    03 Aug 2001 - David Wulff, added new functions to allow you to modify
//                  .. the listctrl view type during runtime.
//    04 Aug 2001 - David Wulff, only selects a sidebar button if the
//                  .. directory is selected.  Misc changes.
//////////////////////////////////////////////////////////////////////////
// Note, all dates given in this file are in the standard UK format (D:M:Y)

#include "stdafx.h"
#include "winuser.h"
#include "dlgs.h"
#include "cmn_resource.h"
#include "Office2000Dlg.h"

//#define _USE_HTMLHELP		// uncomment to have context help for the sidebar.
#define CONTROL_GAP		5	// the default 'gap' between controls

#ifdef _USE_HTMLHELP
#include <htmlhelp.h>
#pragma comment ( lib, "htmlhelp.lib" )
#pragma message ("  NOTE: HTMLHelp support is included.")
#endif

#define ID_SHOW_PREVIEW		3420 // this is the ID for the "preview?" checkbox

BOOL BXFileDialog::m_bClear = FALSE;
TCHAR BXFileDialog::m_szFile[] = {"\0"};

BOOL bDotNetUI = FALSE;

#pragma warning ( disable : 4244 ) // float -> int conversion warnings

/////////////////////////////////////////////////////////////////////////////
// BXFileDialog

IMPLEMENT_DYNAMIC(BXFileDialog, CFileDialog)
BEGIN_MESSAGE_MAP(BXFileDialog, CFileDialog)
//{{AFX_MSG_MAP(BXFileDialog)
ON_WM_SIZE()
ON_WM_HELPINFO()
ON_WM_MEASUREITEM()
ON_BN_CLICKED(IDC_CHECK_PREVIEW, OnClickedPreview)
ON_BN_CLICKED(ID_SHOW_PREVIEW, OnShowPreview)
ON_WM_PAINT()
//}}AFX_MSG_MAP
ON_COMMAND(ID_BTN_HISTORY, OnHistoryClicked)
ON_COMMAND(ID_BTN_PERSONAL, OnPersonalClicked)
ON_COMMAND(ID_BTN_DESKTOP, OnDesktopClicked)
ON_COMMAND(ID_BTN_FAVORITES, OnFavoritesClicked)
ON_COMMAND(ID_BTN_WEBFOLDERS, OnWebFoldersClicked)
ON_COMMAND_RANGE(ID_START, ID_END, OnMyOk)
ON_COMMAND(IDOK, OnOk)
END_MESSAGE_MAP()

/************************************************************************/
/*  BXFileDialog														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff, Norm Almond								*/
/*  Description: Class constructor										*/
/*	Revisions:	 														*/
/************************************************************************/
BXFileDialog::BXFileDialog(BOOL bOpenFileDialog, BOOL bPreview, BOOL bSizing,
						   LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
						   DWORD dwFlags, LPCTSTR lpszFilter,
						   CWnd* pParentWnd) :
CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags,
			lpszFilter, pParentWnd)
{
	m_IsOpen = bOpenFileDialog;
	m_bShowPreview = m_bPreview = bPreview;
	m_bFirst = TRUE;

	m_ofn.hInstance         = AfxGetInstanceHandle();
	m_ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_WIN2K_FILEDIALOG);
	m_ofn.Flags             = dwFlags | OFN_EXPLORER | OFN_ENABLETEMPLATE |
								OFN_ENABLEHOOK | OFN_HIDEREADONLY |
								(bSizing ? OFN_ENABLESIZING : 0);


	HINSTANCE hInst=AfxFindResourceHandle(MAKEINTRESOURCE(IDD_WIN2K_FILEDIALOG),RT_DIALOG);
	m_ofn.hInstance=hInst;
	m_ofn.lpTemplateName=MAKEINTRESOURCE(IDD_WIN2K_FILEDIALOG);
	m_ofn.Flags |= OFN_EXPLORER | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK | OFN_HIDEREADONLY;
}

/************************************************************************/
/*  ~BXFileDialog														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff, Norm Almond								*/
/*  Description: Class destructor										*/
/*	Revisions:	 														*/
/************************************************************************/
BXFileDialog::~BXFileDialog()
{
}

/************************************************************************/
/*  OnInitDialog														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff, Norm Almond								*/
/*  Description: WM_INITDIALOG handler									*/
/*	Revisions:	 														*/
/************************************************************************/
BOOL BXFileDialog::OnInitDialog() 
{
	CFileDialog::OnInitDialog();
	
	// create the imagelist and load the sidebar icons
	m_IL.Create(IDB_ICONS, 32, 1, RGB(255, 0, 255));
	
	// center this dialog on the main window
	CWnd* pMainWnd = AfxGetMainWnd();
	CenterWindowOnOwner(pMainWnd);
	
	// store the width of the static control (set it via the dialog editor)
	CWnd* pWndOutLookBar = GetDlgItem(IDC_OUTLOOK_BAR_PLACEHOLDER);
	CRect rcOLBClient;
	pWndOutLookBar->GetClientRect(rcOLBClient);
	m_SBWidth = rcOLBClient.Width();
	
	return TRUE;
}

/************************************************************************/
/*  OnNotify															*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff, Norm Almond								*/
/*  Description: WM_NOTIFY handler										*/
/*	Revisions:															*/
/************************************************************************/
BOOL BXFileDialog::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	OFNOTIFY* pNotify = (OFNOTIFY*)lParam;
	
	switch(pNotify->hdr.code)
	{
	case CDN_INITDONE:
		{
			SetActiveButton(&m_btnPersonal);
			m_edtFile.SubclassDlgItem(edt1,GetParent());

			OnFileTypeChange(m_ofn.nFilterIndex);

			return TRUE;
		}
		
		// [DW]: Remind me why we need these again?  CFileDialog already
		// .. provides these handlers, so why replace them? [4/8/2001]
	case CDN_SELCHANGE:
		{
			// the listctrl selection has changed
			OnFileNameChange();
			return TRUE;
		}
		
	case CDN_FOLDERCHANGE:
		{
			// the 'root' folder has changed
			OnFolderChange();
			return TRUE;
		}
		
	case CDN_TYPECHANGE:
		{
			// the file type/s to view has changed
			OnFileTypeChange(pNotify->lpOFN->nFilterIndex);
			return TRUE;
		}
	}
	
	return FALSE;
}

/************************************************************************/
/*  GetListCtrl															*/
/*																		*/
/*  Created:     03:8:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Helper function to return the listctrl					*/
/*	Revisions:	 														*/
/************************************************************************/
CListCtrl* BXFileDialog::GetListCtrl()
{
	CListCtrl* pLCtrl;
	BOOL bWin2k = FALSE;
	OSVERSIONINFO osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	
	::GetVersionEx(&osvi);
	
	// TODO [DW]: Check to see which one is needed for Windows ME [3/8/2001]
	
	if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT &&
		osvi.dwMajorVersion == 5)
		bWin2k = TRUE;
	
	// ok, here's the deal:  On Windows 2000, the listctrl we want is a child
	// .. of another, custom, control.  So, if we are running on Windows 2000,
	// .. we will need to take this into account.
	
	// THIS TOOK ME FOUR DAYS TO FIND!  Dammit Microsoft - why can't you stick
	// .. to your own guidelines?  Thank God for Spy++!
	
	if (bWin2k)
	{
		CWnd *pWnd = GetParent()->GetDlgItem(lst2);
		pLCtrl = (CListCtrl*)pWnd->GetDlgItem(1);
	}
	else
		pLCtrl = (CListCtrl*)GetParent()->GetDlgItem(lst1);
	
	return pLCtrl;
}

/************************************************************************/
/*  SetListCtrlView														*/
/*																		*/
/*  Created:     03:8:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Set the listctrl style during runtime					*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::SetListCtrlView(DWORD dwNewStyle)
{
	CListCtrl* pLCtrl = GetListCtrl();
	DWORD dwStyle = GetWindowLong (pLCtrl->GetSafeHwnd(), GWL_STYLE);
	
	// TODO [DW]: LVS_REPORT doesn't work properly! [3/8/2001]
	if ((dwStyle & LVS_TYPEMASK) != dwNewStyle)
		SetWindowLong (pLCtrl->GetSafeHwnd(), GWL_STYLE,
		(dwStyle & ~LVS_TYPEMASK) | dwNewStyle);
}

/************************************************************************/
/*  GetActiveButton														*/
/*																		*/
/*  Created:     07:8:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Returns a pointer to the acitve sidebar button			*/
/*	Revisions:	 														*/
/************************************************************************/
BXSelBtn* BXFileDialog::GetActiveButton()
{
	static TCHAR szPath[MAX_PATH];
	LPITEMIDLIST lpIDList;
	
	// "History"
	SHGetSpecialFolderLocation(0, CSIDL_RECENT, &lpIDList);
	SHGetPathFromIDList(lpIDList, szPath);
	
	if (GetFolderPath().CompareNoCase(CString(szPath)) == 0)
		return &m_btnHistory;
	
	// "Favourites"
	SHGetSpecialFolderLocation(0, CSIDL_FAVORITES, &lpIDList);
	SHGetPathFromIDList(lpIDList, szPath);
	
	if (GetFolderPath().CompareNoCase(CString(szPath)) == 0)
		return &m_btnFavourites;
	
	// "My Documents"
	SHGetSpecialFolderLocation(0, CSIDL_PERSONAL, &lpIDList);
	SHGetPathFromIDList(lpIDList, szPath);
	
	if (GetFolderPath().CompareNoCase(CString(szPath)) == 0)
		return &m_btnPersonal;
	
	// "Desktop"
	SHGetSpecialFolderLocation(0, CSIDL_DESKTOP, &lpIDList);
	SHGetPathFromIDList(lpIDList, szPath);
	
	if (GetFolderPath().CompareNoCase(CString(szPath)) == 0)
		return &m_btnDeskTop;
	
	// "Network Neighbourhood"
	SHGetSpecialFolderLocation(0, CSIDL_NETHOOD, &lpIDList);
	SHGetPathFromIDList(lpIDList, szPath);
	
	if (GetFolderPath().CompareNoCase(CString(szPath)) == 0)
		return &m_btnWebFolders;

	return NULL; // we are not in a 'default' directory
}

/************************************************************************/
/*  OnFileNameChange													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Called when the file name is changed or a new file is	*/
/*				 .. selected.											*/
/*	Revisions:	 27:7:2001 - David Wulff, Clears the preview panel when	*/
/*				 .. the selection changes								*/
/************************************************************************/
void BXFileDialog::OnFileNameChange()
{
	CString strFilePath = (LPCSTR)GetPathName();
	SHFILEINFO shfi;
	CListCtrl* pLCtrl = GetListCtrl();
	POSITION pos = pLCtrl->GetFirstSelectedItemPosition();

	// we wont bother checking for multiple selections, as we can't preview
	// .. mulitple files!
	if (pos != NULL)
	{
		CString strSelName = pLCtrl->GetItemText(pLCtrl->GetNextSelectedItem(pos), 0);
		
		// HACK [DW]: Not the best way to do this! [3/8/2001]
		if (strSelName.Find(_T(".")) == -1)
		{
			if(m_bPreview)
				m_strPreviewPath = _T("\0"); // set image file to null
			
			InvalidateRect(PreviewRect);

			return;
		}
	}
	
	if (!GetFileName().IsEmpty())
	{
		// if we have selected a shortcut, we must resolve it first
		if (SHGetFileInfo((LPCSTR)strFilePath, 0, &shfi, sizeof(shfi),
			SHGFI_DISPLAYNAME | SHGFI_TYPENAME) &&
			!lstrcmp(shfi.szTypeName, "Shortcut"))
		{
			ResolveShortcut(strFilePath);
		}
		
		if(m_bPreview)
			m_strPreviewPath = strFilePath;
		
		InvalidateRect(PreviewRect);
	}
}

/************************************************************************/
/*  OnFolderChange														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Called when the folder is changed						*/
/*	Revisions:	 04:8:2001 - David Wulff, only select a sidebar button	*/
/*				 .. after initialisation if the directory is selected	*/
/************************************************************************/
void BXFileDialog::OnFolderChange()
{
	// if a 'default' directory is selected, activate the appropriate
	// .. sidebar button
	SetActiveButton(GetActiveButton());
}

/************************************************************************/
/*  OnClickedPreview													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Called when the 'Preview'	checkbox is clicked			*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnClickedPreview()
{
	m_bPreview = checkBox.GetCheck() == 1 ? TRUE : FALSE;
}

/************************************************************************/
/*  OnPaint																*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: WM_PAINT handler										*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnPaint() 
{
	CPaintDC dc(this);
	
	// if we are drawing the image preview, draw a 3D border to simulate
	// .. a preview control, and render the image within in
	if (m_bShowPreview)
	{
		// deflate rect to include border
		CRect rect(PreviewRect.left + 1, PreviewRect.top + 1,
			PreviewRect.right - 1, PreviewRect.bottom - 1);
		
		dc.Draw3dRect(&PreviewRect,::GetSysColor(COLOR_BTNSHADOW),
			::GetSysColor(COLOR_BTNHILIGHT));
		
		if(m_bPreview)
			DrawImage(&dc, m_strPreviewPath, PreviewRect.CenterPoint(),
			GetParent()->m_hWnd, rect);
	}
	
	// if we are using the VS.NET UI style, we must draw the sidebar
	// .. border ourselves
	if (!bDotNetUI)
	{
		CRect rcWnd;
		CWnd* pWndOutLookBar = GetDlgItem(IDC_OUTLOOK_BAR_PLACEHOLDER);
		
		pWndOutLookBar->GetWindowRect(&rcWnd);
		ScreenToClient(&rcWnd);
		rcWnd.top += (m_btnHeight * 5);
		
		dc.Draw3dRect(&rcWnd, ::GetSysColor(COLOR_BTNSHADOW),
			::GetSysColor(COLOR_BTNHILIGHT));
		dc.FillRect(&rcWnd, &CBrush(::GetSysColor(COLOR_APPWORKSPACE)));
	}
}

/************************************************************************/
/*  OnHistoryClicked													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Called when the specified side bar button is clicked	*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnHistoryClicked()
{
	SetSpecialDirectory(CSIDL_RECENT);
	SetActiveButton(&m_btnHistory);
}

/************************************************************************/
/*  OnPersonalClicked													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Called when the specified side bar button is clicked	*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnPersonalClicked()
{
	SetSpecialDirectory(CSIDL_PERSONAL);
	SetActiveButton(&m_btnPersonal);
}

/************************************************************************/
/*  OnDesktopClicked													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Called when the specified side bar button is clicked	*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnDesktopClicked()
{
	SetSpecialDirectory(CSIDL_DESKTOP);
	SetActiveButton(&m_btnDeskTop);
}

/************************************************************************/
/*  OnFavoritesClicked													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Called when the specified side bar button is clicked	*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnFavoritesClicked()
{
	SetSpecialDirectory(CSIDL_FAVORITES);
	SetActiveButton(&m_btnFavourites);
}

/************************************************************************/
/*  OnWebFoldersClicked													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Called when the specified side bar button is clicked	*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnWebFoldersClicked()
{
	SetSpecialDirectory(CSIDL_NETHOOD);
	SetActiveButton(&m_btnWebFolders);
}

/************************************************************************/
/*  SetSpecialDirectory													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Navigates to a passed shell director based on the side */
/*				 .. bar button pressed.									*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::SetSpecialDirectory(int nFolder)
{
	LPITEMIDLIST lpIDList;
	
	// get the "special folder" path for the passed folder
	SHGetSpecialFolderLocation(0, nFolder, &lpIDList);
	SHGetPathFromIDList(lpIDList, m_szFile);
	
	CWnd* pWnd = GetParent()->GetDlgItem(edt1);
	CListCtrl* pLCtrl = (CListCtrl*)GetParent()->GetDlgItem(lst1);
	
	// Simulate a refresh to clear the current file name
	// .. this can take a LONG time if the history folder is selected!
	//
	// If you find a better way of doing this, please let me know.
	pLCtrl->PostMessage(WM_KEYDOWN,VK_F5,0x0020001);
	pLCtrl->PostMessage(WM_KEYUP,VK_F5,0xC0020001);
	
	// Add selection to edit box
	pWnd->SetWindowText(m_szFile);
	
	// Simulate a 'Return' key to make selection
	m_bClear = TRUE;
	pWnd->PostMessage(WM_KEYDOWN,VK_RETURN,0x0020001);
	pWnd->PostMessage(WM_KEYUP,VK_RETURN,0xC0020001);
}

/************************************************************************/
/*  SetActiveButton														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      Norm Almond											*/
/*  Description: Sets the currently active side bar button				*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::SetActiveButton(BXSelBtn* btn)
{
	m_btnHistory.SetState(FALSE);
	m_btnPersonal.SetState(FALSE);
	m_btnDeskTop.SetState(FALSE);
	m_btnFavourites.SetState(FALSE);
	m_btnWebFolders.SetState(FALSE);
	
	// if we don't have a valid button, don't select any of them
	if (btn != NULL)
		btn->SetState(TRUE);
}

/************************************************************************/
/*  OnSize																*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff, Norm Almond, Tak^Shoran					*/
/*  Description: WM_SIZE handler.										*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnSize(UINT nType, int cx, int cy) 
{	
	CRect rc;	
	
	CFileDialog::OnSize(nType, cx, cy);
	
	GetWindowRect(&rc);
	
	// The first time the dialog is sized needs special handling (we set
	// .. up the new OK button here, for example.
	if (m_bFirst)
	{	
		InitialReSize(0, 0, cx, cy);
		m_bFirst = false;		
	}
	else if (m_bSizing)
		ReSize(rc.left, rc.top, cx, cy);
}

/************************************************************************/
/*  InitialReSize														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff, Norm Almond								*/
/*  Description: Repositions and subclasses, etc, the dialog controls	*/
/*				 .. when the dialog is first intialised.				*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::InitialReSize(int x, int y, int cx, int cy) 
{
	// position "Look In" label and combo, and the toolbar
	CRect rcDlgCl;
	GetClientRect(&rcDlgCl);
	
	CWnd* pWndOutLookBar = GetDlgItem(IDC_OUTLOOK_BAR_PLACEHOLDER);
	CRect rcOLBClient, rcOLBWindow, rcWnd;
	pWndOutLookBar->GetClientRect(rcOLBClient);
	pWndOutLookBar->GetWindowRect(rcOLBWindow);
	
	int eRight = rcDlgCl.right - CONTROL_GAP;
	int eLeft = rcDlgCl.left + CONTROL_GAP;
	int eTop = rcDlgCl.top + CONTROL_GAP;
	int eBot = rcDlgCl.bottom - CONTROL_GAP;
	int iTmp;
	
	CRect rcWin;
	GetWindowRect(&rcWin);
	
	iTmp = eLeft + m_SBWidth + CONTROL_GAP;
	
	CWnd* pListCtrl = GetParent()->GetDlgItem(lst1);
	CWnd* pComboCtrl = GetParent()->GetDlgItem(cmb2);
	CWnd* pLabel = GetParent()->GetDlgItem(stc4);	
	
	pLabel = GetParent()->GetDlgItem(stc4);
	pLabel->SetWindowPos(0, 40, eTop + 3, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	
	// TODO [DW]: Replace this toolbar with our own, as differnt OS versions
	// .. have different command available. [4/8/2001]
	HWND hWnd = FindWindowEx(GetParent()->m_hWnd, NULL,
		"ToolbarWindow32", NULL);
	CWnd wndToolbar;
	wndToolbar.Attach(hWnd);
	
	pComboCtrl->SetWindowPos(0, iTmp, eTop, 250, 180, SWP_NOZORDER);
	
	wndToolbar.SetWindowPos(0, iTmp + CONTROL_GAP + 250, eTop, 0, 0,
		SWP_NOSIZE | SWP_NOZORDER);
	wndToolbar.Detach();

	// Offset controls
	CWnd* pWnd;
	CWnd* pBar = GetDlgItem(IDC_OUTLOOK_BAR_PLACEHOLDER);
	CRect rcBar;
	pBar->GetWindowRect(rcBar);
	
	if (m_bShowPreview)
		pListCtrl->SetWindowPos(0, iTmp, eTop + 22 + CONTROL_GAP,
		eLeft + 250 - CONTROL_GAP,
		eBot - (CONTROL_GAP * 3) - (22 * 2) - eTop - 22, SWP_NOZORDER);
	else
		pListCtrl->SetWindowPos(0, iTmp, eTop + 22 + CONTROL_GAP,
		eRight - iTmp, eBot - (CONTROL_GAP * 3) - (22 * 2) - eTop - 22,
		SWP_NOZORDER);
	
	pWnd = GetParent()->GetDlgItem(stc3); // File Name label
	pWnd->SetWindowPos(0, iTmp, eBot - (CONTROL_GAP * 2) - (18 * 2), 60,
		15, SWP_NOZORDER);
	
	pWnd = GetParent()->GetDlgItem(stc2); // File type label
	pWnd->SetWindowPos(0, iTmp, eBot - 18, 60, 15, SWP_NOZORDER);
	
	iTmp += 70;
	
	pWnd = GetParent()->GetDlgItem(edt1); // File Name
	pWnd->SetWindowPos(0, iTmp, eBot - CONTROL_GAP - (22 * 2),
		(eRight - 90 - 30 - iTmp), 22, SWP_NOZORDER);
	
	pWnd = GetParent()->GetDlgItem(cmb1); // File Type
	pWnd->SetWindowPos(0, iTmp, eBot - 22, (eRight - 90 - 30 - iTmp), 150,
		SWP_NOZORDER);
	
	// Add our bitmap menu button
	HideControl(IDOK); // undocumented CFileDialog function
	
	if (m_IsOpen)
	{
		m_btn.Create("&Open",WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON,
			CRect(0, 0, 0, 0), this, ID_START);
		m_btn.SetButtonImage(IDB_FILEOPEN, RGB(255,0,255));
	}
	else
	{
		m_btn.Create("&Save",WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON,
			CRect(0, 0, 0, 0), this, ID_START);
		m_btn.SetButtonImage(IDB_FILESAVE, RGB(255,0,255));
	}		
	
	m_btn.SetWindowPos(0, eRight - 90, eBot - CONTROL_GAP - (22 * 2), 90,
		22, SWP_NOZORDER);
	m_btn.ShowWindow(SW_SHOW);
	
	
	pWnd = GetParent()->GetDlgItem(IDCANCEL);
	pWnd->SetWindowPos(0, eRight - 90, eBot - 22, 90, 22, SWP_NOZORDER);

	// Add outlook style directory selection buttons
	pWndOutLookBar->SetWindowPos(0, eLeft, eTop + 22 + CONTROL_GAP,
		m_SBWidth, eBot - eTop - CONTROL_GAP - 22, SWP_NOZORDER);
	
	iTmp = rcOLBClient.Width();
	pWndOutLookBar->GetClientRect(rcOLBClient);
	
	m_btnHeight = rcOLBClient.Height() /  5;
	
	rcWnd.SetRect(0, 0, iTmp, m_btnHeight);
	
	if (!m_btnHistory)
	{
		m_btnHistory.Create("History", WS_CHILD | WS_VISIBLE, rcWnd,
			pWndOutLookBar, ID_BTN_HISTORY, &m_IL,0);  
		m_btnHistory.m_Enabled = TRUE;
	}
	
	rcWnd.OffsetRect(0, m_btnHeight);
	
	if (!m_btnPersonal)
	{
		m_btnPersonal.Create("My Documents", WS_CHILD | WS_VISIBLE, rcWnd,
			pWndOutLookBar, ID_BTN_PERSONAL, &m_IL,2);
		m_btnPersonal.m_Enabled = TRUE;
	}
	
	rcWnd.OffsetRect(0, m_btnHeight);
	
	if (!m_btnDeskTop)
	{
		m_btnDeskTop.Create("Desktop", WS_CHILD | WS_VISIBLE, rcWnd,
			pWndOutLookBar, ID_BTN_DESKTOP, &m_IL,1);
		m_btnDeskTop.m_Enabled = TRUE;
	}
	
	rcWnd.OffsetRect(0, m_btnHeight);
	
	if (!m_btnFavourites)
	{
		m_btnFavourites.Create("Favourites", WS_CHILD | WS_VISIBLE, rcWnd,
			pWndOutLookBar, ID_BTN_FAVORITES, &m_IL,3);
		m_btnFavourites.m_Enabled = TRUE;
	}
	
	rcWnd.OffsetRect(0, m_btnHeight);
	if (!m_btnWebFolders)
	{
		m_btnWebFolders.Create("Web Folders", WS_CHILD | WS_VISIBLE, rcWnd,
			pWndOutLookBar, ID_BTN_WEBFOLDERS, &m_IL,4);
		m_btnWebFolders.m_Enabled = TRUE;
	}
	
	// Added for preview
	checkBox.Create("&Preview",
		(m_bShowPreview ? WS_CHILD|WS_VISIBLE : WS_CHILD) | WS_TABSTOP |
		BS_AUTOCHECKBOX, CRect(0,0,0,0), this, IDC_CHECK_PREVIEW);
	checkBox.SetWindowPos(0,eRight - 90,
		eBot - (CONTROL_GAP * 3) - (22 * 2) - 22, 90, 22, SWP_NOZORDER);
	checkBox.SetFont(GetFont());
	checkBox.SetCheck(m_bPreview);
	
	PreviewRect = CRect(
		(eLeft * 2) + m_SBWidth + 250 + CONTROL_GAP,
		eTop + 22 + CONTROL_GAP,
		eRight,
		eBot - (CONTROL_GAP * 4) - (22 * 3)
		);
	
	m_nPreviewBoxWidth = PreviewRect.Width();
}

/************************************************************************/
/*  OnHelpInfo															*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: WM_HELPINFO handler.									*/
/*	Revisions:	 														*/
/************************************************************************/
BOOL BXFileDialog::OnHelpInfo(HELPINFO* pHelpInfo) 
{
#ifdef _USE_HTMLHELP
	if (pHelpInfo->iCtrlId == IDC_CHECK_PREVIEW ||
		pHelpInfo->iCtrlId == ID_BTN_HISTORY ||
		pHelpInfo->iCtrlId == ID_BTN_PERSONAL ||
		pHelpInfo->iCtrlId == ID_BTN_DESKTOP ||
		pHelpInfo->iCtrlId == ID_BTN_FAVORITES ||
		pHelpInfo->iCtrlId == ID_BTN_WEBFOLDERS)
		DoPopupHelp(pHelpInfo->iCtrlId, pHelpInfo->MousePos);
	else
		CFileDialog::OnHelpInfo(pHelpInfo);
#else
	
	CFileDialog::OnHelpInfo(pHelpInfo);
#endif
	
	return TRUE;
}

/************************************************************************/
/*  DoPopupHelp															*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: If applicable, will show a popup help window for the 	*/
/*				 .. non-standard controls this dialog adds.				*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::DoPopupHelp(int nID, CPoint pt)
{
	if (nID != IDC_STATIC) // Don't show help for un-named controls
	{
		CString strString;
		
		strString.LoadString(nID);
		DoPopupHelp(strString, pt);
	}
}

/************************************************************************/
/*  DoPopupHelp															*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: If applicable, will show a popup help window for the 	*/
/*				 .. non-standard controls this dialog adds.				*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::DoPopupHelp(CString strString, CPoint pt)
{
#ifdef _USE_HTMLHELP
	HH_POPUP hPop;
	CString str;
	
	hPop.cbStruct = sizeof(HH_POPUP);
	hPop.hinst = 0;
	
	hPop.idString = 0;
	
	if (strString == _T(""))
		hPop.pszText = "No help topic is associated with this item";
	else
		hPop.pszText = strString;
	
	hPop.pt = pt;
	hPop.clrForeground = GetSysColor(COLOR_INFOTEXT);
	hPop.clrBackground = GetSysColor(COLOR_INFOBK);
	hPop.rcMargins = CRect(-1, -1, -1, -1);
	hPop.pszFont = "Arial, 8, , ";
	
	HtmlHelp(NULL, NULL, HH_DISPLAY_TEXT_POPUP, (DWORD) (HH_POPUP*) &hPop);
#endif
}

void BXFileDialog::OnOk()
{
}

void BXFileDialog::OnMyOk(UINT nID)
{
	// Simulate the user hiting the enter key
	PostMessage(WM_KEYDOWN,VK_RETURN,0x0020001);
	PostMessage(WM_KEYUP,VK_RETURN,0xC0020001);

	EndDialog(nID);
}

void BXFileDialog::OnShowPreview()
{
	m_bShowPreview = !m_bShowPreview;
	
	CRect rcDlg;
	GetWindowRect(rcDlg);
	
	ReSize(rcDlg.left, rcDlg.top, rcDlg.Width(), rcDlg.Height());
}

/************************************************************************/
/*  CenterWindowOnOwner													*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      Joel Bernard											*/
/*  Description: A better center window function						*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::CenterWindowOnOwner(CWnd *pWndToCenterOn)
{
	// Get the client rectangle of the window on which we want to center
	// Make sure the pointer is not NULL first
	if (pWndToCenterOn == NULL)
		return;
	
	CRect rectToCenterOn;
	pWndToCenterOn->GetWindowRect(&rectToCenterOn);
	
	// Get this window's area
	CRect rectSubDialog;
	GetWindowRect(&rectSubDialog);
	
	// Now rectWndToCenterOn contains the screen rectangle of the window
	// .. pointed to by pWndToCenterOn.  Next, we apply the same centering
	// .. algorithm as does CenterWindow()
	
	// find the upper left of where we should center to
	int xLeft = (rectToCenterOn.left + rectToCenterOn.right) / 2 -
		rectSubDialog.Width() / 2;
	int yTop = (rectToCenterOn.top + rectToCenterOn.bottom) / 2 -
		rectSubDialog.Height() / 2;
	
	// Move the window to the correct coordinates with SetWindowPos()
	GetParent()->SetWindowPos(NULL, xLeft, yTop, -1, -1,
		SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

/************************************************************************/
/*  ResolveShortcut														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      Anatoly Danekin										*/
/*  Description: Resolves the passed shortcut							*/
/*	Revisions:	 														*/
/************************************************************************/
BOOL BXFileDialog::ResolveShortcut(CString& strFile)
{
	HRESULT         hres;
	IShellLink*     psl;
	char            szGotPath[MAX_PATH];
	WIN32_FIND_DATA wfd;
	
	// Get a pointer to the IShellLink interface.
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
		IID_IShellLink, (void**)&psl);
	
	if (SUCCEEDED(hres))
	{
		IPersistFile* ppf;
		
		// Get a pointer to the IPersistFile interface.
		hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
		
		if (SUCCEEDED(hres))
		{
			WORD wsz[MAX_PATH];
			
			// Ensure that the string is Unicode.
			MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strFile, -1, wsz,
				MAX_PATH);
			
			// Load the shortcut.
			hres = ppf->Load(wsz, STGM_READ);
			if (SUCCEEDED(hres))
			{
				// Resolve the link.
				hres = psl->Resolve(GetParent()->m_hWnd, SLR_ANY_MATCH);
				if (SUCCEEDED(hres))
				{
					// Get the path to the link target.
					hres = psl->GetPath(szGotPath, MAX_PATH,
						(WIN32_FIND_DATA*)&wfd, SLGP_SHORTPATH );
					if (SUCCEEDED(hres))
						strFile = szGotPath;
				}
			}
			// Release the pointer to the IPersistFile interface.
			ppf->Release();
		}
		
		// Release the pointer to the IShellLink interface.
		psl->Release();
	}
	
	return SUCCEEDED(hres);
}

// a couple of helper functions:
int GetBiggest(int n1, int n2)
{
	if (n1 > n2)	return n1;
	if (n2 > n1)	return n2;
	return -1; // equal
}

float GetSmallestF(float f1, float f2)
{
	if (f1 < f2)	return f1;
	if (f2 < f1)	return f2;
	return -1.0f; // equal
}

/************************************************************************/
/*  DrawImage															*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      Wes Rogers, David Wulff								*/
/*  Description: Draws the specified image in the specified rectangle	*/
/*	Revisions:	 27:7:2001 - David Wulff, image now resizes properly and*/
/*				 .. centers												*/
/************************************************************************/
BOOL BXFileDialog::DrawImage(CDC* pDC, CString csFile, CPoint ptCenter,
							 HWND hWnd, CRect rectImage)
{
    if (pDC == NULL || csFile.IsEmpty() || hWnd == NULL)
        return FALSE;
	
    LPPICTURE gpPicture = NULL;
	
    if (LoadPictureFile((LPCTSTR)csFile, &gpPicture))
    {
        //Get width and height of picture
        long hmWidth  = 0;
        long hmHeight = 0;
		
        gpPicture->get_Width(&hmWidth);
        gpPicture->get_Height(&hmHeight);
		
		// [DW - 27:7:2001]
		CSize szImg(hmWidth, hmHeight);
		pDC->HIMETRICtoLP(&szImg);
		
		rectImage.DeflateRect(0, 0, 1, 1);
		
		int nLeft, nTop, nRight, nBottom;
		CRect rcDest = rectImage, rcSrc = CRect(0, 0, szImg.cx, szImg.cy);
		
		// if the image wont fit without being shrunk...
		if (GetBiggest(rcDest.Width(), rcSrc.Width()) == rcSrc.Width() ||
			GetBiggest(rcDest.Height(), rcSrc.Height()) == rcSrc.Height())
		{
			float nDX = rcDest.Width(), nDY = rcDest.Height(),
				nSX = rcSrc.Width(), nSY = rcSrc.Height();
			float nModX = nDX / nSX;
			float nModY = nDY / nSY;
			float nMod = GetSmallestF(nModX, nModY);
			
			// float -> int conversion
			nRight = rcSrc.Width() * nMod;
			nBottom = -(rcSrc.Height() * nMod);
			nLeft = rcDest.left + (rcDest.Width() / 2) - (nRight / 2);
			nTop = rcDest.top + (rcDest.Height() / 2) - (nBottom / 2);
		}
		else
		{
			// center the image
			nLeft = rcDest.left + (rcDest.Width() / 2) - (szImg.cx / 2);
			nTop = rcDest.top + (rcDest.Height() / 2) - (szImg.cy / 2) + szImg.cy;
			nRight = szImg.cx;
			nBottom = -(szImg.cy);
		}
		// [/DW - 27:7:2001]
		
        HRESULT hrP = gpPicture->Render(pDC->m_hDC, nLeft, nTop, nRight, nBottom,
			0, 0, hmWidth, hmHeight, NULL);
		
        gpPicture->Release();
		
        if (SUCCEEDED(hrP))
            return TRUE;
    }
	
    return FALSE;
}

/************************************************************************/
/*  LoadPictureFile														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      Wes Rogers												*/
/*  Description: Loads the specified picture into the passed LPPICTURE	*/
/*	Revisions:	 														*/
/************************************************************************/
BOOL BXFileDialog::LoadPictureFile(LPCTSTR szFile, LPPICTURE* pgpPicture)
{
    // open file
    HANDLE hFile = CreateFile(szFile, GENERIC_READ, 0, NULL, OPEN_EXISTING,
		0, NULL);
	
    if (hFile == INVALID_HANDLE_VALUE)
        return FALSE;
	
    // get file size
    DWORD dwFileSize = GetFileSize(hFile, NULL);
	
    if (dwFileSize == (DWORD)-1)
    {
        CloseHandle(hFile);
        return FALSE;
    }
	
    LPVOID pvData = NULL;
	
    // alloc memory based on file size
    HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwFileSize);
	
    if (hGlobal == NULL)
    {
        CloseHandle(hFile);
        return FALSE;
    }
	
    pvData = GlobalLock(hGlobal);
	
    if (pvData == NULL)
    {
        GlobalUnlock(hGlobal);
        CloseHandle(hFile);
        return FALSE;
    }
	
    DWORD dwBytesRead = 0;
	
    // read file and store in global memory
    BOOL bRead = ReadFile(hFile,
		pvData,
		dwFileSize,
		&dwBytesRead,
		NULL);
	
    GlobalUnlock(hGlobal);
    CloseHandle(hFile);
	
    if (!bRead)
        return FALSE;
	
    LPSTREAM pstm = NULL;
	
    // create IStream* from global memory
    HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pstm);
	
    if (!(SUCCEEDED(hr)))
    {
        if (pstm != NULL)
            pstm->Release();
		
        return FALSE;
    }
	
    else if (pstm == NULL)
        return FALSE;
	
	// Create IPicture from image file
	if (*pgpPicture)
		(*pgpPicture)->Release();
	
    hr = ::OleLoadPicture(pstm,
		dwFileSize,
		FALSE,
		IID_IPicture,
		(LPVOID *)&(*pgpPicture));
	
    if (!(SUCCEEDED(hr)))
    {
		pstm->Release();
        return FALSE;
    }
	
    else if (*pgpPicture == NULL)
    {
		pstm->Release();
        return FALSE;
    }
	
    pstm->Release();
	
    return TRUE;
}

/************************************************************************/
/*  ReSize																*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff, Tak^Shoran								*/
/*  Description: Called by the WM_SIZING override to reposition the		*/
/*				 .. dialog's controls.									*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::ReSize(int x, int y, int cx, int cy)
{
	// note: the listctrl is automatically resized by the underlying class
	CWnd* pWnd;
	CRect rcDlgCl, rcWin, rc1, rc2, rcLoc;
	
	GetClientRect(&rcDlgCl);
	GetWindowRect(&rcWin);
	
	int eRight = rcDlgCl.right - CONTROL_GAP;
	int eLeft = rcDlgCl.left + CONTROL_GAP;
	int eTop = rcDlgCl.top + CONTROL_GAP;
	int eBot = rcDlgCl.bottom - CONTROL_GAP;
	
	// Move preview box
	if (m_bShowPreview)
	{
		CWnd* pListCtrl = GetParent()->GetDlgItem(lst1);
		CRect rcList;
		pListCtrl->GetClientRect(&rcList);
		
		checkBox.SetWindowPos(0, eRight - 98,
			eBot - (CONTROL_GAP * 4) - (22 * 4), 90, 22, SWP_NOZORDER);
		
		PreviewRect.bottom = eBot - (CONTROL_GAP * 5) - (22 * 4);
		PreviewRect.right = eRight - CONTROL_GAP - 3;
		PreviewRect.left = PreviewRect.right - m_nPreviewBoxWidth;
	}
	
	// Move button
	m_btn.GetWindowRect(&rc1);
	ScreenToClient(&rc1);
	
	pWnd = GetParent()->GetDlgItem(IDCANCEL);
	pWnd->GetWindowRect(&rc2);
	ScreenToClient(&rc2);
	
	rc1.left  = rc2.left;
	rc1.right = rc2.right;
	
	m_btn.SetWindowPos(0, rc1.left, rc1.top, rc1.Width(), rc1.Height(),
		SWP_NOZORDER);
	
	// Move outbar
	CWnd* pWndOutLookBar = GetDlgItem(IDC_OUTLOOK_BAR_PLACEHOLDER);
	pWndOutLookBar->GetWindowRect(&rc1);
	ScreenToClient(&rc1);
	
	rc1.bottom = rcDlgCl.Height() - rc1.top;
	
	pWndOutLookBar->SetWindowPos(0, rc1.left, rc1.top, rc1.Width(),
		rc1.Height(), SWP_NOZORDER);
	
	Invalidate();
}

/************************************************************************/
/*  SetAppearance														*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Pass in the eAppearance to use	when drawing the dialog	*/
/*				 .. and buttons, etc.									*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::SetAppearance(eAppearance eApp)
{
	m_eAppearance = eApp;
	bDotNetUI = (m_eAppearance == eAppearance::APPEARANCE_VSDOTNET);
}

/************************************************************************/
/*  OnFileTypeChange													*/
/*																		*/
/*  Created:     27:7:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Handler for the CDN_TYPECHANGE message					*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileDialog::OnFileTypeChange(DWORD dwNewFilterIndex)
{
	// you can override this function to provide custom control over
	// .. the OK button's drop-down menu, depending on the file type
	// .. selected.
	
	// E.G:
#if 0
	// destroy the current menu (remove all items)
	m_btn.m_menu.DestroyMenu();
	
	// recreate the popup menu
	m_btn.m_menu.CreatePopupMenu();
	
	// add the new items, depending on the file type selected
	switch(dwNewFilterIndex)
	{
	case 0:
		m_btn.AddMenuItem(ID_START,"&Open",0);
		m_btn.AddMenuItem(ID_START+1,"Open with &Filter",0);
		break;
	case 1:
		m_btn.AddMenuItem(ID_START,"&Open",0);
		break;
	case 2:
		m_btn.AddMenuItem(ID_START,"&Open",0);
		m_btn.AddMenuItem(ID_START+1,"Open As &HTML",0);
		break;
	default:
		break; // do nothing
	}
#endif
}

//////////////////////////////////////////////////////////////////////////
// BXFileEdit (public CEdit)
//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*  BXFileEdit															*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Class constructor										*/
/*	Revisions:	 														*/
/************************************************************************/
BXFileEdit::BXFileEdit()
{
}


/************************************************************************/
/*  ~BXFileEdit															*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: Class destructor										*/
/*	Revisions:	 														*/
/************************************************************************/
BXFileEdit::~BXFileEdit()
{
}

BEGIN_MESSAGE_MAP(BXFileEdit, CEdit)
//{{AFX_MSG_MAP(BXFileEdit)
ON_WM_KEYUP()
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/************************************************************************/
/*  OnKeyUp																*/
/*																		*/
/*  Created:     31:3:2001												*/
/*  Author:      David Wulff											*/
/*  Description: WM_KEYUP handler for the new edit control				*/
/*	Revisions:	 														*/
/************************************************************************/
void BXFileEdit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (BXFileDialog::m_bClear)
	{
		SetWindowText("");
		BXFileDialog::m_bClear = FALSE;
		SetSel(0,-1);
	}
	
	CEdit::OnKeyUp(nChar, nRepCnt, nFlags);
}

#pragma warning ( default : 4244 ) // float -> int conversion warnings
