// UndoRedoEntry.cpp: implementation of the CKUndoRedoEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
/*
#include "UndoRedoEntry.h"
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKUndoRedoEntry::CKUndoRedoEntry()
{
	EntityType=0;
	PreviousState=NULL;
	AfterState=NULL;
}

CKUndoRedoEntry::~CKUndoRedoEntry()
{

}