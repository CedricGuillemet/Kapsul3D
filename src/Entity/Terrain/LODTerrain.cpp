#include "stdafx.h"
#include "Kapsul3D.h"

/*
UINT __declspec(dllexport) Process_LODTerrain(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
	UINT value=0;
	switch(Msg)
	{
	case KM_SETENTITY:
		if (((CEntity*)wParam)->CompilData==NULL)
		{
			((CEntity*)wParam)->CompilData=new CWorldSpawn;
			SyncCreate=0;
			IsCreating=true;
		}

		CurWorldSpawn=(CWorldSpawn*)((CEntity*)wParam)->CompilData;
		WSCurEntity=(CEntity*)wParam;
		
		break;
	case KM_FREEENTITY:
		if ( ((CEntity*)wParam)->CompilData!=NULL) delete (CWorldSpawn*)((CEntity*)wParam)->CompilData;
		break;

	case KM_DRAW:
		glColor4f(0,0,1,1);
		glBegin(GL_QUADS);
		glVertex3f(CurWorldSpawn->Lower.vx,CurWorldSpawn->Lower.vy,CurWorldSpawn->Lower.vz);
		glVertex3f(CurWorldSpawn->Upper.vx,CurWorldSpawn->Lower.vy,CurWorldSpawn->Lower.vz);
		glVertex3f(CurWorldSpawn->Upper.vx,CurWorldSpawn->Upper.vy,CurWorldSpawn->Lower.vz);
		glVertex3f(CurWorldSpawn->Lower.vx,CurWorldSpawn->Upper.vy,CurWorldSpawn->Lower.vz);
		glEnd();
		break;
	case KM_ISCREATING:
		value=IsCreating;
		break;
	case KM_LMOUSEDOWN:
		if (IsCreating)
		{
			if (SyncCreate==0)
			{
				CurWorldSpawn->Lower=*((Vertex *)(lParam));
				CurWorldSpawn->Upper=*((Vertex *)(lParam));

				SyncCreate++;
			}
			else
			if (SyncCreate==1)
			{
				SyncCreate=0;
				IsCreating=0;
			}
		}
		break;
	case KM_MOUSEMOVE:
		if (IsCreating)
		{
			if (SyncCreate==0)
			{
			
			}
			else
			if (SyncCreate==1)
			{
				CurWorldSpawn->Upper=*((Vertex *)(lParam));
			}
		}
		break;

	default:
		break;
	}

	return value;
}
*/