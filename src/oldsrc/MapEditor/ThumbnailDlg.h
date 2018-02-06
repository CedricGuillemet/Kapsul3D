#if !defined(AFX_THUMBNAILDLG_H__0A393529_40C9_471C_BC06_4DD0C7BB788A__INCLUDED_)
#define AFX_THUMBNAILDLG_H__0A393529_40C9_471C_BC06_4DD0C7BB788A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThumbnailDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThumbnailDlg dialog

class CThumbnailDlg : public CDialog
{
// Construction
public:
	CThumbnailDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CThumbnailDlg)
	enum { IDD = IDD_MODDIAG };
	CButton	m_BuildIt;
	CButton	m_TranslateCoords;
	CButton	m_ScaleCoords;
	CButton	m_RotateCoords;
	CButton	m_MoveVertex;
	CButton	m_MoveEdge;
	CComboBox	m_ListNGon;
	CButton	m_Clipper;
	CButton	m_Hollow;
	CButton	m_CsgSub;
	CButton	m_CsgMerge;
	CButton	m_SZ;
	CButton	m_SY;
	CButton	m_SX;
	CButton	m_RZ;
	CButton	m_RY;
	CButton	m_RX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThumbnailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

    virtual void OnOK( );
    
    



    public:
	    void UnselectEdit();
	void	UnActiveIt(void);
// Implementation
protected:
	HICON		m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CThumbnailDlg)

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    virtual void OnCancel( );
	afx_msg void OnHollow();
	afx_msg void OnCsgmerge();
	afx_msg void OnCsgsub();
	afx_msg void OnClipper();
	afx_msg void OnRx();
	afx_msg void OnSx();
	afx_msg void OnRy();
	afx_msg void OnSy();
	afx_msg void OnRz();
	afx_msg void OnSz();
	afx_msg void OnMovevertex();
	afx_msg void OnMoveedge();
	afx_msg void OnTranslatecoords();
	afx_msg void OnScalecoords();
	afx_msg void OnRotatecoords();
	afx_msg void OnBuildit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THUMBNAILDLG_H__0A393529_40C9_471C_BC06_4DD0C7BB788A__INCLUDED_)
