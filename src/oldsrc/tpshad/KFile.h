#pragma once
#include "pakfile.h"

class CKFile :
    public CPakFile
{
public:
    void SetResource(char *PakFile);
    bool UseResource;
    int CurInd; //file indice for resource
    unsigned int CurFileSize;
    FILE *fp;
    char *ResourceName;
    unsigned int FilePtr;
    unsigned int MaxSize;
    bool HasWrite;
    char *CurFileName;


    int fopen(char *FileName,char *Mode);
    void fclose(void);
    int fseek(long offset,int origin);
    int fread(void *ptr,unsigned int Size);
    int fwrite(void *ptr,unsigned int Size);
    unsigned int GetLength(void);
    char *fgets(char *ptr,int MaxBufLength);
    int fputs(char *ptr);
    int fgetc(void);
    int fputc(int c);

    unsigned char *Datas;

public:
    CKFile(void);
    ~CKFile(void);
};
