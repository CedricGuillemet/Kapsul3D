/////////////////////////////////////////////////////////////////////////////
//
// Image.cpp : implementation of the CImage class
//
//   Classe maintenant un DIB et toutes les fonctions nécessaires
//                    au travail sur ce DIB
//
//                          Version 2.6
//
//         Par Philippe Mignard - philippe.mignard@mail.dotcom.fr
//
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <windows.h>
#include <malloc.h>
#include <math.h>
#include <vfw.h> // Les fonctions DrawDib requièrent la bibliothèque 'vfw32'

#include "Image.h"

//////////////////////////////

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if	defined(CIMAGE_NO_MFC)
#define ASSERT(a);
#endif
/////////////////////////////////////////////////////////////////////////////
// CImage

#if !defined(CIMAGE_NO_MFC)
	IMPLEMENT_DYNCREATE(CImage, CObject)
#endif
/////////////////////////////////////////////////////////////////////////////
// CImage diagnostics

#if defined(_DEBUG) && !defined(CIMAGE_NO_MFC)
void CImage::AssertValid() const
{
	CObject::AssertValid();
}

void CImage::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
	dc << "[ CImage = " << (UINT)m_hDib << " ]";
}

#endif //_DEBUG && !CIMAGE_NO_MFC

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////

//===================================================================
//        Fonctions indispensables à la classe. Toujours activées (valides)
//===================================================================

// Init de la classe
CImage::CImage()
{
	m_hDib = NULL;
	m_LoadBuffer = NULL;
	m_nTypeImage = IMG_TYPE_UNKNOWN;
	m_nFileFormat = IMG_FORMAT_END;
	m_dwTransparentColor = NULL;
	m_bDumpImage = FALSE;
}

// Destruction de la classe -> Destruction du DIB et autres variables
CImage::~CImage()
{
	if(m_hDib)
		GlobalFree(m_hDib);

	if(m_bDumpImage && m_LoadBuffer)
		DeleteFile((LPCTSTR)m_LoadBuffer);

	if(m_LoadBuffer)
		free(m_LoadBuffer);
}

// Initialise le Dib avec un HGlobal (DIB fourni en entier)
// Retourne TRUE si l'init s'est bien passé
BOOL CImage::Init(HGLOBAL hDib, int nType)
{
	if(!hDib)	// Dib fourni non valide -> on le refuse
		return FALSE;

	Erase();  // Si Dib déjà existant -> on l'efface

	m_hDib=hDib;  // Affectation du nouveau Dib
	m_nTypeImage = nType;

	return TRUE;
}

#if !defined(CIMAGE_NO_MFC)
// Initialisation de CImage avec un bitmap en ressource, version MFC
BOOL CImage::Init(LPCTSTR lpResourceName, int nType)
{
	HINSTANCE hInst=AfxGetResourceHandle();
	return Init(hInst, lpResourceName, nType);
}
#endif

// Initialisation de CImage avec un bitmap en ressource
BOOL CImage::Init(HINSTANCE hInst, LPCTSTR lpResourceName, int nType)
{
	HRSRC hSrc = FindResource(hInst, lpResourceName, RT_BITMAP);
	BOOL bSuccess = FALSE;
	if (hSrc)
	{
		HGLOBAL hResData = LoadResource(hInst, hSrc);
		if (hResData)
		{
			LPVOID lpResData = LockResource(hResData);
			if (lpResData)
			{
				DWORD dwSize = SizeofResource(hInst, hSrc);
				if (dwSize)
				{
					HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, dwSize);
					if (hGlobal)
					{
						LPVOID lpBitmapData = GlobalLock(hGlobal);
						if (lpBitmapData)
						{
							CopyMemory(lpBitmapData, lpResData, dwSize);
							GlobalUnlock(hGlobal);
							bSuccess = Init(hGlobal, nType);
						}
					}
				}
			}
		}
	}

	return bSuccess;
}

// Ramène la largeur du bitmap
int CImage::GetWidth() const
{
	int nRet=NULL;

	if(m_hDib)
	{
		LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		nRet=BmInfo->biWidth;
		GlobalUnlock(m_hDib);
	}
	return nRet;
}

// Ramène la hauteur du bitmap
int CImage::GetHeight() const
{
	int nRet=NULL;

	if(m_hDib)
	{
		LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		nRet=BmInfo->biHeight;
		GlobalUnlock(m_hDib);
	}
	return nRet;
}

// Ramène le nombre de bits/pixel du bitmap
int CImage::GetBPP() const
{
	int nRet=NULL;

	if(m_hDib)
	{
		LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		nRet=BmInfo->biBitCount;
		GlobalUnlock(m_hDib);
	}
	return nRet;
}

// Récupère la résolution horizontale du bitmap (pixels/mètre)
int CImage::GetResX() const
{
	int nRet=NULL;

	if(m_hDib)
	{
		LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		nRet=BmInfo->biXPelsPerMeter;
		GlobalUnlock(m_hDib);
	}
	return nRet;
}

// Récupère la résolution verticale du bitmap (pixels/mètre)
int CImage::GetResY() const
{
	int nRet=NULL;

	if(m_hDib)
	{
		LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		nRet=BmInfo->biYPelsPerMeter;
		GlobalUnlock(m_hDib);
	}
	return nRet;
}

// Efface le DIB en cours et libère le handle
void CImage::Erase()
{
	if(m_hDib)
	{
		GlobalFree(m_hDib);
		m_hDib=NULL;
	}
	m_nTypeImage = IMG_TYPE_UNKNOWN;
	m_nFileFormat = IMG_FORMAT_END;
	m_dwTransparentColor = NULL;

	if(m_bDumpImage && m_LoadBuffer)
	{
		DeleteFile((LPCTSTR)m_LoadBuffer);
		free(m_LoadBuffer);
		m_LoadBuffer = NULL;
	}
	m_bDumpImage = FALSE;
}

// Opérateur =: Copie un CImage dans un autre CImage
CImage& CImage::operator =(const CImage& Source)
{
	// On commence par détruire le bitmap existant
	Erase();

	// Si image source dumpée, on prend directement son fichier
	#if defined(CIMAGE_SERIALIZE)
		if(Source.m_bDumpImage && Source.m_LoadBuffer)
		{
			if(!(m_LoadBuffer = malloc(_MAX_PATH)))
				return (*this);

			char szTempPath[_MAX_PATH];
			GetTempPath(_MAX_PATH, szTempPath);
			GetTempFileName(szTempPath, "img", 0, (LPSTR)m_LoadBuffer);

			// Copie du fichier source dans un autre fichier réservé à la classe affectée
			if(!CopyFile((LPCTSTR)Source.m_LoadBuffer, (LPCTSTR)m_LoadBuffer, FALSE))
			{
				free(m_LoadBuffer);
				m_LoadBuffer = NULL;
				return (*this);
			}

			// Affectation des autres données
			m_bDumpImage = TRUE;
			m_nTypeImage = Source.m_nTypeImage;
			m_nFileFormat = Source.m_nFileFormat;
			m_dwTransparentColor = Source.m_dwTransparentColor;

			// Retourne l'objet copié
			return (*this);
		}
	#endif

	// Taille source. Nulle -> on ramène un objet vide
	if(!Source.m_hDib)
		return (*this);
	int nSize=GlobalSize(Source.m_hDib);
	if(!nSize)
		return (*this);

	// Allocation mémoire et copie du DIB
	m_hDib=GlobalAlloc(GHND, nSize);
	if(m_hDib)
	{
		void* Src=GlobalLock(Source.m_hDib);
		void* Dest=GlobalLock(m_hDib);
		memcpy(Dest, Src, nSize);
		GlobalUnlock(Source.m_hDib);
		GlobalUnlock(m_hDib);
		m_nTypeImage = Source.m_nTypeImage;
		m_nFileFormat = Source.m_nFileFormat;
		m_dwTransparentColor = Source.m_dwTransparentColor;
	}

	// Retourne l'objet copié
	return (*this);
}

// Opérateur =: Copie un HDIB dans un CImage
CImage& CImage::operator =(const HGLOBAL hSource)
{
	// On commence par détruire le bitmap existant
	Erase();

	// Taille source. Nulle -> on ramène un objet vide
	int nSize=GlobalSize(hSource);
	if(!nSize)
		return (*this);

	// Allocation mémoire et copie du DIB
	m_hDib=GlobalAlloc(GHND, nSize);
	if(m_hDib)
	{
		void* Src=GlobalLock(hSource);
		void* Dest=GlobalLock(m_hDib);
		memcpy(Dest, Src, nSize);
		m_nTypeImage = GetDefaultType(((BITMAPINFOHEADER*)Dest)->biBitCount);
		GlobalUnlock(hSource);
		GlobalUnlock(m_hDib);
		m_nFileFormat = IMG_FORMAT_END;
	}

	// Retourne l'objet copié
	return (*this);
}

// Affecte la résolution du Bitmap. Les res. doivent être pasées en ppm
void CImage::SetRes(int nResX, int nResY)
{
	if(m_hDib)
	{
		LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		if(nResX)
			BmInfo->biXPelsPerMeter=nResX;
		if(nResY)
			BmInfo->biYPelsPerMeter=nResY;
		GlobalUnlock(m_hDib);
	}
}

// Renvoi le type d'image en cours
int CImage::GetType() const
{
	return m_nTypeImage;
}

// Affecte le type d'image utilisé
void CImage::SetType(int nType)
{
	m_nTypeImage = nType;
}

// Retrouve la valeur d'un pixel qq soit le nombre de bits/pixels
// Il faut fournir le pointeur de début du bitmap
DWORD CImage::GetPixel(int x, int y, LPBITMAPINFOHEADER BmInfo, int nColors, int nScanWidth, BYTE* lpBits) const
{
	// Vérifications seulement en mode Debug
	ASSERT(BmInfo);
	ASSERT(x>=0 && x<BmInfo->biWidth && y>=0 && y<BmInfo->biHeight);

	// Détermination du nombre de couleurs
	if(nColors == -1)
		nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);
	// Détermination de la zone des bits de l'image source et largeur lignes en octets
	if(!lpBits)
		lpBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
	if(!nScanWidth)
		nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);

	DWORD dwRet = NULL;
	// Traitement différent selon nombre de bits
	switch(BmInfo->biBitCount)
	{
		case 24:
			{
				int nPos = y*nScanWidth+x*3;
				dwRet=((DWORD)lpBits[nPos])<<16 | ((DWORD)lpBits[nPos+1])<<8
					| (DWORD)lpBits[nPos+2];
			}
			break;

		case 8:
			dwRet=(DWORD)lpBits[y*nScanWidth+x];
			break;

		case 4:
			dwRet=(DWORD)lpBits[y*nScanWidth+(x>>1)];
			if(!(x&1))
				dwRet>>=4;
			dwRet&=0x0FL;
			break;

		case 1:
			dwRet=(DWORD)(lpBits[y*nScanWidth+(x>>3)] >> (7-x%8) ) & 1;
			break;

		default:
			dwRet=NULL;
	}
	return dwRet;
}

// Affecte la valeur d'un pixel qq soit le nombre de bits/pixels
// Il faut fournir le pointeur de début du bitmap
void CImage::SetPixel(int x, int y, DWORD dwValue, LPBITMAPINFOHEADER BmInfo, int nColors, int nScanWidth, BYTE* lpBits)
{
	// Vérifications seulement en mode Debug
	ASSERT(BmInfo);
	ASSERT(x>=0 && x<BmInfo->biWidth && y>=0 && y<BmInfo->biHeight);

	// Détermination du nombre de couleurs
	if(nColors == -1)
		nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);
	// Détermination de la zone des bits de l'image source et largeur lignes en octets
	if(!lpBits)
		lpBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
	if(!nScanWidth)
		nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);

	// Traitement différent selon nombre de bits
	switch(BmInfo->biBitCount)
	{
		case 24:
			{
				int nPos = y*nScanWidth+x*3;
				lpBits[nPos]=(BYTE)((dwValue & 0xFF0000L)>>16);
				lpBits[nPos+1]=(BYTE)((dwValue & 0x00FF00L)>>8);
				lpBits[nPos+2]=(BYTE)(dwValue & 0x0000FFL);
			}
			break;

		case 8:
			lpBits[y*nScanWidth+x]=(BYTE)(dwValue & 0x0000FFL);
			break;

		case 4:
			{
				int nPos = y*nScanWidth+(x>>1);
				lpBits[nPos] &= (x&1 ? 0xF0:0x0F);
				dwValue &=0x0F;
				lpBits[nPos] |= (x&1 ? dwValue : dwValue<<4);
			}
			break;

		case 1:
			{
				int nMod=x%8;
				int nPos = y*nScanWidth+(x>>3);
				lpBits[nPos] &= ~(1<<(7-nMod));
				dwValue &=1;
				lpBits[nPos] |= (dwValue<<(7-nMod));
			}
			break;
	}
}

// Retourne un type d'image par défaut en fct du nbr de bits/pixel
int CImage::GetDefaultType(int nBits) const
{
	switch(nBits)
	{
		case 24:
			return IMG_TYPE_COL24;
			break;
		case 8:
			return IMG_TYPE_COL256;
			break;
		case 4:
			return IMG_TYPE_COL16;
			break;
		case 1:
			return IMG_TYPE_NB;
			break;
		default:
			return IMG_TYPE_UNKNOWN;
	}
}

// Renvoie le format d'image utilisé pour le chargement ou la dernière sauvegarde
int CImage::GetFileFormat() const
{
	return 	m_nFileFormat;
}

// Ramène TRUE si la classe contient une image valide, FALSE sinon
BOOL CImage::IsValid() const
{
	return (m_hDib ? TRUE : FALSE);
}

// Ramène la plus petite valeur des paramètres passés. Permet de passer des 'x++' en paramètre
int CImage::Min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}

// Affecte la couleur transparente. Si bSet est FALSE, efface la couleur
void CImage::SetTransparentColor(DWORD dwColor, BOOL bSet)
{
	if(bSet)
		m_dwTransparentColor = dwColor | 0x80000000L;
	else
		m_dwTransparentColor = NULL;
}

// Ramène la couleur transparente ds dwColor et si celle ci est valide en retour.
BOOL CImage::GetTransparentColor(DWORD *dwColor) const
{
	if(dwColor)
		*dwColor = m_dwTransparentColor & 0x7FFFFFFFL;
	return m_dwTransparentColor & 0x80000000L ? TRUE : FALSE;
}

//===================================================================
//      Fonctions de dessin. Activer avec CIMAGE_DRAW
//===================================================================

#if defined(CIMAGE_DRAW)

// Dessine un bitmap sur un DC. pDC = DC sur lequel il faut dessiner.
// rcDest = Coordonnées où il faut afficher, dwFlag = drapeaux pour dessin (cf DIB_DRAW_...)
// rcSrc = zone source à prendre (tout le bitmap par défaut)

#if !defined(CIMAGE_NO_MFC) // Version MFC
void CImage::Draw(CDC* pDC, CRect rcDest, DWORD dwFlags, CRect rcSrc)
{
	CRect rcDraw(rcDest);
	CRect rcSource(rcSrc);
	BOOL bChangeTaille = FALSE;
	BOOL bUseGDI=FALSE;
	BOOL bTransparent=FALSE;
	CPalette* OldPalette=NULL;
	CRgn ClipRgn;
	HANDLE hTransparentMask;

	if(!m_hDib)
		return;

	// On utilise le GDI pour imprimer ou si on le demande spécifiquement
	if(pDC->IsPrinting() || dwFlags & DIB_DRAW_USE_GDI || dwFlags & DIB_DRAW_PRINTING)
		bUseGDI=TRUE;

	// Détermine le mode transparent (force l'utilisation du GDI)
	if((dwFlags & DIB_DRAW_TRANSPARENT) && (m_dwTransparentColor & 0x80000000L))
		bUseGDI = bTransparent = TRUE;
	else
		bTransparent = FALSE;

	// On place un pointeur sur le début du bitmap
	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);

	// Passer la table des couleurs (non utilisée ici mais ds RealizePalette)
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);
	// Ajustement sur le début de l'image
	BYTE* lpBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);

	// Mode transparent...
	if(bTransparent)
	{
		// Si Impression, on met juste la couleur en blanc
		if(pDC->IsPrinting() || dwFlags & DIB_DRAW_PRINTING)
		{
			hTransparentMask = GlobalAlloc(GHND, GlobalSize(m_hDib));
			if(!hTransparentMask)
				bTransparent = FALSE;
			else
			{
				LPBITMAPINFOHEADER BmDest = (LPBITMAPINFOHEADER)GlobalLock(hTransparentMask);
				memcpy(BmDest, BmInfo, GlobalSize(m_hDib));
				DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
				if(BmInfo->biBitCount==24)
				{
					int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
					BYTE* lpDestBits = (BYTE*)BmDest+BmDest->biSize+nColors*sizeof(RGBQUAD);
					for(int y=0; y<BmInfo->biHeight; y++)
						for(int x=0; x<BmInfo->biWidth; x++)
						{
							DWORD dwColor = GetPixel(x, y, BmDest, nColors, nScanWidth, lpDestBits);
							if(dwColor == dwMaskColor)
								SetPixel(x, y, (DWORD)0xFFFFFFL, BmDest, nColors, nScanWidth, lpDestBits);
						}
				}
				else
				{
					for(int i=0; i<nColors; i++)
						if(i==(int)dwMaskColor)
						{
							memset(&((LPBITMAPINFO)BmDest)->bmiColors[i], 255, sizeof(RGBQUAD));
							((LPBITMAPINFO)BmDest)->bmiColors[i].rgbReserved = 0;
						}
				}
				GlobalUnlock(hTransparentMask);
			}
		}
		else
		{
			if(BmInfo->biBitCount==24)
			{
				// 24 bits -> création d'un bitmap en N&B pour le masque
				int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
				hTransparentMask = GlobalAlloc(GHND, GlobalSize(m_hDib));
				if(!hTransparentMask)
					bTransparent = FALSE;
				else
				{
					LPBITMAPINFOHEADER BmDest = (LPBITMAPINFOHEADER)GlobalLock(hTransparentMask);
					memcpy(BmDest, BmInfo, sizeof(BITMAPINFOHEADER));
					BYTE* lpDestBits = (BYTE*)BmDest+BmDest->biSize+nColors*sizeof(RGBQUAD);
					DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
					for(int y=0; y<BmInfo->biHeight; y++)
						for(int x=0; x<BmInfo->biWidth; x++)
						{
							DWORD dwColor = GetPixel(x, y, BmInfo, nColors, nScanWidth, lpBits);
							SetPixel(x, y, (DWORD)((dwColor == dwMaskColor) ? 0xFFFFFFL : NULL),
								BmDest, nColors, nScanWidth, lpDestBits);
						}
					GlobalUnlock(hTransparentMask);
				}
			}
			else
			{
				// Palette -> On sauvegarde juste la palette
				hTransparentMask = GlobalAlloc(GHND, nColors*sizeof(RGBQUAD));
				if(!hTransparentMask)
					bTransparent = FALSE;
				else
				{
					BYTE* Palette = (BYTE*)GlobalLock(hTransparentMask);
					memcpy(Palette, &((LPBITMAPINFO)BmInfo)->bmiColors[0], nColors*sizeof(RGBQUAD));
					GlobalUnlock(hTransparentMask);
					DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
					for(int i=0; i<nColors; i++)
						if(i==(int)dwMaskColor)
						{
							memset(&((LPBITMAPINFO)BmInfo)->bmiColors[i], 255, sizeof(RGBQUAD));
							((LPBITMAPINFO)BmInfo)->bmiColors[i].rgbReserved = 0;
						}
						else
							memset(&((LPBITMAPINFO)BmInfo)->bmiColors[i], 0, sizeof(RGBQUAD));
				}
			}
		}
	}

	// Calcul des dimensions réelles de la source pour les strechs...
	if(rcSrc.Width()<0 && rcSrc.Height()<0)
	{
		rcSource.left=rcSource.top=NULL;
		rcSource.right=BmInfo->biWidth;
		rcSource.bottom=BmInfo->biHeight;
	}

	// Ouverture librairie des fonctions DrawDib (si on utilise DrawDib)
	HDRAWDIB hdd=NULL;
	if(!bUseGDI)
		hdd = DrawDibOpen();
	if(hdd || bUseGDI)
	{
		// si palette demandée -> on réalize la palette
		if(dwFlags & DIB_DRAW_SETPALETTE)
			if(bUseGDI)
			{
				// En GDI, on construit la palette et on réalize
				if(nColors)
				{
					BYTE* DataImage=(BYTE*)BmInfo+BmInfo->biSize;
					LOGPALETTE* Palette=(LOGPALETTE*)malloc(nColors*sizeof(RGBQUAD)+sizeof(LOGPALETTE));
					Palette->palVersion=0x300;
					Palette->palNumEntries=(WORD)nColors;
					for(int i=0; i<nColors; i++)
					{
						Palette->palPalEntry[i].peBlue=*DataImage;
						DataImage++;
						Palette->palPalEntry[i].peGreen=*DataImage;
						DataImage++;
						Palette->palPalEntry[i].peRed=*DataImage;
						DataImage++;
						Palette->palPalEntry[i].peFlags=(BYTE)NULL;
						DataImage++;
					}
					CPalette Pal;
					Pal.CreatePalette(Palette);
					free(Palette);
					OldPalette=pDC->SelectPalette(&Pal,
						(dwFlags & DIB_DRAW_PALBACKGROUND) ? TRUE : FALSE);
					pDC->RealizePalette();
				}
			}
			else
				DrawDibRealize(hdd, pDC->m_hDC,
					(dwFlags & DIB_DRAW_PALBACKGROUND) ? TRUE : FALSE);

		// Modification de taille en fonction des tailles de départ
		//  et des flags de strech. KeepRatio traite à la fois X et Y
		//  (indisociables dans ce mode) et ajuste l'image au mieux
		//  sur l'affichage.
		if(rcDraw.Width()>rcSource.Width()) // Taille X fenêtre > DIB ?
		{
			if(dwFlags & DIB_DRAW_STRETCH_EXPANDX) // On Streche ?
			{
				if(dwFlags & DIB_DRAW_KEEP_RATIO) // en gardant le bon ratio ?
				{
					// Calcul des ratio et adaptation à la taille de la fenêtre
					double r1 = (double)rcDest.Width()/(double)rcDest.Height();
					double r2 = (double)rcSource.Width()/(double)rcSource.Height();

					rcDraw.right = rcDraw.left
						+ (fabs(r1)<=fabs(r2) ? rcDest.Width() : (int)((double)rcDest.Height() * r2));
					rcDraw.bottom = rcDraw.top
						+ (fabs(r1)>=fabs(r2) ? rcDest.Height() : (int)((double)rcDest.Width() / r2));

					bChangeTaille = TRUE; // Pour empêcher retraitement de l'image
				}
				// Si non -> on garde taille d'origine
			}
			else
			{
				// Pas de Strech -> On réajuste la taille de l'affichage
				rcDraw.right = rcDraw.left + rcSource.Width();
			}
		}

		if(rcDraw.Height()>rcSource.Height()) // Taille Y fenêtre > DIB ?
		{
			if(dwFlags & DIB_DRAW_STRETCH_EXPANDY) // On Streche ?
			{
				if(dwFlags & DIB_DRAW_KEEP_RATIO) // en gardant le bon ratio ?
				{
					// Calcul des ratio et adaptation à la taille de la fenêtre
					double r1 = (double)rcDest.Width()/(double)rcDest.Height();
					double r2 = (double)rcSource.Width()/(double)rcSource.Height();

					rcDraw.right = rcDraw.left
						+ (fabs(r1)<=fabs(r2) ? rcDest.Width() : (int)((double)rcDest.Height() * r2));
					rcDraw.bottom = rcDraw.top
						+ (fabs(r1)>=fabs(r2) ? rcDest.Height() : (int)((double)rcDest.Width() / r2));

					bChangeTaille = TRUE; // Pour empêcher retraitement de l'image
				}
				// Si non -> on garde taille d'origine
			}
			else
			{
				// Pas de Strech -> On réajuste la taille de l'affichage
				rcDraw.bottom = rcDraw.top + rcSource.Height();
			}
		}

		if(rcDraw.Width()<rcSource.Width()) // Taille X fenêtre < DIB ?
		{
			if(dwFlags & DIB_DRAW_STRETCH_REDUCEX) // On Streche ?
			{
				if((dwFlags & DIB_DRAW_KEEP_RATIO) // en gardant le bon ratio ?
					&& !bChangeTaille) // et si taille < n'est pas due à modif précédente
				{
					// Calcul des ratio et adaptation à la taille de la fenêtre
					double r1 = (double)rcDest.Width()/(double)rcDest.Height();
					double r2 = (double)rcSource.Width()/(double)rcSource.Height();

					rcDraw.right = rcDraw.left
						+ (fabs(r1)<=fabs(r2) ? rcDest.Width() : (int)((double)rcDest.Height() * r2));
					rcDraw.bottom = rcDraw.top
						+ (fabs(r1)>=fabs(r2) ? rcDest.Height() : (int)((double)rcDest.Width() / r2));

					bChangeTaille = TRUE; // Pour empêcher retraitement de l'image
				}
				// Si non -> on garde taille d'origine
			}
			else
			{
				// Pas de Strech -> On réajuste la taille de l'affichage
				rcDraw.right = rcDraw.left + rcSource.Width();
			}
		}

		if(rcDraw.Height()<rcSource.Height()) // Taille Y fenêtre < DIB ?
		{
			if(dwFlags & DIB_DRAW_STRETCH_REDUCEY) // On Streche ?
			{
				if((dwFlags & DIB_DRAW_KEEP_RATIO) // en gardant le bon ratio ?
					&& !bChangeTaille) // et si taille < n'est pas due à modif précédente
				{
					// Calcul des ratio et adaptation à la taille de la fenêtre
					double r1 = (double)rcDest.Width()/(double)rcDest.Height();
					double r2 = (double)rcSource.Width()/(double)rcSource.Height();

					rcDraw.right = rcDraw.left
						+ (fabs(r1)<=fabs(r2) ? rcDest.Width() : (int)((double)rcDest.Height() * r2));
					rcDraw.bottom = rcDraw.top
						+ (fabs(r1)>=fabs(r2) ? rcDest.Height() : (int)((double)rcDest.Width() / r2));
				}
				// Si non -> on garde taille d'origine
			}
			else
			{
				// Pas de Strech -> On réajuste la taille de l'affichage
				rcDraw.bottom = rcDraw.top + rcSource.Height();
			}
		}

		// Centre le bitmap horizontalement dans l'affichage
		if((dwFlags & DIB_DRAW_CENTER_HORZ))
		{
			int Width = rcDraw.Width();
			rcDraw.left = rcDest.left + (rcDest.Width()>>1) - (rcDraw.Width()>>1);
			rcDraw.right = rcDraw.left + Width;
		}

		// Centre le bitmap verticalement dans l'affichage
		if((dwFlags & DIB_DRAW_CENTER_VERT))
		{
			int Height = rcDraw.Height();
			rcDraw.top = rcDest.top + (rcDest.Height()>>1) - (rcDraw.Height()>>1);
			rcDraw.bottom = rcDraw.top + Height;
		}

		// Clipping de la région si nécessaire
		if(dwFlags & DIB_DRAW_CLIP)
		{
			ClipRgn.CreateRectRgnIndirect(rcDest);
			pDC->SelectClipRgn(&ClipRgn);
		}

		// Dessin du DIB
		if(bUseGDI)
		{
			// En MapMode != MM_TEXT, les coordonnées sont parfois inversées par les calculs
			if(pDC->GetMapMode()!=MM_TEXT)
			{
				if(rcDraw.top<rcDraw.bottom)
				{
					int nDummy = rcDraw.bottom;
					rcDraw.bottom = rcDraw.top;
					rcDraw.top = nDummy;
				}
				if(rcDraw.right<rcDraw.left)
				{
					int nDummy = rcDraw.right;
					rcDraw.right = rcDraw.left;
					rcDraw.left = nDummy;
				}
			}
			pDC->SetStretchBltMode(STRETCH_DELETESCANS);

			if(!bTransparent)
			{
				// Affichage sans transparence
				StretchDIBits(pDC->m_hDC,
					rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
					rcSource.left, rcSource.top, rcSource.Width(), rcSource.Height(),
					lpBits, (BITMAPINFO*)BmInfo, DIB_RGB_COLORS, SRCCOPY);
			}
			else
			{
				if(pDC->IsPrinting() || dwFlags & DIB_DRAW_PRINTING)
				{
					// Affichage sans transparence du bitmap à fond blanc
					LPBITMAPINFOHEADER BmDest = (LPBITMAPINFOHEADER)GlobalLock(hTransparentMask);
					BYTE* lpDestBits = (BYTE*)BmDest+BmDest->biSize+nColors*sizeof(RGBQUAD);
					StretchDIBits(pDC->m_hDC,
						rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
						rcSource.left, rcSource.top, rcSource.Width(), rcSource.Height(),
						lpDestBits, (BITMAPINFO*)BmDest, DIB_RGB_COLORS, SRCCOPY);
					GlobalUnlock(hTransparentMask);
					GlobalFree(hTransparentMask);
				}
				else
				{
					if(BmInfo->biBitCount==24)
					{
						// Affichage masque
						LPBITMAPINFOHEADER BmDest = (LPBITMAPINFOHEADER)GlobalLock(hTransparentMask);
						BYTE* lpDestBits = (BYTE*)BmDest+BmDest->biSize+nColors*sizeof(RGBQUAD);
						int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
						StretchDIBits(pDC->m_hDC,
							rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
							rcSource.left, rcSource.top, rcSource.Width(), rcSource.Height(),
							lpDestBits, (BITMAPINFO*)BmDest, DIB_RGB_COLORS, SRCAND);

						// Construction puis affichage bitmap transparent
						DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
						DWORD dwColor;
						for(int y=0; y<BmInfo->biHeight; y++)
							for(int x=0; x<BmInfo->biWidth; x++)
							{
								dwColor = GetPixel(x, y, BmInfo, nColors, nScanWidth, lpBits);
								SetPixel(x, y,
									dwColor == dwMaskColor ? NULL : dwColor,
									BmDest, nColors, nScanWidth, lpDestBits);
							}
						StretchDIBits(pDC->m_hDC,
							rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
							rcSource.left, rcSource.top, rcSource.Width(), rcSource.Height(),
							lpDestBits, (BITMAPINFO*)BmDest, DIB_RGB_COLORS, SRCPAINT);
						GlobalUnlock(hTransparentMask);
						GlobalFree(hTransparentMask);
					}
					else
					{
						StretchDIBits(pDC->m_hDC,
							rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
							rcSource.left, rcSource.top, rcSource.Width(), rcSource.Height(),
							lpBits, (BITMAPINFO*)BmInfo, DIB_RGB_COLORS, SRCAND);
						RGBQUAD* Palette = (RGBQUAD*)GlobalLock(hTransparentMask);
						DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
						for(int i=0; i<nColors; i++)
							if(i==(int)dwMaskColor)
								memset(&((LPBITMAPINFO)BmInfo)->bmiColors[i], 0, sizeof(RGBQUAD));
							else
								memcpy(&((LPBITMAPINFO)BmInfo)->bmiColors[i], &Palette[i], sizeof(RGBQUAD));
						StretchDIBits(pDC->m_hDC,
							rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
							rcSource.left, rcSource.top, rcSource.Width(), rcSource.Height(),
							lpBits, (BITMAPINFO*)BmInfo, DIB_RGB_COLORS, SRCPAINT);
						memcpy(&((LPBITMAPINFO)BmInfo)->bmiColors[0], Palette, nColors*sizeof(RGBQUAD));
						GlobalUnlock(hTransparentMask);
						GlobalFree(hTransparentMask);
					}
				}
			}
		}
		else
		{
			DrawDibDraw(hdd, pDC->m_hDC,
				rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(),
				BmInfo, lpBits,	
				rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(),
				NULL);
		}

		if(!bUseGDI)
			DrawDibClose(hdd);

		// Si GDI, on rétablit la palette
		if(bUseGDI && OldPalette)
			pDC->SelectPalette(OldPalette, FALSE);
	}
	else
	{
		// Uniquement en Debug...
		TRACE0("DrawDibOpen failed in Draw\n");
	}
}
#else // Version sans MFC, utilisable seulement si on n'utilise pas les MFC
void CImage::Draw(HDC hDC, RECT* rcDest, DWORD dwFlags, RECT* rcSrc)
{
	RECT rcDraw;
	memcpy(&rcDraw, rcDest, sizeof(rcDraw));
	RECT rcSource;
	RECT rcSrc2;
	rcSrc2.left = rcSrc2.top = 0;
	rcSrc2.right = rcSrc2.bottom = -1;
	if(!rcSrc)
		rcSrc = &rcSrc2;
	memcpy(&rcSource, rcSrc, sizeof(rcSource));
	BOOL bChangeTaille = FALSE;
	BOOL bUseGDI=FALSE;
	BOOL bTransparent=FALSE;
	HPALETTE hOldPalette=NULL;
	HRGN hClipRgn;
	HANDLE hTransparentMask;

	if(!m_hDib)
		return;

	// On utilise le GDI si on le demande spécifiquement (obligatoire pour l'impression)
	if(dwFlags & DIB_DRAW_USE_GDI || dwFlags & DIB_DRAW_PRINTING)
		bUseGDI=TRUE;

	// Détermine le mode transparent (force l'utilisation du GDI)
	if((dwFlags & DIB_DRAW_TRANSPARENT) && (m_dwTransparentColor & 0x80000000L))
		bUseGDI = bTransparent = TRUE;
	else
		bTransparent = FALSE;

	// On place un pointeur sur le début du bitmap
	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);

	// Passer la table des couleurs (non utilisée ici mais ds RealizePalette)
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);
	// Ajustement sur le début de l'image
	BYTE* lpBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);

	// Mode transparent...
	if(bTransparent)
	{
		// Si Impression, on met juste la couleur en blanc
		if(dwFlags & DIB_DRAW_PRINTING)
		{
			hTransparentMask = GlobalAlloc(GHND, GlobalSize(m_hDib));
			if(!hTransparentMask)
				bTransparent = FALSE;
			else
			{
				LPBITMAPINFOHEADER BmDest = (LPBITMAPINFOHEADER)GlobalLock(hTransparentMask);
				memcpy(BmDest, BmInfo, GlobalSize(m_hDib));
				DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
				if(BmInfo->biBitCount==24)
				{
					int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
					BYTE* lpDestBits = (BYTE*)BmDest+BmDest->biSize+nColors*sizeof(RGBQUAD);
					for(int y=0; y<BmInfo->biHeight; y++)
						for(int x=0; x<BmInfo->biWidth; x++)
						{
							DWORD dwColor = GetPixel(x, y, BmDest, nColors, nScanWidth, lpDestBits);
							if(dwColor == dwMaskColor)
								SetPixel(x, y, (DWORD)0xFFFFFFL, BmDest, nColors, nScanWidth, lpDestBits);
						}
				}
				else
				{
					for(int i=0; i<nColors; i++)
						if(i==(int)dwMaskColor)
						{
							memset(&((LPBITMAPINFO)BmDest)->bmiColors[i], 255, sizeof(RGBQUAD));
							((LPBITMAPINFO)BmDest)->bmiColors[i].rgbReserved = 0;
						}
				}
				GlobalUnlock(hTransparentMask);
			}
		}
		else
		{
			if(BmInfo->biBitCount==24)
			{
				// 24 bits -> création d'un bitmap en N&B pour le masque
				int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
				hTransparentMask = GlobalAlloc(GHND, GlobalSize(m_hDib));
				if(!hTransparentMask)
					bTransparent = FALSE;
				else
				{
					LPBITMAPINFOHEADER BmDest = (LPBITMAPINFOHEADER)GlobalLock(hTransparentMask);
					memcpy(BmDest, BmInfo, sizeof(BITMAPINFOHEADER));
					BYTE* lpDestBits = (BYTE*)BmDest+BmDest->biSize+nColors*sizeof(RGBQUAD);
					DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
					for(int y=0; y<BmInfo->biHeight; y++)
						for(int x=0; x<BmInfo->biWidth; x++)
						{
							DWORD dwColor = GetPixel(x, y, BmInfo, nColors, nScanWidth, lpBits);
							SetPixel(x, y, (DWORD)((dwColor == dwMaskColor) ? 0xFFFFFFL : NULL),
								BmDest, nColors, nScanWidth, lpDestBits);
						}
					GlobalUnlock(hTransparentMask);
				}
			}
			else
			{
				// Palette -> On sauvegarde juste la palette
				hTransparentMask = GlobalAlloc(GHND, nColors*sizeof(RGBQUAD));
				if(!hTransparentMask)
					bTransparent = FALSE;
				else
				{
					BYTE* Palette = (BYTE*)GlobalLock(hTransparentMask);
					memcpy(Palette, &((LPBITMAPINFO)BmInfo)->bmiColors[0], nColors*sizeof(RGBQUAD));
					GlobalUnlock(hTransparentMask);
					DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
					for(int i=0; i<nColors; i++)
						if(i==(int)dwMaskColor)
						{
							memset(&((LPBITMAPINFO)BmInfo)->bmiColors[i], 255, sizeof(RGBQUAD));
							((LPBITMAPINFO)BmInfo)->bmiColors[i].rgbReserved = 0;
						}
						else
							memset(&((LPBITMAPINFO)BmInfo)->bmiColors[i], 0, sizeof(RGBQUAD));
				}
			}
		}
	}

	// Calcul des dimensions réelles de la source pour les strechs...
	if((rcSrc->right-rcSrc->left)<0 && (rcSrc->bottom-rcSrc->top)<0)
	{
		rcSource.left=rcSource.top=NULL;
		rcSource.right=BmInfo->biWidth;
		rcSource.bottom=BmInfo->biHeight;
	}

	// Ouverture librairie des fonctions DrawDib (si on utilise DrawDib)
	HDRAWDIB hdd=NULL;
	if(!bUseGDI)
		hdd = DrawDibOpen();
	if(hdd || bUseGDI)
	{
		// si palette demandée -> on réalize la palette
		if(dwFlags & DIB_DRAW_SETPALETTE)
			if(bUseGDI)
			{
				// En GDI, on construit la palette et on réalize
				if(nColors)
				{
					BYTE* DataImage=(BYTE*)BmInfo+BmInfo->biSize;
					LOGPALETTE* Palette=(LOGPALETTE*)malloc(nColors*sizeof(RGBQUAD)+sizeof(LOGPALETTE));
					Palette->palVersion=0x300;
					Palette->palNumEntries=(WORD)nColors;
					for(int i=0; i<nColors; i++)
					{
						Palette->palPalEntry[i].peBlue=*DataImage;
						DataImage++;
						Palette->palPalEntry[i].peGreen=*DataImage;
						DataImage++;
						Palette->palPalEntry[i].peRed=*DataImage;
						DataImage++;
						Palette->palPalEntry[i].peFlags=(BYTE)NULL;
						DataImage++;
					}
					HPALETTE hPal = ::CreatePalette(Palette);
					free(Palette);
					hOldPalette = ::SelectPalette(hDC, hPal,
						(dwFlags & DIB_DRAW_PALBACKGROUND) ? TRUE : FALSE);
					::RealizePalette(hDC);
				}
			}
			else
				DrawDibRealize(hdd, hDC,
					(dwFlags & DIB_DRAW_PALBACKGROUND) ? TRUE : FALSE);

		// Modification de taille en fonction des tailles de départ
		//  et des flags de strech. KeepRatio traite à la fois X et Y
		//  (indisociables dans ce mode) et ajuste l'image au mieux
		//  sur l'affichage.
		if((rcDraw.right-rcDraw.left)>(rcSource.right-rcSource.left)) // Taille X fenêtre > DIB ?
		{
			if(dwFlags & DIB_DRAW_STRETCH_EXPANDX) // On Streche ?
			{
				if(dwFlags & DIB_DRAW_KEEP_RATIO) // en gardant le bon ratio ?
				{
					// Calcul des ratio et adaptation à la taille de la fenêtre
					double r1 = (double)(rcDest->right-rcDest->left)
						/(double)(rcDest->bottom-rcDest->top);
					double r2 = (double)(rcSource.right-rcSource.left)
						/(double)(rcSource.bottom-rcSource.top);

					rcDraw.right = rcDraw.left
						+ (fabs(r1)<=fabs(r2) ? (rcDest->right-rcDest->left) : (int)((double)(rcDest->bottom-rcDest->top) * r2));
					rcDraw.bottom = rcDraw.top
						+ (fabs(r1)>=fabs(r2) ? (rcDest->bottom-rcDest->top) : (int)((double)(rcDest->right-rcDest->left) / r2));

					bChangeTaille = TRUE; // Pour empêcher retraitement de l'image
				}
				// Si non -> on garde taille d'origine
			}
			else
			{
				// Pas de Strech -> On réajuste la taille de l'affichage
				rcDraw.right = rcDraw.left + (rcSource.right-rcSource.left);
			}
		}

		if((rcDraw.bottom-rcDraw.top)>(rcSource.bottom-rcSource.top)) // Taille Y fenêtre > DIB ?
		{
			if(dwFlags & DIB_DRAW_STRETCH_EXPANDY) // On Streche ?
			{
				if(dwFlags & DIB_DRAW_KEEP_RATIO) // en gardant le bon ratio ?
				{
					// Calcul des ratio et adaptation à la taille de la fenêtre
					double r1 = (double)(rcDest->right-rcDest->left)/(double)(rcDest->bottom-rcDest->top);
					double r2 = (double)(rcSource.right-rcSource.left)/(double)(rcSource.bottom-rcSource.top);

					rcDraw.right = rcDraw.left
						+ (fabs(r1)<=fabs(r2) ? (rcDest->right-rcDest->left) : (int)((double)(rcDest->bottom-rcDest->top) * r2));
					rcDraw.bottom = rcDraw.top
						+ (fabs(r1)>=fabs(r2) ? (rcDest->bottom-rcDest->top) : (int)((double)(rcDest->right-rcDest->left) / r2));

					bChangeTaille = TRUE; // Pour empêcher retraitement de l'image
				}
				// Si non -> on garde taille d'origine
			}
			else
			{
				// Pas de Strech -> On réajuste la taille de l'affichage
				rcDraw.bottom = rcDraw.top + (rcSource.bottom-rcSource.top);
			}
		}

		if((rcDraw.right-rcDraw.left)<(rcSource.right-rcSource.left)) // Taille X fenêtre < DIB ?
		{
			if(dwFlags & DIB_DRAW_STRETCH_REDUCEX) // On Streche ?
			{
				if((dwFlags & DIB_DRAW_KEEP_RATIO) // en gardant le bon ratio ?
					&& !bChangeTaille) // et si taille < n'est pas due à modif précédente
				{
					// Calcul des ratio et adaptation à la taille de la fenêtre
					double r1 = (double)(rcDest->right-rcDest->left)/(double)(rcDest->bottom-rcDest->top);
					double r2 = (double)(rcSource.right-rcSource.left)/(double)(rcSource.bottom-rcSource.top);

					rcDraw.right = rcDraw.left
						+ (fabs(r1)<=fabs(r2) ? (rcDest->right-rcDest->left) : (int)((double)(rcDest->bottom-rcDest->top) * r2));
					rcDraw.bottom = rcDraw.top
						+ (fabs(r1)>=fabs(r2) ? (rcDest->bottom-rcDest->top) : (int)((double)(rcDest->right-rcDest->left) / r2));

					bChangeTaille = TRUE; // Pour empêcher retraitement de l'image
				}
				// Si non -> on garde taille d'origine
			}
			else
			{
				// Pas de Strech -> On réajuste la taille de l'affichage
				rcDraw.right = rcDraw.left + (rcSource.right-rcSource.left);
			}
		}

		if((rcDraw.bottom-rcDraw.top)<(rcSource.bottom-rcSource.top)) // Taille Y fenêtre < DIB ?
		{
			if(dwFlags & DIB_DRAW_STRETCH_REDUCEY) // On Streche ?
			{
				if((dwFlags & DIB_DRAW_KEEP_RATIO) // en gardant le bon ratio ?
					&& !bChangeTaille) // et si taille < n'est pas due à modif précédente
				{
					// Calcul des ratio et adaptation à la taille de la fenêtre
					double r1 = (double)(rcDest->right-rcDest->left)/(double)(rcDest->bottom-rcDest->top);
					double r2 = (double)(rcSource.right-rcSource.left)/(double)(rcSource.bottom-rcSource.top);

					rcDraw.right = rcDraw.left
						+ (fabs(r1)<=fabs(r2) ? (rcDest->right-rcDest->left) : (int)((double)(rcDest->bottom-rcDest->top) * r2));
					rcDraw.bottom = rcDraw.top
						+ (fabs(r1)>=fabs(r2) ? (rcDest->bottom-rcDest->top) : (int)((double)(rcDest->right-rcDest->left) / r2));
				}
				// Si non -> on garde taille d'origine
			}
			else
			{
				// Pas de Strech -> On réajuste la taille de l'affichage
				rcDraw.bottom = rcDraw.top + (rcSource.bottom-rcSource.top);
			}
		}

		// Centre le bitmap horizontalement dans l'affichage
		if((dwFlags & DIB_DRAW_CENTER_HORZ))
		{
			int Width = (rcDraw.right-rcDraw.left);
			rcDraw.left = rcDest->left + ((rcDest->right-rcDest->left)>>1) - ((rcDraw.right-rcDraw.left)>>1);
			rcDraw.right = rcDraw.left + Width;
		}

		// Centre le bitmap verticalement dans l'affichage
		if((dwFlags & DIB_DRAW_CENTER_VERT))
		{
			int Height = (rcDraw.bottom-rcDraw.top);
			rcDraw.top = rcDest->top + ((rcDest->bottom-rcDest->top)>>1) - ((rcDraw.bottom-rcDraw.top)>>1);
			rcDraw.bottom = rcDraw.top + Height;
		}

		// Clipping de la région si nécessaire
		if(dwFlags & DIB_DRAW_CLIP)
		{
			hClipRgn = ::CreateRectRgnIndirect(rcDest);
			::SelectClipRgn(hDC, hClipRgn);
		}

		// Dessin du DIB
		if(bUseGDI)
		{
			// En MapMode != MM_TEXT, les coordonnées sont parfois inversées par les calculs
			if(::GetMapMode(hDC)!=MM_TEXT)
			{
				if(rcDraw.top<rcDraw.bottom)
				{
					int nDummy = rcDraw.bottom;
					rcDraw.bottom = rcDraw.top;
					rcDraw.top = nDummy;
				}
				if(rcDraw.right<rcDraw.left)
				{
					int nDummy = rcDraw.right;
					rcDraw.right = rcDraw.left;
					rcDraw.left = nDummy;
				}
			}
			SetStretchBltMode(hDC, STRETCH_DELETESCANS);

			if(!bTransparent)
			{
				// Affichage sans transparence
				StretchDIBits(hDC,
					rcDraw.left, rcDraw.top, (rcDraw.right-rcDraw.left), (rcDraw.bottom-rcDraw.top),
					rcSource.left, rcSource.top, (rcSource.right-rcSource.left), (rcSource.bottom-rcSource.top),
					lpBits, (BITMAPINFO*)BmInfo, DIB_RGB_COLORS, SRCCOPY);
			}
			else
			{
				if(dwFlags & DIB_DRAW_PRINTING)
				{
					// Affichage sans transparence du bitmap à fond blanc
					LPBITMAPINFOHEADER BmDest = (LPBITMAPINFOHEADER)GlobalLock(hTransparentMask);
					BYTE* lpDestBits = (BYTE*)BmDest+BmDest->biSize+nColors*sizeof(RGBQUAD);
					StretchDIBits(hDC,
						rcDraw.left, rcDraw.top, (rcDraw.right-rcDraw.left), (rcDraw.bottom-rcDraw.top),
						rcSource.left, rcSource.top, (rcSource.right-rcSource.left), (rcSource.bottom-rcSource.top),
						lpDestBits, (BITMAPINFO*)BmDest, DIB_RGB_COLORS, SRCCOPY);
					GlobalUnlock(hTransparentMask);
					GlobalFree(hTransparentMask);
				}
				else
				{
					if(BmInfo->biBitCount==24)
					{
						// Affichage masque
						LPBITMAPINFOHEADER BmDest = (LPBITMAPINFOHEADER)GlobalLock(hTransparentMask);
						BYTE* lpDestBits = (BYTE*)BmDest+BmDest->biSize+nColors*sizeof(RGBQUAD);
						int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
						StretchDIBits(hDC,
							rcDraw.left, rcDraw.top, (rcDraw.right-rcDraw.left), (rcDraw.bottom-rcDraw.top),
							rcSource.left, rcSource.top, (rcSource.right-rcSource.left), (rcSource.bottom-rcSource.top),
							lpDestBits, (BITMAPINFO*)BmDest, DIB_RGB_COLORS, SRCAND);

						// Construction puis affichage bitmap transparent
						DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
						DWORD dwColor;
						for(int y=0; y<BmInfo->biHeight; y++)
							for(int x=0; x<BmInfo->biWidth; x++)
							{
								dwColor = GetPixel(x, y, BmInfo, nColors, nScanWidth, lpBits);
								SetPixel(x, y,
									dwColor == dwMaskColor ? NULL : dwColor,
									BmDest, nColors, nScanWidth, lpDestBits);
							}
						StretchDIBits(hDC,
							rcDraw.left, rcDraw.top, (rcDraw.right-rcDraw.left), (rcDraw.bottom-rcDraw.top),
							rcSource.left, rcSource.top, (rcSource.right-rcSource.left), (rcSource.bottom-rcSource.top),
							lpDestBits, (BITMAPINFO*)BmDest, DIB_RGB_COLORS, SRCPAINT);
						GlobalUnlock(hTransparentMask);
						GlobalFree(hTransparentMask);
					}
					else
					{
						StretchDIBits(hDC,
							rcDraw.left, rcDraw.top, (rcDraw.right-rcDraw.left), (rcDraw.bottom-rcDraw.top),
							rcSource.left, rcSource.top, (rcSource.right-rcSource.left), (rcSource.bottom-rcSource.top),
							lpBits, (BITMAPINFO*)BmInfo, DIB_RGB_COLORS, SRCAND);
						RGBQUAD* Palette = (RGBQUAD*)GlobalLock(hTransparentMask);
						DWORD dwMaskColor = m_dwTransparentColor & 0x7FFFFFFFL;
						for(int i=0; i<nColors; i++)
							if(i==(int)dwMaskColor)
								memset(&((LPBITMAPINFO)BmInfo)->bmiColors[i], 0, sizeof(RGBQUAD));
							else
								memcpy(&((LPBITMAPINFO)BmInfo)->bmiColors[i], &Palette[i], sizeof(RGBQUAD));
						StretchDIBits(hDC,
							rcDraw.left, rcDraw.top, (rcDraw.right-rcDraw.left), (rcDraw.bottom-rcDraw.top),
							rcSource.left, rcSource.top, (rcSource.right-rcSource.left), (rcSource.bottom-rcSource.top),
							lpBits, (BITMAPINFO*)BmInfo, DIB_RGB_COLORS, SRCPAINT);
						memcpy(&((LPBITMAPINFO)BmInfo)->bmiColors[0], Palette, nColors*sizeof(RGBQUAD));
						GlobalUnlock(hTransparentMask);
						GlobalFree(hTransparentMask);
					}
				}
			}
		}
		else
		{
			DrawDibDraw(hdd, hDC,
				rcDraw.left, rcDraw.top, (rcDraw.right-rcDraw.left), (rcDraw.bottom-rcDraw.top),
				BmInfo, lpBits,	
				rcSrc->left, rcSrc->top, (rcSrc->right-rcSrc->left),
				(rcSrc->bottom-rcSrc->top), NULL);
		}

		if(!bUseGDI)
			DrawDibClose(hdd);

		// Si GDI, on rétablit la palette
		if(bUseGDI && hOldPalette)
			::SelectPalette(hDC, hOldPalette, FALSE);
	}
}
#endif // !CIMAGE_NO_MFC

