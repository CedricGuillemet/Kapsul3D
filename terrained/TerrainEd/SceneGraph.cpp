
#include "stdafx.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "scenegraph.h"
#include "terra.h"
#include "scenegraph.h"

// --------------------------------------
// GLOBALS
// --------------------------------------

//long gStartTime, gEndTime;
//int gNumFrames;
//unsigned char *gHeightMap;
//int gAnimating;
//int gRotating;
//int gStartX, gStartY;


extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

Landscape gLand;

// Texture
GLuint gTextureID=1;

// Camera Stuff
GLfloat gViewPosition[]		= { 0.f, 5.f, 0.f };
GLfloat gCameraPosition[]	= { 0.f, 0.f, -555.f };
GLfloat gCameraRotation[]	= { 42.f, -181.f, 0.f };
GLfloat gAnimateAngle = 0.f;
GLfloat gClipAngle;

// Misc. Globals

int gAnimating  = 0;
int gRotating  = 0;
int gDrawFrustum = 1;
int gCameraMode = OBSERVE_MODE;
int gDrawMode   = DRAW_USE_TEXTURE;
int gStartX=-1, gStartY;
int gNumTrisRendered;
long gStartTime, gEndTime;
unsigned char *gHeightMap;
unsigned char *gHeightMaster;
int gNumFrames;
float gFovX = 90.0f;

// Beginning frame varience (should be high, it will adjust automatically)
float gFrameVariance = 50;

// Desired number of Binary Triangle tessellations per frame.
// This is not the desired number of triangles rendered!
// There are usually twice as many Binary Triangle structures as there are rendered triangles.
int gDesiredTris = 10000;

void ReduceToUnit(float vector[3])
	{
	float length;
	
	// Calculate the length of the vector		
	length = sqrtf((vector[0]*vector[0]) + 
				   (vector[1]*vector[1]) +
				   (vector[2]*vector[2]));

	// Keep the program from blowing up by providing an exceptable
	// value for vectors that may calculated too close to zero.
	if(length == 0.0f)
		length = 1.0f;

	// Dividing each element by the length will result in a
	// unit normal vector.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
	}

// ---------------------------------------------------------------------
// Points p1, p2, & p3 specified in counter clock-wise order
//
void calcNormal(float v[3][3], float out[3])
	{
	float v1[3],v2[3];
	static const int x = 0;
	static const int y = 1;
	static const int z = 2;

	// Calculate two vectors from the three points
	v1[x] = v[0][x] - v[1][x];
	v1[y] = v[0][y] - v[1][y];
	v1[z] = v[0][z] - v[1][z];

	v2[x] = v[1][x] - v[2][x];
	v2[y] = v[1][y] - v[2][y];
	v2[z] = v[1][z] - v[2][z];

	// Take the cross product of the two vectors to get
	// the normal vector which will be stored in out
	out[x] = v1[y]*v2[z] - v1[z]*v2[y];
	out[y] = v1[z]*v2[x] - v1[x]*v2[z];
	out[z] = v1[x]*v2[y] - v1[y]*v2[x];

	// Normalize the vector (shorten length to one)
	ReduceToUnit(out);
	}

