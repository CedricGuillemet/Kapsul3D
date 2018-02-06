// KFilePlugin.cpp: implementation of the CKFilePlugin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KFilePlugin.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKFilePlugin::CKFilePlugin()
{
	
}

CKFilePlugin::~CKFilePlugin()
{
	
}

CString CKFilePlugin::GetName()
{
	return "";
}
CString CKFilePlugin::GetInfos()
{
	return "";
}

CString CKFilePlugin::GetFilter()
{
	return "";
}

CString CKFilePlugin::GetFileDescription()
{
	return "";
}

CString CKFilePlugin::GetFileExtension()
{
	return "";
}

bool CKFilePlugin::SupportReading()
{
	return false;
}

bool CKFilePlugin::SupportWriting()
{
	return false;
}

bool CKFilePlugin::Read(CKScene *pScene,CString FullFilePath)
{
	return false;
}

bool CKFilePlugin::Write(CKScene *pScene,CString FullFilePath)
{
	return false;
}


