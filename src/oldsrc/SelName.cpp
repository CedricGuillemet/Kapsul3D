// tlctrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SelName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelName dialog

CSelName::CSelName(CWnd* pParent /*=NULL*/)
	: CDialog(CSelName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelName)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSelName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelName)
	DDX_Control(pDX, IDC_LIST2, m_List);
	DDX_Control(pDX, IDC_LISTTYPE, m_Type);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelName, CDialog)
	//{{AFX_MSG_MAP(CSelName)
	ON_BN_CLICKED(IDC_ALL, OnAll)
	ON_BN_CLICKED(IDC_NONE, OnNone)
	ON_BN_CLICKED(IDC_INVERT, OnInvert)
	ON_CBN_SELCHANGE(IDC_LISTTYPE, OnSelchangeListtype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelName message handlers

BOOL CSelName::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    ListView_SetExtendedListViewStyle (m_List.m_hWnd, LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);

    HBITMAP hCam,hObj,hLight,hSkel,hPart,hPatch,hShape;

	
	
	// Set up the image list.
	
    m_imglist.Create ( 16, 16, ILC_COLOR16 | ILC_MASK, 6, 1 );

    hCam = reinterpret_cast<HBITMAP>(::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_HCAM),IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR ));
	hObj = reinterpret_cast<HBITMAP>(::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_HOBJ),IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR ));
	hLight = reinterpret_cast<HBITMAP>(::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_HLIGHT),IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR ));
	hSkel = reinterpret_cast<HBITMAP>(::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_HSKEL),IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR ));
	//hPart = reinterpret_cast<HBITMAP>(::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_HPART),IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR ));
	//hPatch = reinterpret_cast<HBITMAP>(::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_HPATCH),IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR ));
	hShape = reinterpret_cast<HBITMAP>(::LoadImage ( AfxGetResourceHandle(), MAKEINTRESOURCE(IDB_HSHAPE),IMAGE_BITMAP, 16, 16, LR_DEFAULTCOLOR ));


    m_imglist.Add ( CBitmap::FromHandle(hCam),RGB(192,192,192));
	m_imglist.Add ( CBitmap::FromHandle(hObj) ,RGB(192,192,192));
	m_imglist.Add ( CBitmap::FromHandle(hLight) ,RGB(192,192,192));
	m_imglist.Add ( CBitmap::FromHandle(hSkel) ,RGB(192,192,192));
	m_imglist.Add ( CBitmap::FromHandle(hShape) ,RGB(192,192,192));

    m_List.SetImageList ( &m_imglist, LVSIL_SMALL );
    m_List.InsertColumn ( 0, _T("List"), LVCFMT_LEFT, 0, 0 );

    // And set up the list items.


    m_List.SetColumnWidth ( 0, LVSCW_AUTOSIZE_USEHEADER );

	m_Type.SetCurSel(0);
	ListIt();

	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSelName::ListIt(void)
{

	int daType=m_Type.GetCurSel();

	Object *daObj;
	Shape *daShp;
	Camera *daCam;
	CEntity *daEntity;
	CKPatch *daPatch;
	Skeletton *daSkel;

	m_List.DeleteAllItems();
	int avInd=0;
	if ((daType==0)||(daType==2))
		for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
		{
			m_List.InsertItem ( avInd, _T(daObj->Name), 1 );
			if (daObj->Selected)
				ListView_SetItemState(m_List.m_hWnd, avInd,UINT((int(1) + 1) << 12), LVIS_STATEIMAGEMASK);
			avInd++;
		}

		
	if ((daType==0)||(daType==4))
		for (daShp=dk->FirstShape;daShp!=NULL;daShp=daShp->Next)
		{
			m_List.InsertItem ( avInd, _T(daShp->Name), 4 );
			if (daShp->Selected)
				ListView_SetItemState(m_List.m_hWnd, avInd,UINT((int(1) + 1) << 12), LVIS_STATEIMAGEMASK);
			avInd++;
		}
	if ((daType==0)||(daType==1))
		for (daCam=dk->FirstCam;daCam!=NULL;daCam=daCam->Next)
		{
			m_List.InsertItem ( avInd, _T(daCam->Name), 0 );
			if (daCam->Selected)
				ListView_SetItemState(m_List.m_hWnd, avInd,UINT((int(1) + 1) << 12), LVIS_STATEIMAGEMASK);
			avInd++;
		}
	if ((daType==0)||(daType==3))
		for (daLight=dk->FirstLight;daLight!=NULL;daLight=daLight->Next)
		{
			m_List.InsertItem ( avInd, _T(daLight->Name), 2 );
			if (daLight->Selected)
				ListView_SetItemState(m_List.m_hWnd, avInd,UINT((int(1) + 1) << 12), LVIS_STATEIMAGEMASK);
			avInd++;
		}

	if ((daType==0)||(daType==5))
		for (daSkel=dk->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
		{
			m_List.InsertItem ( avInd, _T(daSkel->Name), 3 );
			if (daSkel->Selected)
				ListView_SetItemState(m_List.m_hWnd, avInd,UINT((int(1) + 1) << 12), LVIS_STATEIMAGEMASK);
			avInd++;
		}

}
void CSelName::OnOK() 
{
	int avInd=0;
	int daType=m_Type.GetCurSel();

	Object *daObj;
	Shape *daShp;
	Camera *daCam;
	CLight *daLight;
	Skeletton *daSkel;

	dk->cSel->UnSelectAll(false);

	if ((daType==0)||(daType==2))
		for (daObj=dk->FirstObject;daObj!=NULL;daObj=daObj->Next)
		{
			daObj->Selected=(ListView_GetCheckState(m_List.m_hWnd,avInd)?true:false);
			avInd++;
		}
		
	if ((daType==0)||(daType==4))
		for (daShp=dk->FirstShape;daShp!=NULL;daShp=daShp->Next)
		{
			daShp->Selected=(ListView_GetCheckState(m_List.m_hWnd,avInd)?true:false);
			avInd++;
		}
	if ((daType==0)||(daType==1))
		for (daCam=dk->FirstCam;daCam!=NULL;daCam=daCam->Next)
		{
			daCam->Selected=(ListView_GetCheckState(m_List.m_hWnd,avInd)?true:false);
			avInd++;
		}
	if ((daType==0)||(daType==3))
		for (daLight=dk->FirstLight;daLight!=NULL;daLight=daLight->Next)
		{
			daLight->Selected=(ListView_GetCheckState(m_List.m_hWnd,avInd)?true:false);
			avInd++;
		}

	if ((daType==0)||(daType==5))
		for (daSkel=dk->FirstSkel;daSkel!=NULL;daSkel=daSkel->Next)
		{
			daSkel->Selected=(ListView_GetCheckState(m_List.m_hWnd,avInd)?true:false);
			avInd++;
		}
	CDialog::OnOK();
}

void CSelName::OnCancel() 
{
	CDialog::OnCancel();
}

void CSelName::OnAll() 
{
	for (int i=0;i<m_List.GetItemCount();i++)
        ListView_SetItemState(m_List.m_hWnd, i,UINT((int(1) + 1) << 12), LVIS_STATEIMAGEMASK);
}

void CSelName::OnNone() 
{
	for (int i=0;i<m_List.GetItemCount();i++)
        ListView_SetItemState(m_List.m_hWnd, i,UINT((int(0) + 1) << 12), LVIS_STATEIMAGEMASK);
}

void CSelName::OnInvert() 
{
	for (int i=0;i<m_List.GetItemCount();i++)
        ListView_SetItemState(m_List.m_hWnd, i,UINT((int(ListView_GetCheckState(m_List.m_hWnd,i)?0:1) + 1) << 12), LVIS_STATEIMAGEMASK);
}

void CSelName::OnSelchangeListtype() 
{
	ListIt();
}
