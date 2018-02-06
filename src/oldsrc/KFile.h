#pragma once
//#include "pakfile.h"

class KAPSUL_DESC CKFile 
{
public:
    bool UseResource;
    int CurInd; //file indice for resource
    unsigned int CurFileSize;
    FILE *fp;
    char *ResourceName;
    unsigned int FilePtr;
    unsigned int MaxSize;
    bool HasWrite;
    char *CurFileName;


    int fopen(CString FileName,CString Mode);
    void fclose(void);
    int fseek(long offset,int origin);
    int fread(void *ptr);
    int fwrite(void *ptr,unsigned int Size);
    unsigned int GetLength(void);
    char *fgets(char *ptr,int MaxBufLength);
    int fputs(char *ptr);
    int fgetc(void);
    int fputc(int c);
	int ftell(void);
	bool Exist(CString FileName);

    unsigned char *Datas;
	CKPlugin *daGen;
	CString ZipName;

public:
    CKFile(void);
    ~CKFile(void);
};
