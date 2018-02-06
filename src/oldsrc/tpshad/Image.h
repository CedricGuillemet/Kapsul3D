#if !defined(AFX_IMAGE_H__FC219AC2_441C_11D2_9D22_02608C8A0EC0__INCLUDED_)
#define AFX_IMAGE_H__FC219AC2_441C_11D2_9D22_02608C8A0EC0__INCLUDED_

/////////////////////////////////////////////////////////////////////////////
//
//            Image.h : interface of the CImage class
//
//   Classe maintenant un DIB et toutes les fonctions nécessaires
//                    au travail sur ce DIB
//
//                          Version 2.6
//
//         Par Philippe Mignard - philippe.mignard@mail.dotcom.fr
//
/////////////////////////////////////////////////////////////////////////////

// CImage travaille toujours en Win32
#define __WIN32__

/*--------------------------------------------------------------------------*//*

-> Définitions à ajouter au fichier stdafx.h du projet pour activer les fonctions:

#define CIMAGE_NO_MFC		// Désactive l'utilisation des MFC. Automatique si le projet est "Single Threaded"

#define CIMAGE_DRAW			// Active la fonction de dessin du bitmap.
#define CIMAGE_CHANNEL		// Permet d’activer la fonction de sélection et d’isolement d’un canal RVB.
#define CIMAGE_CONTROLE		// Active les fonctions permettant d’ajuster la lumière et le contraste...
#define CIMAGE_ROTATION		// Active les fonctions de rotation et de miroir horizontal et vertical du bitmap.
#define CIMAGE_NEGATIVE		// Active la fonction d’inversion des couleurs (passage en négatif).
#define CIMAGE_DITHERING	// Active toutes les fonctions permettant le dithering.
#define CIMAGE_CLIPBOARD	// Active les fonctions de copier/coller dans le presse-papier.
#define CIMAGE_SERIALIZE	// Active la possiblité de sauver l’image au format brut (Serialize) dans un Carchive.
#define CIMAGE_LOADFILE		// Active toutes les fonctions nécessaires au chargement d’une image à partir du disque.
#define CIMAGE_SAVEFILE		// Active toutes les fonctions nécessaires à la sauvegarde d’une image sur disque.
#define CIMAGE_EFFECTS_24	// Active les fonctions de filtres pour effets spéciaux sur images en 24 bits.


-> Définition nécessaires pour charger des images à partir des ressources:

#define CIMAGE_LDRSRC_BMP	// Windows/OS2 Bitmap (RLE inclus)
#define CIMAGE_LDRSRC_PCX	// ZSoft PCX
#define CIMAGE_LDRSRC_GIF	// Compuserve GIF
#define CIMAGE_LDRSRC_JPEG	// JPEG
#define CIMAGE_LDRSRC_TIFF	// Tagged Image File Format (TIFF)
#define CIMAGE_LDRSRC_TGA	// TrueVision Targa
#define CIMAGE_LDRSRC_PNG	// Portable Network Graphic (PNG)


-> Définition nécessaires pour utiliser les formats de fichiers de la librairie externe

#define CIMAGE_USE_JPEG		// JPEG
#define CIMAGE_USE_TIFF		// Tagged Image File Format (TIFF)
#define CIMAGE_USE_PNG		// Portable Network Graphic (PNG)

*//*---------------------------------------------------------------------------*/

#if defined(CIMAGE_LDRSRC_JPEG) && !defined(CIMAGE_USE_JPEG)
	#define CIMAGE_USE_JPEG
#endif
#if defined(CIMAGE_LDRSRC_TIFF) && !defined(CIMAGE_USE_TIFF)
	#define CIMAGE_USE_TIFF
#endif
#if defined(CIMAGE_LDRSRC_PNG) && !defined(CIMAGE_USE_PNG)
	#define CIMAGE_USE_PNG
#endif

#if defined(CIMAGE_DRAW)
	#pragma comment(lib, "vfw32.lib" ) // Video for Windows
#endif

