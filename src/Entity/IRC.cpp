#include "stdafx.h"
#include "Kapsul3D.h"
#include "emitter.h"
#include "KIRC.h"

CKIrc *CurIRC;
CKEntity *CurIRCEntity;
//CString xmlDatas,tmpxml;
//MYPOINT spt,spt2;
extern CKSelectionInfos *CurSel;
//extern CKDrawScene *GDrawScene;
extern bool daAddIt;
//MYPOINT sdeb;
extern CKMinMaxEnt m_MinMax;
UINT __declspec(dllexport) Process_IRC(unsigned long Msg,unsigned long wParam,unsigned long lParam)
{
	
	UINT val=0;

	switch( Msg)
	{
	case KM_SETENTITY:
		// an entity instance is given to you. But it's empty. your job is to create a class or a structure
		// for realtime runnning.
		// You struct/class pointer must be CKEntity->CompilData
		// It's also use to determine if you get an enmpty entity or not.

		if (((CKEntity*)wParam)->CompilData==NULL)
			((CKEntity*)wParam)->CompilData=new CKIrc;

		CurIRC=(CKIrc*)((CKEntity*)wParam)->CompilData;
		CurIRCEntity=(CKEntity*)wParam;
		break;
	case KM_FREEENTITY:
		// free up the memory you allocated for the entity
		if ( ((CKEntity*)wParam)->CompilData!=NULL) delete (CKIrc*)((CKEntity*)wParam)->CompilData;
		break;

	case KM_DRAW:
		// simply draw your entity. don't forget to save the matrix and opengl states
		if (CurIRCEntity->m_Scene->Active==lParam) CurIRC->UpdateIRC();
		CurIRC->Draw(wParam,lParam);
		break;
	case KM_ISCREATING:
		// returns 1 when your are editing the entity (multiple clicks to set its position, size ...)
		// It's here to ask (implicitly) he we can add an entity. If you are editing it (with your mouse move
		// ,mouse clic), Kapsul cannot add a new 1.
		// in this case, we always return 0 meaning that every time you clic, you'll make an entity.
		val=0;
		break;
		/*
	case KM_GETSINGLE:
		// Get a X/Y coordinates and you must return an entity if you have 1 close to it.
		// we seek & project for the current entity
	    GDrawScene=(CKDrawScene*)lParam;
		spt=CurIRCEntity->m_Scene->cSel->Get2D(GDrawScene->GetIsoCoord(LOWORD(wParam),HIWORD(wParam),CurIRCEntity->m_Scene->Active));

        spt2=CurIRCEntity->m_Scene->cSel->Get2D(CurEmit->pos);

        if (Pythagore(spt2.x-spt.x,spt2.y-spt.y)<3)
        {
            val=1;
        }
		else
		{
			val=0;
		}

		break;
	case KM_SELECTSINGLE:
		// Get a X/Y coordinates and you must return an entity if you have 1 close to it.
		// we seek & project for the current entity
        val=1;

		if ((bool)wParam) 
		{
			CurIRCEntity->m_Scene->AddBufVert(&CurEmit->pos,CurIRCEntity,0); 
		}

		CurEmit->pos.Selected=(bool)wParam;
		CurEmit->Selected=(bool)wParam;
		CurIRCEntity->Selected=(bool)wParam;
		break;

	case KM_UNSELECT:
		CurEmit->Selected=false;
		CurIRCEntity->Selected=false;
		break;
	case KM_SELECTION:
		CurSel=(CKSelectionInfos *)wParam;

		// set 3D coords to 2D
		sdeb=CurIRCEntity->m_Scene->cSel->Get2D(CurEmit->pos);

		daAddIt=false;

        // omni
		switch(CurSel->TypeSel)
		{
			case SELECT_SINGLE:
				daAddIt=(Pythagore((sdeb.x-CurSel->spt2.x),(sdeb.y-CurSel->spt2.y))<3);
				break;
			case SELECT_CIRCLE:
				daAddIt=(Pythagore((sdeb.x-CurSel->spt.x),(sdeb.y-CurSel->spt.y))<CurSel->Length);
				break;
			case SELECT_QUAD:
				daAddIt=( (((sdeb.x>=CurSel->spt.x)&&(sdeb.x<=CurSel->spt2.x))||((sdeb.x<=CurSel->spt.x)&&(sdeb.x>=CurSel->spt2.x)))&&
					(((sdeb.y>=CurSel->spt.y)&&(sdeb.y<=CurSel->spt2.y))||((sdeb.y<=CurSel->spt.y)&&(sdeb.y>=CurSel->spt2.y))) );
				break;
			case SELECT_FENCE:
				daAddIt=CurSel->daSh->IsVertInShape(CurEmit->pos,CurSel->View);
				break;
		}
       

		if (CurSel->WholeSelect==SELECT_WHOLE) 
		{
			if (daAddIt)
			{
				if ((!CurEmit->Selected)&&(CurSel->AddIt)) 
					CurIRCEntity->m_Scene->AddBufVert(&CurEmit->pos,CurIRCEntity,0); 
				CurEmit->pos.Selected=CurSel->AddIt;
				CurEmit->Selected=CurSel->AddIt;
				CurIRCEntity->Selected=CurSel->AddIt;

			}
		}
		else
		{
			if (daAddIt)
			{
				if ((!CurEmit->Selected)&&(CurSel->AddIt)) 
					CurIRCEntity->m_Scene->AddBufVert(&CurEmit->pos,CurIRCEntity,0); 
				CurEmit->pos.Selected=CurSel->AddIt;
				CurEmit->Selected=CurSel->AddIt;
				CurIRCEntity->Selected=CurSel->AddIt;

			}
			
		}
		break;
		*/
	case KM_GETMINMAX:
		// Send Min/Max : 1 vertex so , only 1 min/max :)
		m_MinMax.Min=CurIRC->Pos;
		m_MinMax.Max=CurIRC->Pos;

		m_MinMax.Max.vx+=IRC_SCREEN_X*20;
		m_MinMax.Max.vy+=0;
		m_MinMax.Max.vz+=IRC_SCREEN_Y*20;

		//+Vertex(IRC_SCREEN_X*20,IRC_SCREEN_Y*20,0);
		val=(int)&m_MinMax;
		break;
	case KM_LMOUSEDOWN:
		CurIRC->Pos=*((Vertex *)(lParam));
		break;
	case KM_GETXML:
		{
			// Build an XML string based upon class properties 
			// item order has no meaning in an xml tag
			// SET & GET xml messages uses the same xml format
			// and it corresponds to the names in entities.xml
			// it returns a pointer to a CString
			// The color format is 0x00RRGGBB
/*
			CKHashTable *table=(CKHashTable *)wParam;

			table->SetEntry("Name",CurEmit->Name);
			table->SetEntry("PositionX",CurEmit->pos.vx);
			table->SetEntry("PositionY",CurEmit->pos.vy);
			table->SetEntry("PositionZ",CurEmit->pos.vz);
			
			table->SetEntry("Yaw",CurEmit->yaw);
			table->SetEntry("YawVar",CurEmit->yawVar);
			table->SetEntry("Pitch",CurEmit->pitch);
			table->SetEntry("PitchVar",CurEmit->pitchVar);

			table->SetEntry("Speed",CurEmit->speed);
			table->SetEntry("SpeedVar",CurEmit->speedVar);
			table->SetEntry("ForceX",CurEmit->force.vx);
			table->SetEntry("ForceY",CurEmit->force.vy);
			table->SetEntry("ForceZ",CurEmit->force.vz);
			
			table->SetEntry("StartSize",CurEmit->startSize);
			table->SetEntry("StartSizeVar",CurEmit->startSizeVar);
			table->SetEntry("EndSize",CurEmit->endSize);
			table->SetEntry("EndSizeVar",CurEmit->endSizeVar);

			table->SetEntry("StartSwirl",CurEmit->startSwirl);
			table->SetEntry("StartSwirlVar",CurEmit->startSwirlVar);
			table->SetEntry("EndSwirl",CurEmit->endSwirl);
			table->SetEntry("EndSwirlVar",CurEmit->endSwirlVar);

			table->SetEntry("TotalParticles",CurEmit->totalParticles);
			table->SetEntry("EmitsPerFrame",CurEmit->emitsPerFrame);
			table->SetEntry("EmitsVar",CurEmit->emitVar);
			table->SetEntry("Life",CurEmit->life);
			table->SetEntry("LifeVar",CurEmit->lifeVar);

			table->SetEntry("StartColor",(DWORD)(CurEmit->startColor.r*65536+CurEmit->startColor.g*256+CurEmit->startColor.b));
			table->SetEntry("StartColorVar",(DWORD)(CurEmit->startColorVar.r*65536+CurEmit->startColorVar.g*256+CurEmit->startColorVar.b));
			table->SetEntry("EndColor",(DWORD)(CurEmit->endColor.r*65536+CurEmit->endColor.g*256+CurEmit->endColor.b));
			table->SetEntry("EndColorVar",(DWORD)(CurEmit->endColorVar.r*65536+CurEmit->endColorVar.g*256+CurEmit->endColorVar.b));

			table->SetEntry("StartColorAlpha",CurEmit->startColor.a);
			table->SetEntry("StartColorAlphaVar",CurEmit->startColorVar.a);
			table->SetEntry("EndColorAlpha",CurEmit->endColor.a);
			table->SetEntry("EndColorAlphaVar",CurEmit->endColorVar.a);
			*/
		}
		break;
	case KM_SETXML:
		{
			/*
			CKHashTable *table=(CKHashTable *)wParam;
			
			CurEmit->Name=table->GetString("Name");
			
			CurEmit->pos.vx=table->GetFloat("PositionX");
			CurEmit->pos.vy=table->GetFloat("PositionY");
			CurEmit->pos.vz=table->GetFloat("PositionZ");
			
			CurEmit->yaw=table->GetFloat("Yaw");
			CurEmit->yawVar=table->GetFloat("YawVar");
			CurEmit->pitch=table->GetFloat("Pitch");
			CurEmit->pitchVar=table->GetFloat("PitchVar");
			
			CurEmit->speed=table->GetFloat("Speed");
			CurEmit->speedVar=table->GetFloat("SpeedVar");
			CurEmit->force.vx=table->GetFloat("ForceX");
			CurEmit->force.vy=table->GetFloat("ForceY");
			CurEmit->force.vz=table->GetFloat("ForceZ");
			
			CurEmit->startSize=table->GetFloat("StartSize");
			CurEmit->startSizeVar=table->GetFloat("StartSizeVar");
			CurEmit->endSize=table->GetFloat("EndSize");
			CurEmit->endSizeVar=table->GetFloat("EndSizeVar");
			
			CurEmit->startSwirl=table->GetFloat("StartSwirl");
			CurEmit->startSwirlVar=table->GetFloat("StartSwirlVar");
			CurEmit->endSwirl=table->GetFloat("EndSwirl");
			CurEmit->endSwirlVar=table->GetFloat("EndSwirlVar");
			
			CurEmit->totalParticles=table->GetInt("TotalParticles");
			CurEmit->emitsPerFrame=table->GetInt("EmitsPerFrame");
			CurEmit->emitVar=table->GetInt("EmitsVar");
			CurEmit->life=table->GetInt("Life");
			CurEmit->lifeVar=table->GetInt("LifeVar");
			
			CurEmit->startColor.a=table->GetFloat("StartColorAlpha");
			CurEmit->startColorVar.a=table->GetFloat("StartColorAlphaVar");
			CurEmit->endColor.a=table->GetFloat("EndColorAlpha");
			CurEmit->endColorVar.a=table->GetFloat("EndColorAlphaVar");
			
			DWORD tmpcolor=table->GetDWord("StartColor");
			CurEmit->startColor.r=((float)((tmpcolor&0xff0000)>>16));
			CurEmit->startColor.g=((float)((tmpcolor&0xff00)>>8));
			CurEmit->startColor.b=((float)(tmpcolor&0xff));
			
			tmpcolor=table->GetDWord("StartColorVar");
			CurEmit->startColorVar.r=((float)((tmpcolor&0xff0000)>>16));
			CurEmit->startColorVar.g=((float)((tmpcolor&0xff00)>>8));
			CurEmit->startColorVar.b=((float)(tmpcolor&0xff));
			
			tmpcolor=table->GetDWord("EndColor");
			CurEmit->endColor.r=((float)((tmpcolor&0xff0000)>>16));
			CurEmit->endColor.g=((float)((tmpcolor&0xff00)>>8));
			CurEmit->endColor.b=((float)(tmpcolor&0xff));
			
			tmpcolor=table->GetDWord("EndColorVar");
			CurEmit->endColorVar.r=((float)((tmpcolor&0xff0000)>>16));
			CurEmit->endColorVar.g=((float)((tmpcolor&0xff00)>>8));
			CurEmit->endColorVar.b=((float)(tmpcolor&0xff));
			*/
			val=1;
			
		}
		break;
	}

	return val;
}
