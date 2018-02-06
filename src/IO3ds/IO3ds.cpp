/*

	IOIO3ds.CPP
	TODO: Save texture info, fix the 1 byte shit

*/

#include "stdafx.h"
#include <Kapsul3D.h>
#include "IO3ds.h"

/*
	3DS chunks 
*/
#pragma pack(1)

typedef struct {
    word    id;
    dword   len;
} TChunkHeader, *PChunkHeader;

typedef struct
{
    word id;
    const char *name;
    void *fnc;
} Chunks;

#define IO3DS_LOADER_FORMAT		0x00000003	// To save version information in 3ds file
#define IO3DS_LOADER_KF_FORMAT  0x0005

enum {
    CHUNK_RGBF      = 0x0010,
    CHUNK_RGBB      = 0x0011,
	CHUNK_PERCENT   = 0x0030,
//    CHUNK_RBGB2     = 0x0012,       // ?? NOT HLS.
    CHUNK_PRJ       = 0xC23D,
    CHUNK_MLI       = 0x3DAA,
    CHUNK_MAIN      = 0x4D4D,
	CHUNK_VERSION   = 0x0002,
    CHUNK_EDIT3D    = 0x3D3D,
	CHUNK_MVERSION  = 0x3D3E,
	CHUNK_MSCALE	= 0x0100,
    CHUNK_BKGCOLOR  = 0x1200,
    CHUNK_AMBCOLOR  = 0x2100,
    CHUNK_OBJBLOCK  = 0x4000,
    CHUNK_TRIMESH   = 0x4100,
    CHUNK_VERTLIST  = 0x4110,
    CHUNK_FACELIST  = 0x4120,
    CHUNK_FACEMAT   = 0x4130,
    CHUNK_MAPLIST   = 0x4140,
    CHUNK_SMOOLIST  = 0x4150,
    CHUNK_TRMATRIX  = 0x4160,
    CHUNK_LIGHT     = 0x4600,
    CHUNK_SPOTLIGHT = 0x4610,
    CHUNK_CAMERA    = 0x4700,
    CHUNK_HIERARCHY = 0x4F00,
    CHUNK_VIEWPORT  = 0x7001,
    CHUNK_MATERIAL  = 0xAFFF,
    CHUNK_MATNAME   = 0xA000,
    CHUNK_AMBIENT   = 0xA010,
    CHUNK_DIFFUSE   = 0xA020,
    CHUNK_SPECULAR  = 0xA030,
	CHUNK_SHININESS = 0xA040,
	CHUNK_SHIN_STR  = 0xA041,
	CHUNK_TRANSPAR  = 0xA050,
	CHUNK_SHADING   = 0xA100,
    CHUNK_TEXTURE   = 0xA200,
    CHUNK_BUMPMAP   = 0xA230,
    CHUNK_MAPFILE   = 0xA300,
    CHUNK_KEYFRAMER = 0xB000,
	CHUNK_KFHEADER  = 0xB00A,
    CHUNK_AMBIENTKEY= 0xB001,
    CHUNK_TRACKINFO = 0xB002,
    CHUNK_TRACKOBJNAME  = 0xB010,
    CHUNK_TRACKPIVOT= 0xB013,
    CHUNK_TRACKPOS  = 0xB020,
    CHUNK_TRACKROTATE   = 0xB021,
    CHUNK_TRACKSCALE= 0xB022,
    CHUNK_OBJNUMBER = 0xB030,
    CHUNK_TRACKCAMERA = 0xB003,
    CHUNK_TRACKFOV  = 0xB023,
    CHUNK_TRACKROLL = 0xB024,
    CHUNK_TRACKCAMTGT = 0xB004,
    CHUNK_TRACKLIGHT  = 0xB005,
    CHUNK_TRACKLIGTGT = 0xB006,
    CHUNK_TRACKSPOTL  = 0xB007,
    CHUNK_FRAMES    = 0xB008
};

