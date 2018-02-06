class __declspec( dllexport )  GenericLib;
class __declspec( dllexport )  OGLView;
class __declspec( dllexport )  Bone;
class __declspec( dllexport )  Desk;
class __declspec( dllexport )  Emitter;
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
class __declspec( dllexport )  KeyFrame;
class __declspec( dllexport )  CMaps;
class __declspec( dllexport )  KPolygon;
class __declspec( dllexport )  CBSPTree;
class __declspec( dllexport )  CKPatch;
//class __declspec( dllexport )  KOption;
class __declspec( dllexport )  CKBoundBox;
class __declspec( dllexport )  CKOctree;
class __declspec( dllexport )  CKOctreeNode;
class __declspec( dllexport )  CTextureSpace;
class __declspec( dllexport )  CTextureSpaceEntry;
class __declspec( dllexport )  CTextureSpacePacker;
class __declspec( dllexport )  CSHBrowseDlg;
class __declspec( dllexport )  CGenericObjects;
class __declspec( dllexport )  CKSlid;
class __declspec( dllexport )  CPaintZone;


#include <math.h>
#include <gl/glu.h>
#include <gl/gl.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>

#include "font\font.h"
#include "font\gltga.h"
#include "font\tga.h"
#include "font\utility.h"
#include "glext.h"

#include "Resource.h"

#include "SelectCam.h"

#include "Polygon.h"
#include "Vertex.h"
#include "Matrix.h"
#include "PrivateData.h"
#include "Texture.h"
#include "Maps.h"
#include "Camera.h"
#include "Object.h"
#include "Bone.h"
#include "Skeletton.h"
#include "VertBuf.h"
#include "KPatch.h"
#include "Light.h"
#include "KSegment.h"
#include "Face.h"
#include "SkyBox.h"
#include "UndoRedoEntry.h"
#include "UndoRedo.h"
#include "Desk.h"  

#include "OGLView.h"  
#include "Selection.h"

#include "Maths.h"
#include "Plan.h"
#include "GenericLib.h"

#include "Shape.h"
#include "LibContainer.h"
#include "KOption.h"


#include "csg.h"
#include "KBoundBox.h"
#include "KOctree.h"
#include "KOctreeNode.h"
#include "TextureSpace.h"
#include "TextureSpacePacker.h"

#include "NumSpinCtrl.h"
#include "NumEdit.h"
#include "HyperLink.h"
#include "InplaceCtrls.h"
#include "SHBrowseDlg.h"
#include "ListBoxEx.h"
#include "RollupCtrl.h"
#include "GenericObjects.h"
#include "KSlid.h"
#include "PaintZone.h"
//#include "base 3D\KOption.h"
#include "utils.h"

#include "bsptree.h"