#endif // NO_DRAW

//===================================================================
// Fonctions de contraste et lumière. Activer avec CIMAGE_CONTROLE
//===================================================================

#if defined(CIMAGE_CONTROLE)

// Ajustement de la lumière du bitmap. nValue va de -100 à +100.
//  Si nValue=0, il n'y a pas de changement
BOOL CImage::AdjustBrightness(int nValue)
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	if(!nValue)
		return TRUE; // Calcul inutile!!

	// Calcul du pourcentage en fonction de nValue originale
	if(nValue>0)
		nValue=(nValue<<1)+100;
	else
		nValue+=100;

	// On crée une tables pour augmenter la rapidité de calcul
	BYTE cCalcValue[256];
	for(int i=0; i<256; i++)
		cCalcValue[i] = max(min(i*nValue/100, 255), 0);

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;

	// Détermination du nombre de couleurs
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);

	if(nColors && nColors<=256 && BmInfo->biBitCount!=24) // Il y a une palette -> on joue sur la palette
	{
		for(int i=0; i<nColors; i++)
		{
			bi->bmiColors[i].rgbRed = cCalcValue[bi->bmiColors[i].rgbRed];
			bi->bmiColors[i].rgbGreen = cCalcValue[bi->bmiColors[i].rgbGreen];
			bi->bmiColors[i].rgbBlue = cCalcValue[bi->bmiColors[i].rgbBlue];
		}
	}
	else
	{	// 24 bits -> pas de palette (!! 32 bits non supporté)

		// Détermination de la zone des bits de l'image
		BYTE* lpLineBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
		BYTE* lpBits;

		for(int y=0; y<BmInfo->biHeight; y++)
		{
			lpBits = lpLineBits;
			for(int x=0; x<BmInfo->biWidth; x++)
			{
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
			}
			lpLineBits += nScanWidth;
		}

		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			lpBits = (BYTE*)&m_dwTransparentColor;
			lpBits[0]=cCalcValue[lpBits[0]];
			lpBits[1]=cCalcValue[lpBits[1]];
			lpBits[2]=cCalcValue[lpBits[2]];
		}
	}

	GlobalUnlock(m_hDib);

	return TRUE;
}

// Ajustement du contraste du bitmap. nValue va de -100 à +100.
//  Si nValue=0, il n'y a pas de changement
BOOL CImage::AdjustContrast(int nValue)
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	if(!nValue)
		return TRUE; // Calcul inutile!!

	// Calcul du pourcentage en fonction de nValue originale
	if(nValue>0)
		nValue=nValue*3+100;
	else
		nValue+=100;

	// On crée une tables pour augmenter la rapidité de calcul
	BYTE cCalcValue[256];
	for(int i=0; i<256; i++)
		cCalcValue[i] = max(min(128+((i-128)*nValue/100), 255), 0);

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;

	// Détermination du nombre de couleurs
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);

	if(nColors && nColors<=256 && BmInfo->biBitCount!=24) // Il y a une palette -> on joue sur la palette
	{
		for(int i=0; i<nColors; i++)
		{
			bi->bmiColors[i].rgbRed = cCalcValue[bi->bmiColors[i].rgbRed];
			bi->bmiColors[i].rgbGreen = cCalcValue[bi->bmiColors[i].rgbGreen];
			bi->bmiColors[i].rgbBlue = cCalcValue[bi->bmiColors[i].rgbBlue];
		}
	}
	else
	{	// 24 bits -> pas de palette (!! 32 bits non supporté)

		// Détermination de la zone des bits de l'image
		BYTE* lpLineBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
		BYTE* lpBits;

		for(int y=0; y<BmInfo->biHeight; y++)
		{
			lpBits = lpLineBits;
			for(int x=0; x<BmInfo->biWidth; x++)
			{
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
			}
			lpLineBits += nScanWidth;
		}

		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			lpBits = (BYTE*)&m_dwTransparentColor;
			lpBits[0]=cCalcValue[lpBits[0]];
			lpBits[1]=cCalcValue[lpBits[1]];
			lpBits[2]=cCalcValue[lpBits[2]];
		}
	}

	GlobalUnlock(m_hDib);

	return TRUE;
}

// Correction du Gamma. 1.0 = pas de modif
BOOL CImage::AdjustGamma(double fValue)
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	if(fValue==1.0)
		return TRUE; // Calcul inutile!!

	// On crée une tables pour augmenter la rapidité de calcul
	BYTE cCalcValue[256];
	for(int i=0; i<256; i++)
		cCalcValue[i] = max(min((int)(pow((double)i/255.0, 1.0/fValue)*255.0+0.5), 255), 0);

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;

	// Détermination du nombre de couleurs
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);

	if(nColors && nColors<=256 && BmInfo->biBitCount!=24) // Il y a une palette -> on joue sur la palette
	{
		for(int i=0; i<nColors; i++)
		{
			bi->bmiColors[i].rgbRed = cCalcValue[bi->bmiColors[i].rgbRed];
			bi->bmiColors[i].rgbGreen = cCalcValue[bi->bmiColors[i].rgbGreen];
			bi->bmiColors[i].rgbBlue = cCalcValue[bi->bmiColors[i].rgbBlue];
		}
	}
	else
	{	// 24 bits -> pas de palette (!! 32 bits non supporté)

		// Détermination de la zone des bits de l'image
		BYTE* lpLineBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
		BYTE* lpBits;

		for(int y=0; y<BmInfo->biHeight; y++)
		{
			lpBits = lpLineBits;
			for(int x=0; x<BmInfo->biWidth; x++)
			{
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
				*lpBits = cCalcValue[*lpBits];
				lpBits++;
			}
			lpLineBits += nScanWidth;
		}

		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			lpBits = (BYTE*)&m_dwTransparentColor;
			lpBits[0]=cCalcValue[lpBits[0]];
			lpBits[1]=cCalcValue[lpBits[1]];
			lpBits[2]=cCalcValue[lpBits[2]];
		}
	}

	GlobalUnlock(m_hDib);

	return TRUE;
}

// Correction des couleurs. Les valeurs passées sont des pourmillième de chaque couleur.
//  Si les valeurs valent 1000, il n'y a pas de changement.
BOOL CImage::CorrectColors(DWORD dwRouge, DWORD dwVert, DWORD dwBleu)
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	if(dwRouge==1000L && dwVert==1000L && dwBleu==1000L)
		return TRUE; // Calcul inutile!!

	// On crée 3 tables pour augmenter la rapidité de calcul
	BYTE cRed[256];
	BYTE cGreen[256];
	BYTE cBlue[256];
	for(DWORD i=0; i<256; i++)
	{
		cRed[i] = (BYTE)max(min((i*dwRouge)/1000L, 255), 0);
		cGreen[i] = (BYTE)max(min((i*dwVert)/1000L, 255), 0);
		cBlue[i] = (BYTE)max(min((i*dwBleu)/1000L, 255), 0);
	}

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;

	// Détermination du nombre de couleurs
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);

	if(nColors && nColors<=256 && BmInfo->biBitCount!=24) // Il y a une palette -> on joue sur la palette
	{
		for(int i=0; i<nColors; i++)
		{
			bi->bmiColors[i].rgbRed = cRed[bi->bmiColors[i].rgbRed];
			bi->bmiColors[i].rgbGreen = cGreen[bi->bmiColors[i].rgbGreen];
			bi->bmiColors[i].rgbBlue = cBlue[bi->bmiColors[i].rgbBlue];
		}
	}
	else
	{	// 24 bits -> pas de palette (!! 32 bits non supporté)

		// Détermination de la zone des bits de l'image
		BYTE* lpLineBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
		BYTE* lpBits;

		for(int y=0; y<BmInfo->biHeight; y++)
		{
			lpBits = lpLineBits;
			for(int x=0; x<BmInfo->biWidth; x++)
			{
				*lpBits = cBlue[*lpBits];
				lpBits++;
				*lpBits = cGreen[*lpBits];
				lpBits++;
				*lpBits = cRed[*lpBits];
				lpBits++;
			}
			lpLineBits += nScanWidth;
		}

		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			lpBits = (BYTE*)&m_dwTransparentColor;
			lpBits[2] = cBlue[lpBits[2]];
			lpBits[1] = cGreen[lpBits[1]];
			lpBits[0] = cRed[lpBits[0]];
		}
	}

	GlobalUnlock(m_hDib);

	return TRUE;
}

// Correction de la saturation et de la teinte des couleurs. Les valeurs vont de -100 à +100
BOOL CImage::AdjustSaturationAndHue(int nValueSat, int nValueHue)
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	if(!nValueSat && !nValueHue)
		return TRUE; // Calcul inutile!!

	// Calcul du pourcentage en fonction de nValue originale
	double fValueSat, fValueHue;
	if(nValueSat>0)
		fValueSat = (4.0*(double)nValueSat)/100.0 + 1.0;
	else
		fValueSat = ((double)nValueSat)/100.0 + 1.0;

	fValueHue = (double)nValueHue/100.0;

	double h, s, l;

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;

	// Détermination du nombre de couleurs
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);

	if(nColors && nColors<=256 && BmInfo->biBitCount!=24) // Il y a une palette -> on joue sur la palette
	{
		for(int i=0; i<nColors; i++)
		{
			RGBtoHSL(bi->bmiColors[i].rgbRed, bi->bmiColors[i].rgbGreen,
				bi->bmiColors[i].rgbBlue, &h, &s, &l);

			if(nValueSat)
				s = max(min(s*fValueSat, 1.0), 0.0);
			if(nValueHue && h!=-1.0)
			{
				h += fValueHue;
				if(h<0.0)
					h += 1.0;
				else
					if(h>1.0)
						h -= 1.0;
			}

			HSLtoRGB(h, s, l, &bi->bmiColors[i].rgbRed, &bi->bmiColors[i].rgbGreen,
				&bi->bmiColors[i].rgbBlue);
		}
	}
	else
	{	// 24 bits -> pas de palette (!! 32 bits non supporté)

		// Détermination de la zone des bits de l'image
		BYTE* lpLineBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
		BYTE* lpBits;

		for(int y=0; y<BmInfo->biHeight; y++)
		{
			lpBits = lpLineBits;
			for(int x=0; x<BmInfo->biWidth; x++)
			{
				RGBtoHSL((BYTE)(*(lpBits+2)), (BYTE)(*(lpBits+1)), (BYTE)(*(lpBits)), &h, &s, &l);

				if(nValueSat)
					s = max(min(s*fValueSat, 1.0), 0.0);
				if(nValueHue && h!=-1.0)
				{
					h += fValueHue;
					if(h<0.0)
						h += 1.0;
					else
						if(h>1.0)
							h -= 1.0;
				}

				HSLtoRGB(h, s, l, (BYTE*)(lpBits+2), (BYTE*)(lpBits+1), (BYTE*)lpBits);
				lpBits+=3;
			}
			lpLineBits += nScanWidth;
		}

		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			lpBits = (BYTE*)&m_dwTransparentColor;
			RGBtoHSL((BYTE)lpBits[0], (BYTE)lpBits[1], (BYTE)lpBits[2], &h, &s, &l);

			if(nValueSat)
				s = max(min(s*fValueSat, 1.0), 0.0);
			if(nValueHue && h!=-1.0)
			{
				h += fValueHue;
				if(h<0.0)
					h += 1.0;
				else
					if(h>1.0)
						h -= 1.0;
			}

			HSLtoRGB(h, s, l, (BYTE*)&lpBits[0], (BYTE*)&lpBits[1], (BYTE*)&lpBits[2]);
		}
	}

	GlobalUnlock(m_hDib);

	return TRUE;
}

// Convertit un espace RGB (255,255,255) en HSL (1.0, 1.0, 1.0)
void CImage::RGBtoHSL(BYTE cRed, BYTE cGreen, BYTE cBlue, double* fHue, double* fSat, double* fLum)
{
	double r = (double)cRed/255.0;
	double g = (double)cGreen/255.0;
	double b = (double)cBlue/255.0;

	double fMax = max(r, max(g,b));
	double fMin = min(r, min(g,b));

	*fHue = -1.0;
	*fSat = 0.0;
	*fLum = (fMin+fMax)/2.0;
	double fDelta = fMax - fMin;
	if(fDelta==0.0)
		return;

	*fSat = fDelta;
	*fSat /= (*fLum<=0.5) ? (fMin+fMax) : (2.0-fMin-fMax);
	if(r==fMax)
		*fHue = g==fMin ? 5.0+(fMax-b)/fDelta : 1.0-(fMax-g)/fDelta;
	else
		if(g==fMax)
			*fHue = b==fMin ? 1.0+(fMax-r)/fDelta : 3.0-(fMax-b)/fDelta;
		else
			*fHue = r==fMin ? 3.0+(fMax-g)/fDelta : 5.0-(fMax-r)/fDelta;
	*fHue /= 6.0;
}

// Convertit un espace HSL (1.0, 1.0, 1.0) en RGB (255,255,255)
void CImage::HSLtoRGB(double fHue, double fSat, double fLum, BYTE* cRed, BYTE* cGreen, BYTE* cBlue)
{
	double r, g, b;

	double v = (fLum <= 0.5) ? (fLum*(1.0+fSat)) : (fLum+fSat-fLum*fSat);
	if(fSat==0.0 || fHue==-1.0)
	{
		*cRed = *cGreen = *cBlue = (BYTE)floor((fLum*255.0)+0.5);
		return;
	}
	fHue *= 6.0;
	double y = 2*fLum-v;
	double x = y+(v-y)*(fHue-(int)fHue);
	double z = v-(v-y)*(fHue-(int)fHue);
	switch ((int)fHue)
	{
		case  0: r=v; g=x; b=y; break;
		case  1: r=z; g=v; b=y; break;
		case  2: r=y; g=v; b=x; break;
		case  3: r=y; g=z; b=v; break;
		case  4: r=x; g=y; b=v; break;
		case  5: r=v; g=y; b=z; break;
		default: r=v; g=x; b=y; break;
	}
	*cRed = (BYTE)floor((r*255.0)+0.5);
	*cGreen = (BYTE)floor((g*255.0)+0.5);
	*cBlue = (BYTE)floor((b*255.0)+0.5);
}

#endif

//===================================================================
// Fonctions de rotation et miroir. Activer avec CIMAGE_ROTATION
//===================================================================

#if defined(CIMAGE_ROTATION)

// Effectue un effet de miroir vertical
BOOL CImage::VerticalMirror()
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
	HGLOBAL hNewDib=GlobalAlloc(GHND, GlobalSize(m_hDib));
	if(!hNewDib)
		return FALSE;  // Pas assez de mémoire ou problème

	LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;

	LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
	LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;

	// Détermination du nombre de couleurs
	int nColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);

	// Copie du Header + palette ds le nouveau bitmap
	CopyMemory(biDest, biSrc, BmSrcInfo->biSize+nColors*sizeof(RGBQUAD));

	// Détermination de la zone des bits de l'image source et largeur lignes en octets
	BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nColors*sizeof(RGBQUAD);
	int nScanWidth = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

	// Détermination de la zone des bits de l'image destination
	BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+nColors*sizeof(RGBQUAD);

	for(int y=0; y<BmSrcInfo->biHeight; y++)
	{
		CopyMemory(lpDestBits+(nScanWidth*(BmSrcInfo->biHeight-y-1)),
			lpSrcBits+(nScanWidth*y), nScanWidth);
	}

	GlobalUnlock(m_hDib);
	GlobalUnlock(hNewDib);
	GlobalFree(m_hDib);

	// On supprime l'ancien DIB et on le remplace par le nouveau
	m_hDib = hNewDib;
	return TRUE;
}

// Effectue un effet de miroir horizontal
BOOL CImage::HorizontalMirror()
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
	HGLOBAL hNewDib=GlobalAlloc(GHND, GlobalSize(m_hDib));
	if(!hNewDib)
		return FALSE;  // Pas assez de mémoire ou problème

	LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;

	LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
	LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;

	// Détermination du nombre de couleurs
	int nColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);

	// Copie du Header + palette ds le nouveau bitmap
	CopyMemory(biDest, biSrc, BmSrcInfo->biSize+nColors*sizeof(RGBQUAD));

	// Détermination de la zone des bits de l'image source et largeur lignes en octets
	BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nColors*sizeof(RGBQUAD);
	int nScanWidth = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

	// Détermination de la zone des bits de l'image destination
	BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+nColors*sizeof(RGBQUAD);

	// Traitement différent selon nombre de bits/pixel
	if(BmSrcInfo->biBitCount==24) // 24 bits
	{
		for(int y=0; y<BmSrcInfo->biHeight; y++)
			for(int x=0; x<BmSrcInfo->biWidth; x++)
			{
				lpDestBits[y*nScanWidth+x*3]=lpSrcBits[y*nScanWidth+(BmSrcInfo->biWidth-x-1)*3];
				lpDestBits[y*nScanWidth+x*3+1]=lpSrcBits[y*nScanWidth+(BmSrcInfo->biWidth-x-1)*3+1];
				lpDestBits[y*nScanWidth+x*3+2]=lpSrcBits[y*nScanWidth+(BmSrcInfo->biWidth-x-1)*3+2];
			}
	}

	if(BmSrcInfo->biBitCount==8) // 8 bits
	{
		for(int y=0; y<BmSrcInfo->biHeight; y++)
			for(int x=0; x<BmSrcInfo->biWidth; x++)
				lpDestBits[y*nScanWidth+x]=lpSrcBits[y*nScanWidth+(BmSrcInfo->biWidth-x-1)];
	}

	if(BmSrcInfo->biBitCount==4 // 4 bits
		|| BmSrcInfo->biBitCount==1) // 1 bits (N&B)
	{
		for(int y=0; y<BmSrcInfo->biHeight; y++)
			for(int x=0; x<BmSrcInfo->biWidth; x++)
				SetPixel(x, y,
					GetPixel(BmSrcInfo->biWidth-x-1, y, BmSrcInfo, nColors, nScanWidth, lpSrcBits),
					BmDestInfo, nColors, nScanWidth, lpDestBits);
	}

	GlobalUnlock(m_hDib);
	GlobalUnlock(hNewDib);
	GlobalFree(m_hDib);

	// On supprime l'ancien DIB et on le remplace par le nouveau
	m_hDib = hNewDib;
	return TRUE;
}

