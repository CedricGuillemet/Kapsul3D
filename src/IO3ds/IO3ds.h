// KIo3ds.h: interface for the CKIoTxt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIo3ds_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
#define AFX_KIo3ds_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned long  dword;

typedef signed char  sbyte;
typedef signed short sword;
typedef signed long  sdword;

class CTmpMaterial
{
public:
	CTmpMaterial(){ pTexture = NULL; szMatName.Empty();};
	~CTmpMaterial(){ pTexture = NULL; szMatName.Empty();};

	CKTexture *pTexture;
	CString  szMatName;
};


class CKIo3ds : public CKFilePlugin
{
public:
	CKIo3ds();
	virtual ~CKIo3ds();

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
	char temp[512];
	CKOption *m_Option;
	CKMesh  *pMesh;
	CKScene *m_Scene;
	CObArray matArray;
	int	curTexMatIndex;
	CString szTmpNameContainer;	
	FILE *f;
	int ind;
	long p;
	int currentObject;
	bool value;

	void CleanUp();
	void SkipReader( int ind, long p);
	void VersionReader( int ind, long p);
	void MeshVersionReader( int ind, long p);
	void MasterScaleReader( int ind, long p);
	void RGBFReader ( int ind, long p);
	void RGBBReader ( int ind, long p);
	void ASCIIZReader ( int ind, long p,CString &Name);
	void ObjBlockReader ( int ind, long p);
	void TriangularMeshReader( int ind, long p);
	void VertListReader ( int ind, long p);
	void FaceListReader ( int ind, long p);
	void FaceMatReader ( int ind, long p);
	void MapListReader ( int ind, long p);
	void SmooListReader ( int ind, long p);
	void TrMatrixReader( int ind, long p);
	void LightReader( int ind, long p);
	void SpotLightReader( int ind, long p);
	void CameraReader( int ind, long p);
	CTmpMaterial *FindMaterialByName(CString szMatName);
	void MatNameReader ( int ind, long p);
	void MapFileReader( int ind, long p);
	void FramesReader( int ind, long p);
	void TrackObjNameReader( int ind, long p);
	void PivotPointReader( int ind, long p);
	void SplineFlagsReader( int ind,word flags);
	void TrackPosReader( int ind, long p);
	void TrackRotReader( int ind, long p);
	void TrackScaleReader( int ind, long p);
	void ObjNumberReader( int ind, long p);
	int FindChunk(word id);
	bool Dispatch(int id,int ind,long p);
	void ChunkReader(int ind, long p);
	bool Load3ds(char FileName[260]);
	dword WriteTexInfo(FILE *f,CKTexture *pTexture);
	void WriteMatList(FILE *f);
	bool DispatchSave(LPCTSTR szFileName);
	bool SaveTo3ds(char FileName[260]);
};

#endif // !defined(AFX_KIOTXT_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
