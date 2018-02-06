// CImageDemoDoc.h : interface of the CCImageDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIMAGEDEMODOC_H__CD874C0E_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_)
#define AFX_CIMAGEDEMODOC_H__CD874C0E_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_

//#include "..\image\Image.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CCImageDemoDoc : public CDocument
{
protected: // create from serialization only
	CCImageDemoDoc();
	DECLARE_DYNCREATE(CCImageDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCImageDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bAffTransparent;
	CImage m_Image;
	virtual ~CCImageDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCImageDemoDoc)
	afx_msg void OnEditionRotation90();
	afx_msg void OnEditionRotation180();
	afx_msg void OnEditionRotation270();
	afx_msg void OnEditionMiroirvertical();
	afx_msg void OnEditionMiroirhorizontal();
	afx_msg void OnEditionNgatif();
	afx_msg void OnEditCopy();
	afx_msg void OnFileSave();
	afx_msg void OnEditionConvertiren16couleurs();
	afx_msg void OnEditionConvertiren16niveauxdegris();
	afx_msg void OnEditionConvertiren24bits();
	afx_msg void OnEditionConvertiren256couleurs();
	afx_msg void OnEditionConvertiren256niveauxdegris();
	afx_msg void OnEditionConvertirenNoiretblanc();
	afx_msg void OnEditPaste();
	afx_msg void OnUpdateEditPaste(CCmdUI* pCmdUI);
	afx_msg void OnEditionInfos();
	afx_msg void OnEditionContraste();
	afx_msg void OnEditionCanalRouge();
	afx_msg void OnEditionCanalVert();
	afx_msg void OnEditionCanalBleu();
	afx_msg void OnEditionConvertirenPhoto();
	afx_msg void OnUpdateEditionConvertirenPhoto(CCmdUI* pCmdUI);
	afx_msg void OnFileSaveAs();
	afx_msg void OnAffichageTransparent();
	afx_msg void OnUpdateAffichageTransparent(CCmdUI* pCmdUI);
	afx_msg void OnEditionDumpimage();
	afx_msg void OnUpdateEditionDumpimage(CCmdUI* pCmdUI);
	afx_msg void OnEditionUndumpimage();
	afx_msg void OnUpdateEditionUndumpimage(CCmdUI* pCmdUI);
	afx_msg void OnEditionCorrectiondescouleurs();
	afx_msg void OnFiltres24bitsCrationfiltre();
	afx_msg void OnUpdateFiltres24bitsCrationfiltre(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CIMAGEDEMODOC_H__CD874C0E_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_)