// Effectue une rotation du bitmap d'un quart de tour ou d'un demi-tour
//   1=90°, 2=180°, 3=270°
BOOL CImage::Rotate(int nAngle)
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	// Rotation de 90°
	if(nAngle==1)
	{
		LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;

		// Détermination du nombre de couleurs
		int nColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);

		// Détermination de la zone des bits de l'image source et largeur lignes en octets
		BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidthSrc = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

		// Largeur des lignes du nouveau bitmap
		int nScanWidthDest = WIDTHBYTES(BmSrcInfo->biHeight * BmSrcInfo->biBitCount);

		// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
		HGLOBAL hNewDib=GlobalAlloc(GHND, BmSrcInfo->biSize+nColors*sizeof(RGBQUAD)
			+ (nScanWidthDest*BmSrcInfo->biWidth));
		if(!hNewDib)
		{
			GlobalUnlock(m_hDib);
			return FALSE;  // Pas assez de mémoire ou problème
		}

		// Adresse du nouveau bitmap
		LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
		LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;

		// Copie du Header + palette ds le nouveau bitmap
		CopyMemory(biDest, biSrc, BmSrcInfo->biSize+nColors*sizeof(RGBQUAD));

		// On inverse la largeur et la hauteur
		BmDestInfo->biWidth = BmSrcInfo->biHeight;
		BmDestInfo->biHeight = BmSrcInfo->biWidth;

		// Détermination de la zone des bits de l'image source et largeur lignes en octets
		BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+nColors*sizeof(RGBQUAD);

		// Traitement différent selon nombre de bits/pixel
		if(BmSrcInfo->biBitCount==24) // 24 bits
		{
			for(int y=0; y<BmSrcInfo->biHeight; y++)
				for(int x=0; x<BmSrcInfo->biWidth; x++)
				{
					lpDestBits[x*nScanWidthDest+(BmDestInfo->biWidth-y-1)*3]=lpSrcBits[y*nScanWidthSrc+x*3];
					lpDestBits[x*nScanWidthDest+(BmDestInfo->biWidth-y-1)*3+1]=lpSrcBits[y*nScanWidthSrc+x*3+1];
					lpDestBits[x*nScanWidthDest+(BmDestInfo->biWidth-y-1)*3+2]=lpSrcBits[y*nScanWidthSrc+x*3+2];
				}
		}

		if(BmSrcInfo->biBitCount==8) // 8 bits
		{
			for(int y=0; y<BmSrcInfo->biHeight; y++)
				for(int x=0; x<BmSrcInfo->biWidth; x++)
					lpDestBits[x*nScanWidthDest+(BmDestInfo->biWidth-y-1)]=lpSrcBits[y*nScanWidthSrc+x];
		}

		if(BmSrcInfo->biBitCount==4 // 4 bits
			|| BmSrcInfo->biBitCount==1) // 1 bits (N&B)
		{
			for(int y=0; y<BmSrcInfo->biHeight; y++)
				for(int x=0; x<BmSrcInfo->biWidth; x++)
					SetPixel(BmDestInfo->biWidth-y-1, x,
						GetPixel(x, y, BmSrcInfo, nColors, nScanWidthSrc, lpSrcBits),
						BmDestInfo, nColors, nScanWidthDest, lpDestBits);
		}

		GlobalUnlock(m_hDib);
		GlobalUnlock(hNewDib);
		GlobalFree(m_hDib);

		// On supprime l'ancien DIB et on le remplace par le nouveau
		m_hDib = hNewDib;
		return TRUE;
	}

	// Rotation de 180° = Miroirs horz + vert
	if(nAngle==2)
	{
		if(VerticalMirror())
		{
			if(HorizontalMirror())
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
		}
		else
			return FALSE;
	}

	// Rotation de 270°
	if(nAngle==3)
	{
		LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;

		// Détermination du nombre de couleurs
		int nColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);

		// Détermination de la zone des bits de l'image source et largeur lignes en octets
		BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidthSrc = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

		// Largeur des lignes du nouveau bitmap
		int nScanWidthDest = WIDTHBYTES(BmSrcInfo->biHeight * BmSrcInfo->biBitCount);

		// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
		HGLOBAL hNewDib=GlobalAlloc(GHND, BmSrcInfo->biSize+nColors*sizeof(RGBQUAD)
			+ (nScanWidthDest*BmSrcInfo->biWidth));
		if(!hNewDib)
		{
			GlobalUnlock(m_hDib);
			return FALSE;  // Pas assez de mémoire ou problème
		}

		// Adresse du nouveau bitmap
		LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
		LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;

		// Copie du Header + palette ds le nouveau bitmap
		CopyMemory(biDest, biSrc, BmSrcInfo->biSize+nColors*sizeof(RGBQUAD));

		// On inverse la largeur et la hauteur
		BmDestInfo->biWidth = BmSrcInfo->biHeight;
		BmDestInfo->biHeight = BmSrcInfo->biWidth;

		// Détermination de la zone des bits de l'image source et largeur lignes en octets
		BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+nColors*sizeof(RGBQUAD);

		// Traitement différent selon nombre de bits/pixel
		if(BmSrcInfo->biBitCount==24) // 24 bits
		{
			for(int y=0; y<BmSrcInfo->biHeight; y++)
				for(int x=0; x<BmSrcInfo->biWidth; x++)
				{
					lpDestBits[(BmDestInfo->biHeight-x-1)*nScanWidthDest+y*3]=lpSrcBits[y*nScanWidthSrc+x*3];
					lpDestBits[(BmDestInfo->biHeight-x-1)*nScanWidthDest+y*3+1]=lpSrcBits[y*nScanWidthSrc+x*3+1];
					lpDestBits[(BmDestInfo->biHeight-x-1)*nScanWidthDest+y*3+2]=lpSrcBits[y*nScanWidthSrc+x*3+2];
				}
		}

		if(BmSrcInfo->biBitCount==8) // 8 bits
		{
			for(int y=0; y<BmSrcInfo->biHeight; y++)
				for(int x=0; x<BmSrcInfo->biWidth; x++)
					lpDestBits[(BmDestInfo->biHeight-x-1)*nScanWidthDest+y]=lpSrcBits[y*nScanWidthSrc+x];
		}

		if(BmSrcInfo->biBitCount==4 // 4 bits
			|| BmSrcInfo->biBitCount==1) // 1 bits (N&B)
		{
			for(int y=0; y<BmSrcInfo->biHeight; y++)
				for(int x=0; x<BmSrcInfo->biWidth; x++)
					SetPixel(y, BmDestInfo->biHeight-x-1,
						GetPixel(x, y, BmSrcInfo, nColors, nScanWidthSrc, lpSrcBits),
						BmDestInfo, nColors, nScanWidthDest, lpDestBits);
		}

		GlobalUnlock(m_hDib);
		GlobalUnlock(hNewDib);
		GlobalFree(m_hDib);

		// On supprime l'ancien DIB et on le remplace par le nouveau
		m_hDib = hNewDib;
		return TRUE;
	}
	return FALSE;
}

#endif

//===================================================================
// Fonction d'inversion des couleurs. Activer avec CIMAGE_NEGATIVE
//===================================================================

#if defined(CIMAGE_NEGATIVE)

// Transforme le bitmap en négatif
BOOL CImage::Negative()
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;

	// Détermination du nombre de couleurs
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);

	if(nColors && nColors<=256 && BmInfo->biBitCount!=24) // Il y a une palette -> on joue sur la palette
	{
		for(int i=0; i<nColors; i++)
		{
			bi->bmiColors[i].rgbRed=~bi->bmiColors[i].rgbRed;
			bi->bmiColors[i].rgbGreen=~bi->bmiColors[i].rgbGreen;
			bi->bmiColors[i].rgbBlue=~bi->bmiColors[i].rgbBlue;
		}
	}
	else
	{	// 24 bits -> pas de palette (!! 32 bits non supporté)

		// Détermination de la zone des bits de l'image
		BYTE* lpBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);

		for(int y=0; y<BmInfo->biHeight; y++)
		{
			for(int x=0; x<BmInfo->biWidth; x++)
			{
				lpBits[y*nScanWidth+x*3]=~lpBits[y*nScanWidth+x*3];
				lpBits[y*nScanWidth+x*3+1]=~lpBits[y*nScanWidth+x*3+1];
				lpBits[y*nScanWidth+x*3+2]=~lpBits[y*nScanWidth+x*3+2];
			}
		}
		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			lpBits = (BYTE*)&m_dwTransparentColor;
			lpBits[0]=~lpBits[0];
			lpBits[1]=~lpBits[1];
			lpBits[2]=~lpBits[2];
		}
	}

	GlobalUnlock(m_hDib);
	return TRUE;
}

#endif

//===================================================================
//     Fonctions de dithering. Activer avec CIMAGE_DITHERING
//===================================================================

#if defined(CIMAGE_DITHERING)

// Effectue le dithering de l'image, de m_nTypeImage vers nNewType
BOOL CImage::Dither(int nNewType, BOOL bDither)
{
	BOOL bRet=FALSE;

	if(!m_hDib)
		return FALSE;

	// Le type demandé est-il connu?
	if(nNewType<IMG_TYPE_COL24 || nNewType>IMG_TYPE_NB)
		return FALSE;

	// Cas spécial: image source en 16 ou 32 bits. Formats non supportés -> passage en 24 bits avant le dithering
	if(GetBPP()==32 || GetBPP()==16)
	{
		LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;

		// Détermination du nombre de couleurs
		int nColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : NULL;
		int nScanWidthSrc = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

		// Détermination de la zone des bits de l'image source et largeur lignes en octets
		BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nColors*sizeof(RGBQUAD);

		// Largeur des lignes du nouveau bitmap en 24 bits
		int nScanWidthDest = WIDTHBYTES(BmSrcInfo->biWidth * 24);

		// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
		HGLOBAL hNewDib=GlobalAlloc(GHND, BmSrcInfo->biSize+(nScanWidthDest*BmSrcInfo->biHeight));
		if(!hNewDib)
		{
			GlobalUnlock(m_hDib);
			return FALSE;  // Pas assez de mémoire ou problème
		}

		// Adresse du nouveau bitmap
		LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
		LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;

		// Copie du Header ds le nouveau bitmap
		CopyMemory(biDest, biSrc, BmSrcInfo->biSize);

		// Changement des paramètres sur le nouveau bitmap
		BmDestInfo->biBitCount = 24;
		BmDestInfo->biClrUsed = 0;
		BmDestInfo->biSizeImage = nScanWidthDest*BmDestInfo->biHeight;

		// Détermination de la zone des bits de l'image source et largeur lignes en octets
		BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize;

		// Copie Pixel à pixel de l'ancien vers le nouveau bitmap
		if(BmSrcInfo->biBitCount==32) // de 32 vers 24 bits
		{
			for(int y=0; y<BmDestInfo->biHeight; y++)
			{
				BYTE* lpSrc = lpSrcBits + (y*nScanWidthSrc);
				BYTE* lpDest = lpDestBits + (y*nScanWidthDest);
				for(int x=0; x<BmDestInfo->biWidth; x++)
				{
					*(lpDest++) = *(lpSrc++);
					*(lpDest++) = *(lpSrc++);
					*(lpDest++) = *(lpSrc++);
					lpSrc++; // on saute un octet pour chaque pixel
				}
			}
		}
		else  // 16 vers 24 bits (32000 couleurs, pas 65000)
		{
			for(int y=0; y<BmDestInfo->biHeight; y++)
			{
				WORD* lpSrc = (WORD*)(lpSrcBits + (y*nScanWidthSrc));
				BYTE* lpDest = lpDestBits + (y*nScanWidthDest);
				for(int x=0; x<BmDestInfo->biWidth; x++)
				{
					*(lpDest++) = (BYTE)((*(lpSrc) & 0x1F) * 8.2258 + 0.5);
					*(lpDest++) = (BYTE)(((*(lpSrc)>>5) & 0x1F) * 8.2258 + 0.5);
					*(lpDest++) = (BYTE)(((*(lpSrc)>>10) & 0x1F) * 8.2258 + 0.5);
					lpSrc++; // on passe au pixel suivant
				}
			}
		}

		// Pas de couleur transparente en 32 ou 16 bits
		m_dwTransparentColor = NULL;

		GlobalUnlock(m_hDib);
		GlobalUnlock(hNewDib);
		GlobalFree(m_hDib);

		// On supprime l'ancien DIB et on le remplace par le nouveau
		m_hDib = hNewDib;
		m_nTypeImage = IMG_TYPE_COL24;
	}

	// Pas de dithering si le type demandé est celui en cours (ou que la transformation en 24 bits a suffit)
	if(nNewType==m_nTypeImage)
		return TRUE;

	// Si type actuel non connu -> on le cherche (couleur par défaut)
	if(m_nTypeImage==IMG_TYPE_UNKNOWN)
		m_nTypeImage = GetDefaultType(GetBPP());

	// Si transparent -> On retrouve la position d'un pixel transparent
	BOOL bOk = FALSE;
	BOOL bDoIt = FALSE;
	int xTrans = 0;
	int yTrans = 0;
	if(m_dwTransparentColor & 0x80000000L)
	{
		LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);
		BYTE* lpBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);
		DWORD dwColor = m_dwTransparentColor & 0x7FFFFFFFL;
		for(yTrans=0; yTrans<BmInfo->biHeight && !bOk; yTrans++)
			for(int xTrans=0; xTrans<BmInfo->biWidth && !bOk; xTrans++)
				if(dwColor == GetPixel(xTrans, yTrans, BmInfo, nColors, nScanWidth, lpBits))
					bOk = TRUE;
		GlobalUnlock(m_hDib);
	}

	// De 24 bits vers tous les autres
	if(m_nTypeImage==IMG_TYPE_COL24)
	{
		switch(nNewType)
		{
			case IMG_TYPE_COL256:
				bRet = DitherQuantize(256, bDither);
				if(bRet)
					bDoIt = TRUE;
				break;
			case IMG_TYPE_COL16:
				bRet = DitherQuantize(16, bDither);
				if(bRet)
					bDoIt = TRUE;
				break;
			case IMG_TYPE_NG256:
				bRet = DitherGrayScale();
				// Cas particulier du 24 bits vers
				//   256NG: réduction facile, sans dithering
				{
					LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
					LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;

					// Si != de 24 bits -> c'est pas bon
					if(BmSrcInfo->biBitCount!=24)
					{
						GlobalUnlock(m_hDib);
						return FALSE;  // Pas assez de mémoire ou problème
					}

					// Détermination du nombre de couleurs
					int nColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);

					// Détermination de la zone des bits de l'image source et largeur lignes en octets
					BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nColors*sizeof(RGBQUAD);
					int nScanWidthSrc = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

					// Largeur des lignes du nouveau bitmap
					int nScanWidthDest = WIDTHBYTES(BmSrcInfo->biWidth * 8);

					// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
					HGLOBAL hNewDib=GlobalAlloc(GHND, BmSrcInfo->biSize+256*sizeof(RGBQUAD)
						+ (nScanWidthDest*BmSrcInfo->biHeight));
					if(!hNewDib)
					{
						GlobalUnlock(m_hDib);
						return FALSE;  // Pas assez de mémoire ou problème
					}

					// Adresse du nouveau bitmap
					LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
					LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;

					// Copie du Header ds le nouveau bitmap
					CopyMemory(biDest, biSrc, BmSrcInfo->biSize);

					// Création palette en 256NG
					for(int i=0; i<256; i++)
						biDest->bmiColors[i].rgbRed = biDest->bmiColors[i].rgbGreen
							= biDest->bmiColors[i].rgbBlue = i;

					// Changement de paramètres ds la structure
					BmDestInfo->biBitCount = 8;
					BmDestInfo->biClrImportant = BmDestInfo->biClrUsed = 256;
					BmDestInfo->biSizeImage = nScanWidthDest*BmSrcInfo->biHeight;

					// Détermination de la zone des bits de l'image source et largeur lignes en octets
					BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+256*sizeof(RGBQUAD);

					// Copie des octets
					BYTE* lpDest = lpDestBits;
					BYTE* lpSrc = lpSrcBits;
					int j;
					for(i=0; i<BmSrcInfo->biHeight; i++)
					{
						for(j=0; j<BmSrcInfo->biWidth; j++)
						{
							*(lpDest++) = *lpSrc;
							lpSrc += 3;
						}
						lpDestBits += nScanWidthDest;
						lpSrcBits += nScanWidthSrc;
						lpDest = lpDestBits;
						lpSrc = lpSrcBits;
					}
					GlobalUnlock(m_hDib);
					GlobalUnlock(hNewDib);
					GlobalFree(m_hDib);
					m_hDib = hNewDib;
					bRet = TRUE;
				}
				break;
			case IMG_TYPE_NG16:
				if(bRet = DitherQuantize(16, bDither))
					if(bRet = DitherGrayScale())
						bDoIt = TRUE;
				break;
			case IMG_TYPE_NB:
				if(bRet = DitherQuantize(2, bDither))
					m_dwTransparentColor = NULL;
				break;
		}
	}

	// De 256 couleurs vers tous les autres
	if(m_nTypeImage==IMG_TYPE_COL256)
	{
		switch(nNewType)
		{
			case IMG_TYPE_COL24:
				bRet = DitherExpand(nNewType);
				break;
			case IMG_TYPE_COL16:
				if(bRet= DitherExpand(IMG_TYPE_COL24))
					if(bRet = DitherQuantize(16, bDither))
						bDoIt = TRUE;
				break;
			case IMG_TYPE_NG256:
				bRet = DitherGrayScale();
				break;
			case IMG_TYPE_NG16:
				if(bRet = DitherExpand(IMG_TYPE_COL24))
					if(bRet = DitherQuantize(16, bDither))
						if(bRet = DitherGrayScale())
							bDoIt = TRUE;
				break;
			case IMG_TYPE_NB:
				if(bRet = DitherExpand(IMG_TYPE_COL24))
					if(bRet = DitherQuantize(2, bDither))
						m_dwTransparentColor = NULL;
				break;
		}
	}

	// De 16 couleurs vers tous les autres
	if(m_nTypeImage==IMG_TYPE_COL16)
	{
		switch(nNewType)
		{
			case IMG_TYPE_COL24:
			case IMG_TYPE_COL256:
				bRet = DitherExpand(nNewType);
				break;
			case IMG_TYPE_NG256:
				if(bRet = DitherGrayScale())
					bRet = DitherExpand(nNewType);
				break;
			case IMG_TYPE_NG16:
				bRet = DitherGrayScale();
				break;
			case IMG_TYPE_NB:
				if(bRet = DitherExpand(IMG_TYPE_COL24))
					if(bRet = DitherQuantize(2, bDither))
						m_dwTransparentColor = NULL;
				break;
		}
	}

	// De 256 niveaux de gris vers tous les autres
	if(m_nTypeImage==IMG_TYPE_NG256)
	{
		switch(nNewType)
		{
			case IMG_TYPE_COL24:
				bRet = DitherExpand(nNewType);
				break;
			case IMG_TYPE_COL256:
				bRet = TRUE;
				break;
			case IMG_TYPE_COL16:
				if(bRet = DitherExpand(IMG_TYPE_COL24))
					if(bRet = DitherQuantize(16, bDither))
						bDoIt = TRUE;
				break;
			case IMG_TYPE_NG16:
				if(bRet = DitherExpand(IMG_TYPE_COL24))
					if(bRet = DitherQuantize(16, bDither))
						if(bRet = DitherGrayScale())
							bDoIt = TRUE;
				break;
			case IMG_TYPE_NB:
				if(bRet = DitherExpand(IMG_TYPE_COL24))
					if(bRet = DitherQuantize(2, bDither))
						m_dwTransparentColor = NULL;
				break;
		}
	}

	// De 16 niveaux de gris vers tous les autres
	if(m_nTypeImage==IMG_TYPE_NG16)
	{
		switch(nNewType)
		{
			case IMG_TYPE_COL24:
			case IMG_TYPE_COL256:
			case IMG_TYPE_NG256:
				bRet = DitherExpand(nNewType);
				break;
			case IMG_TYPE_COL16:
				bRet = TRUE;
				break;
			case IMG_TYPE_NB:
				if(bRet = DitherExpand(IMG_TYPE_COL24))
					if(bRet = DitherQuantize(2, bDither))
						m_dwTransparentColor = NULL;
				break;
		}
	}

	// De Noir et Blanc vers tous les autres
	if(m_nTypeImage==IMG_TYPE_NB)
	{
		bRet = DitherExpand(nNewType);
	}
	
	if(bRet)
	{
		m_nTypeImage=nNewType;

		// Adaptation de la couleur pour mode transparent
		if(bOk && bDoIt)
		{
			LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
			m_dwTransparentColor = GetPixel(xTrans, yTrans, BmInfo) | 0x80000000L;
			GlobalUnlock(m_hDib);
		}
	}

	return bRet;
}

// Expansion d'un bitmap vers un nombre de couleurs plus élevé
BOOL CImage::DitherExpand(int nNewType)
{
	if(!m_hDib)
		return FALSE;

	LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;

	// Détermination du nombre de couleurs
	int nColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);
	int nScanWidthSrc = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

	// Détermination de la zone des bits de l'image source et largeur lignes en octets
	BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nColors*sizeof(RGBQUAD);

	// Détermination du nombre de bits/pixel sur nouveau bitmap
	int nNewTypeBits;
	switch(nNewType)
	{
		case IMG_TYPE_COL24:
			nNewTypeBits=24;
			break;
		case IMG_TYPE_COL256:
		case IMG_TYPE_NG256:
			nNewTypeBits=8;
			break;
		case IMG_TYPE_COL16:
		case IMG_TYPE_NG16:
			nNewTypeBits=4;
			break;
		case IMG_TYPE_NB:
			nNewTypeBits=1;
			break;
	}

	// Largeur des lignes du nouveau bitmap
	int nScanWidthDest = WIDTHBYTES(BmSrcInfo->biWidth * nNewTypeBits);
	// Détermination du nombre de couleurs du bitmap destination
	int nColorsDest = 0x1FF & (1 << nNewTypeBits);

	// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
	HGLOBAL hNewDib=GlobalAlloc(GHND, BmSrcInfo->biSize+nColorsDest*sizeof(RGBQUAD)
		+ (nScanWidthDest*BmSrcInfo->biHeight));
	if(!hNewDib)
	{
		GlobalUnlock(m_hDib);
		return FALSE;  // Pas assez de mémoire ou problème
	}

	// Adresse du nouveau bitmap
	LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
	LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;

	// Copie du Header + palette ds le nouveau bitmap
	CopyMemory(biDest, biSrc, BmSrcInfo->biSize);
	for(int i=0; i<min(nColors, nColorsDest); i++)
		biDest->bmiColors[i]=biSrc->bmiColors[i];

	// Changement des paramètres sur le nouveau bitmap
	BmDestInfo->biBitCount = nNewTypeBits;
	BmDestInfo->biClrUsed = nColorsDest;
	BmDestInfo->biSizeImage = nScanWidthDest*BmDestInfo->biHeight;

	// Détermination de la zone des bits de l'image source et largeur lignes en octets
	BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+nColorsDest*sizeof(RGBQUAD);

	// Copie Pixel à pixel de l'ancien vers le nouveau bitmap
	if(BmDestInfo->biBitCount==24)
	{
		RGBQUAD Couleur;
		for(int y=0; y<BmDestInfo->biHeight; y++)
			for(int x=0; x<BmDestInfo->biWidth; x++)
			{
				Couleur = biSrc->bmiColors[GetPixel(x, y, BmSrcInfo, nColors, nScanWidthSrc, lpSrcBits)];
				SetPixel(x, y, 
					Couleur.rgbBlue<<16 | Couleur.rgbGreen<<8 | Couleur.rgbRed,
					BmDestInfo, nColorsDest, nScanWidthDest, lpDestBits);
			}
		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			Couleur = biSrc->bmiColors[m_dwTransparentColor];
			m_dwTransparentColor = Couleur.rgbBlue<<16 | Couleur.rgbGreen<<8
				| Couleur.rgbRed | 0x80000000L;
		}
	}
	else
	{
		for(int y=0; y<BmDestInfo->biHeight; y++)
			for(int x=0; x<BmDestInfo->biWidth; x++)
				SetPixel(x, y,
					GetPixel(x, y, BmSrcInfo, nColors, nScanWidthSrc, lpSrcBits),
					BmDestInfo, nColorsDest, nScanWidthDest, lpDestBits);
	}

	GlobalUnlock(m_hDib);
	GlobalUnlock(hNewDib);
	GlobalFree(m_hDib);

	// On supprime l'ancien DIB et on le remplace par le nouveau
	m_hDib = hNewDib;

	return TRUE;
}

// Transforme en niveaux de gris le bitmap en cours
BOOL CImage::DitherGrayScale()
{
	if(!m_hDib)
		return FALSE;	// DIB non valide

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;

	// Détermination du nombre de couleurs
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);

	if(nColors && nColors<=256 && BmInfo->biBitCount!=24) // Il y a une palette -> on joue sur la palette
	{
		for(int i=0; i<nColors; i++)
		{
			bi->bmiColors[i].rgbRed = bi->bmiColors[i].rgbGreen
				= bi->bmiColors[i].rgbBlue
				= GRAYSCALE(bi->bmiColors[i].rgbRed, bi->bmiColors[i].rgbGreen,
					bi->bmiColors[i].rgbBlue);
		}
	}
	else
	{	// 24 bits -> pas de palette (!! 32 bits non supporté)
		int nVal;
		// Détermination de la zone des bits de l'image
		BYTE* lpBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);

		for(int y=0; y<BmInfo->biHeight; y++)
		{
			for(int x=0; x<BmInfo->biWidth; x++)
			{
				nVal = y*nScanWidth+x*3;
				lpBits[nVal] = lpBits[nVal+1] = lpBits[nVal+2]
						= GRAYSCALE(lpBits[nVal+2], lpBits[nVal+1], lpBits[nVal]);
			}
		}
		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			lpBits = (BYTE*)&m_dwTransparentColor;
			m_dwTransparentColor = GRAYSCALE(lpBits[2], lpBits[1], lpBits[0]) | 0x80000000L;
		}
	}

	GlobalUnlock(m_hDib);

	return TRUE;
}

// Réduction du nombre de couleurs d'une image par méthode de quantization
// L'image d'entrée est TOUJOURS en 24BPP (expand si besoin)
BOOL CImage::DitherQuantize(UINT nNbrColors, BOOL bDither)
{
	//Traitement spécial si N&B. bDither non pris en compte ici
	if(nNbrColors == 2)
	{
		if(!DitherGrayScale())
			return FALSE;

		BYTE cDitherMatrix[8][8] =
			{
				{	  0, 192,  48, 240,  12, 204,  60, 252 },
				{	128,  64, 176, 112, 140,  76, 188, 124 },
				{	 32, 224,  16, 208,  44, 236,  28, 220 },
				{	160,  96, 144,  80, 172, 108, 156,  92 },
				{	  8, 200,  56, 248,   4, 196,  52, 244 },
				{	136,  72, 184, 120, 132,  68, 180, 116 },
				{	 40, 232,  24, 216,  36, 228,  20, 212 },
				{	168, 104, 152,  88, 164, 100, 148,  84 }
			};

		// Récupération des paramètre du bitmap ds m_hDib
		LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
		LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;
		int nBmColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);
		BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nBmColors*sizeof(RGBQUAD);
		int nScanWidthSrc = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);
		// Création du nouveau DIB
		int nScanWidthDest = WIDTHBYTES(BmSrcInfo->biWidth);
		HGLOBAL hNewDib=GlobalAlloc(GHND, BmSrcInfo->biSize+2*sizeof(RGBQUAD)
			+ (nScanWidthDest * BmSrcInfo->biHeight));
		if(!hNewDib)
		{
			GlobalUnlock(m_hDib);
			return FALSE;  // Pas assez de mémoire ou problème
		}
		LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
		LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;
		CopyMemory(biDest, BmSrcInfo, BmSrcInfo->biSize);
		BmDestInfo->biBitCount = 1;
		BmDestInfo->biClrUsed = BmDestInfo->biClrImportant = 2;
		BmDestInfo->biSizeImage = nScanWidthDest * BmDestInfo->biHeight;

		// Init de la table des couleurs
		memset(&biDest->bmiColors[0], 0, sizeof(biDest->bmiColors[0]));
		memset(&biDest->bmiColors[1], MAX_DITHER_RGB, sizeof(biDest->bmiColors[1]));

		BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+2*sizeof(RGBQUAD);

		// Dither image with the ordered dithering technique.
		BYTE* lpSrc = lpSrcBits;
		if(bDither)
		{
			for(int y=0; y<BmDestInfo->biHeight; y++)
			{
				for(int x=0; x<BmDestInfo->biWidth; x++)
				{
					SetPixel(x, y,
						(*lpSrc) > cDitherMatrix[y & 0x07][x & 0x07] ? 1 : 0,
						BmDestInfo, 2, nScanWidthDest, lpDestBits);
					lpSrc += 3;
				}
				lpSrcBits += nScanWidthSrc;
				lpSrc = lpSrcBits;
			}
		}
		else
		{
			for(int y=0; y<BmDestInfo->biHeight; y++)
			{
				for(int x=0; x<BmDestInfo->biWidth; x++)
				{
					SetPixel(x, y, (*lpSrc) > 127 ? 1 : 0,
						BmDestInfo, 2, nScanWidthDest, lpDestBits);
					lpSrc += 3;
				}
				lpSrcBits += nScanWidthSrc;
				lpSrc = lpSrcBits;
			}
		}
		GlobalUnlock(m_hDib);
		GlobalUnlock(hNewDib);
		GlobalFree(m_hDib);
		m_hDib = hNewDib;
		return TRUE;
	}

	// Calcule la profondeur de l'arbre de quantification
	UINT nColors = nNbrColors;
	for(int nDepth=1; nColors; nDepth++)
		nColors >>= 2;
	if(bDither)
		nDepth--;

	// Création et init du "cube" de quantization
	DitherCubeInfo CubeInfo;

	memset(&CubeInfo, 0, sizeof(CubeInfo));

	if(nDepth > MAX_TREE_DEPTH)
		nDepth = MAX_TREE_DEPTH;
	if(nDepth < 2)
		nDepth=2;
	CubeInfo.wDepth = (WORD)nDepth;

	// Initialise le RootNode du cube
	CubeInfo.RootNode = DitherGetNodeInfo(&CubeInfo, 0, 0, NULL);
	CubeInfo.dwSquares = (DWORD*)malloc((MAX_DITHER_RGB+MAX_DITHER_RGB+1)*sizeof(DWORD));
	if(!CubeInfo.RootNode || !CubeInfo.dwSquares)
	{
		DitherDestroyCubeInfo(&CubeInfo);
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	CubeInfo.RootNode->Parent = CubeInfo.RootNode;
	CubeInfo.RootNode->fQuantizationError = 0.0;
	CubeInfo.dwColors = NULL;
	CubeInfo.dwSquares += MAX_DITHER_RGB;
	for(int i=-MAX_DITHER_RGB; i <= MAX_DITHER_RGB; i++)
		CubeInfo.dwSquares[i]=i*i;
	CubeInfo.bDither = bDither;
	
	// Initialise les ressources pour le dithering
	if(CubeInfo.bDither)
	{
		CubeInfo.nCache = (int *)malloc((1 << 18)*sizeof(int));
		CubeInfo.cRangeLimit = (BYTE*)malloc(3*(MAX_DITHER_RGB+1)*sizeof(BYTE));
		if(!CubeInfo.nCache || !CubeInfo.cRangeLimit)
		{
			DitherDestroyCubeInfo(&CubeInfo);
			GlobalUnlock(m_hDib);
			return FALSE;
		}
		// Initialise les tables des limites
		for(i=0; i<=MAX_DITHER_RGB; i++)
		{
			CubeInfo.cRangeLimit[i]=0;
			CubeInfo.cRangeLimit[i+(MAX_DITHER_RGB+1)] = (BYTE)i;
			CubeInfo.cRangeLimit[i+((MAX_DITHER_RGB+1)*2)] = MAX_DITHER_RGB;
		}
		CubeInfo.cRangeLimit += (MAX_DITHER_RGB+1);
		// Initialise le cache des couleurs
		for(i=0; i<(1 << 18); i++)
			CubeInfo.nCache[i] = -1;
		double fWeight=1.0;
		for(i=0; i<ERROR_QUEUE_LENGTH; i++)
		{
			CubeInfo.fWeights[ERROR_QUEUE_LENGTH-i-1] = 1.0/fWeight;
			fWeight *= exp(log(MAX_DITHER_RGB+1)/(ERROR_QUEUE_LENGTH-1));
		}
		fWeight = 0.0;
		for(i=0; i<ERROR_QUEUE_LENGTH; i++)
			fWeight += CubeInfo.fWeights[i];
		for(i=0; i<ERROR_QUEUE_LENGTH; i++)
			CubeInfo.fWeights[i] /= fWeight;
	}

	// Récupération des paramètre du bitmap ds m_hDib
	LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;
	int nBmColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);
	BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nBmColors*sizeof(RGBQUAD);
	int nScanWidthSrc = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

	// Classification des couleurs
	double fDistanceSquared;
	DitherNodeInfo* NodeInfo;
	double fBisect[] = { 128.0, 64.0, 32.0, 16.0, 8.0, 4.0, 2.0, 1.0, 0.5 };

	DWORD* dwSquares=CubeInfo.dwSquares;
	CubeInfo.RootNode->fQuantizationError =
		3.0*(MAX_DITHER_RGB/2.0)*(MAX_DITHER_RGB/2.0)*BmSrcInfo->biWidth;
	for(i=0; i<BmSrcInfo->biHeight; i++)
	{
		for(int j=0; j<BmSrcInfo->biWidth; j++)
		{
			if (CubeInfo.dwNodes > MAX_NODES)
			{
				// Suppression d'un niveau si arbre trop grand
				DitherPruneLevel(&CubeInfo, CubeInfo.RootNode);
				CubeInfo.wDepth--;
			}

			// Début à RootNode, puis on descend ds l'arbre
			NodeInfo = CubeInfo.RootNode;
			int nIndex = MAX_TREE_DEPTH-1;
			double fMidRed = MAX_DITHER_RGB/2.0;
			double fMidGreen = MAX_DITHER_RGB/2.0;
			double fMidBlue = MAX_DITHER_RGB/2.0;

			RGBQUAD Packet;
			DWORD PixelColor = GetPixel(j, i, BmSrcInfo, nBmColors, nScanWidthSrc, lpSrcBits);
			Packet.rgbBlue = (BYTE)((PixelColor>>16) & 0xFF);
			Packet.rgbGreen = (BYTE)((PixelColor>>8) & 0xFF);
			Packet.rgbRed = (BYTE)(PixelColor & 0xFF);
			Packet.rgbReserved = NULL;

			for(int nLevel=1; nLevel<=CubeInfo.wDepth; nLevel++)
			{
				UINT nId=((((UINT)(Packet.rgbRed) >> nIndex) & 0x01) << 2) |
					((((UINT)(Packet.rgbGreen) >> nIndex) & 0x01) << 1) |
					(((UINT)(Packet.rgbBlue) >> nIndex) & 0x01);
				fMidRed += nId & 4 ? fBisect[nLevel] : -fBisect[nLevel];
				fMidGreen += nId & 2 ? fBisect[nLevel] : -fBisect[nLevel];
				fMidBlue += nId & 1 ? fBisect[nLevel] : -fBisect[nLevel];
				if(!NodeInfo->Child[nId])
				{
					// Affecte les couleurs d'un nouveau node
					NodeInfo->cCensus |= (1 << nId);
					NodeInfo->Child[nId]=DitherGetNodeInfo(&CubeInfo, nId, nLevel, NodeInfo);
					if(!NodeInfo->Child[nId])
					{
						DitherDestroyCubeInfo(&CubeInfo);
						GlobalUnlock(m_hDib);
						return FALSE;
					}
					if(nLevel == CubeInfo.wDepth)
						CubeInfo.dwColors++;
				}
				NodeInfo = NodeInfo->Child[nId];
				if(nLevel != 8)
				{
					// Approximate the quantization error represented by this node.
					fDistanceSquared = dwSquares[(int)((UINT)(Packet.rgbRed)-fMidRed)]+
						dwSquares[(int)((UINT)(Packet.rgbGreen)-fMidGreen)]+
						dwSquares[(int)((UINT)(Packet.rgbBlue)-fMidBlue)];
					NodeInfo->fQuantizationError += fDistanceSquared;
				}
				nIndex--;
			}

			// Sum RGB values for this leaf for later derivation of the mean cube color.
			NodeInfo->dwNumberUnique++;
			NodeInfo->fTotalRed += Packet.rgbRed;
			NodeInfo->fTotalGreen += Packet.rgbGreen;
			NodeInfo->fTotalBlue += Packet.rgbBlue;
		}
	}

	// Reduce the number of colors in the continuous tone image.
	if((CubeInfo.dwColors >> 1) < nNbrColors)
		bDither = FALSE;
	if(nNbrColors < CubeInfo.dwColors)
	{
		// Réduction du nombre de couleurs
		DitherReduction(&CubeInfo, nNbrColors);
		UINT nSpan = (UINT)CubeInfo.dwColors;
		CubeInfo.fNextPruningThreshold = 0.0;
		while(CubeInfo.dwColors > nNbrColors)
		{
			CubeInfo.fPruningThreshold = CubeInfo.fNextPruningThreshold;
			CubeInfo.fNextPruningThreshold = CubeInfo.RootNode->fQuantizationError;
			CubeInfo.dwColors = 0;
			DitherReduce(&CubeInfo, CubeInfo.RootNode);
		}
	}

	// Création du nouveau DIB
	int nNewBitCount = (nNbrColors==2) ? 1 : (nNbrColors==16 ? 4 : 8);
	int nScanWidthDest = WIDTHBYTES(BmSrcInfo->biWidth * nNewBitCount);
	HGLOBAL hNewDib=GlobalAlloc(GHND, BmSrcInfo->biSize+nNbrColors*sizeof(RGBQUAD)
		+ (nScanWidthDest * BmSrcInfo->biHeight));
	if(!hNewDib)
	{
		DitherDestroyCubeInfo(&CubeInfo);
		GlobalUnlock(m_hDib);
		return FALSE;  // Pas assez de mémoire ou problème
	}
	LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
	LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;
	CopyMemory(biDest, BmSrcInfo, BmSrcInfo->biSize);
	BmDestInfo->biBitCount = nNewBitCount;
	BmDestInfo->biClrUsed = BmDestInfo->biClrImportant = nNbrColors;
	BmDestInfo->biSizeImage = nScanWidthDest * BmDestInfo->biHeight;
	
	// Assignement des couleurs
	CubeInfo.biColorMap = biDest;
	CubeInfo.dwColors = 0;
	DitherDefineColormap(&CubeInfo, CubeInfo.RootNode);

	// Create a reduced color image.
	if(bDither)
	{
		// Initialize error queue.
		for(i=0; i<ERROR_QUEUE_LENGTH; i++)
			CubeInfo.Error[i].nRed = CubeInfo.Error[i].nGreen = CubeInfo.Error[i].nBlue = 0;

		// Distribute quantization error along a Hilbert curve.
		CubeInfo.x = CubeInfo.y = 0;
		i = (BmSrcInfo->biWidth>BmSrcInfo->biHeight)? BmSrcInfo->biWidth : BmSrcInfo->biHeight;
		for (nDepth=1; i; nDepth++)
			i>>=1;
		DitherHilbertCurve(&CubeInfo, BmSrcInfo, biDest, nDepth-1, N_GRAVITY);
		DitherDither(&CubeInfo, BmSrcInfo, biDest, FORGET_GRAVITY);
	}
	else
	{
		BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+nNbrColors*sizeof(RGBQUAD);
		for(i=0; i<BmSrcInfo->biHeight; i++)
		{
			for(int j=0; j<BmSrcInfo->biWidth; j++)
			{
				// Identify the deepest node containing the pixel's color.
				NodeInfo = CubeInfo.RootNode;

				RGBQUAD Packet;
				DWORD PixelColor = GetPixel(j, i, BmSrcInfo, nBmColors, nScanWidthSrc, lpSrcBits);
				Packet.rgbBlue = (BYTE)((PixelColor>>16) & 0xFF);
				Packet.rgbGreen = (BYTE)((PixelColor>>8) & 0xFF);
				Packet.rgbRed = (BYTE)(PixelColor & 0xFF);
				Packet.rgbReserved = NULL;

				for(WORD wIndex = MAX_TREE_DEPTH-1; (int)wIndex>0; wIndex--)
				{
					UINT nId=(((UINT)(Packet.rgbRed) >> wIndex) & 0x01) << 2 |
						(((UINT)(Packet.rgbGreen) >> wIndex) & 0x01) << 1 |
						(((UINT)(Packet.rgbBlue) >> wIndex) & 0x01);
					if((NodeInfo->cCensus & (1 << nId)) == 0)
						break;
					NodeInfo=NodeInfo->Child[nId];
				}
				// Find closest color among siblings and their children.
				CubeInfo.rgbColor.rgbRed = Packet.rgbRed;
				CubeInfo.rgbColor.rgbGreen = Packet.rgbGreen;
				CubeInfo.rgbColor.rgbBlue = Packet.rgbBlue;
				CubeInfo.fDistance = 3.0*(MAX_DITHER_RGB+1)*(MAX_DITHER_RGB+1);
				DitherClosestColor(&CubeInfo, NodeInfo->Parent);
				wIndex = (WORD)CubeInfo.dwColorNumber;
				// Cette version ne supporte qu'une palette en sortie
				SetPixel(j, i, wIndex, BmDestInfo, nNbrColors, nScanWidthDest, lpDestBits);
			}
		}
	}

	DitherDestroyCubeInfo(&CubeInfo);
	GlobalUnlock(m_hDib);
	GlobalUnlock(hNewDib);
	GlobalFree(m_hDib);
	m_hDib = hNewDib;
	return TRUE;
}

