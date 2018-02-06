// KFilePlugin.h: interface for the CKFilePlugin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KFILEPLUGIN_H__C7020E6F_DBA6_4316_871F_009A9169A502__INCLUDED_)
#define AFX_KFILEPLUGIN_H__C7020E6F_DBA6_4316_871F_009A9169A502__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class KAPSUL_DESC CKFilePlugin  
{
public:
	CKFilePlugin();
	virtual ~CKFilePlugin();

	HINSTANCE m_hInst;

	virtual CString GetName();
	virtual CString GetInfos();
	virtual CString GetFilter();
	virtual CString GetFileDescription();
	virtual CString GetFileExtension();
	virtual bool SupportReading();
	virtual bool SupportWriting();
	virtual bool Read(CKScene *pScene,CString FullFilePath);
	virtual bool Write(CKScene *pScene,CString FullFilePath);

};

#endif // !defined(AFX_KFILEPLUGIN_H__C7020E6F_DBA6_4316_871F_009A9169A502__INCLUDED_)
