// BackWorldCap.cpp : implementation file
//

#include "stdafx.h"
#include "kapsulse.h"
#include "BackWorldCap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBackWorldCap dialog


CBackWorldCap::CBackWorldCap(CWnd* pParent /*=NULL*/)
	: CDialog(CBackWorldCap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBackWorldCap)
	//}}AFX_DATA_INIT
}


void CBackWorldCap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBackWorldCap)
	DDX_Control(pDX, IDC_TOPSY, m_TopSY);
	DDX_Control(pDX, IDC_TOPSX, m_TopSX);
	DDX_Control(pDX, IDC_TOPSIZEY, m_TopSizeY);
	DDX_Control(pDX, IDC_TOPSIZEX, m_TopSizeX);
	DDX_Control(pDX, IDC_TOPOY, m_TopOY);
	DDX_Control(pDX, IDC_TOPOX, m_TopOX);
	DDX_Control(pDX, IDC_TOPORIGINY, m_TopOriginY);
	DDX_Control(pDX, IDC_TOPORIGINX, m_TopOriginX);
	DDX_Control(pDX, IDC_TOPOPA, m_TopOPA);
	DDX_Control(pDX, IDC_TOPKEEP, m_TopKeep);
	DDX_Control(pDX, IDC_TOPEDIT, m_TopEdit);
	DDX_Control(pDX, IDC_TOPBOTTOM, m_TopBottom);
	DDX_Control(pDX, IDC_TOPAFF, m_TopAff);
	DDX_Control(pDX, IDC_SZ, m_SZ);
	DDX_Control(pDX, IDC_SY, m_SY);
	DDX_Control(pDX, IDC_SX, m_SX);
	DDX_Control(pDX, IDC_SIZEZ, m_SizeZ);
	DDX_Control(pDX, IDC_SIZEY, m_SizeY);
	DDX_Control(pDX, IDC_SIZEX, m_SizeX);
	DDX_Control(pDX, IDC_OZ, m_OZ);
	DDX_Control(pDX, IDC_OY, m_OY);
	DDX_Control(pDX, IDC_OX, m_OX);
	DDX_Control(pDX, IDC_ORIGINZ, m_OriginZ);
	DDX_Control(pDX, IDC_ORIGINX, m_OriginX);
	DDX_Control(pDX, IDC_ORIGINY, m_OriginY);
	DDX_Control(pDX, IDC_LIBTOPWORLD, m_LibTopWorld);
	DDX_Control(pDX, IDC_LIBTOPSIZE, m_LibTopSize);
	DDX_Control(pDX, IDC_LIBTOPORIGIN, m_LibTopOrigin);
	DDX_Control(pDX, IDC_LIBTOPOPACITY, m_LibTopOpacity);
	DDX_Control(pDX, IDC_LIBTOPFILE, m_LibTopFile);
	DDX_Control(pDX, IDC_LIBLEFTWORLD, m_LibLeftWorld);
	DDX_Control(pDX, IDC_LIBLEFTSIZE, m_LibLeftSize);
	DDX_Control(pDX, IDC_LIBLEFTORIGIN, m_LibLeftOrigin);
	DDX_Control(pDX, IDC_LIBLEFTOPACITY, m_LibLeftOpacity);
	DDX_Control(pDX, IDC_LIBLEFTFILE, m_LibLeftFile);
	DDX_Control(pDX, IDC_LIBFRONTWORLD, m_LibFrontWorld);
	DDX_Control(pDX, IDC_LIBFRONTSIZE, m_LibFrontSize);
	DDX_Control(pDX, IDC_LIBFRONTORIGIN, m_LibFrontOrigin);
	DDX_Control(pDX, IDC_LIBFRONTOPACITY, m_LibFrontOPA);
	DDX_Control(pDX, IDC_LIBFRONTFILE, m_LibFrontFile);
	DDX_Control(pDX, IDC_LIBCAPSIZE, m_LibCapSize);
	DDX_Control(pDX, IDC_LIBCAPORIGIN, m_LibCapOrigin);
	DDX_Control(pDX, IDC_LEFTSY, m_LeftSY);
	DDX_Control(pDX, IDC_LEFTSX, m_LeftSX);
	DDX_Control(pDX, IDC_LEFTSIZEY, m_LeftSizeY);
	DDX_Control(pDX, IDC_LEFTSIZEX, m_LeftSizeX);
	DDX_Control(pDX, IDC_LEFTRIGHT, m_LeftRight);
	DDX_Control(pDX, IDC_LEFTOY, m_LeftOY);
	DDX_Control(pDX, IDC_LEFTOX, m_LeftOX);
	DDX_Control(pDX, IDC_LEFTORIGINY, m_LeftOriginY);
	DDX_Control(pDX, IDC_LEFTORIGINX, m_LeftOriginX);
	DDX_Control(pDX, IDC_LEFTOPA, m_LeftOPA);
	DDX_Control(pDX, IDC_LEFTKEEP, m_LeftKeep);
	DDX_Control(pDX, IDC_LEFTEDIT, m_LeftEdit);
	DDX_Control(pDX, IDC_LEFTAFF, m_LeftAff);
	DDX_Control(pDX, IDC_FRONTSY, m_FrontSY);
	DDX_Control(pDX, IDC_FRONTSX, m_FrontSX);
	DDX_Control(pDX, IDC_FRONTSIZEY, m_FrontSizeY);
	DDX_Control(pDX, IDC_FRONTSIZEX, m_FrontSizeX);
	DDX_Control(pDX, IDC_FRONTOY, m_FrontOY);
	DDX_Control(pDX, IDC_FRONTOX, m_FrontOX);
	DDX_Control(pDX, IDC_FRONTORIGINY, m_FrontOriginY);
	DDX_Control(pDX, IDC_FRONTORIGINX, m_FrontOriginX);
	DDX_Control(pDX, IDC_FRONTOPA, m_FrontOPA);
	DDX_Control(pDX, IDC_FRONTKEEP, m_FrontKeep);
	DDX_Control(pDX, IDC_FRONTEDIT, m_FrontEdit);
	DDX_Control(pDX, IDC_FRONTBACK, m_FrontBack);
	DDX_Control(pDX, IDC_FRONTAFF, m_FrontAff);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBackWorldCap, CDialog)
	//{{AFX_MSG_MAP(CBackWorldCap)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BROWSEFRONT, OnBrowsefront)
	ON_BN_CLICKED(IDC_BROWSELEFT, OnBrowseleft)
	ON_BN_CLICKED(IDC_BROWSETOP, OnBrowsetop)
	ON_BN_CLICKED(IDC_TOPKEEP, OnTopkeep)
	ON_BN_CLICKED(IDC_LEFTKEEP, OnLeftkeep)
	ON_BN_CLICKED(IDC_FRONTKEEP, OnFrontkeep)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBackWorldCap message handlers

