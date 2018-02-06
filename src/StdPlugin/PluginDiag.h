#if !defined(AFX_PLUGINDIAG_H__43E91472_F67C_4E4B_AB10_F5EDBAC4D61F__INCLUDED_)
#define AFX_PLUGINDIAG_H__43E91472_F67C_4E4B_AB10_F5EDBAC4D61F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PluginDiag.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPluginDiag dialog

class CPluginDiag : public CDialog
{
// Construction
public:
	CPluginDiag(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPluginDiag)
	enum { IDD = IDD_DIAG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPluginDiag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPluginDiag)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLUGINDIAG_H__43E91472_F67C_4E4B_AB10_F5EDBAC4D61F__INCLUDED_)