// Allocation mémoire et construction d'un nouveau Node
DitherNodeInfo* CImage::DitherGetNodeInfo(DitherCubeInfo *pCubeInfo, UINT nId, UINT nLevel, DitherNodeInfo *pParentNode)
{
	DitherNodeInfo* pNodeInfo;

	if(!pCubeInfo->dwFreeNodes)
	{
		// Allocate a new nodes of nodes.
		DitherNodes* pNodes = (DitherNodes*)malloc(sizeof(DitherNodes));
		if(!pNodes)
			return NULL;

		pNodes->Next = pCubeInfo->NodeQueue;
		pCubeInfo->NodeQueue = pNodes;
		pCubeInfo->NextNode = pNodes->Nodes;
		pCubeInfo->dwFreeNodes = NODES_IN_A_LIST;
	}

	pCubeInfo->dwNodes++;
	pCubeInfo->dwFreeNodes--;
	pNodeInfo = pCubeInfo->NextNode++;
	pNodeInfo->Parent = pParentNode;

	for(int i=0; i<8; i++)
		pNodeInfo->Child[i] = NULL;

	pNodeInfo->cId = nId;
	pNodeInfo->cLevel = nLevel;
	pNodeInfo->cCensus = 0;
	pNodeInfo->dwNumberUnique = NULL;
	pNodeInfo->fQuantizationError = 0.0;
	pNodeInfo->fTotalRed = 0.0;
	pNodeInfo->fTotalGreen = 0.0;
	pNodeInfo->fTotalBlue = 0.0;

	return pNodeInfo;
}

// Suppression des nodes au niveau le plus bas et mélange des couleurs
void CImage::DitherPruneLevel(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo)
{
	// Traverse any children.
	if(pNodeInfo->cCensus)
		for(int nId=0; nId<8; nId++)
			if(pNodeInfo->cCensus & (1 << nId))
				DitherPruneLevel(pCubeInfo, pNodeInfo->Child[nId]);

	if(pNodeInfo->cLevel == pCubeInfo->wDepth)
		DitherPruneChild(pCubeInfo, pNodeInfo);
}

// Suppression d'un Node et passage de ses params à son parent
void CImage::DitherPruneChild(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo)
{
	// Traverse any children.
	if(pNodeInfo->cCensus)
		for(int nId=0; nId<8; nId++)
			if(pNodeInfo->cCensus & (1 << nId))
				DitherPruneChild(pCubeInfo, pNodeInfo->Child[nId]);

	// Merge color statistics into parent.
	DitherNodeInfo* pParent;
	pParent=pNodeInfo->Parent;
	pParent->cCensus &= ~(1 << pNodeInfo->cId);
	pParent->dwNumberUnique += pNodeInfo->dwNumberUnique;
	pParent->fTotalRed += pNodeInfo->fTotalRed;
	pParent->fTotalGreen += pNodeInfo->fTotalGreen;
	pParent->fTotalBlue += pNodeInfo->fTotalBlue;
	pCubeInfo->dwNodes--;
}

// Réduction de l'arbre par élimination de Nodes
void CImage::DitherReduction(DitherCubeInfo *pCubeInfo, UINT nNbrColors)
{
	UINT nSpan;

	nSpan = (UINT)pCubeInfo->dwColors;
	pCubeInfo->fNextPruningThreshold = 0.0;
	while(pCubeInfo->dwColors>nNbrColors)
	{
		pCubeInfo->fPruningThreshold = pCubeInfo->fNextPruningThreshold;
		pCubeInfo->fNextPruningThreshold = pCubeInfo->RootNode->fQuantizationError;
		pCubeInfo->dwColors = NULL;
		DitherReduce(pCubeInfo, pCubeInfo->RootNode);
	}
}

// Destruction des Nodes inutiles (qd la quantization devient inférieure à un certain seuil)
void CImage::DitherReduce(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo)
{
	// Traverse any children.
	if(pNodeInfo->cCensus)
		for(int nId=0; nId < 8; nId++)
			if(pNodeInfo->cCensus & (1 << nId))
				DitherReduce(pCubeInfo, pNodeInfo->Child[nId]);
	if(pNodeInfo->fQuantizationError<=pCubeInfo->fPruningThreshold)
		DitherPruneChild(pCubeInfo, pNodeInfo);
	else
	{
		// Find minimum pruning threshold.
		if(pNodeInfo->dwNumberUnique>0)
			pCubeInfo->dwColors++;
		if(pNodeInfo->fQuantizationError<pCubeInfo->fNextPruningThreshold)
			pCubeInfo->fNextPruningThreshold = pNodeInfo->fQuantizationError;
	}
}

// Définit toutes les entrées des nodes qui vont faire partie de la palette finale
void CImage::DitherDefineColormap(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo)
{
	// Traverse any children.
	if(pNodeInfo->cCensus)
		for(int nId=0; nId<8; nId++)
			if(pNodeInfo->cCensus & (1 << nId))
				DitherDefineColormap(pCubeInfo, pNodeInfo->Child[nId]);

	if (pNodeInfo->dwNumberUnique)
	{
		// Colormap entry is defined by the mean color in this pCubeInfo.
		double fNumberUnique = (double)pNodeInfo->dwNumberUnique;

		pCubeInfo->biColorMap->bmiColors[pCubeInfo->dwColors].rgbRed
			=(BYTE)((pNodeInfo->fTotalRed + fNumberUnique/2)/fNumberUnique);
		pCubeInfo->biColorMap->bmiColors[pCubeInfo->dwColors].rgbGreen
			=(BYTE)((pNodeInfo->fTotalGreen + fNumberUnique/2)/fNumberUnique);
		pCubeInfo->biColorMap->bmiColors[pCubeInfo->dwColors].rgbBlue
			=(BYTE)((pNodeInfo->fTotalBlue + fNumberUnique/2)/fNumberUnique);
		pCubeInfo->biColorMap->bmiColors[pCubeInfo->dwColors].rgbReserved = 0;

		pNodeInfo->dwColorNumber=(DWORD)pCubeInfo->dwColors++;
	}
}

// Destruction du Cube de couleurs
void CImage::DitherDestroyCubeInfo(DitherCubeInfo *pCubeInfo)
{
	DitherNodes* pNodes;

	// Release color cube tree storage.
	do
	{
		pNodes = pCubeInfo->NodeQueue->Next;
		free(pCubeInfo->NodeQueue);
		pCubeInfo->NodeQueue = pNodes;
	}
	while (pCubeInfo->NodeQueue);

	pCubeInfo->dwSquares -= MAX_DITHER_RGB;
	free(pCubeInfo->dwSquares);
	if(!pCubeInfo->bDither)
		return;

	// Free memory resources.
	pCubeInfo->cRangeLimit -= (MAX_DITHER_RGB+1);
	free(pCubeInfo->cRangeLimit);
	free(pCubeInfo->nCache);
}

// Retrouve la couleur dans la palette la plus proche de celle demandée
void CImage::DitherClosestColor(DitherCubeInfo *pCubeInfo, DitherNodeInfo *pNodeInfo)
{
	if(pCubeInfo->fDistance != 0.0)
	{
		// Traverse any children.
		if(pNodeInfo->cCensus)
			for(int nId=0; nId<8; nId++)
				if(pNodeInfo->cCensus & (1 << nId))
					DitherClosestColor(pCubeInfo, pNodeInfo->Child[nId]);
		if (pNodeInfo->dwNumberUnique)
		{
			RGBQUAD Color;
			double fDistanceSquared;
			DWORD* dwSquares;

			// Determine if this color is "closest".
			dwSquares = pCubeInfo->dwSquares;
			memcpy((LPVOID)&Color, (LPVOID)&(pCubeInfo->biColorMap->bmiColors[pNodeInfo->dwColorNumber]), sizeof(RGBQUAD));
			fDistanceSquared = dwSquares[Color.rgbRed-(int)pCubeInfo->rgbColor.rgbRed]+
				dwSquares[Color.rgbGreen-(int)pCubeInfo->rgbColor.rgbGreen]+
				dwSquares[Color.rgbBlue-(int)pCubeInfo->rgbColor.rgbBlue];
			if(fDistanceSquared<pCubeInfo->fDistance)
			{
				pCubeInfo->fDistance = fDistanceSquared;
				pCubeInfo->dwColorNumber = (DWORD)((WORD)pNodeInfo->dwColorNumber);
			}
		}
	}
}

// Distribue la différence de couleur entre original et quantized aux pixels voisins
void CImage::DitherDither(DitherCubeInfo *pCubeInfo, LPBITMAPINFOHEADER BmSrcInfo, LPBITMAPINFO BiDestInfo, UINT nDirection)
{
	if ((pCubeInfo->x>=0) && (pCubeInfo->x<(int)BmSrcInfo->biWidth)
		&& (pCubeInfo->y>=0) && (pCubeInfo->y<(int)BmSrcInfo->biHeight))
	{
		double fBlueError, fGreenError, fRedError;
		BYTE cBlue, cGreen, cRed;
		WORD wIndex;

		// Distribute error
		fRedError = fGreenError= fBlueError = 0.0;
		for(int i=0; i<ERROR_QUEUE_LENGTH; i++)
		{
			fRedError += pCubeInfo->Error[i].nRed * pCubeInfo->fWeights[i];
			fGreenError += pCubeInfo->Error[i].nGreen * pCubeInfo->fWeights[i];
			fBlueError += pCubeInfo->Error[i].nBlue * pCubeInfo->fWeights[i];
		}

		RGBQUAD Packet;
		DWORD PixelColor = GetPixel(pCubeInfo->x, pCubeInfo->y, BmSrcInfo);
		Packet.rgbBlue = (BYTE)((PixelColor>>16) & 0xFF);
		Packet.rgbGreen = (BYTE)((PixelColor>>8) & 0xFF);
		Packet.rgbRed = (BYTE)(PixelColor & 0xFF);
		Packet.rgbReserved = NULL;

		cRed = pCubeInfo->cRangeLimit[Packet.rgbRed+(int)fRedError];
		cGreen = pCubeInfo->cRangeLimit[Packet.rgbGreen+(int)fGreenError];
		cBlue = pCubeInfo->cRangeLimit[Packet.rgbBlue+(int)fBlueError];
		i = (cBlue >> DITHER_CACHE_SHIFT) << 12 | (cGreen >> DITHER_CACHE_SHIFT) << 6
			| (cRed >> DITHER_CACHE_SHIFT);
		if(pCubeInfo->nCache[i]<0)
		{
			// Identify the deepest node containing the pixel's color.
			DitherNodeInfo* pNodeInfo = pCubeInfo->RootNode;
			for(wIndex = MAX_TREE_DEPTH-1; (int)wIndex>0; wIndex--)
			{
				UINT nId=(((UINT)(cRed) >> wIndex) & 0x01) << 2 |
					(((UINT)(cGreen) >> wIndex) & 0x01) << 1 |
					(((UINT)(cBlue) >> wIndex) & 0x01);
				if ((pNodeInfo->cCensus & (1 << nId)) == 0)
					break;
				pNodeInfo = pNodeInfo->Child[nId];
			}
			// Find closest color among siblings and their children.
			pCubeInfo->rgbColor.rgbRed = cRed;
			pCubeInfo->rgbColor.rgbGreen = cGreen;
			pCubeInfo->rgbColor.rgbBlue = cBlue;
			pCubeInfo->fDistance = 3.0*(MAX_DITHER_RGB+1)*(MAX_DITHER_RGB+1);
			DitherClosestColor(pCubeInfo, pNodeInfo->Parent);
			pCubeInfo->nCache[i] = (int)pCubeInfo->dwColorNumber;
		}

		// Assign pixel to closest colormap entry.
		wIndex = (WORD)pCubeInfo->nCache[i];

		// Cette version ne supporte qu'une palette en sortie
		SetPixel(pCubeInfo->x, pCubeInfo->y, wIndex, (LPBITMAPINFOHEADER)BiDestInfo);

		//Propagate the error as the last entry of the error queue.
		for(i=0; i<(ERROR_QUEUE_LENGTH-1); i++)
			pCubeInfo->Error[i] = pCubeInfo->Error[i+1];
		pCubeInfo->Error[i].nRed = cRed-(int)BiDestInfo->bmiColors[wIndex].rgbRed;
		pCubeInfo->Error[i].nGreen = cGreen-(int)BiDestInfo->bmiColors[wIndex].rgbGreen;
		pCubeInfo->Error[i].nBlue = cBlue-(int)BiDestInfo->bmiColors[wIndex].rgbBlue;
	}
	switch (nDirection)
	{
		case W_GRAVITY:
			pCubeInfo->x--;
			break;
		case E_GRAVITY:
			pCubeInfo->x++;
			break;
		case N_GRAVITY:
			pCubeInfo->y--;
			break;
		case S_GRAVITY:
			pCubeInfo->y++;
			break;
	}
}

// Permet de parcourir tous les points d'une grille. Utilisée pour le dithering
void CImage::DitherHilbertCurve(DitherCubeInfo *pCubeInfo, LPBITMAPINFOHEADER BmSrcInfo, LPBITMAPINFO BiDestInfo, int nLevel, UINT nDirection)
{
	if (nLevel == 1)
	{
		switch(nDirection)
		{
			case W_GRAVITY:
			{
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, E_GRAVITY);
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, S_GRAVITY);
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, W_GRAVITY);
				break;
			}
			case E_GRAVITY:
			{
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, W_GRAVITY);
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, N_GRAVITY);
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, E_GRAVITY);
				break;
			}
			case N_GRAVITY:
			{
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, S_GRAVITY);
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, E_GRAVITY);
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, N_GRAVITY);
				break;
			}
			case S_GRAVITY:
			{
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, N_GRAVITY);
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, W_GRAVITY);
				DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, S_GRAVITY);
				break;
			}
			default:
				break;
		}
		return;
	}
	switch(nDirection)
	{
		case W_GRAVITY:
		{
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, N_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, E_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, W_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, S_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, W_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, W_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, S_GRAVITY);
			break;
		}
		case E_GRAVITY:
		{
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, S_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, W_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, E_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, N_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, E_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, E_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, N_GRAVITY);
			break;
		}
		case N_GRAVITY:
		{
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, W_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, S_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, N_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, E_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, N_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, N_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, E_GRAVITY);
			break;
		}
		case S_GRAVITY:
		{
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, E_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, N_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, S_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, W_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, S_GRAVITY);
			DitherDither(pCubeInfo, BmSrcInfo, BiDestInfo, S_GRAVITY);
			DitherHilbertCurve(pCubeInfo, BmSrcInfo, BiDestInfo, nLevel-1, W_GRAVITY);
			break;
		}
		default:
			break;
	}
}

#endif

//===================================================================
//  Fonction de copie dans clipboard. Activer avec CIMAGE_CLIPBOARD
//===================================================================

#if defined(CIMAGE_CLIPBOARD)

// Copie l'image en cours dans le presse-papier
BOOL CImage::CopyToClipboard()
{
	HGLOBAL hClipDIB = NULL;
	HGLOBAL hClipExtra = NULL;
	if(CopyToHandle(&hClipDIB, & hClipExtra))
	{
		// Met le bitmap ds le presse papier
		if(!(::OpenClipboard(NULL)))
		{
			GlobalFree(hClipDIB);
			if(hClipExtra)
				GlobalFree(hClipExtra);
			return FALSE;
		}

		EmptyClipboard();
		SetClipboardData(CF_DIB, hClipDIB);
		if(hClipExtra)
			SetClipboardData(CF_TEXT, hClipExtra);
		CloseClipboard();

		return TRUE;
	}

	return FALSE;
}

// Réserve et rempli les handles passés pour copie ds presse-papiers ou Drag&Drop
BOOL CImage::CopyToHandle(HGLOBAL* hClipDIB, HGLOBAL* hClipExtra)
{
	if(!m_hDib)
		return FALSE;

	// Réserve la mémoire à passer au presse papier
	if(!(*hClipDIB=GlobalAlloc(GHND | GMEM_DDESHARE,
			GlobalSize(m_hDib))))
		return FALSE;

	// Copie du DIB dans la mémoire destinée au presse-papier
	PVOID Source=GlobalLock(m_hDib);
	PVOID Destination=GlobalLock(*hClipDIB);
	CopyMemory(Destination, Source, GlobalSize(m_hDib));
	GlobalUnlock(m_hDib);
	GlobalUnlock(*hClipDIB);

	// ExtraInfos
	if(m_dwTransparentColor & 0x80000000L)
	{
		if(*hClipExtra=GlobalAlloc(GHND | GMEM_DDESHARE, CLIPEXTRA_MEM))
		{
			char* szExtra = (char*)GlobalLock(*hClipExtra);
			lstrcpy(szExtra, CLIPEXTRA_HEADER);

			lstrcat(szExtra, CLIPEXTRA_TRANSPARENT);
			char szDummy[20];
			lstrcat(szExtra, ltoa(m_dwTransparentColor & 0x7FFFFFFFL, szDummy, 10));
			lstrcat(szExtra, "}");
			GlobalUnlock(*hClipExtra);
		}
	}

	return TRUE;
}

// Ramène TRUE si le bitmap contient un CF_DIB dans de clipboard
//    et si celui-ci est supporté par la classe (nombre couleurs).
BOOL CImage::IsClipboardOK() const
{
	if(!IsClipboardFormatAvailable(CF_DIB))
		return FALSE;

	if(!(::OpenClipboard(NULL)))
		return FALSE;

	HGLOBAL hClipDIB = GetClipboardData(CF_DIB);
	BOOL bRet = VerifyHandle(hClipDIB);

	CloseClipboard();
	return bRet;
}

// Ramène TRUE si le HANDLE contient un bitmap valide
BOOL CImage::VerifyHandle(HGLOBAL hClipDIB) const
{
	if(!hClipDIB)
		return FALSE;
	BITMAPINFOHEADER* bm = (BITMAPINFOHEADER*)GlobalLock(hClipDIB);
	BOOL bRet = FALSE;
	if(bm->biPlanes==1
			&& (bm->biBitCount==1 || bm->biBitCount==4 || bm->biBitCount==8 || bm->biBitCount==24)
			&& bm->biCompression==BI_RGB && bm->biWidth && bm->biHeight)
		bRet = TRUE;

	GlobalUnlock(hClipDIB);
	return bRet;
}

// Vérifie si le clipboard est OK et initialise la classe avec son contenu
BOOL CImage::PasteClipboard()
{
	if(!IsClipboardOK())
		return FALSE;
	if(!(::OpenClipboard(NULL)))
		return FALSE;

	HGLOBAL hClipDIB = GetClipboardData(CF_DIB);
	HGLOBAL hClipExtra = GetClipboardData(CF_TEXT);

	BOOL bRet = PasteHandle(hClipDIB, hClipExtra);

	CloseClipboard();
	return bRet;
}

// Initialise les données des handles dans la classe
BOOL CImage::PasteHandle(HGLOBAL hClipDIB, HGLOBAL hClipExtra)
{
	if(!hClipDIB)
		return FALSE;

	*this = hClipDIB;

	if(hClipExtra)
	{
		char* szExtra = (char*)GlobalLock(hClipExtra);
		if(!strncmp(szExtra, CLIPEXTRA_HEADER, sizeof(CLIPEXTRA_HEADER)-1))
		{
			char szDummy[CLIPEXTRA_MEM];
			szExtra+=sizeof(CLIPEXTRA_HEADER)-1;
			lstrcpyn(szDummy, szExtra, CLIPEXTRA_MEM);

			szExtra = strtok(szDummy, "}");
			while(szExtra)
			{
				switch(szExtra[0])
				{
					case 'T':
						m_dwTransparentColor = atol(szExtra+1) | 0x80000000L;
						break;
				}
				szExtra = strtok(NULL, "}");
			}
		}
		GlobalUnlock(hClipExtra);
	}
	return TRUE;
}

#endif

//===================================================================
//  Fonctions de sérialisation dans un CArchive. Activer avec CIMAGE_SERIALIZE
//===================================================================

#if defined(CIMAGE_SERIALIZE) && !defined(CIMAGE_NO_MFC)

void CImage::Serialize(CArchive &ar)
{
	if (ar.IsStoring())
	{
		// Sauvegarde de l'image au sein du fichier
		ar << *this;
	}
	else
	{
		// Chargement de l'image
		ar >> *this;
	}
}

// Chargement de l'image en provenance d'un CArchive
CArchive& AFXAPI operator >> (CArchive& ar, CImage &Img)
{
	DWORD dwImgSize;
	DWORD dwTransColor = NULL;

	Img.Erase();

	ar >> dwImgSize;
	if(dwImgSize)
	{
		if(dwImgSize & 0x80000000L) // Bit d'info de données supplémentaires
		{
			BOOL bImage = FALSE;
			BYTE cTag;
			WORD wTagSize;

			// Interprétation des données supplémentaires
			while(!bImage)
			{
				ar.Read(&cTag, sizeof(BYTE));

				switch(cTag)
				{
					case DUMP_TAG_IMAGE: // Image -> Fin des infos
						bImage = TRUE;
						break;

					case DUMP_TAG_TRANSPARENT: // Couleur transparente
						ar.Read(&wTagSize, sizeof(WORD));
						ar.Read(&dwTransColor, sizeof(DWORD));
						break;

					default: // Tag inconnu -> On lit la taille et le tag sans l'interprêter
						ar.Read(&wTagSize, sizeof(WORD));
						if(wTagSize)
						{
							BYTE* DummyBuffer = (BYTE*)malloc(wTagSize);
							if(DummyBuffer)
							{
								ar.Read(DummyBuffer, (UINT)wTagSize);
								free(DummyBuffer);
							}
						}
						break;
				}
			}
		}

		HGLOBAL hDib=GlobalAlloc(GHND, dwImgSize & 0x7FFFFFFFL);
		if(hDib)
		{
			void* Datas=GlobalLock(hDib);
			ar.Read(Datas, (UINT)(dwImgSize & 0x7FFFFFFFL));
			GlobalUnlock(hDib);
			Img.Init(hDib);
			Img.m_dwTransparentColor = dwTransColor;
		}
	}
	return ar;
}

// Sauvegarde de l'image dans un CArchive
CArchive& AFXAPI operator << (CArchive& ar, CImage const &Img)
{
	DWORD dwSize=NULL;
	if(Img.m_hDib)
	{
		dwSize = GlobalSize(Img.m_hDib);

		// Si infos supplémentaires -> bit poid fort à 1
		if(Img.m_dwTransparentColor & 0x80000000L)
		{
			ar << (DWORD)(dwSize | 0x80000000L);

			// Enregistre les différentes données à sauver: Type TAG: 1 BYTE, taille TAG: 1 WORD

			// Couleur transparente
			if(Img.m_dwTransparentColor & 0x80000000L)
			{
				ar << (BYTE)(DUMP_TAG_TRANSPARENT);
				ar << (WORD)sizeof(DWORD);  // Taille du tag
				ar << (DWORD)Img.m_dwTransparentColor;
			}

			// Sortie du tag de l'image (Exception: pas de taille de tag), toujours en dernier
			ar << (BYTE)(DUMP_TAG_IMAGE);
		}
		else
			ar << (DWORD)dwSize;
		void* Datas=GlobalLock(Img.m_hDib);
		ar.Write(Datas, (UINT)dwSize);
		GlobalUnlock(Img.m_hDib);
	}
	else
		ar << (DWORD)dwSize;
	return ar;
}

// Indique si l'image est "dumped"
BOOL CImage::IsDumped() const
{
	return m_bDumpImage;
}

// Met l'image dans un fichier temporaire et vide la mémoire.
BOOL CImage::DumpImage()
{
	if(m_bDumpImage)
		return TRUE;
	if(!m_hDib)
		return FALSE;
	if(!(m_LoadBuffer = malloc(_MAX_PATH)))
		return FALSE;

	char szTempPath[_MAX_PATH];
	GetTempPath(_MAX_PATH, szTempPath);
	GetTempFileName(szTempPath, "img", 0, (LPSTR)m_LoadBuffer);

	CFile File;
	if(!File.Open((LPCTSTR)m_LoadBuffer, CFile::modeCreate | CFile::modeReadWrite))
	{
		DeleteFile((LPCTSTR)m_LoadBuffer);
		free(m_LoadBuffer);
		m_LoadBuffer = NULL;
		return FALSE;
	}

	CArchive ar(&File, CArchive::store);

	// Sauvegarde de l'image au sein du fichier
	ar << *this;

	// Fermeture du fichier
	ar.Close();
	File.Close();

	// Effacement des données de l'image
	m_bDumpImage = TRUE;
	GlobalFree(m_hDib);
	m_hDib = NULL;

	return TRUE;
}

// Récupère l'image située dans un fichier temporaire
BOOL CImage::UndumpImage()
{
	if(!m_bDumpImage)
		return TRUE;
	if(!m_LoadBuffer)
		return FALSE;

	CFile File;
	if(!File.Open((LPCTSTR)m_LoadBuffer, CFile::modeReadWrite))
		return FALSE;

	CArchive ar(&File, CArchive::load);

	// Sauvegarde des paramètres car l'opérateur ">>" fait un Erase()
	int nTypeImage = m_nTypeImage;
	int nFileFormat = m_nFileFormat;
	DWORD dwTransparentColor = m_dwTransparentColor;
	char szTempFile[_MAX_PATH];
	lstrcpy(szTempFile, (LPCTSTR)m_LoadBuffer);

	// Récupère l'image
	ar >> *this;

	// Fermeture et destruction du fichier
	ar.Close();
	File.Close();
	DeleteFile(szTempFile);

	// Réaffectation des données
	m_nTypeImage = nTypeImage;
	m_nFileFormat = nFileFormat;
	m_dwTransparentColor = dwTransparentColor;

	return TRUE;
}

#endif

//===================================================================
//  Fonctions de chargement de fichier. Activer avec CIMAGE_LOADFILE
//===================================================================

#if defined(CIMAGE_LOADFILE)

// Chargement d'un fichier à partir du disque. Trouve le format tout seul
BOOL CImage::LoadFile(LPCTSTR szFileName)
{
	if(!szFileName || !szFileName[0])
		return FALSE;

	// Commande non autorisée en mode Dumped
	if(m_bDumpImage)
		return FALSE;

	// On commence par charger tout le fichier en mémoire dans le buffer m_LoadBuffer
	HANDLE hFile=CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	DWORD dwTailleFichier=GetFileSize(hFile,NULL);
	if(!dwTailleFichier || dwTailleFichier==(DWORD)-1)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if(!(m_LoadBuffer=malloc((size_t)dwTailleFichier)))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	DWORD dwByteRead;
	BOOL bRetour=ReadFile(hFile, m_LoadBuffer, dwTailleFichier, &dwByteRead, NULL);
	CloseHandle(hFile);

	if(!bRetour || dwByteRead!=dwTailleFichier)
	{
		free(m_LoadBuffer);
		return FALSE;
	}

	// On essai les chargements un par un. Si la sous-fct ramène FALSE,
	//  le bitmap n'est pas chargé et on essai le format suivant
	BOOL bSuccess=FALSE;
	int nOldFormat=m_nFileFormat;
	m_nFileFormat = IMG_FORMAT_END;
	DWORD dwOldTransparentColor = m_dwTransparentColor;
	m_dwTransparentColor = NULL;
	for(int nFormat=0; nFormat<IMG_FORMAT_END && !bSuccess; nFormat++)
	{
		switch(nFormat)
		{
			case IMG_FORMAT_BMPWIN:
			case IMG_FORMAT_BMPOS2:
			case IMG_FORMAT_RLE:
				bSuccess = LoadBMP();
				nFormat = IMG_FORMAT_RLE;
				break;
			case IMG_FORMAT_PCX:
				bSuccess = LoadPCX();
				break;
			case IMG_FORMAT_GIF:
				bSuccess = LoadGIF();
				break;
			case IMG_FORMAT_JPEG:
				#if defined(CIMAGE_USE_JPEG)
					bSuccess = LoadJPEG();
				#endif
				break;
			case IMG_FORMAT_TIFF:
				#if defined(CIMAGE_USE_TIFF)
					bSuccess = LoadTIFF();
				#endif
				break;
			case IMG_FORMAT_TGA:
				bSuccess = LoadTGA();
				break;
			case IMG_FORMAT_PNG:
				#if defined(CIMAGE_USE_PNG)
					bSuccess = LoadPNG();
				#endif
				break;
		}
	}

	// Libération du buffer
	if(m_LoadBuffer)
		free(m_LoadBuffer);
	m_LoadBuffer = NULL;

	if(bSuccess)
	{
		// Au cas où une sous-fonction oublierait de mettre m_nFileFormat à jour
		if(m_nFileFormat == IMG_FORMAT_END)
			m_nFileFormat = nFormat;
		// Une résolution de bitmap ne doit jamais être nulle
		if(!GetResX() || !GetResY())
			SetRes(DEFAULT_RES, DEFAULT_RES);
	}
	else
	{
		m_nFileFormat=nOldFormat; // On le remet comme avant si on a rien chargé
		m_dwTransparentColor = dwOldTransparentColor;
	}

	return bSuccess;
}

