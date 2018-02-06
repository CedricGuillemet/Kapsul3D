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

#if !defined(AFX_KSLID_H__3CEA1A77_5366_479E_AC1F_BE5CAC9E89C8__INCLUDED_)
#define AFX_KSLID_H__3CEA1A77_5366_479E_AC1F_BE5CAC9E89C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KSlid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKSlid window

class KAPSUL_DESC CKSlid : public CWnd
{
// Construction
public:
	CKSlid();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKSlid)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetPos2(int val);
	void SetPos1(int val);
	int GetPos2(void);
	int GetPos1(void);
	void SetRange2(int _min2,int _max2);
	void SetRange1(int _min1,int _max1);
	virtual ~CKSlid();
	// Generated message map functions
protected:
	//{{AFX_MSG(CKSlid)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

    bool IsDouble;
    int Pos1,Pos2;
    int Min1,Min2,Max1,Max2;
    bool P1Track,P2Track;
    float Pos1A;
    float Pos2A;
    float NewPos1,NewPos2;
    POINT TrackPT;
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSLID_H__3CEA1A77_5366_479E_AC1F_BE5CAC9E89C8__INCLUDED_)
