// TVTestDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "TVTest.h"
#include "TVTestDlg.h"
#include "MatBrowser.h"
//#include "
#include <direct.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTVTestDlg dialog
extern int GCurSelect;
extern CKPluginManager *GKPlugins;
extern CKOption *KOption;
int m_TextureLayer;

CTVTestDlg::CTVTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTVTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTVTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTVTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTVTestDlg)
	DDX_Control(pDX, IDC_TWEAKUV, m_TweakUV);
	DDX_Control(pDX, IDC_LAYERSTRING, m_LayerString);
	DDX_Control(pDX, IDC_HIDETWEAKUV, m_HideTweakUV);
	DDX_Control(pDX, IDC_PROJECT, m_Project);
	DDX_Control(pDX, IDC_PREFABS, m_Prefabs);
	DDX_Control(pDX, IDC_CLICKAPPLYPOLY, m_ClickApplyPoly);
	DDX_Control(pDX, IDC_CLICKAPPLYOBJ, m_ClickApplyObject);
	DDX_Control(pDX, IDC_TREE2, m_Hierar);
	DDX_Control(pDX, IDC_TAB1, m_Tabs1);
	DDX_Control(pDX, IDC_TAB2, m_Tabs2);
	DDX_Control(pDX, IDC_TAB3, m_Tabs3);
	DDX_Control(pDX, IDC_TAB4, m_Tabs4);
	DDX_Control(pDX, IDC_TAB5, m_Tabs5);
	DDX_Control(pDX, IDC_LAYER1, m_Layer1);
	DDX_Control(pDX, IDC_LAYER2, m_Layer2);
	DDX_Control(pDX, IDC_LAYER3, m_Layer3);
	DDX_Control(pDX, IDC_LAYER4, m_Layer4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTVTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTVTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_NOTIFY( TVN_SELCHANGED , IDC_TREE2 , OnSelChanged)
	ON_BN_CLICKED(IDC_TAB1,OnBtTab1Clicked)
	ON_BN_CLICKED(IDC_TAB2,OnBtTab2Clicked)
	ON_BN_CLICKED(IDC_TAB3,OnBtTab3Clicked)
	ON_BN_CLICKED(IDC_TAB4,OnBtTab4Clicked)
	ON_BN_CLICKED(IDC_TAB5,OnBtTab5Clicked)
	ON_BN_CLICKED(IDC_CLICKAPPLYOBJ, OnClickapplyobj)
	ON_BN_CLICKED(IDC_CLICKAPPLYPOLY, OnClickapplypoly)
	ON_BN_CLICKED(IDC_LAYER1, OnLayer1)
	ON_BN_CLICKED(IDC_LAYER2, OnLayer2)
	ON_BN_CLICKED(IDC_LAYER3, OnLayer3)
	ON_BN_CLICKED(IDC_LAYER4, OnLayer4)
	ON_BN_CLICKED(IDC_HIDETWEAKUV, OnHidetweakuv)
	ON_MESSAGE(WM_DRAWSCENE,OnWmUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTVTestDlg message handlers

BOOL CTVTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	p1Hiden=false;
	p2Hiden=false;
/*
	m_HideTweakUV.SetFlat(false);
	m_HideLayer.SetFlat(false);

	m_HideLayer.SetAlwaysTrack(false);
	*/
	m_TweakUVDiag.Create(MAKEINTRESOURCE(IDD_TWEAKUV),this);
	/*
	m_Tabs.InsertItem(1,"B");
	m_Tabs.InsertItem(2,"H");
	m_Tabs.InsertItem(3,"M");
	m_Tabs.InsertItem(4,"L");
	m_Tabs.InsertItem(5,"P");
*/
 // TODO: Add extra initialization here
 // Here we subclass our CDirTreeCtrl

	m_Hierar.ShowWindow(SW_HIDE);

	m_cDialog.Create(IDD_TSCROLL_DIALOG,this);
	m_cDialog.ShowWindow(SW_SHOWNORMAL);

	m_Browser.Create(IDD_MATBROWSER,this);
	m_Browser.ShowWindow(SW_HIDE);


	imgl.Create(16,16,ILC_COLOR24,8,1);
	imgpref.Create(16,16,ILC_COLOR24,2,1);

	bmp1.LoadBitmap(IDB_HGROUP);
	imgpref.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HPREFAB);
	imgpref.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();


	bmp1.LoadBitmap(IDB_HROOT);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HGROUP);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HCAM);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HENTITY);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HOBJ);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HSHAPE);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HSKELETTON);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HBONE);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HPATCH);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();


	// switch bmps
	m_Tabs1.SetFlat();
	m_Tabs1.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DESKBUILD)),RGB(255,255,255));

	m_Tabs2.SetFlat();
	m_Tabs2.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DESKHIERAR)),RGB(255,255,255));

	m_Tabs3.SetFlat();
	m_Tabs3.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DESKMAPS)),RGB(255,255,255));

	m_Tabs4.SetFlat();
	m_Tabs4.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DESKPREFABS)),RGB(255,255,255));

	m_Tabs5.SetFlat();
	m_Tabs5.SetBitmaps(::LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_DESKPROJECT)),RGB(255,255,255));

