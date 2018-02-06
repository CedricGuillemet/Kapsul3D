#include "StdAfx.h"
#include "Zip_src\ZipArchive.h"	
#include "pakfile.h"




bool GetZipName(char *Path,char *Dest,char *ZipRep)
{
    ZipRep[0]=0;
    char *tmp2=strstr(Path,".zip");
    if (tmp2==NULL) return false;

    if ((Dest==NULL)||(ZipRep==NULL)) return true;

    unsigned int ptr=(unsigned int)tmp2-(unsigned int)Path;
    int MaxLen=ptr+4;
    memcpy(Dest,Path,MaxLen);
    Dest[MaxLen]=0;
    int DstAv=0;
/*
    while (Path[ptr]!='\\') ptr--;

    ptr++;


    while ((Path[ptr]!='\\')&&(Path[ptr]!=0))
    {
        Dest[DstAv++]=Path[ptr++];
        Dest[DstAv]=0;
    }
    */
    ptr=MaxLen;
    if (((Path[ptr]=='\\')&&(Path[ptr+1]!='0'))&&(Path[ptr]!=0))
    {
        ptr++;
        DstAv=0;

        while (Path[ptr]!=0)
        {
            ZipRep[DstAv++]=Path[ptr++];
            ZipRep[DstAv]=0;
        }
        strcat(ZipRep,"\\");
    }

}


CPakFile::CPakFile(void)
{
	//daArch=NULL;
}

CPakFile::~CPakFile(void)
{
}

void CPakFile::SetPassWord(char *daPass)
{
}

bool CPakFile::SetArchive(char * daArch,bool ReadWrite)
{
    if (daArch!=NULL)
    {
        if (strcmp(daArch,Archive)==0) return true;
        daZip.Close();
        strcpy(Archive,daArch);
        
    }
    FILE *tmpf=fopen(daArch,"rb");
    if (tmpf==NULL)
    {
        daZip.Open(Archive,CZipArchive::create);
    }
    else
    {
        fclose(tmpf);
        daZip.Open(Archive,(ReadWrite?CZipArchive::open:CZipArchive::
            openReadOnly));
    }
    nbEnts=daZip.GetNoEntries();
    Entries.erase(Entries.begin(), Entries.end());
	for (int i = 0; i < nbEnts; i++)
	{
		CZipFileHeader fh;
        daZip.GetFileInfo(fh, (WORD)i);
        Entries.push_back(fh);

    }
    return true;
}

bool CPakFile::LoadFile(char *daName,void *Dest)
{
    daZip.Open(Archive);
    int fInd=GetFileIndex(daName);
    if (fInd!=-1)
    {
        daZip.OpenFile(fInd);
        daZip.ReadFile(Dest,Entries[fInd].m_uUncomprSize);
        return true;
    }
    
    return false;
}
int CPakFile::GetFileIndex(char *daName)
{
    daZip.Open(Archive);
    CString cfn;
    for (int i = 0; i < nbEnts; i++)
	{
        cfn=Entries[i].GetFileName();
        if (strcmp(cfn.GetBuffer(1),daName)==0)
        {
            return i;
        }
    }
    return -1;
}

unsigned int CPakFile::GetFileSize(char *daName)
{
    int fInd=GetFileIndex(daName);
    if (fInd!=-1)
        return Entries[fInd].m_uUncomprSize;

    return -1;
}

int CountLevel(char *rep)
{
    int value=0;

    for (int i=0;i<strlen(rep);i++)
    {
        if (rep[i]=='\\')
        {
            value++;
        }
    }

    return value;
}
CString tmprep;
char *CPakFile::GetFolder(char *rep,int ind)
{
    int CurLevel=CountLevel(rep)+1;
    int CurInd=0;
    for (int i=0;i<nbEnts;i++)
    {
        if (daZip.IsFileDirectory(i))
        {
            if (CountLevel(Entries[i].GetFileName().GetBuffer(1))==CurLevel)
            {
                bool good=true;

                tmprep=Entries[i].GetFileName();

                if (tmprep.GetLength()<strlen(rep)) good=false;

                if (good)
                {
                    for (int j=0;j<strlen(rep);j++)
                    {
                        if (tmprep.GetAt(j)!=rep[j]) good=false;
                    }
                }

                if (good)
                {
                    if (CurInd==ind)
                    {

                        return tmprep.GetBuffer(1);
                    }
                    CurInd++;
                }
            }
        }
    }
    return NULL;
}
char *CPakFile::GetFolderFiles(char *rep,int ind,char *WildCard,bool &IsFolder,std::vector<FolderFileEntry>	&VectorImageNames)
{
    int CurLevel=CountLevel(rep)+1;
    int CurInd=0;
    CString date,size;
    for (int i=0;i<nbEnts;i++)
    {
        bool good=true;

        tmprep=Entries[i].GetFileName();
        date.Format("%d",Entries[i].m_uModDate);
        size.Format("%d",Entries[i].m_uUncomprSize);

        if (tmprep.GetLength()<strlen(rep)) good=false;

        if (good)
        {
            for (int j=0;j<strlen(rep);j++)
            {
                if (tmprep.GetAt(j)!=rep[j]) 
                {
                    good=false;
                    break;
                }
            }
        }

        if (good)
        {
            //if (CurInd==ind)
            char *anot=tmprep.GetBuffer(1);
            anot+=(strlen(rep));

            {
                if (daZip.IsFileDirectory(i))
                {
                    IsFolder=true;
                    int CurLvl=CountLevel(anot);
                    if (CurLvl==1)
                        //return tmprep.GetBuffer(1);
                        VectorImageNames.push_back(FolderFileEntry(CString(anot),"Folder","0",date));
                    else
                        CurInd--;
                }
                else
                {
                    //return tmprep.GetBuffer(1);
                    int CurLvl=CountLevel(anot);
                    if (CurLvl==0)
                        //VectorImageNames.push_back(anot);
                        VectorImageNames.push_back(FolderFileEntry(CString(anot),"Packed file",size,date));
                }
            }
            CurInd++;
        }
    }
    return NULL;
}

    CString Name;
    CString Type;
    unsigned int Size;
    CString Date;