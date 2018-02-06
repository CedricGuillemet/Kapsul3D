// tlctrlDlg.h : header file
//

#if !defined(AFX_TLCTRLDLG_H__AC6AC76D_D22C_4620_9DEC_B604395E437B__INCLUDED_)
#define AFX_TLCTRLDLG_H__AC6AC76D_D22C_4620_9DEC_B604395E437B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resource.h"
#include "Desk.h"
/////////////////////////////////////////////////////////////////////////////
// CSelName dialog

class CSelName : public CDialog
{
// Construction
public:
	CSelName(CWnd* pParent = NULL);	// standard constructor
	Desk *dk;
	void ListIt(void);

// Dialog Data
	//{{AFX_DATA(CSelName)
	enum { IDD = IDD_SELNAME };
	CListCtrl	m_List;
	CComboBox	m_Type;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:
	HICON m_hIcon;
    CImageList m_imglist;
	// Generated message map functions
	//{{AFX_MSG(CSelName)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnAll();
	afx_msg void OnNone();
	afx_msg void OnInvert();
	afx_msg void OnSelchangeListtype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TLCTRLDLG_H__AC6AC76D_D22C_4620_9DEC_B604395E437B__INCLUDED_)
