#include "StdAfx.h"
/*
#include "kfile.h"

#include <io.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
*/

extern CKPluginManager *daLib;

CKFile::CKFile(void)
{
    UseResource=false;
    fp=NULL;
    Datas=NULL;
    ResourceName=NULL;
    CurFileName=NULL;
    HasWrite=false;
}

CKFile::~CKFile(void)
{
    if (ResourceName!=NULL) delete ResourceName;
    if (fp!=NULL)
        fclose();
    if (CurFileName!=NULL) delete [] CurFileName;
}

int CKFile::fopen(CString FileName,CString Mode)
{
    fclose();

	CString ZipRep;
	daGen=daLib->GetSupportedResManager(FileName,ZipName,ZipRep);
	if (daGen!=NULL)
	{
		fp=(FILE*)daGen->Process(KM_RESOURCEOPEN,(UINT)ZipName.GetBuffer(0),(UINT)ZipRep.GetBuffer(0));
		UseResource=true;
		return (int)fp;
	}
	else
	{
		// simple file
		UseResource=false;
        fp=::fopen(FileName,Mode);
        return (int)fp;
    }

/*
    if (UseResource)
    {
        if (strstr(Mode,"r"))
            SetArchive(ResourceName,false);
        else
            SetArchive(ResourceName,true);

        FilePtr=0;
        if (CurFileName!=NULL) delete [] CurFileName;
        CurFileName=new char[strlen(FileName)+1];
        memcpy(CurFileName,FileName,strlen(FileName)+1);

        CurInd=GetFileIndex(FileName);
        if (CurInd!=-1)
        {
            CurFileSize=Entries[CurInd].m_uUncomprSize;
            Datas=(unsigned char*)malloc(CurFileSize);
            LoadFile(FileName,Datas);
            MaxSize=CurFileSize;
            HasWrite=false;
            FilePtr=0;
        }
        else
        {
            // new file
            CZipFileHeader header;
            header.SetFileName(FileName);
            daZip.OpenNewFile(header);
            MaxSize=0;
            HasWrite=false;
            FilePtr=0;
            Datas=NULL;
        }
        return 1;
    }
    else
    {
	*/
}

void CKFile::fclose(void)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		daGen->Process(KM_RESOURCECLOSE,(UINT)fp);
		fp=NULL;
		/*
        // do flush datas
        if (HasWrite)
        {
            if (CurInd!=-1)
            {
                daZip.CloseFile();
                daZip.DeleteFile(CurInd);
                CZipFileHeader header;
                header.SetFileName(CurFileName);
                daZip.OpenNewFile(header);
            }

            daZip.WriteNewFile(Datas,CurFileSize);
            daZip.CloseNewFile();
        }

        if (Datas!=NULL)
            free(Datas);

        daZip.Close();
		*/
    }
    else
    {
        if (fp!=NULL)
        {
            ::fclose(fp);
            fp=NULL;
        }
    }
}

int CKFile::fseek(long offset,int origin)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		return 0;
		daGen->Process(KM_SETRESOURCEHANDLE,(UINT)fp,0);
		daGen->Process(KM_RESOURCESEEK,(UINT)origin,(UINT)offset);
/*
        switch(origin)
        {
        case SEEK_CUR:
            FilePtr+=offset;
            break;
        case SEEK_END:
            FilePtr=CurFileSize+offset;
            break;
        case SEEK_SET:
            FilePtr=offset;
            break;
        }
		*/
    }
    else
    {
        return ::fseek(fp,offset,origin);
    }
}

int CKFile::fread(void *ptr)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		daGen->Process(KM_RESOURCEREAD,(UINT)fp,(UINT)ptr);
		return 1;
/*
        if (FilePtr+Size>CurFileSize)
        {
            int tmpSize=CurFileSize-FilePtr;
            memcpy(ptr,Datas,CurFileSize-FilePtr);
            FilePtr=CurFileSize;
            return tmpSize;
        }
        else
        {
            FilePtr+=Size;
            memcpy(ptr,Datas,Size);
        }
		*/
    }
    else
    {
        return ::fread(ptr,GetLength(),1,fp);
    }
}

int CKFile::fwrite(void *ptr,unsigned int Size)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		/*
        HasWrite=true;
        if (Datas==NULL)
        {
            Datas=(unsigned char *)malloc(65536);
            MaxSize=65536;
            CurFileSize=Size;
        }
        else
        {
            if (FilePtr+Size>CurFileSize)
            {
                MaxSize+=(((Size-(Size%65536))/65536)+1)*65536;
                Datas=(unsigned char*)realloc(Datas,MaxSize);

            }
        }
        memcpy(&Datas[FilePtr],ptr,Size);
        FilePtr+=Size;
        if (FilePtr>CurFileSize) CurFileSize=FilePtr;
		*/
		daGen->Process(KM_SETRESOURCEHANDLE,(UINT)fp,0);
		daGen->Process(KM_RESOURCEWRITE,(UINT)ptr,(UINT)Size);
		return 1;
    }
    else
    {
        return ::fwrite(ptr,Size,1,fp);
    }
}

unsigned int CKFile::GetLength(void)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		return (UINT)daGen->Process(KM_RESOURCEGETFILESIZE);
    }
    else
    {
        if (fp!=NULL)
        {
            int fno=_fileno(fp);
            return _filelength(fno);
        }
        return 0;
    }
}

char *CKFile::fgets(char *ptr,int MaxBufLength)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		return 0;
    }
    else
    {
        return ::fgets(ptr,MaxBufLength,fp);
    }
}

int CKFile::fputs(char *ptr)
{
    if ((UseResource)&&(daGen!=NULL))
    {
        //HasWrite=true;
		return 0;
    }
    else
    {
        return ::fputs(ptr,fp);
    }
}

int CKFile::fgetc(void)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		return 0;
    }
    else
    {
        return ::fgetc(fp);
    }
}

int CKFile::fputc(int c)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		/*
        if (FilePtr==CurFileSize)
        {
           // if (

        }
        HasWrite=true;
		*/
		return 0;
    }
    else
    {
        return ::fputc(c,fp);
    }
}

bool CKFile::Exist(CString FileName)
{
	CString ZipRep;
	daGen=daLib->GetSupportedResManager(FileName,ZipName,ZipRep);
	if (daGen!=NULL)
	{
		fp=(FILE*)daGen->Process(KM_RESOURCEOPEN,(UINT)ZipName.GetBuffer(0),(UINT)ZipRep.GetBuffer(0));
		daGen->Process(KM_RESOURCECLOSE,(UINT)fp);		
		return (fp!=NULL);
	}
	else
	{
		FILE *tmpfp=::fopen(FileName,"rb");
		if (tmpfp!=NULL)
		{
			::fclose(tmpfp);
			return true;
		}
		return false;
	}
}

int CKFile::ftell(void)
{
    if ((UseResource)&&(daGen!=NULL))
    {
		return 0;
    }
    else
    {
        return ::ftell(fp);
    }
}