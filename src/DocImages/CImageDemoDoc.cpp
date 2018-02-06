// CImageDemoDoc.cpp : implementation of the CCImageDemoDoc class
//

#include "stdafx.h"
#include "CImageDemo.h"

//#include "..\image\Image.h"
#include "CImageDemoDoc.h"
#include "ContrasteDlg.h"
#include "CorrectionCouleursDlg.h"
#include "CreateFilterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoDoc

IMPLEMENT_DYNCREATE(CCImageDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CCImageDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CCImageDemoDoc)
	ON_COMMAND(ID_EDITION_ROTATION90, OnEditionRotation90)
	ON_COMMAND(ID_EDITION_ROTATION180, OnEditionRotation180)
	ON_COMMAND(ID_EDITION_ROTATION270, OnEditionRotation270)
	ON_COMMAND(ID_EDITION_MIROIRVERTICAL, OnEditionMiroirvertical)
	ON_COMMAND(ID_EDITION_MIROIRHORIZONTAL, OnEditionMiroirhorizontal)
	ON_COMMAND(ID_EDITION_NGATIF, OnEditionNgatif)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_EDITION_CONVERTIREN_16COULEURS, OnEditionConvertiren16couleurs)
	ON_COMMAND(ID_EDITION_CONVERTIREN_16NIVEAUXDEGRIS, OnEditionConvertiren16niveauxdegris)
	ON_COMMAND(ID_EDITION_CONVERTIREN_24BITS, OnEditionConvertiren24bits)
	ON_COMMAND(ID_EDITION_CONVERTIREN_256COULEURS, OnEditionConvertiren256couleurs)
	ON_COMMAND(ID_EDITION_CONVERTIREN_256NIVEAUXDEGRIS, OnEditionConvertiren256niveauxdegris)
	ON_COMMAND(ID_EDITION_CONVERTIREN_NOIRETBLANC, OnEditionConvertirenNoiretblanc)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	ON_COMMAND(ID_EDITION_INFOS, OnEditionInfos)
	ON_COMMAND(ID_EDITION_CONTRASTE, OnEditionContraste)
	ON_COMMAND(ID_EDITION_CANAL_ROUGE, OnEditionCanalRouge)
	ON_COMMAND(ID_EDITION_CANAL_VERT, OnEditionCanalVert)
	ON_COMMAND(ID_EDITION_CANAL_BLEU, OnEditionCanalBleu)
	ON_COMMAND(ID_EDITION_CONVERTIREN_PHOTO, OnEditionConvertirenPhoto)
	ON_UPDATE_COMMAND_UI(ID_EDITION_CONVERTIREN_PHOTO, OnUpdateEditionConvertirenPhoto)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_AFFICHAGE_TRANSPARENT, OnAffichageTransparent)
	ON_UPDATE_COMMAND_UI(ID_AFFICHAGE_TRANSPARENT, OnUpdateAffichageTransparent)
	ON_COMMAND(ID_EDITION_DUMPIMAGE, OnEditionDumpimage)
	ON_UPDATE_COMMAND_UI(ID_EDITION_DUMPIMAGE, OnUpdateEditionDumpimage)
	ON_COMMAND(ID_EDITION_UNDUMPIMAGE, OnEditionUndumpimage)
	ON_UPDATE_COMMAND_UI(ID_EDITION_UNDUMPIMAGE, OnUpdateEditionUndumpimage)
	ON_COMMAND(ID_EDITION_CORRECTIONDESCOULEURS, OnEditionCorrectiondescouleurs)
	ON_COMMAND(ID_FILTRES24BITS_CRATIONFILTRE, OnFiltres24bitsCrationfiltre)
	ON_UPDATE_COMMAND_UI(ID_FILTRES24BITS_CRATIONFILTRE, OnUpdateFiltres24bitsCrationfiltre)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoDoc construction/destruction

CCImageDemoDoc::CCImageDemoDoc()
{
	m_bAffTransparent = FALSE;
}

CCImageDemoDoc::~CCImageDemoDoc()
{
}

BOOL CCImageDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//m_Image.LoadFromRessource(MAKEINTRESOURCE(IDR_IMAGE1), IMG_FORMAT_JPEG, "Images");

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CCImageDemoDoc diagnostics

