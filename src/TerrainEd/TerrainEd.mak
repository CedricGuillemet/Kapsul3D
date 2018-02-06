# Microsoft Developer Studio Generated NMAKE File, Based on TerrainEd.dsp
!IF "$(CFG)" == ""
CFG=TerrainEd - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TerrainEd - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TerrainEd - Win32 Release" && "$(CFG)" != "TerrainEd - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TerrainEd.mak" CFG="TerrainEd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TerrainEd - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TerrainEd - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "TerrainEd - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\TerrainEd.exe"


CLEAN :
	-@erase "$(INTDIR)\AffImage.obj"
	-@erase "$(INTDIR)\CSkyView.obj"
	-@erase "$(INTDIR)\HeightDesign.obj"
	-@erase "$(INTDIR)\MapLightEdit.obj"
	-@erase "$(INTDIR)\OglViewer.obj"
	-@erase "$(INTDIR)\Preview.obj"
	-@erase "$(INTDIR)\rfHillTerrain.obj"
	-@erase "$(INTDIR)\SceneGraph.obj"
	-@erase "$(INTDIR)\SkyBoxEd.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Terra.obj"
	-@erase "$(INTDIR)\TerrainEd.obj"
	-@erase "$(INTDIR)\TerrainEd.pch"
	-@erase "$(INTDIR)\TerrainEd.res"
	-@erase "$(INTDIR)\TerrainEdDlg.obj"
	-@erase "$(INTDIR)\TerraLight.obj"
	-@erase "$(INTDIR)\TerraTex.obj"
	-@erase "$(INTDIR)\TreeDesign.obj"
	-@erase "$(INTDIR)\TreeView.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TerrainEd.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TerrainEd.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\TerrainEd.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TerrainEd.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib glu32.lib glut32.lib glaux.lib Prim3D.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\TerrainEd.pdb" /machine:I386 /out:"$(OUTDIR)\TerrainEd.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AffImage.obj" \
	"$(INTDIR)\CSkyView.obj" \
	"$(INTDIR)\HeightDesign.obj" \
	"$(INTDIR)\MapLightEdit.obj" \
	"$(INTDIR)\OglViewer.obj" \
	"$(INTDIR)\Preview.obj" \
	"$(INTDIR)\rfHillTerrain.obj" \
	"$(INTDIR)\SceneGraph.obj" \
	"$(INTDIR)\SkyBoxEd.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Terra.obj" \
	"$(INTDIR)\TerrainEd.obj" \
	"$(INTDIR)\TerrainEdDlg.obj" \
	"$(INTDIR)\TerraLight.obj" \
	"$(INTDIR)\TerraTex.obj" \
	"$(INTDIR)\TreeDesign.obj" \
	"$(INTDIR)\TreeView.obj" \
	"$(INTDIR)\TerrainEd.res"

"$(OUTDIR)\TerrainEd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TerrainEd - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\TerrainEd.exe"


CLEAN :
	-@erase "$(INTDIR)\AffImage.obj"
	-@erase "$(INTDIR)\CSkyView.obj"
	-@erase "$(INTDIR)\HeightDesign.obj"
	-@erase "$(INTDIR)\MapLightEdit.obj"
	-@erase "$(INTDIR)\OglViewer.obj"
	-@erase "$(INTDIR)\Preview.obj"
	-@erase "$(INTDIR)\rfHillTerrain.obj"
	-@erase "$(INTDIR)\SceneGraph.obj"
	-@erase "$(INTDIR)\SkyBoxEd.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Terra.obj"
	-@erase "$(INTDIR)\TerrainEd.obj"
	-@erase "$(INTDIR)\TerrainEd.pch"
	-@erase "$(INTDIR)\TerrainEd.res"
	-@erase "$(INTDIR)\TerrainEdDlg.obj"
	-@erase "$(INTDIR)\TerraLight.obj"
	-@erase "$(INTDIR)\TerraTex.obj"
	-@erase "$(INTDIR)\TreeDesign.obj"
	-@erase "$(INTDIR)\TreeView.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TerrainEd.pdb"
	-@erase "..\TerrainEd.exe"
	-@erase "..\TerrainEd.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TerrainEd.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\TerrainEd.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TerrainEd.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib glu32.lib glut32.lib glaux.lib Prim3D.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\TerrainEd.pdb" /debug /machine:I386 /out:"../TerrainEd.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AffImage.obj" \
	"$(INTDIR)\CSkyView.obj" \
	"$(INTDIR)\HeightDesign.obj" \
	"$(INTDIR)\MapLightEdit.obj" \
	"$(INTDIR)\OglViewer.obj" \
	"$(INTDIR)\Preview.obj" \
	"$(INTDIR)\rfHillTerrain.obj" \
	"$(INTDIR)\SceneGraph.obj" \
	"$(INTDIR)\SkyBoxEd.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Terra.obj" \
	"$(INTDIR)\TerrainEd.obj" \
	"$(INTDIR)\TerrainEdDlg.obj" \
	"$(INTDIR)\TerraLight.obj" \
	"$(INTDIR)\TerraTex.obj" \
	"$(INTDIR)\TreeDesign.obj" \
	"$(INTDIR)\TreeView.obj" \
	"$(INTDIR)\TerrainEd.res"

"..\TerrainEd.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("TerrainEd.dep")
!INCLUDE "TerrainEd.dep"
!ELSE 
!MESSAGE Warning: cannot find "TerrainEd.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TerrainEd - Win32 Release" || "$(CFG)" == "TerrainEd - Win32 Debug"
SOURCE=.\AffImage.cpp

"$(INTDIR)\AffImage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\CSkyView.cpp

"$(INTDIR)\CSkyView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\HeightDesign.cpp

"$(INTDIR)\HeightDesign.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\MapLightEdit.cpp

"$(INTDIR)\MapLightEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\OglViewer.cpp

"$(INTDIR)\OglViewer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\Preview.cpp

"$(INTDIR)\Preview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\rfHillTerrain.cpp

"$(INTDIR)\rfHillTerrain.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\SceneGraph.cpp

"$(INTDIR)\SceneGraph.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\SkyBoxEd.cpp

"$(INTDIR)\SkyBoxEd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\Splash.cpp

"$(INTDIR)\Splash.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TerrainEd - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TerrainEd.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TerrainEd.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TerrainEd - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TerrainEd.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TerrainEd.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Terra.cpp

"$(INTDIR)\Terra.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\TerrainEd.cpp

"$(INTDIR)\TerrainEd.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\TerrainEd.rc

"$(INTDIR)\TerrainEd.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\TerrainEdDlg.cpp

"$(INTDIR)\TerrainEdDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\TerraLight.cpp

"$(INTDIR)\TerraLight.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\TerraTex.cpp

"$(INTDIR)\TerraTex.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\TreeDesign.cpp

"$(INTDIR)\TreeDesign.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"


SOURCE=.\TreeView.cpp

"$(INTDIR)\TreeView.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TerrainEd.pch"



!ENDIF 

