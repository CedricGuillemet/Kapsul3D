#if !defined(AFX_ANIMSKEL_H__05C43EA4_1794_4521_A489_60F08E7E19DB__INCLUDED_)
#define AFX_ANIMSKEL_H__05C43EA4_1794_4521_A489_60F08E7E19DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AnimSkel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAnimSkel dialog

class CAnimSkel : public CDialog
{
// Construction
public:
	CAnimSkel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimSkel)
	enum { IDD = IDD_ANIMS };
	CComboBox	m_ListAnims;
	CButton	m_MoveBone;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimSkel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnimSkel)
	afx_msg void OnAddanim();
	afx_msg void OnRenanim();
	afx_msg void OnDelanim();
	afx_msg void OnMovebone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANIMSKEL_H__05C43EA4_1794_4521_A489_60F08E7E19DB__INCLUDED_)