//------------------------------------------------------------------------------
Chunks ChunkNames[] = {
    {CHUNK_RGBF,        "RGB float",        NULL},
    {CHUNK_RGBB,        "RGB byte",         NULL},

    {CHUNK_PRJ,         "Project",          NULL},
    {CHUNK_MLI,         "Material Library", NULL},

    {CHUNK_MAIN,        "Main",             NULL},
	{CHUNK_VERSION,		"Version",			NULL},
    {CHUNK_EDIT3D,      "Mesh Section",		NULL},
	{CHUNK_MVERSION,	"Mesh Version",		NULL},
	{CHUNK_MSCALE,		"Mesh Scale",		NULL},
    {CHUNK_BKGCOLOR,    "Background color", NULL},
    {CHUNK_AMBCOLOR,    "Ambient color",    NULL},
    {CHUNK_OBJBLOCK,    "Object Block",     NULL},
    {CHUNK_TRIMESH,     "Tri-Mesh",         NULL},
    {CHUNK_VERTLIST,    "Vertex list",      NULL},
    {CHUNK_FACELIST,    "Face list",        NULL},
    {CHUNK_FACEMAT,     "Face material",    NULL},
    {CHUNK_MAPLIST,     "Mappings list",    NULL},
    {CHUNK_SMOOLIST,    "Smoothings",       NULL},
    {CHUNK_TRMATRIX,    "Matrix",           NULL},
    {CHUNK_LIGHT,       "Light",            NULL},
    {CHUNK_SPOTLIGHT,   "Spotlight",        NULL},
    {CHUNK_CAMERA,      "Camera",           NULL},
    {CHUNK_HIERARCHY,   "Hierarchy",        NULL},

    {CHUNK_VIEWPORT,    "Viewport info",    NULL},
    {CHUNK_MATERIAL,    "Material",         NULL},
    {CHUNK_MATNAME,     "Material name",    NULL},
    {CHUNK_AMBIENT,     "Ambient color",    NULL},
    {CHUNK_DIFFUSE,     "Diffuse color",    NULL},
    {CHUNK_SPECULAR,    "Specular color",   NULL},
    {CHUNK_TEXTURE,     "Texture map",      NULL},
    {CHUNK_BUMPMAP,     "Bump map",         NULL},
    {CHUNK_MAPFILE,     "Map filename",     NULL},

    {CHUNK_KEYFRAMER,   "Keyframer data",   NULL},
    {CHUNK_AMBIENTKEY,  "Ambient key",      NULL},
    {CHUNK_TRACKINFO,   "Track info",       NULL},
    {CHUNK_FRAMES,      "Frames",           NULL},
    {CHUNK_TRACKOBJNAME,"Track Obj. Name",  NULL},
    {CHUNK_TRACKPIVOT,  "Pivot point",      NULL},
    {CHUNK_TRACKPOS,    "Position keys",    NULL},
    {CHUNK_TRACKROTATE, "Rotation keys",    NULL},
    {CHUNK_TRACKSCALE,  "Scale keys",       NULL},
    {CHUNK_OBJNUMBER,   "Object number",    NULL},

    {CHUNK_TRACKCAMERA, "Camera track",             NULL},
    {CHUNK_TRACKCAMTGT, "Camera target track",      NULL},
    {CHUNK_TRACKLIGHT,  "Pointlight track",         NULL},
    {CHUNK_TRACKLIGTGT, "Pointlight target track",  NULL},
    {CHUNK_TRACKSPOTL,  "Spotlight track",          NULL},
    {CHUNK_TRACKFOV,    "FOV track",                NULL},
    {CHUNK_TRACKROLL,   "Roll track",               NULL}
    };

CKIo3ds::CKIo3ds()
{
}

CKIo3ds::~CKIo3ds()
{
}

CString CKIo3ds::GetName()
{
	return "3DStudio 1-4 I/O";
}
CString CKIo3ds::GetInfos()
{
	return "3DStudio 1-4 I/O";
}
CString CKIo3ds::GetFilter()
{
	return "*.3ds";
}
CString CKIo3ds::GetFileDescription()
{
	return "3DStudio 1-4";
}
CString CKIo3ds::GetFileExtension()
{
	return ".3ds";
}

bool CKIo3ds::SupportReading()
{
	return true;
}

bool CKIo3ds::SupportWriting()
{
	return true;
}
bool CKIo3ds::Read(CKScene *pScene,CString FullFilePath)
{
	m_Scene = pScene;
	pMesh=NULL;
	curTexMatIndex = -1;
	CleanUp();

	m_Option = (CKOption*)GetGOption();	//To be used for texture path

	return Load3ds(FullFilePath.GetBuffer(0));		
}
bool CKIo3ds::Write(CKScene *pScene,CString FullFilePath)
{
	m_Scene = pScene;
	pMesh=NULL;
	curTexMatIndex = -1;
	CleanUp();

	return SaveTo3ds(FullFilePath.GetBuffer(0)); //Did everything went right ?
}





/*
    Tmp Material Class
*/


/*
  --- IMPORTANT --- This func should be called to clean up before a new loading occours
*/
void CKIo3ds::CleanUp()
{
 value			= false;
 f				= NULL;
 p				= 0;
 currentObject  = -1;
 curTexMatIndex = -1;
 ind			= 0;
 szTmpNameContainer.Empty();

 matArray.SetSize(0);
 matArray.FreeExtra();
}


//CTmpMaterial *FindMaterialByName(CString szMatName);
//void ChunkReader(int ind, long p);

void CKIo3ds::SkipReader( int ind, long p)
{
}

void CKIo3ds::VersionReader( int ind, long p)
{
 long sVersion = 0;

 if(fread(&sVersion,sizeof(sVersion),1,f) != 1)
	 return;
}

void CKIo3ds::MeshVersionReader( int ind, long p)
{
 long sVersion = 0;

 if(fread(&sVersion,sizeof(sVersion),1,f) != 1)
	 return;
}

void CKIo3ds::MasterScaleReader( int ind, long p)
{
 float fScale = 0.0f;

 if(fread(&fScale,sizeof(fScale),1,f) != 1)
	 return; 
}

