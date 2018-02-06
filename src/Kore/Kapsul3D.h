/*


    Kapsul 3D defs and includes


*/


#ifndef Kapsul3DH
#define Kapsul3DH

#pragma warning(disable: 4244)  
// structures divers
typedef struct
{

    double x,y;

} MYPOINT;


//#pragma pack(16)

#define VIEW_MODE2x2 101
#define VIEW_MODE1x3a 102
#define VIEW_MODE1x3b 103
#define VIEW_MODE1x2a 104
#define VIEW_MODE1x2b 105

#define MAX_ZOOM 100000000

// -- Edition ------------------------------------------------------------------

#define EDIT_MOVE 1
#define EDIT_MOVETO 2
#define EDIT_ROTATE 3
#define EDIT_BEND 4
#define EDIT_SKEW 5
#define EDIT_ARRAY 6

#define EDIT_SCALE 8
#define EDIT_BOOLEAN 9
#define EDIT_BREAK 11
#define EDIT_CLOSE 12
#define EDIT_TOGGLELINEAR 13
//#define EDIT_MOVECURVE EDIT_MOVE
//#define EDIT_MOVECURVE
#define EDIT_APPLYMAT 15
//#define EDIT_INSERTVERTEX EDIT_BREAK
#define EDIT_SQUIZ 17
#define EDIT_BUILDLINE 18
#define EDIT_BUILDFACE 19
#define EDIT_CREATECAM 23
#define EDIT_MESHUNIFY 27
#define EDIT_INVERTVECTPROD  28
#define EDIT_MOVESPACE 29
#define EDIT_ROTATEISO 30
#define EDIT_CREATELINE 31
#define EDIT_DELSEG 32
//#define EDIT_TOGGLELINEAR 33
#define EDIT_MOVECURVE 34
#define EDIT_CREATENGON 35
#define EDIT_CREATEARC 36
#define EDIT_BREAKSEG 37
#define EDIT_CREATEQUAD 38
#define EDIT_ROTATECAM 60
#define EDIT_CREATESTAR 61
/*
#define EDIT_SELECTSINGLE 39
#define EDIT_SELECTQUAD 40
#define EDIT_SELECTCIRCLE 41
*/
#define EDIT_TAPER 45

#define EDIT_LOUPE  50
#define EDIT_TOSURFACE 66
#define EDIT_3DSCALE 67

#define EDIT_BOOLEANADD 70
#define EDIT_BOOLEANSUB 71
#define EDIT_BOOLEANEX 72
#define EDIT_BOOLEANINT 73

#define EDIT_DETAIL 74

#define EDIT_SELECTFITX 75
#define EDIT_SELECTFITY 76
#define EDIT_SELECTPATHPOLY 77
#define EDIT_EXTRUD 78

#define EDIT_BUILD 80
#define EDIT_ATTACH 81
#define EDIT_MOVEIK 82

// -- Edition de la camera -----------------------------------------------------

#define EDIT_CAMPROP 60
#define EDIT_CAMMOVETARGET 61
#define EDIT_CAMMOVESOURCE 62
#define EDIT_CAMROLL 63
#define EDIT_CAMFOCUS 64

/*
// -- Sens ---------------------------------------------------------------------
#define SENS_DROITE 0
#define SENS_HAUT 1
#define SENS_GAUCHE 2
#define SENS_BAS 3

#define SENS_HORZ 4
#define SENS_VERT 8
*/

// newbies

#define EDIT_MOVEVIEW 1
#define EDIT_ROTATEVIEW 2

#define EDIT_SELECTSINGLE 800
#define EDIT_SELECTQUAD 801
#define EDIT_SELECTCIRCLE 802
#define EDIT_SELECTFENCE 803

#define EDIT_ZOOM 900
#define EDIT_REGIONFIT 901
#define EDIT_MOVEBUF 902
#define EDIT_ROTATEBUF 903
#define EDIT_PUTAXIS 904
#define EDIT_SCALEBUF 905
#define EDIT_TAPERBUF 906
#define EDIT_BENDBUF 907
#define EDIT_SQUIZBUF 908
#define EDIT_PAN3D 909
#define EDIT_PAN3D2 910

#define EDIT_CLICKAPPLYMESH 1001
#define EDIT_CLICKAPPLYPOLY 1002

#define EDIT_PLUGINCREATION 101
#define EDIT_PLUGINMODIF 102
#define EDIT_PLUGINPRIMITIVE 103



#define SHPSTL_SEL 1
#define SHPSTL_SHP 2

#define PLUGIN_CREATION 1001
#define PLUGIN_TEXTURE 1002
#define PLUGIN_MODIF 1003
#define PLUGIN_DOCVIEW 1004
#define PLUGIN_PRIMITIVE 1005
#define PLUGIN_RESOURCE 1006
#define PLUGIN_OPERATION 1007

