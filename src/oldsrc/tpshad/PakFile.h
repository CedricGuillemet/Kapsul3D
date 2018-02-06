#pragma once
#include <vector>
#include "Zip_src\ZipArchive.h"	

using std::vector;
class FolderFileEntry
{
public:
    CString Name;
    CString Type;
    CString Size;
    CString Date;
public:
    FolderFileEntry(CString _Name,CString _Type, CString _Size, CString _Date)
    {
        Name=_Name;
        Type=_Type;
        Size=_Size;
        Date=_Date;
    }

} ;

class CPakFile
{
public:
    CPakFile(void);
    ~CPakFile(void);
    CZipArchive daZip;
    void SetPassWord(char * daPass);
    bool SetArchive(char * daArch,bool ReadWrite);
    bool LoadFile(char *daName,void *Dest);
    int GetFileIndex(char *daName);
    unsigned int GetFileSize(char *daName);
    char *GetFolder(char *rep,int ind);
    char *GetFolderFiles(char *rep,int ind,char *WildCard,bool &IsFolder,std::vector<FolderFileEntry>	&VectorImageNames);
public:
    char Password[32];
    char Archive[MAX_PATH];
    unsigned int Length;
    unsigned int nbEnts;

    vector<CZipFileHeader> Entries;
};


bool GetZipName(char *Path,char *Dest,char *ZipRep);
extern CPakFile pak;