#ifndef __PSHEET2_INCLUDED__
#define __PSHEET2_INCLUDED__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CPropertySheet2

class CPropertySheet2 : public CPropertySheet
{
  DECLARE_DYNAMIC(CPropertySheet2)

// Construction
public:
  CPropertySheet2();

// Attributes
public:

// Operations
public:
  BOOL CheckKey(TCHAR cAccel);
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CPropertySheet2)
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CPropertySheet2();

  // Generated message map functions
protected:
  //{{AFX_MSG(CPropertySheet2)
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  BOOL PreTranslateMessage(MSG *pMsg);

  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __PSHEET2_INCLUDED__
