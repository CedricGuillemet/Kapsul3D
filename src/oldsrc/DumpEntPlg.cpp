// DumpInfos.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "DumpEntPlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern "C" CEntity *CurrentPropEntity;

inline DWORD Rgb2Bgr(DWORD &val)
{
	return (((val&0xff)<<16)+(val&0xff00)+((val&0xff0000)>>16));
}
/////////////////////////////////////////////////////////////////////////////
// CEntPlg dialog

int GetParamType(char *ParamTypeName)
{
	if (strcmp(ParamTypeName,"string")==0) return 0;
	if (strcmp(ParamTypeName,"integer")==0) return 1;
	if (strcmp(ParamTypeName,"color")==0) return 2;
	if (strcmp(ParamTypeName,"float")==0) return 3;
	if (strcmp(ParamTypeName,"combo")==0) return 4;
	return -1;
}

vector<CEntityType*> m_EntsType;

CEntPlg::CEntPlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEntPlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEntPlg)
	//}}AFX_DATA_INIT
}


void CEntPlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEntPlg)
	DDX_Control(pDX, IDC_CB1, m_EntsTypes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEntPlg, CDialog)
	//{{AFX_MSG_MAP(CEntPlg)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_CBN_SELCHANGE(IDC_CB1, OnSelchangeCb1)
	ON_NOTIFY(0xf0f0f0f0, IDC_OI, OnNotifyProp)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEntPlg message handlers

void CEntPlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}

BOOL CEntPlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Oi.Create(CRect(0,20,165,600),this,8858,WS_CHILD|WS_VISIBLE);

char value[256];
	int cblAv=0;

	CEntityParam *CurPar;
	CEntityGroup *CurGrp;
	CEntityType *CurType;

	ResetAllValues();

	//m_Oi.Create(CRect(10,10,100,200),this,25147,WS_CHILD|WS_VISIBLE);

//	CObjectInspector::CProperty *pProp;

	// Prepare control's appearance
	m_szBorderStyle		   = "bsLowered";
	m_bHotTrack			   = false;
	m_b3dFocus			   = false;
	m_szValueHeader		   = _T("Value");
	m_szPropertyHeader	   = _T("Property");
	m_clBackColor		   = ::GetSysColor(COLOR_BTNFACE);
	m_clVTColor			   = RGB(200,200,200);
	m_clPTColor			   = (COLORREF)0;
	m_clGridLineColor	   = RGB(80,80,80);
	m_nMinPropertyColWidth = 50;
	m_nMinValueColWidth    = 50;
	m_clFocusLineColor     = RGB(200,200,200);
	m_nStyle			   = 1;


	init init;
	tree_parser parser("entities.xml");

	if (!parser) 
	{
		//std::cerr << argv[0] << ": error parsing XML file\r\n";
		MessageBox("Error parsing file");
		return 1;
	}
	
	node &root = parser.get_root_node();

	node::const_iterator child(root.begin()), child_end(root.end());
	for (; child != child_end; ++child) 
	{
		if (child->is_text()) continue;


		if (strcmp(child->get_name() ,"Entity")==0)
		{
			node::const_iterator child2(child->begin()), child_end(child->end());
			for (; child2 != child_end; ++child2) 
			{
				if (child2->is_text()) continue;

				if (strcmp(child2->get_name() ,"desc")==0)
				{
					child2->get_attr("value",value);
					m_EntsTypes.AddString(value);
					CurType=new CEntityType(value);
					m_EntsType.insert(m_EntsType.end(),CurType);



				}
					
				if (strcmp(child2->get_name() ,"Group")==0)
				{
					

					// param name
					child2->get_attr("value",value);

					CurGrp=new CEntityGroup(value);
					CurType->m_Groups.insert(CurType->m_Groups.end(),CurGrp);

					node::const_iterator child3(child2->begin()), child_end(child2->end());
					for (; child3 != child_end; ++child3) 
					{
						if (child3->is_text()) continue;

						if (strcmp(child3->get_name() ,"Groupvalues")==0)
						{
							child3->get_attr("name",value);
							CurPar=new CEntityParam(value,1);
							CurGrp->m_Params.insert(CurGrp->m_Params.end(),CurPar);

							child3->get_attr("type",value);
							CurPar->Type=GetParamType(value);

							if (CurPar->Type==4)
							{
								// combo
								char tempcbl[64];
								int valAv=0;

								sprintf(tempcbl,"value%d",valAv);
								while(child3->get_attr(tempcbl,value))
								{
									m_cbListProp[cblAv].AddTail(value);
									valAv++;
									sprintf(tempcbl,"value%d",valAv);
								}
								cblAv++;
							}
						}
					}
				}
			}
		}
	}
	UpdatePropList(m_EntsType[0]);
	m_EntsTypes.SetCurSel(0);
	m_EntsTypes.SetDroppedWidth(300);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEntPlg::OnOK( )
{

}