#endif // CIMAGE_LOADFILE

//===================================================================
//  Fonctions de chargement de ressource. Valide si un CIMAGE_LDRSRC_... est défini
//===================================================================

#if defined(CIMAGE_LDRSRC_BMP) || defined(CIMAGE_LDRSRC_PCX) || defined(CIMAGE_LDRSRC_GIF)\
	|| defined(CIMAGE_LDRSRC_JPEG) || defined(CIMAGE_LDRSRC_TIFF) || defined(CIMAGE_LDRSRC_TGA)\
	|| defined(CIMAGE_LDRSRC_PNG)

// Chargement à partir d'une ressource, version MFC (hInst est tiré du handle de resources par défaut)
#if !defined(CIMAGE_NO_MFC)
BOOL CImage::LoadFromRessource(LPCTSTR lpResourceName, int nFormat, LPCTSTR lpType)
{
	HINSTANCE hInst=AfxGetResourceHandle();
	return LoadFromRessource(hInst, lpResourceName, nFormat, lpType);
}
#endif

// Chargement à partir d'une ressource
BOOL CImage::LoadFromRessource(HINSTANCE hInst, LPCTSTR lpResourceName, int nFormat, LPCTSTR lpType)
{
	HRSRC hSrc = FindResource(hInst, lpResourceName, lpType);
	BOOL bSuccess = FALSE;
	if(hSrc)
	{
		HGLOBAL hResData = LoadResource(hInst, hSrc);
		if(hResData)
		{
			LPVOID lpResData = LockResource(hResData);
			if(lpResData)
			{
				DWORD dwSize = SizeofResource(hInst, hSrc);
				if(dwSize)
				{
					m_LoadBuffer = malloc(dwSize);
					if(m_LoadBuffer)
					{
						CopyMemory(m_LoadBuffer, lpResData, dwSize);
						int nOldFormat=m_nFileFormat;
						m_nFileFormat = IMG_FORMAT_END;
						DWORD dwOldTransparentColor = m_dwTransparentColor;
						m_dwTransparentColor = NULL;
						switch(nFormat)
						{
							case IMG_FORMAT_BMPWIN:
							case IMG_FORMAT_BMPOS2:
							case IMG_FORMAT_RLE:
								#if defined(CIMAGE_LDRSRC_BMP)
									bSuccess = LoadBMP();
								#endif
								break;
							case IMG_FORMAT_PCX:
								#if defined(CIMAGE_LDRSRC_PCX)
									bSuccess = LoadPCX();
								#endif
								break;
							case IMG_FORMAT_GIF:
								#if defined(CIMAGE_LDRSRC_GIF)
									bSuccess = LoadGIF();
								#endif
								break;
							case IMG_FORMAT_JPEG:
								#if defined(CIMAGE_USE_JPEG) && defined(CIMAGE_LDRSRC_JPEG)
									bSuccess = LoadJPEG();
								#endif
								break;
							case IMG_FORMAT_TIFF:
								#if defined(CIMAGE_USE_TIFF) && defined(CIMAGE_LDRSRC_TIFF)
									bSuccess = LoadTIFF();
								#endif
								break;
							case IMG_FORMAT_TGA:
								#if defined(CIMAGE_LDRSRC_TGA)
									bSuccess = LoadTGA();
								#endif
								break;
							case IMG_FORMAT_PNG:
								#if defined(CIMAGE_USE_PNG) && defined(CIMAGE_LDRSRC_PNG)
									bSuccess = LoadPNG();
								#endif
								break;
						}

						// Libération du buffer
						free(m_LoadBuffer);
						m_LoadBuffer = NULL;

						if(bSuccess)
						{
							// Au cas où une sous-fonction oublierait de mettre m_nFileFormat à jour
							if(m_nFileFormat == IMG_FORMAT_END)
								m_nFileFormat = nFormat;
							// Une résolution de bitmap ne doit jamais être nulle
							if(!GetResX() || !GetResY())
								SetRes(DEFAULT_RES, DEFAULT_RES);
						}
						else
						{
							m_nFileFormat=nOldFormat; // On le remet comme avant si on a rien chargé
							m_dwTransparentColor = dwOldTransparentColor;
						}
					}
				}
			}
		}
	}

	return bSuccess;
}

#endif

//===================================================================
//  Fonctions de chargement de ficher et de ressource.
//===================================================================

#if defined(CIMAGE_LOADFILE) || defined(CIMAGE_LDRSRC_BMP)
// Charge une image BMP ou DIB Windows ou OS/2
BOOL CImage::LoadBMP()
{
	// Première vérif: taille minimale pour le header
	if(_msize(m_LoadBuffer)<sizeof(BITMAPFILEHEADER))
		return FALSE;

	// Test de la marque de signature
	LPBITMAPFILEHEADER BmHeader = (LPBITMAPFILEHEADER)m_LoadBuffer;
	if(BmHeader->bfType!=FORMAT_BMP)
		return FALSE;

	LPBITMAPINFO BmInfo = (LPBITMAPINFO)((BYTE*)m_LoadBuffer
		+ sizeof(BITMAPFILEHEADER));

	HGLOBAL hNewDib = NULL;
	try
	{
		// BMP, DIB ou RLE Windows
		if(BmInfo->bmiHeader.biSize == sizeof(BITMAPINFOHEADER))
		{
			if(BmInfo->bmiHeader.biCompression == BI_BITFIELDS)
				return FALSE; // Format avec BI_BITFIELDS non supporté

			// Format BMP ou DIB, sans compression
			if(BmInfo->bmiHeader.biCompression == BI_RGB)
			{
				// Réservation de la place pour le nouveau bitmap
				int nColors = BmInfo->bmiHeader.biClrUsed ? BmInfo->bmiHeader.biClrUsed
					: 0x1FF & (1 << BmInfo->bmiHeader.biBitCount);
				int nScanWidth = WIDTHBYTES(BmInfo->bmiHeader.biWidth * BmInfo->bmiHeader.biBitCount);

				// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
				hNewDib=GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)
					+ nColors*sizeof(RGBQUAD)
					+ (nScanWidth*BmInfo->bmiHeader.biHeight));
				if(!hNewDib)
					return FALSE;
				LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);			
				// Bitmap non compressé -> copie directe en mémoire
				CopyMemory((void*)BiDest, BmInfo, sizeof(BITMAPINFOHEADER)
					+ nColors*sizeof(RGBQUAD));
				CopyMemory(((BYTE*)BiDest)+sizeof(BITMAPINFOHEADER)+nColors*sizeof(RGBQUAD),
					((BYTE*)BmHeader)+BmHeader->bfOffBits, nScanWidth*BmInfo->bmiHeader.biHeight);
				GlobalUnlock(hNewDib);
				BOOL bRet = Init(hNewDib, GetDefaultType(BmInfo->bmiHeader.biBitCount));
				if(bRet)
					m_nFileFormat = IMG_FORMAT_BMPWIN;
				else
					GlobalFree(hNewDib);
				return bRet;
			}

			// Bitmap compressé en RLE8
			if(BmInfo->bmiHeader.biCompression == BI_RLE8)
			{
				// Réservation mémoire et copie du header
				int nColors = BmInfo->bmiHeader.biClrUsed ? BmInfo->bmiHeader.biClrUsed
					: 0x1FF & (1 << BmInfo->bmiHeader.biBitCount);
				int nScanWidth = WIDTHBYTES(BmInfo->bmiHeader.biWidth * BmInfo->bmiHeader.biBitCount);

				// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
				hNewDib=GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)
					+ nColors*sizeof(RGBQUAD)
					+ (nScanWidth*BmInfo->bmiHeader.biHeight));
				if(!hNewDib)
					return FALSE;
				LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
				CopyMemory((void*)BiDest, BmInfo,
					sizeof(BITMAPINFOHEADER)+nColors*sizeof(RGBQUAD));
				BiDest->biCompression = BI_RGB;
				BiDest->biClrUsed = nColors;
				BiDest->biSizeImage = nScanWidth*BmInfo->bmiHeader.biHeight;

				int x=NULL;
				int y=NULL;
				int i;
				int k;
				BOOL bEnd=FALSE;
				BYTE* lpDestBits=(BYTE*)BiDest+sizeof(BITMAPINFOHEADER)
					+nColors*sizeof(RGBQUAD);
				BYTE* lpSrcBits=(BYTE*)BmInfo+sizeof(BITMAPINFOHEADER)
					+nColors*sizeof(RGBQUAD);
				BYTE* EndBuffer = (BYTE*)m_LoadBuffer + (UINT)_msize(m_LoadBuffer);
				while(!bEnd && lpSrcBits<EndBuffer)
				{
					if(!*(lpSrcBits++))
					{
						switch(*lpSrcBits)
						{
							case 0:
								y++;
								x=0;
								lpSrcBits++;
								break;
							case 1:
								bEnd=TRUE;
								lpSrcBits++;
								break;
							case 2:
								x+=*(lpSrcBits++);
								y+=*(lpSrcBits++);
								break;
							default:
								k = *(lpSrcBits++);
								for(i=0; i<k && lpSrcBits<EndBuffer; i++)
								{
									SetPixel(Min(x++,BiDest->biWidth-1),
										Min(y,BiDest->biHeight-1),
										*(lpSrcBits++), BiDest);
									if(x>BiDest->biWidth)
									{
										x=0;
										y++;
									}
								}
								if(k&1)
									lpSrcBits++; // doit être réaligné sur un word
								break;
						}
					}
					else
					{
						k=*(lpSrcBits-1);
						for(i=0; i<k && lpSrcBits<EndBuffer; i++)
						{
							SetPixel(Min(x++,BiDest->biWidth-1),
								Min(y,BiDest->biHeight-1),
								*lpSrcBits, BiDest);
							if(x>BiDest->biWidth)
							{
								x=0;
								y++;
							}
						}
						lpSrcBits++;
					}
				}
				GlobalUnlock(hNewDib);
				BOOL bRet = Init(hNewDib, GetDefaultType(BmInfo->bmiHeader.biBitCount));
				if(bRet)
					m_nFileFormat = IMG_FORMAT_RLE;
				else
					GlobalFree(hNewDib);
				return bRet;
			}

			// Bitmap 16 bits compressé en RLE4
			if(BmInfo->bmiHeader.biCompression == BI_RLE4)
			{
				// Réservation mémoire et copie du header
				int nColors = BmInfo->bmiHeader.biClrUsed ? BmInfo->bmiHeader.biClrUsed
					: 0x1FF & (1 << BmInfo->bmiHeader.biBitCount);
				int nScanWidth = WIDTHBYTES(BmInfo->bmiHeader.biWidth * BmInfo->bmiHeader.biBitCount);

				// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
				hNewDib=GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)
					+ nColors*sizeof(RGBQUAD)
					+ (nScanWidth*BmInfo->bmiHeader.biHeight));
				if(!hNewDib)
					return FALSE;
				LPBITMAPINFOHEADER BiDest=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
				CopyMemory((void*)BiDest, BmInfo,
					sizeof(BITMAPINFOHEADER)+nColors*sizeof(RGBQUAD));
				BiDest->biCompression = BI_RGB;
				BiDest->biClrUsed = nColors;
				BiDest->biSizeImage = nScanWidth*BmInfo->bmiHeader.biHeight;

				int x=NULL;
				int y=NULL;
				int i;
				int k;
				BOOL bEnd=FALSE;
				BYTE* lpDestBits=(BYTE*)BiDest+sizeof(BITMAPINFOHEADER)
					+nColors*sizeof(RGBQUAD);
				BYTE* lpSrcBits=(BYTE*)BmInfo+sizeof(BITMAPINFOHEADER)
					+nColors*sizeof(RGBQUAD);
				BYTE* EndBuffer = (BYTE*)m_LoadBuffer + (UINT)_msize(m_LoadBuffer);
				while(!bEnd && lpSrcBits<EndBuffer)
				{
					if(!*(lpSrcBits++))
					{
						switch(*lpSrcBits)
						{
							case 0:
								y++;
								x=0;
								lpSrcBits++;
								break;
							case 1:
								bEnd=TRUE;
								lpSrcBits++;
								break;
							case 2:
								x+=*(lpSrcBits++);
								y+=*(lpSrcBits++);
								break;
							default:
								k = *(lpSrcBits++);
								for(i=0; i<k && lpSrcBits<EndBuffer; i++)
								{
									if(!(i&1))
									{
										SetPixel(Min(x++,BiDest->biWidth-1),
											Min(y,BiDest->biHeight-1),
											((*lpSrcBits)>>4) & 0x0F, BiDest);
									}
									else
									{
										SetPixel(Min(x++,BiDest->biWidth-1),
											Min(y,BiDest->biHeight-1),
											(*lpSrcBits) & 0x0F, BiDest);
										lpSrcBits++;
									}
									if(x>BiDest->biWidth)
									{
										x=0;
										y++;
									}
								}
								if(k & 1)
								{
									lpSrcBits++; // si impaire, passer octet
									k++;
								}
								if(k & 2)
									lpSrcBits++; // doit être réaligné sur un word
								break;
						}
					}
					else
					{
						k=*(lpSrcBits-1);
						for(i=0; i<k && lpSrcBits<EndBuffer; i++)
						{
							if(i&1)
								SetPixel(Min(x++,BiDest->biWidth-1),
									Min(y,BiDest->biHeight-1), (*lpSrcBits) & 0x0F, BiDest);
							else
								SetPixel(Min(x++,BiDest->biWidth-1),
									Min(y,BiDest->biHeight-1), ((*lpSrcBits)>>4) & 0x0F, BiDest);
							if(x>BiDest->biWidth)
							{
								x=0;
								y++;
							}
						}
						lpSrcBits++;
					}
				}
				GlobalUnlock(hNewDib);
				BOOL bRet = Init(hNewDib, GetDefaultType(BmInfo->bmiHeader.biBitCount));
				if(bRet)
					m_nFileFormat = IMG_FORMAT_RLE;
				else
					GlobalFree(hNewDib);
				return bRet;
			}

			// Si on arrive ici, il y a pépin. Donc on rentre!!
			return FALSE;
		}

		// BMP OS/2
		if(BmInfo->bmiHeader.biSize == sizeof(BITMAPCOREHEADER))
		{
			LPBITMAPCOREINFO BmCore = (LPBITMAPCOREINFO)BmInfo;

			// Détermination du nombre ce couleurs et largeurs lignes
			int nColors = 0x1FF & (1 << BmCore->bmciHeader.bcBitCount);
			int nScanWidth = WIDTHBYTES(BmCore->bmciHeader.bcWidth * BmCore->bmciHeader.bcBitCount);

			// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
			hNewDib=GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)
				+ nColors*sizeof(RGBQUAD)
				+ (nScanWidth*BmCore->bmciHeader.bcHeight));
			if(!hNewDib)
				return FALSE;  // Pas assez de mémoire ou problème

			// Adresse du nouveau bitmap
			LPBITMAPINFO BiDest=(LPBITMAPINFO)GlobalLock(hNewDib);

			// Copie des données du Header
			BiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
			BiDest->bmiHeader.biWidth = BmCore->bmciHeader.bcWidth;
			BiDest->bmiHeader.biHeight = BmCore->bmciHeader.bcHeight;
			BiDest->bmiHeader.biPlanes = BmCore->bmciHeader.bcPlanes;
			BiDest->bmiHeader.biBitCount = BmCore->bmciHeader.bcBitCount;
			BiDest->bmiHeader.biCompression = BI_RGB;
			BiDest->bmiHeader.biSizeImage = nScanWidth*BmCore->bmciHeader.bcHeight;
			BiDest->bmiHeader.biXPelsPerMeter =
				BiDest->bmiHeader.biYPelsPerMeter = DEFAULT_RES; // arbitraire
			BiDest->bmiHeader.biClrUsed = nColors;
			BiDest->bmiHeader.biClrImportant = NULL;

			// Copie de la palette (si existante)
			for(int i=0; i<nColors; i++)
			{
				BiDest->bmiColors[i].rgbBlue = BmCore->bmciColors[i].rgbtBlue;
				BiDest->bmiColors[i].rgbGreen = BmCore->bmciColors[i].rgbtGreen;
				BiDest->bmiColors[i].rgbRed = BmCore->bmciColors[i].rgbtRed;
			}

			// Copie des bits du bitmap
			int nSize1 = nScanWidth*BmCore->bmciHeader.bcHeight;
			int nSize2 = _msize(m_LoadBuffer)-sizeof(BITMAPFILEHEADER)-sizeof(BITMAPCOREHEADER)-nColors*sizeof(RGBTRIPLE);
			CopyMemory((BYTE*)BiDest+BiDest->bmiHeader.biSize+nColors*sizeof(RGBQUAD),
				(BYTE*)BmCore+sizeof(BITMAPCOREHEADER)+nColors*sizeof(RGBTRIPLE),
				min(nSize1, nSize2));

			GlobalUnlock(hNewDib);
			BOOL bRet = Init(hNewDib, GetDefaultType(BiDest->bmiHeader.biBitCount));
			if(bRet)
				m_nFileFormat = IMG_FORMAT_BMPOS2;
			else
				GlobalFree(hNewDib);
			return bRet;
		}

		// Format non reconnu
		return FALSE;
	}
	catch(...)
	{
		if(hNewDib)
		{
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
		}
		return FALSE;
	}
}
#endif


#if defined(CIMAGE_LOADFILE) || defined(CIMAGE_LDRSRC_PCX)
// Charge une image au format PCX
BOOL CImage::LoadPCX()
{
	// Première vérif: taille minimale pour le header
	if(_msize(m_LoadBuffer)<sizeof(TypeHeaderPCX))
		return FALSE;

	// Quelques tests pour voir si c'est bien du PCX
	TypeHeaderPCX* EntetePCX=(TypeHeaderPCX*)m_LoadBuffer;
	if(EntetePCX->yGriffe!=0x0A && EntetePCX->yGriffe!=0x0C)
		return FALSE;
	if(EntetePCX->yCodage!=1)
		return FALSE;

	// Dimensions négatives ou nulles? On rentre!!
	if((EntetePCX->x2-EntetePCX->x1+1)<=NULL
			|| (EntetePCX->y2-EntetePCX->y1+1)<=NULL)
		return FALSE;

	HGLOBAL hNewDib = NULL;
	BYTE* lpLineBits = NULL;

	try
	{
		// Détermination du nombre ce couleurs et largeurs lignes
		int nColors = 0x1FF & (1 << (EntetePCX->yBits*EntetePCX->cNbrPlanes));
		int nScanWidth = WIDTHBYTES((EntetePCX->x2-EntetePCX->x1+1)
			* (EntetePCX->yBits*EntetePCX->cNbrPlanes));

		// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
		HGLOBAL hNewDib=GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)
			+ nColors*sizeof(RGBQUAD)
			+ (nScanWidth*(EntetePCX->y2-EntetePCX->y1+1)));
		if(!hNewDib)
			return FALSE;  // Pas assez de mémoire ou problème

		// Adresse du nouveau bitmap
		LPBITMAPINFO BiDest=(LPBITMAPINFO)GlobalLock(hNewDib);

		// Copie des données du Header
		BiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
		BiDest->bmiHeader.biWidth = (LONG)(EntetePCX->x2-EntetePCX->x1+1);
		BiDest->bmiHeader.biHeight = (LONG)(EntetePCX->y2-EntetePCX->y1+1);
		BiDest->bmiHeader.biPlanes = 1;
		BiDest->bmiHeader.biBitCount = EntetePCX->yBits*EntetePCX->cNbrPlanes;
		BiDest->bmiHeader.biCompression = BI_RGB;
		BiDest->bmiHeader.biSizeImage = nScanWidth*BiDest->bmiHeader.biHeight;
		BiDest->bmiHeader.biXPelsPerMeter = (LONG)(EntetePCX->wHres/0.0254+0.5);
		BiDest->bmiHeader.biYPelsPerMeter = (LONG)(EntetePCX->wVres/0.0254+0.5);
		BiDest->bmiHeader.biClrUsed = nColors;
		BiDest->bmiHeader.biClrImportant = NULL;

		// Détermination de la position des bits (source et destination)
		BYTE* lpDestBitsOrg=(BYTE*)BiDest+sizeof(BITMAPINFOHEADER)
			+nColors*sizeof(RGBQUAD);
		BYTE* lpSrcBits=(BYTE*)m_LoadBuffer + sizeof(TypeHeaderPCX);
		BYTE* lpDestBits;

		// Réservation de la mémoire pour une ligne
		lpLineBits=(BYTE*)malloc((size_t)EntetePCX->wBytesPerLine*(size_t)EntetePCX->cNbrPlanes);
		if(!lpLineBits)
		{
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
			return FALSE;
		}

		// Décodage succéssif des lignes
		for(int y=BiDest->bmiHeader.biHeight-1; y>=0; y--)
		{
			// Décodage d'une ligne
			for(int j=0; j<EntetePCX->wBytesPerLine*EntetePCX->cNbrPlanes; )
			{
				int nCount=1;
				BYTE nVal=*(lpSrcBits++);
				if(nVal>=0xC0)
				{
					nCount=nVal-0xC0;
					nVal=*(lpSrcBits++);
				}
				for(int k=0; k<nCount; k++)
				{
					if(j>EntetePCX->wBytesPerLine*EntetePCX->cNbrPlanes)
						break;
					lpLineBits[j++]=nVal;
				}
			}

			// Traitement selon le nombre de bits/pixel
			// -> 8 bits et 1 bit/pixel (en 1 plan)
			if(BiDest->bmiHeader.biBitCount==8 || BiDest->bmiHeader.biBitCount==1)
			{
				lpDestBits=lpDestBitsOrg+(nScanWidth*y);
				for(int i=0; i<EntetePCX->wBytesPerLine; i++)
					*(lpDestBits++)=lpLineBits[i];
			}

			// -> 4 bit/pixel (4 plans de 1 bit)
			if(BiDest->bmiHeader.biBitCount==4)
			{
				for(int nPlane=0; nPlane<EntetePCX->cNbrPlanes; nPlane++)
				{
					lpDestBits=lpDestBitsOrg+(nScanWidth*y);
					for(int i=0; i<EntetePCX->wBytesPerLine; i++)
					{
						if(i<<2>=nScanWidth)
							break;
						for(int k=7; k>0; )
						{
							*(lpDestBits)|=
								((lpLineBits[i+(nPlane*EntetePCX->wBytesPerLine)]>>(k--))&1)<<(nPlane+4);
							*(lpDestBits++)|=
								((lpLineBits[i+(nPlane*EntetePCX->wBytesPerLine)]>>(k--))&1)<<nPlane;
						}
					}
				}
			}

			// -> 24 bits (en 3 plans RGB -> convertir en 1 plan BRG)
			if(BiDest->bmiHeader.biBitCount==24)
				for(int nPlane=0; nPlane<3; nPlane++)
				{
					lpDestBits=lpDestBitsOrg+(nScanWidth*y)+(2-nPlane);
					for(int i=0; i<EntetePCX->wBytesPerLine; i++)
					{
						*(lpDestBits)=lpLineBits[i+(nPlane*EntetePCX->wBytesPerLine)];
						lpDestBits+=3;
					}
				}
		}
		// Libération de la mémoire de la ligne
		free((void*)lpLineBits);
		lpLineBits = NULL;
		
		// Remplissage de la palette selon nombre de bits
		if(nColors==2)
		{	
			BiDest->bmiColors[0].rgbBlue =
			BiDest->bmiColors[0].rgbGreen =
			BiDest->bmiColors[0].rgbRed = 
			BiDest->bmiColors[0].rgbReserved =
			BiDest->bmiColors[1].rgbReserved = NULL;
			BiDest->bmiColors[1].rgbBlue =
			BiDest->bmiColors[1].rgbGreen =
			BiDest->bmiColors[1].rgbRed = 0xFF;
		}	
		if(nColors==16)
		{	
			for(int i=0; i<16; i++)
			{
				BiDest->bmiColors[i].rgbRed = EntetePCX->yPalette[i*3];
				BiDest->bmiColors[i].rgbGreen = EntetePCX->yPalette[i*3+1];
				BiDest->bmiColors[i].rgbBlue = EntetePCX->yPalette[i*3+2];
				BiDest->bmiColors[i].rgbReserved=NULL;
			}
		}
		if(nColors==256)
		{
			lpSrcBits++;

			for(int i=0; i<256; i++)
			{
				BiDest->bmiColors[i].rgbRed=*(lpSrcBits++);
				BiDest->bmiColors[i].rgbGreen=*(lpSrcBits++);
				BiDest->bmiColors[i].rgbBlue=*(lpSrcBits++);
				BiDest->bmiColors[i].rgbReserved=NULL;
			}
		}

		// Fini, on initialise le bitmap final
		GlobalUnlock(hNewDib);
		int nType=GetDefaultType(BiDest->bmiHeader.biBitCount);
		if(EntetePCX->wTypePalette == 2 && nType==IMG_TYPE_COL256)
			nType = IMG_TYPE_NG256;
		if(EntetePCX->wTypePalette == 2 && nType==IMG_TYPE_COL16)
			nType = IMG_TYPE_NG16;
		BOOL bRet = Init(hNewDib, nType);
		if(bRet)
			m_nFileFormat = IMG_FORMAT_PCX;
		else
			GlobalFree(hNewDib);
		return bRet;
	}
	catch(...)
	{
		if(hNewDib)
		{
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
		}
		if(lpLineBits)
			free((void*)lpLineBits);
		return FALSE;
	}
}
#endif

#if defined(CIMAGE_LOADFILE) || defined(CIMAGE_LDRSRC_TGA)
// Charge une image au format TGA
BOOL CImage::LoadTGA()
{
	// Première vérif: taille minimale pour le header
	if(_msize(m_LoadBuffer)<sizeof(TypeHeaderTGA))
		return FALSE;

	TypeHeaderTGA* EnteteTGA = (TypeHeaderTGA*)m_LoadBuffer;

	// Vérification du format
	if(EnteteTGA->ColorMapType<0 || EnteteTGA->ColorMapType>1)
		return FALSE;
	if((EnteteTGA->ImageType<1 && EnteteTGA->ImageType>3)
			|| (EnteteTGA->ImageType<9 && EnteteTGA->ImageType>10))
		return FALSE;
	if(!EnteteTGA->IS_Width || !EnteteTGA->IS_Height)
		return FALSE;
	if(EnteteTGA->IS_BPP!=8 && EnteteTGA->IS_BPP!=24)
		return FALSE; // Images TGA seulement en 8 et 24 BPP
	if(EnteteTGA->CMS_MapBPP !=0 && EnteteTGA->CMS_MapBPP!=24)
		return FALSE;

	// Détermination du nombre de couleurs et largeurs lignes
	int nColors = 0x1FF & (1 << EnteteTGA->IS_BPP);
	int nScanWidth = WIDTHBYTES((EnteteTGA->IS_Width) * EnteteTGA->IS_BPP);

	if(nColors > 256)
		return FALSE;

	HGLOBAL hNewDib = NULL;

	try
	{
		// ça a l'air tout bon, on continue en réservant le nouveau bitmap
		hNewDib=GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)
			+ nColors*sizeof(RGBQUAD)
			+ nScanWidth*EnteteTGA->IS_Height);
		if(!hNewDib)
			return FALSE;  // Pas assez de mémoire ou problème

		// Adresse du nouveau bitmap
		LPBITMAPINFO BiDest=(LPBITMAPINFO)GlobalLock(hNewDib);

		// Copie des données du Header
		BiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
		BiDest->bmiHeader.biWidth = (LONG)EnteteTGA->IS_Width;
		BiDest->bmiHeader.biHeight = (LONG)EnteteTGA->IS_Height;
		BiDest->bmiHeader.biPlanes = 1;
		BiDest->bmiHeader.biBitCount = EnteteTGA->IS_BPP;
		BiDest->bmiHeader.biCompression = BI_RGB;
		BiDest->bmiHeader.biSizeImage = nScanWidth*BiDest->bmiHeader.biHeight;
		BiDest->bmiHeader.biXPelsPerMeter =
			BiDest->bmiHeader.biYPelsPerMeter = DEFAULT_RES;
		BiDest->bmiHeader.biClrUsed = nColors;
		BiDest->bmiHeader.biClrImportant = NULL;

		// On détermine le sens de l'image codée
		int nXBegin, nXEnd, nXStep;
		int nYBegin, nYEnd, nYStep;
		if(!(EnteteTGA->IS_Descriptor & 0x10))
		{
			nXBegin = 0;
			nXEnd = EnteteTGA->IS_Width;
			nXStep = 1;
		}
		else
		{
			nXBegin = EnteteTGA->IS_Width;
			nXEnd = 0;
			nXStep = -1;
		}
		if(!(EnteteTGA->IS_Descriptor & 0x20))
		{
			nYBegin = 0;
			nYEnd = EnteteTGA->IS_Height;
			nYStep = 1;
		}
		else
		{
			nYBegin = EnteteTGA->IS_Height;
			nYEnd = 0;
			nYStep = -1;
		}

		BYTE* ImgDatas = (BYTE*)m_LoadBuffer + sizeof(TypeHeaderTGA) + EnteteTGA->IDLen;
		BYTE* EndData = (BYTE*)m_LoadBuffer + _msize(m_LoadBuffer);

		// Construction de la palette (si necessaire)
		if(nColors && EnteteTGA->ColorMapType)
		{
			for(int i=0; i<EnteteTGA->CMS_NbrColor; i++)
			{
				if(ImgDatas > EndData-3)
				{
					GlobalUnlock(hNewDib);
					GlobalFree(hNewDib);
					return FALSE;
				}

				BiDest->bmiColors[i].rgbBlue = *(ImgDatas++);
				BiDest->bmiColors[i].rgbGreen = *(ImgDatas++);
				BiDest->bmiColors[i].rgbRed = *(ImgDatas++);
			}
		}

		// Détermination de la position des bits (destination)
		BYTE* lpBits=(BYTE*)BiDest+sizeof(BITMAPINFOHEADER)
			+nColors*sizeof(RGBQUAD);

		// Décodage de l'image
		if(EnteteTGA->ImageType < 3)
		{
			// Image non compressée
			for(int y = nYBegin; y < nYEnd; y+=nYStep)
				for(int x = nXBegin; x < nXEnd; x+=nXStep)
				{
					if(ImgDatas > EndData)
					{
						GlobalUnlock(hNewDib);
						GlobalFree(hNewDib);
						return FALSE;
					}
					if(EnteteTGA->ImageType == 1)
						lpBits[y*nScanWidth+x] = *(ImgDatas++);
					else
					{
						lpBits[y*nScanWidth+3*x] = *(ImgDatas++);
						lpBits[y*nScanWidth+3*x+1] = *(ImgDatas++);
						lpBits[y*nScanWidth+3*x+2] = *(ImgDatas++);
					}
				}
		}
		else
		{
			// Image compressée RLE
			int nCount;
			BYTE cData1, cData2, cData3;
			int x = nXBegin;
			int y = nYBegin;
			BOOL bBreak = FALSE;
			while(ImgDatas<EndData && !bBreak)
			{
				nCount = *(ImgDatas++);
				if(nCount & 0x80)
				{
					// Run-length packet
					nCount = (nCount & 0x7F) + 1;
					if(nCount>128)
					{
						GlobalUnlock(hNewDib);
						GlobalFree(hNewDib);
						return FALSE;
					}
					cData1 = *(ImgDatas++);
					if(EnteteTGA->ImageType == 10)
					{
						cData2 = *(ImgDatas++);
						cData3 = *(ImgDatas++);
					}
					for(int i=0; i<nCount && !bBreak; i++)
					{
						if(EnteteTGA->ImageType == 9)
							lpBits[y*nScanWidth+x] = cData1;
						else
						{
							lpBits[y*nScanWidth+3*x] = cData1;
							lpBits[y*nScanWidth+3*x+1] = cData2;
							lpBits[y*nScanWidth+3*x+2] = cData3;
						}
						x += nXStep;
						if((nXStep<0 && x<=nXEnd) || (nXStep>0 && x>=nXEnd))
						{
							y += nYStep;
							x = nXBegin;
						}
						if((nYStep<0 && y<=nYEnd) || (nYStep>0 && y>=nYEnd))
							bBreak = TRUE;
					}
				}
				else
				{
					// Raw packet
					nCount++;
					if(nCount>128)
					{
						GlobalUnlock(hNewDib);
						GlobalFree(hNewDib);
						return FALSE;
					}

					for(int i=0; i<nCount && !bBreak; i++)
					{
						if(EnteteTGA->ImageType == 9)
							lpBits[y*nScanWidth+x] = *(ImgDatas++);
						else
						{
							lpBits[y*nScanWidth+3*x] = *(ImgDatas++);
							lpBits[y*nScanWidth+3*x+1] = *(ImgDatas++);
							lpBits[y*nScanWidth+3*x+2] = *(ImgDatas++);
						}
						x += nXStep;
						if((nXStep<0 && x<=nXEnd) || (nXStep>0 && x>=nXEnd))
						{
							y += nYStep;
							x = nXBegin;
						}
						if((nYStep<0 && y<=nYEnd) || (nYStep>0 && y>=nYEnd))
							bBreak = TRUE;
					}
				}
				if((nXStep<0 && x<=nXEnd) || (nXStep>0 && x>=nXEnd))
				{
					y += nYStep;
					x = nXBegin;
				}
				if((nYStep<0 && y<=nYEnd) || (nYStep>0 && y>=nYEnd))
					bBreak = TRUE;
			}
		}

		// Fini, on initialise le bitmap final
		GlobalUnlock(hNewDib);
		BOOL bRet = Init(hNewDib, GetDefaultType(BiDest->bmiHeader.biBitCount));
		if(bRet)
			m_nFileFormat = IMG_FORMAT_TGA;
		else
			GlobalFree(hNewDib);
		return bRet;
	}
	catch(...)
	{
		if(hNewDib)
		{
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
		}
		return FALSE;
	}
}
#endif

