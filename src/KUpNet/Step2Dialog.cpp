// Step2Dialog.cpp : implementation file
//

#include "stdafx.h"
#include "KUpNet.h"
#include "InetDL.h"
#include "Step2Dialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStep2Dialog dialog


CStep2Dialog::CStep2Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStep2Dialog::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//{{AFX_DATA_INIT(CStep2Dialog)

	//}}AFX_DATA_INIT
}


void CStep2Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStep2Dialog)
	DDX_Control(pDX, IDC_AFFSTAT, m_AffStat);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	DDX_Control(pDX, IDC_LIB2, m_Lib2);
	DDX_Control(pDX, IDC_LIB1, m_Lib1);
	DDX_Control(pDX, IDC_LIST3, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStep2Dialog, CDialog)
	//{{AFX_MSG_MAP(CStep2Dialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStep2Dialog message handlers
extern bool Downing;
UINT CStep2Dialog::_DownloadThread(LPVOID pParam)
{
  //Convert from the SDK world to the C++ world
	/*
  CHttpDownloadDlg* pDlg = (CHttpDownloadDlg*) pParam;
  ASSERT(pDlg);
  ASSERT(pDlg->IsKindOf(RUNTIME_CLASS(CHttpDownloadDlg)));
  */
  DownloadThread((CThInfo*)pParam);
  return 0;
}

CThInfo nfo;
char tmpnpt[MAX_PATH];
char tmpnnpt[MAX_PATH];

class UpdateList
{
public:
	UpdateList() {};
	~UpdateList() {};
	CString PackName;
	CString PackDesc;
	CString PackFile;
	CString DestDir;

};

UpdateList m_UpdtList[50];
int nbUpdtList;

