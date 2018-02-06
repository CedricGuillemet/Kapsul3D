// CreateFilterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CImageDemo.h"
//#include "..\image\Image.h"
#include "CImageDemoDoc.h"
#include "CreateFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Variables globales de déclaration des filtres
char* g_szCimageFiltersTitles[] =
{
	"FILTRE DE BASE",
	"FILTER_BLUR_NORMAL",
	"FILTER_BLUR_MEAN_3x3",
	"FILTER_BLUR_MEAN_5x5",
	"FILTER_BLUR_MEAN_7x7",
	"FILTER_SOFTEN_LIGHT",
	"FILTER_SOFTEN_MEDIUM",
	"FILTER_SOFTEN_HEAVY",
	"FILTER_HIGH_PASS_3X3",
	"FILTER_HIGH_PASS_5X5",
	"FILTER_EMBOSS",
	"FILTER_EMBOSS_EAST",
	"FILTER_EMBOSS_NORTH",
	"FILTER_EMBOSS_SOUTH",
	"FILTER_EMBOSS_WEST",
	"FILTER_EMBOSS_NORTHEAST",
	"FILTER_EMBOSS_NORTHWEST",
	"FILTER_EDGE_LIGHT",
	"FILTER_EDGE_MEDIUM",
	"FILTER_EDGE_HEAVY",
	"FILTER_EDGE_LAPLACE3",
	"FILTER_EDGE_LAPLACE5",
	"FILTER_EDGE_LAPLACE5INV",
	"FILTER_EDGE_HORZ",
	"FILTER_EDGE_VERT",
	"FILTER_EDGE_DIAGLH",
	"FILTER_EDGE_DIAGRH",
	"FILTER_ENHANCED_FOCUS",
	"FILTER_ENHANCED_DETAILS_LOW",
	"FILTER_ENHANCED_DETAILS_HIGH",
	"FILTER_REDUCE_JAGGIES"
};
char* g_szCimageFiltersMatrices[] =
{
	"1,0,3, 0,0,0, 0,1,0, 0,0,0",
	FILTER_BLUR_NORMAL,
	FILTER_BLUR_MEAN_3x3,
	FILTER_BLUR_MEAN_5x5,
	FILTER_BLUR_MEAN_7x7,
	FILTER_SOFTEN_LIGHT,
	FILTER_SOFTEN_MEDIUM,
	FILTER_SOFTEN_HEAVY,
	FILTER_HIGH_PASS_3X3,
	FILTER_HIGH_PASS_5X5,
	FILTER_EMBOSS,
	FILTER_EMBOSS_EAST,
	FILTER_EMBOSS_NORTH,
	FILTER_EMBOSS_SOUTH,
	FILTER_EMBOSS_WEST,
	FILTER_EMBOSS_NORTHEAST,
	FILTER_EMBOSS_NORTHWEST,
	FILTER_EDGE_LIGHT,
	FILTER_EDGE_MEDIUM,
	FILTER_EDGE_HEAVY,
	FILTER_EDGE_LAPLACE3,
	FILTER_EDGE_LAPLACE5,
	FILTER_EDGE_LAPLACE5INV,
	FILTER_EDGE_HORZ,
	FILTER_EDGE_VERT,
	FILTER_EDGE_DIAGLH,
	FILTER_EDGE_DIAGRH,
	FILTER_ENHANCED_FOCUS,
	FILTER_ENHANCED_DETAILS_LOW,
	FILTER_ENHANCED_DETAILS_HIGH,
	FILTER_REDUCE_JAGGIES
};


//////////
/////////////////////////////////////////////////////////////////////////////
// CCreateFilterDlg dialog


