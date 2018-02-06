// UndoRedoEntry.h: interface for the CUndoRedoEntry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDOREDOENTRY_H__2E4AEBD0_4970_4A5C_BD63_D9182C2A739D__INCLUDED_)
#define AFX_UNDOREDOENTRY_H__2E4AEBD0_4970_4A5C_BD63_D9182C2A739D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class __declspec( dllexport ) CUndoRedoEntry  
{
public:
	/*
	one of those:
	
#define PLUGIN_CAMERA 1
#define PLUGIN_OBJECT 2
#define PLUGIN_SHAPE 4
#define PLUGIN_PARTICLE 8
#define PLUGIN_SKELETTON 16
#define PLUGIN_LIGHT 32
#define PLUGIN_GRID 64
#define PLUGIN_AXIS 128
#define PLUGIN_ENTITY 256

  */
	int EntityType;
	void *PreviousState;
	void *AfterState;
public:
	CUndoRedoEntry();
	virtual ~CUndoRedoEntry();

};

#endif // !defined(AFX_UNDOREDOENTRY_H__2E4AEBD0_4970_4A5C_BD63_D9182C2A739D__INCLUDED_)