void CEntPlg::OnCancel( )
{

}

void CEntPlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	if (IsWindow(m_EntsTypes.m_hWnd))
	{
		//m_EntsTypes.SetWindowPos(NULL,0,0,cx,22,SWP_NOZORDER);
		m_Oi.MoveWindow(CRect(0,50,cx,cy));
	}
	
}


void CEntPlg::UpdatePropList(CEntityType *daTyp)
{
	CObjectInspector::CProperty *pProp;

	//m_Oi.SetRedraw(FALSE);

	//m_Oi.CleanUp();
	ResetAllValues();

	m_Oi.m_PropertyList.clear();
	int szAv=0,clAv=0,iAv=0,fAv=0,cbAv=0;

	for (vector<CEntityGroup*>::iterator i = daTyp->m_Groups.begin(); i != daTyp->m_Groups.end(); i++)
	{
		m_Oi.AddProperty (pProp = new CObjectInspector::CProperty((*i)->Name));
		pProp->Expand ();

		for (vector<CEntityParam*>::iterator j = (*i)->m_Params.begin(); j != (*i)->m_Params.end(); j++)
		{
			switch((*j)->Type)
			{
			case 0:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_szProp[szAv++]));
				break;
			case 1:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_iProp[iAv++]));
				break;
			case 2:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_clProp[clAv++]));
				break;
			case 3:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_fProp[fAv++]));
				break;
			case 4:
				pProp->AddProperty (new CObjectInspector::CProperty((*j)->Name, &m_cbProp[cbAv], &m_cbListProp[cbAv] , -1, CBS_DROPDOWNLIST));
				cbAv++;
				break;
			}
		}
	}
	//m_Oi.SetRedraw(TRUE);
}


void CEntPlg::ResetAllValues(void)
{
	for (int i=0;i<20;i++)
	{
		m_szProp[i]="";
		m_fProp[i]=0;
		m_iProp[i]=0;
		m_clProp[i]=0;
		m_cbProp[i]="";
		m_cbListProp[i].RemoveAll();
	}
}

void CEntPlg::BuildXmlProps(CString &EntProp)
{
	EntProp="<?xml version=\"1.0\" standalone=\"yes\"?>\r\n"
					"<body>\r\n"
					"<Entity \r\n";
	
	for (vector<CObjectInspector::CProperty*>::iterator i = m_Oi.m_PropertyList.begin(); i != m_Oi.m_PropertyList.end(); i++)
	{

		for (vector<CObjectInspector::CProperty*>::iterator j = (*i)->m_Childs.begin(); j != (*i)->m_Childs.end(); j++)
		{
			switch((*j)->GetType())
			{
				case CObjectInspector::ptColor:
					{
						CString refColor;
					EntProp+=(*j)->GetName();
					refColor.Format("=\"0x00%x\"\r\n",Rgb2Bgr(*(*j)->m_pclValue));
					EntProp+=refColor;
					}
					break;
				default:

					EntProp+=(*j)->GetName();
					EntProp+="=\"";
					EntProp+=(*j)->GetValueAsText();
					EntProp+="\"\r\n ";
					break;
			}
		}
	}

	EntProp+="/>\r\n</body>";
}