void CKIo3ds::RGBFReader ( int ind, long p)
{
    float c[3];
    if (fread(&c, sizeof(c), 1, f) != 1) return;
}

void CKIo3ds::RGBBReader ( int ind, long p)
{
    byte c[3];
    if (fread(&c, sizeof(c), 1, f) != 1) return;
}

void CKIo3ds::ASCIIZReader ( int ind, long p,CString &Name)
{
    char c;

	Name="";
    while ( (c = fgetc(f)) != EOF && c != '\0')
        Name += c;

	//AfxMessageBox(Name);
}

/*
  BugFix By Dexter of Bug #110
*/
void CKIo3ds::ObjBlockReader ( int ind, long p)
{
	ASCIIZReader(ind,p,szTmpNameContainer);
    ChunkReader(ind,p);
}

void CKIo3ds::TriangularMeshReader( int ind, long p)
{
     pMesh = m_Scene->AddMesh();
	 if(pMesh->Prev)
		 pMesh->Prev->UpdateMesh();
	 

     m_Scene->NextMesh->Name = szTmpNameContainer;
     ChunkReader(ind,p);
}

void CKIo3ds::VertListReader ( int ind, long p)
{
    word nv;
    float c[3];
    int i;

	value=true;
    if (fread(&nv, sizeof(nv), 1, f) != 1) return;

    m_Scene->NextMesh->AllocatePoly(0,(int)nv);
    i=0;
    while (nv-- > 0)
    {
        if (fread(&c, sizeof(c), 1, f) != 1) return;

        m_Scene->NextMesh->pv[i].x=c[0];
        m_Scene->NextMesh->pv[i].y=c[1];
        m_Scene->NextMesh->pv[i].z=c[2];
        i++;

    }
}

void CKIo3ds::FaceListReader ( int ind, long p)
{
    word nv;
    word c[3];
    word flags;
    int i;

    if (fread(&nv, sizeof(nv), 1, f) != 1) return;

    m_Scene->NextMesh->AllocatePoly((int)nv,0);
    i=0;
    while (nv-- > 0) {
        if (fread(&c, sizeof(c), 1, f) != 1) return;
        if (fread(&flags, sizeof(flags), 1, f) != 1) return;

	    m_Scene->NextMesh->pl[i].Allocate(m_Scene->NextMesh,1,3); 
        m_Scene->NextMesh->pl[i].nbvert[0]=(int)c[0];
        m_Scene->NextMesh->pl[i].nbvert[1]=(int)c[1];
        m_Scene->NextMesh->pl[i].nbvert[2]=(int)c[2];

        m_Scene->NextMesh->pl[i].Tex[0][0]=(int)c[0];
        m_Scene->NextMesh->pl[i].Tex[0][1]=(int)c[1];
        m_Scene->NextMesh->pl[i].Tex[0][2]=(int)c[2];

        i++;
    }

    ChunkReader(ind,p);
}

void CKIo3ds::FaceMatReader ( int ind, long p)
{
	CTmpMaterial *pMat = NULL;
    //char test[256];
	CString test;
    word n, nf;
    int  i;

    ASCIIZReader(ind,p,test);
	pMat = FindMaterialByName(test);

	// Read number of faces to read
    if(fread(&n, sizeof(n), 1, f) != 1) 
		return;

	for(i = 0;i < n; i++) 
		if(fread(&nf, sizeof(nf), 1, f) == 1) 
			if(pMat)
			{
			 // We assign material texture to this face
			 m_Scene->NextMesh->pl[i].Maps[0] = pMat->pTexture;
			}

}

void CKIo3ds::MapListReader ( int ind, long p)
{
    short nv;
    float c1,c2;
    int i;

	
    if (fread(&nv, 2, 1, f) != 1) return;

	m_Scene->NextMesh->AllocateUV(0,nv);

    i=0;
    while (nv-- > 0) {
        if (fread(&c1, 4, 1, f) != 1) return;
        if (fread(&c2, 4, 1, f) != 1) return;

        m_Scene->NextMesh->puv[0][i].u=c1;
        m_Scene->NextMesh->puv[0][i].v=c2;

        i++;
    }
}

void CKIo3ds::SmooListReader ( int ind, long p)
{
    dword s;
    int i;

    while (ftell(f) < p) {
        if (fread(&s, sizeof(s), 1, f) != 1) return;
        for (i = 0; i < 32; i++)
            if (s & (1 << i))
                ;
    }
}

void CKIo3ds::TrMatrixReader( int ind, long p)
{
    float rot[9];
    float trans[3];

    if (fread(&rot, sizeof(rot), 1, f) != 1) 
		return;
    if (fread(&trans, sizeof(trans), 1, f) != 1) 
		return;
}

void CKIo3ds::LightReader( int ind, long p)
{
    float c[3];
    if (fread(&c, sizeof(c), 1, f) != 1) 
		return;

    ChunkReader(ind,p);
}

void CKIo3ds::SpotLightReader( int ind, long p)
{
    float c[5];
    if (fread(&c, sizeof(c), 1, f) != 1)
		return;
}