void Patch::Split(TriTreeNode *tri)
{
	// We are already split, no need to do it again.
	if (tri->LeftChild)
		return;

	// If this triangle is not in a proper diamond, force split our base neighbor
	if ( tri->BaseNeighbor && (tri->BaseNeighbor->BaseNeighbor != tri) )
		Split(tri->BaseNeighbor);

	// Create children and link into mesh
	tri->LeftChild  = Landscape::AllocateTri();
	tri->RightChild = Landscape::AllocateTri();

	// If creation failed, just exit.
	if ( !tri->LeftChild )
		return;

	// Fill in the information we can get from the parent (neighbor pointers)
	tri->LeftChild->BaseNeighbor  = tri->LeftNeighbor;
	tri->LeftChild->LeftNeighbor  = tri->RightChild;

	tri->RightChild->BaseNeighbor  = tri->RightNeighbor;
	tri->RightChild->RightNeighbor = tri->LeftChild;

	// Link our Left Neighbor to the new children
	if (tri->LeftNeighbor != NULL)
	{
		if (tri->LeftNeighbor->BaseNeighbor == tri)
			tri->LeftNeighbor->BaseNeighbor = tri->LeftChild;
		else if (tri->LeftNeighbor->LeftNeighbor == tri)
			tri->LeftNeighbor->LeftNeighbor = tri->LeftChild;
		else if (tri->LeftNeighbor->RightNeighbor == tri)
			tri->LeftNeighbor->RightNeighbor = tri->LeftChild;
		else
			;// Illegal Left Neighbor!
	}

	// Link our Right Neighbor to the new children
	if (tri->RightNeighbor != NULL)
	{
		if (tri->RightNeighbor->BaseNeighbor == tri)
			tri->RightNeighbor->BaseNeighbor = tri->RightChild;
		else if (tri->RightNeighbor->RightNeighbor == tri)
			tri->RightNeighbor->RightNeighbor = tri->RightChild;
		else if (tri->RightNeighbor->LeftNeighbor == tri)
			tri->RightNeighbor->LeftNeighbor = tri->RightChild;
		else
			;// Illegal Right Neighbor!
	}

	// Link our Base Neighbor to the new children
	if (tri->BaseNeighbor != NULL)
	{
		if ( tri->BaseNeighbor->LeftChild )
		{
			tri->BaseNeighbor->LeftChild->RightNeighbor = tri->RightChild;
			tri->BaseNeighbor->RightChild->LeftNeighbor = tri->LeftChild;
			tri->LeftChild->RightNeighbor = tri->BaseNeighbor->RightChild;
			tri->RightChild->LeftNeighbor = tri->BaseNeighbor->LeftChild;
		}
		else
			Split( tri->BaseNeighbor);  // Base Neighbor (in a diamond with us) was not split yet, so do that now.
	}
	else
	{
		// An edge triangle, trivial case.
		tri->LeftChild->RightNeighbor = NULL;
		tri->RightChild->LeftNeighbor = NULL;
	}
}

// ---------------------------------------------------------------------
// Tessellate a Patch.
// Will continue to split until the variance metric is met.
//
void Patch::RecursTessellate( TriTreeNode *tri,
							 int leftX,  int leftY,
							 int rightX, int rightY,
							 int apexX,  int apexY,
							 int node )
{
	float TriVariance;
	int centerX = (leftX + rightX)>>1; // Compute X coordinate of center of Hypotenuse
	int centerY = (leftY + rightY)>>1; // Compute Y coord...

	if ( node < (1<<VARIANCE_DEPTH) )
	{
		// Extremely slow distance metric (sqrt is used).
		// Replace this with a faster one!
		float distance = 1.0f + sqrtf( SQR((float)centerX - gViewPosition[0]) +
									   SQR((float)centerY - gViewPosition[2]) );
		
		// Egads!  A division too?  What's this world coming to!
		// This should also be replaced with a faster operation.
		TriVariance = ((float)m_CurrentVariance[node] * MAP_SIZE * 2)/distance;	// Take both distance and variance into consideration
	}

	if ( (node >= (1<<VARIANCE_DEPTH)) ||	// IF we do not have variance info for this node, then we must have gotten here by splitting, so continue down to the lowest level.
		 (TriVariance > gFrameVariance))	// OR if we are not below the variance tree, test for variance.
	{
		Split(tri);														// Split this triangle.
		
		if (tri->LeftChild &&											// If this triangle was split, try to split it's children as well.
			((abs(leftX - rightX) >= 3) || (abs(leftY - rightY) >= 3)))	// Tessellate all the way down to one vertex per height field entry
		{
			RecursTessellate( tri->LeftChild,   apexX,  apexY, leftX, leftY, centerX, centerY,    node<<1  );
			RecursTessellate( tri->RightChild, rightX, rightY, apexX, apexY, centerX, centerY, 1+(node<<1) );
		}
	}
}