/*
	bmp1.LoadBitmap(IDB_DESKBUILD);
	m_Tabs1.SetBitmap(bmp1);
	bmp1.Detach();
*/
	bmp1.LoadBitmap(IDB_DESKHIERAR);
	m_Tabs2.SetBitmap(bmp1);
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_DESKMAPS);
	m_Tabs3.SetBitmap(bmp1);
	bmp1.Detach();


	bmp1.LoadBitmap(IDB_DESKPREFABS);
	m_Tabs4.SetBitmap(bmp1);
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_DESKPROJECT);
	m_Tabs5.SetBitmap(bmp1);
	bmp1.Detach();

	m_Hierar.SetImageList(&imgl,TVSIL_NORMAL);
	m_Prefabs.SetImageList(&imgpref,TVSIL_NORMAL);

	// test prj/prefabs
	
	//m_Prefabs.InsertItem("Prefabs",0,0);


	UpdatePrefabTree();

	OnBtTab1Clicked();
	OnLayer1();
	m_Layer1.SetCheck(1);
	m_TweakUVDiag.ShowWindow(SW_HIDE);


	// projet

	prjList.Create(16,16,ILC_COLOR24,2,1);

	bmp1.LoadBitmap(IDB_HPROJECT);
	prjList.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HGROUP);
	prjList.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HSCRIPT);
	prjList.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HOBJ);
	prjList.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	m_Project.SetImageList(&prjList,TVSIL_NORMAL);
	
	
	//m_Project.AddFileToProject("zobby2.2x");
	//m_Prj.SaveProject(&m_Project,"yop.xml");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTVTestDlg::UpdatePrefabTree(void)
{
	m_Prefabs.DeleteAllItems();

	if (!KOption->GetPrefabDir(0).IsEmpty())
	{
		HTREEITEM FirstPref=m_Prefabs.InsertItem("Prefabs",0,0,TVI_ROOT);
		for (int i=0;i<KOption->GetnbPrefabDir();i++)
		{
			RecurseFindPrefabs(&m_Prefabs,FirstPref,KOption->GetPrefabDir(i),"");
		}
		m_Prefabs.Expand(FirstPref,TVE_EXPAND);
	}	
	m_Prefabs.CanDropFile=true;

}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTVTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTVTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
/*
void CTVTestDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{

	switch(m_Tabs.GetCurSel())
	{
	case 0:
		m_Hierar.ShowWindow(SW_HIDE);
		m_cDialog.ShowWindow(SW_SHOWNORMAL);
		m_Browser.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_Hierar.ShowWindow(SW_SHOWNORMAL);
		m_cDialog.ShowWindow(SW_HIDE);
		m_Browser.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_Hierar.ShowWindow(SW_HIDE);
		m_cDialog.ShowWindow(SW_HIDE);
		m_Browser.ShowWindow(SW_SHOWNORMAL);
		break;
	}
	
	*pResult = 0;
}
*/

void CTVTestDlg::OnOK() 
{
}

void CTVTestDlg::OnCancel() 
{
}