void CEntPlg::OnNotifyProp(NMHDR* pNMHDR, LRESULT* pResult)
{

	if (CurrentPropEntity!=NULL)
	{
		CString tmpXmlDatas;
		BuildXmlProps(tmpXmlDatas);
		//CurrentPropEntity->ProcessMessage(KM_SETXML,(UINT)&tmpXmlDatas,0);
		CurrentPropEntity->SetXmlScript(tmpXmlDatas);
	}
	
}

void CEntPlg::OnNotifyProp(void)
{

	if (CurrentPropEntity!=NULL)
	{
		CString tmpXmlDatas;
		BuildXmlProps(tmpXmlDatas);
		//CurrentPropEntity->ProcessMessage(KM_SETXML,(UINT)&tmpXmlDatas,0);
		CurrentPropEntity->SetXmlScript(tmpXmlDatas);
	}
	
}

void CEntPlg::OnSelchangeCb1() 
{
	ResetAllValues();
	UpdatePropList(m_EntsType[m_EntsTypes.GetCurSel()]);	
}
CEntityType* CEntPlg::FindEntityTypeByName(char *EntName,int &ListNb)
{
	int j=0;
	for (vector<CEntityType*>::iterator i = m_EntsType.begin(); i != m_EntsType.end(); i++)
	{
		ListNb=j;
		if (strcmp((*i)->Name,EntName)==0) return (*i);
		j++;
	}
	return NULL;
}
void CEntPlg::UpdatePropsFromEntity(void)
{

	if (CurrentPropEntity!=NULL)
	{
		CString *GetXmlData;
		CString tmpzut;
		tmpzut=CurrentPropEntity->EntType;
		GetXmlData=(CString*)CurrentPropEntity->ProcessMessage(KM_GETXML,0/*(UINT)&CurrentPropEntity->m_XmlStr*/,0);
		if (GetXmlData==NULL)
		{
			MessageBox("Not able to get XML parameters from that entity.","XML parsing error!",MB_OK);
			return;
		}

		CurrentPropEntity->SetXmlScript(*GetXmlData,false);

		
		
		char value[256];
		int szAv=0,clAv=0,iAv=0,fAv=0,cbAv=0;
		
		init init;
		tree_parser parser(CurrentPropEntity->GetScriptBuffer(),CurrentPropEntity->GetScriptSize());
		
		if (!parser) 
		{
			MessageBox("Error parsing xml buffer fro properties update !","XML parsing error!",MB_OK);
			return ;
		}
		
		node &root = parser.get_root_node();
		
		node::const_iterator child(root.begin()), child_end(root.end());
		for (; child != child_end; ++child) 
		{
			if (child->is_text()) continue;
			
			
			if (strcmp(child->get_name() ,"Entity")==0)
			{
				
				
				for (vector<CObjectInspector::CProperty*>::iterator i = m_Oi.m_PropertyList.begin(); i != m_Oi.m_PropertyList.end(); i++)
				{
					
					for (vector<CObjectInspector::CProperty*>::iterator j = (*i)->m_Childs.begin(); j != (*i)->m_Childs.end(); j++)
					{
						char attrName[256];
						strcpy(attrName,(*j)->GetName().GetBuffer(1));
						child->get_attr(attrName,value);

						switch((*j)->GetType())
						{
							
						case CObjectInspector::ptGroup:
							break;
						case CObjectInspector::ptShort:
						case CObjectInspector::ptInteger:
							sscanf(value,"%d",(*j)->m_pnValue);
							//(*j)->SetValueInternal();
							break;
						case CObjectInspector::ptFloat:
						case CObjectInspector::ptDouble:
							sscanf(value,"%f",(*j)->m_pfValue);
								break;
						case CObjectInspector::ptBool:
							break;
						case CObjectInspector::ptDate:
							break;
						case CObjectInspector::ptColor:
							sscanf(value,"%x",(*j)->m_pclValue);
							*(*j)->m_pclValue=Rgb2Bgr(*(*j)->m_pclValue);
								break;
						case CObjectInspector::ptStringList:
							//sscanf(value,"%s",(*j)->m_pszValue);
							*(*j)->m_pszValue=value;
							break;
							
						}
						
					}
				}
			}
		}
		m_Oi.Invalidate(FALSE);
	}
}