// ---------------------------------------------------------------------
// Render the tree.  Simple no-fan method.
//
void Patch::RecursRender( TriTreeNode *tri, int leftX, int leftY, int rightX, int rightY, int apexX, int apexY )
{
	if ( tri->LeftChild )					// All non-leaf nodes have both children, so just check for one
	{
		int centerX = (leftX + rightX)>>1;	// Compute X coordinate of center of Hypotenuse
		int centerY = (leftY + rightY)>>1;	// Compute Y coord...

		RecursRender( tri->LeftChild,  apexX,   apexY, leftX, leftY, centerX, centerY );
		RecursRender( tri->RightChild, rightX, rightY, apexX, apexY, centerX, centerY );
	}
	else									// A leaf node!  Output a triangle to be rendered.
	{
		// Actual number of rendered triangles...
		gNumTrisRendered++;

		GLfloat leftZ  = m_HeightMap[(leftY *MAP_SIZE)+leftX ];
		GLfloat rightZ = m_HeightMap[(rightY*MAP_SIZE)+rightX];
		GLfloat apexZ  = m_HeightMap[(apexY *MAP_SIZE)+apexX ];

        double tx,ty;

        tx=leftX;
        ty=leftY;

        tx+=m_WorldX;
        ty+=m_WorldY;

        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,tx,ty);

        tx/=(MAP_SIZE);//*512.0f);
        ty/=(MAP_SIZE);//*512.0f);

        //glTexCoord2d(tx,ty);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,tx,ty);
        

		glVertex3f(		(GLfloat) leftX,
						(GLfloat) leftY,
						(GLfloat) leftZ );


        tx=rightX;
        ty=rightY;
        tx+=m_WorldX;
        ty+=m_WorldY;

        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,tx,ty);

        tx/=(MAP_SIZE);//*512.0f);
        ty/=(MAP_SIZE);//*512.0f);

        //glTexCoord2d(tx,ty);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,tx,ty);

		glVertex3f(		(GLfloat) rightX,
						(GLfloat) rightY,
						(GLfloat) rightZ );

        tx=apexX;
        ty=apexY;
        tx+=m_WorldX;
        ty+=m_WorldY;

        glMultiTexCoord2fARB(GL_TEXTURE1_ARB,tx,ty);

        tx/=(MAP_SIZE);//*512.0f);
        ty/=(MAP_SIZE);//*512.0f);

        //glTexCoord2d(tx,ty);
        glMultiTexCoord2fARB(GL_TEXTURE0_ARB,tx,ty);

		glVertex3f(		(GLfloat) apexX,
						(GLfloat) apexY,
						(GLfloat) apexZ );
	}
}

// ---------------------------------------------------------------------
// Computes Variance over the entire tree.  Does not examine node relationships.
//
unsigned char Patch::RecursComputeVariance( int leftX,  int leftY,  unsigned char leftZ,
										    int rightX, int rightY, unsigned char rightZ,
											int apexX,  int apexY,  unsigned char apexZ,
											int node)
{
	//        /|\
	//      /  |  \
	//    /    |    \
	//  /      |      \
	//  ~~~~~~~*~~~~~~~  <-- Compute the X and Y coordinates of '*'
	//
	int centerX = (leftX + rightX) >>1;		// Compute X coordinate of center of Hypotenuse
	int centerY = (leftY + rightY) >>1;		// Compute Y coord...
	unsigned char myVariance;

	// Get the height value at the middle of the Hypotenuse
	unsigned char centerZ  = m_HeightMap[(centerY * MAP_SIZE) + centerX];

	// Variance of this triangle is the actual height at it's hypotenuse midpoint minus the interpolated height.
	// Use values passed on the stack instead of re-accessing the Height Field.
	myVariance = abs((int)centerZ - (((int)leftZ + (int)rightZ)>>1));

	// Since we're after speed and not perfect representations,
	//    only calculate variance down to an 8x8 block
	if ( (abs(leftX - rightX) >= 8) ||
		 (abs(leftY - rightY) >= 8) )
	{
		// Final Variance for this node is the max of it's own variance and that of it's children.
		myVariance = MAX( myVariance, RecursComputeVariance( apexX,   apexY,  apexZ, leftX, leftY, leftZ, centerX, centerY, centerZ,    node<<1 ) );
		myVariance = MAX( myVariance, RecursComputeVariance( rightX, rightY, rightZ, apexX, apexY, apexZ, centerX, centerY, centerZ, 1+(node<<1)) );
	}

	// Store the final variance for this node.  Note Variance is never zero.
	if (node < (1<<VARIANCE_DEPTH))
		m_CurrentVariance[node] = 1 + myVariance;

	return myVariance;
}

// -------------------------------------------------------------------------------------------------
//	PATCH CLASS
// -------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------
// Initialize a patch.
//
void Patch::Init( int heightX, int heightY, int worldX, int worldY, unsigned char *hMap )
{
	// Clear all the relationships
	m_BaseLeft.RightNeighbor = m_BaseLeft.LeftNeighbor = m_BaseRight.RightNeighbor = m_BaseRight.LeftNeighbor =
	m_BaseLeft.LeftChild = m_BaseLeft.RightChild = m_BaseRight.LeftChild = m_BaseLeft.LeftChild = NULL;

	// Attach the two m_Base triangles together
	m_BaseLeft.BaseNeighbor = &m_BaseRight;
	m_BaseRight.BaseNeighbor = &m_BaseLeft;

	// Store Patch offsets for the world and heightmap.
	m_WorldX = worldX;
	m_WorldY = worldY;

	// Store pointer to first byte of the height data for this patch.
	m_HeightMap = &hMap[heightY * MAP_SIZE + heightX];

	// Initialize flags
	m_VarianceDirty = 1;
	m_isVisible = 0;
}

