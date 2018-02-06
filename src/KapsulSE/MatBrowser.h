#if !defined(AFX_MATBROWSER_H__532EFB8D_D100_4DC6_9E4C_705D59F26A60__INCLUDED_)
#define AFX_MATBROWSER_H__532EFB8D_D100_4DC6_9E4C_705D59F26A60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatBrowser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatBrowser dialog
#include <vector>

class CMatBrowser : public CDialog
{
// Construction
public:
	CMatBrowser(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMatBrowser)
	enum { IDD = IDD_MATBROWSER };
	CComboBox	m_Choose;
	CProgressCtrl	m_Progress;
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatBrowser)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

public:

	BOOL GetImageFileNames();
	void DrawThumbnails();
	void ApplyTexture(CString TexName);
	void UpdateCBPath(void);
	void SelectTexture(CString TextureName);


	CImageList				m_ImageListThumb;		// image list holding the thumbnails
    std::vector<CString>	m_VectorImageNames;		// vector holding the image names
	int						m_nSelectedItem;
	CString					m_strImageDir;
	CString					m_Texture;

	CKScene					*m_Scene;
	// Generated message map functions
	//{{AFX_MSG(CMatBrowser)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeCbchoose();
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeydownList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATBROWSER_H__532EFB8D_D100_4DC6_9E4C_705D59F26A60__INCLUDED_)