void CKIo3ds::CameraReader( int ind, long p)
{
    float c[8];
    Vertex src,dst;

    if (fread(&c, sizeof(c), 1, f) != 1) 
		return;
    {
        m_Scene->AddCam();
        src.x=c[0];
        src.y=c[1];
        src.z=c[2];

        dst.x=c[3];
        dst.y=c[4];
        dst.z=c[5];

        m_Scene->NextCam->SetDest(dst);
        m_Scene->NextCam->SetSource(src);

		//m_Scene->GenerateName(PLUGIN_CAMERA);
		m_Scene->NextCam->Name = szTmpNameContainer;
    }
}

CTmpMaterial *CKIo3ds::FindMaterialByName(CString szMatName)
{
 int size = matArray.GetSize();

 for(int k = 0;k < size;k++)
 {
  CTmpMaterial *pMat = (CTmpMaterial*)matArray.GetAt(k);

  if(pMat->szMatName.CompareNoCase(szMatName) == 0)
	return pMat;
 }

 return NULL;
}

void CKIo3ds::MatNameReader ( int ind, long p)
{
	/* Oke, guys, it works That way. For each material we have, 
	   we add it to an array with its name and texture definition,
	   to be used when texturing
	*/

    //char test[256];
	CString test;
    
	ASCIIZReader(ind,p,test);

    CTmpMaterial *tmpMat = new CTmpMaterial();
	tmpMat->pTexture  = m_Scene->FirstTexture;
	tmpMat->szMatName = test;

	curTexMatIndex=matArray.Add((CObject*)tmpMat);
}

void CKIo3ds::MapFileReader( int ind, long p)
{
    //char	 test[256];
	CString test;
	CString TexName;
	CKTexture *pTexture = NULL;
	
    ASCIIZReader(ind,p,test);
	TexName = GetFullPath(test);

	{
	 //Overwrite default texture in current mat definition
	 pTexture = m_Scene->AddTex(TexName);
	 m_Scene->NextTexture->Type = TEXTURE_FILE;

	 if (curTexMatIndex!=-1)
	 {
		 CTmpMaterial * pMat = (CTmpMaterial*)matArray.GetAt(curTexMatIndex);
		 pMat->pTexture = pTexture;
		 matArray.SetAt(curTexMatIndex,(CObject*)pMat);
	 }
	 
	}
}

void CKIo3ds::FramesReader( int ind, long p)
{
    dword c[2];
    if (fread(&c, sizeof(c), 1, f) != 1) return;
//    printf("%*s    Start: %ld, End: %ld\n",
//           ind, "", c[0], c[1]);
}

void CKIo3ds::TrackObjNameReader( int ind, long p)
{
    word w[2];
    word parent;
	//char temp[256];
	CString temp;

    ASCIIZReader(ind,p,temp);
    if (fread(&w, sizeof(w), 1, f) != 1) 
		return;
    if (fread(&parent, sizeof(parent), 1, f) != 1) 
		return;
}

void CKIo3ds::PivotPointReader( int ind, long p)
{
    float pos[3];

    if (fread(&pos, sizeof(pos), 1, f) != 1) 
		return;
}



        // NOTE THIS IS NOT A CHUNK, but A PART OF SEVERAL CHUNKS
void CKIo3ds::SplineFlagsReader( int ind,word flags)
{
    int i;
    float dat;

    for (i = 0; i < 16; i++) {
        static const char *flagnames[] = {
            "Tension",
            "Continuity",
            "Bias",
            "Ease To",
            "Ease From",
        };
        if (flags & (1 << i)) {
            if (fread(&dat, sizeof(dat), 1, f) != 1) return;
            if (i < sizeof(flagnames)/sizeof(*flagnames))
//                printf("%*s             %-15s = %f\n",
//                       ind, "", flagnames[i], dat);
                ;
            else
//                printf("%*s             %-15s = %f\n",
//                       ind, "", "Unknown", dat);
                ;
        }
    }
}

void CKIo3ds::TrackPosReader( int ind, long p)
{
    word n, nf;
    float pos[3];
    word unkown;
    word flags;

    fseek(f, 10, SEEK_CUR);
    if (fread(&n, sizeof(n), 1, f) != 1) return;
//    printf("%*sPosition keys: %d\n", ind, "", n);
    fseek(f, 2, SEEK_CUR);
    while (n-- > 0) {
        if (fread(&nf, sizeof(nf), 1, f) != 1) return;
        if (fread(&unkown, sizeof(unkown), 1, f) != 1) return;
        if (fread(&flags, sizeof(flags), 1, f) != 1) return;
//        printf("%*s  Frame %3d: Flags 0x%X\n", ind, "", nf, flags);
        SplineFlagsReader(ind,flags);
        if (fread(&pos, sizeof(pos), 1, f) != 1) return;
//        printf("%*s             X: %f, Y: %f, Z: %f\n",
//               ind, "", pos[0], pos[1], pos[2]);
    }
}