CCreateFilterDlg::CCreateFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateFilterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateFilterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCreateFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateFilterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateFilterDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateFilterDlg)
	ON_WM_DRAWITEM()
	ON_EN_CHANGE(IDC_NROWS, OnChangeNrows)
	ON_BN_CLICKED(IDC_APPLIQUER, OnAppliquer)
	ON_BN_CLICKED(IDC_COPIER_FILTRE, OnCopierFiltre)
	ON_LBN_DBLCLK(IDC_FILTRES_CIMAGE, OnDblclkFiltresCimage)
	//}}AFX_MSG_MAP
	ON_CONTROL_RANGE(EN_CHANGE, IDC_MATRICE1, IDC_MATRICE121, OnChangeNrows)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateFilterDlg message handlers

BOOL CCreateFilterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetDlgItemInt(IDC_MATRICE61, 1);
	SetDlgItemInt(IDC_NBIAS, 0);
	SetDlgItemInt(IDC_NROWS, 3);

	for(int i=0; i<(sizeof(g_szCimageFiltersTitles)/sizeof(g_szCimageFiltersTitles[0])); i++)
		((CListBox*)GetDlgItem(IDC_FILTRES_CIMAGE))->AddString(g_szCimageFiltersTitles[i]);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateFilterDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if(nIDCtl==IDC_IMAGE
		&& lpDrawItemStruct->itemAction==ODA_DRAWENTIRE
		&& m_Image.IsValid())
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		CRect rcDraw;
		(dc.GetWindow())->GetClientRect(&rcDraw);
		m_Image.Draw(dc.m_hDC, rcDraw, DIB_DRAW_SETPALETTE
			| DIB_DRAW_STRETCH_REDUCEX | DIB_DRAW_STRETCH_REDUCEY
			| DIB_DRAW_CENTER_HORZ | DIB_DRAW_CENTER_VERT
			| DIB_DRAW_KEEP_RATIO);
		dc.Detach();
		return;
	}
	
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

// Change le calcul de nKoef
void CCreateFilterDlg::OnChangeNrows() 
{
	int nRows = GetDlgItemInt(IDC_NROWS);
	if(nRows<3 || nRows>11 || !(nRows&1))
		return;
	int nKoef = 0;
	for(int y=IDC_MATRICE56-11*(nRows>>1); y<=IDC_MATRICE56+11*(nRows>>1); y+=11)
		for(int x=5-(nRows>>1); x<=5+(nRows>>1); x++)
			nKoef += GetDlgItemInt(y+x);
	if(!nKoef)
		nKoef = 1;
	SetDlgItemInt(IDC_NKOEF, nKoef);
}