#define PLUGIN_CAMERA 1
#define PLUGIN_MESH 2
#define PLUGIN_SHAPE 4
#define PLUGIN_PARTICLE 8
#define PLUGIN_SKELETON 16
#define PLUGIN_LIGHT 32
#define PLUGIN_GRID 64
#define PLUGIN_AXIS 128
#define PLUGIN_ENTITY 256
#define PLUGIN_PATCH 512
#define PLUGIN_BONE 1024
#define PLUGIN_SEGMENT 2048

#define PLUGIN_ALL PLUGIN_BONE|PLUGIN_SEGMENT|PLUGIN_CAMERA|PLUGIN_MESH|PLUGIN_SHAPE|PLUGIN_PARTICLE|PLUGIN_SKELETON|PLUGIN_LIGHT|PLUGIN_GRID|PLUGIN_AXIS|PLUGIN_ENTITY|PLUGIN_PATCH
#define PLUGIN_NONE 0

#define PLUGIN_PATH 2004
#define PLUGIN_MATERIAL 2005
#define PLUGIN_FILE 2006
#define PLUGIN_MAPPING 2008
#define PLUGIN_OTHER 2009


#define STAT_MESH 1
#define STAT_CAMERA 2
#define STAT_SHAPE 4
#define STAT_PARTICLE 8
#define STAT_LIGHT 16
#define STAT_SKELETON 32
#define STAT_ENTITIES 64

#define STAT_ALL STAT_MESH|STAT_CAMERA|STAT_SHAPE|STAT_PARTICLE|STAT_LIGHT|STAT_SKELETON|STAT_ENTITIES


// -- Sélection modes - bt de selection - mode de creation ---------------------

#define MODE_WINDOW 1
#define MODE_SEGMENT 2
#define MODE_FACE 3
#define MODE_MESH 4
#define MODE_LIGHT 5
#define MODE_SPOT 6
#define MODE_PATH 7
#define MODE_POLYGON 8
#define MODE_CAM 9
#define MODE_DEFORM 10
#define MODE_IK 11


// -- Primitives ---------------------------------------------------------------

#define PRIM_VERTEX 1
#define PRIM_SEGMENT 2
#define PRIM_FACE 3
#define PRIM_MESH 4

// il le fallait bien...
#define PI 3.1415926535897932384626433832795


// -- Macros -------------------------------------------------------------------

#define COMPRISIN(X,Y,Z) (((Z>=X)&&(Z<=Y))||((Z<=X)&&(Z>=Y)))

//MYPOINT pt1,MYPOINT pt2,double x)
#define INTERPOLATE(W,X,Y,Z) if ((Y.x-X.x)!=0) \
                                W=((Y.y-X.y)/(Y.x-X.x))*(Z-X.x)+X.y; \
                            else \
                                W=Y.x; 

// -- Couleurs -----------------------------------------------------------------

typedef struct
{
    unsigned char bRed;	// red component of color
    unsigned char bGreen;	// green component of color
    unsigned char bBlue;	// blue component of color
	
	DWORD GetDW(void)
	{
		return ((bRed<<16)+(bGreen<<8)+(bBlue));
	}

} RGB;

enum {
    clShape     =   0xf0,
    clShapeTk   =   0xf1,
    clShapeSel  =   0xf2,
    clShapeTkSel=   0xf3,

    clPath      =   0xe0,
    clPathTk    =   0xe1,

    clObj       =   0xd0,
    clObjTk     =   0xd1,
    clObjSel    =   0xd2,
    clObjTkSel  =   0xd3,


    clGridDot   =   0x10,
    clGridLine  =   0x11,

    clIkBone    =   0x21,
    clIkJoint   =   0x22,
    clIkRoot    =   0x23,

    clCamSrc    =   0x30,
    clCamDst    =   0x31,
    clCamLenz   =   0x32,
    clCamCone   =   0x33,

    clBack      =   0x00

};

// -- Macros -------------------------------------------------------------------

#define AssCoul(x,y) \
    x.rgbRed=y.bRed; \
    x.rgbGreen=y.bGreen; \
    x.rgbBlue=y.bBlue;

#define RotX(x,y,z) \
    x * cos (z) - y * sin (z) ;

#define RotY(x,y,z) \
    x * sin (z) + y * cos (z) ;

#define DEG2RAD(x) \
	((x*PI)/360.0f)



// -- Chunks KDK ---------------------------------------------------------------
/*
typedef struct
{
    word id;
    const char *name;
    void *fnc;
} KDKChunk;
*/


#define NB23DSCHUNKS 51


// -- Segment sorting ----------------------------------------------------------

typedef struct
{
    double  xy;
    int     sind;
    void * val;

} SegSort;

typedef int TriangleList[10000];


// -- Curseurs -----------------------------------------------------------------

#define crLoupe 40
#define crRegionFit 41
#define crBuild 42
#define crSelect 43
#define crSpan 44
#define crMoveAll 45
#define crMoveUpDown 46
#define crMoveRightLeft 47





