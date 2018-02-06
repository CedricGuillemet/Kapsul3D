// TokenEx.cpp: implementation of the CTokenEx class.
//
// MFC Simple CString Tokenizer (Version 1)
//	
// Written by Daniel Madden (daniel.madden@compaq.com)
// Copyright © 2000
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name and all copyright 
// notices remains intact. 
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TokenEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTokenEx::CTokenEx()
{
}

CTokenEx::~CTokenEx()
{
}

CString CTokenEx::GetString(CString &tmp, CString Search, BOOL bAddEmpty)
{
	int		nFound=-1;

	CString csRet="";
	CString csTmp1 = tmp;

	if (Search.IsEmpty()) {
		// Add default [comma] if empty!
		// acknowledgement: Guru Prasad [gprasad@rti.ie]
		Search = ","; 
	}

	if (!bAddEmpty) {
		// This 'do loop' will strip the empty
		// deliminators from the string
		if (tmp.Left(Search.GetLength()) == Search) {
			do {
				// get the 
				tmp = csTmp1.Mid(Search.GetLength());
				csTmp1 = tmp;
			} while (tmp.Left(Search.GetLength()) == Search);
			tmp = csTmp1.Mid(Search.GetLength() - 1);
		}
	}

	// copy of the 'ref' tmp variable 
	CString csTmp = tmp;

	// get the first position of the first
	// deliminator in the string
	nFound = tmp.Find(Search,0);
	if (nFound >= 0) {
		// fill the var. with info left
		// of the deliminator
		csRet = csTmp.Left(nFound);

		// load the ref'd var. with the info right of
		// the csTmp var.
		tmp = csTmp.Mid(nFound + (Search.GetLength()));
	}
	else {
		// no deliminator found, so return the whole string
		csRet = csTmp;

		// load the ref'd var. with the empty string
		tmp = "";
	}

	// return the string found (if any)
	return csRet;
}


CString CTokenEx::Join(CString Deliminator, CStringArray& AddIt)
{
	CString csReturn;
	CString csTmp;

	if (Deliminator.IsEmpty()) {
		// Add default [comma] if empty!
		// acknowledgement: Guru Prasad [gprasad@rti.ie]
		Deliminator = ","; 
	}

	// Loop through the Array and Append the Deliminator
	// to the string
	for( int iNum = 0; iNum < AddIt.GetSize(); iNum++ ) {
		csTmp += AddIt.GetAt(iNum);
		csTmp += Deliminator;
	}
	// finish the returned string with the info
	// found (and remove the last appended deliminator)
	csReturn = csTmp.Left(csTmp.GetLength() - 1);

	return csReturn;
}


void CTokenEx::Split(CString Source, CString Deliminator, CStringArray& AddIt, BOOL bAddEmpty)
{
	// initialize the variables
	CString		 newCString = Source;
	CString		 tmpCString = "";
	CString		 AddCString = "";

	int pos1 = 0;
	int pos = 0;

	if (Deliminator.IsEmpty()) {
		// Add default [comma] if empty!
		// acknowledgement: Guru Prasad [gprasad@rti.ie]
		Deliminator = ","; 
	}

	// do this loop as long as you have a deliminator
	do {
		// set to zero
		pos1 = 0;
		// position of deliminator starting at pos1 (0)
		pos = newCString.Find(Deliminator, pos1);
		// if the deliminator is found...
		if ( pos != -1 ) {
			// load a new var with the info left
			// of the position
			CString AddCString = newCString.Left(pos);
			if (!AddCString.IsEmpty()) {
				// if there is a string to add, then
				// add it to the Array
				AddIt.Add(AddCString);
			}
			else if (bAddEmpty) {
				// if empty strings are ok, then add them
				AddIt.Add(AddCString);
			}

			// make a copy of the of this var. with the info
			// right of the deliminator
			tmpCString = newCString.Mid(pos + Deliminator.GetLength());
			
			// reset this var with new info
			newCString = tmpCString;
		}
	} while ( pos != -1 );
	
	if (!newCString.IsEmpty()) {
		// as long as the variable is not emty, add it
		AddIt.Add(newCString);
	}

}


void CTokenEx::SplitPath (BOOL UsingDirsOnly, CString Path, CString& Drive, CString& Dir, CString& FName, CString& Ext)
{

	int nSecond;

	// Look for a UNC Name!
	if (Path.Left(2) == "\\\\") {

		// find the first '\' after the first two '\\'
		int nFirst = Path.Find("\\",3);

		// find the second '\' after the first one found
		nSecond = Path.Find("\\",nFirst + 1);

		// if the second does NOT exist
		if (nSecond == -1) {
			// add the 'Path' var to the 'Drive' var
			// because the passed var is just a UNC share
			// i.e.: '\\Server\Share'
			Drive = Path;

			// set ALL others to empty
			Dir = "";
			FName = "";
			Ext = "";
		}
		else if (nSecond > nFirst) {
			// set the 'Drive' var with the correct info
			// i.e.: '\\Server\Share'
			Drive = Path.Left(nSecond);
		}
	}
	else { 
		// Look for normal Drive Structure (C:\Dir\File.name)
		nSecond = 2;
		Drive = Path.Left(2);
	}

	// check if we are looking for directory or file
	if (UsingDirsOnly) {
		// load the correct information in the 'Dir' var
		Dir = Path.Right((Path.GetLength() - nSecond) - 1);

		// set ALL others to empty
		FName = "";
		Ext = "";
	}
	else { // this means we have a filename structure
		// first find the the '\' (in reverse)
		int nDirEnd = Path.ReverseFind('\\');
		if (nDirEnd == Path.GetLength()) {
			// if we are here, this means that
			// 'C:\' was passed, so
			// set ALL to empty
			Dir = "";
			FName = "";
			Ext = "";
		}
		else {

			// set the 'Dir' var with directory info
			Dir = Path.Mid(nSecond + 1, (nDirEnd - nSecond) - 1);

			// breakdown the filename
			//
			// look for a period '.'
			int nFileEnd = Path.ReverseFind('.');

			// if it doesn't exist 
			if (nFileEnd != -1) {
				
				if (nDirEnd > nFileEnd) {
					// this would also mean no file extension found
					FName = Path.Right(Path.GetLength() - nDirEnd);
					Ext = "";
				}
				else {
					// fill vars with info
					FName = Path.Mid(nDirEnd + 1, (nFileEnd - nDirEnd) - 1);
					Ext = Path.Right((Path.GetLength() - nFileEnd) - 1);
				}
			}
			else {
				// this means filename w/o extention
				FName = Path.Right((Path.GetLength() - nDirEnd) - 1);
				Ext = "";
			}
		}
	}
}
