#if !defined(SCENEGRAPH)
#define SCENEGRAPH

#include "headers.h"

extern Camera *VCam;


#define FOLLOW_MODE (0)
#define OBSERVE_MODE (1)
#define DRIVE_MODE (2)
#define FLY_MODE (3)

// Perspective & Window defines
#define FOV_ANGLE     (30.0f)
#define NEAR_CLIP     (1.0f)
#define FAR_CLIP      (2500.0f)
// Defines...
#define WINDOW_WIDTH  (640)
#define WINDOW_HEIGHT (480)

// Globals...
extern unsigned char *gHeightMap;

// Functions...
void ReduceToUnit(float vector[3]);
void calcNormal(float v[3][3], float out[3]);
void loadTerrain(int size, unsigned char **dest);
void freeTerrain();
void SetDrawModeContext();
int roamInit(unsigned char *map);
void roamDrawFrame();
void drawFrustum();


void RenderWater();
void SetParams(Vertex &origin, Vertex &dimen, float density, float waterHeight);
void RenderSkyBox();

extern int gAnimating;
extern int gCameraMode;
/*
extern void KeyObserveToggle(void);
extern void KeyDrawModeSurf(void);
extern void KeyForward(void);
extern void KeyLeft(void);
extern void KeyBackward(void);
extern void KeyRight(void);
extern void KeyAnimateToggle(void);
extern void KeyDrawFrustumToggle(void);
extern void KeyUp(void);
extern void KeyDown(void);
extern void KeyMoreDetail(void);
extern void KeyLessDetail(void);
extern void ChangeSize(GLsizei w, GLsizei h);
extern void KeyFOVDown(void);
extern void KeyFOVUp(void);
*/
void RenderScene(void);
//extern void IdleFunction(void);
//extern void MouseMove(int mouseX, int mouseY);
extern void SetupRC();

// Depth of variance tree: should be near SQRT(PATCH_SIZE) + 1
#define VARIANCE_DEPTH (9)

// Predefines...
class Landscape;

//
// TriTreeNode Struct
// Store the triangle tree data, but no coordinates!
//
struct TriTreeNode
{
	TriTreeNode *LeftChild;
	TriTreeNode *RightChild;
	TriTreeNode *BaseNeighbor;
	TriTreeNode *LeftNeighbor;
	TriTreeNode *RightNeighbor;
};

//
// Patch Class
// Store information needed at the Patch level
//
class Patch
{
protected:
	unsigned char *m_HeightMap;									// Pointer to height map to use
	int m_WorldX, m_WorldY;										// World coordinate offset of this patch.

	unsigned char m_VarianceLeft[ 1<<(VARIANCE_DEPTH)];			// Left variance tree
	unsigned char m_VarianceRight[1<<(VARIANCE_DEPTH)];			// Right variance tree

	unsigned char *m_CurrentVariance;							// Which varience we are currently using. [Only valid during the Tessellate and ComputeVariance passes]
	unsigned char m_VarianceDirty;								// Does the Varience Tree need to be recalculated for this Patch?
	unsigned char m_isVisible;									// Is this patch visible in the current frame?

	TriTreeNode m_BaseLeft;										// Left base triangle tree node
	TriTreeNode m_BaseRight;									// Right base triangle tree node

public:
	// Some encapsulation functions & extras
	TriTreeNode *GetBaseLeft()  { return &m_BaseLeft; }
	TriTreeNode *GetBaseRight() { return &m_BaseRight; }
	char isDirty()     { return m_VarianceDirty; }
	int  isVisibile( ) { return m_isVisible; }
	void SetVisibility( int eyeX, int eyeY, int leftX, int leftY, int rightX, int rightY );

	// The static half of the Patch Class
	virtual void Init( int heightX, int heightY, int worldX, int worldY, unsigned char *hMap );
	virtual void Reset();
	virtual void Tessellate();
	virtual void Render();
	virtual void ComputeVariance();

	// The recursive half of the Patch Class
	virtual void			Split( TriTreeNode *tri);
	virtual void			RecursTessellate( TriTreeNode *tri, int leftX, int leftY, int rightX, int rightY, int apexX, int apexY, int node );
	virtual void			RecursRender( TriTreeNode *tri, int leftX, int leftY, int rightX, int rightY, int apexX, int apexY );
	virtual unsigned char	RecursComputeVariance(	int leftX,  int leftY,  unsigned char leftZ,
													int rightX, int rightY, unsigned char rightZ,
													int apexX,  int apexY,  unsigned char apexZ,
													int node);
};


#define MAP_1024

#ifdef MAP_2048

// ------- 2048x2048 MAP -------
#define MAP_SIZE (2048)
#define NUM_PATCHES_PER_SIDE (32)

#else
#ifdef MAP_1024

// ------- 1024x1024 MAP -------
#define MAP_SIZE (1024)
#define NUM_PATCHES_PER_SIDE (16)

#else

// ------- 512x512 MAP -------
#define MAP_SIZE (512)
#define NUM_PATCHES_PER_SIDE (8)

#endif
#endif
  
/*
#define MAP_SIZE (256)
#define NUM_PATCHES_PER_SIDE (4)
*/
// ---------------------------------------------------------------------
// Scale of the terrain ie: 1 unit of the height map == how many world units (meters)?
// 1.0f == 1 meter resolution
// 0.5f == 1/2 meter resolution
// 0.25f == 1/4 meter resolution
// etc..
#define MULT_SCALE (0.5f)

// How many TriTreeNodes should be allocated?
#define POOL_SIZE (25000)

// Some more definitions
#define PATCH_SIZE (MAP_SIZE/NUM_PATCHES_PER_SIDE)
#define TEXTURE_SIZE (128)

// Drawing Modes
#define DRAW_USE_TEXTURE   (0)
#define DRAW_USE_LIGHTING  (1)
#define DRAW_USE_FILL_ONLY (2)
#define DRAW_USE_WIREFRAME (3)

// Rotation Indexes
#define ROTATE_PITCH (0)
#define ROTATE_YAW   (1)
#define ROTATE_ROLL	 (2)


#define SQR(x) ((x) * (x))
#define MAX(a,b) ((a < b) ? (b) : (a))
#define DEG2RAD(a) (((a) * M_PI) / 180.0f)
#define M_PI (3.14159265358979323846f)

// External variables and functions:
/*
extern GLuint gTextureID;
extern int gDrawMode;
extern GLfloat gViewPosition[];
extern GLfloat gCameraRotation[];
extern GLfloat gClipAngle;
extern float gFrameVariance;
extern int gDesiredTris;
extern int gNumTrisRendered;
extern float gFovX;

extern void calcNormal(float v[3][3], float out[3]);
extern void ReduceToUnit(float vector[3]);
*/
//
// Landscape Class
// Holds all the information to render an entire landscape.
//
class Landscape
{
protected:
	unsigned char *m_HeightMap;										// HeightMap of the Landscape
	Patch m_Patches[NUM_PATCHES_PER_SIDE][NUM_PATCHES_PER_SIDE];	// Array of patches

	static int	m_NextTriNode;										// Index to next free TriTreeNode
	static TriTreeNode m_TriPool[POOL_SIZE];						// Pool of TriTree nodes for splitting

	static int GetNextTriNode() { return m_NextTriNode; }
	static void SetNextTriNode( int nNextNode ) { m_NextTriNode = nNextNode; }

public:
	static TriTreeNode *AllocateTri();

	virtual void Init(unsigned char *hMap);
	virtual void Reset();
	virtual void Tessellate();
	virtual void Render();

};

#endif