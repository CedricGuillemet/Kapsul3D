#include "stdafx.h"
#include "Kapsul3D.h"
#include "emitter.h"
#include "Particle.h"


CKEntityParticle::CKEntityParticle()
{
}
CKEntityParticle::~CKEntityParticle()
{
}

void CKEntityParticle::SelectSingle(bool SelectFlag)
{
	if (SelectFlag) 
	{
		m_Scene->AddBufVert(&m_Emit.pos,this,0); 
	}

	m_Emit.pos.Selected=SelectFlag;
	m_Emit.Selected=SelectFlag;
	Selected=SelectFlag;
}
void CKEntityParticle::OwnerDraw(int iState,int iWichone)
{
	if (m_Scene!=NULL)
	{
		if (m_Scene->Active==iWichone) m_Emit.UpdateEmitter();
		m_Emit.Draw(m_Scene->m_Renderer,iState,iWichone);
	}
}

void CKEntityParticle::Update()
{
	Min=m_Emit.pos;
	Max=m_Emit.pos;
}
bool CKEntityParticle::GetSingle(int X,int Y,CKRenderer *pRenderer)
{
	
	spt=m_Scene->Get2D(m_Scene->m_Renderer->GetIsoCoord(X,Y,m_Scene->Active));

    spt2=m_Scene->Get2D(m_Emit.pos);

    if (Pythagore(spt2.x-spt.x,spt2.y-spt.y)<3)
    {
        return true;
    }
	else
	{
		return false;
	}

}

void CKEntityParticle::Select(CKSelectionInfos &SelInfos)
{
	// set 3D coords to 2D
	sdeb=m_Scene->Get2D(m_Emit.pos);

	daAddIt=false;

    // omni
	switch(SelInfos.TypeSel)
	{
		case SELECT_SINGLE:
			daAddIt=(Pythagore((sdeb.x-SelInfos.spt2.x),(sdeb.y-SelInfos.spt2.y))<3);
			break;
		case SELECT_CIRCLE:
			daAddIt=(Pythagore((sdeb.x-SelInfos.spt.x),(sdeb.y-SelInfos.spt.y))<SelInfos.Length);
			break;
		case SELECT_QUAD:
			daAddIt=( (((sdeb.x>=SelInfos.spt.x)&&(sdeb.x<=SelInfos.spt2.x))||((sdeb.x<=SelInfos.spt.x)&&(sdeb.x>=SelInfos.spt2.x)))&&
				(((sdeb.y>=SelInfos.spt.y)&&(sdeb.y<=SelInfos.spt2.y))||((sdeb.y<=SelInfos.spt.y)&&(sdeb.y>=SelInfos.spt2.y))) );
			break;
		case SELECT_FENCE:
			daAddIt=SelInfos.daSh->IsVertInShape(m_Emit.pos,m_Scene->m_Renderer);
			break;
	}
   

	if (SelInfos.WholeSelect==SELECT_WHOLE) 
	{
		if (daAddIt)
		{
			if ((!m_Emit.Selected)&&(SelInfos.AddIt)) 
				m_Scene->AddBufVert(&m_Emit.pos,this,0); 
			m_Emit.pos.Selected=SelInfos.AddIt;
			m_Emit.Selected=SelInfos.AddIt;
			Selected=SelInfos.AddIt;
		}
	}
	else
	{
		if (daAddIt)
		{
			if ((!m_Emit.Selected)&&(SelInfos.AddIt)) 
				m_Scene->AddBufVert(&m_Emit.pos,this,0); 
			m_Emit.pos.Selected=SelInfos.AddIt;
			m_Emit.Selected=SelInfos.AddIt;
			Selected=SelInfos.AddIt;
		}
	}
}

void CKEntityParticle::Unselect()
{
	m_Emit.Selected=false;
	Selected=false;
}

bool CKEntityParticle::CreatingStatus()
{
	return false;
}

