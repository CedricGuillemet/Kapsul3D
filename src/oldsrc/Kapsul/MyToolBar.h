#if !defined(AFX_MYTOOLBAR_H__92EBC4B4_BC3E_4834_8572_8B341E5736BB__INCLUDED_)
#define AFX_MYTOOLBAR_H__92EBC4B4_BC3E_4834_8572_8B341E5736BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyToolBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyToolBar window

class CMyToolBar : public CToolBar
{
// Construction
public:
	CMyToolBar();

// Attributes
public:

// Operations
public:
    CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

    CSize CalcDynamicLayout(int nLength, DWORD dwMode);
    CSize CalcLayout(DWORD dwMode, int nLength= -1);
    void _GetButton(int nIndex, TBBUTTON* pButton) const;
    void _SetButton(int nIndex, TBBUTTON* pButton);
    void  SizeToolBar(TBBUTTON* pData, int nCount, int nLength, BOOL bVert= FALSE);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyToolBar)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTOOLBAR_H__92EBC4B4_BC3E_4834_8572_8B341E5736BB__INCLUDED_)