#if defined(CIMAGE_LOADFILE) || defined(CIMAGE_LDRSRC_GIF)
// Chargement des images au format GIF
BOOL CImage::LoadGIF()
{
	if(_msize(m_LoadBuffer) < sizeof(TypeHeaderGIFGlobal))
		return FALSE;

	// Quelques tests pour voir si c'est bien du GIF
	TypeHeaderGIFGlobal* EnteteGlobal=(TypeHeaderGIFGlobal*)m_LoadBuffer;
	if(strncmp((const char*)EnteteGlobal->szSignature, "GIF", 3))
		return FALSE;
	if(strncmp((const char*)EnteteGlobal->szVersion, "87a", 3)
			&& strncmp((const char*)EnteteGlobal->szVersion, "89a", 3))
		return FALSE;

	HGLOBAL hNewDib = NULL;
	short* pPrefix = NULL;
	BYTE* pPixels = NULL;
	BYTE* pSuffix = NULL;
	BYTE* pPixelStack= NULL;

	try
	{
		int nBPP = ((EnteteGlobal->cFlags & 0x70) >> 4) + 1;
		if(nBPP < 1)
			nBPP = 8;
		if(nBPP>1 && nBPP<4)
			nBPP = 8;
		if(nBPP>4 && nBPP<8)
			nBPP = 8;

		int nGifColors = 0;
		if(EnteteGlobal->cFlags & 0x80)
			nGifColors = 1 << ((EnteteGlobal->cFlags & 0x07)+1);

		TypeHeaderGIFLocal* EnteteLocal=(TypeHeaderGIFLocal*)((BYTE*)m_LoadBuffer
			+ sizeof(TypeHeaderGIFGlobal) + 3*nGifColors);
		while(EnteteLocal->cId == '!')
		{
			if(*((BYTE*)EnteteLocal+1)==255)
				EnteteLocal = (TypeHeaderGIFLocal*)(((BYTE*)EnteteLocal) + *((BYTE*)EnteteLocal+2)+8);
			else
			{
				if(*((BYTE*)EnteteLocal+1)==0xF9)
				{
					if(*((BYTE*)EnteteLocal+3) & 1)
						SetTransparentColor((DWORD)(*((BYTE*)EnteteLocal+6)));
				}
				EnteteLocal = (TypeHeaderGIFLocal*)(((BYTE*)EnteteLocal) + *((BYTE*)EnteteLocal+2)+4);
			}
		}
		if(EnteteLocal->cId != ',')
			return FALSE;

		// Copie de la palette
		BYTE* Palette = (BYTE*)m_LoadBuffer + sizeof(TypeHeaderGIFGlobal);
		BYTE* lpSrcBits = (BYTE*)EnteteLocal + sizeof(TypeHeaderGIFLocal);
		if(EnteteLocal->cFlags & 0x80)
		{
			Palette = (BYTE*)EnteteLocal + sizeof(TypeHeaderGIFLocal);
			nGifColors = 1 << ((EnteteLocal->cFlags & 0x07)+1);
			BYTE* lpSrcBits= Palette + 3*nGifColors;
		}

		if(nGifColors > 16)
			nBPP = 8;
		if(nGifColors > 2 && nGifColors < 16)
			nBPP = 4;

		// Réserve la place pour le bitmap
		int nColors = 0x1FF & (1 << nBPP);
		int nScanWidth = WIDTHBYTES(EnteteLocal->wWidth * nBPP);

		// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
		hNewDib=GlobalAlloc(GHND, sizeof(BITMAPINFOHEADER)
			+ nColors*sizeof(RGBQUAD) + (nScanWidth*EnteteLocal->wHeight));
		if(!hNewDib)
			return FALSE;  // Pas assez de mémoire ou problème

		// Adresse du nouveau bitmap
		LPBITMAPINFO BiDest=(LPBITMAPINFO)GlobalLock(hNewDib);

		// Copie des données du Header
		BiDest->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
		BiDest->bmiHeader.biWidth = (LONG)EnteteLocal->wWidth;
		BiDest->bmiHeader.biHeight = (LONG)EnteteLocal->wHeight;
		BiDest->bmiHeader.biPlanes = 1;
		BiDest->bmiHeader.biBitCount = nBPP;
		BiDest->bmiHeader.biCompression = BI_RGB;
		BiDest->bmiHeader.biSizeImage = nScanWidth*BiDest->bmiHeader.biHeight;
		BiDest->bmiHeader.biXPelsPerMeter = DEFAULT_RES;
		BiDest->bmiHeader.biYPelsPerMeter = DEFAULT_RES;
		BiDest->bmiHeader.biClrUsed = nColors;
		BiDest->bmiHeader.biClrImportant = NULL;

		if(!nGifColors)
		{
			BiDest->bmiColors[1].rgbRed = BiDest->bmiColors[1].rgbGreen
				= BiDest->bmiColors[1].rgbBlue = 255;
		}
		else
		{
			for(int i=0; i<min(nGifColors, nColors); i++)
			{
				BiDest->bmiColors[i].rgbRed = *(Palette + 3*i);
				BiDest->bmiColors[i].rgbGreen = *(Palette + 3*i +1);
				BiDest->bmiColors[i].rgbBlue = *(Palette + 3*i + 2);
			}
		}
		BYTE* lpDestBits=(BYTE*)BiDest+sizeof(BITMAPINFOHEADER)
			+nColors*sizeof(RGBQUAD);

		// Décodage des données de l'image (LZW)
		// Allocate decoder tables.
		short* pPrefix=(short*)malloc(MAX_LZW_STACKSIZE*sizeof(short));
		BYTE* pPixels = (BYTE*)malloc(EnteteLocal->wWidth*EnteteLocal->wHeight);
		BYTE* pSuffix=(BYTE*)malloc(MAX_LZW_STACKSIZE*sizeof(BYTE));
		BYTE* pPixelStack=(BYTE*)malloc((MAX_LZW_STACKSIZE+1)*sizeof(BYTE));
		if(!pPixels || !pPrefix || !pSuffix || !pPixelStack)
		{
			free(pPrefix);
			free(pPixels);
			free(pSuffix);
			free(pPixelStack);
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
			return FALSE;
		}

		// Initialize GIF data stream decoder.
		BYTE cDataSize=*(lpSrcBits++);
		int nClear=1 << cDataSize;
		int nEndOfInformation = nClear+1;
		int nAvailable = nClear+2;
		int nOldCode = -1;
		int nCodeSize = cDataSize+1;
		int nCodeMask=(1 << nCodeSize)-1;
		for(int nCode=0; nCode < nClear; nCode++)
		{
			pPrefix[nCode] = 0;
			pSuffix[nCode] = nCode;
		}

		// Decode GIF pixel stream.
		UINT nDatum = 0;
		int nBits = 0;
		BYTE* pC = lpSrcBits;
		int nCount = 0;
		BYTE cFirst = 0;
		BYTE* pTopStack = pPixelStack;
		BYTE* pP = pPixels;
		for(int i=0; i < (int)(BiDest->bmiHeader.biWidth*BiDest->bmiHeader.biHeight); )
		{
			if(pTopStack == pPixelStack)
			{
				if(nBits < nCodeSize)
				{
					// Load bytes until there is enough bits for a nCode.
					if(nCount == 0)
					{
						// Read a new data block.
						//lpSrcBits=pC;
						nCount = *(pC++);
						//pC=lpSrcBits;
					}
					nDatum += (*pC) << nBits;
					nBits += 8;
					pC++;
					nCount--;
					continue;
				}
				// Get the next nCode.
				nCode = nDatum & nCodeMask;
				nDatum >>= nCodeSize;
				nBits -= nCodeSize;
				// Interpret the nCode
				if((nCode > nAvailable) || (nCode == nEndOfInformation))
					break;
				if(nCode == nClear)
				{
					// Reset decoder.
					nCodeSize = cDataSize+1;
					nCodeMask = (1 << nCodeSize)-1;
					nAvailable = nClear+2;
					nOldCode = -1;
					continue;
				}
				if(nOldCode == -1)
				{
					*(pTopStack++) = pSuffix[nCode];
					nOldCode = nCode;
					cFirst = (BYTE)nCode;
					continue;
				}
				int nInCode = nCode;
				if(nCode == nAvailable)
				{
					*(pTopStack++) = cFirst;
					nCode = nOldCode;
				}
				while(nCode > nClear)
				{
					*(pTopStack++) = pSuffix[nCode];
					nCode = pPrefix[nCode];
				}
				cFirst = pSuffix[nCode];

				// Add a new string to the string table,
				if(nAvailable >= MAX_LZW_STACKSIZE)
					break;
				*(pTopStack++) = cFirst;
				pPrefix[nAvailable] = nOldCode;
				pSuffix[nAvailable] = cFirst;
				nAvailable++;
				if(((nAvailable & nCodeMask) == 0) && (nAvailable < MAX_LZW_STACKSIZE))
				{
					nCodeSize++;
					nCodeMask += nAvailable;
				}
				nOldCode = nInCode;
			}
			// Pop a pixel off the pixel stack.
			pTopStack--;
			*pP = (*pTopStack);
			pP++;
			i++;
		}

		// Free decoder memory.
		free(pPrefix); pPrefix = NULL;
		free(pSuffix); pSuffix = NULL;
		free(pPixelStack); pPixelStack = NULL;

		// Copie ds le bitmap final en prenant en compte l'entrelacement si besoin
		if(EnteteLocal->cFlags & 0x40)
		{
			int nInterlaceRate[4] = { 8, 8, 4, 2 };
			int nInterlaceStart[4] = { 0, 4, 2, 1 };

			//Interlace image.
			BYTE* pP = pPixels;
			int x;
			int y;
			for(int nPass=0; nPass<4; nPass++)
			{
				y=nInterlaceStart[nPass];
				while(y<(int)EnteteLocal->wHeight)
				{
					for(x=0; x<(int)EnteteLocal->wWidth; x++)
						SetPixel(x, EnteteLocal->wHeight-1-y,
							(DWORD)((BYTE)(*(pP++))), (LPBITMAPINFOHEADER)BiDest,
							nColors, nScanWidth, lpDestBits);
					y+=nInterlaceRate[nPass];
				}
			}
		}
		else
		{
			BYTE* pP = pPixels;
			for(int y=EnteteLocal->wHeight-1; y>=0; y--)
				for(int x=0; x<EnteteLocal->wWidth; x++)
					SetPixel(x, y, (DWORD)((BYTE)(*(pP++))), (LPBITMAPINFOHEADER)BiDest,
						nColors, nScanWidth, lpDestBits);
		}

		free(pPixels); pPixels = NULL;
		GlobalUnlock(hNewDib);
		DWORD dwTransparentColor = m_dwTransparentColor;
		BOOL bRet = Init(hNewDib, GetDefaultType(BiDest->bmiHeader.biBitCount));
		if(bRet)
		{
			m_nFileFormat = IMG_FORMAT_GIF;
			m_dwTransparentColor = dwTransparentColor;
		}
		else
			GlobalFree(hNewDib);
		return bRet;
	}
	catch(...)
	{
		if(hNewDib)
		{
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
		}
		if(pPrefix)
			free(pPrefix);
		if(pPixels)
			free(pPixels);
		if(pSuffix)
			free(pSuffix);
		if(pPixelStack)
			free(pPixelStack);
		return FALSE;
	}
}
#endif

#if (defined(CIMAGE_LOADFILE) && defined(CIMAGE_USE_JPEG)) || defined(CIMAGE_LDRSRC_JPEG)
// Charge une image JPEG avec la librairie externe ImageLib
BOOL CImage::LoadJPEG()
{
	// Les fichiers doivent forcément commencer par la signature JFIF
	if(_msize(m_LoadBuffer)<sizeof(FORMAT_JFIF))
		return FALSE;
	if(strncmp((char*)m_LoadBuffer, FORMAT_JFIF, sizeof(FORMAT_JFIF)-1))
		return FALSE;

	jpeg_decompress_struct cinfo;
	jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jerr.error_exit = CImageJpegErrorExit;  // Register custom error manager.

	HGLOBAL hNewDib = NULL;
	BYTE* pScanLine = NULL;

	try
	{
		jpeg_create_decompress(&cinfo);

		// Specify data source (=m_LoadBuffer)
		jpeg_source_mgr src;
		src.next_input_byte = (const JOCTET *)m_LoadBuffer;
		src.bytes_in_buffer = _msize(m_LoadBuffer);
		src.init_source = CImageJpegInitSource;
		src.fill_input_buffer = CImageJpegFillInputBuffer;
		src.resync_to_restart = jpeg_resync_to_restart;
		src.skip_input_data = CImageJpegSkipInputData;
		src.term_source = CImageJpegTermSource;
		cinfo.src = &src;

		// Read file parameters with jpeg_read_header()
		jpeg_read_header(&cinfo, TRUE);

		// Start decompressor
		jpeg_start_decompress(&cinfo);

		// Allocation de mémoire pour le nouveau bitmap
		if(!cinfo.output_width || !cinfo.output_height)
			return FALSE;

		int nBPP = cinfo.num_components<<3;
		int nScanWidth = WIDTHBYTES(cinfo.output_width * nBPP);
		int nColors = 0x1FF & (1 << nBPP);

		hNewDib = GlobalAlloc(GHND, (nScanWidth * cinfo.output_height)
			+(nColors*sizeof(RGBQUAD))+sizeof(BITMAPINFOHEADER));
		if(!hNewDib)
			return FALSE;

		LPBITMAPINFO bi = (LPBITMAPINFO)GlobalLock(hNewDib);

		// Création palette NG si necessaire
		if(nColors)
		{
			int nGray = 0;
			int nStep = 256/nColors;
			for(int i=0; i<nColors; i++)
			{
				bi->bmiColors[i].rgbRed = bi->bmiColors[i].rgbGreen
					= bi->bmiColors[i].rgbBlue = nGray;
				nGray += nStep;
			}
		}

		// Remplissage header
		bi->bmiHeader.biBitCount = nBPP;
		bi->bmiHeader.biClrUsed = nColors;
		bi->bmiHeader.biCompression = BI_RGB;
		bi->bmiHeader.biHeight = cinfo.output_height;
		bi->bmiHeader.biWidth = cinfo.output_width;
		bi->bmiHeader.biPlanes = 1;
		bi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		switch(cinfo.density_unit)
		{
			case 1:
				bi->bmiHeader.biXPelsPerMeter = DPI2PPM(cinfo.X_density);
				bi->bmiHeader.biYPelsPerMeter = DPI2PPM(cinfo.Y_density);
				break;
			case 2:
				bi->bmiHeader.biXPelsPerMeter = cinfo.X_density;
				bi->bmiHeader.biYPelsPerMeter = cinfo.Y_density;
				break;
		}
		if(bi->bmiHeader.biXPelsPerMeter<1)
			bi->bmiHeader.biXPelsPerMeter = DEFAULT_RES;
		if(bi->bmiHeader.biYPelsPerMeter<1)
			bi->bmiHeader.biYPelsPerMeter = DEFAULT_RES;

		// Réservation espace pour une ligne
		int nLineSize = cinfo.output_width*cinfo.num_components;
		pScanLine = (BYTE*)malloc(nLineSize);

		// Pointeur sur la dernière ligne
		BYTE* pDestLine = (BYTE*)bi+bi->bmiHeader.biSize+nColors*sizeof(RGBQUAD)
			+nScanWidth*(bi->bmiHeader.biHeight-1);

		// Lecture successive des lignes
		while(cinfo.output_scanline < cinfo.output_height)
		{
			jpeg_read_scanlines(&cinfo, &pScanLine, 1);
			memcpy(pDestLine, pScanLine, nLineSize);
			if(cinfo.num_components==3)
			{
				BYTE cDummy;
				for(int i=0; i<nLineSize; i+=3)
				{
					cDummy = *(pDestLine+i);
					*(pDestLine+i) = *(pDestLine+i+2);
					*(pDestLine+i+2) = cDummy;
				}
			}
			pDestLine -= nScanWidth;
		}

		// Finish decompression
		jpeg_finish_decompress(&cinfo);

		// Release JPEG decompression object
		jpeg_destroy_decompress(&cinfo);

		free(pScanLine);
		GlobalUnlock(hNewDib);

		int nType;
		if(nBPP==8)
			nType = IMG_TYPE_NG256;
		else
			nType = IMG_TYPE_COL24;
		BOOL bRet = Init(hNewDib, nType);
		if(bRet)
			m_nFileFormat = IMG_FORMAT_JPEG;
		else
			GlobalFree(hNewDib);

		return bRet;
	}
	catch(...)
	{
		jpeg_abort_decompress(&cinfo);
		if(hNewDib)
		{
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
		}
		if(pScanLine)
			free(pScanLine);
		return FALSE;
	}
}

// Init de la source Jpeg -> ne fait rien
METHODDEF(void) CImageJpegInitSource(j_decompress_ptr cinfo)
{
}

// Gestion source Jpeg. Met EOI ds un buffer car normalement m_LoadBuffer contient tout le fichier
METHODDEF(boolean) CImageJpegFillInputBuffer(j_decompress_ptr cinfo)
{
  jpeg_source_mgr* src = cinfo->src;
  src->next_input_byte = (const JOCTET*)"\xFF\xD9";
  src->bytes_in_buffer = 2;
  return TRUE;
}

// Gestion source Jpeg -> passe n octets
METHODDEF(void) CImageJpegSkipInputData(j_decompress_ptr cinfo, long num_bytes)
{
  jpeg_source_mgr* src = cinfo->src;
  src->bytes_in_buffer -= num_bytes;
  src->next_input_byte += num_bytes;
  if (src->bytes_in_buffer < 0)
    CImageJpegFillInputBuffer(cinfo);
}

// Termine source JPeg -> ne fait rien
METHODDEF(void) CImageJpegTermSource(j_decompress_ptr cinfo)
{
}
#endif // (defined(CIMAGE_LOADFILE) && defined(CIMAGE_USE_JPEG)) || defined(CIMAGE_LDRSRC_BMP)

#if (defined(CIMAGE_LOADFILE) && defined(CIMAGE_USE_TIFF)) || defined(CIMAGE_LDRSRC_TIFF)
// Charge une image TIFF avec la librairie externe ImageLib
BOOL CImage::LoadTIFF()
{
	// Test sommaire sur le TIFF -> le fichier début par 'MM' ou 'II' suivi de (WORD)42
	if(_msize(m_LoadBuffer)<10)
		return FALSE;
	if(*((DWORD*)m_LoadBuffer)!=0x002A4949L && *((DWORD*)m_LoadBuffer)!=0x2A004D4DL)
		return FALSE;

	// Les Handlers sont nuls car la classe n'affiche rien.
	TIFFSetErrorHandler(NULL);
	TIFFSetWarningHandler(NULL);

	HGLOBAL hNewDib = NULL;
	DWORD* pScanline = NULL;
	BYTE* pScanlineBytes = NULL;

	try
	{
		TIFF* tiff = TIFFOpenMem ((BYTE*)m_LoadBuffer, _msize(m_LoadBuffer));
		if(!tiff)
			return FALSE;

		short nWidth;
		short nHeight;
		short nBitsPerSample;
		short nSamplePerPixel;
		short nPhotometric;
		short nResUnits;
		float fResX, fResY;

		// Récupération des paramètres de l'image
		TIFFGetField(tiff,TIFFTAG_IMAGEWIDTH,&nWidth);
		TIFFGetField(tiff,TIFFTAG_IMAGELENGTH,&nHeight);
		TIFFGetFieldDefaulted(tiff, TIFFTAG_BITSPERSAMPLE, &nBitsPerSample);
		TIFFGetFieldDefaulted(tiff, TIFFTAG_SAMPLESPERPIXEL, &nSamplePerPixel);
		TIFFGetFieldDefaulted(tiff, TIFFTAG_PHOTOMETRIC, &nPhotometric);
		TIFFGetFieldDefaulted(tiff, TIFFTAG_RESOLUTIONUNIT, &nResUnits);
		TIFFGetField(tiff, TIFFTAG_XRESOLUTION, &fResX);
		TIFFGetField(tiff, TIFFTAG_YRESOLUTION, &fResY);

		if(nPhotometric<PHOTOMETRIC_MINISWHITE || nPhotometric>PHOTOMETRIC_PALETTE)
		{
			TIFFClose(tiff);
			return FALSE;
		}

		int nBPP = nBitsPerSample*nSamplePerPixel;
		if(nBPP!=1 && nBPP != 4 && nBPP!=8 && nBPP!=24)
		{
			TIFFClose(tiff);
			return FALSE;
		}

		// Les bitmaps 'Tiles' (=en carreaux) sont récupérés en 24 bits car le mode palette ne marche pas
		if(nPhotometric == PHOTOMETRIC_PALETTE && TIFFIsTiled(tiff))
		{
			nBPP = 24;
			nPhotometric = PHOTOMETRIC_RGB;
		}

		int nColors = 0x1FF & (1 << nBPP);
		int nScanWidth = WIDTHBYTES(nWidth * nBPP);

		hNewDib = GlobalAlloc(GHND, (nScanWidth * nHeight)
			+(nColors*sizeof(RGBQUAD))+sizeof(BITMAPINFOHEADER));
		if(!hNewDib)
		{
			TIFFClose(tiff);
			return FALSE;
		}

		LPBITMAPINFO bi = (LPBITMAPINFO)GlobalLock(hNewDib);

		bi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi->bmiHeader.biBitCount = nBPP;
		bi->bmiHeader.biClrUsed = nColors;
		bi->bmiHeader.biCompression = BI_RGB;
		bi->bmiHeader.biHeight = (LONG)nHeight;
		bi->bmiHeader.biPlanes = 1;
		bi->bmiHeader.biWidth = (LONG)nWidth;
		switch(nResUnits)
		{
			case 2:
				bi->bmiHeader.biXPelsPerMeter = DPI2PPM(fResX);
				bi->bmiHeader.biYPelsPerMeter = DPI2PPM(fResY);
				break;
			case 3:
				bi->bmiHeader.biXPelsPerMeter = (int)(100.0*fResX);
				bi->bmiHeader.biYPelsPerMeter = (int)(100.0*fResY);
				break;
			default:
				bi->bmiHeader.biXPelsPerMeter = bi->bmiHeader.biYPelsPerMeter = DEFAULT_RES;
				break;
		}

		// Création palette NG si necessaire ou récupération palette couleur
		int i;
		switch(nPhotometric)
		{
			case PHOTOMETRIC_MINISBLACK:
				for (i=0; i<(int)nColors; i++)
				{
					bi->bmiColors[i].rgbRed = bi->bmiColors[i].rgbGreen
						= bi->bmiColors[i].rgbBlue = (255*i)/(nColors-1);
				}
				break;
			case PHOTOMETRIC_MINISWHITE:
				for (i=0; i<(int)nColors; i++)
				{
					bi->bmiColors[nColors-i-1].rgbRed = bi->bmiColors[nColors-i-1].rgbGreen
						= bi->bmiColors[nColors-i-1].rgbBlue = (255*i)/(nColors-1);
				}
				break;
			case PHOTOMETRIC_PALETTE:
				{
					unsigned short *nRedColormap=NULL, *nGreenColormap=NULL, *nBlueColormap=NULL;
					TIFFGetField(tiff, TIFFTAG_COLORMAP,
						&nRedColormap, &nGreenColormap, &nBlueColormap);
					int nRange = 256;
					for(i=0; i<nColors; i++)
						if(nRedColormap[i]>255 || nGreenColormap[i]>255 || nBlueColormap[i]>255)
						{
							nRange = 65535;
							break;
						}
					for(i=0; i<nColors; i++)
					{
						bi->bmiColors[i].rgbRed = (BYTE)(255*(int)nRedColormap[i]/nRange);
						bi->bmiColors[i].rgbGreen = (BYTE)(255*(int)nGreenColormap[i]/nRange);
						bi->bmiColors[i].rgbBlue = (BYTE)(255*(int)nBlueColormap[i]/nRange);
					}
				}
				break;
		}

		BYTE* lpBits = (BYTE*)bi+bi->bmiHeader.biSize+nColors*sizeof(RGBQUAD);

		// Pas de palette -> récupération en un seul coup
		if(nPhotometric != PHOTOMETRIC_PALETTE)
		{
			pScanline = (DWORD*)malloc(nWidth*nHeight*sizeof(DWORD)+4);
			DWORD* pDestLine = pScanline;
			if(!pScanline)
			{
				GlobalUnlock(hNewDib);
				GlobalFree(hNewDib);
				TIFFClose(tiff);
				return FALSE;
			}

			if(!TIFFReadRGBAImage(tiff, nWidth, nHeight, pScanline, 0))
			{
				GlobalUnlock(hNewDib);
				GlobalFree(hNewDib);
				TIFFClose(tiff);
				return FALSE;
			}

			for(int y=0; y<nHeight; y++)
				for(int x=0; x<nWidth; x++)
					SetPixel(x, y, *(pDestLine++), (LPBITMAPINFOHEADER)bi, nColors, nScanWidth, lpBits);

			free(pScanline);
			pScanline = NULL;
		}
		else
		{
			// Palette -> Récupération ligne par ligne
			if(TIFFIsTiled(tiff))
			{
				GlobalUnlock(hNewDib);
				GlobalFree(hNewDib);
				TIFFClose(tiff);
				return FALSE;
			}

			int nLineSize = TIFFScanlineSize(tiff);
			pScanlineBytes = (BYTE*)malloc(nLineSize);
			if(!pScanlineBytes)
			{
				GlobalUnlock(hNewDib);
				GlobalFree(hNewDib);
				TIFFClose(tiff);
				return FALSE;
			}

			for(int y=0; y<nHeight; y++)
			{
				TIFFReadScanline(tiff, pScanlineBytes, y);
				memcpy(lpBits+(nScanWidth*(nHeight-y-1)), pScanlineBytes, nLineSize);
			}

			free(pScanlineBytes);
			pScanlineBytes = NULL;
		}


		GlobalUnlock(hNewDib);
		TIFFClose(tiff);

		int nType = GetDefaultType(nBPP);
		if(nPhotometric==PHOTOMETRIC_MINISBLACK || nPhotometric==PHOTOMETRIC_MINISWHITE)
		{
			if(nBPP==4)
				nType = IMG_TYPE_NG16;
			if(nBPP==8)
				nType = IMG_TYPE_NG256;
		}
		BOOL bRet = Init(hNewDib, nType);
		if(bRet)
			m_nFileFormat = IMG_FORMAT_TIFF;
		else
			GlobalFree(hNewDib);

		return bRet;
	}
	catch(...)
	{
		if(hNewDib)
		{
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
		}
		if(pScanline)
			free(pScanline);
		if(pScanlineBytes)
			free(pScanlineBytes);
		return FALSE;
	}
}
#endif

#if (defined(CIMAGE_LOADFILE) && defined(CIMAGE_USE_PNG)) || defined(CIMAGE_LDRSRC_PNG)
// Charge une image PNG avec la librairie externe ImageLib
BOOL CImage::LoadPNG()
{
	// Les fichiers doivent forcément commencer par la signature PNG
	if(_msize(m_LoadBuffer)<sizeof(FORMAT_PNG))
		return FALSE;
	if(strncmp((char*)m_LoadBuffer, FORMAT_PNG, sizeof(FORMAT_PNG)-1))
		return FALSE;

	png_structp pPng;
	png_infop pInfo;
	DWORD dwWidth, dwHeight=NULL;
	int nBitDepth, nColorType, nInterlaceType;

	// Allocation des structures pour PNG
	pPng = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, CImagePngError, NULL);
	if(!pPng)
		return FALSE;
	pInfo = png_create_info_struct(pPng);
	if(!pInfo)
	{
		png_destroy_read_struct(&pPng, (png_infopp)NULL, (png_infopp)NULL);
		return FALSE;
	}

	HGLOBAL hNewDib = NULL;
	BYTE** pRowBuffer = NULL;
	PngCustomData CustomData;
	CustomData.pLoadBuffer = (BYTE*)m_LoadBuffer;
	CustomData.pEndBuffer = CustomData.pLoadBuffer + _msize(m_LoadBuffer);

	try
	{
		// On met la procédure de lecture perso
		png_set_read_fn(pPng, (void*)&CustomData, CImagePngRead);

		// Lecture des infos du PNG
		png_read_info(pPng, pInfo);
		png_get_IHDR(pPng, pInfo, &dwWidth, &dwHeight, &nBitDepth, &nColorType,
			&nInterlaceType, NULL, NULL);

		// Calcul de la place nécessaire pour le bitmap
		if(nBitDepth>8 || nBitDepth==2)
		{
			png_destroy_read_struct(&pPng, &pInfo, (png_infopp)NULL);
			return FALSE;
		}

		int nChannels = png_get_channels(pPng, pInfo);
		int nBPP;
		if(nChannels>=3)
			nBPP = 24;
		else
			nBPP = nBitDepth;

		int nScanWidth = WIDTHBYTES(dwWidth * nBPP);
		int nColors = 0x1FF & (1 << nBPP);

		// Réservation mémoire pour bitmap
		hNewDib = GlobalAlloc(GHND, (nScanWidth * dwHeight)
			+(nColors*sizeof(RGBQUAD))+sizeof(BITMAPINFOHEADER));
		if(!hNewDib)
			return FALSE;

		LPBITMAPINFO bi = (LPBITMAPINFO)GlobalLock(hNewDib);

		// Création palette NG si necessaire
		if(nColors && (nColorType==PNG_COLOR_TYPE_GRAY || nColorType==PNG_COLOR_TYPE_GRAY_ALPHA))
		{
			int nGray = 0;
			int nStep = 256/nColors;
			for(int i=0; i<nColors; i++)
			{
				bi->bmiColors[i].rgbRed = bi->bmiColors[i].rgbGreen
					= bi->bmiColors[i].rgbBlue = nGray;
				nGray += nStep;
			}
		}

		// Récupération palette si mode palette
		if(nColorType==PNG_COLOR_TYPE_PALETTE)
		{
			png_color* pColors;
			int nNbrColors;
			png_get_PLTE(pPng, pInfo, &pColors, &nNbrColors);
			for(int i=0; i<nNbrColors; i++)
			{
				bi->bmiColors[i].rgbRed = pColors[i].red;
				bi->bmiColors[i].rgbGreen = pColors[i].green;
				bi->bmiColors[i].rgbBlue = pColors[i].blue;
			}
		}

		if(nColorType==PNG_COLOR_TYPE_RGB || nColorType==PNG_COLOR_TYPE_RGB_ALPHA)
			png_set_bgr(pPng);

		// Remplissage header
		bi->bmiHeader.biBitCount = nBPP;
		bi->bmiHeader.biClrUsed = nColors;
		bi->bmiHeader.biCompression = BI_RGB;
		bi->bmiHeader.biHeight = dwHeight;
		bi->bmiHeader.biWidth = dwWidth;
		bi->bmiHeader.biPlanes = 1;
		bi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bi->bmiHeader.biXPelsPerMeter = png_get_x_pixels_per_meter(pPng, pInfo);
		bi->bmiHeader.biYPelsPerMeter = png_get_y_pixels_per_meter(pPng, pInfo);
		if(bi->bmiHeader.biXPelsPerMeter<1)
			bi->bmiHeader.biXPelsPerMeter = DEFAULT_RES;
		if(bi->bmiHeader.biYPelsPerMeter<1)
			bi->bmiHeader.biYPelsPerMeter = DEFAULT_RES;

		// Récupération couleur transparente
		DWORD dwTransColor = NULL;
		if(png_get_valid(pPng, pInfo, PNG_INFO_tRNS))
		{
			png_bytep pTransIdx;
			png_color_16p pTransColor;
			png_get_tRNS(pPng, pInfo, &pTransIdx, NULL, &pTransColor);
			switch(nColorType)
			{
				case PNG_COLOR_TYPE_PALETTE:
					dwTransColor = *pTransIdx | 0x80000000L;
					break;
				case PNG_COLOR_TYPE_RGB:
				case PNG_COLOR_TYPE_RGB_ALPHA:
					dwTransColor = RGB(pTransColor->red, pTransColor->green,
						pTransColor->blue) | 0x80000000L;
					break;
				case PNG_COLOR_TYPE_GRAY:
				case PNG_COLOR_TYPE_GRAY_ALPHA:
					dwTransColor = pTransColor->gray | 0x80000000L;
			}
		}		

		// Stripper alpha
		png_set_strip_alpha(pPng);

		// Récupère taille ligne -> réserve buffer pour image totale
		png_read_update_info(pPng, pInfo);
		int nRowSize = png_get_rowbytes(pPng, pInfo);
		pRowBuffer = (BYTE**)malloc(sizeof(BYTE*) * dwHeight);
		if(!pRowBuffer)
		{
			GlobalFree(hNewDib);
			png_destroy_read_struct(&pPng, &pInfo, (png_infopp)NULL);
			return FALSE;
		}
		for(int i=0; i<(int)dwHeight; i++)
		{
			pRowBuffer[i] = (BYTE*)malloc(nRowSize);
			if(!pRowBuffer[i])
			{
				GlobalFree(hNewDib);
				png_destroy_read_struct(&pPng, &pInfo, (png_infopp)NULL);
				for(int j=0; j<i; j++)
					free(pRowBuffer[j]);
				free(pRowBuffer);
				return FALSE;
			}
		}

		png_read_image(pPng, pRowBuffer);

		// Copie des lignes une à une ds le bitmap
		BYTE* pDestLine = (BYTE*)bi+bi->bmiHeader.biSize+nColors*sizeof(RGBQUAD)
			+nScanWidth*(bi->bmiHeader.biHeight-1);
		for(i=0; i<(int)dwHeight; i++)
		{
			memcpy(pDestLine, pRowBuffer[i], nRowSize);
			pDestLine -= nScanWidth;
		}

		// Fin de lecture, libération mémoire et init bitmap
		png_destroy_read_struct(&pPng, &pInfo, (png_infopp)NULL);
		for(i=0; i<(int)dwHeight; i++)
			free(pRowBuffer[i]);
		free(pRowBuffer);
		GlobalUnlock(hNewDib);

		int nType;
		nType = GetDefaultType(bi->bmiHeader.biBitCount);
		if(nColorType==PNG_COLOR_TYPE_GRAY || nColorType==PNG_COLOR_TYPE_GRAY_ALPHA)
		{
			if(nType==IMG_TYPE_COL256)
				nType = IMG_TYPE_NG256;
			if(nType==IMG_TYPE_COL16)
				nType = IMG_TYPE_NG16;
		}
		BOOL bRet = Init(hNewDib, nType);
		if(bRet)
		{
			m_nFileFormat = IMG_FORMAT_PNG;
			m_dwTransparentColor = dwTransColor;
		}

		else
			GlobalFree(hNewDib);

		return bRet;
	}
	catch(...)
	{
		// Erreur -> libération mémoire et retour
		png_destroy_read_struct(&pPng, &pInfo, (png_infopp)NULL);
		if(hNewDib)
		{
			GlobalUnlock(hNewDib);
			GlobalFree(hNewDib);
		}
		if(pRowBuffer)
		{
			for(int i=0; i<(int)dwHeight; i++)
				free(pRowBuffer[i]);
			free(pRowBuffer);
		}
		return FALSE;
	}
}

// Lecture des données pour le PNG
void CImagePngRead(png_structp pPng, png_bytep pData, unsigned int nLen)
{
	PngCustomData *pCustomData = (PngCustomData*)pPng->io_ptr;
	if(pCustomData->pLoadBuffer+nLen > pCustomData->pEndBuffer)
		png_error(pPng, "read Error");
	memcpy(pData, pCustomData->pLoadBuffer, nLen);
	pCustomData->pLoadBuffer += nLen;
}
#endif