/*
class CKBackPic
{
public:
	CKBackPic() {};
	~CKBackPic() {};
	bool Active;
	bool Keep;
	MYPOINT Origin;
	MYPOINT Size;
	float Opacity;
	CKTexture tex;
};

class KAPSUL_DESC CKScene
{
    private:
		bool RecCountSkel(CKBone *daBone);


    public:
		CKBackPic m_bkTop,m_bkFront,m_bkLeft;
*/

BOOL CBackWorldCap::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString tmp;

	// -- Top --

	m_TopSX.SetBuddy(&m_TopSizeX);
	m_TopSX.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_TopSX.SetPos(m_Scene->m_bkTop->Size.x);
	m_TopSX.SetDelta(1.0f);	
	
	m_TopSY.SetBuddy(&m_TopSizeY);
	m_TopSY.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_TopSY.SetPos(m_Scene->m_bkTop->Size.y);
	m_TopSY.SetDelta(1.0f);	
	
	m_TopOX.SetBuddy(&m_TopOriginX);
	m_TopOX.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_TopOX.SetPos(m_Scene->m_bkTop->Origin.x);
	m_TopOX.SetDelta(1.0f);	
	
	m_TopOY.SetBuddy(&m_TopOriginY);
	m_TopOY.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_TopOY.SetPos(m_Scene->m_bkTop->Origin.y);
	m_TopOY.SetDelta(1.0f);	

	m_TopOPA.SetRange(0,100);
	m_TopOPA.SetPos((m_Scene->m_bkTop->Opacity*100.0f));
	tmp.Format("%d%%",m_TopOPA.GetPos());
	m_TopAff.SetWindowText(tmp);

	m_TopKeep.SetCheck((m_Scene->m_bkTop->Keep)?1:0);
	m_TopBottom.SetCheck((m_Scene->m_bkTop->Active)?1:0);

	m_TopEdit.SetWindowText(m_Scene->m_bkTop->tex->FileName);

	// -- Left --

	m_LeftSX.SetBuddy(&m_LeftSizeX);
	m_LeftSX.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_LeftSX.SetPos(m_Scene->m_bkLeft->Size.x);
	m_LeftSX.SetDelta(1.0f);	
	
	m_LeftSY.SetBuddy(&m_LeftSizeY);
	m_LeftSY.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_LeftSY.SetPos(m_Scene->m_bkLeft->Size.y);
	m_LeftSY.SetDelta(1.0f);	
	
	m_LeftOX.SetBuddy(&m_LeftOriginX);
	m_LeftOX.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_LeftOX.SetPos(m_Scene->m_bkLeft->Origin.x);
	m_LeftOX.SetDelta(1.0f);	
	
	m_LeftOY.SetBuddy(&m_LeftOriginY);
	m_LeftOY.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_LeftOY.SetPos(m_Scene->m_bkLeft->Origin.y);
	m_LeftOY.SetDelta(1.0f);	

	m_LeftOPA.SetRange(0,100);
	m_LeftOPA.SetPos((m_Scene->m_bkLeft->Opacity*100.0f));
	tmp.Format("%d%%",m_LeftOPA.GetPos());
	m_LeftAff.SetWindowText(tmp);

	m_LeftKeep.SetCheck((m_Scene->m_bkLeft->Keep)?1:0);
	m_LeftRight.SetCheck((m_Scene->m_bkLeft->Active)?1:0);

	m_LeftEdit.SetWindowText(m_Scene->m_bkLeft->tex->FileName);

	// -- Front --

	m_FrontSX.SetBuddy(&m_FrontSizeX);
	m_FrontSX.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_FrontSX.SetPos(m_Scene->m_bkFront->Size.x);
	m_FrontSX.SetDelta(1.0f);	
	
	m_FrontSY.SetBuddy(&m_FrontSizeY);
	m_FrontSY.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_FrontSY.SetPos(m_Scene->m_bkFront->Size.y);
	m_FrontSY.SetDelta(1.0f);	
	
	m_FrontOX.SetBuddy(&m_FrontOriginX);
	m_FrontOX.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_FrontOX.SetPos(m_Scene->m_bkFront->Origin.x);
	m_FrontOX.SetDelta(1.0f);	
	
	m_FrontOY.SetBuddy(&m_FrontOriginY);
	m_FrontOY.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_FrontOY.SetPos(m_Scene->m_bkFront->Origin.y);
	m_FrontOY.SetDelta(1.0f);	

	m_FrontOPA.SetRange(0,100);
	m_FrontOPA.SetPos((m_Scene->m_bkFront->Opacity*100.0f));
	tmp.Format("%d%%",m_FrontOPA.GetPos());
	m_FrontAff.SetWindowText(tmp);

	m_FrontKeep.SetCheck((m_Scene->m_bkFront->Keep)?1:0);
	m_FrontBack.SetCheck((m_Scene->m_bkFront->Active)?1:0);

	m_FrontEdit.SetWindowText(m_Scene->m_bkFront->tex->FileName);

	// caping

	m_OX.SetBuddy(&m_OriginX);
	m_OX.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_OX.SetPos(m_Scene->ClipOrigin.x);
	m_OX.SetDelta(1.0f);	
	m_OY.SetBuddy(&m_OriginY);
	m_OY.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_OY.SetPos(m_Scene->ClipOrigin.y);
	m_OY.SetDelta(1.0f);	
	m_OZ.SetBuddy(&m_OriginZ);
	m_OZ.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_OZ.SetPos(m_Scene->ClipOrigin.z);
	m_OZ.SetDelta(1.0f);	

	m_SX.SetBuddy(&m_SizeX);
	m_SX.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_SX.SetPos(m_Scene->ClipSize.x);
	m_SX.SetDelta(1.0f);	
	m_SY.SetBuddy(&m_SizeY);
	m_SY.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_SY.SetPos(m_Scene->ClipSize.y);
	m_SY.SetDelta(1.0f);	
	m_SZ.SetBuddy(&m_SizeZ);
	m_SZ.SetRange(-MAX_ZOOM, MAX_ZOOM);
	m_SZ.SetPos(m_Scene->ClipSize.z);
	m_SZ.SetDelta(1.0f);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBackWorldCap::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CString tmp;

	tmp.Format("%d%%",m_TopOPA.GetPos());
	m_TopAff.SetWindowText(tmp);
	tmp.Format("%d%%",m_LeftOPA.GetPos());
	m_LeftAff.SetWindowText(tmp);
	tmp.Format("%d%%",m_FrontOPA.GetPos());
	m_FrontAff.SetWindowText(tmp);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