void CKEntityParticle::SetProperties()
{
	m_Emit.Name=m_Table.GetString("Name");
	
	m_Emit.pos.x=m_Table.GetFloat("PositionX");
	m_Emit.pos.y=m_Table.GetFloat("PositionY");
	m_Emit.pos.z=m_Table.GetFloat("PositionZ");
	
	m_Emit.yaw=m_Table.GetFloat("Yaw");
	m_Emit.yawVar=m_Table.GetFloat("YawVar");
	m_Emit.pitch=m_Table.GetFloat("Pitch");
	m_Emit.pitchVar=m_Table.GetFloat("PitchVar");
	
	m_Emit.speed=m_Table.GetFloat("Speed");
	m_Emit.speedVar=m_Table.GetFloat("SpeedVar");
	m_Emit.force.x=m_Table.GetFloat("ForceX");
	m_Emit.force.y=m_Table.GetFloat("ForceY");
	m_Emit.force.z=m_Table.GetFloat("ForceZ");
	
	m_Emit.startSize=m_Table.GetFloat("StartSize");
	m_Emit.startSizeVar=m_Table.GetFloat("StartSizeVar");
	m_Emit.endSize=m_Table.GetFloat("EndSize");
	m_Emit.endSizeVar=m_Table.GetFloat("EndSizeVar");
	
	m_Emit.startSwirl=m_Table.GetFloat("StartSwirl");
	m_Emit.startSwirlVar=m_Table.GetFloat("StartSwirlVar");
	m_Emit.endSwirl=m_Table.GetFloat("EndSwirl");
	m_Emit.endSwirlVar=m_Table.GetFloat("EndSwirlVar");
	
	m_Emit.totalParticles=m_Table.GetInt("TotalParticles");
	m_Emit.emitsPerFrame=m_Table.GetInt("EmitsPerFrame");
	m_Emit.emitVar=m_Table.GetInt("EmitsVar");
	m_Emit.life=m_Table.GetInt("Life");
	m_Emit.lifeVar=m_Table.GetInt("LifeVar");
	
	m_Emit.startColor.a=m_Table.GetFloat("StartColorAlpha");
	m_Emit.startColorVar.a=m_Table.GetFloat("StartColorAlphaVar");
	m_Emit.endColor.a=m_Table.GetFloat("EndColorAlpha");
	m_Emit.endColorVar.a=m_Table.GetFloat("EndColorAlphaVar");
	
	DWORD tmpcolor=m_Table.GetDWord("StartColor");
	m_Emit.startColor.r=((float)((tmpcolor&0xff0000)>>16));
	m_Emit.startColor.g=((float)((tmpcolor&0xff00)>>8));
	m_Emit.startColor.b=((float)(tmpcolor&0xff));
	
	tmpcolor=m_Table.GetDWord("StartColorVar");
	m_Emit.startColorVar.r=((float)((tmpcolor&0xff0000)>>16));
	m_Emit.startColorVar.g=((float)((tmpcolor&0xff00)>>8));
	m_Emit.startColorVar.b=((float)(tmpcolor&0xff));
	
	tmpcolor=m_Table.GetDWord("EndColor");
	m_Emit.endColor.r=((float)((tmpcolor&0xff0000)>>16));
	m_Emit.endColor.g=((float)((tmpcolor&0xff00)>>8));
	m_Emit.endColor.b=((float)(tmpcolor&0xff));
	
	tmpcolor=m_Table.GetDWord("EndColorVar");
	m_Emit.endColorVar.r=((float)((tmpcolor&0xff0000)>>16));
	m_Emit.endColorVar.g=((float)((tmpcolor&0xff00)>>8));
	m_Emit.endColorVar.b=((float)(tmpcolor&0xff));
}

void CKEntityParticle::GetProperties()
{

	m_Table.SetEntry("Name",m_Emit.Name);
	m_Table.SetEntry("PositionX",m_Emit.pos.x);
	m_Table.SetEntry("PositionY",m_Emit.pos.y);
	m_Table.SetEntry("PositionZ",m_Emit.pos.z);
	
	m_Table.SetEntry("Yaw",m_Emit.yaw);
	m_Table.SetEntry("YawVar",m_Emit.yawVar);
	m_Table.SetEntry("Pitch",m_Emit.pitch);
	m_Table.SetEntry("PitchVar",m_Emit.pitchVar);

	m_Table.SetEntry("Speed",m_Emit.speed);
	m_Table.SetEntry("SpeedVar",m_Emit.speedVar);
	m_Table.SetEntry("ForceX",m_Emit.force.x);
	m_Table.SetEntry("ForceY",m_Emit.force.y);
	m_Table.SetEntry("ForceZ",m_Emit.force.z);
	
	m_Table.SetEntry("StartSize",m_Emit.startSize);
	m_Table.SetEntry("StartSizeVar",m_Emit.startSizeVar);
	m_Table.SetEntry("EndSize",m_Emit.endSize);
	m_Table.SetEntry("EndSizeVar",m_Emit.endSizeVar);

	m_Table.SetEntry("StartSwirl",m_Emit.startSwirl);
	m_Table.SetEntry("StartSwirlVar",m_Emit.startSwirlVar);
	m_Table.SetEntry("EndSwirl",m_Emit.endSwirl);
	m_Table.SetEntry("EndSwirlVar",m_Emit.endSwirlVar);

	m_Table.SetEntry("TotalParticles",m_Emit.totalParticles);
	m_Table.SetEntry("EmitsPerFrame",m_Emit.emitsPerFrame);
	m_Table.SetEntry("EmitsVar",m_Emit.emitVar);
	m_Table.SetEntry("Life",m_Emit.life);
	m_Table.SetEntry("LifeVar",m_Emit.lifeVar);

	m_Table.SetEntry("StartColor",(DWORD)(m_Emit.startColor.r*65536+m_Emit.startColor.g*256+m_Emit.startColor.b));
	m_Table.SetEntry("StartColorVar",(DWORD)(m_Emit.startColorVar.r*65536+m_Emit.startColorVar.g*256+m_Emit.startColorVar.b));
	m_Table.SetEntry("EndColor",(DWORD)(m_Emit.endColor.r*65536+m_Emit.endColor.g*256+m_Emit.endColor.b));
	m_Table.SetEntry("EndColorVar",(DWORD)(m_Emit.endColorVar.r*65536+m_Emit.endColorVar.g*256+m_Emit.endColorVar.b));

	m_Table.SetEntry("StartColorAlpha",m_Emit.startColor.a);
	m_Table.SetEntry("StartColorAlphaVar",m_Emit.startColorVar.a);
	m_Table.SetEntry("EndColorAlpha",m_Emit.endColor.a);
	m_Table.SetEntry("EndColorAlphaVar",m_Emit.endColorVar.a);
}

void CKEntityParticle::LMouseDown(int X,int Y,Vertex &Pos)
{
	m_Emit.pos=Pos;
}

void CKEntityParticle::RMouseDown(int X,int Y,Vertex &Pos)
{
}

void CKEntityParticle::LMouseUp(int X,int Y,Vertex &Pos)
{
}

void CKEntityParticle::RMouseUp(int X,int Y,Vertex &Pos)
{
}

void CKEntityParticle::MouseMove(int X,int Y,Vertex &Pos)
{
}