#if defined(CIMAGE_USE_JPEG) || defined(CIMAGE_USE_TIFF) || defined(CIMAGE_USE_PNG)
	#if defined(CIMAGE_USE_JPEG)
		extern "C"
		{
			#undef FAR
			#include <jpeglib.h> // Déclarations pour le JPEG
		}
	#endif
	#if defined(CIMAGE_USE_TIFF)
		extern "C"
		{
			#include <tiffiop.h>
			#include <tif_msrc.h>
		}
	#endif
	#if defined(CIMAGE_USE_PNG)
		extern "C"
		{
			#include <png.h>
		}
	#endif
	// Choix de la libraire à inclure
	#if defined(_DEBUG)
		#if defined(_MT)
			#if defined(_DLL)
				#pragma comment(lib, "ImageLibDMTD.lib" ) // Debug MultiThreaded DLL
			#else
				#pragma comment(lib, "ImageLibDMT.lib" ) // Debug MultiThreaded
			#endif
		#else
			#pragma comment(lib, "ImageLibD.lib" ) // Debug Single-Threaded
			#define CIMAGE_NO_MFC
		#endif
	#else
		#if defined(_MT)
			#if defined(_DLL)
				#pragma comment(lib, "ImageLibMTD.lib" ) // Release MultiThreaded DLL
			#else
				#pragma comment(lib, "ImageLibMT.lib" ) // Release MultiThreaded
			#endif
		#else
			#pragma comment(lib, "ImageLib.lib" ) // Release Single-Threaded
			#define CIMAGE_NO_MFC
		#endif
	#endif
#endif

//----------------------------------------------------------------
//                     Définitions publiques
//----------------------------------------------------------------

// Définitions pour la procédure de dessin:
	// Réalize la palette avant de dessiner
#define DIB_DRAW_SETPALETTE					1L
	// Force la palette en tant que Background
#define DIB_DRAW_PALBACKGROUND				2L
	// Centre horizontalement le bitmap dans la zone donnée
#define DIB_DRAW_CENTER_HORZ				4L
	// Centre verticalement le bitmap dans la zone donnée
#define DIB_DRAW_CENTER_VERT				8L
	// Autorise l'agrandissement en X du bitmap
#define DIB_DRAW_STRETCH_EXPANDX			16L
	// Autorise la réduction en X du bitmap
#define DIB_DRAW_STRETCH_REDUCEX			32L
	// Autorise l'agrandissement en Y du bitmap
#define DIB_DRAW_STRETCH_EXPANDY			64L
	// Autorise la réduction en Y du bitmap
#define DIB_DRAW_STRETCH_REDUCEY			128L
	// Garde le rapport X/Y lors de l'agrandissement ou de la réduction
#define DIB_DRAW_KEEP_RATIO					256L
	// Utilise le GDI au lieu de Video For Windows pour dessiner
#define DIB_DRAW_USE_GDI					512L
	// Clip la région à dessiner -> le bitmap ne peut pas dépasser cette dimension
#define DIB_DRAW_CLIP						1024L
	// Précise si le bitmap doit être dessiné en transparent si le couleur transparente est valide
#define DIB_DRAW_TRANSPARENT				2048L
	// Indique que l'on est en train d'imprimer. Inutile en MFC car déterminé par pDC->IsPrinting()
#define DIB_DRAW_PRINTING					4096L

// Définitions des canaux RVB (pour la fonction SelectChannelRVB):
#define CANALRVB_ROUGE						0
#define CANALRVB_VERT						1
#define CANALRVB_BLEU						2

