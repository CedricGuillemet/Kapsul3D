#if !defined(AFX_INFOSSEL_H__F720BEC2_8811_48E2_AD63_EB7B989060DD__INCLUDED_)
#define AFX_INFOSSEL_H__F720BEC2_8811_48E2_AD63_EB7B989060DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfosSel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfosSel dialog

class CInfosSel : public CDialog
{
// Construction
public:
	CInfosSel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfosSel)
	enum { IDD = IDD_INFOSSEL };
	CStatic	m_Skeleton;
	CStatic	m_Shape;
	CStatic	m_Segment;
	CStatic	m_Patch;
	CStatic	m_MeshVert;
	CStatic	m_MeshFaces;
	CStatic	m_Mesh;
	CStatic	m_Entities;
	CStatic	m_Camera;
	CStatic	m_Bone;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfosSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfosSel)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOSSEL_H__F720BEC2_8811_48E2_AD63_EB7B989060DD__INCLUDED_)
