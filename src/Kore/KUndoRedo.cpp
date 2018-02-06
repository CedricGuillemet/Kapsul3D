// UndoRedo.cpp: implementation of the CKUndoRedo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
/*
#include "UndoRedo.h"
*/
extern CKPluginManager *daLib;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CKUndoRedo::CKUndoRedo(CString _PlugName,CKScene *_Scene,int _nbEntries,CKUndoRedo *_Prev,CKUndoRedo *_Next)
{
	//PlugName=new char [32];
	PlugName=_PlugName;

	Prev=_Prev;
	Next=_Next;

	m_Scene=_Scene;
	nbEntries=_nbEntries;
	Entries=new CKUndoRedoEntry [nbEntries];

	gen=daLib->GetScenePluginByName(_PlugName);
}

CKUndoRedo::~CKUndoRedo()
{
	//delete [] PlugName;
	delete [] Entries;
}


CKUndoRedoEntry * CKUndoRedo::GetEntry(int Indice)
{
	return &Entries[Indice];
}

void CKUndoRedo::SetAfterEntry(int Indice, int Type, void *Entry)
{
	Entries[Indice].EntityType=Type;

	switch(Type)
	{
	case PLUGIN_MESH:
		if (Entries[Indice].AfterState==NULL)
			Entries[Indice].AfterState=new (CKMesh)();
		((CKMesh*)Entries[Indice].AfterState)->IsCopyOf((CKMesh*)Entry);
		break;
	case PLUGIN_CAMERA:
		if (Entries[Indice].AfterState==NULL)
			Entries[Indice].AfterState=new (CKCamera)();
		((CKCamera*)Entries[Indice].AfterState)->IsCopyOf((CKCamera*)Entry);
		break;
	case PLUGIN_ENTITY:
		if (Entries[Indice].AfterState==NULL)
			Entries[Indice].AfterState=new (CKEntity)();
		((CKEntity*)Entries[Indice].AfterState)->IsCopyOf((CKEntity*)Entry);
		break;
	case PLUGIN_PATCH:
		if (Entries[Indice].AfterState==NULL)
			Entries[Indice].AfterState=new (CKPatch)();
		((CKPatch*)Entries[Indice].AfterState)->IsCopyOf((CKPatch*)Entry);
		break;
	case PLUGIN_SKELETON:
		if (Entries[Indice].AfterState==NULL)
			Entries[Indice].AfterState=new (CKSkeleton)();
		((CKSkeleton*)Entries[Indice].AfterState)->IsCopyOf((CKSkeleton*)Entry);
		break;
	case PLUGIN_SHAPE:
		if (Entries[Indice].AfterState==NULL)
			Entries[Indice].AfterState=new (CKShape)();
		((CKShape*)Entries[Indice].AfterState)->IsCopyOf((CKShape*)Entry);
		break;

	default:
		break;

	}

}

void CKUndoRedo::SetPrevEntry(int Indice, int Type, void *Entry)
{
	Entries[Indice].EntityType=Type;

	switch(Type)
	{
	case PLUGIN_MESH:
		if (Entries[Indice].PreviousState==NULL)
			Entries[Indice].PreviousState=new (CKMesh)();
		((CKMesh*)Entries[Indice].PreviousState)->IsCopyOf((CKMesh*)Entry);
		break;
	case PLUGIN_CAMERA:
		if (Entries[Indice].PreviousState==NULL)
			Entries[Indice].PreviousState=new (CKCamera)();
		((CKCamera*)Entries[Indice].PreviousState)->IsCopyOf((CKCamera*)Entry);
		break;
	case PLUGIN_ENTITY:
		if (Entries[Indice].PreviousState==NULL)
			Entries[Indice].PreviousState=new (CKEntity)();
		((CKEntity*)Entries[Indice].PreviousState)->IsCopyOf((CKEntity*)Entry);
		break;
	case PLUGIN_PATCH:
		if (Entries[Indice].PreviousState==NULL)
			Entries[Indice].PreviousState=new (CKPatch)();
		((CKPatch*)Entries[Indice].PreviousState)->IsCopyOf((CKPatch*)Entry);
		break;
	case PLUGIN_SHAPE:
		if (Entries[Indice].PreviousState==NULL)
			Entries[Indice].PreviousState=new (CKShape)();
		((CKShape*)Entries[Indice].PreviousState)->IsCopyOf((CKShape*)Entry);
		break;
	case PLUGIN_SKELETON:
		if (Entries[Indice].PreviousState==NULL)
			Entries[Indice].PreviousState=new (CKSkeleton)();
		((CKSkeleton*)Entries[Indice].PreviousState)->IsCopyOf((CKSkeleton*)Entry);
		break;

	default:
		break;

	}

}

