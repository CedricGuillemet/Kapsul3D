// EntiDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "Enti.h"
#include "EntityProp.h"
#include "EntityType.h"
#include "EntityName.h"
#include "EntiDlg.h"
#include "TestProps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntiDlg dialog

CEntiDlg::CEntiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntiDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEntiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntiDlg)
	DDX_Control(pDX, IDC_CBVALS, m_Vals);
	DDX_Control(pDX, IDC_LISTPROPS, m_ListProps);
	DDX_Control(pDX, IDC_COMBO1, m_EntType);
    DDX_Control(pDX, IDC_TYPEEDIT,m_TypeEdit);
    DDX_Control(pDX, IDC_TYPECOMBO,m_TypeCombo);
    DDX_Control(pDX, IDC_TYPEFILE,m_TypeFile);
    DDX_Control(pDX, IDC_TYPETRUEFALSE,m_TypeTrueFalse);
    DDX_Control(pDX, IDC_TYPECOLORPICKER,m_TypeColorPicker);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEntiDlg, CDialog)
	//{{AFX_MSG_MAP(CEntiDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADDENT, OnAddent)
	ON_BN_CLICKED(IDC_DELENT, OnDelent)
	ON_BN_CLICKED(IDC_RENENT, OnRenent)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_BN_CLICKED(IDC_REN, OnRen)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_LBN_SELCHANGE(IDC_LISTPROPS, OnSelchangeListprops)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_TYPECOLORPICKER, OnTypecolorpicker)
	ON_BN_CLICKED(IDC_TYPECOMBO, OnTypecombo)
	ON_BN_CLICKED(IDC_TYPEEDIT, OnTypeedit)
	ON_BN_CLICKED(IDC_TYPEFILE, OnTypefile)
	ON_BN_CLICKED(IDC_TYPETRUEFALSE, OnTypetruefalse)
	ON_EN_KILLFOCUS(IDC_CBVALS, OnKillfocusCbvals)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntiDlg message handlers

BOOL CEntiDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	if (ReadEntityTypesFromDisk("Entities.txt"))
    {
        for (CEntityType *daEnt=GetFirstEntType();daEnt!=NULL;daEnt=daEnt->Next)
            m_EntType.AddString(daEnt->Name);
    }
    m_EntType.SetCurSel(0);

    CString dalib;
    m_EntType.GetLBText(m_EntType.GetCurSel(),dalib);
    CurEnt=GetByName(dalib.GetBuffer(1));
    OnSelchangeCombo1();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEntiDlg::OnPaint() 
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
HCURSOR CEntiDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEntiDlg::OnAddent() 
{
	CEntityName ceName;

    ceName.DoModal();

    if (strlen(ceName.Name)>0)
    {
        int daInd=m_EntType.FindStringExact(0,ceName.Name);

        if (daInd==CB_ERR)
        {
            m_EntType.AddString(ceName.Name);
            AddEntityType(ceName.Name);
            m_EntType.SetCurSel(m_EntType.FindStringExact(0,ceName.Name));
        }
        else
            m_EntType.SetCurSel(daInd);
    }
}

void CEntiDlg::OnDelent() 
{
	if (MessageBox("Delete this type?","Deletion",MB_YESNO)==IDYES)
    {
        CString dalib;
        m_EntType.GetLBText(m_EntType.GetCurSel(),dalib);
        DelEntityType(GetByName(dalib.GetBuffer(1)));
        m_EntType.DeleteString(m_EntType.GetCurSel());
        m_EntType.SetCurSel(0);
    }
}

void CEntiDlg::OnRenent() 
{
    CString dalib;
    CEntityName ceName;

    ceName.DoModal();

    if (strlen(ceName.Name)>0)
    {
        m_EntType.GetLBText(m_EntType.GetCurSel(),dalib);

        strcpy(GetByName(dalib.GetBuffer(1))->Name,ceName.Name);
        m_EntType.DeleteString(m_EntType.GetCurSel());
        m_EntType.AddString(ceName.Name);

        m_EntType.SetCurSel(m_EntType.FindStringExact(0,ceName.Name));
    }
}

void CEntiDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	WriteEntityTypes2Disk("Entities.txt");
}

void CEntiDlg::OnAdd() 
{
	CEntityName ceName;

    ceName.DoModal();

    if (strlen(ceName.Name)>0)
    {
        int daInd=m_ListProps.FindStringExact(0,ceName.Name);

        if (daInd==LB_ERR)
        {
            m_ListProps.AddString(ceName.Name);
            CurEnt->AddEntityProp(ceName.Name);
            m_ListProps.SetCurSel(m_ListProps.FindStringExact(0,ceName.Name));
        }
        else
            m_ListProps.SetCurSel(daInd);

        OnSelchangeListprops();
    }
}

void CEntiDlg::OnDel() 
{
	if (MessageBox("Delete this property?","Deletion",MB_YESNO)==IDYES)
    {
        CString dalib;
        m_ListProps.GetText(m_ListProps.GetCurSel(),dalib);
        CurEnt->DelEntityProp(CurEnt->GetByName(dalib.GetBuffer(1)));
        m_ListProps.DeleteString(m_ListProps.GetCurSel());
        m_ListProps.SetCurSel(0);
        OnSelchangeListprops();
    }	
}

void CEntiDlg::OnRen() 
{
    CString dalib;
    CEntityName ceName;

    ceName.DoModal();

    if (strlen(ceName.Name)>0)
    {
        m_ListProps.GetText(m_ListProps.GetCurSel(),dalib);

        strcpy(CurEnt->GetByName(dalib.GetBuffer(1))->Name,ceName.Name);
        m_ListProps.DeleteString(m_ListProps.GetCurSel());
        m_ListProps.AddString(ceName.Name);

        m_ListProps.SetCurSel(m_ListProps.FindStringExact(0,ceName.Name));
        OnSelchangeListprops();
    }
}

