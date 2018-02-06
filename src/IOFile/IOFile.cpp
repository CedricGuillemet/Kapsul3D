/*

	IOFile.CPP
	Plugin Skeleton
	A working example that is recognize in kapsul
	but does nothing :-p

*/

#include "stdafx.h"
#include <stdio.h>
#include "iofile.h"

CKIoFile::CKIoFile()
{
}
 CKIoFile::~CKIoFile()
 {
 }

CString CKIoFile::GetName()
{
	return "Kapsul File Plugin Skeleton";
}
CString CKIoFile::GetInfos()
{
	return "Kapsul File Plugin Skeleton";
}
CString CKIoFile::GetFilter()
{
	return "*.Dummy";
}
CString CKIoFile::GetFileDescription()
{
	return "Kapsul Dummy file";
}
CString CKIoFile::GetFileExtension()
{
	return ".dummy";
}


bool CKIoFile::SupportReading()
{
	return true;
}
bool CKIoFile::SupportWriting()
{
	return true;
}
bool CKIoFile::Read(CKScene *pScene,CString FullFilePath)
{
	FILE *fp;
	// DO NOT forget to return value corresponding on Loading success
	// Same for saving.

	KOption=(CKOption*)GetGOption();

	fp=fopen(FullFilePath,"rt");
	if (fp!=NULL)
	{
		// Load the file
		// do the stuff here

		fclose(fp);
		//return true; // Good Loading
		// but loading always fail ;)
		return false;
	}

	return false; // Bad Loading
}
bool CKIoFile::Write(CKScene *pScene,CString FullFilePath)
{
	FILE *fp;
	
	fp=fopen(FullFilePath,"wt");
	if (fp!=NULL)
	{
		// save the file
		// do the stuff here

		fclose(fp);
		return true; // Good saving
	}

	return false; // Bad saving
}