#ifdef _DEBUG
void CCImageDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCImageDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCImageDemoDoc commands

BOOL CCImageDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	BOOL bRet = m_Image.LoadFile(lpszPathName);
	if(bRet)
		m_bAffTransparent = m_Image.GetTransparentColor();
	else
		m_bAffTransparent = FALSE;
	return bRet;
}

void CCImageDemoDoc::OnEditionRotation90() 
{
	m_Image.Rotate(1);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionRotation180() 
{
	m_Image.Rotate(2);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionRotation270() 
{
	m_Image.Rotate(3);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionMiroirvertical() 
{
	m_Image.VerticalMirror();
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionMiroirhorizontal() 
{
	m_Image.HorizontalMirror();
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionNgatif() 
{
	m_Image.Negative();
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditCopy() 
{
	m_Image.CopyToClipboard();
}

void CCImageDemoDoc::OnFileSave() 
{
	OnFileSaveAs();
}

void CCImageDemoDoc::OnEditionConvertiren16couleurs() 
{
	m_Image.Dither(IMG_TYPE_COL16, ((CCImageDemoApp*)AfxGetApp())->m_bUseDithering);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionConvertiren16niveauxdegris() 
{
	m_Image.Dither(IMG_TYPE_NG16, ((CCImageDemoApp*)AfxGetApp())->m_bUseDithering);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionConvertiren24bits() 
{
	m_Image.Dither(IMG_TYPE_COL24, ((CCImageDemoApp*)AfxGetApp())->m_bUseDithering);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionConvertiren256couleurs() 
{
	m_Image.Dither(IMG_TYPE_COL256, ((CCImageDemoApp*)AfxGetApp())->m_bUseDithering);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionConvertiren256niveauxdegris() 
{
	m_Image.Dither(IMG_TYPE_NG256, ((CCImageDemoApp*)AfxGetApp())->m_bUseDithering);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionConvertirenNoiretblanc() 
{
	m_Image.Dither(IMG_TYPE_NB, ((CCImageDemoApp*)AfxGetApp())->m_bUseDithering);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditPaste() 
{
	if(m_Image.PasteClipboard())
		m_bAffTransparent = m_Image.GetTransparentColor();
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_Image.IsClipboardOK());
}

void CCImageDemoDoc::OnEditionInfos() 
{
	CString szDummy;
	szDummy.Format("Image de %d par %d en %d bits/pixels\nRésolution X: %d dpi, Y: %d dpi",
		m_Image.GetWidth(), m_Image.GetHeight(), m_Image.GetBPP(),
		(int)(PPM2DPI(m_Image.GetResX())), (int)(PPM2DPI(m_Image.GetResY())));
	AfxMessageBox(szDummy, MB_ICONINFORMATION | MB_OK);
}

void CCImageDemoDoc::OnEditionContraste() 
{
	CContrasteDlg Dlg;
	Dlg.m_pParent = this;
	Dlg.m_Image = m_Image;
	if(Dlg.DoModal()==IDOK)
	{
		m_Image = Dlg.m_Image;
		UpdateAllViews(NULL);
	}
}

void CCImageDemoDoc::OnEditionCanalRouge() 
{
	m_Image.SelectChannelRVB(CANALRVB_ROUGE);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionCanalVert() 
{
	m_Image.SelectChannelRVB(CANALRVB_VERT);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionCanalBleu() 
{
	m_Image.SelectChannelRVB(CANALRVB_BLEU);
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnEditionConvertirenPhoto() 
{
	((CCImageDemoApp*)AfxGetApp())->m_bUseDithering
		= !(((CCImageDemoApp*)AfxGetApp())->m_bUseDithering);
}

void CCImageDemoDoc::OnUpdateEditionConvertirenPhoto(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(((CCImageDemoApp*)AfxGetApp())->m_bUseDithering);
}

void CCImageDemoDoc::OnFileSaveAs()
{
	if(!m_Image.IsValid())
		return;

	// Création de la boîte de dialogue de sauvegarde
	CString szFilters;
	CString szSection;
	CString szKey;

	szFilters.LoadString(IDS_FILE_FILTERS);
	CFileDialog Dlg(FALSE, NULL, NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST,
		(LPCTSTR)szFilters);

	// Appel de la boîte
	if(Dlg.DoModal()!=IDOK)
		return;

	AfxGetApp()->DoWaitCursor(1);

	CString szFileName=Dlg.GetPathName();
	CString szExt=Dlg.GetFileExt();

	// Invoque la sauvegarde en fonction du type d'image choisi
	BOOL bSuccess=FALSE;
	switch(Dlg.m_ofn.nFilterIndex-1)
	{
		case 0:
			if(szExt.IsEmpty())
				szFileName += ".bmp";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_BMPWIN);
			break;
		case 1:
			if(szExt.IsEmpty())
				szFileName += ".bmp";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_BMPOS2);
			break;
		case 2:
			if(szExt.IsEmpty())
				szFileName += ".rle";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_RLE);
			break;
		case 3:
			if(szExt.IsEmpty())
				szFileName += ".pcx";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_PCX);
			break;
		case 4:
			if(szExt.IsEmpty())
				szFileName += ".tga";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_TGA,
				IMG_COMPRESS_NONE);
			break;
		case 5:
			if(szExt.IsEmpty())
				szFileName += ".tga";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_TGA,
				IMG_COMPRESS_RLE);
			break;
		case 6:
			if(szExt.IsEmpty())
				szFileName += ".gif";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_GIF);
			break;
		case 7:
			if(szExt.IsEmpty())
				szFileName += ".jpg";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_JPEG, 80);
			break;
		case 8:
			if(szExt.IsEmpty())
				szFileName += ".tif";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_TIFF, IMG_COMPRESS_NONE);
			break;
		case 9:
			if(szExt.IsEmpty())
				szFileName += ".tif";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_TIFF, IMG_COMPRESS_RLE);
			break;
		case 10:
			if(szExt.IsEmpty())
				szFileName += ".tif";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_TIFF, IMG_COMPRESS_LZW);
			break;
		case 11:
			if(szExt.IsEmpty())
				szFileName += ".tif";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_TIFF, IMG_COMPRESS_JPEG);
			break;
		case 12:
			if(szExt.IsEmpty())
				szFileName += ".png";
			bSuccess=m_Image.SaveFile(szFileName, IMG_FORMAT_PNG);
			break;
	}

	AfxGetApp()->DoWaitCursor(-1);

	// Si sauvegarde pas réussie, on ne sort pas
	if(!bSuccess)
		AfxMessageBox(IDS_SAVEFILE_ERROR, MB_OK | MB_ICONEXCLAMATION);
}

void CCImageDemoDoc::OnAffichageTransparent() 
{
	m_bAffTransparent = !m_bAffTransparent;
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnUpdateAffichageTransparent(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bAffTransparent);
}

void CCImageDemoDoc::OnEditionDumpimage() 
{
	//m_Image.DumpImage();
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnUpdateEditionDumpimage(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(!m_Image.IsDumped());
}

void CCImageDemoDoc::OnEditionUndumpimage() 
{
	//m_Image.UndumpImage();
	UpdateAllViews(NULL);
}

void CCImageDemoDoc::OnUpdateEditionUndumpimage(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(m_Image.IsDumped());
}

void CCImageDemoDoc::OnEditionCorrectiondescouleurs() 
{
	CCorrectionCouleursDlg Dlg;
	Dlg.m_pParent = this;
	Dlg.m_Image = m_Image;
	if(Dlg.DoModal()==IDOK)
	{
		m_Image = Dlg.m_Image;
		UpdateAllViews(NULL);
	}
}

void CCImageDemoDoc::OnFiltres24bitsCrationfiltre() 
{
	CCreateFilterDlg Dlg;
	Dlg.m_pParent = this;
	Dlg.m_Image = m_Image;
	if(Dlg.DoModal()==IDOK)
	{
		m_Image = Dlg.m_Image;
		UpdateAllViews(NULL);
	}
}

void CCImageDemoDoc::OnUpdateFiltres24bitsCrationfiltre(CCmdUI* pCmdUI) 
{
	// Interdit les filtres si l'image n'est pas en 24 BPP
	pCmdUI->Enable(m_Image.GetBPP()==24);
}