// Définitions de matrices pour filtres effets spéciaux 24 bits. Def = nKoef,nBias,nRows,...Matrice...
// Flou normal
#define FILTER_BLUR_NORMAL					"14,0,3, 1,2,1, 2,2,2, 1,2,1"
// Flou par moyenne 3x3
#define FILTER_BLUR_MEAN_3x3				"10,0,3, 1,1,1, 1,2,1, 1,1,1"
// Flou par moyenne 5x5
#define FILTER_BLUR_MEAN_5x5				"26,0,5, 1,1,1,1,1, 1,1,1,1,1, 1,1,2,1,1, 1,1,1,1,1, 1,1,1,1,1"
// Flou par moyenne 7x7
#define FILTER_BLUR_MEAN_7x7				"52,0,7, 1,1,1,1,1,1,1, 1,1,1,1,1,1,1, 1,1,1,1,1,1,1, 1,1,1,4,1,1,1, 1,1,1,1,1,1,1, 1,1,1,1,1,1,1, 1,1,1,1,1,1,1"
// Adoucissement faible
#define FILTER_SOFTEN_LIGHT					"97,0,3, 6,12,6, 12,25,12, 6,12,6"
// Adoucissement moyen
#define FILTER_SOFTEN_MEDIUM				"100,0,3, 10,10,10, 10,20,10, 10,10,10"
// Adoucissement fort
#define FILTER_SOFTEN_HEAVY					"99,0,3, 11,11,11, 11,11,11, 11,11,11"
// Renforcement contours (filtre passe haut 3x3)
#define FILTER_HIGH_PASS_3X3				"1,0,3,	-1,-1,-1, -1,9,-1, -1,-1,-1"
// Renforcement contours + flou (filtre passe haut 5x5)
#define FILTER_HIGH_PASS_5X5				"-7,0,5,	0,-1,-1,-1,0, -1,2,-4,2,-1, -1,-4,13,-4,-1, -1,2,-4,2,-1, 0,-1,-1,-1,0"
// Relief
#define FILTER_EMBOSS						"1,128,3, -1,0,0, 0,0,0, 0,0,1"
// Relief Est
#define FILTER_EMBOSS_EAST					"1,128,3, 1,0,-1, 2,0,-2, 1,0,-1"
// Relief Nord
#define FILTER_EMBOSS_NORTH					"1,128,3, -1,-2,-1, 0,0,0, 1,2,1"
// Relief Sud
#define FILTER_EMBOSS_SOUTH					"1,128,3, 1,2,1, 0,0,0, -1,-2,-1"
// Relief Ouest
#define FILTER_EMBOSS_WEST					"1,128,3, -1,0,1, -2,0,2, -1,0,1"
// Relief Nord Est
#define FILTER_EMBOSS_NORTHEAST				"1,128,3, 0,-1,-2, 1,0,-1, 2,1,0"
// Relief Nord Ouest
#define FILTER_EMBOSS_NORTHWEST				"1,128,3, -2,-1,0, -1,0,1, 0,1,2"
// Détection des bords fins
#define FILTER_EDGE_LIGHT					"1,0,3, 0,1,0, 1,-4,1, 0,1,0"
// Détection des bords moyens
#define FILTER_EDGE_MEDIUM					"1,0,3, -1,-1,-1, -1,8,-1, -1,-1,-1"
// Détection des bords grossier
#define FILTER_EDGE_HEAVY					"1,0,3, 1,-2,1, -2,4,-2, 1,-2,1"
// Détection des bords moyens (filtre de Laplace 3x3)
#define FILTER_EDGE_LAPLACE3				"1,0,3, 0,-1,0, -1,4,-1, 0,-1,0"
// Détection des bords -> Laplace 5x5
#define FILTER_EDGE_LAPLACE5				"1,0,5, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,24,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1"
// Détection des bords -> Laplace 5x5 Inversé
#define FILTER_EDGE_LAPLACE5INV				"1,0,5, 1,1,1,1,1, 1,1,1,1,1, 1,1,-24,1,1, 1,1,1,1,1, 1,1,1,1,1"
// Détection des bords horizontaux
#define FILTER_EDGE_HORZ					"1,0,3, -1,-1,-1, 2,2,2, -1,-1,-1"
// Détection des bords verticaux
#define FILTER_EDGE_VERT					"1,0,3, -1,2,-1, -1,2,-1, -1,2,-1"
// Détection des bords Diagonaux Gauche Haut -> Bas Droite
#define FILTER_EDGE_DIAGLH					"1,0,3, 2,-1,-1, -1,2,-1, -1,-1,2"
// Détection des bords Diagonaux Droite Haut -> Bas Gauche
#define FILTER_EDGE_DIAGRH					"1,0,3, -1,-1,2, -1,2,-1, 2,-1,-1"
// Renforcement du focus
#define FILTER_ENHANCED_FOCUS				"3,0,3, -1,0,-1, 0,7,0, -1,0,-1"
// Renforcement détail faible
#define FILTER_ENHANCED_DETAILS_LOW			"6,0,3, 0,-1,0, -1,10,-1, 0,-1,0"
// Renforcement détail fort
#define FILTER_ENHANCED_DETAILS_HIGH		"2,0,3, 0,-2,0, -2,10,-2, 0,-2,0"
// Réduction des impuretés
#define FILTER_REDUCE_JAGGIES				"15,0,5, 0,0,-1,0,0, 0,0,3,0,0, -1,3,7,3,-1, 0,0,3,0,0, 0,0,-1,0,0"

