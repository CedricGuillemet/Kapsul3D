// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__CD874C08_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_)
#define AFX_STDAFX_H__CD874C08_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC OLE automation classes
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


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

#define CIMAGE_LDRSRC_GIF	// Compuserve GIF

#define CIMAGE_USE_JPEG		// JPEG
#define CIMAGE_USE_TIFF		// Tagged Image File Format (TIFF)
#define CIMAGE_USE_PNG		// Portable Network Graphic (PNG)
#include "headers.h"

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__CD874C08_8ADC_11D2_9D51_02608C7A0EC4__INCLUDED_)

