// Option.h: interface for the COption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTION_H__90F178C3_2BAD_46F8_B636_FDCC5AC0E3EB__INCLUDED_)
#define AFX_OPTION_H__90F178C3_2BAD_46F8_B636_FDCC5AC0E3EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec( dllexport )COption  
{
private:
    char *OptMapDirs[100];
    int nbMapsDir;

public:
	COption();
	virtual ~COption();

    void AddMapDir(char *daMapDir);
    void DelAllMapDir(void);
    int GetnbMapDir(void);
    char * GetMapDir(int Number);

};


//COption __declspec( dllexport ) KOption;

#endif // !defined(AFX_OPTION_H__90F178C3_2BAD_46F8_B636_FDCC5AC0E3EB__INCLUDED_)