// Application du filtre sur l'image
void CCreateFilterDlg::OnAppliquer() 
{
	int nRows = GetDlgItemInt(IDC_NROWS);
	if(nRows<3 || nRows>11 || !(nRows&1))
	{
		AfxMessageBox(IDS_ERR_MATRICE, MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	int nKoef = GetDlgItemInt(IDC_NKOEF);
	if(!nKoef)
		nKoef = 1;
	int nMatrice[225];
	for(int i=0; i<225; nMatrice[i++]=0);
	int k=0;
	for(int y=IDC_MATRICE56-11*(nRows>>1); y<=IDC_MATRICE56+11*(nRows>>1); y+=11)
		for(int x=5-(nRows>>1); x<=5+(nRows>>1); x++)
			nMatrice[k++] = GetDlgItemInt(y+x);

	m_Image = m_pParent->m_Image;

	CString szFiltre, szDummy;
	szFiltre.Format("%d,%d,%d,", nKoef, GetDlgItemInt(IDC_NBIAS), nRows);

	for(i=0; i<k-1; i++)
	{
		if(!(i%nRows))
			szFiltre += " ";
		szDummy.Format("%d,", nMatrice[i]);
		szFiltre += szDummy;
	}
	szDummy.Format("%d", nMatrice[i]);
	szFiltre += szDummy;

	m_Image.Effect24MatrixFilter(szFiltre);

	GetDlgItem(IDC_IMAGE)->InvalidateRect(NULL);
}

// Copie les paramètres ds le presse-papiers pour aider au #define de filtres
void CCreateFilterDlg::OnCopierFiltre() 
{
	int nRows = GetDlgItemInt(IDC_NROWS);
	if(nRows<3 || nRows>11 || !(nRows&1))
	{
		AfxMessageBox(IDS_ERR_MATRICE, MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	int nKoef = GetDlgItemInt(IDC_NKOEF);
	if(!nKoef)
		nKoef = 1;
	int nMatrice[225];
	for(int i=0; i<225; nMatrice[i++]=0);
	int k=0;
	for(int y=IDC_MATRICE56-11*(nRows>>1); y<=IDC_MATRICE56+11*(nRows>>1); y+=11)
		for(int x=5-(nRows>>1); x<=5+(nRows>>1); x++)
			nMatrice[k++] = GetDlgItemInt(y+x);
	CString szFiltre, szDummy;
	szFiltre.Format("\"%d,%d,%d,", nKoef, GetDlgItemInt(IDC_NBIAS), nRows);

	for(i=0; i<k-1; i++)
	{
		if(!(i%nRows))
			szFiltre += " ";
		szDummy.Format("%d,", nMatrice[i]);
		szFiltre += szDummy;
	}
	szDummy.Format("%d\"", nMatrice[i]);
	szFiltre += szDummy;

	// Met le texte ds le presse papier
	HGLOBAL hTexte=GlobalAlloc(GHND | GMEM_DDESHARE, CLIPEXTRA_MEM);
	if(!hTexte)
		return;
	char* szTexte = (char*)GlobalLock(hTexte);
	lstrcpy(szTexte, (LPCTSTR)szFiltre);
	GlobalUnlock(hTexte);
	if(!(::OpenClipboard(NULL)))
	{
		GlobalFree(hTexte);
		return;
	}
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hTexte);
	CloseClipboard();
}

void CCreateFilterDlg::OnDblclkFiltresCimage() 
{
	for(int i=IDC_MATRICE1; i<IDC_MATRICE121; i++)
		SetDlgItemText(i, "");

	char* szCoefs = (char*)g_szCimageFiltersMatrices[((CListBox*)GetDlgItem(IDC_FILTRES_CIMAGE))->GetCurSel()];
	int nKoef = atoi(szCoefs);
	while((szCoefs[0]>='0' && szCoefs[0]<='9') || szCoefs[0]=='-')
		szCoefs++;
	while(szCoefs[0] && (szCoefs[0]<'0' || szCoefs[0]>'9') && szCoefs[0]!='-')
		szCoefs++;
	int nBias = atoi(szCoefs);
	while((szCoefs[0]>='0' && szCoefs[0]<='9') || szCoefs[0]=='-')
		szCoefs++;
	while(szCoefs[0] && (szCoefs[0]<'0' || szCoefs[0]>'9') && szCoefs[0]!='-')
		szCoefs++;
	int nRows = atoi(szCoefs);
	// Récupération de la matrice
	int nMatrix[225];
	for(i=0; i<nRows*nRows; i++)
	{
		while((szCoefs[0]>='0' && szCoefs[0]<='9') || szCoefs[0]=='-')
			szCoefs++;
		while(szCoefs[0] && (szCoefs[0]<'0' || szCoefs[0]>'9') && szCoefs[0]!='-')
			szCoefs++;
		nMatrix[i] = atoi(szCoefs);
	}

	SetDlgItemInt(IDC_NROWS, 1);
	int k=0;
	for(int y=IDC_MATRICE56-11*(nRows>>1); y<=IDC_MATRICE56+11*(nRows>>1); y+=11)
		for(int x=5-(nRows>>1); x<=5+(nRows>>1); x++)
			SetDlgItemInt(y+x, nMatrix[k++]);
	SetDlgItemInt(IDC_NROWS, nRows);
	SetDlgItemInt(IDC_NKOEF, nKoef);
	SetDlgItemInt(IDC_NBIAS, nBias);
}
