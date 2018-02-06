// EntityManager.cpp: implementation of the CKEntityManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/*
HMODULE CKEntityManager::m_EntMod=NULL;
extern CKOption *KOption2;
CKEntityManager::CKEntityManager()
{
	m_EntMod=LoadLibrary(KOption2->EntityDLLLocation());
	if (m_EntMod==NULL)
	{
		MessageBox(NULL,"Entity.dll library not found !!!\nModify UserOptions.xml and/or Options.xml.","nKapsul execution aborted.",MB_OK|MB_ICONERROR);
		PostQuitMessage(0);
	}

}

CKEntityManager::~CKEntityManager()
{
	FreeLibrary(m_EntMod);
}

PROCESSIT CKEntityManager::GetHandler(CString daEntType)
{
	char temp[512];
	strcpy(temp,"Process_");
	strcat(temp,daEntType.GetBuffer(0));
	//CString temp="Process_";
	//temp+=daEntType;
	return (PROCESSIT)GetProcAddress(m_EntMod,temp);
}

PROCESSIT CKEntityManager::GetHandlerC(char* daEntType)
{
	char temp[512];
	strcpy(temp,"Process_");
	strcat(temp,daEntType);
	//CString temp="Process_";
	//temp+=daEntType;
	return (PROCESSIT)GetProcAddress(m_EntMod,temp);
}
PROCESSIT CKEntityManager::GetHandler(int Ordinal)
{
	CString temp;
	temp.Format("%d",Ordinal);
	return (PROCESSIT)GetProcAddress(m_EntMod,(char*)Ordinal);
}
*/
/*
 __declspec( dllexport ) vector<CKEntityType*> m_EntsType;
 __declspec( dllexport ) CKEntityType m_MeshProps("");
 __declspec( dllexport ) CKEntityType m_SkeletonProps("");
 __declspec( dllexport ) CKEntityType m_PatchProps("");
 __declspec( dllexport ) CKEntityType m_ShapeProps("");
 __declspec( dllexport ) CKEntityType m_CameraProps("");
*/
vector<CKEntityType*> m_EntsType;
CKEntityType m_MeshProps("");
CKEntityType m_SkeletonProps("");
CKEntityType m_PatchProps("");
CKEntityType m_ShapeProps("");
CKEntityType m_CameraProps("");

vector<CKEntityType*> *GetEntsType(void) {	return &m_EntsType; }
CKEntityType *GetObjectProps(void) {	return &m_MeshProps; }
CKEntityType *GetSkeletonProps(void) {	return &m_SkeletonProps; }
CKEntityType *GetPatchProps(void) {	return &m_PatchProps; }
CKEntityType *GetShapeProps(void) {	return &m_ShapeProps; }
CKEntityType *GetCameraProps(void) {	return &m_CameraProps; }

int GetParamType(char *ParamTypeName)
{
	if (strcmp(ParamTypeName,"string")==0)		return 0;
	if (strcmp(ParamTypeName,"integer")==0)		return 1;
	if (strcmp(ParamTypeName,"color")==0)		return 2;
	if (strcmp(ParamTypeName,"float")==0)		return 3;
	if (strcmp(ParamTypeName,"combo")==0)		return 4;
	if (strcmp(ParamTypeName,"masked")==0)		return 5;
	if (strcmp(ParamTypeName,"slider")==0)		return 6;
	if (strcmp(ParamTypeName,"memo")==0)		return 7;
	if (strcmp(ParamTypeName,"fbrowser")==0)	return 8;
	if (strcmp(ParamTypeName,"bool")==0)	return 9;
	return -1;
}

bool LoadXmlPresets(void)
{
	
	char value[256];
	CKEntityParam *CurPar;
	CKEntityGroup *CurGrp;
	CKEntityType *CurType;
	int cblAv=0,iOther=0;

	init init;

	char *tmppath=((CKOption*)GetGOption())->EntityXMLLocation();
	tree_parser parser(tmppath);

	if (!parser) 
	{
		//std::cerr << argv[0] << ": error parsing XML file\r\n";
		MessageBox(NULL,"Entity.xml file not found.","Error parsing file",MB_ICONERROR|MB_OK);
		return false;
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
					if (strcmp(value,"Mesh")==0)
					{
						// mesh
						m_MeshProps.Name=value;
						m_MeshProps.m_Groups.erase(m_MeshProps.m_Groups.begin(),m_MeshProps.m_Groups.end());
						CurType=&m_MeshProps;
					}
					else
					if (strcmp(value,"Camera")==0)
					{
						// Camera
						m_CameraProps.Name=value;
						m_CameraProps.m_Groups.erase(m_CameraProps.m_Groups.begin(),m_CameraProps.m_Groups.end());
						CurType=&m_CameraProps;

					}
					else
					if (strcmp(value,"Shape")==0)
					{
						// Shape
						m_ShapeProps.Name=value;
						m_ShapeProps.m_Groups.erase(m_ShapeProps.m_Groups.begin(),m_ShapeProps.m_Groups.end());
						CurType=&m_ShapeProps;

					}
					else
					if (strcmp(value,"Skeleton")==0)
					{
						// Skeleton
						m_SkeletonProps.Name=value;
						m_SkeletonProps.m_Groups.erase(m_SkeletonProps.m_Groups.begin(),m_SkeletonProps.m_Groups.end());
						CurType=&m_SkeletonProps;

					}
					else
					if (strcmp(value,"Patch")==0)
					{
						// Patch
						m_PatchProps.Name=value;
						m_PatchProps.m_Groups.erase(m_PatchProps.m_Groups.begin(),m_PatchProps.m_Groups.end());
						CurType=&m_PatchProps;

					}
					else
					{
						//entities
						//m_EntsTypes.AddString(value);
						CurType=new CKEntityType(value);
						m_EntsType.insert(m_EntsType.end(),CurType);
					}
				}
					
				if (strcmp(child2->get_name() ,"Group")==0)
				{
					

					// param name
					child2->get_attr("value",value);

					CurGrp=new CKEntityGroup(value);
					CurType->m_Groups.insert(CurType->m_Groups.end(),CurGrp);

					node::const_iterator child3(child2->begin()), child_end(child2->end());
					for (; child3 != child_end; ++child3) 
					{
						if (child3->is_text()) continue;

						if (strcmp(child3->get_name() ,"Groupvalues")==0)
						{
							child3->get_attr("name",value);
							CurPar=new CKEntityParam(value,1);
							CurGrp->m_Params.insert(CurGrp->m_Params.end(),CurPar);

							child3->get_attr("type",value);
							CurPar->Type=GetParamType(value);

							if (CurPar->Type == 4)
							{
								// combo,masked & slider
								char tempcbl[64];
								int valAv=0;
								CurPar->m_ListProp=new CStringList;

								sprintf(tempcbl,"value%d",valAv);
								while(child3->get_attr(tempcbl,value))
								{
									CurPar->m_ListProp->AddTail(value);
									valAv++;
									sprintf(tempcbl,"value%d",valAv);
								}

								cblAv++;
							}else
							if (CurPar->Type == 5 || CurPar->Type == 6)
							{
								// masked & slider
								char tempcbl[64];
								int valAv=0;
								CurPar->m_ListProp=new CStringList;

								sprintf(tempcbl,"value%d",valAv);
								while(child3->get_attr(tempcbl,value))
								{
									CurPar->m_ListProp->AddTail(value);
									valAv++;
									sprintf(tempcbl,"value%d",valAv);
								}
								iOther++;
							}
							if (child3->get_attr("default",value))
							{
								CurPar->Default=value;
							}
						}
					}
				}
			}
		}
	}
	
	return true;
}
