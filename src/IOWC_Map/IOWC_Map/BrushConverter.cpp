// BrushConverter.cpp: implementation of the CBrushConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BrushConverter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBrushConverter::CBrushConverter()
{
	m_nProcessedBrushes  = 0;
	m_nProcessedEntities = 0;
	m_nLoadedBrushes	 = 0; 
}

CBrushConverter::~CBrushConverter()
{

}


SWINDING *CBrushConverter::Winding_Alloc(int iNumPoints)
{
 SWINDING	*w;
 int		size;
	
 if(iNumPoints > 64)
	TRACE("Winding_Alloc has too many points! (%i points)", iNumPoints);
	
 size = sizeof(SWINDING);//(int)sizeof(((SWINDING *)0)->points[iNumPoints]);
 w = new SWINDING;
 memset(w,0,size);
 w->iMaxPoints = iNumPoints;
 w->points = new CV3[iNumPoints];	

 return w;
}

void CBrushConverter::Winding_Free(SWINDING * w)
{
 if(!w)
	 return;

 if(w->points)
 {
	 delete [] w->points;
   w->points = NULL;
 }

 delete w;
}

SWINDING *CBrushConverter::Winding_GetFacePlane(SFACE *sFace)
{
 int		x;
 float		max, v;
 CV3 		vOrigin, vRight, vUp;
 SWINDING	*w;

 vUp.x = vUp.y = vUp.z = 0.0f;

 // find the major axis
 max = -18000;
 x = -1;

 v = (float)fabs(sFace->sFacePlane.vNormal.x);
 if (v > max)
 {
		x = 0;
		max = v;
 }

 v = (float)fabs(sFace->sFacePlane.vNormal.y);
 if (v > max)
 {
		x = 1;
		max = v;
 }

 v = (float)fabs(sFace->sFacePlane.vNormal.z);
 if (v > max)
 {
		x = 2;
		max = v;
 }
 if(x==-1)
	MessageBox(NULL,"Winding_GetFacePlane: Error finding major axis",NULL,MB_OK);
		
 switch (x)
 {
	case 0:
	case 1:
		vUp.z = 1;
		break;		
	case 2:
		vUp.x = 1;
		break;		
 }


 v = vUp.Dot(sFace->sFacePlane.vNormal);

 vUp.x = vUp.x - v * sFace->sFacePlane.vNormal.x;
 vUp.y = vUp.y - v * sFace->sFacePlane.vNormal.y;
 vUp.z = vUp.z - v * sFace->sFacePlane.vNormal.z;

 vUp.Normalize();
		
 vOrigin.Scale(sFace->sFacePlane.vNormal,sFace->sFacePlane.fDist);	
 
 vRight = vUp;
 vRight = vRight.Cross(sFace->sFacePlane.vNormal);

 vUp.Scale(vUp,18000.0f);

 vRight.Scale(vRight,18000.0f);

 w = Winding_Alloc(4);
 if(!w)
	 return NULL;
	
 w->points[0] = vOrigin - vRight; 
 w->points[0] = vUp + w->points[0];	

 w->points[1] = vOrigin + vRight;
 w->points[1] = w->points[1] + vUp;	

 w->points[2] = vOrigin + vRight;
 w->points[2] = w->points[2] - vUp;	

 w->points[3] = vOrigin - vRight;
 w->points[3] = w->points[3] - vUp;
	
 w->iNumPoints = 4;
	
 return w;	
}