static char CBReadFilter[]={"All supported Images\0*.bmp;*.pcx;*.tif;*.tiff;*.tga;*.jpg;*.jpeg;*.png\0\0"};

void CBackWorldCap::OnBrowsefront() 
{
	CString fileName;
	BXFileDialog dlg(TRUE, TRUE, TRUE);

	CString strTitle("Select Image File");

	dlg.m_ofn.lpstrFilter = CBReadFilter ;
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlg.m_ofn.hwndOwner = AfxGetMainWnd()->m_hWnd; 

	dlg.SetAppearance(BXFileDialog::eAppearance::APPEARANCE_VSDOTNET);

	if (dlg.DoModal()==IDOK)
	{
		m_FrontEdit.SetWindowText(fileName);

		m_Scene->m_bkFront->tex->Type=TEXTURE_FILE;
		m_Scene->m_bkFront->tex->FileName=fileName;
		m_Scene->m_bkFront->tex->Load();
		FrontProp=(float)m_Scene->m_bkFront->tex->SizeX/(float)m_Scene->m_bkFront->tex->SizeY;

		m_FrontSX.SetPos(m_Scene->m_bkFront->tex->SizeX);
		m_FrontSY.SetPos(m_Scene->m_bkFront->tex->SizeY);
		m_FrontBack.SetCheck(1);
	}
	
}