void CTVTestDlg::OnSize(UINT nType,int cx,int cy)
{
	CDialog::OnSize(nType,cx,cy);

	if (IsWindow(m_Hierar.m_hWnd))
	{
		m_Hierar.MoveWindow(0,0,cx,cy-cx/5-5);

		m_Tabs1.MoveWindow(0,cy-cx/5,cx/5,cx/5);
		m_Tabs2.MoveWindow((cx/5),cy-cx/5,cx/5,cx/5);
		m_Tabs3.MoveWindow((cx/5)*2,cy-cx/5,cx/5,cx/5);
		m_Tabs4.MoveWindow((cx/5)*3,cy-cx/5,cx/5,cx/5);
		m_Tabs5.MoveWindow((cx/5)*4,cy-cx/5,cx/5,cx/5);

		m_cDialog.MoveWindow(0,0,cx,cy-cx/5-5);

		m_Prefabs.MoveWindow(0,0,cx,cy-cx/5-5);
		m_Project.MoveWindow(0,0,cx,cy-cx/5-5);

		//m_Browser.MoveWindow(0,0,cx,cy-cx/5-2-185);

		m_ClickApplyPoly.MoveWindow(0,cy-2-cx/5-22,cx/2,22);
		m_ClickApplyObject.MoveWindow(cx/2,cy-2-cx/5-22,cx/2,22);

		if (p1Hiden)
		{
			m_Browser.MoveWindow(0,0,cx,cy-cx/5-2-92);
			m_TweakUV.MoveWindow(0,cy-cx/5-2-80,cx,20);
			m_HideTweakUV.SetWindowPos(&m_TweakUV,10,cy-cx/5-2-82,cx-20,14,0);

			m_TweakUVDiag.ShowWindow(SW_HIDE);//MoveWindow(2,cy-cx/5-2-166,cx-4,90);
		}		
		else
		{
			m_Browser.MoveWindow(0,0,cx,cy-cx/5-2-185);
			m_TweakUV.MoveWindow(0,cy-cx/5-2-180,cx,112);
			m_HideTweakUV.SetWindowPos(&m_TweakUV,10,cy-cx/5-2-182,cx-20,14,0);

			m_TweakUVDiag.MoveWindow(2,cy-cx/5-2-166,cx-4,90);
			if (m_Tabs3.GetCheck())
				m_TweakUVDiag.ShowWindow(SW_SHOWNORMAL);//MoveWindow(2,cy-cx/5-2-166,cx-4,90);
			else
				m_TweakUVDiag.ShowWindow(SW_HIDE);//MoveWindow(2,cy-cx/5-2-166,cx-4,90);
		}

		m_LayerString.MoveWindow(0,cy-cx/5-2-60,cx,35);


		

		m_Layer1.MoveWindow(4,cy-cx/5-2-44,(cx-8)/4,15);
		m_Layer2.MoveWindow(4+((cx-8)/4),cy-cx/5-2-44,(cx-8)/4,15);
		m_Layer3.MoveWindow(4+((cx-8)/4)*2,cy-cx/5-2-44,(cx-8)/4,15);
		m_Layer4.MoveWindow(4+((cx-8)/4)*3,cy-cx/5-2-44,(cx-8)/4,15);
		
		if (GCurPlug!=NULL)
		{
			GCurPlug->ReSize(cx,cy-40);
		}

	}
}

void CTVTestDlg::RecCalcBone(CKBone *daBone,HTREEITEM &hItem)
{
	CKBone *daBone2;

	HTREEITEM hItem2=m_Hierar.InsertItem(daBone->Name,7,7,hItem);
	m_Hierar.SetItemParam(hItem2,(LPARAM)daBone);

	daBone2=daBone->FirstBone;
	while(daBone2!=NULL)
	{
		RecCalcBone(daBone2,hItem2);
		daBone2=daBone2->Next;
	}
}