void CKIo3ds::TrackRotReader( int ind, long p)
{
    word n, nf;
    float pos[4];
    word unkown;
    word flags;

    fseek(f, 10, SEEK_CUR);
    if (fread(&n, sizeof(n), 1, f) != 1) return;
//    printf("%*sRotation keys: %d\n", ind, "", n);
    fseek(f, 2, SEEK_CUR);
    while (n-- > 0) {
        if (fread(&nf, sizeof(nf), 1, f) != 1) return;
        if (fread(&unkown, sizeof(unkown), 1, f) != 1) return;
        if (fread(&flags, sizeof(flags), 1, f) != 1) return;
//        printf("%*s  Frame %3d: Flags 0x%X\n", ind, "", nf, flags);
        SplineFlagsReader(ind,flags);
        if (fread(&pos, sizeof(pos), 1, f) != 1) return;
//        printf("%*s             Angle: %f§, X: %f, Y: %f, Z: %f\n",
//               ind, "", pos[0]*180.0/PI, pos[1], pos[2], pos[3]);
    }
}

void CKIo3ds::TrackScaleReader( int ind, long p)
{
    word n, nf;
    float pos[3];
    word unkown;
    word flags;

    fseek(f, 10, SEEK_CUR);
    if (fread(&n, sizeof(n), 1, f) != 1) return;
//    printf("%*sScale keys: %d\n", ind, "", n);
    fseek(f, 2, SEEK_CUR);
    while (n-- > 0) {
        if (fread(&nf, sizeof(nf), 1, f) != 1) return;
        if (fread(&unkown, sizeof(unkown), 1, f) != 1) return;
        if (fread(&flags, sizeof(flags), 1, f) != 1) return;
//        printf("%*s  Frame %3d: Flags 0x%X\n", ind, "", nf, flags);
        SplineFlagsReader(ind,flags);
        if (fread(&pos, sizeof(pos), 1, f) != 1) return;
//        printf("%*s            X: %f, Y: %f, Z: %f\n",
//               ind, "", pos[0], pos[1], pos[2]);
    }
}

void CKIo3ds::ObjNumberReader( int ind, long p)
{
    word n;

    if (fread(&n, sizeof(n), 1, f) != 1) return;
//    printf("%*sObject number: %d\n", ind, "", n);
}


// ------------------------------------


int CKIo3ds::FindChunk(word id) {
    int i;
    for (i = 0; i < NB23DSCHUNKS; i++)
        if (id == ChunkNames[i].id)
            return i;

		return -1;
}

// ------------------------------------

bool CKIo3ds::Dispatch(int id,int ind,long p)
{
    switch (id)
    {
    case CHUNK_RGBF:
        RGBFReader(ind,p);
        return true;
    case CHUNK_RGBB:
        RGBBReader(ind,p);
        return true;
    case CHUNK_OBJBLOCK:
        ObjBlockReader(ind,p);
        return true;
    case CHUNK_TRIMESH:
		TriangularMeshReader(ind,p);
		return true;
    case CHUNK_VERTLIST:
        VertListReader(ind,p);
        return true;
    case CHUNK_FACELIST:
        FaceListReader(ind,p);
        return true;
    case CHUNK_FACEMAT:
        FaceMatReader(ind,p);
        return true;
    case CHUNK_MAPLIST:
        MapListReader(ind,p);
        return true;
    case CHUNK_SMOOLIST:
        SmooListReader(ind,p);
        return true;
    case CHUNK_TRMATRIX:
        TrMatrixReader(ind,p);
        return true;
    case CHUNK_LIGHT:
        LightReader(ind,p);
        return true;
    case CHUNK_SPOTLIGHT:
        SpotLightReader(ind,p);
        return true;
    case CHUNK_CAMERA:
        CameraReader(ind,p);
        return true;
    case CHUNK_MATNAME:
        MatNameReader(ind,p);
        return true;
   case CHUNK_MAPFILE:
        MapFileReader(ind,p);
        return true;
    case CHUNK_FRAMES:
        FramesReader(ind,p);
        return true;
    case CHUNK_TRACKOBJNAME:
        TrackObjNameReader(ind,p);
        return true;
    case CHUNK_TRACKPIVOT:
        PivotPointReader(ind,p);
        return true;
    case CHUNK_TRACKPOS:
        TrackPosReader(ind,p);
        return true;
    case CHUNK_TRACKROTATE:
        TrackRotReader(ind,p);
        return true;
    case CHUNK_TRACKSCALE:
        TrackScaleReader(ind,p);
        return true;
    case CHUNK_OBJNUMBER:
        ObjNumberReader(ind,p);
        return true;
    case CHUNK_MATERIAL:
        ChunkReader(ind,p);
        return true;
	case CHUNK_VERSION:
		VersionReader(ind,p);
		return true;
	case CHUNK_MVERSION:
		MeshVersionReader(ind,p);
		return true;
	case CHUNK_MSCALE:
		MasterScaleReader(ind,p);
		return true;
    case CHUNK_TEXTURE:
		//curTexMatIndex = matArray.GetUpperBound();
		return false;
    case CHUNK_KEYFRAMER:
    case CHUNK_AMBIENTKEY:
    case CHUNK_TRACKINFO:
    case CHUNK_HIERARCHY:
    case CHUNK_VIEWPORT:
    case CHUNK_AMBIENT:
    case CHUNK_DIFFUSE:
    case CHUNK_SPECULAR:
    case CHUNK_BUMPMAP:
    case CHUNK_TRACKCAMERA:
    case CHUNK_TRACKCAMTGT:
    case CHUNK_TRACKLIGHT:
    case CHUNK_TRACKLIGTGT:
    case CHUNK_TRACKSPOTL:
    case CHUNK_TRACKFOV:
    case CHUNK_TRACKROLL:
    case CHUNK_PRJ:
    case CHUNK_MLI:
    case CHUNK_MAIN:
    case CHUNK_EDIT3D:
    case CHUNK_BKGCOLOR:
    case CHUNK_AMBCOLOR:
        return false;
    }

    return false;

}