// ---------------------------------------------------------------------
// Reset the patch.
//
void Patch::Reset()
{
	// Assume patch is not visible.
	m_isVisible = 0;

	// Reset the important relationships
	m_BaseLeft.LeftChild = m_BaseLeft.RightChild = m_BaseRight.LeftChild = m_BaseLeft.LeftChild = NULL;

	// Attach the two m_Base triangles together
	m_BaseLeft.BaseNeighbor = &m_BaseRight;
	m_BaseRight.BaseNeighbor = &m_BaseLeft;

	// Clear the other relationships.
	m_BaseLeft.RightNeighbor = m_BaseLeft.LeftNeighbor = m_BaseRight.RightNeighbor = m_BaseRight.LeftNeighbor = NULL;
}

// ---------------------------------------------------------------------
// Compute the variance tree for each of the Binary Triangles in this patch.
//
void Patch::ComputeVariance()
{
	// Compute variance on each of the base triangles...

	m_CurrentVariance = m_VarianceLeft;
	RecursComputeVariance(	0,          PATCH_SIZE, m_HeightMap[PATCH_SIZE * MAP_SIZE],
							PATCH_SIZE, 0,          m_HeightMap[PATCH_SIZE],
							0,          0,          m_HeightMap[0],
							1);

	m_CurrentVariance = m_VarianceRight;
	RecursComputeVariance(	PATCH_SIZE, 0,          m_HeightMap[ PATCH_SIZE],
							0,          PATCH_SIZE, m_HeightMap[ PATCH_SIZE * MAP_SIZE],
							PATCH_SIZE, PATCH_SIZE, m_HeightMap[(PATCH_SIZE * MAP_SIZE) + PATCH_SIZE],
							1);

	// Clear the dirty flag for this patch
	m_VarianceDirty = 0;
}

// ---------------------------------------------------------------------
// Discover the orientation of a triangle's points:
//
// Taken from "Programming Principles in Computer Graphics", L. Ammeraal (Wiley)
//
inline int orientation( int pX, int pY, int qX, int qY, int rX, int rY )
{
	int aX, aY, bX, bY;
	float d;

	aX = qX - pX;
	aY = qY - pY;

	bX = rX - pX;
	bY = rY - pY;

	d = (float)aX * (float)bY - (float)aY * (float)bX;
	return (d < 0) ? (-1) : (d > 0);
}

// ---------------------------------------------------------------------
// Set patch's visibility flag.
//
void Patch::SetVisibility( int eyeX, int eyeY, int leftX, int leftY, int rightX, int rightY )
{
	// Get patch's center point
	int patchCenterX = m_WorldX + PATCH_SIZE / 2;
	int patchCenterY = m_WorldY + PATCH_SIZE / 2;
	
	// Set visibility flag (orientation of both triangles must be counter clockwise)
	m_isVisible = (orientation( eyeX,  eyeY,  rightX, rightY, patchCenterX, patchCenterY ) < 0) &&
				  (orientation( leftX, leftY, eyeX,   eyeY,   patchCenterX, patchCenterY ) < 0);
}

// ---------------------------------------------------------------------
// Create an approximate mesh.
//
void Patch::Tessellate()
{
	// Split each of the base triangles
	m_CurrentVariance = m_VarianceLeft;
	RecursTessellate (	&m_BaseLeft,
						m_WorldX,				m_WorldY+PATCH_SIZE,
						m_WorldX+PATCH_SIZE,	m_WorldY,
						m_WorldX,				m_WorldY,
						1 );
					
	m_CurrentVariance = m_VarianceRight;
	RecursTessellate(	&m_BaseRight,
						m_WorldX+PATCH_SIZE,	m_WorldY,
						m_WorldX,				m_WorldY+PATCH_SIZE,
						m_WorldX+PATCH_SIZE,	m_WorldY+PATCH_SIZE,
						1 );
}