void CTVTestDlg::UpdateHierTree(CKScene *_Scene)
{
	CKMesh *daMesh;
	CKCamera *daCam;
	CKShape *daShp;
	CKEntity *daEntity;
	CKPatch *daPatch;
	CKSkeleton *daSkel;
	CKBone *daBone;

	m_Scene=_Scene;

	m_Hierar.SetRedraw(FALSE);
	m_Hierar.DeleteAllItems();

	daRoot=m_Hierar.InsertItem(_T("Root"),0,0);

	HTREEITEM hItem;

	// Obj
	for (daMesh=m_Scene->FirstMesh;daMesh!=NULL;daMesh=daMesh->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T(daMesh->Name),4,4,daRoot),(LPARAM)daMesh);
	}

	// cam
	for (daCam=m_Scene->FirstCam;daCam!=NULL;daCam=daCam->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T(daCam->Name),2,2,daRoot),(LPARAM)daCam);
	}

	// entity
	for (daEntity=m_Scene->FirstEntity;daEntity!=NULL;daEntity=daEntity->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T("Entity"),3,3,daRoot),(LPARAM)daEntity);
	}

	// shape
	for (daShp=m_Scene->FirstShape;daShp!=NULL;daShp=daShp->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T(daShp->Name),5,5,daRoot),(LPARAM)daShp);
	}

	// skeletton
	for (daSkel=m_Scene->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
	{
		hItem=m_Hierar.InsertItem(_T(daSkel->Name),6,6,daRoot);
		m_Hierar.SetItemParam(hItem,(LPARAM)daSkel);

		for (daBone=daSkel->bone;daBone!=NULL;daBone=daBone->Next)
		{
			RecCalcBone(daBone,hItem);
		}
	}

	// patch
	for (daPatch=m_Scene->FirstPatch;daPatch!=NULL;daPatch=daPatch->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T(daPatch->Name),8,8,daRoot),(LPARAM)daPatch);
	}

	m_Hierar.Expand(daRoot,TVE_EXPAND ); 
	m_Browser.m_Scene=m_Scene;
	m_Hierar.SetRedraw();
}