void CEntiDlg::OnSelchangeCombo1() 
{
    CString dalib;
    m_EntType.GetLBText(m_EntType.GetCurSel(),dalib);
    CurEnt=GetByName(dalib.GetBuffer(1));
    m_ListProps.ResetContent();

    for (CEntityProp *daProp=CurEnt->FirstProp;daProp!=NULL;daProp=daProp->Next)
        m_ListProps.AddString(daProp->Name);
        
    CurProp=NULL;

    m_ListProps.SetCurSel(0);
    OnSelchangeListprops();
}

void CEntiDlg::OnSelchangeListprops() 
{
    CString dalib;
    if (m_ListProps.GetCurSel()!=-1)
    {
        m_ListProps.GetText(m_ListProps.GetCurSel(),dalib);
 
	    CurProp=CurEnt->GetByName(dalib.GetBuffer(1));
        if (CurProp!=NULL)
        {
            m_TypeEdit.EnableWindow(TRUE);
            m_TypeCombo.EnableWindow(TRUE);
            m_TypeFile.EnableWindow(TRUE);
            m_TypeTrueFalse.EnableWindow(TRUE);
            m_TypeColorPicker.EnableWindow(TRUE);

            m_TypeEdit.SetCheck(0);
            m_TypeCombo.SetCheck(0);
            m_TypeFile.SetCheck(0);
            m_TypeTrueFalse.SetCheck(0);
            m_TypeColorPicker.SetCheck(0);
            switch (CurProp->Type)
            {
            case 1:
                m_TypeEdit.SetCheck(1);
                m_Vals.EnableWindow(FALSE);
                m_Vals.SetWindowText("");
                break;
            case 2:
                m_TypeCombo.SetCheck(1);
                m_Vals.EnableWindow(TRUE);
                break;
            case 3:
                m_TypeTrueFalse.SetCheck(1);
                m_Vals.EnableWindow(FALSE);
                m_Vals.SetWindowText("");
                break;
            case 4:
                m_TypeFile.SetCheck(1);
                m_Vals.EnableWindow(TRUE);
                break;
            case 5:
                m_TypeColorPicker.SetCheck(1);
                m_Vals.EnableWindow(FALSE);
                m_Vals.SetWindowText("");
                break;
            }

            if (CurProp->SizeVals!=0)
            {
                char temp[16384];
                temp[0]=0;
                int tmpav=0;

                for (int i=0;i<CurProp->SizeVals;i++)
                {
                    if (CurProp->Vals[i]!='|')
                    {
                        temp[tmpav]=CurProp->Vals[i];
                        temp[++tmpav]=0;
                        
                    }
                    else
                    {
                        strcat(temp,"\r\n");
                        tmpav+=2;
                    }
                }
                m_Vals.SetWindowText(temp);
            }
            else
                m_Vals.SetWindowText("");
        }
        return;
    }

    m_TypeEdit.SetCheck(1);
    m_TypeCombo.SetCheck(0);
    m_TypeFile.SetCheck(0);
    m_TypeTrueFalse.SetCheck(0);
    m_TypeColorPicker.SetCheck(0);
    m_Vals.EnableWindow(FALSE);
    m_TypeEdit.EnableWindow(FALSE);
    m_TypeCombo.EnableWindow(FALSE);
    m_TypeFile.EnableWindow(FALSE);
    m_TypeTrueFalse.EnableWindow(FALSE);
    m_TypeColorPicker.EnableWindow(FALSE);

}

void CEntiDlg::OnButton1() 
{
    CTestProps	tp;

    tp.DoModal();
}

void CEntiDlg::OnTypecolorpicker() 
{
	CurProp->Type=5;
    m_Vals.EnableWindow(FALSE);
    m_Vals.SetWindowText("");

    if (CurProp->Vals!=NULL)
        delete [] CurProp->Vals;
    CurProp->Vals=NULL;
    CurProp->SizeVals=0;

}

void CEntiDlg::OnTypecombo() 
{
	CurProp->Type=2;
	m_Vals.EnableWindow(TRUE);
}

void CEntiDlg::OnTypeedit() 
{
	CurProp->Type=1;
	m_Vals.EnableWindow(FALSE);
    m_Vals.SetWindowText("");
    if (CurProp->Vals!=NULL)
        delete [] CurProp->Vals;
    CurProp->Vals=NULL;
    CurProp->SizeVals=0;

}

void CEntiDlg::OnTypefile() 
{
	CurProp->Type=4;
	m_Vals.EnableWindow(TRUE);
}

void CEntiDlg::OnTypetruefalse() 
{
	CurProp->Type=3;
	m_Vals.EnableWindow(FALSE);
    m_Vals.SetWindowText("");
    if (CurProp->Vals!=NULL)
        delete [] CurProp->Vals;
    CurProp->Vals=NULL;
    CurProp->SizeVals=0;

}

void CEntiDlg::OnKillfocusCbvals() 
{
	char temp[16384],temp2[16384];
    m_Vals.GetWindowText(temp,16384);
    temp2[0]=0;
    int tmpav=0;

    for (unsigned int i=0;i<strlen(temp);i++)
    {
        if (temp[i]!=10)
        {
            if (temp[i]==13)
            {
                temp2[tmpav++]='|';
            }
            else
            {
                temp2[tmpav++]=temp[i];
            }
        }
    }
    //temp[i]=0;
    temp2[tmpav]=0;
    if (CurProp->Vals!=NULL)
        delete [] CurProp->Vals;

    CurProp->SizeVals=tmpav;
    CurProp->Vals=new char [tmpav+1];
    memcpy(CurProp->Vals,temp2,tmpav+1);
}
