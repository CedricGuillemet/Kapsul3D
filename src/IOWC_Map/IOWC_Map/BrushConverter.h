// BrushConverter.h: interface for the CBrushConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRUSHCONVERTER_H__EE970941_2C7C_491E_83AD_CEBD96477888__INCLUDED_)
#define AFX_BRUSHCONVERTER_H__EE970941_2C7C_491E_83AD_CEBD96477888__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Kapsul3D.h"
#include "fmath.h"

// Brush sides
#define	SIDE_CROSS		-2
#define	SIDE_FRONT		0
#define	SIDE_BACK		1
#define	SIDE_ON			2

// Brush property
typedef struct tag_SPROPERTY
{
  tag_SPROPERTY * m_pNext;
  char			* szPropName;
  char			* szPropValue;
} SPROPERTY;

// Structures definitions
typedef struct
{
	int		iMaxPoints;
	int		iNumPoints;
	CV3	*points;
} SWINDING;

//Plane definition
typedef struct{
	CV3	vNormal;
	float	fDist;
}SPLANE;

// A texture definition
typedef struct {
	char	*Name;
	float	Shift[2];
	float	Rotate;
	float	Scale[2];
}STEXTURE;

// A Face (could be composed of more polys)
typedef struct {
	SPLANE	sFacePlane;			// Plane on wich face lays
	CV3		vPlanePts[3];		// points that makes the plane face lays on

	STEXTURE	sFaceTexture;	// Texture definition for this face
	SWINDING	*sFaceWinding;	// Face building informations
}SFACE;

class CBrushConverter  
{
public:
	int		m_nProcessedBrushes;
	int		m_nProcessedEntities;
	int		m_nLoadedBrushes;

	CBrushConverter();
	~CBrushConverter();

	void PrintStatistics()
	{
	 CString szTemp;
	 szTemp.Format("%i brushes loaded and %i of them have been successfully converted! ( %i entities loaded )",
		 m_nLoadedBrushes,m_nProcessedBrushes,m_nProcessedEntities);

	 MessageBox(NULL,szTemp,"iowc_map.dll",MB_OK);
	}

	class CBrushRaw
	{
	public:
		CBrushRaw()
		{ 
			s_Faces  = NULL;
			m_nFaces = 0;
		}

		~CBrushRaw()
		{
			if(s_Faces)
				delete [] s_Faces;

			m_nFaces = 0;
			s_Faces  = NULL;

		}

		SFACE *s_Faces;
		int	  m_nFaces;

		CV3 m_Mins,m_Maxs;
	};

	//Winding Ops
	SWINDING *Winding_Alloc(int iNumPoints);
	void	 Winding_Free(SWINDING * w);
	SWINDING *Winding_GetFacePlane(SFACE *sFace);
	SWINDING *Winding_Clip(SWINDING *in, SPLANE *split, BOOL keepon);
	SWINDING *Face_MakeWinding(SFACE *sFace,CBrushRaw *Brush);
	void	 Brush_BuildWinding(CBrushRaw * Brush);

	//Face Ops
	void	 Face_BuildPlane(SFACE *sFace);

	//Kapsul Desk Integration
	bool	 Desk_Import(Desk *dadk,CBrushRaw *pBrush);
	bool	 ApplyTexture(SFACE *sFace);

};

#endif // !defined(AFX_BRUSHCONVERTER_H__EE970941_2C7C_491E_83AD_CEBD96477888__INCLUDED_)
