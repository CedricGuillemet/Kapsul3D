#if !defined(AFX_NUMEDIT_H__7482F7FF_A479_11D2_A6A7_00600844997A__INCLUDED_)
#define AFX_NUMEDIT_H__7482F7FF_A479_11D2_A6A7_00600844997A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NumEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumEdit window

#ifndef CLASS_EXPORT
	#define CLASS_EXPORT
#endif

class KAPSUL_DESC CNumEdit : public CEdit
{
	DECLARE_DYNAMIC(CNumEdit)
// Construction
public:
	CNumEdit();

// Attributes
public:
	enum {VALID = 0x00, OUT_OF_RANGE = 0x01, INVALID_CHAR = 0x02, MINUS_PLUS = 0x03};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void ChangeAmount(int step);
	virtual float GetDelta();
	virtual void SetDelta(float delta);
	virtual void GetRange(float &min, float &max)const; 
	virtual void SetRange(float min, float max);
	virtual void Verbose(BOOL v);
	virtual BOOL Verbose()const; 
	virtual int IsValid()const; 
	virtual int IsValid(const CString &str)const; 

	virtual BOOL SetValue(float val);
	virtual float GetValue()const; 
	virtual ~CNumEdit();

	// Generated message map functions
protected:
	virtual CString& ConstructFormat(CString &str, float num);
	BYTE m_NumberOfNumberAfterPoint;
	BOOL m_Verbose;
	float m_Delta, m_MinValue, m_MaxValue;
	//{{AFX_MSG(CNumEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMEDIT_H__7482F7FF_A479_11D2_A6A7_00600844997A__INCLUDED_)
