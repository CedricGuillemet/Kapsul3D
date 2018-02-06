#include "stdafx.h"
#include "Kapsul3D.h"
#include "Entities\Light.h"
#include "Lightp.h"


CKEntityLight::CKEntityLight()
{
	CreateSeg=0;
}
CKEntityLight::~CKEntityLight()
{
}
	//void UpdateDLLLink(void);

void CKEntityLight::SelectSingle(bool SelectFlag)
{
	if (SelectFlag) 
	{
		if (m_Light.Type==0)
		{
			m_Scene->AddBufVert(&m_Light.Source,this,0); 
		}
		else
		{
			m_Scene->AddBufVert(&m_Light.Source,this,0); 
			m_Scene->AddBufVert(&m_Light.Target,this,0); 
		}
	}

	m_Light.Source.Selected=SelectFlag;
	m_Light.Target.Selected=SelectFlag;
	Selected=SelectFlag;
}
void CKEntityLight::OwnerDraw(int iState,int iWichone)
{
	if (m_Scene!=NULL)
		m_Light.Draw(m_Scene->m_Renderer,*m_Scene->ViewSize,iWichone,iState);
}

void CKEntityLight::Update()
{	
	Min=m_Light.GetMinOf()-Vertex(m_Light.Radius,m_Light.Radius,m_Light.Radius);
	Max=m_Light.GetMaxOf()+Vertex(m_Light.Radius,m_Light.Radius,m_Light.Radius);
}

bool CKEntityLight::GetSingle(int X,int Y,CKRenderer *pRenderer)
{
	Lspt=m_Scene->Get2D(pRenderer->GetIsoCoord(X,Y,m_Scene->Active));

    Lspt2=m_Scene->Get2D(m_Light.Source);

    if (Pythagore(Lspt2.x-Lspt.x,Lspt2.y-Lspt.y)<7)
    {
        return true;
    }
	else
	{
		return false;
	}
}