//===================================================================
// Fonctions communes au chargement et à la sauvegarde de fichiers
//===================================================================

#if defined(CIMAGE_USE_JPEG)
// Gestionnaire d'erreur du jpeg, commun à la compression et à la décompression
METHODDEF(void) CImageJpegErrorExit(j_common_ptr pcinfo)
{
	// Génère une erreur systématique qui est reprise par le catch de la classe
	BYTE* pDummy = NULL;
	*pDummy = 1;
}
#endif

#if defined(CIMAGE_USE_PNG)
// Gestionnaire d'erreur du PNG, commun à la compression et à la décompression
void CImagePngError(png_structp pPng, png_const_charp ErrMsg)
{
	// Génère une erreur systématique qui est reprise par le catch de la classe
	BYTE* pDummy = NULL;
	*pDummy = 1;
}
#endif

//===================================================================
// Fonctions de sauvegarde de fichier. Activer avec CIMAGE_SAVEFILE
//===================================================================

#if defined(CIMAGE_SAVEFILE)

// Sauvegarde de l'image sur disque avec le format demandé en paramètre
BOOL CImage::SaveFile(LPCTSTR szFileName, int nFormat, int nData1, int nData2)
{
	if(!szFileName || !szFileName[0])
		return FALSE;

	if(!m_hDib)
		return FALSE; // Pas d'image à sauver -> inutile de se fatiguer!!

	if(nFormat>=IMG_FORMAT_END)
		return FALSE; // Format inconnu au bataillon -> on rentre...

	// Init du buffer de sauvegarde
	if(!InitSaveBuffer())
		return FALSE;

	// Ouverture générale du fichier. Le handle est ensuite passé aux sous-fonctions
	HANDLE hFile=CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	BOOL bSuccess = FALSE;
	// Procédure de sauvegarde en fonction du format demandé
	switch(nFormat)
	{
		case IMG_FORMAT_BMPWIN:
			bSuccess = SaveBMPWIN(hFile);
			break;
		case IMG_FORMAT_BMPOS2:
			bSuccess = SaveBMPOS2(hFile);
			break;
		case IMG_FORMAT_RLE:
			bSuccess = SaveRLE(hFile);
			break;
		case IMG_FORMAT_PCX:
			bSuccess=SavePCX(hFile);
			break;
		case IMG_FORMAT_GIF:
			bSuccess=SaveGIF(hFile);
			break;
		case IMG_FORMAT_JPEG:
			#if defined(CIMAGE_USE_JPEG)
				bSuccess = SaveJPEG(hFile, nData1);
			#endif
			break;
		case IMG_FORMAT_TIFF:
			#if defined(CIMAGE_USE_TIFF)
				bSuccess = SaveTIFF(hFile, szFileName, nData1);
			#endif
			break;
		case IMG_FORMAT_TGA:
			bSuccess=SaveTGA(hFile, nData1);
			// nData1 contient le type de compression à utiliser
			break;
		case IMG_FORMAT_PNG:
			#if defined(CIMAGE_USE_PNG)
				bSuccess = SavePNG(hFile);
			#endif
			break;
	}

	// Flush et destruction du buffer
	if(!FlushSaveBuffer(hFile, bSuccess))
		bSuccess=FALSE;

	// Le type de format est remis à jour ici, pas dans les sous-fonctions
	if(bSuccess)
		m_nFileFormat = nFormat;

	// Fermeture du fichier en cours
	CloseHandle(hFile);

	// Si la sauvegarde a échoué -> on supprime le fichier créé vide
	if(!bSuccess)
		DeleteFile(szFileName);

	return bSuccess;
}

// Init du buffer de sauvegarde. Les fonctions de bufferisation permettent
//  de limiter les accès disques et d'accelérer ainsi les sauvegardes
BOOL CImage::InitSaveBuffer()
{
	// On vérifie que m_LoadBuffer n'est pas déjà utilisé
	if(m_LoadBuffer)
		return FALSE;

	// Réserve de la mémoire avec taille standard de 10ko
	if(!(m_LoadBuffer=malloc(SIZE_SAVE_BUFFER)))
		return FALSE;

	// OK -> on ramène TRUE
	memset(m_LoadBuffer, 0, SIZE_SAVE_BUFFER);
	m_dwSaveBufferLen = NULL;
	return TRUE;
}

// Place des octets à sauver du disque dans le buffer. Si le buffer est
//  plein, il est écrit sur disque et vidé
BOOL CImage::WriteSaveBuffer(HANDLE hFile, LPVOID Buffer, DWORD nLen)
{
	// !! Ne jamais appeler cette fonction si m_LoadBuffer n'est pas valide
	// !! Pour augmenter la rapidité, aucune vérification sur la validité
	//  des données n'est effectuée

	// Copie des octets 1 à 1 dans le buffer
	for(DWORD i=0; i<nLen; )
	{
		((BYTE*)m_LoadBuffer)[m_dwSaveBufferLen++]=((BYTE*)Buffer)[i++];

		// Si on dépasse le buffer, on écrit et on vide
		if(m_dwSaveBufferLen>=SIZE_SAVE_BUFFER)
		{
			DWORD dwByteWrite;
			if(!WriteFile(hFile, m_LoadBuffer, m_dwSaveBufferLen,
					&dwByteWrite, NULL)
					|| dwByteWrite!=m_dwSaveBufferLen)
				return FALSE;
			memset(m_LoadBuffer, 0, SIZE_SAVE_BUFFER);
			m_dwSaveBufferLen = NULL;
		}
	}
	return TRUE;
}

// Force l'écriture des données sur disque et détruit le buffer
// Si bWrite==FALSE, seulement destruction, pas d'écriture
BOOL CImage::FlushSaveBuffer(HANDLE hFile, BOOL bWrite)
{
	// Si buffer inexistant -> on rentre
	if(!m_LoadBuffer)
		return FALSE;

	BOOL bSuccess = TRUE;

	// Ecriture des données sur disque
	if(bWrite && m_dwSaveBufferLen)
	{
		DWORD dwByteWrite;
		if(!WriteFile(hFile, m_LoadBuffer, m_dwSaveBufferLen,
				&dwByteWrite, NULL)
				|| dwByteWrite!=m_dwSaveBufferLen)
			bSuccess = FALSE;
	}

	// Destruction du buffer et sortie
	free(m_LoadBuffer);
	m_LoadBuffer=NULL;
	return bSuccess;
}

// Sauvegarde du BMP sous format natif dans le fichier hFile
BOOL CImage::SaveBMPWIN(HANDLE hFile)
{
	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);			
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);
	int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);

	// Header avec marque de signature
	BITMAPFILEHEADER BmHeader;
	memset(&BmHeader, 0, sizeof(BITMAPFILEHEADER));
	BmHeader.bfType=FORMAT_BMP;
	BmHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
		+nColors*sizeof(RGBQUAD);
	BmHeader.bfSize=BmHeader.bfOffBits+nScanWidth*BmInfo->biHeight;
	
	// Ecriture du Header sur disque
	if(!WriteSaveBuffer(hFile, &BmHeader, sizeof(BITMAPFILEHEADER)))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Détermination de la taille du Bitmap à sauver
	DWORD dwTaille = (DWORD)(BmHeader.bfSize-sizeof(BITMAPFILEHEADER));
	if(GlobalSize(m_hDib)<dwTaille)
		dwTaille=GlobalSize(m_hDib);

	// Ecriture de l'image sur disque
	if(!WriteSaveBuffer(hFile, BmInfo, dwTaille))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Terminé sans encombre
	GlobalUnlock(m_hDib);
	return TRUE;
}

// Sauvegarde d'un bitmap au format BMP OS/2
BOOL CImage::SaveBMPOS2(HANDLE hFile)
{
	LPBITMAPINFO BmInfo=(LPBITMAPINFO)GlobalLock(m_hDib);			
	int nColors = BmInfo->bmiHeader.biClrUsed ? BmInfo->bmiHeader.biClrUsed
		: 0x1FF & (1 << BmInfo->bmiHeader.biBitCount);
	int nScanWidth = WIDTHBYTES(BmInfo->bmiHeader.biWidth * BmInfo->bmiHeader.biBitCount);

	// Header avec marque de signature
	BITMAPFILEHEADER BmHeader;
	memset(&BmHeader, 0, sizeof(BITMAPFILEHEADER));
	BmHeader.bfType=FORMAT_BMP;
	BmHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPCOREHEADER)
		+nColors*sizeof(RGBTRIPLE);
	BmHeader.bfSize=BmHeader.bfOffBits+nScanWidth*BmInfo->bmiHeader.biHeight;

	// Préparation du header de type BITMAPCORE
	LPBITMAPCOREINFO BmCore=(LPBITMAPCOREINFO)malloc(sizeof(BITMAPCOREHEADER)
		+nColors*sizeof(RGBTRIPLE));
	if(!BmCore)
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}
	BmCore->bmciHeader.bcSize=sizeof(BITMAPCOREHEADER);
	BmCore->bmciHeader.bcWidth=(WORD)BmInfo->bmiHeader.biWidth;
	BmCore->bmciHeader.bcHeight=(WORD)BmInfo->bmiHeader.biHeight;
	BmCore->bmciHeader.bcPlanes=BmInfo->bmiHeader.biPlanes;
	BmCore->bmciHeader.bcBitCount=BmInfo->bmiHeader.biBitCount;

	for(int i=0; i<nColors; i++)
	{
		BmCore->bmciColors[i].rgbtBlue = BmInfo->bmiColors[i].rgbBlue;
		BmCore->bmciColors[i].rgbtGreen = BmInfo->bmiColors[i].rgbGreen;
		BmCore->bmciColors[i].rgbtRed = BmInfo->bmiColors[i].rgbRed;
	}


	// Ecriture du FileHeader sur disque
	if(!WriteSaveBuffer(hFile, &BmHeader, sizeof(BITMAPFILEHEADER)))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Ecriture du CoreHeader sur disque
	if(!WriteSaveBuffer(hFile, BmCore, sizeof(BITMAPCOREHEADER)+nColors*sizeof(RGBTRIPLE)))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Ecriture de l'image sur disque
	if(!WriteSaveBuffer(hFile, (BYTE*)BmInfo+sizeof(BITMAPINFOHEADER)+nColors*sizeof(RGBQUAD),
		nScanWidth * BmInfo->bmiHeader.biHeight))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Terminé sans encombre
	GlobalUnlock(m_hDib);
	return TRUE;
}

// Sauvegarde d'un bitmap au format PCX
BOOL CImage::SavePCX(HANDLE hFile)
{
	// Adresse du Bitmap en cours
	LPBITMAPINFO BmInfo=(LPBITMAPINFO)GlobalLock(m_hDib);			
	int nColors = BmInfo->bmiHeader.biClrUsed ? BmInfo->bmiHeader.biClrUsed
		: 0x1FF & (1 << BmInfo->bmiHeader.biBitCount);
	int nScanWidth = WIDTHBYTES(BmInfo->bmiHeader.biWidth * BmInfo->bmiHeader.biBitCount);

	// Remplissage et sauvegarde du header
	TypeHeaderPCX EntetePCX;
	memset(&EntetePCX, 0, sizeof(TypeHeaderPCX));
	EntetePCX.yGriffe=0x0A;
	EntetePCX.yVersion=5;
	EntetePCX.yCodage=1;
	switch(BmInfo->bmiHeader.biBitCount)
	{
		case 1:
			EntetePCX.yBits=EntetePCX.cNbrPlanes=1;
			EntetePCX.wBytesPerLine =
				((((BmInfo->bmiHeader.biWidth
				* BmInfo->bmiHeader.biBitCount) + 15) >>4 ) << 1);
			break;
		case 4:
			EntetePCX.yBits=1;
			EntetePCX.cNbrPlanes=4;
			EntetePCX.wBytesPerLine = (WORD)((BmInfo->bmiHeader.biWidth+1)>>3);
			break;
		case 8:
			EntetePCX.yBits=8;
			EntetePCX.cNbrPlanes=1;
			EntetePCX.wBytesPerLine =
				((((BmInfo->bmiHeader.biWidth
				* BmInfo->bmiHeader.biBitCount) + 15) >>4 ) << 1);
			break;
		case 24:
			EntetePCX.yBits=8;
			EntetePCX.cNbrPlanes=3;
			EntetePCX.wBytesPerLine = (WORD)BmInfo->bmiHeader.biWidth
				+(BmInfo->bmiHeader.biWidth & 1 ? 1 : 0);
			break;
	}
	EntetePCX.x2 = BmInfo->bmiHeader.biWidth-1;
	EntetePCX.y2 = BmInfo->bmiHeader.biHeight-1;
	EntetePCX.wHres = (WORD)(BmInfo->bmiHeader.biXPelsPerMeter*0.0254);
	EntetePCX.wVres = (WORD)(BmInfo->bmiHeader.biYPelsPerMeter*0.0254);
	EntetePCX.wShres = 640;
	EntetePCX.wSvres = 480;
	EntetePCX.wTypePalette =(m_nTypeImage==IMG_TYPE_NG256
		|| m_nTypeImage==IMG_TYPE_NG16 ? 2 : 1);

	// Pour les palettes 2 et 16 couleurs -> Palette dans entête
	if(nColors<=16)
	{
		for(int i=0; i<nColors; i++)
		{
			EntetePCX.yPalette[i*3] = BmInfo->bmiColors[i].rgbRed;
			EntetePCX.yPalette[i*3+1] = BmInfo->bmiColors[i].rgbGreen;
			EntetePCX.yPalette[i*3+2] = BmInfo->bmiColors[i].rgbBlue;
		}
	}

	// Ecriture du Header sur disque
	if(!WriteSaveBuffer(hFile, &EntetePCX, sizeof(TypeHeaderPCX)))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Détermination de la position des bits (source)
	BYTE* lpBits=(BYTE*)BmInfo+sizeof(BITMAPINFOHEADER)
		+nColors*sizeof(RGBQUAD);

	// Réservation de la mémoire pour une ligne
	BYTE* lpLineBits=(BYTE*)malloc((size_t)EntetePCX.wBytesPerLine*
		(size_t)EntetePCX.cNbrPlanes+16L);
	if(!lpLineBits)
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Encodage succéssif des lignes
	for(int y=BmInfo->bmiHeader.biHeight-1; y>=0; y--)
	{
		memset(lpLineBits, 0, nScanWidth);
		// Copie des bits de donnée en fonction du nombre de bits/pixel
		if(BmInfo->bmiHeader.biBitCount == 1
				|| BmInfo->bmiHeader.biBitCount == 8)
			CopyMemory(lpLineBits, lpBits+(y*nScanWidth), nScanWidth);

		if(BmInfo->bmiHeader.biBitCount == 4)
		{
			for(int nLayer=0; nLayer<4; nLayer++)
			{
				int x=0;
				for(int i=0; i<EntetePCX.wBytesPerLine; i++)
				{
					for(int j=0; j<8 ; j++)
						if(x+j < BmInfo->bmiHeader.biWidth)
							lpLineBits[i+EntetePCX.wBytesPerLine*nLayer] |=
								((((BYTE)GetPixel(x+j, y, (LPBITMAPINFOHEADER)BmInfo)
									>> nLayer) & 1) << (7-j));
					x+=8;
				}
			}
		}

		if(BmInfo->bmiHeader.biBitCount == 24)
		{
			BYTE* lpTempLine = lpLineBits;
			BYTE* lpSourceBits = lpBits+(y*nScanWidth);
			for(int nLayer=2; nLayer>=0; nLayer--)
				for(int i=0; i<EntetePCX.wBytesPerLine; i++)
					*(lpTempLine++)=lpSourceBits[i*3+nLayer];
		}

		// Encodage de la ligne
		BYTE buffer[4];
		BYTE first;
		int nCount;
		for(int nLayer=0; nLayer<EntetePCX.cNbrPlanes; nLayer++)
		{
			for(int i=0; i<EntetePCX.wBytesPerLine; )
			{
				first=lpLineBits[i+EntetePCX.wBytesPerLine*nLayer];
				nCount=1;
				while(lpLineBits[++i+EntetePCX.wBytesPerLine*nLayer]==first
						&& i<EntetePCX.wBytesPerLine
						&& nCount<63)
					nCount++;
				if(nCount == 1 && first<0xC0)
				{
					buffer[0]=first;
					if(!WriteSaveBuffer(hFile, &buffer))
					{
						GlobalUnlock(m_hDib);
						free(lpLineBits);
						return FALSE;
					}
				}
				else
				{
					buffer[0]=nCount+0xC0;
					buffer[1]=first;
					if(!WriteSaveBuffer(hFile, &buffer, 2L))
					{
						GlobalUnlock(m_hDib);
						free(lpLineBits);
						return FALSE;
					}
				}
			}
		}
	}

	// Libération de la mémoire de la ligne
	free((void*)lpLineBits);
	
	// Remplissage de la palette en 256 couleurs (en fin de fichier)
	if(nColors==256)
	{
		BYTE cPalette[768];
		cPalette[0]=12;
		WriteSaveBuffer(hFile, &cPalette);
		for(int i=0; i<256; i++)
		{
			cPalette[i*3] = BmInfo->bmiColors[i].rgbRed;
			cPalette[i*3+1] = BmInfo->bmiColors[i].rgbGreen;
			cPalette[i*3+2] = BmInfo->bmiColors[i].rgbBlue;
		}
		// Ecriture des octets sur disque
		if(!WriteSaveBuffer(hFile, &cPalette, 768L))
		{
			GlobalUnlock(m_hDib);
			return FALSE;
		}
	}

	// Terminé avec succès
	GlobalUnlock(m_hDib);
	return TRUE;
}

// Sauvegarde du BMP sous format compressé RLE (8 bits seulement)
//  !! les images en 4 bits sont codées en RLE 8
BOOL CImage::SaveRLE(HANDLE hFile)
{
	if(GetBPP() != 8 && GetBPP() != 4)
		return FALSE;

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);			
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);
	int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);

	// Header avec marque de signature
	BITMAPFILEHEADER BmHeader;
	memset(&BmHeader, 0, sizeof(BITMAPFILEHEADER));
	BmHeader.bfType=FORMAT_BMP;
	BmHeader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)
		+nColors*sizeof(RGBQUAD);
	BmHeader.bfSize=BmHeader.bfOffBits+nScanWidth*BmInfo->biHeight;
	
	// Ecriture du Header sur disque
	if(!WriteSaveBuffer(hFile, &BmHeader, sizeof(BITMAPFILEHEADER)))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}
	
	// On change le marqueur de compression
	BmInfo->biCompression = BmInfo->biBitCount==8 ? BI_RLE8 : BI_RLE4;

	// Ecriture du BitmapInfo sur disque sur disque + couleurs
	if(!WriteSaveBuffer(hFile, BmInfo, sizeof(BITMAPINFOHEADER)
		+nColors*sizeof(RGBQUAD)))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// On Remet le marqueur de compression à BI_RGB
	BmInfo->biCompression = BI_RGB;
	
	// Détermination de la position des bits (source)
	BYTE* lpBits=(BYTE*)BmInfo+sizeof(BITMAPINFOHEADER)
		+nColors*sizeof(RGBQUAD);

	BYTE buffer[4];
	BYTE first;
	BYTE first2;
	int nCount;

	// Encodage des lignes
	for(int y=0; y<BmInfo->biHeight; y++)
	{
		if(BmInfo->biBitCount==8) // en RLE8
		{
			for(int x=0; x<BmInfo->biWidth; )
			{
				first=lpBits[x];
				nCount=1;
				while(lpBits[++x]==first && x<BmInfo->biWidth && nCount<0xFE)
					nCount++;

				if(nCount == 1)
				{
					int nDummy = 1;
					while(x+nDummy<=BmInfo->biWidth
							&& lpBits[x+nDummy]!=lpBits[x+nDummy-1]
							&& nDummy<0xFE)
						nDummy++;
					x--;
					if(nDummy<3)
					{
						for(int i=0; i<nDummy; i++)
						{
							buffer[0]=1;
							buffer[1]=lpBits[x++];
							if(!WriteSaveBuffer(hFile, &buffer, 2L))
							{
								GlobalUnlock(m_hDib);
								return FALSE;
							}
						}
					}
					else
					{
						buffer[0]=0;
						buffer[1]=(BYTE)nDummy;
						if(!WriteSaveBuffer(hFile, &buffer, 2L))
						{
							GlobalUnlock(m_hDib);
							return FALSE;
						}
						for(int i=0; i<nDummy; i++)
						{
							if(!WriteSaveBuffer(hFile, &lpBits[x++]))
							{
								GlobalUnlock(m_hDib);
								return FALSE;
							}
						}
						if(nDummy & 1)
						{
							buffer[0]=0;
							WriteSaveBuffer(hFile, &buffer);
						}
					}
				}
				else
				{
					buffer[0]=nCount;
					buffer[1]=first;
					if(!WriteSaveBuffer(hFile, &buffer, 2L))
					{
						GlobalUnlock(m_hDib);
						return FALSE;
					}
				}
			}
		}
		else // en RLE4
		{
			int nFirstX;
			for(int x=0; x<BmInfo->biWidth; )
			{
				nCount=2;
				nFirstX = x;
				first=(BYTE)GetPixel(x++, y, BmInfo);
				if(x++<BmInfo->biWidth)
				{
					--x;
					first2=(BYTE)GetPixel(x, y, BmInfo);
					while(x++<BmInfo->biWidth && nCount<0xFC)
					{
						if(!(nCount & 1))
						{
							BYTE cPixCol = NULL;
							if(x<BmInfo->biWidth)
								cPixCol = (BYTE)GetPixel(x, y, BmInfo);
							if(cPixCol!=first)
								break;
							else
								nCount++;
						}
						else
						{
							BYTE cPixCol = NULL;
							if(x<BmInfo->biWidth)
								cPixCol = (BYTE)GetPixel(x, y, BmInfo);
							if(cPixCol!=first2)
								break;
							else
								nCount++;
						}
					}
				}

				if(nCount < 4)
				{
					int nDummy = 0;
					x-=nCount;
					while(x+nDummy<BmInfo->biWidth && nDummy<0xFC)
					{
						BOOL bFlag1=FALSE;
						BYTE cPixel1 = 0;
						BYTE cPixel2 = 0;
						if(x+nDummy+2 < BmInfo->biWidth)
						{
							cPixel1 = (BYTE)GetPixel(x+nDummy, y, BmInfo);
							cPixel2 = (BYTE)GetPixel(x+nDummy+2, y, BmInfo);
							if(cPixel1 == cPixel2)
								bFlag1=TRUE;
						}
						BOOL bFlag2=FALSE;
						cPixel1 = 0;
						cPixel2 = 0;
						if(x+nDummy+3 < BmInfo->biWidth)
						{
							cPixel1 = (BYTE)GetPixel(x+nDummy+1, y, BmInfo);
							cPixel2 = (BYTE)GetPixel(x+nDummy+3, y, BmInfo);
							if(cPixel1 == cPixel2)
								bFlag2=TRUE;
						}
						if(bFlag1 && bFlag2)
							break;
						else
							nDummy+=2;
					}
					if(x+nDummy>=BmInfo->biWidth)
						nDummy=BmInfo->biWidth-x;
					if(nDummy<3)
					{
						buffer[0]=nDummy;
						if(x<BmInfo->biWidth)
							buffer[1]=(BYTE)GetPixel(x++, y, BmInfo)<<4;
						else
							x++;
						if(x<BmInfo->biWidth)
							buffer[1] |= (BYTE)GetPixel(x++, y, BmInfo);
						else
							x++;				
						if(!WriteSaveBuffer(hFile, &buffer, 2L))
						{
							GlobalUnlock(m_hDib);
							return FALSE;
						}
					}
					else
					{
						buffer[0]=0;
						buffer[1]=(BYTE)nDummy;
						if(!WriteSaveBuffer(hFile, &buffer, 2L))
						{
							GlobalUnlock(m_hDib);
							return FALSE;
						}
						for(int i=0; i<nDummy; i+=2)
						{
							if(x<BmInfo->biWidth)
								buffer[0]=(BYTE)GetPixel(x++, y, BmInfo)<<4;
							else
								x++;
							if(x<BmInfo->biWidth)
								buffer[0] |= (BYTE)GetPixel(x++, y, BmInfo);
							else
								x++;
							if(!WriteSaveBuffer(hFile, &buffer))
							{
								GlobalUnlock(m_hDib);
								return FALSE;
							}
						}
						if((nDummy+1) & 2)
						{
							buffer[0]=0;
							WriteSaveBuffer(hFile, &buffer);
						}
					}
				}
				else
				{
					if(nFirstX+nCount>=BmInfo->biWidth)
						nCount=BmInfo->biWidth-nFirstX;
					buffer[0]=nCount;
					buffer[1]=first<<4 | first2;
					if(!WriteSaveBuffer(hFile, &buffer, 2L))
					{
						GlobalUnlock(m_hDib);
						return FALSE;
					}
				}
			}
		}
		// Marque de fin de ligne
		buffer[0]=buffer[1]=0;
		if(!WriteSaveBuffer(hFile, &buffer, 2L))
		{
			GlobalUnlock(m_hDib);
			return FALSE;
		}
		lpBits+=nScanWidth;
	}

	// Marque de fin de bitmap
	buffer[0]=0;
	buffer[1]=1;
	if(!WriteSaveBuffer(hFile, &buffer, 2L))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Terminé sans encombre
	GlobalUnlock(m_hDib);
	return TRUE;
}

// Sauvegarde d'une image au format TGA, compressé en RLE ou non
BOOL CImage::SaveTGA(HANDLE hFile, int nCompression)
{
	// Les images TGA sont en 8 ou 24 bits/pixels
	if(GetBPP() < 8)
		return FALSE;

	// Vérifie que la compression demandée est possible
	if(nCompression != IMG_COMPRESS_RLE
			&& nCompression != IMG_COMPRESS_NONE)
		return FALSE;
	BYTE buffer[4];

	// Adresse du Bitmap en cours
	LPBITMAPINFO BmInfo=(LPBITMAPINFO)GlobalLock(m_hDib);			
	int nColors = BmInfo->bmiHeader.biClrUsed ? BmInfo->bmiHeader.biClrUsed
		: 0x1FF & (1 << BmInfo->bmiHeader.biBitCount);
	int nScanWidth = WIDTHBYTES(BmInfo->bmiHeader.biWidth * BmInfo->bmiHeader.biBitCount);

	// Remplissage et sauvegarde du header
	TypeHeaderTGA EnteteTGA;
	memset(&EnteteTGA, 0, sizeof(TypeHeaderTGA));
	EnteteTGA.ColorMapType = nColors ? 1 : 0;
	if(nCompression == IMG_COMPRESS_NONE)
		EnteteTGA.ImageType = nColors ? 1 : 2;
	if(nCompression == IMG_COMPRESS_RLE)
		EnteteTGA.ImageType = nColors ? 9 : 10;
	EnteteTGA.CMS_NbrColor = nColors;
	EnteteTGA.CMS_MapBPP = nColors ? 24 : 0;
	EnteteTGA.IS_Width = (WORD)BmInfo->bmiHeader.biWidth;
	EnteteTGA.IS_Height = (WORD)BmInfo->bmiHeader.biHeight;
	EnteteTGA.IS_BPP = (BYTE)BmInfo->bmiHeader.biBitCount;

	// Ecriture du Header sur disque
	if(!WriteSaveBuffer(hFile, &EnteteTGA, sizeof(TypeHeaderTGA)))
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	// Ecriture de la palette
	for(int i=0; i<nColors; i++)
	{
		buffer[0] = BmInfo->bmiColors[i].rgbBlue;
		buffer[1] = BmInfo->bmiColors[i].rgbGreen;
		buffer[2] = BmInfo->bmiColors[i].rgbRed;
		if(!WriteSaveBuffer(hFile, &buffer, 3))
		{
			GlobalUnlock(m_hDib);
			return FALSE;
		}
	}

	// Détermination de la position des bits (source)
	BYTE* lpBits=(BYTE*)BmInfo+sizeof(BITMAPINFOHEADER)
		+nColors*sizeof(RGBQUAD);

	// Sauvegarde des données non compressées
	if(nCompression == IMG_COMPRESS_NONE)
	{
		for(int y=0; y<BmInfo->bmiHeader.biHeight; y++)
		{
			// Ecriture directement de la ligne, en donnant la bonne taille
			if(!WriteSaveBuffer(hFile, lpBits, BmInfo->bmiHeader.biWidth * (BmInfo->bmiHeader.biBitCount>>3)))
			{
				GlobalUnlock(m_hDib);
				return FALSE;
			}
			lpBits+=nScanWidth;
		}
	}

	// Sauvegarde des données compressées en RLE
	if(nCompression == IMG_COMPRESS_RLE)
	{
		DWORD first;
		int nCount;
		for(int y=0; y<BmInfo->bmiHeader.biHeight; y++)
		{
			for(int x=0; x<BmInfo->bmiHeader.biWidth; )
			{
				nCount = 1;
				first = GetPixel(Min(x++,BmInfo->bmiHeader.biWidth-1),
					Min(y,BmInfo->bmiHeader.biHeight-1),
					(LPBITMAPINFOHEADER)BmInfo);
				while(GetPixel(Min(x++,BmInfo->bmiHeader.biWidth-1),
							Min(y,BmInfo->bmiHeader.biHeight-1),
							(LPBITMAPINFOHEADER)BmInfo)==first
						&& x<=BmInfo->bmiHeader.biWidth
						&& nCount<=0x7F)
					nCount++;

				x--;

				// Pixels différents codés en RLE
				if(nCount==1)
				{
					while(GetPixel(Min(x-1,BmInfo->bmiHeader.biWidth-1),
							Min(y,BmInfo->bmiHeader.biHeight-1),
							(LPBITMAPINFOHEADER)BmInfo)
							!=GetPixel(Min(x++,BmInfo->bmiHeader.biWidth-1),
							Min(y,BmInfo->bmiHeader.biHeight-1),
							(LPBITMAPINFOHEADER)BmInfo)
							&& x<BmInfo->bmiHeader.biWidth
							&& nCount<=0x7F)
						nCount++;
					x-=nCount+1;
					buffer[0]=(BYTE)(nCount-1);
					WriteSaveBuffer(hFile, &buffer);
					for(int i=0; i<nCount; i++)
					{
						int nLen;
						first=GetPixel(Min(x++,BmInfo->bmiHeader.biWidth-1),
							Min(y,BmInfo->bmiHeader.biHeight-1), (LPBITMAPINFOHEADER)BmInfo);
						switch(BmInfo->bmiHeader.biBitCount)
						{
							case 8:
								buffer[0]=(BYTE)(first&0xFF);
								nLen=1;
								break;
							case 24:
								buffer[0]=(BYTE)((first>>16)&0xFF);
								buffer[1]=(BYTE)((first>>8)&0xFF);
								buffer[2]=(BYTE)(first&0xFF);
								nLen=3;
								break;
						}
						if(!WriteSaveBuffer(hFile, &buffer, nLen))
						{
							GlobalUnlock(m_hDib);
							return FALSE;
						}
					}
				}
				else
				{
					// Pixels identiques codés en RLE
					int nLen;
					buffer[0]=(BYTE)(nCount-1) | 0x80;
					switch(BmInfo->bmiHeader.biBitCount)
					{
						case 8:
							buffer[1]=(BYTE)(first&0xFF);
							nLen=2;
							break;
						case 24:
							buffer[1]=(BYTE)((first>>16)&0xFF);
							buffer[2]=(BYTE)((first>>8)&0xFF);
							buffer[3]=(BYTE)(first&0xFF);
							nLen=4;
							break;
					}
					if(!WriteSaveBuffer(hFile, &buffer, nLen))
					{
						GlobalUnlock(m_hDib);
						return FALSE;
					}
				}
			}
		}
	}

	// Terminé avec succès
	GlobalUnlock(m_hDib);
	return TRUE;
}