void CKIo3ds::ChunkReader(int ind, long p)
{
    TChunkHeader h;
    int n;
    long pc;

    while (ftell(f) < p) {
        pc = ftell(f);
        if (fread(&h, sizeof(h), 1, f) != 1) 
			return;

        if (h.len == 0) 
			continue;

        n = FindChunk(h.id);
        if (n < 0) {
           /* if (Verbose)
                printf("%*sUnknown chunk: 0x%04X, offset 0x%lX, size: %d bytes.\n",
                       ind, "", h.id, pc, h.len);*/
            fseek(f, pc + h.len, SEEK_SET);
        } else {
			//AfxMessageBox(ChunkNames[n].name);
            pc = pc + h.len;
            if (!Dispatch(ChunkNames[n].id,ind+2,pc))
                ChunkReader( ind + 2, pc);

            fseek(f, pc, SEEK_SET);
        }
    }
}

bool CKIo3ds::Load3ds(char FileName[260])
{
    f = fopen(FileName, "rb");
    fseek(f, 0, SEEK_END);
    p = ftell(f);
    fseek(f, 0, SEEK_SET);
    WORD tst;
	fread(&tst,sizeof(WORD),1,f);
	if (tst!=0x4d4d) return false;

	fseek(f, 0, SEEK_SET);

	// Go!
    ChunkReader(0,p);

	if(pMesh)
		pMesh->UpdateMesh();

	fclose(f);

	CleanUp();

	return true;
}


/*
 Write support - By Dexter
*/

dword CKIo3ds::WriteTexInfo(FILE *f,CKTexture *pTexture)
{
 return 0;
}

void CKIo3ds::WriteMatList(FILE *f)
{
 byte			Rgb[3]; Rgb[0] = Rgb[1] = Rgb[2] = 3;
 short			pcData = 0;
 char			szMatName[15];
 TChunkHeader	ch;
 CKTexture *pTexture = m_Scene->FirstTexture;

 long  matStart  = 0;
 dword dwMatSize = 6;

 while(pTexture != NULL)
 {
  if(m_Scene->IsTextureStillUsed(pTexture))
  {
   matStart  = ftell(f);
   dwMatSize = 0;

   // We write it to material list, otherwise we skipp it
   sprintf(szMatName,"mat_%i",pTexture->TexID);

   ch.id  = CHUNK_MATERIAL;
   dwMatSize += ch.len = 6;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
		continue;

   // -> Write material name
   ch.id  = CHUNK_MATNAME;
   dwMatSize += ch.len = 7 + strlen(szMatName);

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
		continue;

   fputs(szMatName,f);
   fputc('\0',f);

   /* -> Write ambient color chunk
   ch.id  = CHUNK_AMBIENT;
   dwMatSize += ch.len = 15;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   ch.id  = CHUNK_RGBB;
   ch.len = 9;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   if(fwrite(&Rgb,sizeof(Rgb),1,f) != 1)
	   continue;

   // -> Write diffuse color chunk
   ch.id  = CHUNK_DIFFUSE;
   dwMatSize += ch.len = 15;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   ch.id  = CHUNK_RGBB;
   ch.len = 9;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   if(fwrite(&Rgb,sizeof(Rgb),1,f) != 1)
	   continue;

   // -> Write specular color chunk
   ch.id  = CHUNK_SPECULAR;
   dwMatSize += ch.len = 15;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   ch.id  = CHUNK_RGBB;
   ch.len = 9;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   if(fwrite(&Rgb,sizeof(Rgb),1,f) != 1)
	   continue;

   // -> Write shininess ratio percent
   ch.id  = CHUNK_SHININESS;
   dwMatSize += ch.len = 14;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   ch.id  = CHUNK_PERCENT;
   ch.len = 8;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   if(fwrite(&pcData,sizeof(pcData),1,f) != 1)
	   continue;

   // -> Write shininess strength
   ch.id  = CHUNK_SHIN_STR;
   dwMatSize += ch.len = 14;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   ch.id  = CHUNK_PERCENT;
   ch.len = 8;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   if(fwrite(&pcData,sizeof(pcData),1,f) != 1)
	   continue;

   // -> Write mat transparency ration
   ch.id  = CHUNK_TRANSPAR;
   dwMatSize += ch.len = 14;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   ch.id  = CHUNK_PERCENT;
   ch.len = 8;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;

   if(fwrite(&pcData,sizeof(pcData),1,f) != 1)
	   continue;

   // -> Write mat shading
   ch.id  = CHUNK_SHADING;
   dwMatSize += ch.len = 8;

   if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  continue;
	
   pcData = 3;
   if(fwrite(&pcData,sizeof(pcData),1,f) != 1)
	   continue;

   // -> Finally, we write our shit about textures
   dwMatSize += WriteTexInfo(f,pTexture);//*/

   // -> We update material size
   fseek(f,SEEK_SET,matStart);

   char Msg[10];
   sprintf(Msg,"%i",dwMatSize);
   //AfxMessageBox(Msg);
   ch.id  = CHUNK_MATERIAL;
   ch.len = dwMatSize;

   fwrite(&ch,sizeof(TChunkHeader),1,f);

   fseek(f,SEEK_END,0);
   
  }

  pTexture = pTexture->Next;
 }

}