// ---------------------------------------------------------------------
// Render the mesh.
//
void Patch::Render()
{
	// Store old matrix
	glPushMatrix();
	
	// Translate the patch to the proper world coordinates
	glTranslatef( (GLfloat)m_WorldX, (GLfloat)m_WorldY, 0 );
    
    

	glBegin(GL_TRIANGLES);
		
		RecursRender (	&m_BaseLeft,
			0,				PATCH_SIZE,
			PATCH_SIZE,		0,
			0,				0);
		
		RecursRender(	&m_BaseRight,
			PATCH_SIZE,		0,
			0,				PATCH_SIZE,
			PATCH_SIZE,		PATCH_SIZE);
	
	glEnd();
	
	// Restore the matrix
	glPopMatrix();
}

// -------------------------------------------------------------------------------------------------
//	LANDSCAPE CLASS
// -------------------------------------------------------------------------------------------------

// ---------------------------------------------------------------------
// Definition of the static member variables
//
int         Landscape::m_NextTriNode;
TriTreeNode Landscape::m_TriPool[POOL_SIZE];

// ---------------------------------------------------------------------
// Allocate a TriTreeNode from the pool.
//
TriTreeNode *Landscape::AllocateTri()
{
	TriTreeNode *pTri;

	// IF we've run out of TriTreeNodes, just return NULL (this is handled gracefully)
	if ( m_NextTriNode >= POOL_SIZE )
		return NULL;

	pTri = &(m_TriPool[m_NextTriNode++]);
	pTri->LeftChild = pTri->RightChild = NULL;

	return pTri;
}

// ---------------------------------------------------------------------
// Initialize all patches
//
void Landscape::Init(unsigned char *hMap)
{
	Patch *patch;
	int X, Y;

	// Store the Height Field array
	m_HeightMap = hMap;

	// Initialize all terrain patches
	for ( Y=0; Y < NUM_PATCHES_PER_SIDE; Y++)
		for ( X=0; X < NUM_PATCHES_PER_SIDE; X++ )
		{
			patch = &(m_Patches[Y][X]);
			patch->Init( X*PATCH_SIZE, Y*PATCH_SIZE, X*PATCH_SIZE, Y*PATCH_SIZE, hMap );
			patch->ComputeVariance();
		}
}

// ---------------------------------------------------------------------
// Reset all patches, recompute variance if needed
//
void Landscape::Reset()
{
	//
	// Perform simple visibility culling on entire patches.
	//   - Define a triangle set back from the camera by one patch size, following
	//     the angle of the frustum.
	//   - A patch is visible if it's center point is included in the angle: Left,Eye,Right
	//   - This visibility test is only accurate if the camera cannot look up or down significantly.
	//
	const float PI_DIV_180 = M_PI / 180.0f;
	const float FOV_DIV_2 = gFovX/2;

	int eyeX = (int)(gViewPosition[0] - PATCH_SIZE * sinf( gClipAngle * PI_DIV_180 ));
	int eyeY = (int)(gViewPosition[2] + PATCH_SIZE * cosf( gClipAngle * PI_DIV_180 ));

	int leftX  = (int)(eyeX + 100.0f * sinf( (gClipAngle-FOV_DIV_2) * PI_DIV_180 ));
	int leftY  = (int)(eyeY - 100.0f * cosf( (gClipAngle-FOV_DIV_2) * PI_DIV_180 ));

	int rightX = (int)(eyeX + 100.0f * sinf( (gClipAngle+FOV_DIV_2) * PI_DIV_180 ));
	int rightY = (int)(eyeY - 100.0f * cosf( (gClipAngle+FOV_DIV_2) * PI_DIV_180 ));

	int X, Y;
	Patch *patch;

	// Set the next free triangle pointer back to the beginning
	SetNextTriNode(0);

	// Reset rendered triangle count.
	gNumTrisRendered = 0;

	// Go through the patches performing resets, compute variances, and linking.
	for ( Y=0; Y < NUM_PATCHES_PER_SIDE; Y++ )
		for ( X=0; X < NUM_PATCHES_PER_SIDE; X++)
		{
			patch = &(m_Patches[Y][X]);
			
			// Reset the patch
			patch->Reset();
			patch->SetVisibility( eyeX, eyeY, leftX, leftY, rightX, rightY );
			
			// Check to see if this patch has been deformed since last frame.
			// If so, recompute the varience tree for it.
			if ( patch->isDirty() )
				patch->ComputeVariance();

			if ( patch->isVisibile() )
			{
				// Link all the patches together.
				if ( X > 0 )
					patch->GetBaseLeft()->LeftNeighbor = m_Patches[Y][X-1].GetBaseRight();
				else
					patch->GetBaseLeft()->LeftNeighbor = NULL;		// Link to bordering Landscape here..

				if ( X < (NUM_PATCHES_PER_SIDE-1) )
					patch->GetBaseRight()->LeftNeighbor = m_Patches[Y][X+1].GetBaseLeft();
				else
					patch->GetBaseRight()->LeftNeighbor = NULL;		// Link to bordering Landscape here..

				if ( Y > 0 )
					patch->GetBaseLeft()->RightNeighbor = m_Patches[Y-1][X].GetBaseRight();
				else
					patch->GetBaseLeft()->RightNeighbor = NULL;		// Link to bordering Landscape here..

				if ( Y < (NUM_PATCHES_PER_SIDE-1) )
					patch->GetBaseRight()->RightNeighbor = m_Patches[Y+1][X].GetBaseLeft();
				else
					patch->GetBaseRight()->RightNeighbor = NULL;	// Link to bordering Landscape here..
			}
		}

}