SWINDING *CBrushConverter::Winding_Clip(SWINDING *in, SPLANE *split, BOOL keepon)
{
	float	dists[64],dot;
	int		sides[64];
	int		counts[3];
	int		i;
	CV3		mid,p1,p2;
	SWINDING	*neww;
	int		maxpts;
	
	counts[0] = counts[1] = counts[2] = 0;

	// determine sides for each point
	for (i = 0 ;i < in->iNumPoints; i++)
	{
		dot = split->vNormal.Dot(in->points[i]);
		dot -= split->fDist;
		dists[i] = dot;
		if (dot > 0.01)
			sides[i] = SIDE_FRONT;
		else if (dot < -0.01)
			sides[i] = SIDE_BACK;
		else
		{
			sides[i] = SIDE_ON;
		}
		counts[sides[i]]++;
	}
	sides[i] = sides[0];
	dists[i] = dists[0];
	
	if (keepon && !counts[0] && !counts[1])
		return in;
		
	if (!counts[0])
	{
		Winding_Free (in);
		return NULL;
	}

	if (!counts[1])
		return in;
	
	maxpts = in->iNumPoints+4;
	neww = Winding_Alloc (maxpts);
		
	for (i=0 ; i < in->iNumPoints ; i++)
	{
		p1 = in->points[i];		
		if(sides[i] == SIDE_ON)
		{
			neww->points[neww->iNumPoints] = p1;
			neww->iNumPoints++;
			continue;
		}
	
		if(sides[i] == SIDE_FRONT)
		{
			neww->points[neww->iNumPoints] = p1;
			neww->iNumPoints++;
		}
		
		if(sides[i+1] == SIDE_ON || sides[i+1] == sides[i])
			continue;
			
		// generate a split point
		p2 = in->points[(i+1)%in->iNumPoints];		
		dot = dists[i] / (dists[i]-dists[i+1]);

	  if(split->vNormal.x == 1)
			mid.x = split->fDist;
	  else if(split->vNormal.x == -1)
			mid.x = -split->fDist;
	  else
			mid.x = p1.x + dot*(p2.x-p1.x);

	  if(split->vNormal.y == 1)
			mid.y = split->fDist;
	  else if(split->vNormal.y == -1)
			mid.y = -split->fDist;
	  else
			mid.y = p1.y + dot*(p2.y-p1.y);

	  if(split->vNormal.z == 1)
			mid.z = split->fDist;
	  else if(split->vNormal.z == -1)
			mid.z = -split->fDist;
	  else
			mid.z = p1.z + dot*(p2.z-p1.z);
		
		neww->points[neww->iNumPoints] = mid;
		neww->iNumPoints++;
	}
	
	if (neww->iNumPoints > maxpts)
		MessageBox(NULL,"Too many points resulted from clipping operation.","iowc_map.dll",MB_OK);
		
	// free the original winding
	Winding_Free(in);
	
	return neww;
}

SWINDING *CBrushConverter::Face_MakeWinding(SFACE *sFace,CBrushRaw *Brush)
{
 SFACE		*clip;
 SPLANE		plane;
 BOOL		bPast = FALSE; 	

 SWINDING *w = Winding_GetFacePlane(sFace);

 clip = Brush->s_Faces;
 for(int i = 0;clip && w && i < Brush->m_nFaces;i++,clip = &Brush->s_Faces[i])
 {
	 if(clip == sFace)
	 {
		bPast = TRUE;
		continue;
	 }

	 if(sFace->sFacePlane.vNormal.Dot(clip->sFacePlane.vNormal) > 0.999 &&
		  fabs(sFace->sFacePlane.fDist - clip->sFacePlane.fDist) < 0.01)
	 {
		// Identical planes
		if(bPast)
		{
			free(w);
			return NULL;
		}
		continue;
	 }

	 CV3 vOrigin;
	 vOrigin.Set(0,0,0);

	 plane.vNormal = vOrigin - clip->sFacePlane.vNormal;
	 plane.fDist = -clip->sFacePlane.fDist;

	 w = Winding_Clip(w,&plane,FALSE);
	 if(!w)
		 return w;
 }

 if(w->iNumPoints < 3)
 {
	delete w;
	w = NULL;
 }

 if(!w)
	 MessageBox(NULL,"Face_MakeWinding clipping error","iowc_map.dll",MB_OK);

 return w;
}

