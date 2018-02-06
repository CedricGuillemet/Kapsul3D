// KIoFile.h: interface for the CKIoTxt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KIoFile_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
#define AFX_KIoFile_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKIoFile : public CKFilePlugin
{
public:
	CKIoFile();
	virtual ~CKIoFile();

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
	CKOption *KOption;

};

#endif // !defined(AFX_KIOTXT_H__F6539E57_4BF5_45B5_95B6_D4D8499AE4EE__INCLUDED_)
