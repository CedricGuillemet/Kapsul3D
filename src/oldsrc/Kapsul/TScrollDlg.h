// TScrollDlg.h : header file
//

#if !defined(AFX_TSCROLLDLG_H__47E5BC25_CFE6_4A78_9092_9E9A49E6B882__INCLUDED_)
#define AFX_TSCROLLDLG_H__47E5BC25_CFE6_4A78_9092_9E9A49E6B882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CoolScroll.h"
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CTScrollDlg dialog

class CTScrollDlg : public CDialog
{
// Construction
public:
	CTScrollDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTScrollDlg)
	enum { IDD = IDD_TSCROLL_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTScrollDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	public:
	//CCoolScroll cool;
    void SetPlug(HWND dahwnd,CWnd *Parent);
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTScrollDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );

    virtual void OnCancel( );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSCROLLDLG_H__47E5BC25_CFE6_4A78_9092_9E9A49E6B882__INCLUDED_)
