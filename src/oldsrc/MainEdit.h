#if !defined(AFX_MAINEDIT_H__4EDCDA52_75F9_476D_BEE7_DC1525657F57__INCLUDED_)
#define AFX_MAINEDIT_H__4EDCDA52_75F9_476D_BEE7_DC1525657F57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainEdit dialog

class CMainEdit : public CDialog
{
// Construction
public:
	CMainEdit(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMainEdit)
	enum { IDD = IDD_EDIT };
	CButton	m_Star;
	CButton	m_Quad;
	CButton	m_NGon;
	CButton	m_Line;
	CButton	m_Arc;
	//}}AFX_DATA

public:
    void UnSetPlugin(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CMainEdit)
	afx_msg void OnLine();
	afx_msg void OnArc();
	afx_msg void OnNgon();
	afx_msg void OnQuad();
	afx_msg void OnStar();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINEDIT_H__4EDCDA52_75F9_476D_BEE7_DC1525657F57__INCLUDED_)
