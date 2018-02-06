// KIOWC_Map.h: interface for the CKIoTxt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIOWC_Map_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
#define AFX_KIOWC_Map_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKIOWC_Map : public CKFilePlugin
{
public:
	CKIOWC_Map();
	virtual ~CKIOWC_Map();

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
	CKScene *m_Scene;

	bool LoadFile(char *FileName);
	bool SaveFile(char *fname);
	void LoadWcMap(char *pBuf);
	bool LoadWcEntity(char *m_pData);
	bool LoadWcBrush(char *m_pData);
	char *GetToken(char *m_pData);
	BOOL IsMap(char *szBuffer);
	void WriteObject(CKMesh *obj, FILE *f, int objnum);
	BOOL AreFacePlanesEqual(SFACE *plane1, SFACE *plane2);
	void CreatePlaneByPoly(SFACE *face, CKMesh *obj, int poly_num);
};

#endif // !defined(AFX_KIOTXT_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