// ---------------------------------------------------------------------
// Create an approximate mesh of the landscape.
//
void Landscape::Tessellate()
{
	// Perform Tessellation
	int nCount;
	Patch *patch = &(m_Patches[0][0]);
	for (nCount=0; nCount < NUM_PATCHES_PER_SIDE*NUM_PATCHES_PER_SIDE; nCount++, patch++ )
	{
		if (patch->isVisibile())
			patch->Tessellate( );
	}
}

// ---------------------------------------------------------------------
// Render each patch of the landscape & adjust the frame variance.
//
void Landscape::Render()
{
	int nCount;
	Patch *patch = &(m_Patches[0][0]);

	// Scale the terrain by the terrain scale specified at compile time.
//	glScalef( 1.0f, 1, 1.0f );

	for (nCount=0; nCount < NUM_PATCHES_PER_SIDE*NUM_PATCHES_PER_SIDE; nCount++, patch++ )
	{
		if (patch->isVisibile())
			patch->Render();
	}

	// Check to see if we got close to the desired number of triangles.
	// Adjust the frame variance to a better value.
	if ( GetNextTriNode() != gDesiredTris )
		gFrameVariance += ((float)GetNextTriNode() - (float)gDesiredTris) / (float)gDesiredTris;

	// Bounds checking.
	if ( gFrameVariance < 0 )
		gFrameVariance = 0;
}




// ---------------------------------------------------------------------
// Load the Height Field from a data file
//

extern "C" CTerra img;

void loadTerrain(int size, unsigned char **dest)
{
    
	FILE *fp;
	char fileName[30];

	// Optimization:  Add an extra row above and below the height map.
	//   - The extra top row contains a copy of the last row in the height map.
	//   - The extra bottom row contains a copy of the first row in the height map.
	// This simplifies the wrapping of height values to a trivial case. 
	gHeightMaster = (unsigned char *)malloc( size * size * sizeof(unsigned char) + size * 2 );
	
	// Give the rest of the application a pointer to the actual start of the height map.
	*dest = gHeightMaster + size;

	sprintf( fileName, "Height%d.raw", size );
	fp = fopen(fileName, "rb");

	// TESTING: READ A TREAD MARKS MAP...
	if ( fp == NULL )
	{
		sprintf( fileName, "Map.ved", size );
		fp = fopen(fileName, "rb");
		if ( fp != NULL )
			fseek( fp, 40, SEEK_SET );	// Skip to the goods...
	}

	if (fp == NULL)
	{
		// Oops!  Couldn't find the file.
		
		// Clear the board.
		memset( gHeightMaster, 0, size * size + size * 2 );
		return;
	}
	fread(gHeightMaster + size, 1, (size * size), fp);
	fclose(fp);

	// Copy the last row of the height map into the extra first row.
	memcpy( gHeightMaster, gHeightMaster + size * size, size );

/*
	gHeightMaster = (unsigned char *)malloc( size * size * sizeof(unsigned char) + size * 2 );
	
	// Give the rest of the application a pointer to the actual start of the height map.
	*dest = gHeightMaster + size;


    LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(img.m_hDib);			


    BYTE *lpBits = ((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER);

    BYTE *lpDest=(gHeightMaster + size);

	//memcpy(gHeightMaster + size, lpBits,(size*size));

    for (int i=0;i<(size*size);i++)
    {
        *lpDest=*lpBits;
        lpDest++;
        lpBits+=3;
    }

    //memcpy( gHeightMaster, gHeightMaster + size * size, size );

    GlobalUnlock(BiDest);
	// Copy the first row of the height map into the extra last row.
*/
}

