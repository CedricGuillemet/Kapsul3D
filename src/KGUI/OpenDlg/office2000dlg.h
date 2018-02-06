/////////////////////////////////////////////////////////////////////////////
// Office2000Dlg.h : header file
// 
// Windows 2000 / Office 2000 style file dialog.
// 
// This WILL work on Win 95 / 98 / NT 4 / NT 5 (2000) / WinME
// 
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OFFICE2KDLG1_H__4DE1F584_3B00_4229_883C_EF4D507E5C9A__INCLUDED_)
#define AFX_OFFICE2KDLG1_H__4DE1F584_3B00_4229_883C_EF4D507E5C9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "kapsul3D.h"

// for backward compatability:
#define COffice2KDlg BXFileDialog
#define BXOffice2kDlg BXFileDialog

/////////////////////////////////////////////////////////////////////////////
// BXFileDialog dialog
#include "CoolBtn.h"
#include "SelBtn.h"

#define ID_START			34220
#define ID_END				34250

extern BOOL bDotNetUI;

/////////////////////////////////////////////////////////////////////////////
// BXFileEdit window

class BXFileEdit : public CEdit
{
// Construction
public:
	BXFileEdit();

// Implementation
public:
	virtual ~BXFileEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(BXFileEdit)
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

class KAPSUL_DESC BXFileDialog : public CFileDialog
{
	DECLARE_DYNAMIC(BXFileDialog)

public:
	CListCtrl* GetListCtrl();
	void SetListCtrlView(DWORD dwNewStyle);
	enum eAppearance
	{
		APPEARANCE_DEFAULT = 0,
		APPEARANCE_VSDOTNET,

		NUM_APPEARANCES
	};
	
	virtual ~BXFileDialog();

	BOOL DrawImage(CDC*    pDC,					//Device context
               CString csFile,					//Pathname to image file
               CPoint  ptCenter,				//Center point for image
               HWND    hWnd,					//Handle to view window
               CRect   rectImage);				//Display area rectangle

	BOOL LoadPictureFile(LPCTSTR szFile,		//Image file pathname
                     LPPICTURE* pgpPicture);	//Ptr to PICTURE for image

	BOOL ResolveShortcut(CString& strFile);
	void CenterWindowOnOwner(CWnd *pWndToCenterOn);
	void OnMyOk(UINT nID);
	void DoPopupHelp(CString strString, CPoint pt);
	void DoPopupHelp(int nID, CPoint pt);
	void SetAppearance(eAppearance eApp = eAppearance::APPEARANCE_DEFAULT);
	
	void SetActiveButton(BXSelBtn *btn);
	BXFileDialog(BOOL bOpenFileDialog = TRUE,
		BOOL bPreview = FALSE,
		BOOL m_bSizing = TRUE,
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	void SetSpecialDirectory(int nFolder);
	
	BXCoolBtn		m_btn;

	BXSelBtn*		m_pCurrent;
	BXSelBtn		m_btnHistory;
	BXSelBtn		m_btnPersonal;
	BXSelBtn		m_btnDeskTop;
	BXSelBtn		m_btnFavourites;
	BXSelBtn		m_btnWebFolders;

	CImageList		m_IL;

	BXFileEdit		m_edtFile;

	static BOOL		m_bClear;
	static TCHAR	m_szFile[MAX_PATH];

	int				m_btnHeight;
	int				m_nPreviewBoxWidth;
	int				m_SBWidth;
	
	CString			m_csFileName;
	CString			m_strPreviewPath;
	
	CButton			checkBox;
	CButton			m_ToolbarBtn;
	
	CRect			PreviewRect;
	
	BOOL			m_bCanResize;
	BOOL			m_IsOpen;
	BOOL			m_bPreview;
	BOOL			m_bShowPreview;
	BOOL			m_bSizing;
	bool			m_bFirst;
	
	eAppearance		m_eAppearance;

private:

	BXSelBtn* GetActiveButton();

protected:
	//{{AFX_MSG(BXFileDialog)
	afx_msg void OnClickedPreview();
	afx_msg void OnShowPreview();
	afx_msg void OnPaint();

	virtual BOOL OnInitDialog();
	virtual void OnOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG

	virtual void OnFileNameChange();
	virtual void OnFolderChange();
	virtual void OnFileTypeChange(DWORD dwNewFilterIndex);

	afx_msg void OnHistoryClicked();
	afx_msg void OnPersonalClicked();
	afx_msg void OnDesktopClicked();
	afx_msg void OnFavoritesClicked();
	afx_msg void OnWebFoldersClicked();
	
	BOOL OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult );
	void InitialReSize(int x, int y, int cx, int cy);
	void ReSize(int x, int y, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_Office2KDlg1_H__4DE1F584_3B00_4229_883C_EF4D507E5C9A__INCLUDED_)