void CKUndoRedo::CommitAllPrev(CKScenePlugin *gen)
{
	CKMesh *daObj;
	CKCamera *daCam;
	CKSkeleton *daSkel;
	CKShape *daCKShape;
	CKEntity *daEntity;
	CKPatch *daPatch;

	for (int i=0;i<nbEntries;i++)
	{
		switch(Entries[i].EntityType)
		{

		// -- CKMesh ----------------------------------------------------------
		case PLUGIN_MESH:
			switch(UndoType)
			{
			case UNDO_CREATE:
				daObj=(CKMesh*)m_Scene->GetByUnique(((CKMesh*)Entries[i].AfterState)->Unique,PLUGIN_MESH);
				if (daObj!=NULL)
				{
					if (gen!=NULL)
						gen->DeleteStuff((void*)daObj,PLUGIN_MESH);

					m_Scene->DelMesh(daObj);
				}
				break;
			case UNDO_MODIFY:
				daObj=(CKMesh*)m_Scene->GetByUnique(((CKMesh*)Entries[i].PreviousState)->Unique,PLUGIN_MESH);
				if (daObj!=NULL)
					daObj->IsCopyOf((CKMesh*)Entries[i].PreviousState);

				break;
			case UNDO_DELETE:
				m_Scene->AddMesh();
				daObj=m_Scene->NextMesh;
				daObj->IsCopyOf(((CKMesh*)Entries[i].PreviousState));
				break;
			}
			break;
		// -- CKCamera ----------------------------------------------------------
		case PLUGIN_CAMERA:
			switch(UndoType)
			{
			case UNDO_CREATE:
				daCam=(CKCamera*)m_Scene->GetByUnique(((CKCamera*)Entries[i].AfterState)->Unique,PLUGIN_CAMERA);
				if (daCam!=NULL)
				{
					if (gen!=NULL)
						gen->DeleteStuff((void*)daCam,PLUGIN_CAMERA);

					m_Scene->DelCamera(daCam);
				}
				break;
			case UNDO_MODIFY:
				daCam=(CKCamera*)m_Scene->GetByUnique(((CKCamera*)Entries[i].PreviousState)->Unique,PLUGIN_CAMERA);
				if (daCam!=NULL)
					daCam->IsCopyOf((CKCamera*)Entries[i].PreviousState);

				break;
			case UNDO_DELETE:
				m_Scene->AddCam();
				daCam=m_Scene->NextCam;
				daCam->IsCopyOf(((CKCamera*)Entries[i].PreviousState));
				break;
			}
			break;
		// -- Entity ----------------------------------------------------------
		case PLUGIN_ENTITY:
			switch(UndoType)
			{
			case UNDO_CREATE:
				daEntity=(CKEntity*)m_Scene->GetByUnique(((CKEntity*)Entries[i].AfterState)->Unique,PLUGIN_ENTITY);
				if (daEntity!=NULL)
				{
					if (gen!=NULL)
						gen->DeleteStuff((void*)daEntity,PLUGIN_ENTITY);

					m_Scene->DelEntity(daEntity);
				}
				break;
			case UNDO_MODIFY:
				daEntity=(CKEntity*)m_Scene->GetByUnique(((CKEntity*)Entries[i].PreviousState)->Unique,PLUGIN_ENTITY);
				if (daEntity!=NULL)
					daEntity->IsCopyOf((CKEntity*)Entries[i].PreviousState);

				break;
			case UNDO_DELETE:
				daEntity=m_Scene->AddEntity(((CKEntity*)Entries[i].PreviousState)->EntType);
				daEntity->IsCopyOf(((CKEntity*)Entries[i].PreviousState));
				break;
			}
			break;
		// -- Patch -----------------------------------------------------------
		case PLUGIN_PATCH:
			switch(UndoType)
			{
			case UNDO_CREATE:
				daPatch=(CKPatch*)m_Scene->GetByUnique(((CKPatch*)Entries[i].AfterState)->Unique,PLUGIN_PATCH);
				if (daPatch!=NULL)
				{
					if (gen!=NULL)
						gen->DeleteStuff((void*)daPatch,PLUGIN_PATCH);

					m_Scene->DelPatch(daPatch);
				}
				break;
			case UNDO_MODIFY:
				daPatch=(CKPatch*)m_Scene->GetByUnique(((CKPatch*)Entries[i].PreviousState)->Unique,PLUGIN_PATCH);
				if (daPatch!=NULL)
					daPatch->IsCopyOf((CKPatch*)Entries[i].PreviousState);

				break;
			case UNDO_DELETE:
				m_Scene->AddPatch();
				daPatch=m_Scene->NextPatch;
				daPatch->IsCopyOf(((CKPatch*)Entries[i].PreviousState));
				break;
			}
			break;

		// -- CKShape -----------------------------------------------------------
		case PLUGIN_SHAPE:
			switch(UndoType)
			{
			case UNDO_CREATE:
				daCKShape=(CKShape*)m_Scene->GetByUnique(((CKShape*)Entries[i].AfterState)->Unique,PLUGIN_SHAPE);
				if (daCKShape!=NULL)
				{
					if (gen!=NULL)
						gen->DeleteStuff((void*)daCKShape,PLUGIN_SHAPE);

					m_Scene->DelShape(daCKShape);
				}
				break;
			case UNDO_MODIFY:
				daCKShape=(CKShape*)m_Scene->GetByUnique(((CKShape*)Entries[i].PreviousState)->Unique,PLUGIN_SHAPE);
				if (daCKShape!=NULL)
					daCKShape->IsCopyOf((CKShape*)Entries[i].PreviousState);

				break;
			case UNDO_DELETE:
				m_Scene->AddShape();
				daCKShape=m_Scene->NextShape;
				daCKShape->IsCopyOf(((CKShape*)Entries[i].PreviousState));
				break;
			}
			break;
		// -- CKSkeleton -------------------------------------------------------
		case PLUGIN_SKELETON:
			switch(UndoType)
			{
			case UNDO_CREATE:
				daSkel=(CKSkeleton*)m_Scene->GetByUnique(((CKSkeleton*)Entries[i].AfterState)->Unique,PLUGIN_SKELETON);
				if (daSkel!=NULL)
				{
					if (gen!=NULL)
						gen->DeleteStuff((void*)daSkel,PLUGIN_SKELETON);

					m_Scene->DelSkeleton(daSkel);
				}
				break;
			case UNDO_MODIFY:
				daSkel=(CKSkeleton*)m_Scene->GetByUnique(((CKSkeleton*)Entries[i].PreviousState)->Unique,PLUGIN_SKELETON);
				if (daSkel!=NULL)
					daSkel->IsCopyOf((CKSkeleton*)Entries[i].PreviousState);

				break;
			case UNDO_DELETE:
				m_Scene->AddSkel();
				daSkel=m_Scene->NextSkel;
				daSkel->IsCopyOf(((CKSkeleton*)Entries[i].PreviousState));
				break;
			}
			break;

		default:
			break;
		}
	}
}

void CKUndoRedo::CommitAllAfter()
{
	CKObjectBase *daObj;

	for (int i=0;i<nbEntries;i++)
	{
		switch(UndoType)
		{
		case UNDO_CREATE:
			daObj=Entries[i].AfterState->AllocateNew();
			daObj->IsCopyOf(Entries[i].AfterState);
			break;
		case UNDO_MODIFY:
			daObj=(CKMesh*)m_Scene->GetByUnique(((CKMesh*)Entries[i].AfterState)->Unique,PLUGIN_MESH);
			if (daObj!=NULL)
				daObj->IsCopyOf((CKMesh*)Entries[i].AfterState);//->IsCopyOf(daObj);

			break;
		case UNDO_DELETE:
			daObj=(CKMesh*)m_Scene->GetByUnique(((CKMesh*)Entries[i].PreviousState)->Unique,PLUGIN_MESH);
			if (daObj!=NULL)
				m_Scene->DelMesh(daObj);

			break;
		}
	}
}
