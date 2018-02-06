//*****************************************************************
// Some struct and macro to speed up developement
//*****************************************************************
#include <windows.h>
#include <stdio.h>

#if !defined(_MYTYPES_INCLUDED_)
#define _MYTYPES_INCLUDED_

//-----------------------------------------------------------------
// A very simple list structure
//-----------------------------------------------------------------
struct min_plist
{
	//data
	UINT	*list;
	min_plist	*next;
	min_plist	*prev;
};

//=================================================================
// 3D specific definition
//=================================================================

//-----------------------------------------------------------------
// Standard vertex format using float
//-----------------------------------------------------------------

struct o_vert3f
{
	//data
	float x,y,z;	//Vertex coordinates

	//Some useful operator
	o_vert3f& operator == (o_vert3f &v) {x=v.x;y=v.y;z=v.z;return *this;}
	o_vert3f& operator = (float f) {x=y=z=f;return *this;}
	o_vert3f& operator += (o_vert3f &v) {x+=v.x;y+=v.y;z+=v.z;return *this;}
	o_vert3f& operator -= (o_vert3f &v) {x-=v.x;y-=v.y;z-=v.z;return *this;}
	o_vert3f& operator *= (o_vert3f &v) {x*=v.x;y*=v.y;z*=v.z;return *this;}
	o_vert3f& operator /= (o_vert3f &v) {x/=v.x;y/=v.y;z/=v.z;return *this;}
};

//-----------------------------------------------------------------
// Polygone structure
//-----------------------------------------------------------------
#define MAX_NUMBER_OF_VERTEX_PER_POLY	1023	//1023 - 200 seems to be a good value

struct o_poly
{
	//data
	int NumofVertex;
	int verts[MAX_NUMBER_OF_VERTEX_PER_POLY];
	int Surface;
	o_vert3f norm;
};

//-----------------------------------------------------------------
// Triangle structure
//-----------------------------------------------------------------

/*struct o_triangle
{
	//data
	int verts[3];
	o_vert3f norm;
};*/

//-----------------------------------------------------------------
// UV mapping list storage structure
//-----------------------------------------------------------------
struct o_uvmap
{
	//data
	char	*name;
	float	*u,*v;
	UINT	*index;
	o_uvmap	*prev,*next;
};

//-----------------------------------------------------------------
// W mapping list storage structure
//-----------------------------------------------------------------
struct o_wmap
{
	//data
	char	*name;
	float	*w;
	UINT	*index;
	o_wmap	*prev,*next;
};

//-----------------------------------------------------------------
// Mesh list storage structure
//-----------------------------------------------------------------
struct o_mesh
{
	//data
    o_vert3f*	verts;
	o_vert3f*	norms;
    o_poly*		polys;
//	o_triangle*	triangles;
    int numverts;
    int numpolys;
	o_mesh *next;
	o_mesh *prev;
};

//-----------------------------------------------------------------
// Surface list storage structure
//-----------------------------------------------------------------
struct o_surf
{
	//data
	char *name;
	float dr,dg,db,da;
	o_surf	*next;
	o_surf	*prev;
};

//-----------------------------------------------------------------
// Typical LWO storage structure
//-----------------------------------------------------------------
struct t_3Dobject
{
	//data
	o_mesh*		meshes;
	o_uvmap*	uvmap;
	o_wmap*		wmap;
	min_plist*	plist;
	o_surf*		surf;
    int numverts;
    int numpolys;
	int nummeshes;
	int numuvmaps;
	int numwmaps;
	int numplists;
	int numsurfs;

	//Some useful operator
	void Delete()
	{
		int j=0;

		//Delete Mesh Layers
		o_mesh *tm = meshes;
		if (tm)
		for (j=0; j<nummeshes; j++)
		{
			if (tm->norms) delete (tm->norms);
			delete (tm->verts);
			//Delete the array of polygons
//			delete (tm->triangles);
			delete (tm->polys);
			if (!tm->next) break;
			tm = tm->next;
			delete (tm->prev);
		}
		delete (tm);

		//Delete UVMAPs
		o_uvmap *tuv = uvmap;
		if (tuv)
		for (j=0; j<numuvmaps; j++)
		{
			delete (tuv->name);
			delete (tuv->u);
			delete (tuv->v);
			delete (tuv->index);
			if (!tuv->next) break;
			tuv = tuv->next;
			delete (tuv->prev);
		}
		delete (tuv);

		//Delete WMAPs
		o_wmap *tw = wmap;
		if (tw)
		for (j=0; j<numwmaps; j++)
		{
			delete (tw->name);
			delete (tw->w);
			delete (tw->index);
			if (!tw->next) break;
			tw = tw->next;
			delete (tw->prev);
		}
		delete (tw);
		//delete (wmap);

		//Delete PLISTs
		min_plist *tpl = plist;
		if (tpl)
		for (j=0; j<numplists; j++)
		{
			delete (tpl->list);
			if (!tpl->next) break;
			tpl = tpl->next;
			delete (tpl->prev);
		}
		delete (tpl);

		//Delete PLISTs
		o_surf *ts = surf;
		if (ts)
		for (j=0; j<numsurfs; j++)
		{
			delete (ts->name);
			if (!ts->next) break;
			ts = ts->next;
			delete (ts->prev);
		}
		delete (ts);

	}
};

//=================================================================
// Macro and function definition
//=================================================================

//invert 4 bytes and returns a long
#define	invert4bytes( src , res )\
{\
char *pres,*psrc;\
pres = res;\
psrc = src;\
BYTE x=3,y=0;\
while (y!=4) pres[y++] = psrc[x--];\
}

/*#define	invert4bytes( src , res )\
{\
byte *pres,*psrc;\
pres = res;\
psrc = src;\
BYTE x=3,y=0;\
while (y!=4) pres[y++] = psrc[x--];\
}*/

#define ReadINTEGERfromBuffer(Entier,Buffer)\
{\
Entier = (int)Buffer[1] + (int)(Buffer[0]<<8);\
Buffer += 2;\
}

#endif // !defined(_MYTYPES_INCLUDED_)
