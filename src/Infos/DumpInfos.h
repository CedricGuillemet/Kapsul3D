#if !defined(AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
#define AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DumpInfos.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDumpInfos dialog
#include "resource.h"
class CDumpInfos : public CDialog
{
// Construction
public:
	CDumpInfos(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDumpInfos)
	enum { IDD = IDD_MODDIAG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDumpInfos)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDumpInfos)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DUMPINFOS_H__A4074657_9EA2_4EB9_95A3_3A9B19FEB15E__INCLUDED_)
