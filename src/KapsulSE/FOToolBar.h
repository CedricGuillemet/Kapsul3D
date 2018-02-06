/*
	FOToolBar.h
*/

#if !defined(AFX_FOTOOLBAR_H__677F5047_E1FD_42C6_B3AB_C25B33EF8972__INCLUDED_)
#define AFX_FOTOOLBAR_H__677F5047_E1FD_42C6_B3AB_C25B33EF8972__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FOToolBar.h : header file
//
#include "ChoosePrim.h"
#include "ChooseSel.h"
#include "ChooseMode.h"
#include <memory>
#include <vector>
using namespace std;

class CFlyout;	// declaration

/////////////////////////////////////////////////////////////////////////////
// CFOToolBar window

class CFOToolBar : public CToolBar
{
// Construction
public:
	CFOToolBar();

// Attributes
public:

// Operations
public:
	void Init();
	void addFlyout(UINT buttonIndex, UINT toolbarID);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFOToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFOToolBar();

	// Generated message map functions
protected:

	//{{AFX_MSG(CFOToolBar)
		// NOTE - the ClassWizard will add and remove member functions here.
		afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
		afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
		afx_msg void OnMouseMove( UINT nFlags, CPoint point );
		afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	vector<pair<UINT, UINT> > ids;	// first - button ID second - toolbar ID

	int index;
	UINT nID;
public:
	CChoosePrim m_flyout;
	CChooseSel m_flyout2;
	CChooseMode m_flyout3;
	bool toDrawDropDownArrows;


};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOTOOLBAR_H__677F5047_E1FD_42C6_B3AB_C25B33EF8972__INCLUDED_)
