// EntityManager.h: interface for the CKEntityManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITYMANAGER_H__5E8CF4B8_FEAF_4C36_85AA_639AFE1DD0DF__INCLUDED_)
#define AFX_ENTITYMANAGER_H__5E8CF4B8_FEAF_4C36_85AA_639AFE1DD0DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

class KAPSUL_DESC CKEntityParam
{
public :
	CKEntityParam(CString daName,int daType)
	{
		Name=daName;
		Type=daType;
	};
	~CKEntityParam() {};

	
	CString Name;
	int Type;
	CString Default;
	CStringList *m_ListProp;
};


class KAPSUL_DESC CKEntityGroup
{
public :
	CKEntityGroup(char *daName)
	{
		Name=daName;
	};
	~CKEntityGroup() {};

	CString  Name;
	vector<CKEntityParam*> m_Params;
};


class KAPSUL_DESC CKEntityType
{
public :
	CKEntityType(CString  daName)
	{
		//Name=new char [64]; 
		Name=daName;
	};
	~CKEntityType() {};

	CString  Name;
	vector<CKEntityGroup*> m_Groups;
};

/*
typedef unsigned int (*PROCESSIT)(int,int,int);

class KAPSUL_DESC CKEntityManager  
{
public:
	CKEntityManager();
	virtual ~CKEntityManager();
	static PROCESSIT GetHandler(CString daEntType);
	static PROCESSIT GetHandler(int Ordinal);
	static PROCESSIT GetHandlerC(char* daEntType);
	bool LoadXmlPresets(void);
private:
	static HMODULE m_EntMod;
};
*/
KAPSUL_DESC vector<CKEntityType*> *GetEntsType(void);
KAPSUL_DESC CKEntityType *GetObjectProps(void);
KAPSUL_DESC CKEntityType *GetSkeletonProps(void);
KAPSUL_DESC CKEntityType *GetPatchProps(void);
KAPSUL_DESC CKEntityType *GetShapeProps(void);
KAPSUL_DESC CKEntityType *GetCameraProps(void);

bool KAPSUL_DESC LoadXmlPresets(void);
/*
extern __declspec( dllexport ) vector<CKEntityType*> m_EntsType;
extern __declspec( dllexport ) CKEntityType m_ObjectProps;
extern __declspec( dllexport ) CKEntityType m_SkeletonProps;
extern __declspec( dllexport ) CKEntityType m_PatchProps;
extern __declspec( dllexport ) CKEntityType m_ShapeProps;
extern __declspec( dllexport ) CKEntityType m_CameraProps;
*/
#endif // !defined(AFX_ENTITYMANAGER_H__5E8CF4B8_FEAF_4C36_85AA_639AFE1DD0DF__INCLUDED_)
