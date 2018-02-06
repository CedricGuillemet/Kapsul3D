#if !defined(AFX_MODEBAR_H__86BC1651_762C_4E2E_B1C3_9133C651F4C8__INCLUDED_)
#define AFX_MODEBAR_H__86BC1651_762C_4E2E_B1C3_9133C651F4C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModeBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModeBar window

class CModeBar : public CMyToolBar
{
// Construction
public:
	CModeBar();

// Attributes
public:

   CComboBox m_wndSnap;

// Operations
public:

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CMyToolBar)
    public:

    //}}AFX_VIRTUAL
// Implementation
public:
	virtual ~CModeBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CModeBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODEBAR_H__86BC1651_762C_4E2E_B1C3_9133C651F4C8__INCLUDED_)
