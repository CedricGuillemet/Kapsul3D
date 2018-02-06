//********************************************************************************
//
// module Name: 3DObjectStuff.cpp
//
// Description: Some useful fonction that allow us to transform a Kapsul scene
// into our 3D object
//
//Creation: March 06th 2003 by GROUMF
//
//
//********************************************************************************

#include "stdafx.h"
#include <Kapsul3D.h>
#include "3DObjectStuff.h"

#include "stdafx.h"
#include <Kapsul3D.h>
#include "3DObjectStuff.h"

//====================================================================
// Transform our 3D object into a Kapsul scene object
//
// Input:
//	t_3Dobject *The3DObject - The object to transform
//	CKScene *TheKapsulScene - The scene to send back to the Kapsul editor
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool Compute3DObject_to_KapsulScene(t_3Dobject *The3DObject,CKScene *TheKapsulScene)
{
bool ReturnValue = true;
int i=0,j=0,k=0;

	if (TheKapsulScene != NULL)	//Is there a valid Kapsul scene ?
		{
		// -- Meshs --------------------------------------------------------------
		CKMesh *pCKMesh;
		o_mesh *pOMesh = The3DObject->meshes;


		for (k=0;k<The3DObject->nummeshes;k++)
			{
			//Create a new mesh and initialize it
			pCKMesh=TheKapsulScene->AddMesh();
			//pCKMesh=TheKapsulScene->NextMesh;

			// Allocate and fill vertex buffer 
			pCKMesh->AllocatePoly(0,pOMesh->numverts);

			for (i=0;i<pOMesh->numverts;i++)
				{
				pCKMesh->pv[i].x = pOMesh->verts[i].x;
				pCKMesh->pv[i].y = pOMesh->verts[i].y;
				pCKMesh->pv[i].z = pOMesh->verts[i].z;
				}

			// Allocate polygons buffer
			pCKMesh->AllocatePoly(pOMesh->numpolys,0);

			o_poly *pOPolys = pOMesh->polys;	//Temporary pointer for actual 3DObject polygon

			for (i=0;i<pOMesh->numpolys;i++)
				{
				//Allocate and fill the polygon number i in the Kapsul scene
				if (pOPolys->NumofVertex<3 )	//Triangle is the first primitive we are handling in Kapsul editor
				{
					pCKMesh->pl[i].Allocate(pCKMesh,pCKMesh->nbTexCanals,3);	
					if (pOPolys->NumofVertex==1)
					{
						pCKMesh->pl[i].nbvert[0] = pOPolys->verts[0];
						pCKMesh->pl[i].Tex[0][0] = 0;
						pCKMesh->pl[i].nbvert[1] = pOPolys->verts[0];
						pCKMesh->pl[i].Tex[0][1] = 0;
						pCKMesh->pl[i].nbvert[2] = pOPolys->verts[0];
						pCKMesh->pl[i].Tex[0][2] = 0;
					}
					else
					{
						pCKMesh->pl[i].nbvert[0] = pOPolys->verts[0];
						pCKMesh->pl[i].Tex[0][0] = 0;
						pCKMesh->pl[i].nbvert[1] = pOPolys->verts[1];
						pCKMesh->pl[i].Tex[0][1] = 0;
						pCKMesh->pl[i].nbvert[2] = pOPolys->verts[0];
						pCKMesh->pl[i].Tex[0][2] = 0;
					}
				}
				else
				{
				pCKMesh->pl[i].Allocate(pCKMesh,pCKMesh->nbTexCanals,pOPolys->NumofVertex);

				for (j=0;j<pCKMesh->pl[i].nb2vert;j++)	//Looping on the number of vertex for this polygon
					{
					switch(pCKMesh->nbTexCanals)	//Depending on the number of texture coordinates channels
						{
						case 1:
							//Vertex array
							pCKMesh->pl[i].nbvert[j] = pOPolys->verts[j];
							//Texture coordinates
							pCKMesh->pl[i].Tex[0][j] = 0;
						break;

						case 2:
							//Vertex array
							pCKMesh->pl[i].nbvert[j] = pOPolys->verts[j];
							//Texture coordinates
							pCKMesh->pl[i].Tex[0][j] = 0;
							pCKMesh->pl[i].Tex[1][j] = 0;
						break;
					
						case 3:
							//Vertex array
							pCKMesh->pl[i].nbvert[j] = pOPolys->verts[j];
							//Texture coordinates
							pCKMesh->pl[i].Tex[0][j] = 0;
							pCKMesh->pl[i].Tex[1][j] = 0;
							pCKMesh->pl[i].Tex[2][j] = 0;
						break;
					
						case 4:
							//Vertex array
							pCKMesh->pl[i].nbvert[j] = pOPolys->verts[j];
							//Texture coordinates
							pCKMesh->pl[i].Tex[0][j] = 0;
							pCKMesh->pl[i].Tex[1][j] = 0;
							pCKMesh->pl[i].Tex[2][j] = 0;
							pCKMesh->pl[i].Tex[3][j] = 0;
						break;
						}
					}
				}
				pOPolys++;	//Next 3DObject polygon
				}
			pCKMesh->UpdateMesh();	//Update mesh
			pOMesh = pOMesh->next;	//Next 3DObject Mesh
			}
		// -- End - Meshs --------------------------------------------------------
		}

return ReturnValue;
}