// ---------------------------------------------------------------------
// Free the Height Field array
//
void freeTerrain()
{
	if ( gHeightMaster )
		free( gHeightMaster );
}

// ---------------------------------------------------------------------
// Initialize the ROAM implementation
//

int roamInit(unsigned char *map)
{
	// Perform some bounds checking on the #define statements
	if ( gDesiredTris > POOL_SIZE )
		return -1;

	if ( POOL_SIZE < 100 )
		return -1;



// ----------- LANDSCAPE INITIALIZATION -----------
	gLand.Init(map);

	return 0;
}

// ---------------------------------------------------------------------
// Call all functions needed to draw a frame of the landscape
//
void roamDrawFrame()
{
	// Perform all the functions needed to render one frame.
	gLand.Reset();
	gLand.Tessellate();
	gLand.Render();
}
/*
void RenderScene(void)
{
    gViewPosition[0] =VCam->Source.vx;
	gViewPosition[1] =0;
	gViewPosition[2] =VCam->Source.vy;


	glPushMatrix();

    gClipAngle =-((ng(VCam->Source.vx,VCam->Source.vy,VCam->Dest.vx,VCam->Dest.vy)*180)/PI)+90;


	roamDrawFrame();

	glPopMatrix();

	// Increment the frame counter.
	gNumFrames++;
}
*/

////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////


	Vertex		 origin, dimen;			// terrain origin in space, and its dimensions
	unsigned long		 vertXRes, vertYRes;	// vertex buffer size
	float		 waterHeight;			// height of water (0..1) 

	//VertexData	*pVertexData;			// the vertex data for the terrain

	//word		*pIndexArray;

	Vertex		 skyBoxVerts[12];		// vertices for skybox

    unsigned long mapXRes=1024;
    unsigned long mapYRes=1024;


void SetParams(Vertex &origin, Vertex &dimen, float density, float waterHeight)
{
	origin = origin;
	dimen = dimen;
	waterHeight = waterHeight;

	// calculate the resolution of our vertex-map
	vertXRes = (unsigned long)(mapXRes * density);
	vertYRes = (unsigned long)(mapYRes * density);

	if (vertXRes < 3)
		vertXRes = 3;

	if (vertYRes < 3)
		vertYRes = 3;

	vertXRes = 1 + ((vertXRes-1)>>1)*2;
	vertYRes = 1 + ((vertYRes-1)>>1)*2;

//	pVertexData = new VertexData[vertXRes*vertYRes];


//	BuildTerrain();

	
	// construct sky-box vertices

	// vertices
	Vertex	center, radius;
	const float rad = dimen.vx*12;

	center = origin + (dimen * 0.5f);
	center.vy = origin.vy+dimen.vy*waterHeight;
	radius.vx=rad;
    radius.vy=rad;
    radius.vz=rad;

	// top
	skyBoxVerts[0].vx=center.vx-radius.vx;
    skyBoxVerts[0].vz=center.vy+radius.vy;
    skyBoxVerts[0].vy=center.vz+radius.vz;

	skyBoxVerts[1].vx=center.vx+radius.vx;
    skyBoxVerts[1].vz=center.vy+radius.vy;
    skyBoxVerts[1].vy=center.vz+radius.vz;

	skyBoxVerts[2].vx=center.vx+radius.vx;
    skyBoxVerts[2].vz=center.vy+radius.vy;
    skyBoxVerts[2].vy=center.vz-radius.vz;

	skyBoxVerts[3].vx=center.vx-radius.vx;
    skyBoxVerts[3].vz=center.vy+radius.vy;
    skyBoxVerts[3].vy=center.vz-radius.vz;

	// bottom
	skyBoxVerts[4].vx=center.vx-radius.vx;
    skyBoxVerts[4].vz=center.vy;
    skyBoxVerts[4].vy=center.vz+radius.vz;

	skyBoxVerts[5].vx=center.vx+radius.vx;
    skyBoxVerts[5].vz=center.vy;
    skyBoxVerts[5].vy=center.vz+radius.vz;

	skyBoxVerts[6].vx=center.vx+radius.vx;
    skyBoxVerts[6].vz=center.vy;
    skyBoxVerts[6].vy=center.vz-radius.vz;

	skyBoxVerts[7].vx=center.vx-radius.vx;
    skyBoxVerts[7].vz=center.vy;
    skyBoxVerts[7].vy=center.vz-radius.vz;
}


