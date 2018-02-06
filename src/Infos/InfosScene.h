#if !defined(AFX_INFOSSCENE_H__770C6721_79CD_4DD3_AAB2_5F4154A9D76E__INCLUDED_)
#define AFX_INFOSSCENE_H__770C6721_79CD_4DD3_AAB2_5F4154A9D76E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfosScene.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfosScene dialog

class CInfosScene : public CDialog
{
// Construction
public:
	CInfosScene(CWnd* pParent = NULL);   // standard constructor
	void AffValues();
	int RecCalcBone(CKBone *daBone);
	CKScene *m_Scene;
// Dialog Data
	//{{AFX_DATA(CInfosScene)
	enum { IDD = IDD_INFOSSCENE };
	CStatic	m_Mesh;
	CStatic	m_Skeletons;
	CStatic	m_shapes;
	CStatic	m_Segments;
	CStatic	m_MeshVert;
	CStatic	m_Patch;
	CStatic	m_MeshFaces;
	CStatic	m_Entities;
	CStatic	m_Camera;
	CStatic	m_Bone;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfosScene)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfosScene)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFOSSCENE_H__770C6721_79CD_4DD3_AAB2_5F4154A9D76E__INCLUDED_)