//====================================================================
// Transform a Kapsul scene int o a 3D object
//
// Input:
//	CKScene *TheKapsulScene - The scene to save fromo the Kapsul editor
//	t_3Dobject *The3DObject - The 3D object
//
// Output:
//	bool - true if everything is ok, false otherwise
//
//====================================================================

bool ComputeKapsulScene_to_3DObject(CKScene *TheKapsulScene,t_3Dobject *The3DObject)
{
bool ReturnValue = true;
long i=0,j=0,k=0;
t_3Dobject *Temp3DObject = The3DObject;

	if (TheKapsulScene != NULL)	//Is there a valid Kapsul scene ?
		{
		// -- Meshs --------------------------------------------------------------
		CKMesh *pCKMesh = NULL;

		o_mesh *pOMesh = NULL;
		o_poly *pOPolys=NULL;

		int iObjCount = 0;

		// Looping trought the meshes
		for(pCKMesh = TheKapsulScene->FirstMesh;pCKMesh != NULL;pCKMesh = pCKMesh->Next,iObjCount++)
			{
			//We have a new object, so create a new mesh in our object
			//First Mesh Entry
			if (Temp3DObject->meshes==NULL)
				{
				pOMesh = Temp3DObject->meshes = new o_mesh;
				memset(pOMesh,0,sizeof(o_mesh));
				Temp3DObject->nummeshes++;
				}
			else
				{
				o_mesh *tm=Temp3DObject->meshes;
				while (tm->next) tm=tm->next;
				pOMesh = new o_mesh;
				memset(pOMesh,0,sizeof(o_mesh));
				tm->next = pOMesh;
				tm->next->prev = tm;
				Temp3DObject->nummeshes++;
				}

			//Allocate Vertex buffer and indice buffer
			if (pOMesh->numverts == NULL)
				{
				pOMesh->numverts = pCKMesh->nb2vert;
				pOMesh->verts	= new o_vert3f[pOMesh->numverts];
				}

			//First triangle Entry
			pOPolys=pOMesh->polys;

			if (pOPolys==NULL)
				{
				pOMesh->numpolys = pCKMesh->nb2poly;
				pOPolys = pOMesh->polys = new o_poly[pOMesh->numpolys];
				memset(pOPolys,0,(pOMesh->numpolys)*sizeof(o_poly));
				}

			//Now it's time too fill up our buffers
			//First the vertex buffer
			for (i=0;i<pOMesh->numverts;i++)
				{
				pOMesh->verts[i].x = pCKMesh->pv[i].x;
				pOMesh->verts[i].y = pCKMesh->pv[i].y;
				pOMesh->verts[i].z = pCKMesh->pv[i].z;
				}

			for (i=0;i<pOMesh->numpolys;i++)
				{
				pOPolys[i].NumofVertex = pCKMesh->pl[i].nb2vert;
				for (j=0;j<pCKMesh->pl[i].nb2vert;j++)	//Looping on the number of vertex for this polygon
					{
					//Vertex array
					pOPolys[i].verts[j] = pCKMesh->pl[i].nbvert[j];
					}
				}
			}

		// -- End - Meshs --------------------------------------------------------
		}

return ReturnValue;
}