void CBackWorldCap::OnBrowseleft() 
{
	CString fileName;
	BXFileDialog dlg(TRUE, TRUE, TRUE);

	CString strTitle("Select Image File");

	dlg.m_ofn.lpstrFilter = CBReadFilter ;
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlg.m_ofn.hwndOwner = AfxGetMainWnd()->m_hWnd; 

	dlg.SetAppearance(BXFileDialog::eAppearance::APPEARANCE_VSDOTNET);

	if (dlg.DoModal()==IDOK)
	{
		m_LeftEdit.SetWindowText(fileName);

		m_Scene->m_bkLeft->tex->Type=TEXTURE_FILE;
		m_Scene->m_bkLeft->tex->FileName=fileName;
		m_Scene->m_bkLeft->tex->Load();
		LeftProp=(float)m_Scene->m_bkLeft->tex->SizeX/(float)m_Scene->m_bkLeft->tex->SizeY;

		m_LeftSX.SetPos(m_Scene->m_bkLeft->tex->SizeX);
		m_LeftSY.SetPos(m_Scene->m_bkLeft->tex->SizeY);
		m_LeftRight.SetCheck(1);
	}
	
}

void CBackWorldCap::OnBrowsetop() 
{
	CString fileName;
	BXFileDialog dlg(TRUE, TRUE, TRUE);

	CString strTitle("Select Image File");

	dlg.m_ofn.lpstrFilter = CBReadFilter ;
	dlg.m_ofn.lpstrTitle = strTitle;
	dlg.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);
	dlg.m_ofn.hwndOwner = AfxGetMainWnd()->m_hWnd; 

	dlg.SetAppearance(BXFileDialog::eAppearance::APPEARANCE_VSDOTNET);

	if (dlg.DoModal()==IDOK)
	{
		m_TopEdit.SetWindowText(fileName);

		m_Scene->m_bkTop->tex->Type=TEXTURE_FILE;
		m_Scene->m_bkTop->tex->FileName=fileName;
		m_Scene->m_bkTop->tex->Load();
		TopProp=(float)m_Scene->m_bkTop->tex->SizeX/(float)m_Scene->m_bkTop->tex->SizeY;

		m_TopSX.SetPos(m_Scene->m_bkTop->tex->SizeX);
		m_TopSY.SetPos(m_Scene->m_bkTop->tex->SizeY);

		m_TopBottom.SetCheck(1);
	}
	
}

