// EntityType.h: interface for the CEntityType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITYTYPE_H__3AE254DB_2249_4FC9_9724_94074B24B194__INCLUDED_)
#define AFX_ENTITYTYPE_H__3AE254DB_2249_4FC9_9724_94074B24B194__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EntityProp.h"

class __declspec( dllexport ) CEntityType  
{
public:
	CEntityType *Next;
	CEntityType *Prev;
	char Name[32];
	CEntityType(CEntityType *daPrev,CEntityType *daNext);
	virtual ~CEntityType();
    CEntityProp *FirstProp,*NextProp;

    void AddEntityProp(char *daName);
    CEntityProp *GetByName(char *daName);
    void DelEntityProp(CEntityProp *daProp);
};

__declspec( dllexport ) CEntityType *AddEntityType(char *daName);
__declspec( dllexport ) bool WriteEntityTypes2Disk(char *FileName);
__declspec( dllexport ) bool ReadEntityTypesFromDisk(char *FileName);
__declspec( dllexport ) CEntityType *GetByName(char *daName);
__declspec( dllexport ) void DelEntityType(CEntityType *daEnt);
__declspec( dllexport ) void DelAllEntityType(void);
__declspec( dllexport ) CEntityType *GetFirstEntType(void);

#endif // !defined(AFX_ENTITYTYPE_H__3AE254DB_2249_4FC9_9724_94074B24B194__INCLUDED_)