bool CKIo3ds::DispatchSave(LPCTSTR szFileName)
{
 /*
  Behaviour:
   -> Write Main Chunk
    -> Write Version Chunk
    -> Write Editor Chunk
	   [ Write Object Chunks ]
	   -> Write Object Name Chunk
	    -> Write Trimesh Chunk
	     -> Write Vertex List Chunk
		 -> Write Face List Chunk
     -> Write Camera Chunks
   -> Update Main Chunk
 */

 TChunkHeader ch;

 dword dwFileSize = 0;
 dword dwEditPos  = 0;

 CKMesh *daMesh = NULL;
 CKCamera *daCam = NULL;

 int	k		  = 0;
 int    iObjCount = 0;
 int	iCamCount = 0;

 float  vVert[3];		//To store vertices
 word	vFace[3];		//To store faces
 word	fFlags;			//To store flags

 float  vCam[8];		//To store camera things

 long  sVersion = IO3DS_LOADER_FORMAT;	//To store version
 float fMasterScale = 1.0f;				//Default

 float UV[2];

 //Zero out this shit
 memset(&ch,0,sizeof(TChunkHeader));

 // -> Write Main Chunk
 ch.id  = CHUNK_MAIN;
 ch.len = sizeof(sVersion);

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	 return false;

 // -> Write Version Chunk (REQUIRED)
 ch.id  = CHUNK_VERSION;
 ch.len = sizeof(sVersion) + 6;

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	 return false;

 if(fwrite(&sVersion,sizeof(sVersion),1,f) != 1)
	 return false;

 // -> Write Edit3D Chunk
 ch.id  = CHUNK_EDIT3D;
 ch.len = 12 + sizeof(sVersion);

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	 return false;

 // -> Write Mesh Version Chunk (REQUIRED)
 ch.id  = CHUNK_MVERSION;
 ch.len = sizeof(sVersion) + 6;

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	 return false;

 if(fwrite(&sVersion,sizeof(sVersion),1,f) != 1)
	 return false;

 // -> Build a list of used materials(textures) Doesnt work well
 //WriteMatList(f);

 // -> Write Master Scale Chunk
 ch.id  = CHUNK_MSCALE;
 ch.len = sizeof(float) + 6;

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	 return false;

 if(fwrite(&fMasterScale,sizeof(fMasterScale),1,f) != 1)
	 return false;

 // -> Write Object Chunks
 for(daMesh = m_Scene->FirstMesh;daMesh != NULL;daMesh = daMesh->Next,iObjCount++)
 {
  word vertNum = daMesh->nb2vert;
  word faceNum = daMesh->nb2poly;

  dword dwVertListSize = 8 + vertNum * sizeof(vVert);
  dword dwFaceListSize = 8 + faceNum * 8;	//sizeof(word) + faceNum *(sizeof(word) * 4)) + sizeof(TChunkHeader);
  dword dwMapListSize  = 8 + vertNum * 8;

  ch.id  = CHUNK_OBJBLOCK;
  ch.len = 12 + dwMapListSize + dwVertListSize + dwFaceListSize + strlen(daMesh->Name) + 1;

  if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	  return false;

  fputs(daMesh->Name,f);
  if(fputc('\0',f) == EOF)		//Append NULL character as fputs wipes it out
	  return false;

  // -> Write Trimesh Chunk
  ch.id  = CHUNK_TRIMESH;
  ch.len = dwMapListSize + dwVertListSize + dwFaceListSize + 6;

  if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	  return false;

  // -> Write Vertlist Chunk
  ch.id  = CHUNK_VERTLIST;
  ch.len = dwVertListSize;

  if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	  return false;

  if(fwrite(&vertNum,sizeof(vertNum),1,f) != 1)
 	  return false;

  for(k = 0;k < vertNum;k++)
  {
   vVert[0] = daMesh->pv[k].x;	
   vVert[1] = daMesh->pv[k].y;	
   vVert[2] = daMesh->pv[k].z;	

   if(fwrite(&vVert,sizeof(vVert),1,f) != 1)
	   return false;
  }

  // -> Write Tex_Vert Chunk
  ch.id  = CHUNK_MAPLIST;
  ch.len = dwMapListSize;

  if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	  return false;

  if(fwrite(&vertNum,sizeof(vertNum),1,f) != 1)
	  return false;

  if (daMesh->puv[0]==NULL)
  {
	  for(k = 0;k < vertNum;k++)
	  {
	   UV[0] = 0;//
	   UV[1] = 0;//

	   if(fwrite(&UV,sizeof(UV),1,f) != 1)
		   return false;
	  }
  }
  else
  {
	  for(k = 0;k < vertNum;k++)
	  {
	   UV[0] = daMesh->puv[0][k].u;
	   UV[1] = daMesh->puv[0][k].v;

	   if(fwrite(&UV,sizeof(UV),1,f) != 1)
		   return false;
	  }
  }

  // -> Write Facelist Chunk
  ch.id  = CHUNK_FACELIST;
  ch.len = dwFaceListSize;

  if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	  return false;

  if(fwrite(&faceNum,sizeof(faceNum),1,f) != 1)
 	  return false;

  for(k = 0;k < faceNum;k++)
  {
   vFace[0] = daMesh->pl[k].nbvert[0];
   vFace[1] = daMesh->pl[k].nbvert[1];
   vFace[2] = daMesh->pl[k].nbvert[2];

   if(fwrite(&vFace,sizeof(vFace),1,f) != 1)
	   return false;

   if(fwrite(&fFlags,sizeof(word),1,f) != 1)
	   return false;
  }
 }

 // -> Write Camera Chunks
 for(daCam = m_Scene->FirstCam;daCam != NULL;daCam = daCam->Next,iCamCount++)
 {
  dword dwCameraSize = 6 + sizeof(vCam);

  ch.id  = CHUNK_OBJBLOCK;
  ch.len = 6 + dwCameraSize + strlen(daCam->Name) + 1;

  if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	  return false;

  fputs(daCam->Name,f);
  if(fputc('\0',f) == EOF)		//Append NULL character as fputs wipes it out
	  return false;

  // -> Write Camera CHUNK
  ch.id  = CHUNK_CAMERA;
  ch.len = dwCameraSize;

  if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	  return false;

  vCam[0] = daCam->Source.x;
  vCam[1] = daCam->Source.y;
  vCam[2] = daCam->Source.z;

  vCam[3] = daCam->Dest.x;
  vCam[4] = daCam->Dest.y;
  vCam[5] = daCam->Dest.z;

  vCam[6] = 1.0f;			// Back angle?
  vCam[7] = daCam->Fov;

  if(fwrite(&vCam,sizeof(vCam),1,f) != 1)
 	  return false;

 }

 // -> Keyframer chunk (REQUIRED)
 ch.id  = CHUNK_KEYFRAMER;
 dword kf_len = ch.len = 6 + 13; //Header + CHUNK_KFHEADER chunk (KEYFRAME GENERAL DATA)

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	 return false;

 // -> Keyframe general data subchunk (REQUIRED)
 ch.id  = CHUNK_KFHEADER;
 ch.len = 13;

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
 	 return false;

 short kfVers = IO3DS_LOADER_KF_FORMAT;

 if(fwrite(&kfVers,sizeof(kfVers),1,f) != 1)
 	 return false;

 fputc('\0',f);

 long anim_len = 30;

 if(fwrite(&anim_len,sizeof(anim_len),1,f) != 1)
 	 return false;

 dwFileSize = ftell(f);
 
 // -> Update Main Chunk
 ch.id  = CHUNK_MAIN;
 ch.len = dwFileSize - 6;

 fseek(f,0,SEEK_SET);
 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	  return false;


 // -> Update Version Chunk
 ch.id  = CHUNK_VERSION;
 ch.len = sizeof(sVersion) + 6;

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	 return false;

 if(fwrite(&sVersion,sizeof(sVersion),1,f) != 1)
	 return false;


 // -> Update Edit3D Chunk
 ch.id  = CHUNK_EDIT3D;
 ch.len = dwFileSize - 16 - kf_len;	//Minus version chunk size and main header

 if(fwrite(&ch,sizeof(TChunkHeader),1,f) != 1)
	 return false;

 return true;
}

bool CKIo3ds::SaveTo3ds(char FileName[260])
{
	f = NULL;

    f = fopen(FileName, "wb");
	if(!f)
		return false;

	// We extract file name only
    CString szFileName = FileName;
	szFileName.MakeReverse();
	szFileName = szFileName.SpanExcluding("\\/");
	szFileName.MakeReverse();


	bool value = DispatchSave(szFileName);
	/*
	if(!value)
		MessageBox(NULL,"There was an error while attemping to save to 3ds.","io3ds.dll",MB_OK);
*/
	fclose(f);

    return value;
}
