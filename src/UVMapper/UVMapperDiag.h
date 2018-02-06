#if !defined(AFX_UVMapperDiag_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
#define AFX_UVMapperDiag_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUVMapperDiag dialog
#include "UVMapper.h"

class CUVMapperDiag : public CDialog
{
// Construction
public:
	CUVMapperDiag(CWnd* pParent = NULL);   // standard constructor
	CKUVMapper *m_Plugin;
// Dialog Data
	//{{AFX_DATA(CUVMapperDiag)
	enum { IDD = IDD_UVEDIT };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUVMapperDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );
	

	// Generated message map functions
	//{{AFX_MSG(CUVMapperDiag)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelobject();
	afx_msg void OnLoadmap();
	afx_msg void OnCheck1();
	afx_msg void OnSavebmp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif 