void aaRender()
{
/*
	// enable a clipping plane (so that the terrain that extrudes out of the water
	// doesn't get drawn
	double plane_eqn[4] = { 0, -1, 0, origin.y + dimen.y*waterHeight}; 
	glClipPlane( GL_CLIP_PLANE0, plane_eqn ); 
	glEnable( GL_CLIP_PLANE0 ); 


	// vertical-flip everything
	glTranslatef(0, 2*waterHeight*dimen.y, 0);
	glScalef(1, -1, 1);

		// reverse culling order
		glCullFace(GL_BACK);
		
		RenderTerrain();
		RenderSkyBox();

		// restore correct culling
		glCullFace(GL_FRONT);

	// re-flip vertically
	glScalef(1, -1, 1);
	glTranslatef(0, -2*waterHeight*dimen.y, 0);

	// disable extra clipping-plane
	glDisable( GL_CLIP_PLANE0 ); 



	// render water
	RenderWater();

	// render the terrain
	RenderTerrain();

	// render the skybox (will set its own textures)
	RenderSkyBox();
    */
}
extern "C" CTexture *pTexSkyBox[5];

void RenderSkyBox()
{
	// skybox

	const float u0 = 0.5f / 256.f,
				u1 = (256.f-0.5f) / 256.f,
				v0 = 0.5f / 256.f,
				v1 = (256.f-0.5f) / 256.f;

	const unsigned long dataOfs[5][4] = {
		{7,6,2,3},
		{1,2,6,5},
		{0,1,5,4},
		{4,7,3,0},
		{3,2,1,0}
	};

	const float mapping[4][2] = { {u0, v1}, {u1,v1}, {u1,v0}, {u0, v0} };

	unsigned long i;


	for (i=0; i<5; i++) {
//		pTexSkyBox[i].Use();
        pTexSkyBox[i]->Bind();
		glBegin( GL_QUADS );

		long j;

		for (j=0; j<4; j++) {
			glTexCoord2d(mapping[j][0], mapping[j][1]);
			glVertex3f(skyBoxVerts[dataOfs[i][j]].vx,skyBoxVerts[dataOfs[i][j]].vy,skyBoxVerts[dataOfs[i][j]].vz);
		}

		glEnd();
	}


	// front
	// right
	// back
	// left
	// top
}

//extern "C" CTexture *WaterTex;
//extern int WaterTexID;

void RenderWater()
{
	float waterTile = 2*60.f;

#define	WATER_STRIP_LEN	15
#define WATER_STRIP_LEN_1	(WATER_STRIP_LEN-1)

	Vertex	temp;
	Vertex	dU, dV;

	dU = skyBoxVerts[5] - skyBoxVerts[4];
	dV = skyBoxVerts[7] - skyBoxVerts[4];


    //glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,1,1,0.75f);

//	pTexSkyBox[5].Use();
//    WaterTex->Bind();


	for (unsigned long j=0; j<WATER_STRIP_LEN; j++) {
		glBegin( GL_QUAD_STRIP );
		for (unsigned long i=0; i<WATER_STRIP_LEN+1; i++) {
			for (long dy=1; dy>=0; dy--) {
				temp = skyBoxVerts[4];
				temp += dU * ((float)i / WATER_STRIP_LEN);
				temp += dV * ((float)(j+dy) / WATER_STRIP_LEN);
				glTexCoord2d((j+dy)*waterTile/WATER_STRIP_LEN, i*waterTile/WATER_STRIP_LEN);
                temp.vz=0;
				glVertex3f(temp.vx,temp.vy,temp.vz);
			}
		}
		glEnd();
	}

//	glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);//GL_SRC_ALPHA);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);//GL_SRC_ALPHA);


	float anim = 0;//sys_Time*0.00003f;

	for (j=0; j<WATER_STRIP_LEN; j++) {
		glBegin( GL_QUAD_STRIP );
		for (unsigned long i=0; i<WATER_STRIP_LEN+1; i++) {
			for (long dy=1; dy>=0; dy--) {
				temp = skyBoxVerts[4];
				temp += dU * ((float)i / WATER_STRIP_LEN);
				temp += dV * ((float)(j+dy) / WATER_STRIP_LEN);
				glTexCoord2d(anim+((j+dy)*waterTile/WATER_STRIP_LEN), anim+(i*waterTile/WATER_STRIP_LEN));
				//glVertex3fv(temp.GetPtr());
                temp.vz=0;
                glVertex3f(temp.vx,temp.vy,temp.vz);
			}
		}
		glEnd();
	}

    //glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);


}