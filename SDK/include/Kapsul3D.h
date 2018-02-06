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

// -- Vues edition desk --------------------------------------------------------

#define VIEW_DESK 16
#define VIEW_TOP 17
#define VIEW_FRONT 18
#define VIEW_LEFT 19
#define VIEW_BOTTOM 20
#define VIEW_BACK 21
#define VIEW_RIGHT 22
#define VIEW_USER 23
#define VIEW_CAMERA 24

// -- Vue lofter ---------------------------------------------------------------

#define VIEW_LOFTER 32

#define VIEW_SCALETOP 33
#define VIEW_SCALERIGHT 34
#define VIEW_TWIST 35
#define VIEW_FITTOP 36
#define VIEW_FITRIGHT 37
#define VIEW_PREVIEW 38

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
#define EDIT_OBJECTUNIFY 27
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

// -- Sens ---------------------------------------------------------------------
#define SENS_DROITE 0
#define SENS_HAUT 1
#define SENS_GAUCHE 2
#define SENS_BAS 3

#define SENS_HORZ 4
#define SENS_VERT 8


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

#define EDIT_PLUGINCREATION 101
#define EDIT_PLUGINMODIF 102


#define SHPSTL_SEL 1
#define SHPSTL_SHP 2

#define PLUGIN_CREATION 1001
#define PLUGIN_TEXTURE 1002
#define PLUGIN_MODIF 1003

#define PLUGIN_CAMERA 1
#define PLUGIN_OBJECT 2
#define PLUGIN_SHAPE 4
#define PLUGIN_PARTICLE 8
#define PLUGIN_SKELETTON 16
#define PLUGIN_LIGHT 32
#define PLUGIN_GRID 64
#define PLUGIN_AXIS 128
#define PLUGIN_ENTITY 256
#define PLUGIN_PATCH 512

#define PLUGIN_ALL PLUGIN_CAMERA|PLUGIN_OBJECT|PLUGIN_SHAPE|PLUGIN_PARTICLE|PLUGIN_SKELETTON|PLUGIN_LIGHT|PLUGIN_GRID|PLUGIN_AXIS|PLUGIN_ENTITY|PLUGIN_PATCH
#define PLUGIN_NONE 0

#define PLUGIN_PATH 2004
#define PLUGIN_MATERIAL 2005
#define PLUGIN_FILE 2006
#define PLUGIN_MAPPING 2008
#define PLUGIN_OTHER 2009


#define STAT_OBJECT 1
#define STAT_CAMERA 2
#define STAT_SHAPE 4
#define STAT_PARTICLE 8
#define STAT_LIGHT 16
#define STAT_SKELETTON 32

#define STAT_ALL STAT_OBJECT|STAT_CAMERA|STAT_SHAPE|STAT_PARTICLE|STAT_LIGHT|STAT_SKELETTON


// -- Sélection modes - bt de selection - mode de creation ---------------------

#define MODE_WINDOW 1
#define MODE_SEGMENT 2
#define MODE_FACE 3
#define MODE_OBJECT 4
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
#define PRIM_OBJECT 4

// boolean

#define BOOL_INFIRST 1
#define BOOL_INSECOND 2
#define BOOL_INTWICE 3
//#define MODE_

// type de segment dans le path

#define PATHSEG_PATH 1
#define PATHSEG_SCALE 2
#define PATHSEG_TWIST 3
#define PATHSEG_FIT 4

// type de buffer

#define BUFFER_PATH 1
#define BUFFER_POLY 2
#define BUFFER_OBJECT 3
#define BUFFER_IK 4
#define BUFFER_IKROOT 5
#define BUFFER_IKORIGIN 6
#define BUFFER_IKROOTORIGIN 7

// type de vertex dans un segment

#define SEGDEB 1
#define SEGFIN 2

// type de selection

#define SELECT_CROSSING 1
#define SELECT_WINDOW 2

// type de poly poly->path

#define POLYPATH_EXT 1
#define POLYPATH_FITX 2
#define POLYPATH_FITY 3

// il le fallait bien...
#define PI 3.1415926535897932384626433832795

// -- IK -----------------------------------------------------------------------
#define IK_MAXCNX 10        // nb max cd cnx pere->fils


// -- Mémoire ------------------------------------------------------------------

// entité minimale d'allocation mémoire

#define MEM_SEG_ENT 10
#define MEM_FENCESEG_ENT 10
#define MEM_BONE_ENT 20
#define MEM_KEYFRAME_ENT 10
#define MEM_MATERIAL_ENT 10
#define MEM_OBJECT_ENT 10
#define MEM_PATH_ENT 10

// -- Min/Max/Scale segs -------------------------------------------------------

#define SEG_MIN_NGON 3
#define SEG_MAX_NGON 1000
#define SEG_SCALE_NGON 1

#define SEG_MIN_ARC 3
#define SEG_MAX_ARC 1000
#define SEG_SCALE_ARC 1

#define SEG_MIN_STAR 6
#define SEG_MAX_STAR 1000
#define SEG_SCALE_STAR 2

