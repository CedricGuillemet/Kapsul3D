#if !defined(AFX_NUMSPINCTRL_H__C2BD95A2_A482_11D2_A6A7_00600844997A__INCLUDED_)
#define AFX_NUMSPINCTRL_H__C2BD95A2_A482_11D2_A6A7_00600844997A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NumSpinCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumSpinCtrl window
#include "NumEdit.h"

#ifndef CLASS_EXPORT
	#define CLASS_EXPORT
#endif

class KAPSUL_DESC CNumSpinCtrl : public CSpinButtonCtrl
{
	DECLARE_DYNAMIC(CNumSpinCtrl)
// Construction
public:
	CNumSpinCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumSpinCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void SetDelta(float delta);
	virtual float GetDelta();
	virtual void SetBuddy(CNumEdit *edit);
	virtual CNumEdit* GetBuddy() const;
	virtual void GetRange(float &lower, float& upper ) const;
	virtual void SetRange(float nLower, float nUpper );
	virtual float GetPos();
	virtual void SetPos(float val);
	virtual ~CNumSpinCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNumSpinCtrl)
	afx_msg void OnDeltapos(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMSPINCTRL_H__C2BD95A2_A482_11D2_A6A7_00600844997A__INCLUDED_)