void CBackWorldCap::OnOK()
{
	m_Scene->m_bkTop->Active=(m_TopBottom.GetCheck()!=0);
	m_Scene->m_bkLeft->Active=(m_LeftRight.GetCheck()!=0);
	m_Scene->m_bkFront->Active=(m_FrontBack.GetCheck()!=0);

	m_Scene->m_bkTop->Opacity=(float)m_TopOPA.GetPos()/100.0f;
	m_Scene->m_bkLeft->Opacity=(float)m_LeftOPA.GetPos()/100.0f;
	m_Scene->m_bkFront->Opacity=(float)m_FrontOPA.GetPos()/100.0f;

	m_Scene->m_bkTop->Origin.x=m_TopOX.GetPos();
	m_Scene->m_bkTop->Origin.y=m_TopOY.GetPos();
	m_Scene->m_bkTop->Size.x=m_TopSX.GetPos();
	m_Scene->m_bkTop->Size.y=m_TopSY.GetPos();

	m_Scene->m_bkLeft->Origin.x=m_LeftOX.GetPos();
	m_Scene->m_bkLeft->Origin.y=m_LeftOY.GetPos();
	m_Scene->m_bkLeft->Size.x=m_LeftSX.GetPos();
	m_Scene->m_bkLeft->Size.y=m_LeftSY.GetPos();

	m_Scene->m_bkFront->Origin.x=m_FrontOX.GetPos();
	m_Scene->m_bkFront->Origin.y=m_FrontOY.GetPos();
	m_Scene->m_bkFront->Size.x=m_FrontSX.GetPos();
	m_Scene->m_bkFront->Size.y=m_FrontSY.GetPos();

	m_Scene->ClipOrigin.x=m_OX.GetPos();
	m_Scene->ClipOrigin.y=m_OY.GetPos();
	m_Scene->ClipOrigin.z=m_OZ.GetPos();

	m_Scene->ClipSize.x=m_SX.GetPos();
	m_Scene->ClipSize.y=m_SY.GetPos();
	m_Scene->ClipSize.z=m_SZ.GetPos();

	CDialog::OnOK();
}

void CBackWorldCap::OnTopkeep() 
{
	// TODO: Add your control notification handler code here
	
}

void CBackWorldCap::OnLeftkeep() 
{
	// TODO: Add your control notification handler code here
	
}

void CBackWorldCap::OnFrontkeep() 
{
	// TODO: Add your control notification handler code here
	
}

void CBackWorldCap::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default

	if (m_Scene->m_bkTop->tex->TexID!=-1)
		if (m_TopKeep.GetCheck()!=0) 
			m_TopSY.SetPos((m_TopSX.GetPos()/TopProp));

	if (m_Scene->m_bkLeft->tex->TexID!=-1)
		if (m_LeftKeep.GetCheck()!=0) 
			m_LeftSY.SetPos((m_LeftSX.GetPos()/LeftProp));

	if (m_Scene->m_bkFront->tex->TexID!=-1)
		if (m_FrontKeep.GetCheck()!=0) 
			m_FrontSY.SetPos((m_FrontSX.GetPos()/FrontProp));

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