// Définitions des types d'images
typedef enum
	{
		IMG_TYPE_COL24,		// Millions de couleurs
		IMG_TYPE_COL256,	// 256 couleurs
		IMG_TYPE_COL16,		// 16 couleurs
		IMG_TYPE_NG256,		// 256 niveaux de gris
		IMG_TYPE_NG16,		// 16 niveaux de gris
		IMG_TYPE_NB,		// Noir et Blanc 1 bit
		IMG_TYPE_UNKNOWN,	// Type non connu ou image non valide
		IMG_TYPE_END		// Indique la fin des types d'images
	};

// Définitions des format de fichiers d'images sur disque
typedef enum
	{
		IMG_FORMAT_BMPWIN,	// Bitmap Windows BMP (DIB)
		IMG_FORMAT_BMPOS2,	// Bitmap BMP OS/2
		IMG_FORMAT_RLE,		// Bitmap Windows compressé méthode RLE
		IMG_FORMAT_PCX,		// Fichier PCX
		IMG_FORMAT_GIF,		// Fichier GIF
		IMG_FORMAT_JPEG,	// Fichier JPEG
		IMG_FORMAT_TIFF,	// Fichier TIFF
		IMG_FORMAT_TGA,		// Fichier Targa
		IMG_FORMAT_PNG,		// Fichier PNG (Portable Network Graphic)
		IMG_FORMAT_END		// Indique la fin des formats disponibles ou format inconnu
	};

// Définitions des types de compressions qu'il est possible de passer
//  en paramètre à une fonction de sauvegarde
typedef enum
	{
		IMG_COMPRESS_NONE,	// Aucune compression
		IMG_COMPRESS_RLE,	// Compression en RLE
		IMG_COMPRESS_LZW,	// Compression LZW
		IMG_COMPRESS_JPEG,	// Compression JPEG
		IMG_COMPRESS_FAX3,	// Compression CCITT FAX3
		IMG_COMPRESS_FAX4,	// Compression CCITT FAX4
		IMG_COMPRESS_END	// Fin des types de compression possible
	};

// Macros de transformations DPI vers PPM et inversement
#define DPI2PPM(a)							((int)((a/0.0254)+0.5))
#define PPM2DPI(a)							((double)(0.0254*a))


//----------------------------------------------------------------
//                     Définitions privées
//----------------------------------------------------------------

// Définition de WITHBYTES: arrondit une ligne de bits à l'octet
#define WIDTHBYTES(bits)					((((bits) + 31) >>5 ) << 2)

// Transformation de 3 valeurs RGB en niveau de gris (=luminance)
#define GRAYSCALE(r,g,b)					(int)(0.299*(double)r+0.587*(double)g+0.114*(double)b)

// Résolution par défaut d'un bitmap ne contenant pas d'info de résolution (en ppm)
#define DEFAULT_RES							2954

// Taille du buffer de sauvegarde sur disque
#define SIZE_SAVE_BUFFER					10240

// Marques de Headers
#define FORMAT_BMP							0x4d42
#define FORMAT_JFIF							"\xFF\xD8\xFF\xE0\x00\x10JFIF\x00"
#define FORMAT_PNG							"\x89\x50\x4E\x47\x0D\x0A\x1A\x0A"

// Conversion des WORD et DWORD de Big Endian vers Little Endian et Vice-versa
#define ENDIAN_WORD(a)						(((a&0xFF)<<8) | ((a&0xFF00)>>8))
#define ENDIAN_DWORD(a)						(((a&0xFF)<<24) | ((a&0xFF00)<<8) | ((a&0xFF0000)>>8) | ((a&0xFF000000)>>24))

// Compression/Décompression LZW (GIF)
#define MAX_LZW_STACKSIZE					4096
#define MAX_LZW_HASH_TABLE					5003
#define MAX_GIF_BITS						12

// Tags ds une image ds presse-papiers
#define CLIPEXTRA_MEM						100
#define CLIPEXTRA_HEADER					"##CIMAGE?EXTRAINFOS#"
#define CLIPEXTRA_TRANSPARENT				"T"

// Tags ds une image dumpée
#define DUMP_TAG_TRANSPARENT				0
#define DUMP_TAG_IMAGE						1


//----------------------------------------------------------------
//         Structures de formats de fichiers
//----------------------------------------------------------------

// Les Header sont tous définis à l'octet près
#pragma pack(1)

