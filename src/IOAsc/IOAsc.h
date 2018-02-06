// KIoASC.h: interface for the CKIoTxt class.
//
//////////////////////////////////////////////////////////////////////
#include "..\common\3dtypes.h"

#if !defined(_KIOASC_INCLUDED_)
#define _KIOASC_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

typedef signed char  sbyte;
typedef signed short sword;
typedef signed long  sdword;

//==============================================================
// Our Material class
//==============================================================

class CTmpMaterial
{
public:
	CTmpMaterial(){ pTexture = NULL; szMatName.Empty();};
	~CTmpMaterial(){ pTexture = NULL; szMatName.Empty();};

	CKTexture *pTexture;
	CString  szMatName;
};

//==============================================================
// Our ASC file plugin class
//==============================================================

class CKIoASC : public CKFilePlugin
{
public:
	CKIoASC();
	virtual ~CKIoASC();

	CString GetName();
	CString GetInfos();
	CString GetFilter();
	CString GetFileDescription();
	CString GetFileExtension();
	bool SupportReading();
	bool SupportWriting();
	bool Read(CKScene *pScene,CString FullFilePath);
	bool Write(CKScene *pScene,CString FullFilePath);

private:
	//Data members
	char temp[512];
	CKOption *m_Option;
	CKMesh  *m_pMesh;
	CKScene *m_pScene;
	CObArray matArray;
	int	curTexMatIndex;
	CString szTmpNameContainer;	
	FILE *f;
	long m_lFileLenght;
	int ind;
	long p;
	int currentObject;
	bool value;

	//Internal 3D object related
	t_3Dobject *m_pObj;	//Our internal 3DObject
	o_mesh *m_pActualMesh;	//The actual mesh we are working on
	
	//** Important **
	bool IsFormatValid(char* filename);

	//ASC specific
	bool ReadASCFile(char* buffer);
	bool WriteASCFile(char* filename);
	long CreateTriangleFanFromPolygon(FILE *file,o_poly *p_poly, long StartFaceIndice);


	//Functions members

	void CleanUp();
	bool LoadASC(char *FileName);
	bool SaveASC(char *FileName);
};

#endif // !defined(_KIOASC_INCLUDED_)
