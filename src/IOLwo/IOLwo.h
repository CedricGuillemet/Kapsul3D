// KIoLWO.h: interface for the CKIoTxt class.
//
//////////////////////////////////////////////////////////////////////
#include "..\common\3dtypes.h"

#if !defined(_KIOLWO_INCLUDED_)
#define _KIOLWO_INCLUDED_

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
// Our Ligthwave file plugin class
//==============================================================

class CKIoLWO : public CKFilePlugin
{
public:
	CKIoLWO();
	virtual ~CKIoLWO();

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
	int ind;
	long p;
	int currentObject;
	bool value;

	//Internal 3D object related
	t_3Dobject *m_pObj;	//Our internal 3DObject
	o_mesh *m_pActualMesh;	//The actual mesh we are working on

	//** Important **
	bool IsFormatValid(char* filename);
	
	//Lightwave specific
	int m_iLWOType;	//The type of Lightwave object (LWOB or LWO2)

	//Functions members

	void CleanUp();
	bool LoadLWO(char *FileName);
	bool SaveLWO(char *FileName);

	long GetChunk(char* buffer,t_3Dobject *g_obj);

	long LoadFORMChunk(char* buffer,long ChunkLength,int *Indice);
	long LoadPNTSChunk(char* buffer,long ChunkLength,int *Indice);
	long LoadPOLSChunk(char* buffer,long ChunkLength,int *Indice);
	long LoadVMAPChunk(char* buffer,long ChunkLength,int *Indice);
	long LoadSURFChunk(char* buffer,long ChunkLength,int *Indice);
	long LoadPTAGChunk(char* buffer,long ChunkLength,int *Indice);
};

#endif // !defined(_KIOLWO_INCLUDED_)
