#if !defined(AFX_PATH_H__883A7C18_59C3_4F76_86DF_82940B92D5A2__INCLUDED_)
#define AFX_PATH_H__883A7C18_59C3_4F76_86DF_82940B92D5A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Path.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPath dialog

class CPath : public CDialog
{
// Construction
public:
	CPath(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPath)
	enum { IDD = IDD_PATH };
	CButton	m_Capping;
	CButton	m_SplinedShape;
	CButton	m_SplinedPath;
	CNumEdit	m_EditShape;
	CNumEdit	m_EditPath;
	CNumSpinCtrl	m_SpinShape;
	CNumSpinCtrl	m_SpinPath;
	CStatic	m_PathName;
	CStatic	m_ShapeName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
public:
	CKPluginModifier *m_Plugin;
// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );
	// Generated message map functions
	//{{AFX_MSG(CPath)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPath();
	afx_msg void OnRotate();
	afx_msg void OnShape();
	afx_msg void OnSplinedpath();
	afx_msg void OnSplinedshape();
	afx_msg void OnScale();
	afx_msg void OnRotatey();
	afx_msg void OnRotatez();
	afx_msg void OnScaley();
	afx_msg void OnCapping();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATH_H__883A7C18_59C3_4F76_86DF_82940B92D5A2__INCLUDED_)