// -- Infos --------------------------------------------------------------------

#define INFOS_PERCENT   1
#define INFOS_ANGLE     2
#define INFOS_TRANSLATE 4

// -- Keyframe -----------------------------------------------------------------

#define KEYFRAME_IK     1



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


class GenericLib;
class OGLView;
class Bone;
class Desk;
//class Emitter;
class Particle;
class Selection;
class Camera;
class Face;
class Vertex;
class GenericThread;
class CImage;
class IniFile;
class KColor;
class KDKFile;
class Material;
class Math;
class Object;
class Particle;
//class Path;
class Segment;
class Shape;
class Skeletton;
class VertBuf;
class Script;
class Light;
class Bone;
class Plan;
class Matrix;
//class KeyFrame;
class ToolBarWarp;



class __declspec( dllexport )  GenericLib;
class __declspec( dllexport )  OGLView;
class __declspec( dllexport )  Bone;
class __declspec( dllexport )  Desk;
//class __declspec( dllexport )  Emitter;
class __declspec( dllexport )  Particle;
class __declspec( dllexport )  Selection;
class __declspec( dllexport )  Camera;
class __declspec( dllexport )  Face;
class __declspec( dllexport )  Vertex;
class __declspec( dllexport )  GenericThread;
class __declspec( dllexport )  CImage;
class __declspec( dllexport )  IniFile;
class __declspec( dllexport )  KColor;
class __declspec( dllexport )  KDKFile;
class __declspec( dllexport )  Material;
class __declspec( dllexport )  Math;
class __declspec( dllexport )  Object;
class __declspec( dllexport )  Particle;
class __declspec( dllexport )  Segment;
class __declspec( dllexport )  Shape;
class __declspec( dllexport )  Skeletton;
class __declspec( dllexport )  VertBuf;
class __declspec( dllexport )  Script;
class __declspec( dllexport )  Light;
class __declspec( dllexport )  Bone;
class __declspec( dllexport )  Plan;
class __declspec( dllexport )  CQuat;
class __declspec( dllexport )  CMaps;
class __declspec( dllexport )  CPrivateData;

// -- Messages perso ----------------------------------------------------------

#define WM_GETSTATUS WM_USER+1
#define WM_DRAWSCENE WM_USER+2
#define WM_SETSTATUS WM_USER+3
#define WM_GETPANELHEIGHT WM_USER+4
#define WM_GETKNAME WM_USER+5
#define WM_SETPLUGIN WM_USER+6
#define WM_GETCTKEYS WM_USER+7
#define WM_SETMOUSECURSOR WM_USER+8

// -- Selection ---------------------------------------------------------------

#define SELECT_SINGLE 101
#define SELECT_FENCE 102
#define SELECT_QUAD 103
#define SELECT_CIRCLE 104

#define SELECT_VERTEX 201
#define SELECT_FACE 202
#define SELECT_WHOLE 203
#define SELECT_SEGMENT 204

// -- Plugins messages --------------------------------------------------------

#define KM_DKCHANGE 101
#define KM_OPEN 102
#define KM_CLOSE 103 
#define KM_KEYDOWN 104
#define KM_KEYUP 105
#define KM_LMOUSEDOWN 106
#define KM_LMOUSEUP 107
#define KM_MOUSEMOVE 108
#define KM_RMOUSEDOWN 109
#define KM_RMOUSEUP 110
#define KM_GETNAME 111 
#define KM_GETINFOS 112
#define KM_GETTYPE 113
#define KM_GETSECONDARYTYPE 114
#define KM_GETFILTER 115
#define KM_GETFILEDESC 116
#define KM_GETREADSUPPORT 117
#define KM_GETWRITESUPPORT 118
#define KM_WRITEFILE 119
#define KM_READFILE 120
#define KM_ISPROPERTY 121
#define KM_ISCREATING 122
#define KM_SETDESK 123
#define KM_GETBITMAP 124
#define KM_SETOBJECT 125
#define KM_DRAW 126
#define KM_SETVIEW 127
#define KM_MOVEWINDOW 128
#define KM_SAVEDESK 129
#define KM_OPTIONSCHANGE 130
#define KM_LOADDESK 131
#define KM_UNSETPLUGIN 132

#define KM_SETFRAME 133
#define KM_PREVKEY 134
#define KM_NEXTKEY 135
#define KM_DELKEY 136
#define KM_SETNBFRAMES 137

#define KM_UNDO 138
#define KM_REDO 139
#define KM_FREEUNDOREDO 140


// -- Undo --------------------------------------------------------------------

#define UNDO_CREATE 1
#define UNDO_MODIFY 2
#define UNDO_DELETE 3

// -- Object properties -------------------------------------------------------

#define PROP_FORCETRI 0x00000001

// -- Object Dirty Parameters -------------------------------------------------

#def    DIRTY_MAPPING 1
#define DIRTY_GEOM 2
#define DIRTY_COLOR 4


#endif
