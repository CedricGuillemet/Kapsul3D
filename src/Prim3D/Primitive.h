#if !defined(AFX_PRIMITIVE_H__E29B3B07_F4C3_431C_9902_B1F808215593__INCLUDED_)
#define AFX_PRIMITIVE_H__E29B3B07_F4C3_431C_9902_B1F808215593__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Primitive.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPrimitive dialog

class CPrimitive : public CDialog
{
    DECLARE_DYNCREATE(CPrimitive)

// Construction
public:
	CPrimitive(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrimitive)
	enum { IDD = IDD_MODDIAG1 };
	CButton	m_Patch;
	CButton	m_Cone2;
	CButton	m_Tube2;
	CButton	m_Tree2;
	CButton	m_Torus2;
	CButton	m_Sphere2;
	CButton	m_Hemis2;
	CButton	m_Grid2;
	CButton	m_Cylinder2;
	CButton	m_Cube2;
	//}}AFX_DATA

    void UnSetPlugin(void);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrimitive)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual void OnOK( );
	virtual void OnCancel( );

	// Generated message map functions
	//{{AFX_MSG(CPrimitive)
	afx_msg void OnCone2();
	afx_msg void OnCube2();
	afx_msg void OnCylinder2();
	afx_msg void OnGrid2();
	afx_msg void OnHemis2();
	afx_msg void OnSphere2();
	afx_msg void OnTorus2();
	afx_msg void OnTree2();
	afx_msg void OnTube2();
	virtual BOOL OnInitDialog();
	afx_msg void OnPatch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRIMITIVE_H__E29B3B07_F4C3_431C_9902_B1F808215593__INCLUDED_)
