// TVTestDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "TVTest.h"
#include "TVTestDlg.h"
#include <direct.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTVTestDlg dialog

CTVTestDlg::CTVTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTVTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTVTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTVTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTVTestDlg)
	DDX_Control(pDX, IDC_TREE3, m_Projects);
	DDX_Control(pDX, IDC_TREE2, m_Hierar);
	DDX_Control(pDX, IDC_TREE1, m_TVFileView);
	DDX_Control(pDX, IDC_TAB1, m_Tabs);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTVTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTVTestDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, OnSelchangeTab1)
	ON_WM_SIZE()
	ON_MESSAGE(WM_DRAWSCENE,OnWmUpdate)
	ON_NOTIFY( TVN_SELCHANGED , IDC_TREE2 , OnSelChanged)
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
	
	m_Tabs.InsertItem(1,"Browse");
	m_Tabs.InsertItem(2,"Hierarchy");
	m_Tabs.InsertItem(3,"Project");
	TCHAR  szWorkDir[MAX_PATH];
    
 // TODO: Add extra initialization here
 // Here we subclass our CDirTreeCtrl

	m_TVFileView.DisplayTree( NULL, TRUE);
	m_Hierar.ShowWindow(SW_HIDE);
	m_Projects.ShowWindow(SW_HIDE);



	imgl.Create(16,16,ILC_COLOR24,8,1);

	bmp1.LoadBitmap(IDB_HROOT);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HGROUP);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HCAM);
	imgl.Add(&bmp1,RGB(255,255,255));
	bmp1.Detach();

	bmp1.LoadBitmap(IDB_HLIGHT);
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

	m_Hierar.SetImageList(&imgl,TVSIL_NORMAL);

	return TRUE;  // return TRUE  unless you set the focus to a control
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

void CTVTestDlg::OnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult) 
{

	switch(m_Tabs.GetCurSel())
	{
	case 0:
		m_Hierar.ShowWindow(SW_HIDE);
		m_TVFileView.ShowWindow(SW_SHOWNORMAL);
		m_Projects.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_Hierar.ShowWindow(SW_SHOWNORMAL);
		m_TVFileView.ShowWindow(SW_HIDE);
		m_Projects.ShowWindow(SW_HIDE);
		break;
	case 2:
		m_Hierar.ShowWindow(SW_HIDE);
		m_TVFileView.ShowWindow(SW_HIDE);
		m_Projects.ShowWindow(SW_SHOWNORMAL);
		break;
	}
	
	*pResult = 0;
}


void CTVTestDlg::OnOK() 
{
}

void CTVTestDlg::OnCancel() 
{
}

void CTVTestDlg::OnSize(UINT nType,int cx,int cy)
{
	CDialog::OnSize(nType,cx,cy);

	if (IsWindow(m_Tabs.m_hWnd))
	{
		m_Hierar.MoveWindow(0,0,cx,cy-24);
		m_TVFileView.MoveWindow(0,0,cx,cy-24);
		m_Projects.MoveWindow(0,0,cx,cy-24);

		m_Tabs.MoveWindow(0,cy-23,cx,20);

	}
}

void CTVTestDlg::RecCalcBone(Bone *daBone,HTREEITEM &hItem)
{
	Bone *daBone2;

	HTREEITEM hItem2=m_Hierar.InsertItem(_T(daBone->Name),7,7,hItem);
	m_Hierar.SetItemParam(hItem2,(LPARAM)daBone);

	daBone2=daBone->FirstBone;
	while(daBone2!=NULL)
	{
		RecCalcBone(daBone2,hItem2);
		daBone2=daBone2->Next;
	}
}


void CTVTestDlg::UpdateHierTree(Desk *dk)
{
	Object *daObj;
	Camera *daCam;
	//Emitter *daPart;
	Shape *daShp;
	CLight *daLight;
	Skeletton *daSkel;
	Segment *daSeg;
	Bone *daBone;

	dadk=dk;

	m_Hierar.SetRedraw(FALSE);
	m_Hierar.DeleteAllItems();

	daRoot=m_Hierar.InsertItem(_T("Root"),0,0);

	HTREEITEM hItem;

	// Obj
	for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T(daObj->Name),4,4,daRoot),(LPARAM)daObj);
	}

	// cam
	for (daCam=dk->FirstCam;daCam!=NULL;daCam=daCam->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T(daCam->Name),2,2,daRoot),(LPARAM)daCam);
	}

	// light
	for (daLight=dk->FirstLight;daLight!=NULL;daLight=daLight->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T(daLight->Name),3,3,daRoot),(LPARAM)daLight);
	}

	// shape
	for (daShp=dk->FirstShape;daShp!=NULL;daShp=daShp->Next)
	{
		m_Hierar.SetItemParam(m_Hierar.InsertItem(_T(daShp->Name),5,5,daRoot),(LPARAM)daShp);
	}

	// skeletton
	for (daSkel=dk->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
	{
		hItem=m_Hierar.InsertItem(_T(daSkel->Name),6,6,daRoot);
		m_Hierar.SetItemParam(hItem,(LPARAM)daSkel);

		for (daBone=daSkel->bone;daBone!=NULL;daBone=daBone->Next)
		{
			RecCalcBone(daBone,hItem);
		}
	}

	m_Hierar.SetRedraw();
}

void CTVTestDlg::UpdateDeskTree(void)
{
	bool Selected;

	HTREEITEM dait=TreeView_GetFirstVisible(m_Hierar.m_hWnd);

	while (dait!=NULL)
	{
		Selected=m_Hierar.IsItemSelected(dait);

		switch (m_Hierar.GetItemId(dait))
		{
			// Camera
		case 2:
			((Camera*)m_Hierar.GetItemParam(dait))->Selected=Selected;
			break;
			// Light
		case 3:
			((CLight*)m_Hierar.GetItemParam(dait))->Selected=Selected;
			break;
			// object
		case 4:
			((Object*)m_Hierar.GetItemParam(dait))->Selected=Selected;
			break;
			// shape
		case 5:
			((Shape*)m_Hierar.GetItemParam(dait))->Selected=Selected;
			break;
			// skelette
		case 6:
			((Skeletton*)m_Hierar.GetItemParam(dait))->Selected=Selected;
			break;

		default:
			break;
		}
		dait=TreeView_GetNextVisible(m_Hierar.m_hWnd,dait);
    
	}


	DrawViews();
}
bool CTVTestDlg::SetItemHiding(HTREEITEM dait,bool Hidden)
{
	bool value=false;

	switch (m_Hierar.GetItemId(dait))
	{
		// Camera
	case 2:
		value|=(((Camera*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((Camera*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// Light
	case 3:
		value|=(((CLight*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((CLight*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// object
	case 4:
		value|=(((Object*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((Object*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// shape
	case 5:
		value|=(((Shape*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((Shape*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
		break;
		// skelette
	case 6:
		value|=(((Skeletton*)m_Hierar.GetItemParam(dait))->Hided!=Hidden);
		((Skeletton*)m_Hierar.GetItemParam(dait))->Hided=Hidden;
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
	bool Hided;

	if (RecurseHide(daRoot,false)) DrawViews();
}

LRESULT CTVTestDlg::OnWmUpdate(WPARAM wParam, LPARAM lParam) 
{
	UpdateHierTree((Desk *)wParam);
	return FALSE; 
}

LRESULT CTVTestDlg::OnSelChanged(WPARAM wParam, LPARAM lParam) 
{
	UpdateDeskTree();
	return false;
}
