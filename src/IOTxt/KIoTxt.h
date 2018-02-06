// KIoTxt.h: interface for the CKIoTxt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIOTXT_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
#define AFX_KIOTXT_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKIoTxt : public CKFilePlugin
{
public:
	CKIoTxt();
	virtual ~CKIoTxt();

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
	CKSkeleton *CurSkel;
	char temp[512],temp2[512];
	int nBufSize;
	float v1,v2,v3;
	CKOption *m_Option;
	void ReadBone(CKBone *daBone,FILE *fp);
	void WriteBone(CKBone *daBone,FILE *fp);
};

#endif // !defined(AFX_KIOTXT_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
