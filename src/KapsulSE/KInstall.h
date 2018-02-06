// KInstall.h: interface for the CKInstall class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KINSTALL_H__D089C327_8767_4963_8391_1FAF4A96142B__INCLUDED_)
#define AFX_KINSTALL_H__D089C327_8767_4963_8391_1FAF4A96142B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKInstall  
{
public:
	CKInstall();
	virtual ~CKInstall();

	void WriteOptionsXML(void);
	void RegisterFileTypes(void);

	void StoreProgramPath(void);
	void SetProgramPath(void);
};

#endif // !defined(AFX_KINSTALL_H__D089C327_8767_4963_8391_1FAF4A96142B__INCLUDED_)
