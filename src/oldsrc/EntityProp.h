// EntityProp.h: interface for the CEntityProp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ENTITYPROP_H__FD3C5D91_6474_45BB_9752_C5999EA4EB68__INCLUDED_)
#define AFX_ENTITYPROP_H__FD3C5D91_6474_45BB_9752_C5999EA4EB68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec( dllexport ) CEntityProp  
{
public:
	CEntityProp(CEntityProp *daPrev,CEntityProp *daNext);
	virtual ~CEntityProp();

    CEntityProp *Prev,*Next;
    char Name[32];
    int Type;
    char *Vals;
    int SizeVals;

};

#endif // !defined(AFX_ENTITYPROP_H__FD3C5D91_6474_45BB_9752_C5999EA4EB68__INCLUDED_)