// Définition du Header d'un fichier type PCX (128 octets)
typedef struct
	{
		BYTE    yGriffe;
		BYTE    yVersion;
		BYTE    yCodage;
		BYTE    yBits;
		WORD    x1;
		WORD    y1;
		WORD    x2;
		WORD    y2;
		WORD    wHres;
		WORD    wVres;
		BYTE    yPalette[48];
		char    cBidon;
		char    cNbrPlanes;
		WORD    wBytesPerLine;
		WORD    wTypePalette;
		WORD    wShres;
		WORD    wSvres;
		char    dummy[54];
	}  TypeHeaderPCX;

// Définition du Header d'un fichier type TGA (Targa)
typedef struct
	{
		BYTE    IDLen;
		BYTE    ColorMapType;
		BYTE    ImageType;
		WORD    CMS_FirstColor;
		WORD    CMS_NbrColor;
		BYTE    CMS_MapBPP;
		WORD    IS_Xorg;
		WORD    IS_Yorg;
		WORD    IS_Width;
		WORD    IS_Height;
		BYTE    IS_BPP;
		BYTE    IS_Descriptor;
	}  TypeHeaderTGA;

// Définition du Header d'un fichier type GIF Global (le premier du fichier)
typedef struct
	{
		BYTE    szSignature[3];
		BYTE	szVersion[3];
		WORD	wScreenWidth;
		WORD	wScreenHeight;
		BYTE	cFlags;
		BYTE	cBackgroundColor;
		BYTE	cPixelAspectRatio;
	}  TypeHeaderGIFGlobal;

// Définition du Header d'un fichier type GIF Local (un par image)
typedef struct
	{
		BYTE	cId;
		WORD	wLeft;
		WORD	wTop;
		WORD	wWidth;
		WORD	wHeight;
		BYTE	cFlags;
	}  TypeHeaderGIFLocal;

#pragma pack()


//----------------------------------------------------------------
//      Définitions et structures pour le dithering
//----------------------------------------------------------------

#define ERROR_QUEUE_LENGTH					16
#define MAX_NODES							266817
#define MAX_TREE_DEPTH						8
#define NODES_IN_A_LIST						2048
#define MAX_DITHER_RGB						255
#define FORGET_GRAVITY						0
#define N_GRAVITY							2
#define W_GRAVITY							4
#define E_GRAVITY							6
#define S_GRAVITY							8
#define DITHER_CACHE_SHIFT					2

typedef struct DitherNodeInfoDef
	{
		double					fTotalRed;
		double					fTotalGreen;
		double					fTotalBlue;
		double					fQuantizationError;
		DWORD					dwNumberUnique;
		DWORD					dwColorNumber;
		BYTE					cId;
		BYTE					cLevel;
		BYTE					cCensus;
		struct DitherNodeInfoDef*	Parent;
		struct DitherNodeInfoDef*	Child[8];
	}  DitherNodeInfo;

typedef struct DitherNodesDef
	{
		DitherNodeInfo			Nodes[NODES_IN_A_LIST];
		struct DitherNodesDef*	Next;
	}  DitherNodes;

typedef struct
	{
		int						nRed;
		int						nGreen;
		int						nBlue;
	}  DitherErrorPacket;

typedef struct
	{
		DitherNodeInfo*			RootNode;
		WORD					wDepth;
		DWORD					dwColors;
		RGBQUAD					rgbColor;
		LPBITMAPINFO			biColorMap;
		double					fDistance;
		double					fPruningThreshold;
		double					fNextPruningThreshold;
		DWORD*					dwSquares;
		DWORD					dwNodes;
		DWORD					dwFreeNodes;
		DWORD					dwColorNumber;
		DitherNodeInfo*			NextNode;
		DitherNodes*			NodeQueue;
		BOOL					bDither;
		int						x;
		int						y;
		int*					nCache;
		BYTE*					cRangeLimit;
		DitherErrorPacket		Error[ERROR_QUEUE_LENGTH];
		double					fWeights[ERROR_QUEUE_LENGTH];
	}  DitherCubeInfo;


//----------------------------------------------------------------
//                 Définitions pour le JPEG
//----------------------------------------------------------------

