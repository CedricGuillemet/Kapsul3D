// EntityType.cpp: implementation of the CEntityType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "Enti.h"
#include "EntityProp.h"
#include "EntityType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEntityType *FirstEntType=NULL,*NextEntType=NULL;
CEntityType *AddEntityType(char *daName)
{
    if (FirstEntType==NULL)
    {
        FirstEntType=new CEntityType(NULL,NULL);
        NextEntType=FirstEntType;
    }
    else
    {
        NextEntType->Next=new CEntityType(NextEntType,NULL);
        NextEntType=NextEntType->Next;
    }

    strcpy(NextEntType->Name,daName);

    return NextEntType;
}

bool WriteEntityTypes2Disk(char *FileName)
{
    CEntityType *daEnt;

    FILE *fp=fopen(FileName,"wt");
    if (fp!=NULL)
    {
        int nbEnts=0;

        for (daEnt=FirstEntType;daEnt!=NULL;daEnt=daEnt->Next)
            nbEnts++;

        char temp[512];

        sprintf(temp,"%d Entities\n",nbEnts);
        fputs(temp,fp);

        for (daEnt=FirstEntType;daEnt!=NULL;daEnt=daEnt->Next)
        {
            fputs(daEnt->Name,fp);

            fputs("\n{\n",fp);
            for (CEntityProp *daProp=daEnt->FirstProp;daProp!=NULL;daProp=daProp->Next)
            {
                sprintf(temp,"%d %d %s\n",daProp->SizeVals,daProp->Type,daProp->Name);
                fputs(temp,fp);
                if (daProp->SizeVals!=0)
                {
                    fputs(daProp->Vals,fp);
                    fputs("\n",fp);
                }
            }

            fputs("}\n",fp);
        }

        fclose(fp);
        return true;
    }
    return false;
}

bool ReadEntityTypesFromDisk(char *FileName)
{
    CEntityType *daEnt;

    FILE *fp=fopen(FileName,"rt");
    if (fp!=NULL)
    {
        char temp[512];
        int nBufSize=512;
        int nbEnts;

        fgets(temp,nBufSize,fp);
        sscanf(temp,"%d Entities",&nbEnts);

        for (int i=0;i<nbEnts;i++)
        {
            fgets(temp,nBufSize,fp);
            temp[strlen(temp)-1]=0;
            temp[31]=0;

            daEnt=AddEntityType(temp);

            fgets(temp,nBufSize,fp);

            fgets(temp,nBufSize,fp);
            while(temp[0]!='}')
            {
                char temp2[512];
                int daType;
                int SizeVals;

                sscanf(temp,"%d %d %s",&SizeVals,&daType,temp2);
                temp2[strlen(temp2)]=0;
                temp2[31]=0;

                daEnt->AddEntityProp(temp2);
                daEnt->NextProp->Type=daType;
                daEnt->NextProp->SizeVals=SizeVals;
                if (SizeVals!=0)
                {
                    daEnt->NextProp->Vals=new char [SizeVals+2];
                    fgets(daEnt->NextProp->Vals,SizeVals+2,fp);
                    daEnt->NextProp->Vals[SizeVals]=0;
                }

                fgets(temp,nBufSize,fp);
            }
        }

        fclose(fp);
        return true;
    }
    return false;
}

CEntityType *GetByName(char *daName)
{
    for (CEntityType *daEnt=FirstEntType;daEnt!=NULL;daEnt=daEnt->Next)
        if (strcmp(daName,daEnt->Name)==0) return daEnt;

    return NULL;
}

void DelEntityType(CEntityType *daEnt)
{
    if (daEnt!=NULL)
    {
        if (daEnt==FirstEntType)
        {
            FirstEntType->Next->Prev=NULL;
            FirstEntType=FirstEntType->Next;
        }
        else
        if (daEnt==NextEntType)
        {
            NextEntType->Prev->Next=NULL;
        }
        else
        {
            daEnt->Next->Prev=daEnt->Prev;
            daEnt->Prev->Next=daEnt->Next;
        }

        delete daEnt;
    }
}

void DelAllEntityType(void)
{
    for (CEntityType *daEnt=FirstEntType;daEnt!=NULL;daEnt=daEnt->Next)
        delete daEnt;
}

CEntityType *GetFirstEntType(void)
{
    return FirstEntType;
}

CEntityType::CEntityType(CEntityType *daPrev,CEntityType *daNext)
{
    Prev=daPrev;
    Next=daNext;
    memset(Name,0,32);
    FirstProp=NULL;
    NextProp=NULL;
}

CEntityType::~CEntityType()
{
    for (CEntityProp *daProp=FirstProp;daProp!=NULL;daProp=daProp->Next)
        delete daProp;
}

void CEntityType::AddEntityProp(char *daName)
{
    if (FirstProp==NULL)
    {
        FirstProp=new CEntityProp(NULL,NULL);
        NextProp=FirstProp;
    }
    else
    {
        NextProp->Next=new CEntityProp(NextProp,NULL);
        NextProp=NextProp->Next;
    }

    strcpy(NextProp->Name,daName);
}


CEntityProp *CEntityType::GetByName(char *daName)
{
    for (CEntityProp *daProp=FirstProp;daProp!=NULL;daProp=daProp->Next)
        if (strcmp(daName,daProp->Name)==0) return daProp;

    return NULL;
}

void CEntityType::DelEntityProp(CEntityProp *daProp)
{
    if (daProp!=NULL)
    {
        if (daProp==FirstProp)
        {
            FirstProp->Next->Prev=NULL;
            FirstProp=FirstProp->Next;
        }
        else
        if (daProp==NextProp)
        {
            NextProp->Prev->Next=NULL;
        }
        else
        {
            daProp->Next->Prev=daProp->Prev;
            daProp->Prev->Next=daProp->Next;
        }

        delete daProp;
    }
}
