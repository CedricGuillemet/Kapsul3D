// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//


#if !defined(AFX_STDAFX_H__91556EB7_C802_4FE6_AB3C_291A38C99A81__INCLUDED_)
#define AFX_STDAFX_H__91556EB7_C802_4FE6_AB3C_291A38C99A81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "Kapsul3D.h"
#include "kgui.h"
#include <stdlib.h>
class CModDiag;

#include "resource.h"
#include "KUVEdit.h"
#include "ModDiag.h"
#include "ModModifier.h"
#include "Interface.h"
#include "Modifier.h"
#include "extrud.h"
#include "Lathe.h"
#include "Path.h"
#include "spherize.h"
#include "uvparam.h"
#include "Normals.h"
#include "subdiv.h"
#include "ModModifier.h"
#include "explode.h"
#include "Fractalize.h"
#include "Divide.h"
#include "CalcTex.h"
#include "UVMapperDiag.h"
#include "ResSwitch.h"
#include "PrecalcLight.h"

#define ACTION_EXPLODE 1
#define ACTION_SPHERIZE 2
#define ACTION_LATHE 3
#define ACTION_CUTTER 4
#define ACTION_EXTRUD 5
#define ACTION_FRACTALIZE 6
#define ACTION_SELECTSHAPE 7
#define ACTION_SELECTPATH 8
#define ACTION_PATHMOVE 9
#define ACTION_PATHSCALEX 10
#define ACTION_PATHSCALEY 11
#define ACTION_PATHROTATEX 12
#define ACTION_PATHROTATEY 13
#define ACTION_PATHROTATEZ 14
#define ACTION_SUBDIVIDE 15
#define ACTION_MAPPINGEDIT 16

extern CModifier m_Modify;
extern CExplode m_Explode;
extern CExtrud m_Extrud;
extern CLathe m_Lathe;
extern CPath m_Path;
extern CSpherize m_Spherize;
extern CUVParam m_UVParam;
extern CNormals m_Normals;
extern CSubdiv m_SubDiv;
extern CFractalize m_Fractalize;
extern CDivide m_Divide;
extern CCalcTex m_CalcTex;
extern CUVMapperDiag m_Mapper;
extern CPrecalcLight m_Lightmap;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__2581243C_E13D_4E7F_896D_5B9A16E7997C__INCLUDED_)