#if defined(CIMAGE_USE_JPEG)

	// Déclarations communes
	METHODDEF(void) CImageJpegErrorExit(j_common_ptr pcinfo);

	// Déclarations pour la lecture
	METHODDEF(void) CImageJpegInitSource(j_decompress_ptr cinfo);
	METHODDEF(boolean) CImageJpegFillInputBuffer(j_decompress_ptr cinfo);
	METHODDEF(void) CImageJpegSkipInputData(j_decompress_ptr cinfo, long num_bytes);
	METHODDEF(void) CImageJpegTermSource(j_decompress_ptr cinfo);

	// Déclarations pour la sauvegarde
	METHODDEF(void) CImageJpegInitDest(j_compress_ptr cinfo);
	METHODDEF(boolean) CImageJpegEmptyOutputBuffer(j_compress_ptr cinfo);
	METHODDEF(void) CImageJpegTermDest(j_compress_ptr cinfo);

#endif

//----------------------------------------------------------------
//                 Définitions pour le PNG
//----------------------------------------------------------------

#if defined(CIMAGE_USE_PNG)

	// Déclarations communes
	void CImagePngError(png_structp pPng, png_const_charp ErrMsg);

	// Déclarations pour la lecture
	void CImagePngRead(png_structp pPng, png_bytep pData, unsigned int nLen);

	// Déclarations pour l'écriture
	void CImagePngWrite(png_structp pPng, png_bytep pData, unsigned int nLen);
	void CImagePngFlush(png_structp pPng);

#endif

typedef struct
	{
		BYTE*		pLoadBuffer;
		BYTE*		pEndBuffer;
		HANDLE		hFile;
	} PngCustomData;

//----------------------------------------------------------------
//----------------------------------------------------------------
//                       Classe CImage
//----------------------------------------------------------------
//----------------------------------------------------------------

#if !defined(CIMAGE_NO_MFC)
// En MFC, la classe dérive de CObject
class CImage : public CObject
{
	DECLARE_DYNCREATE(CImage)

#else
// Sinon, elle ne dérive de rien
class CImage
{

#endif

protected:
	BOOL SavePNG(HANDLE hFile);
	BOOL LoadPNG();
	BOOL SaveTIFF(HANDLE hFile, LPCTSTR szFileName, int nCompression);
	BOOL LoadTIFF();
	void HSLtoRGB(double fHue, double fSat, double fLum, BYTE* cRed, BYTE* cGreen, BYTE* cBlue);
	void RGBtoHSL(BYTE cRed, BYTE cGreen, BYTE cBlue, double* fHue, double* fSat, double* fLum);
	BOOL SaveJPEG(HANDLE hFile, int nQuality);
	BOOL LoadJPEG();
	BOOL m_bDumpImage;
	BOOL SaveGIF(HANDLE hFile);
	BOOL LoadGIF();
	int Min(int a, int b);
	void DitherHilbertCurve(DitherCubeInfo *pCubeInfo, LPBITMAPINFOHEADER BmSrcInfo, LPBITMAPINFO BiDestInfo, int nLevel, UINT nDirection);
	void DitherDither(DitherCubeInfo *pCubeInfo, LPBITMAPINFOHEADER BmSrcInfo, LPBITMAPINFO BmDestInfo, UINT nDirection);
	void DitherClosestColor(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo);
	BOOL DitherQuantize(UINT nNbrColors, BOOL bDither);
	DitherNodeInfo* DitherGetNodeInfo(DitherCubeInfo *pCubeInfo, UINT nId, UINT nLevel, DitherNodeInfo *pParentNode);
	void DitherPruneLevel(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo);
	void DitherPruneChild(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo);
	void DitherReduction(DitherCubeInfo *pCubeInfo, UINT nNbrColors);
	void DitherReduce(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo);
	void DitherDefineColormap(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo);
	void DitherDestroyCubeInfo(DitherCubeInfo *pCubeInfo);
	BOOL LoadTGA();
	BOOL SaveTGA(HANDLE hFile, int nCompression);
	BOOL FlushSaveBuffer(HANDLE hFile, BOOL bWrite=TRUE);
	BOOL WriteSaveBuffer(HANDLE hFile, LPVOID Buffer, DWORD nLen=1L);
	BOOL InitSaveBuffer();
	BOOL SaveRLE(HANDLE hFile);
	BOOL SavePCX(HANDLE hFile);
	BOOL SaveBMPOS2(HANDLE hFile);
	BOOL SaveBMPWIN(HANDLE hFile);
	BOOL LoadPCX();
	BOOL LoadBMP();
	int GetDefaultType(int nBits) const;
	BOOL DitherGrayScale();
	BOOL DitherExpand(int nNewType);

