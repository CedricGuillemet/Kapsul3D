// Kapsul Core Library
// Copyright © 1999 - 2001, Cédric Guillemet
//
// Contact: lacrapul@club-internet.fr
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#if !defined(AFX_PAINTZONE_H__3E0C378B_E43A_44F3_8C5B_7983721A0AD6__INCLUDED_)
#define AFX_PAINTZONE_H__3E0C378B_E43A_44F3_8C5B_7983721A0AD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaintZone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPaintZone window

class __declspec( dllexport ) CPaintZone : public CStatic
{
// Construction
public:
	CPaintZone();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaintZone)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetVal(int s1,int s2);
	virtual ~CPaintZone();
    unsigned char Brush[32][32];


	// Generated message map functions
protected:
	//{{AFX_MSG(CPaintZone)
	afx_msg void OnPaint();
	//}}AFX_MSG

    int Size1,Size2;

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINTZONE_H__3E0C378B_E43A_44F3_8C5B_7983721A0AD6__INCLUDED_)