void CStep2Dialog::OnTimer(UINT nIDEvent) 
{
	KillTimer(1);
	 
	nfo.m_sURLToDownload="http://www.kapsul-design.com/NetUpdate/update.txt";
	//nfo.m_sURLToDownload="http://perso.club-internet.fr/lacrapul/packages/pack plugs.rar";
	//nfo.m_sURLToDownload="http://perso.club-internet.fr/lacrapul/complete.wav";
	GetTempPath(MAX_PATH,tmpnpt);

	GetTempFileName(tmpnpt,"tmp",1,tmpnnpt);

	nfo.m_sFileToDownloadInto=CString(tmpnnpt);
	nfo.jauge=&m_Progress;
	nfo.Info=NULL;//&m_DlInfo;

	
	m_pThread = AfxBeginThread(_DownloadThread, &nfo, THREAD_PRIORITY_NORMAL, CREATE_SUSPENDED);
	if (m_pThread == NULL)
	{
		TRACE(_T("Failed to create download thread, dialog is aborting\n"));
		EndDialog(IDCANCEL);
		return ;
	}
	
	m_pThread->m_bAutoDelete = FALSE;
	m_pThread->ResumeThread();

	if (m_pThread)
	{
		while (WaitForSingleObject(m_pThread->m_hThread, 100) == WAIT_TIMEOUT) 
		{ 
			MSG msg;
			while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		delete m_pThread;
		m_pThread = NULL;
	}

	m_Lib1.ShowWindow(SW_SHOWNORMAL);
	m_Lib2.ShowWindow(SW_HIDE);
	m_Progress.ShowWindow(SW_HIDE);
	m_List.ShowWindow(SW_SHOWNORMAL);


	// ReadFile
	FILE *fp=fopen(tmpnnpt,"rt");
	if (fp!=NULL)
	{
		nbUpdtList=0;
		int Sync=0;
		char fstr[MAX_PATH];


		while (fgets(fstr,MAX_PATH,fp)!=NULL)
		{
			if (fstr[0]!='#')
			{
				CString tfstr;
				if (fstr[0]=='$')
				{
					tfstr="c:\\program files\\";
					CString tmpss(fstr);
					tfstr+=tmpss.Mid(1);
				}
				else
					tfstr=fstr;

				tfstr.Replace('\n','\0');
				switch(Sync)
				{
				case 0:
					m_UpdtList[nbUpdtList].PackName=tfstr;
					break;
				case 1:
					m_UpdtList[nbUpdtList].PackDesc=tfstr;
					break;
				case 2:
					m_UpdtList[nbUpdtList].PackFile=tfstr;
					break;
				case 3:
					m_UpdtList[nbUpdtList].DestDir=tfstr;
					break;

				}
				
				Sync++;
				if (Sync==4)
				{
					Sync=0;
					nbUpdtList++;
				}
			}
		}

		fclose(fp);
		ListPackages();
	}
	else
	{
		// errors
	}

	CDialog::OnTimer(nIDEvent);
}

void CStep2Dialog::ListPackages()
{
	m_List.LockWindowUpdate();	// ***** lock window updates while filling list *****

	int nItem, nSubItem;
	CString str;

	for (nItem = 0; nItem < nbUpdtList; nItem++)
	{
		for (nSubItem = 0; nSubItem < 3; nSubItem++)
		{
			
			if (nSubItem == 0)			// checkbox
				str = "";//m_UpdtList[nItem].PackName;
			if (nSubItem == 1)			// text
				str = m_UpdtList[nItem].PackName;
			if (nSubItem == 2)			// combo
				str = m_UpdtList[nItem].PackDesc;
			
			if (nSubItem == 0)
				m_List.InsertItem(nItem, str);
			else
				m_List.SetItemText(nItem, nSubItem, str);

			
			if (nSubItem == 0)
				m_List.SetCheckbox(nItem, nSubItem, 0);
		}
	}

m_List.UnlockWindowUpdate();	// ***** unlock window updates *****


}
BOOL CStep2Dialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
m_Lib2.ShowWindow(SW_SHOWNORMAL);
m_Lib1.ShowWindow(SW_HIDE);
m_Progress.ShowWindow(SW_SHOWNORMAL);
m_List.ShowWindow(SW_HIDE);

	SetTimer(1,1000,NULL);
	
	CXListCtrl& list=m_List;

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_TRACKSELECT);

	// call EnableToolTips to enable tooltip display
	m_List.EnableToolTips(TRUE);


	CRect rect;
	list.GetWindowRect(&rect);

	

	int w = rect.Width() - 2;
	int colwidths[3] = { 7, 20, 60 };	// sixty-fourths

	TCHAR *	lpszHeaders[] = { _T(""),
							  _T("Package"),
							  _T("Description"),
							  NULL };
	int i;
	int total_cx = 0;
	LV_COLUMN lvcolumn;
	memset(&lvcolumn, 0, sizeof(lvcolumn));

	// add columns
	for (i = 0; ; i++)
	{
		if (lpszHeaders[i] == NULL)
			break;

		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = (i == 1 || i == 5) ? LVCFMT_LEFT : LVCFMT_CENTER;
		lvcolumn.pszText = lpszHeaders[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = (lpszHeaders[i+1] == NULL) ? w - total_cx - 2 : (w * colwidths[i]) / 64;
		total_cx += lvcolumn.cx;
		list.InsertColumn(i, &lvcolumn);
	}


	// create the image list from bitmap resource
	VERIFY(list.m_cImageList.Create(IDB_CHECKBOXES, 16, 3, RGB(255, 0, 255)));
	list.m_HeaderCtrl.SetImageList(&list.m_cImageList);

	// iterate through header items and attach the image list
	HDITEM hditem;

	for (i = 0; i < list.m_HeaderCtrl.GetItemCount(); i++)
	{
		hditem.mask = HDI_IMAGE | HDI_FORMAT;
		list.m_HeaderCtrl.GetItem(i, &hditem);
		hditem.fmt |=  HDF_IMAGE;
		if (i == 0 || i == 4)
			hditem.iImage = XHEADERCTRL_UNCHECKED_IMAGE;
		else
			hditem.iImage = XHEADERCTRL_NO_IMAGE;

		list.m_HeaderCtrl.SetItem(i, &hditem);
	}

	memset(&lvcolumn, 0, sizeof(lvcolumn));

	// set the format again - must do this twice or first column does not get set
	for (i = 0; ; i++)
	{
		if (lpszHeaders[i] == NULL)
			break;

		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM;
		lvcolumn.fmt = (i == 1 || i == 5) ? LVCFMT_LEFT : LVCFMT_CENTER;
		lvcolumn.iSubItem = i;
		list.SetColumn(i, &lvcolumn);
	}


	// items

	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CStep2Dialog::OnNext() 
{
	// TODO: Add your control notification handler code here
	m_List.EnableWindow(false);//LockWindowUpdate();	// ***** lock window updates while filling list *****

	int nItem, nSubItem;
	CString str;
/*
	for (nItem = 0; nItem < nbUpdtList; nItem++)
	{
		m_List.SetEnabled(nItem,false);
	}
*/
	for (nItem = 0; nItem < nbUpdtList; nItem++)
	{

		if (m_List.GetCheckbox(nItem, 0))
		{
			// download file
			m_List.SetProgress(nItem, 2);
			m_List.UpdateProgress(nItem, 2,(int)0);


	nfo.m_sURLToDownload="http://www.kapsul-design.com/NetUpdate/";
	nfo.m_sURLToDownload+=m_UpdtList[nItem].PackFile;

	GetTempPath(MAX_PATH,tmpnpt);

	GetTempFileName(tmpnpt,"tmp",1,tmpnnpt);

	nfo.m_sFileToDownloadInto=CString(tmpnnpt);
	nfo.jauge=&m_Progress;
	nfo.Info=&m_AffStat;
	nfo.Percent=0;//&m_DlInfo;

	
	m_pThread = AfxBeginThread(_DownloadThread, &nfo, THREAD_PRIORITY_NORMAL, CREATE_SUSPENDED);
	if (m_pThread == NULL)
	{
		TRACE(_T("Failed to create download thread, dialog is aborting\n"));
		EndDialog(IDCANCEL);
		return ;
	}
	
	m_pThread->m_bAutoDelete = FALSE;
	m_pThread->ResumeThread();

	if (m_pThread)
	{
		while (WaitForSingleObject(m_pThread->m_hThread, 100) == WAIT_TIMEOUT) 
		{ 
			MSG msg;
			while (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			// awfull Hack...
			m_List.UpdateProgress(nItem, 2,(int)nfo.Percent);
		}
		m_List.DeleteProgress(nItem,2);
		m_List.SetItemText(nItem, 2, CString("Completed"));
		delete m_pThread;
		m_pThread = NULL;
	}




		}
	}

//m_List.UnlockWindowUpdate();	// ***** unlock window updates *****
	m_List.EnableWindow(true);

	EndDialog(IDC_NEXT);
}

void CStep2Dialog::OnCancel() 
{
	if (MessageBox("Are you sure you want to exit the Net Updater?","Quit?",MB_YESNO)==IDYES)
		CDialog::OnCancel();
}

void CStep2Dialog::OnPaint() 
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


HCURSOR CStep2Dialog::OnQueryDragIcon() 
{
	return (HCURSOR) m_hIcon;
}