	DWORD m_dwTransparentColor;
	int m_nFileFormat;
	int m_nTypeImage;
	void* m_LoadBuffer;
	DWORD m_dwSaveBufferLen;

// Implementation
public:
	BOOL Effect24MatrixFilter(LPCTSTR szMatrice);
	BOOL LoadFromRessource(HINSTANCE hInst, LPCTSTR lpResourceName, int nFormat, LPCTSTR lpType);
#if !defined(CIMAGE_NO_MFC)
	BOOL LoadFromRessource(LPCTSTR lpResourceName, int nFormat, LPCTSTR lpType);
#endif
	BOOL AdjustSaturationAndHue(int nValueSat, int nValueHue);
	BOOL AdjustGamma(double fValue);
	BOOL CorrectColors(DWORD dwRouge, DWORD dwVert, DWORD dwBleu);
	BOOL IsDumped() const;
	BOOL UndumpImage();
	BOOL DumpImage();
	BOOL GetTransparentColor(DWORD* dwColor=NULL) const;
	void SetTransparentColor(DWORD dwColor, BOOL bSet = TRUE);
	void SetPixel(int x, int y, DWORD dwValue, LPBITMAPINFOHEADER BmInfo, int nColors=-1, int nScanWidth=0, BYTE* lpBits=NULL);
	DWORD GetPixel(int x, int y, LPBITMAPINFOHEADER BmInfo, int nColors=-1, int nScanWidth=0, BYTE* lpBits=NULL) const;
	void SelectChannelRVB(int nChannel);
	BOOL IsValid() const;
	BOOL PasteClipboard();
	BOOL PasteHandle(HGLOBAL hClipDIB, HGLOBAL hClipExtra);
	BOOL IsClipboardOK() const;
	BOOL VerifyHandle(HGLOBAL hClipDIB) const;
#if !defined(CIMAGE_NO_MFC)
	friend CArchive& AFXAPI operator >> (CArchive& ar, CImage &Img);
	friend CArchive& AFXAPI operator << (CArchive& ar, CImage const &Img);
#endif
	int GetFileFormat() const;
	BOOL SaveFile(LPCTSTR szFileName, int nFormat=IMG_FORMAT_BMPWIN, int nData1=NULL, int nData2=NULL);
	BOOL LoadFile(LPCTSTR szFileName);
	BOOL CopyToClipboard();
	BOOL CopyToHandle(HGLOBAL* hClipDIB, HGLOBAL* hClipExtra);
#if !defined(CIMAGE_NO_MFC)
	BOOL Init(LPCTSTR lpResourceName, int nType=IMG_TYPE_UNKNOWN);
#endif
	BOOL Init(HINSTANCE hInst, LPCTSTR lpResourceName, int nType=IMG_TYPE_UNKNOWN);
	BOOL Dither(int nNewType, BOOL bDither=TRUE);
	void SetType(int nType);
	int GetType() const;
	BOOL Rotate(int nAngle);
	BOOL Negative();
	BOOL HorizontalMirror();
	BOOL VerticalMirror();
	int GetBPP() const;
	BOOL AdjustContrast(int nValue);
	BOOL AdjustBrightness(int nValue);
	void SetRes(int nResX, int nResY);
	CImage& operator =(const HGLOBAL hSource);
	CImage& operator =(const CImage& Source);
	void Erase();
	int GetResY() const;
	int GetResX() const;
	int GetHeight() const;
	int GetWidth() const;
	BOOL Init(HGLOBAL hDib, int nType = IMG_TYPE_UNKNOWN);
#if !defined(CIMAGE_NO_MFC)
	void Draw(CDC* pDC, CRect rcDest, DWORD dwFlags=DIB_DRAW_SETPALETTE, CRect rcSrc=CRect(0,0,-1,-1));
#else
	void Draw(HDC hDC, RECT* rcDest, DWORD dwFlags=DIB_DRAW_SETPALETTE, RECT* rcSrc=NULL);
#endif
	CImage();
	virtual ~CImage();

#if defined(CIMAGE_SERIALIZE) && !defined(CIMAGE_NO_MFC)
	void Serialize(CArchive & ar);
#endif

#if defined(_DEBUG)  && !defined(CIMAGE_NO_MFC)
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	HGLOBAL m_hDib; // Handle du DIB maintenu par la classe (avec palette)

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_IMAGE_H__FC219AC2_441C_11D2_9D22_02608C8A0EC0__INCLUDED_)