void CBrushConverter::Brush_BuildWinding(CBrushRaw * Brush)
{
 SWINDING *w = NULL;
 float	v;
 int	j = 0,i = 0;

 // We reset mins\maxs
 Brush->m_Mins.x = Brush->m_Mins.y = Brush->m_Mins.z = 18000;
 Brush->m_Maxs.x = Brush->m_Maxs.y = Brush->m_Maxs.z = -18000;

 // We compute plane pts
 for(i; i < Brush->m_nFaces; i ++)
	 Face_BuildPlane(&Brush->s_Faces[i]);

 // We compute windings
 for(i = 0; i < Brush->m_nFaces; i ++)
 {
	 Winding_Free(Brush->s_Faces[i].sFaceWinding); 
	 w = Brush->s_Faces[i].sFaceWinding = Face_MakeWinding(&Brush->s_Faces[i],Brush);
	 if(!w)
		 continue;

	 // We compute real bbox
	 for(int k = 0 ;k < w->iNumPoints; k++)
	 {	
		v = w->points[k].x;
		if(v > Brush->m_Maxs.x)
			Brush->m_Maxs.x = v;

		if(v < Brush->m_Mins.x)
			Brush->m_Mins.x = v;

		v = w->points[k].y;
		if(v > Brush->m_Maxs.y)
			Brush->m_Maxs.y = v;

		if(v < Brush->m_Mins.y)
			Brush->m_Mins.y = v;

		v = w->points[k].z;
		if(v > Brush->m_Maxs.z)
			Brush->m_Maxs.z = v;

		if(v < Brush->m_Mins.z)
			Brush->m_Mins.z = v;
	 }
 }

 m_nProcessedBrushes++;
}

void CBrushConverter::Face_BuildPlane(SFACE *sFace)
{
 int  j = 0;
 CV3	v1, v2, v3;

 v1.x = sFace->vPlanePts[0].x - sFace->vPlanePts[1].x;
 v2.x = sFace->vPlanePts[2].x - sFace->vPlanePts[1].x;
 v3.x = sFace->vPlanePts[1].x;
	
 v1.y = sFace->vPlanePts[0].y - sFace->vPlanePts[1].y;
 v2.y = sFace->vPlanePts[2].y - sFace->vPlanePts[1].y;
 v3.y = sFace->vPlanePts[1].y;

 v1.z = sFace->vPlanePts[0].z - sFace->vPlanePts[1].z;
 v2.z = sFace->vPlanePts[2].z - sFace->vPlanePts[1].z;
 v3.z = sFace->vPlanePts[1].z;

 sFace->sFacePlane.vNormal = v1.Cross(v2);
 sFace->sFacePlane.vNormal.Normalize();
 sFace->sFacePlane.fDist = v3.Dot(sFace->sFacePlane.vNormal);
}

bool CBrushConverter::Desk_Import(Desk *dadk,CBrushRaw *pBrush)
{
 if(!pBrush->s_Faces)
 {
  MessageBox(NULL,"Bad Object or Invalid Data","iowc_map.dll",MB_OK);
  return FALSE;
 }

 int k,i;
 dadk->AddObject();

 int nb2verts=0;

 for(k = 0; k < pBrush->m_nFaces; k++)
 {
  nb2verts += pBrush->s_Faces[k].sFaceWinding->iNumPoints;
 }

 int VertAv=0,PlAv=0;

 dadk->NextObject->AllocatePoly(pBrush->m_nFaces,nb2verts); 
 //dadk->NextObject->AllocateUV(pBrush->m_nFaces,nb2verts);

 for(k = 0; k < pBrush->m_nFaces; k++)
 {
  // set number of vertex used in the poly
  dadk->NextObject->pl[k].Allocate(1,pBrush->s_Faces[k].sFaceWinding->iNumPoints); 

  //dadk->NextObject->pl[PlAv].Tex[0][0] = 

  for(i = 0 ;i < pBrush->s_Faces[k].sFaceWinding->iNumPoints; i++)
  {
   dadk->NextObject->pv[VertAv].vx = pBrush->s_Faces[k].sFaceWinding->points[i].x;
   dadk->NextObject->pv[VertAv].vy = pBrush->s_Faces[k].sFaceWinding->points[i].y;
   dadk->NextObject->pv[VertAv].vz = pBrush->s_Faces[k].sFaceWinding->points[i].z;

   dadk->NextObject->pl[PlAv].nbvert[(pBrush->s_Faces[k].sFaceWinding->iNumPoints-1)-i] = VertAv;    // need to index vertex to polygons
   
   VertAv++;
  }

  PlAv++;
  //UVAv += pBrush->s_Faces[k].sFaceWinding->iNumPoints;
 }

 delete pBrush;
 pBrush = NULL;

 return TRUE;
}

bool CBrushConverter::ApplyTexture(SFACE *sFace)
{
 return TRUE;
}