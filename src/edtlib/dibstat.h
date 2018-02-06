/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1998 by Jorge Lodos
// All rights reserved
//
// Distribute and use freely, except:
// 1. Don't alter or remove this notice.
// 2. Mark the changes you made
//
// Send bug reports, bug fixes, enhancements, requests, etc. to:
//    lodos@cigb.edu.cu
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIBSTATIC_H__40E4BDE3_BD3A_11D1_89F4_0000E81D3D27__INCLUDED_)
#define AFX_DIBSTATIC_H__40E4BDE3_BD3A_11D1_89F4_0000E81D3D27__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DIBStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDIBStatic window

class EDITPADC_CLASS CDIBStatic : public CStatic
{
// Construction
public:
	CDIBStatic();

// Attributes
public:
	CDib m_DIB;

public:
	BOOL IsValidDib() const { return (m_DIB.IsValid()); }

// Operations
public:
	BOOL LoadDib(LPCTSTR lpszFileName);
	BOOL LoadDib(CFile& file);
	void UpdateDib();
	void RemoveDib() { m_DIB.Invalidate(); UpdateDib(); }
	
	BOOL DoRealizePalette(BOOL bForceBackGround);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDIBStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDIBStatic();

protected:
	void ClearDib();
	void PaintDib(BOOL bDibValid);

	// Generated message map functions
protected:
	//{{AFX_MSG(CDIBStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIBSTATIC_H__40E4BDE3_BD3A_11D1_89F4_0000E81D3D27__INCLUDED_)