void CTVTestDlg::UpdateDeskTree(void)
{
	bool Selected;
	CKMesh *daMesh;
	CKCamera *daCam;
	CKEntity *daEntity;
	CKPatch *daPatch;
	CKShape *daShp;
	CKSkeleton *daSkel;

	HTREEITEM dait=TreeView_GetFirstVisible(m_Hierar.m_hWnd);

	while (dait!=NULL)
	{
		Selected=m_Hierar.IsItemSelected(dait);

		switch (m_Hierar.GetItemId(dait))
		{
			// Camera
		case 2:
			daCam=((CKCamera*)m_Hierar.GetItemParam(dait));
			m_Scene->SingleCamera(daCam,Selected);

			break;
			// Entity
		case 3:
			daEntity=((CKEntity*)m_Hierar.GetItemParam(dait));
			m_Scene->SingleEntity(daEntity,Selected);
			break;
			// object
		case 4:
			daMesh=((CKMesh*)m_Hierar.GetItemParam(dait));
			m_Scene->SingleMesh(daMesh,Selected);

			break;
			// shape
		case 5:
			daShp=((CKShape*)m_Hierar.GetItemParam(dait));
			m_Scene->SingleShape(daShp,Selected);
			break;
			// skelette
		case 6:
			daSkel=((CKSkeleton*)m_Hierar.GetItemParam(dait));
			m_Scene->SingleSkeleton(daSkel,Selected);
			break;
			// patch
		case 8:
			daPatch=((CKPatch*)m_Hierar.GetItemParam(dait));
			m_Scene->SinglePatch(daPatch,Selected);
			break;

		default:
			break;
		}
		dait=TreeView_GetNextVisible(m_Hierar.m_hWnd,dait);
    
	}

	m_Browser.m_Scene->UpdateSmthSel();

	DrawViews();
}
bool CTVTestDlg::SetItemHiding(HTREEITEM dait,bool Hidden)
{
	bool value=false;

	switch (m_Hierar.GetItemId(dait))
	{
		// Camera
	case 2:
		value|=(((CKCamera*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((CKCamera*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// Entity
	case 3:
		value|=(((CKEntity*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((CKEntity*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// object
	case 4:
		value|=(((CKMesh*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((CKMesh*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// shape
	case 5:
		value|=(((CKShape*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((CKShape*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// skelette
	case 6:
		value|=(((CKSkeleton*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((CKSkeleton*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// patch
	case 8:
		value|=(((CKPatch*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((CKPatch*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;

	default:
		break;
	}

	return value;
}

bool CTVTestDlg::RecurseHide(HTREEITEM dait,bool Hidden)
{
	bool Value=false,Hided;
	HTREEITEM dait2=m_Hierar.GetChildItem(dait);
	
	while (dait2!=NULL)
	{
		Hided=m_Hierar.IsItemChecked(dait2);

		if (m_Hierar.GetItemId(dait2)==1)
			Value|=RecurseHide(dait2,m_Hierar.IsItemChecked(dait2)|Hidden);
		else
			Value|=SetItemHiding(dait2,m_Hierar.IsItemChecked(dait2)|Hidden);
		
		dait2=m_Hierar.GetNextItem(dait2, TVGN_NEXT);
	}
	return Value;

}
void CTVTestDlg::UpdateHiding(void)
{
	if (RecurseHide(daRoot,false)) DrawViews();
}

LRESULT CTVTestDlg::OnWmUpdate(WPARAM wParam, LPARAM lParam) 
{
	UpdateHierTree((CKScene *)wParam);
	return FALSE; 
}

LRESULT CTVTestDlg::OnSelChanged(WPARAM wParam, LPARAM lParam) 
{
	UpdateDeskTree();
	return false;
}

void CTVTestDlg::OnBtTab1Clicked()
{
	m_Tabs1.SetCheck(1);
	m_Tabs2.SetCheck(0);
	m_Tabs3.SetCheck(0);
	m_Tabs4.SetCheck(0);
	m_Tabs5.SetCheck(0);

	m_cDialog.ShowWindow(SW_SHOWNORMAL);
	m_Hierar.ShowWindow(SW_HIDE);
	m_Browser.ShowWindow(SW_HIDE);
	m_Prefabs.ShowWindow(SW_HIDE);
	m_Project.ShowWindow(SW_HIDE);
	
	m_TweakUV.ShowWindow(SW_HIDE);
	m_HideTweakUV.ShowWindow(SW_HIDE);
	m_TweakUVDiag.ShowWindow(SW_HIDE);

	ShowMappingTool(false);

}
void CTVTestDlg::OnBtTab2Clicked()
{
	m_Tabs1.SetCheck(0);
	m_Tabs2.SetCheck(1);
	m_Tabs3.SetCheck(0);
	m_Tabs4.SetCheck(0);
	m_Tabs5.SetCheck(0);

	m_cDialog.ShowWindow(SW_HIDE);
	m_Hierar.ShowWindow(SW_SHOWNORMAL);
	m_Browser.ShowWindow(SW_HIDE);
	m_Prefabs.ShowWindow(SW_HIDE);
	m_Project.ShowWindow(SW_HIDE);

	m_TweakUV.ShowWindow(SW_HIDE);
	m_HideTweakUV.ShowWindow(SW_HIDE);
	m_TweakUVDiag.ShowWindow(SW_HIDE);

	ShowMappingTool(false);

}
void CTVTestDlg::OnBtTab3Clicked()
{
	m_Tabs1.SetCheck(0);
	m_Tabs2.SetCheck(0);
	m_Tabs3.SetCheck(1);
	m_Tabs4.SetCheck(0);
	m_Tabs5.SetCheck(0);

	m_cDialog.ShowWindow(SW_HIDE);
	m_Hierar.ShowWindow(SW_HIDE);
	m_Browser.ShowWindow(SW_SHOWNORMAL);
	m_Prefabs.ShowWindow(SW_HIDE);
	m_Project.ShowWindow(SW_HIDE);

	m_TweakUV.ShowWindow(SW_SHOWNORMAL);
	m_HideTweakUV.ShowWindow(SW_SHOWNORMAL);
	if (!p1Hiden) m_TweakUVDiag.ShowWindow(SW_SHOWNORMAL);

	ShowMappingTool(true);

}
void CTVTestDlg::OnBtTab4Clicked()
{
	m_Tabs1.SetCheck(0);
	m_Tabs2.SetCheck(0);
	m_Tabs3.SetCheck(0);
	m_Tabs4.SetCheck(1);
	m_Tabs5.SetCheck(0);

	m_cDialog.ShowWindow(SW_HIDE);
	m_Hierar.ShowWindow(SW_HIDE);
	m_Browser.ShowWindow(SW_HIDE);
	m_Prefabs.ShowWindow(SW_SHOWNORMAL);
	m_Project.ShowWindow(SW_HIDE);

	m_TweakUV.ShowWindow(SW_HIDE);
	m_HideTweakUV.ShowWindow(SW_HIDE);
	m_TweakUVDiag.ShowWindow(SW_HIDE);

	ShowMappingTool(false);

}
void CTVTestDlg::OnBtTab5Clicked()
{
	m_Tabs1.SetCheck(0);
	m_Tabs2.SetCheck(0);
	m_Tabs3.SetCheck(0);
	m_Tabs4.SetCheck(0);
	m_Tabs5.SetCheck(1);

	m_cDialog.ShowWindow(SW_HIDE);
	m_Hierar.ShowWindow(SW_HIDE);
	m_Browser.ShowWindow(SW_HIDE);
	m_Prefabs.ShowWindow(SW_HIDE);
	m_Project.ShowWindow(SW_SHOWNORMAL);

	m_TweakUV.ShowWindow(SW_HIDE);
	m_HideTweakUV.ShowWindow(SW_HIDE);
	m_TweakUVDiag.ShowWindow(SW_HIDE);

	ShowMappingTool(false);

}
void CTVTestDlg::ShowMappingTool(bool ShowIt)
{
	m_ClickApplyPoly.ShowWindow((ShowIt?SW_SHOWNORMAL:SW_HIDE));
	m_ClickApplyObject.ShowWindow((ShowIt?SW_SHOWNORMAL:SW_HIDE));
	m_LayerString.ShowWindow((ShowIt?SW_SHOWNORMAL:SW_HIDE));
	m_Layer1.ShowWindow((ShowIt?SW_SHOWNORMAL:SW_HIDE));
	m_Layer2.ShowWindow((ShowIt?SW_SHOWNORMAL:SW_HIDE));
	m_Layer3.ShowWindow((ShowIt?SW_SHOWNORMAL:SW_HIDE));
	m_Layer4.ShowWindow((ShowIt?SW_SHOWNORMAL:SW_HIDE));
}

void CTVTestDlg::OnClickapplyobj() 
{
	m_ClickApplyPoly.SetCheck(0);
	if (m_ClickApplyObject.GetCheck()==BST_UNCHECKED)
	{
		FunctionID=GCurSelect;
	}
	else
	{
		FunctionID=EDIT_CLICKAPPLYMESH;
	}
}

void CTVTestDlg::OnClickapplypoly() 
{
	m_ClickApplyObject.SetCheck(0);
	if (m_ClickApplyPoly.GetCheck()==BST_UNCHECKED)
	{
		FunctionID=GCurSelect;
	}
	else
	{
		FunctionID=EDIT_CLICKAPPLYPOLY;
	}
}

void CTVTestDlg::OnLayer1() 
{
	m_TextureLayer=1;
}

void CTVTestDlg::OnLayer2() 
{
	m_TextureLayer=2;
}

void CTVTestDlg::OnLayer3() 
{
	m_TextureLayer=3;
}

void CTVTestDlg::OnLayer4() 
{
	m_TextureLayer=4;
}


void CTVTestDlg::OnHidetweakuv() 
{
	RECT rc;
	GetClientRect(&rc);
	int cx=rc.right-rc.left;
	int cy=rc.bottom-rc.top;

	p1Hiden=!p1Hiden;
	if (p1Hiden)
	{
		m_Browser.MoveWindow(0,0,cx,cy-cx/5-2-92);
		m_TweakUV.MoveWindow(0,cy-cx/5-2-80,cx,20);
		m_HideTweakUV.SetWindowPos(&m_TweakUV,10,cy-cx/5-2-82,cx-20,14,0);

		m_TweakUVDiag.ShowWindow(SW_HIDE);//MoveWindow(2,cy-cx/5-2-166,cx-4,90);
	}
	else
	{
		m_Browser.MoveWindow(0,0,cx,cy-cx/5-2-185);
		m_TweakUV.MoveWindow(0,cy-cx/5-2-180,cx,112);
		m_HideTweakUV.SetWindowPos(&m_TweakUV,10,cy-cx/5-2-182,cx-20,14,0);
		m_TweakUVDiag.MoveWindow(2,cy-cx/5-2-166,cx-4,90);
		m_TweakUVDiag.ShowWindow(SW_SHOWNORMAL);
	}
}

bool CTVTestDlg::RecurseFindPrefabs(CTreeCtrl *pTree,HTREEITEM Parent,CString Path,CString DispPath)
{
	CString	strPath, strPattern;
    CString Cards[99];
	HANDLE					hFind = NULL;
	WIN32_FIND_DATA			FindFileData;
	std::vector<CString>	VectorNames;
	std::vector<CString>	VectorDirs;
	bool bRC;
	int i;

	int CardAV=0;


	for (i=0;i<GKPlugins->FilePlugins.size();i++)
	{
		if (GKPlugins->FilePlugins[i]->SupportReading())
		{
			Cards[CardAV++]=GKPlugins->FilePlugins[i]->GetFilter();
		}
	}
	
	bool HasFileInPath=false;
	bool HasDirsInPath=false;

	// seek for files
    for (i=0;i<CardAV;i++)
    {
	    strPattern = Path + "\\"+CString(Cards[i]);//"\\*.bmp";
	    hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
	    if(hFind != INVALID_HANDLE_VALUE)
	    {
	        if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
	           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
	           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
	           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
	        {  	  
                VectorNames.push_back(CString(FindFileData.cFileName));
				HasFileInPath=true;
	        }  
            bRC = TRUE;

	        while(bRC)
	        {
		        bRC = ::FindNextFile(hFind, &FindFileData);
		        if(bRC)
		        {
			        // filter off the system files and directories
			        if(!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
			           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
			           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
			           !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
			        {
				        VectorNames.push_back(CString(FindFileData.cFileName));
						HasFileInPath=true;
			        }
		        }
	        } // end of while loop
	        ::FindClose(hFind);
        }
    }
	// seek for dirs

	strPattern = Path + "\\*.*";
	hFind = ::FindFirstFile(strPattern, &FindFileData);	// strat search	
	if(hFind != INVALID_HANDLE_VALUE)
	{
		if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
	       !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
	       !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
	       !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
	    {  	  
			if ((CString(FindFileData.cFileName)!=".")&&(CString(FindFileData.cFileName)!=".."))
			{
	            VectorDirs.push_back(CString(FindFileData.cFileName));
				HasDirsInPath=true;
			}
	    }  

        bRC = TRUE;

	    while(bRC)
	    {
		    bRC = ::FindNextFile(hFind, &FindFileData);
		    if(bRC)
		    {
			    if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)  &&
			       !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM)     &&
			       !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)     &&
			       !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_TEMPORARY))
			    {
					if ((CString(FindFileData.cFileName)!=".")&&(CString(FindFileData.cFileName)!=".."))
					{
						VectorDirs.push_back(CString(FindFileData.cFileName));
						HasDirsInPath=true;
					}
			    }
		    }
	    } // end of while loop
	    ::FindClose(hFind);
    }

	// add tree items
	bool UnderHas=false;


	HTREEITEM prt;

	if (HasFileInPath)
	{
		//prt=pTree->InsertItem(DispPath,0,0,Parent);
		for ( vector<CString>::iterator j = VectorNames.begin();j != VectorNames.end(); j++)
		{
			pTree->InsertItem(*j,1,1,Parent);
		}
	}

	if (HasDirsInPath)
	{
		for ( vector<CString>::iterator j = VectorDirs.begin();j != VectorDirs.end(); j++)
		{
			/*
			HTREEITEM prt2;

			if (HasFileInPath)
				prt2=pTree->InsertItem(*j,0,0,prt);
			else
				prt2=pTree->InsertItem(*j,0,0,Parent);
*/
			HTREEITEM prt2=pTree->InsertItem(*j,0,0,Parent);
			CString strRecPath=Path+"\\"+ *j;
			if (!RecurseFindPrefabs(pTree,prt2,strRecPath,*j))
				
				pTree->DeleteItem(prt2);
			else
				UnderHas=true;
		}
	}
	return (HasFileInPath|UnderHas);
}