void CKEntityLight::Select(CKSelectionInfos &SelInfos)
{
	sdeb=m_Scene->Get2D(m_Light.Source);
    sfin=m_Scene->Get2D(m_Light.Target);

	daAddIt1=false;
	daAddIt2=false;

    if (m_Light.Type==0)
    {
        // omni
		switch(SelInfos.TypeSel)
		{
			case SELECT_SINGLE:
				daAddIt1=(Pythagore((sdeb.x-SelInfos.spt2.x),(sdeb.y-SelInfos.spt2.y))<3);
				break;
			case SELECT_CIRCLE:
				daAddIt1=(Pythagore((sdeb.x-SelInfos.spt.x),(sdeb.y-SelInfos.spt.y))<SelInfos.Length);
				break;
			case SELECT_QUAD:
				daAddIt1=( (((sdeb.x>=SelInfos.spt.x)&&(sdeb.x<=SelInfos.spt2.x))||((sdeb.x<=SelInfos.spt.x)&&(sdeb.x>=SelInfos.spt2.x)))&&
					(((sdeb.y>=SelInfos.spt.y)&&(sdeb.y<=SelInfos.spt2.y))||((sdeb.y<=SelInfos.spt.y)&&(sdeb.y>=SelInfos.spt2.y))) );
				break;
			case SELECT_FENCE:
				daAddIt1=SelInfos.daSh->IsVertInShape(m_Light.Source,m_Scene->m_Renderer);
				break;
		}
    }
    else
    {
        // spot
		switch(SelInfos.TypeSel)
		{
			case SELECT_SINGLE:
				if (SelInfos.WholeSelect==SELECT_WHOLE) 
				{
					daAddIt1=(SegDistance(sdeb,sfin,SelInfos.spt2)<3);
					daAddIt2=daAddIt1;
				}
				if (SelInfos.WholeSelect==SELECT_VERTEX) 
				{
					daAddIt1=(Pythagore((sdeb.x-SelInfos.spt2.x),(sdeb.y-SelInfos.spt2.y))<3);
					daAddIt2=(Pythagore((sfin.x-SelInfos.spt2.x),(sfin.y-SelInfos.spt2.y))<3);
				}
				break;
			case SELECT_CIRCLE:
				daAddIt1=(Pythagore((sdeb.x-SelInfos.spt.x),(sdeb.y-SelInfos.spt.y))<SelInfos.Length);
				daAddIt2=(Pythagore((sfin.x-SelInfos.spt.x),(sfin.y-SelInfos.spt.y))<SelInfos.Length);
				break;
			case SELECT_QUAD:
				daAddIt1=( (((sdeb.x>=SelInfos.spt.x)&&(sdeb.x<=SelInfos.spt2.x))||((sdeb.x<=SelInfos.spt.x)&&(sdeb.x>=SelInfos.spt2.x)))&&
					(((sdeb.y>=SelInfos.spt.y)&&(sdeb.y<=SelInfos.spt2.y))||((sdeb.y<=SelInfos.spt.y)&&(sdeb.y>=SelInfos.spt2.y))) );
				daAddIt2=( (((sfin.x>=SelInfos.spt.x)&&(sfin.x<=SelInfos.spt2.x))||((sfin.x<=SelInfos.spt.x)&&(sfin.x>=SelInfos.spt2.x)))&&
					(((sfin.y>=SelInfos.spt.y)&&(sfin.y<=SelInfos.spt2.y))||((sfin.y<=SelInfos.spt.y)&&(sfin.y>=SelInfos.spt2.y))) );
				break;
			case SELECT_FENCE:
				daAddIt1=SelInfos.daSh->IsVertInShape(m_Light.Source,m_Scene->m_Renderer);
				daAddIt2=SelInfos.daSh->IsVertInShape(m_Light.Target,m_Scene->m_Renderer);
				break;
		}
    }

	if (SelInfos.WholeSelect==SELECT_WHOLE) 
	{
		if (m_Light.Type==0)
		{
			if (daAddIt1)
			{
				if ((!m_Light.Source.Selected)&&(SelInfos.AddIt)) 
					m_Scene->AddBufVert(&m_Light.Source,this,0); 
				m_Light.Source.Selected=SelInfos.AddIt;
			}					

			m_Light.Selected=daAddIt1;
			Selected=daAddIt1;

		}
		else
		{
			if (SelInfos.Crossing) daAddIt=daAddIt1 || daAddIt2;
				else daAddIt=daAddIt1 && daAddIt2;

			// Add it if OK!
			if (daAddIt)
			{
				if ((!m_Light.Source.Selected)&&(SelInfos.AddIt)) 
					m_Scene->AddBufVert(&m_Light.Source,this,0); 
				m_Light.Source.Selected=SelInfos.AddIt;

				if ((!m_Light.Target.Selected)&&(SelInfos.AddIt)) 
					m_Scene->AddBufVert(&m_Light.Target,this,0); 
				m_Light.Target.Selected=SelInfos.AddIt;

				m_Light.Selected=SelInfos.AddIt;
				Selected=SelInfos.AddIt;

			}
		}
	}
	else
	{
		if (daAddIt1)
		{
			if ((!m_Light.Source.Selected)&&(SelInfos.AddIt)) 
				m_Scene->AddBufVert(&m_Light.Source,this,0); 
			m_Light.Source.Selected=SelInfos.AddIt;
		}

		if (daAddIt2) 
		{
			if ((!m_Light.Target.Selected)&&(SelInfos.AddIt)) 
				m_Scene->AddBufVert(&m_Light.Target,this,0); 
			m_Light.Target.Selected=SelInfos.AddIt;
		}
	}
}

void CKEntityLight::Unselect()
{
	m_Light.Selected=false;
	Selected=false;
}

bool CKEntityLight::CreatingStatus()
{
	return (CreateSeg!=0);
}