// -- Messages perso ----------------------------------------------------------

#define WM_GETSTATUS WM_USER+1
#define WM_DRAWSCENE WM_USER+2
#define WM_SETSTATUS WM_USER+3
#define WM_GETPANELHEIGHT WM_USER+4
#define WM_GETKNAME WM_USER+5
#define WM_SETPLUGIN WM_USER+6
#define WM_GETCTKEYS WM_USER+7
#define WM_SETMOUSECURSOR WM_USER+8
#define WM_DOCUMENTUPDATED WM_USER+12
#define WM_LISTDOCUMENT WM_USER+13

// -- Selection ---------------------------------------------------------------

#define SELECT_SINGLE 101
#define SELECT_FENCE 102
#define SELECT_QUAD 103
#define SELECT_CIRCLE 104

#define SELECT_VERTEX 201
#define SELECT_FACE 202
#define SELECT_WHOLE 203
#define SELECT_SEGMENT 204


#define VIEWTYPE_ORTHO 1
#define VIEWTYPE_CAMERA 2
#define VIEWTYPE_PERSPECTIVE 3
#define VIEWTYPE_UV 4

// -- Undo --------------------------------------------------------------------

#define UNDO_CREATE 1
#define UNDO_MODIFY 2
#define UNDO_DELETE 3

// -- Object Dirty Parameters -------------------------------------------------

#define DIRTY_MAPPING 1
#define DIRTY_GEOM 2
#define DIRTY_COLOR 4

// -- DLL Import/Export -------------------------------------------------------

#ifdef KAPSUL_EXPORT
	#define KAPSUL_DESC __declspec(dllexport)
#else
	#define KAPSUL_DESC __declspec(dllimport)
#endif


#include <vector>
using std::vector;

       

class KAPSUL_DESC  CKObjectBase;
class KAPSUL_DESC  CKPlugin;
class KAPSUL_DESC  CKBone;
class KAPSUL_DESC  CKSceneBase;
class KAPSUL_DESC  CKSceneSelection;
class KAPSUL_DESC  CKSceneOperation;
class KAPSUL_DESC  CKScene;
class KAPSUL_DESC  CKCamera;
//class KAPSUL_DESC  Vertex;
class KAPSUL_DESC  CKImage;
class KAPSUL_DESC  KColor;
class KAPSUL_DESC  CKMesh;
class KAPSUL_DESC  CKSegment;
class KAPSUL_DESC  CKShape;
class KAPSUL_DESC  CKSkeleton;
class KAPSUL_DESC  VertBuf;
class KAPSUL_DESC  CKBone;
class KAPSUL_DESC  CKPlan;
class KAPSUL_DESC  CKTexture;

#include <math.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

//#include "KDirectInput8.h"

#include "CKImage.h"
#include "gl/glext.h"
#include "Resource.h"

// Entity manager

#include "KEntityManager.h"
#include "KHashTable.h"
#include "KLocalization.h"
#include "Vertex.h"
#include "VertBuf.h"
#include "KObjectBase.h"
#include "VertBuf.h"
#include "KPolygon.h"
#include "KMatrix.h"
#include "KTexture.h"
#include "KCamera.h"
#include "KBspTree.h"
#include "KMesh.h"
#include "KBone.h"
#include "KSkeleton.h"
#include "KPatch.h"
#include "KSegment.h"
#include "KSkyBox.h"
#include "KUndoRedoEntry.h"
#include "KUndoRedo.h"
#include "KEntity.h"
#include "KSceneBase.h"  
#include "KSceneSelection.h"
#include "KSceneOperation.h"
#include "KScene.h"
#include "KPlan.h"
//#include "KPlugin.h"

#include "KShape.h"
#include "KFilePlugin.h"
#include "KScenePlugin.h"
#include "KPluginManager.h"
#include "KOption.h"
#include "KBoundBox.h"
#include "KOctree.h"
#include "KOctreeNode.h"
#include "KTextureSpace.h"
#include "KTextureSpacePacker.h"

#include "KGenericMesh.h"

#include "KUtils.h"
#include "KRenderer.h"




// xml
#include "xmlwrapper\init.h"
#include "xmlwrapper\tree_parser.h"
#include "xmlwrapper\node.h"

// font
#include "KFontManager.h"

// -- Selection Structure -----------------------------------------------------


// -- Bitmap struct



// list files struct
class PackListFiles
{
public:
	CString FileName;
	unsigned int Size;
	CTime Date;
	bool	IsFile;
public:
	PackListFiles() {};
	PackListFiles(CString _FileName,unsigned int _Size,CTime _Date,bool _IsFile)
	{
		FileName=_FileName;
		Size=_Size;
		Date=_Date;
		IsFile=_IsFile;
	}

	~PackListFiles() {};

};
//#include "KThumbListView.h"

/*
#include "KFileDialog.h"

#include "KFile.h"
*/


#endif
