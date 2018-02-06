// TerrainEdDlg.h : header file
//

#if !defined(AFX_TERRAINEDDLG_H__9A01761E_42D4_4660_A98D_294B76C05235__INCLUDED_)
#define AFX_TERRAINEDDLG_H__9A01761E_42D4_4660_A98D_294B76C05235__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTerrainEdDlg dialog
#include <headers.h>
#include "Terra.h"
#include "AffImage.h"
#include "TerraLight.h"
#include "TerraTex.h"
#include "OglViewer.h"
//#include "Preview.h"
#include "HeightDesign.h"
#include "MapLightEdit.h"
#include "afxwin.h"
//#include "SkyBoxEd.h"
class CTerrainEdDlg : public CDialog
{
// Construction
public:
	CTerrainEdDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTerrainEdDlg)
	enum { IDD = IDD_TERRAINED_DIALOG };
	CButton	m_SkyboxWin;
	CButton	m_LightWin;
	CButton	m_HeightWinBt;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTerrainEdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

    CImage Img1,Img2,Img3,Img4;
    int LightPosX,LightPosY;
    int MapPosX,MapPosY;
    int TreePosX,TreePosY;
    CHeightDesign htDesign;
    CMapLightEdit mlDesign;
    //CSkyBoxEd sbDesign;

// Implementation
public:
	HICON m_hIcon;
    CKSlid   m_dbls;
    CKSlid   m_treer;
    CImage m_Trees;
//    CPreview m_pPreview;
    void GenerateTrees(int Min,int Max,int dens,CTerra *dater);
	// Generated message map functions
	//{{AFX_MSG(CTerrainEdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHeightwin();
	afx_msg void OnLightwin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CComboBox m_SizeLand;
	afx_msg void OnBnClickedGenerate();
	CButton m_Strips;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TERRAINEDDLG_H__9A01761E_42D4_4660_A98D_294B76C05235__INCLUDED_)