void CKEntityLight::SetProperties()
{
	m_Light.Name=m_Table.GetString("Name");
	
	m_Light.Source.x=m_Table.GetFloat("PositionX");
	m_Light.Source.y=m_Table.GetFloat("PositionY");
	m_Light.Source.z=m_Table.GetFloat("PositionZ");
	DWORD tmpcolor=m_Table.GetDWord("Color");
	m_Light.r=((float)((tmpcolor&0xff0000)>>16));
	m_Light.g=((float)((tmpcolor&0xff00)>>8));
	m_Light.b=((float)(tmpcolor&0xff));

	CString tmptype=m_Table.GetString("Type");
	
	if (tmptype=="Omni")
		m_Light.Type = 0;
	else
		if (tmptype=="Spot")
			m_Light.Type = 1;
		else
			m_Light.Type = 2;
	
	tmptype=m_Table.GetString("SpotType");


	if (tmptype=="Rectangular") 
		m_Light.SpotType = 0;
	else
		m_Light.SpotType = 1;

	m_Light.Target.x=m_Table.GetFloat("TargetX");
	m_Light.Target.y=m_Table.GetFloat("TargetY");
	m_Light.Target.z=m_Table.GetFloat("TargetZ");
	m_Light.Radius=m_Table.GetFloat("Radius");

	DrawViews();
}
void CKEntityLight::GetProperties()
{
	m_Table.SetEntry("Name",m_Light.Name);
	m_Table.SetEntry("PositionX",m_Light.Source.x);
	m_Table.SetEntry("PositionY",m_Light.Source.y);
	m_Table.SetEntry("PositionZ",m_Light.Source.z);
	m_Table.SetEntry("Color",(DWORD)(m_Light.r*65536+m_Light.g*256+m_Light.b));
	
	switch(m_Light.Type)
	{
	case 0:
		m_Table.SetEntry("Type","Omni");
		break;
	case 1:
		m_Table.SetEntry("Type","Spot");
		break;
	case 2:
		m_Table.SetEntry("Type","Neon");
		break;
	}
	
	switch(m_Light.SpotType)
	{
	case 0:
		m_Table.SetEntry("SpotType","Rectangular");
		break;
	case 1:
		m_Table.SetEntry("SpotType","Circular");
		break;
	}
	
	m_Table.SetEntry("TargetX",m_Light.Target.x );
	m_Table.SetEntry("TargetY",m_Light.Target.y );
	m_Table.SetEntry("TargetZ",m_Light.Target.z );
	
	m_Table.SetEntry("Radius",m_Light.Radius);

}

void CKEntityLight::LMouseDown(int X,int Y,Vertex &Pos)
{
	if (CreateSeg==0)
    {
        m_Light.Source=Pos;
        m_Light.Target=Vertex(0,0,0);
		m_Light.Radius=1;
        CreateSeg=1;
    }
	else
	{
		if ((CreateSeg==1)&&(m_Light.Type==0))
		{
			CreateSeg=0;
		}
		else
		{
			if (CreateSeg==2)
			{
				CreateSeg=0;
			}
			else
				CreateSeg=2;
			
		}
	}
}

void CKEntityLight::RMouseDown(int X,int Y,Vertex &Pos)
{
}

void CKEntityLight::LMouseUp(int X,int Y,Vertex &Pos)
{
}

void CKEntityLight::RMouseUp(int X,int Y,Vertex &Pos)
{
	CreateSeg=0;
}

void CKEntityLight::MouseMove(int X,int Y,Vertex &Pos)
{
if (CreateSeg!=0)
    {
		switch (m_Light.Type)
		{
		case 0:
			m_Light.Radius=Pythagore3D(m_Light.Source,(Pos));
			RStatus("Omni light radius : %d",(int)(m_Light.Radius));
			LStatus("Click to end omni light creation.");
			break;
		case 1:
			if (CreateSeg==1)
			{
				m_Light.Target=Pos;
				m_Light.Radius=1;
				LStatus("Click to set spot light target.");
			}
			else
			{
				m_Light.Radius=Pythagore3D(m_Light.Target,(Pos));
				m_Light.Radius/=2;
				RStatus("Spot light radius : %5.2f",m_Light.Radius);
				LStatus("Click to end spot light creation.");
			}
			break;
		case 2:
			if (CreateSeg==1)
			{
				m_Light.Target=Pos;
				m_Light.Radius=1;
				LStatus("Click to set neon light end.");
			}
			else
			{
				m_Light.Radius=Pythagore3D(m_Light.Target,(Pos));
				RStatus("Neon light radius : %5.2",m_Light.Radius);
				LStatus("Click to end neon light creation.");
			}
			break;
		}
		tmpradius=m_Light.Radius;
		DrawViews();
	}
	else
	{
		LStatus("Click to set light source.");
	}
}
