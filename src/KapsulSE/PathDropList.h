#if !defined(AFX_PATHDROPLIST_H__9907EB41_8E23_442E_A5A9_B91DE16F0C54__INCLUDED_)
#define AFX_PATHDROPLIST_H__9907EB41_8E23_442E_A5A9_B91DE16F0C54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PathDropList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPathDropList window

class CPathDropList : public CListBox
{
// Construction
public:
	CPathDropList();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPathDropList)
	//}}AFX_VIRTUAL

// Implementation
public:
	void DeleteFiles();
	virtual ~CPathDropList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPathDropList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATHDROPLIST_H__9907EB41_8E23_442E_A5A9_B91DE16F0C54__INCLUDED_)