// Sauvegarde d'une image au format GIF
BOOL CImage::SaveGIF(HANDLE hFile)
{
	if(!m_hDib)
		return FALSE;
	if(GetBPP() > 8)  // Le format GIF ne supporte pas plus de 256 couleurs
		return FALSE;

	LPBITMAPINFO BmInfo = (LPBITMAPINFO)GlobalLock(m_hDib);

	// Ecriture Header Global
	TypeHeaderGIFGlobal HeaderGlobal;
	memset(&HeaderGlobal, 0, sizeof(HeaderGlobal));
	memcpy(&HeaderGlobal, "GIF87a", 6);
	HeaderGlobal.wScreenWidth = (WORD)BmInfo->bmiHeader.biWidth;
	HeaderGlobal.wScreenHeight = (WORD)BmInfo->bmiHeader.biHeight;
	HeaderGlobal.cFlags = 0x80 | ((BmInfo->bmiHeader.biBitCount-1)<<4)
		| (BmInfo->bmiHeader.biBitCount-1);
	WriteSaveBuffer(hFile, &HeaderGlobal, sizeof(HeaderGlobal));

	// Ecriture de la palette
	int nGifColors = 0x1FF & (1 << BmInfo->bmiHeader.biBitCount);
	int nColors = BmInfo->bmiHeader.biClrUsed ? BmInfo->bmiHeader.biClrUsed
		: 0x1FF & (1 << BmInfo->bmiHeader.biBitCount);
	for(int i=0; i<nGifColors; i++)
	{
		if(i<nColors)
		{
			WriteSaveBuffer(hFile, &BmInfo->bmiColors[i].rgbRed);
			WriteSaveBuffer(hFile, &BmInfo->bmiColors[i].rgbGreen);
			WriteSaveBuffer(hFile, &BmInfo->bmiColors[i].rgbBlue);
		}
		else
		{
			BYTE c[3] = {0, 0, 0};
			WriteSaveBuffer(hFile, &c, 3);
		}
	}

	// Si couleur transparente -> Block transparent
	if(m_dwTransparentColor & 0x80000000L)
	{
		BYTE Block[8];
		memset(&Block, 0, sizeof(Block));
		Block[0] = '!';
		Block[1] = 0xF9;
		Block[2] = 4;
		Block[3] = 1;
		Block[6] = (BYTE)(m_dwTransparentColor & 0x7FFFFFFFL);
		WriteSaveBuffer(hFile, &Block, 8);
	}

	// Ecriture entête local
	TypeHeaderGIFLocal HeaderLocal;
	memset(&HeaderLocal, 0, sizeof(HeaderLocal));
	HeaderLocal.cId = ',';
	HeaderLocal.wWidth = (WORD)BmInfo->bmiHeader.biWidth;
	HeaderLocal.wHeight = (WORD)BmInfo->bmiHeader.biHeight;
	WriteSaveBuffer(hFile, &HeaderLocal, sizeof(HeaderLocal));

	// Encodage LZW et sortie de l'image
	BYTE* lpBits = (BYTE*)BmInfo+BmInfo->bmiHeader.biSize+nColors*sizeof(RGBQUAD);
	int nScanWidth = WIDTHBYTES(BmInfo->bmiHeader.biWidth * BmInfo->bmiHeader.biBitCount);

	// Macro pour sortie du code
	#define GIF_OUTPUT_CODE(nCode) \
	{ \
		if(nBits>0) \
			lDatum |= ((long)nCode << nBits); \
		else \
			lDatum=(long)nCode; \
		nBits += nNumberBits; \
		while(nBits>=8) \
		{ \
			pPacket[nByteCount++]=(BYTE)(lDatum & 0xFF); \
			if(nByteCount>=254) \
			{ \
				BYTE c = (BYTE)nByteCount; \
				WriteSaveBuffer(hFile, &c); \
				WriteSaveBuffer(hFile, pPacket, nByteCount); \
				nByteCount=0; \
			} \
			lDatum>>=8; \
			nBits-=8; \
		} \
		if(nFreeCode>nMaxCode) \
		{ \
			nNumberBits++; \
			if(nNumberBits == MAX_GIF_BITS) \
				nMaxCode = (1<<MAX_GIF_BITS); \
			else \
				nMaxCode = ((1<<(nNumberBits))-1); \
		} \
	}
	// Fin de macro de sortie de code

	// Allocate encoder tables.
	BYTE* pPacket=(BYTE*)malloc(256*sizeof(BYTE));
	short* pHashCode=(short*)malloc(MAX_LZW_HASH_TABLE*sizeof(short));
	short* pHashPrefix=(short*)malloc(MAX_LZW_HASH_TABLE*sizeof(short));
	BYTE* pHashSuffix=(BYTE*)malloc(MAX_LZW_HASH_TABLE*sizeof(BYTE));
	if(!pPacket || !pHashCode || !pHashPrefix || !pHashSuffix)
	{
		GlobalUnlock(m_hDib);
		free(pPacket);
		free(pHashCode);
		free(pHashSuffix);
		free(pHashPrefix);
		return FALSE;
	}

	//Initialize GIF encoder.
	int nDataSize = max(BmInfo->bmiHeader.biBitCount, 2)+1;
	int nNumberBits = nDataSize;
	short nMaxCode = ((1 << (nNumberBits))-1);
	short nClearCode=((short)(1<<(nDataSize-1)));
	short nEndOfInformationCode = nClearCode+1;
	short nFreeCode = nClearCode+2;
	int nByteCount = 0;
	long lDatum = 0;
	int nBits = 0;
	for(i=0; i<MAX_LZW_HASH_TABLE; i++)
		pHashCode[i]=0;
	{
		BYTE c = (BYTE)nDataSize-1;
		WriteSaveBuffer(hFile, &c);
	}

	// Encode pixels.
	short nWaitingCode = (short)(GetPixel(0, BmInfo->bmiHeader.biHeight-1,
		(LPBITMAPINFOHEADER)BmInfo, nColors, nScanWidth, lpBits) & 0xFF);
	int nDisplacement;
	for(int y=BmInfo->bmiHeader.biHeight-1; y>=0; y--)
	{
		for(int x=((y==BmInfo->bmiHeader.biHeight-1)?1:0); x<BmInfo->bmiHeader.biWidth; x++)
		{
			// Probe hash table.
			short nIndex = (short)(GetPixel(x, y, (LPBITMAPINFOHEADER)BmInfo, nColors,
				nScanWidth, lpBits) & 0xFF);
			int k = (int)((int) nIndex << (MAX_GIF_BITS-8)) + nWaitingCode;
			if(k >= MAX_LZW_HASH_TABLE)
				k -= MAX_LZW_HASH_TABLE;

			// Encodage LZW
			if(pHashCode[k] > 0)
			{
				if((pHashPrefix[k]==nWaitingCode) && (pHashSuffix[k]==nIndex))
				{
					nWaitingCode = pHashCode[k];
					continue;
				}
				if(!k)
					nDisplacement = 1;
				else
					nDisplacement = MAX_LZW_HASH_TABLE-k;
				BOOL bNextPixel = FALSE;
				for( ; ; )
				{
					k -= nDisplacement;
					if(k < 0)
						k += MAX_LZW_HASH_TABLE;
					if(!pHashCode[k])
						break;
					if((pHashPrefix[k] == nWaitingCode) && (pHashSuffix[k] == nIndex))
					{
						nWaitingCode = pHashCode[k];
						bNextPixel = TRUE;
						break;
					}
				}
				if(bNextPixel)
					continue;
			}
			// Fin encodage LZW

			GIF_OUTPUT_CODE(nWaitingCode);
			if(nFreeCode < (1 << MAX_GIF_BITS))
			{
				pHashCode[k] = nFreeCode++;
				pHashPrefix[k] = nWaitingCode;
				pHashSuffix[k] = (BYTE)nIndex;
			}
			else
			{
				// Fill the hash table with empty entries.
				for(k=0; k<MAX_LZW_HASH_TABLE; k++)
					pHashCode[k]=0;
				// Reset compressor and issue a clear code.
				nFreeCode = nClearCode+2;
				GIF_OUTPUT_CODE(nClearCode);
				nNumberBits = nDataSize;
				nMaxCode = ((1 << (nNumberBits))-1);
			}
			nWaitingCode = nIndex;
		}
	}
	// Flush out the buffered code.
	GIF_OUTPUT_CODE(nWaitingCode);
	GIF_OUTPUT_CODE(nEndOfInformationCode);
	if(nBits > 0)
	{
		// Add a character to current packet.
		pPacket[nByteCount++]=(BYTE)(lDatum & 0xff);
		if(nByteCount >= 254)
		{
			BYTE c = (BYTE)nByteCount;
			WriteSaveBuffer(hFile, &c);
			WriteSaveBuffer(hFile, pPacket, nByteCount);
			nByteCount=0;
		}
	}
	// Flush accumulated data.
	if(nByteCount > 0)
	{
		BYTE c = (BYTE)nByteCount;
		WriteSaveBuffer(hFile, &c);
		WriteSaveBuffer(hFile, pPacket, nByteCount);
	}

	// Ecriture du trailer en fin de fichier
	BYTE cTrailer[2] = {0x00, 0x3B};
	WriteSaveBuffer(hFile, &cTrailer, 2);

	// Free encoder memory.
	GlobalUnlock(m_hDib);
	free(pPacket);
	free(pHashCode);
	free(pHashSuffix);
	free(pHashPrefix);

	// On supprime la macro de sortie de code
	#undef GIF_OUTPUT_CODE

	return TRUE;
}

#if defined(CIMAGE_USE_JPEG)
// Sauvegarde d'une image au format JPEG
BOOL CImage::SaveJPEG(HANDLE hFile, int nQuality)
{
	if(!m_hDib)
		return FALSE;

	BOOL bGrayScale = FALSE;

	// Vérification qu'il s'agit bien d'une image en 256 NG ou 24 bits
	LPBITMAPINFO bi = (LPBITMAPINFO)GlobalLock(m_hDib);

	if(bi->bmiHeader.biBitCount<8)
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	int nColors = bi->bmiHeader.biClrUsed ? bi->bmiHeader.biClrUsed : 0x1FF & (1 << bi->bmiHeader.biBitCount);
	if(bi->bmiHeader.biBitCount!=24)
	{
		bGrayScale = TRUE;
		for(int i=0; i<nColors; i++)
			if(bi->bmiColors[i].rgbRed!=bi->bmiColors[i].rgbGreen
				|| bi->bmiColors[i].rgbRed !=bi->bmiColors[i].rgbBlue)
			{
				// Image en couleur avec palettes -> pas supporté
				GlobalUnlock(m_hDib);
				return FALSE;
			}
	}

	int nLineSize = bi->bmiHeader.biWidth*(bGrayScale?1:3);
	BYTE* pScanLine = (BYTE*)malloc(nLineSize);
	if(!pScanLine)
	{
		GlobalUnlock(m_hDib);
		return FALSE;
	}

	jpeg_compress_struct cinfo;
	jpeg_error_mgr jerr;

	cinfo.err = jpeg_std_error(&jerr);
	jerr.error_exit = CImageJpegErrorExit;  // Register custom error manager.

	typedef struct
	{
		void* pBuffer;
		HANDLE hFile;
	} JPegData;

	JPegData JData;
	JData.pBuffer = m_LoadBuffer;
	JData.hFile = hFile;

	try
	{
		jpeg_create_compress(&cinfo);

		// Specify data destination
		jpeg_destination_mgr dest;
		dest.next_output_byte = (JOCTET *)m_LoadBuffer;
		dest.free_in_buffer = SIZE_SAVE_BUFFER-4;
		dest.init_destination = CImageJpegInitDest;
		dest.empty_output_buffer = CImageJpegEmptyOutputBuffer;
		dest.term_destination = CImageJpegTermDest;
		cinfo.dest = &dest;
		cinfo.client_data = &JData;

		// Spécifications de l'image
		cinfo.image_width = bi->bmiHeader.biWidth;
		cinfo.image_height = bi->bmiHeader.biHeight;
		cinfo.input_components = bGrayScale ? 1 : 3;
		cinfo.in_color_space = bGrayScale ? JCS_GRAYSCALE : JCS_RGB;
		jpeg_set_defaults(&cinfo);

		// Affinage des paramètres de sortie
		jpeg_set_quality(&cinfo, nQuality, TRUE);
		cinfo.dct_method = JDCT_ISLOW;
		cinfo.optimize_coding = TRUE;
		cinfo.density_unit = 1;
		cinfo.X_density = (int)PPM2DPI(bi->bmiHeader.biXPelsPerMeter);
		cinfo.Y_density = (int)PPM2DPI(bi->bmiHeader.biYPelsPerMeter);

		// Start compressor
		jpeg_start_compress(&cinfo, TRUE);

		// Ecriture successive des lignes
		int nScanWidth = WIDTHBYTES(bi->bmiHeader.biWidth * bi->bmiHeader.biBitCount);
		BYTE* pSrcLine = (BYTE*)bi+bi->bmiHeader.biSize+nColors*sizeof(RGBQUAD)
			+nScanWidth*(bi->bmiHeader.biHeight-1);
		while(cinfo.next_scanline < cinfo.image_height)
		{
			memcpy(pScanLine, pSrcLine, nLineSize);
			if(bGrayScale)
				for(int i=0; i<nLineSize; i++)
					pScanLine[i] = bi->bmiColors[pScanLine[i]].rgbRed;
			else
			{
				BYTE cDummy;
				for(int i=0; i<nLineSize; i+=3)
				{
					cDummy = *(pScanLine+i);
					*(pScanLine+i) = *(pScanLine+i+2);
					*(pScanLine+i+2) = cDummy;
				}
			}
			jpeg_write_scanlines(&cinfo, &pScanLine, 1);
			pSrcLine -= nScanWidth;
		}

		// Finish compression
		jpeg_finish_compress(&cinfo);

		// Release JPEG decompression object
		jpeg_destroy_compress(&cinfo);

		free(pScanLine);
		GlobalUnlock(m_hDib);

		return TRUE;
	}
	catch(...)
	{
		jpeg_abort_compress(&cinfo);
		GlobalUnlock(m_hDib);
		free(pScanLine);
		return FALSE;
	}
}

// Init de la destination JPEG -> ne fait rien
METHODDEF(void) CImageJpegInitDest(j_compress_ptr cinfo)
{
}

// Ecrit le buffer de sauvegarde sur disque
METHODDEF(boolean) CImageJpegEmptyOutputBuffer(j_compress_ptr cinfo)
{
	typedef struct
	{
		void* pBuffer;
		HANDLE hFile;
	} JPegData;
	DWORD dwByteWrite;

	JPegData* JData = (JPegData*)cinfo->client_data;
	WriteFile(JData->hFile, JData->pBuffer, SIZE_SAVE_BUFFER-4,
		&dwByteWrite, NULL);
	memset(JData->pBuffer, 0, SIZE_SAVE_BUFFER);
	cinfo->dest->next_output_byte = (JOCTET *)JData->pBuffer;
	cinfo->dest->free_in_buffer = SIZE_SAVE_BUFFER-4;

	return TRUE;
}

// Termine source ou destination JPeg -> ne fait rien
METHODDEF(void) CImageJpegTermDest(j_compress_ptr cinfo)
{
	typedef struct
	{
		void* pBuffer;
		HANDLE hFile;
	} JPegData;
	DWORD dwByteWrite;

	JPegData* JData = (JPegData*)cinfo->client_data;
	int nSize = (int)((BYTE*)cinfo->dest->next_output_byte - (BYTE*)JData->pBuffer);
	if(nSize<1 || nSize>SIZE_SAVE_BUFFER-4)
		return;
	WriteFile(JData->hFile, JData->pBuffer, nSize, &dwByteWrite, NULL);
}
#endif  // CIMAGE_USE_JPEG

#if defined(CIMAGE_USE_TIFF)
// Sauvegarde d'une image au format TIFF
BOOL CImage::SaveTIFF(HANDLE hFile, LPCTSTR szFileName, int nCompression)
{
	if(!m_hDib)
		return FALSE;

	// Les Handlers sont nuls car la classe n'affiche rien.
	TIFFSetErrorHandler(NULL);
	TIFFSetWarningHandler(NULL);

	LPBITMAPINFO bi = (LPBITMAPINFO)GlobalLock(m_hDib);

	// Ouverture fichier
	TIFF* tiff = TIFFFdOpen((int)hFile, szFileName, "wb");
	if(!tiff)
		return FALSE;

	// Indication des paramètres du fichier
	TIFFSetField(tiff, TIFFTAG_IMAGEWIDTH, (DWORD)bi->bmiHeader.biWidth);
	TIFFSetField(tiff, TIFFTAG_IMAGELENGTH, (DWORD)bi->bmiHeader.biHeight);
	TIFFSetField(tiff, TIFFTAG_RESOLUTIONUNIT, RESUNIT_INCH);
	TIFFSetField(tiff, TIFFTAG_XRESOLUTION, (float)PPM2DPI(bi->bmiHeader.biXPelsPerMeter));
	TIFFSetField(tiff, TIFFTAG_YRESOLUTION, (float)PPM2DPI(bi->bmiHeader.biYPelsPerMeter));
	TIFFSetField(tiff, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);

	int nColors = bi->bmiHeader.biClrUsed ? bi->bmiHeader.biClrUsed : 0x1FF & (1 << bi->bmiHeader.biBitCount);
	short nPhotometric;
	if(bi->bmiHeader.biBitCount<=8)
	{
		TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, bi->bmiHeader.biBitCount);
		TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, 1);
		if(bi->bmiHeader.biBitCount==4)
			nPhotometric = PHOTOMETRIC_PALETTE;
		if(bi->bmiHeader.biBitCount==1)
			if(!bi->bmiColors[0].rgbRed)
				nPhotometric = PHOTOMETRIC_MINISBLACK;
			else
				nPhotometric = PHOTOMETRIC_MINISWHITE;
		if(bi->bmiHeader.biBitCount==8)
		{
			nPhotometric = PHOTOMETRIC_MINISBLACK;
			for(int i=0; i<nColors; i++)
				if(bi->bmiColors[i].rgbRed!=bi->bmiColors[i].rgbGreen
					|| bi->bmiColors[i].rgbRed !=bi->bmiColors[i].rgbBlue)
				{
					// Image en couleur avec palettes
					nPhotometric = PHOTOMETRIC_PALETTE;
					break;
				}
		}
	}
	else
	{
		TIFFSetField(tiff, TIFFTAG_BITSPERSAMPLE, 8);
		TIFFSetField(tiff, TIFFTAG_SAMPLESPERPIXEL, 3);
		nPhotometric = PHOTOMETRIC_RGB;
	}
	TIFFSetField(tiff, TIFFTAG_PHOTOMETRIC, nPhotometric);

	// Construction palette si necessaire
	unsigned short nRed[256], nGreen[256], nBlue[256];
	memset(&nRed, 0, sizeof(nRed));
	memset(&nGreen, 0, sizeof(nGreen));
	memset(&nBlue, 0, sizeof(nBlue));
	if(nPhotometric == PHOTOMETRIC_PALETTE)
	{
		unsigned short nRed[256], nGreen[256], nBlue[256];
		for(int i=0; i<nColors; i++)
		{
			nRed[i] = bi->bmiColors[i].rgbRed;
			nGreen[i] = bi->bmiColors[i].rgbGreen;
			nBlue[i] = bi->bmiColors[i].rgbBlue;
		}
		TIFFSetField(tiff, TIFFTAG_COLORMAP, &nRed, &nGreen, &nBlue);
	}

	// Indication de la compression à utiliser
	short nCompressTag;
	switch(nCompression)
	{
		case IMG_COMPRESS_LZW:
			nCompressTag = COMPRESSION_LZW;
			break;
		case IMG_COMPRESS_RLE:
			nCompressTag = (short)COMPRESSION_PACKBITS;
			break;
		case IMG_COMPRESS_JPEG:
			nCompressTag = COMPRESSION_JPEG;
			break;
		case IMG_COMPRESS_FAX3:
			nCompressTag = COMPRESSION_CCITTFAX3;
			break;
		case IMG_COMPRESS_FAX4:
			nCompressTag = COMPRESSION_CCITTFAX4;
			break;
		case IMG_COMPRESS_NONE:
		default:
			nCompressTag = COMPRESSION_NONE;
			break;
	}
	TIFFSetField(tiff, TIFFTAG_COMPRESSION, nCompressTag);

	// Ecriture des lignes
	int nScanWidth = WIDTHBYTES(bi->bmiHeader.biWidth*bi->bmiHeader.biBitCount);
	BYTE* lpBits = (BYTE*)bi+bi->bmiHeader.biSize+nColors*sizeof(RGBQUAD);

	BYTE* pScanline = (BYTE*)malloc(nScanWidth);
	if(!pScanline)
	{
		GlobalUnlock(m_hDib);
		TIFFClose(tiff);
		return FALSE;
	}

	for(int y=0; y<bi->bmiHeader.biHeight; y++)
	{
		memcpy(pScanline, lpBits+nScanWidth*(bi->bmiHeader.biHeight-y-1), nScanWidth);
		if(bi->bmiHeader.biBitCount==24)
			for(int i=0; i<bi->bmiHeader.biWidth*3; i+=3)
			{
				BYTE cDummy = pScanline[i];
				pScanline[i] = pScanline[i+2];
				pScanline[i+2] = cDummy;
			}

		if(bi->bmiHeader.biBitCount==8 && nPhotometric==PHOTOMETRIC_MINISBLACK)
			for(int i=0; i<bi->bmiHeader.biWidth; i++)
				pScanline[i] = bi->bmiColors[pScanline[i]].rgbRed;
		if(TIFFWriteScanline(tiff, (char*)pScanline, y, 0)<0)
		{
			free(pScanline);
			GlobalUnlock(m_hDib);
			TIFFClose(tiff);
			return FALSE;
		}
	}

	free(pScanline);
	GlobalUnlock(m_hDib);
	TIFFClose(tiff);
	return TRUE;
}
#endif // CIMAGE_USE_TIFF

#if defined(CIMAGE_USE_PNG)
// Sauvegarde d'une image au format PNG. Nécessite la librairie externe
BOOL CImage::SavePNG(HANDLE hFile)
{
	if(!m_hDib)
		return FALSE;

	BOOL bGrayScale = FALSE;

	LPBITMAPINFO bi = (LPBITMAPINFO)GlobalLock(m_hDib);
	int nColors = bi->bmiHeader.biClrUsed ? bi->bmiHeader.biClrUsed : 0x1FF & (1 << bi->bmiHeader.biBitCount);
	int nTypeColors;
	int nBitDepth = bi->bmiHeader.biBitCount;
	int nScanWidth = WIDTHBYTES(bi->bmiHeader.biWidth * bi->bmiHeader.biBitCount);

	switch(bi->bmiHeader.biBitCount)
	{
		case 1:
			nTypeColors = PNG_COLOR_TYPE_GRAY;
			break;
		case 4:
			nTypeColors = PNG_COLOR_TYPE_PALETTE;
			break;
		case 8:
			{
				nTypeColors = PNG_COLOR_TYPE_GRAY;
				for(int i=0; i<nColors; i++)
					if(bi->bmiColors[i].rgbRed!=bi->bmiColors[i].rgbGreen
						|| bi->bmiColors[i].rgbRed !=bi->bmiColors[i].rgbBlue)
					{
						// Image en couleur avec palettes
						nTypeColors = PNG_COLOR_TYPE_PALETTE;
						break;
					}
			}
			break;
		case 24:
			nBitDepth = 8;
			nTypeColors = PNG_COLOR_TYPE_RGB;
			break;
		default:
			GlobalUnlock(m_hDib);
			return FALSE;
	}

	png_structp pPng;
	png_infop pInfo;

	// Allocation des structures pour PNG
	pPng = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, CImagePngError, NULL);
	if(!pPng)
		return FALSE;
	pInfo = png_create_info_struct(pPng);
	if(!pInfo)
	{
		png_destroy_write_struct(&pPng, (png_infopp)NULL);
		return FALSE;
	}

	BYTE** pRowBuffer = NULL;
	PngCustomData CustomData;
	png_color Palette[256];
	BYTE* pScanLine = NULL;

	try
	{
		// On met la procédure d'écriture perso
		CustomData.hFile = hFile;
		png_set_write_fn(pPng, (void*)&CustomData, CImagePngWrite, CImagePngFlush);

		// paramétrage de la librairie
		png_set_compression_level(pPng, Z_BEST_COMPRESSION);
		png_set_IHDR(pPng, pInfo, bi->bmiHeader.biWidth, bi->bmiHeader.biHeight, nBitDepth,
			nTypeColors, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		if(nTypeColors==PNG_COLOR_TYPE_RGB)
			png_set_bgr(pPng);

		if(nTypeColors==PNG_COLOR_TYPE_GRAY && bi->bmiHeader.biBitCount==1
				&& bi->bmiColors[0].rgbRed)
			png_set_invert_mono(pPng);

		if(nTypeColors==PNG_COLOR_TYPE_PALETTE)
		{
			for(int i=0; i<nColors; i++)
			{
				Palette[i].red = bi->bmiColors[i].rgbRed;
				Palette[i].green = bi->bmiColors[i].rgbGreen;
				Palette[i].blue = bi->bmiColors[i].rgbBlue;
			}
			png_set_PLTE(pPng, pInfo, Palette, nColors);
		}

		if(m_dwTransparentColor & 0x80000000L)
		{
			// Affecter couleur transparente ds le PNG
			png_color_16 TransValues;
			memset(&TransValues, 0, sizeof(TransValues));
			if(nTypeColors==PNG_COLOR_TYPE_PALETTE)
			{
				png_byte Trans = (BYTE)(m_dwTransparentColor & 0xFF);
				TransValues.index = (BYTE)(m_dwTransparentColor & 0xFF);
				png_set_tRNS(pPng, pInfo, (png_bytep)&Trans, 0, &TransValues);
			}
			else
			{
				if(nTypeColors==PNG_COLOR_TYPE_RGB)
				{
					TransValues.red = (BYTE)(m_dwTransparentColor & 0xFF);
					TransValues.green = (BYTE)((m_dwTransparentColor>>8) & 0xFF);
					TransValues.blue = (BYTE)((m_dwTransparentColor>>16) & 0xFF);
				}
				else  // PNG_COLOR_TYPE_GRAY
					TransValues.gray = bi->bmiColors[m_dwTransparentColor & 0xFF].rgbRed;
				png_set_tRNS(pPng, pInfo, NULL, 0, (png_color_16p)&TransValues);
			}
		}

		// Affecter résolutions ds le PNG
		png_set_pHYs(pPng, pInfo, bi->bmiHeader.biXPelsPerMeter, bi->bmiHeader.biYPelsPerMeter,
			PNG_RESOLUTION_METER);

		// Ecriture des infos de base
		png_write_info(pPng, pInfo);

		// Ecriture ligne par ligne, avec transformation si besoin
		BYTE* pSrcLine = (BYTE*)bi+bi->bmiHeader.biSize+nColors*sizeof(RGBQUAD)
			+nScanWidth*(bi->bmiHeader.biHeight-1);
		if(nTypeColors==PNG_COLOR_TYPE_GRAY && bi->bmiHeader.biBitCount==8)
		{
			BYTE* pScanLine = (BYTE*)malloc(nScanWidth);
			if(!pScanLine)
			{
				png_destroy_write_struct(&pPng, (png_infopp)NULL);
				GlobalUnlock(m_hDib);
				return FALSE;
			}
			for(int i=bi->bmiHeader.biHeight-1; i>=0; i--)
			{
				memcpy(pScanLine, pSrcLine, nScanWidth);
				for(int j=0; j<nScanWidth; j++)
					pScanLine[j] = bi->bmiColors[pScanLine[j]].rgbRed;
				png_write_rows(pPng, &pScanLine, 1);
				pSrcLine -= nScanWidth;
			}
		}
		else
			for(int i=bi->bmiHeader.biHeight-1; i>=0; i--)
			{
				png_write_rows(pPng, &pSrcLine, 1);
				pSrcLine -= nScanWidth;
			}

		// Ecriture fichier terminée
		png_write_end(pPng, pInfo);
		if(pScanLine)
			free(pScanLine);
		GlobalUnlock(m_hDib);
		png_destroy_write_struct(&pPng, &pInfo);

		return TRUE;
	}
	catch(...)
	{
		png_destroy_write_struct(&pPng, &pInfo);
		if(pScanLine)
			free(pScanLine);
		GlobalUnlock(m_hDib);
		return FALSE;
	}
}

// Ecriture des données pour le PNG
void CImagePngWrite(png_structp pPng, png_bytep pData, unsigned int nLen)
{
	PngCustomData *pCustomData = (PngCustomData*)pPng->io_ptr;
	DWORD dwByteWrite;
	WriteFile(pCustomData->hFile, pData, (DWORD)nLen, &dwByteWrite, NULL);
	if(dwByteWrite!=(DWORD)nLen)
		png_error(pPng, "Write Error");
}

// Flush les buffers d'écriture pour le PNG
void CImagePngFlush(png_structp pPng)
{
	PngCustomData *pCustomData = (PngCustomData*)pPng->io_ptr;
	FlushFileBuffers(pCustomData->hFile);
}
#endif  // CIMAGE_USE_PNG

#endif

//===================================================================
// Fonction pour sélectionner un canal RVB. Activer avec CIMAGE_CHANNEL
//===================================================================

#if defined(CIMAGE_CHANNEL)

// Permet de sélectionner un canal RVB et d'affecter sa valeur aux autres canaux
void CImage::SelectChannelRVB(int nChannel)
{
	if(!m_hDib)
		return;	// DIB non valide

	LPBITMAPINFOHEADER BmInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO bi=(LPBITMAPINFO)BmInfo;

	// Détermination du nombre de couleurs
	int nColors = BmInfo->biClrUsed ? BmInfo->biClrUsed : 0x1FF & (1 << BmInfo->biBitCount);

	int nVal;

	if(nColors && nColors<=256 && BmInfo->biBitCount!=24) // Il y a une palette -> on joue sur la palette
	{
		for(int i=0; i<nColors; i++)
		{
			switch(nChannel)
			{
				case CANALRVB_ROUGE:
					nVal = bi->bmiColors[i].rgbRed;
					break;
				case CANALRVB_VERT:
					nVal = bi->bmiColors[i].rgbGreen;
					break;
				case CANALRVB_BLEU:
					nVal = bi->bmiColors[i].rgbBlue;
					break;
				default:
					nVal = GRAYSCALE(bi->bmiColors[i].rgbRed,
				bi->bmiColors[i].rgbGreen, bi->bmiColors[i].rgbBlue);
			}
			bi->bmiColors[i].rgbRed = bi->bmiColors[i].rgbGreen
				= bi->bmiColors[i].rgbBlue = nVal;
		}
	}
	else
	{	// 24 bits -> pas de palette (!! 32 bits non supporté)
		// Détermination de la zone des bits de l'image
		BYTE* lpBits = (BYTE*)BmInfo+BmInfo->biSize+nColors*sizeof(RGBQUAD);
		int nScanWidth = WIDTHBYTES(BmInfo->biWidth * BmInfo->biBitCount);

		for(int y=0; y<BmInfo->biHeight; y++)
		{
			int nOffset;
			for(int x=0; x<BmInfo->biWidth; x++)
			{
				nOffset = y*nScanWidth+x*3;
				switch(nChannel)
				{
					case CANALRVB_ROUGE:
						nVal = lpBits[nOffset+2];
						break;
					case CANALRVB_VERT:
						nVal = lpBits[nOffset+1];
						break;
					case CANALRVB_BLEU:
						nVal = lpBits[nOffset];
						break;
					default:
						nVal = GRAYSCALE(lpBits[nOffset+2],
							lpBits[nOffset+1], lpBits[nOffset]);
				}
				lpBits[nOffset] = lpBits[nOffset+1]
					= lpBits[nOffset+2] = nVal;
			}
		}
		// Adaptation de la couleur transparente
		if(m_dwTransparentColor & 0x80000000L)
		{
			lpBits = (BYTE*)&m_dwTransparentColor;
			switch(nChannel)
			{
				case CANALRVB_ROUGE:
					nVal = lpBits[2];
					break;
				case CANALRVB_VERT:
					nVal = lpBits[1];
					break;
				case CANALRVB_BLEU:
					nVal = lpBits[0];
					break;
				default:
					nVal = GRAYSCALE(lpBits[2],
						lpBits[1], lpBits[0]);
			}
			lpBits[0] = lpBits[1] = lpBits[2] = nVal;
		}
	}

	GlobalUnlock(m_hDib);
}

#endif

//===================================================================
// Fonctions pour effets spéciaux (Seulement en 24 bits). Activer avec CIMAGE_EFFECTS_24
//===================================================================

#if defined(CIMAGE_EFFECTS_24)

// Effectue un filtre par matrice (blur, soften...). Matrice Max: 15x15
BOOL CImage::Effect24MatrixFilter(LPCTSTR szMatrice)
{
	char* szCoefs = (char*)szMatrice;
	int nKoef = atoi(szCoefs);
	while((szCoefs[0]>='0' && szCoefs[0]<='9') || szCoefs[0]=='-')
		szCoefs++;
	while(szCoefs[0] && (szCoefs[0]<'0' || szCoefs[0]>'9') && szCoefs[0]!='-')
		szCoefs++;
	int nBias = atoi(szCoefs);
	while((szCoefs[0]>='0' && szCoefs[0]<='9') || szCoefs[0]=='-')
		szCoefs++;
	while(szCoefs[0] && (szCoefs[0]<'0' || szCoefs[0]>'9') && szCoefs[0]!='-')
		szCoefs++;
	int nRows = atoi(szCoefs);

	// Vérifications du filtre en mode Debug uniquement
	ASSERT(nKoef); // nKoef != 0 (sinon erreur division par 0)
	ASSERT(nRows>=3 && nRows<=15 && (nRows&1)); // Matrice min: 3x3, max:15x15, nRows impaire

	if(!m_hDib)
		return FALSE;	// DIB non valide

	if(GetBPP()!=24)
		return FALSE;

	// Récupération de la matrice
	int nMatrix[225];
	for(int i=0; i<nRows*nRows; i++)
	{
		while((szCoefs[0]>='0' && szCoefs[0]<='9') || szCoefs[0]=='-')
			szCoefs++;
		while(szCoefs[0] && (szCoefs[0]<'0' || szCoefs[0]>'9') && szCoefs[0]!='-')
			szCoefs++;
		nMatrix[i] = atoi(szCoefs);
	}

	// On crée une nouvelle zone mémoire pour accueillir le nouveau bitmap
	HGLOBAL hNewDib=GlobalAlloc(GHND, GlobalSize(m_hDib));
	if(!hNewDib)
		return FALSE;  // Pas assez de mémoire ou problème

	LPBITMAPINFOHEADER BmSrcInfo=(LPBITMAPINFOHEADER)GlobalLock(m_hDib);
	LPBITMAPINFO biSrc=(LPBITMAPINFO)BmSrcInfo;

	LPBITMAPINFOHEADER BmDestInfo=(LPBITMAPINFOHEADER)GlobalLock(hNewDib);
	LPBITMAPINFO biDest=(LPBITMAPINFO)BmDestInfo;

	// Détermination du nombre de couleurs
	int nColors = BmSrcInfo->biClrUsed ? BmSrcInfo->biClrUsed : 0x1FF & (1 << BmSrcInfo->biBitCount);

	// Copie du Header + palette ds le nouveau bitmap
	CopyMemory(biDest, biSrc, BmSrcInfo->biSize+nColors*sizeof(RGBQUAD));

	// Détermination de la zone des bits de l'image source et largeur lignes en octets
	BYTE* lpSrcBits = (BYTE*)BmSrcInfo+BmSrcInfo->biSize+nColors*sizeof(RGBQUAD);
	int nScanWidth = WIDTHBYTES(BmSrcInfo->biWidth * BmSrcInfo->biBitCount);

	// Détermination de la zone des bits de l'image destination
	BYTE* lpDestBits = (BYTE*)BmDestInfo+BmDestInfo->biSize+nColors*sizeof(RGBQUAD);

	int nRow2 = nRows>>1;

	for(int y=0; y<BmSrcInfo->biHeight; y++)
	{
		for(int x=0; x<BmSrcInfo->biWidth; x++)
		{
			int nRNewVal = 0;
			int nGNewVal = 0;
			int nBNewVal = 0;
			int k=0;
			for(int j=0; j<nRows; j++)
			{
				for(int i=0; i<nRows; i++)
				{
					if(x+i-nRow2>=0 && x+i-nRow2<BmSrcInfo->biWidth && y+j-nRow2>=0 && y+j-nRow2<BmSrcInfo->biHeight)
					{
						nBNewVal += lpSrcBits[(3*(x+i-nRow2))+((y+j-nRow2)*nScanWidth)]*nMatrix[k];
						nGNewVal += lpSrcBits[(3*(x+i-nRow2))+((y+j-nRow2)*nScanWidth)+1]*nMatrix[k];
						nRNewVal += lpSrcBits[(3*(x+i-nRow2))+((y+j-nRow2)*nScanWidth)+2]*nMatrix[k++];
					}
					else
					{
						nBNewVal += lpSrcBits[y*nScanWidth+x*3]*nMatrix[k];
						nGNewVal += lpSrcBits[y*nScanWidth+x*3+1]*nMatrix[k];
						nRNewVal += lpSrcBits[y*nScanWidth+x*3+2]*nMatrix[k++];
					}
				}
			}
			lpDestBits[y*nScanWidth+x*3] = (BYTE)max(min((int)(nBNewVal/nKoef+nBias), 255),0);
			lpDestBits[y*nScanWidth+x*3+1] = (BYTE)max(min((int)(nGNewVal/nKoef+nBias), 255),0);
			lpDestBits[y*nScanWidth+x*3+2] = (BYTE)max(min((int)(nRNewVal/nKoef+nBias), 255),0);
		}
	}

	GlobalUnlock(m_hDib);
	GlobalUnlock(hNewDib);
	GlobalFree(m_hDib);

	// On supprime l'ancien DIB et on le remplace par le nouveau
	m_hDib = hNewDib;
	return TRUE;
}

#endif

//===================================================================
//                        Fin du fichier
//===================================================================

