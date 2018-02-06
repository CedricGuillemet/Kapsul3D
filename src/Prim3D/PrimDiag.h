#if !defined(AFX_PRIMDIAG_H__7A64FC70_A9AC_4CDC_81B9_AF33764DCE7B__INCLUDED_)
#define AFX_PRIMDIAG_H__7A64FC70_A9AC_4CDC_81B9_AF33764DCE7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrimDiag.h : header file
//
#include "Mapping.h"
#include "Primitive.h"
#include "TreeParam.h"
#include "Parameters.h"
/////////////////////////////////////////////////////////////////////////////
// CPrimDiag dialog

class CPrimDiag : public CDialog
{
// Construction
public:
	CPrimDiag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrimDiag)
	enum { IDD = IDD_MODDIAG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrimDiag)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

public:

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CPrimDiag)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIMDIAG_H__7A64FC70_A9AC_4CDC_81B9_AF33764DCE7B__INCLUDED_)
