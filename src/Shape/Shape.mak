# Microsoft Developer Studio Generated NMAKE File, Based on Shape.dsp
!IF "$(CFG)" == ""
CFG=Shape - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Shape - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Shape - Win32 Release" && "$(CFG)" != "Shape - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Shape.mak" CFG="Shape - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Shape - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Shape - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Shape - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\shape.dll"


CLEAN :
	-@erase "$(INTDIR)\MainEdit.obj"
	-@erase "$(INTDIR)\MainFrame.obj"
	-@erase "$(INTDIR)\ModdShape.obj"
	-@erase "$(INTDIR)\ModShape.obj"
	-@erase "$(INTDIR)\Parameters.obj"
	-@erase "$(INTDIR)\Shape.pch"
	-@erase "$(INTDIR)\ShapeRes.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\shape.exp"
	-@erase "$(OUTDIR)\shape.lib"
	-@erase "..\plugins\shape.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Shape.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\ShapeRes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Shape.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib aglMFC.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\shape.pdb" /machine:I386 /out:"../plugins/shape.dll" /implib:"$(OUTDIR)\shape.lib" 
LINK32_OBJS= \
	"$(INTDIR)\MainEdit.obj" \
	"$(INTDIR)\MainFrame.obj" \
	"$(INTDIR)\ModdShape.obj" \
	"$(INTDIR)\ModShape.obj" \
	"$(INTDIR)\Parameters.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\ShapeRes.res"

"..\plugins\shape.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Shape - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\shape.dll"


CLEAN :
	-@erase "$(INTDIR)\MainEdit.obj"
	-@erase "$(INTDIR)\MainFrame.obj"
	-@erase "$(INTDIR)\ModdShape.obj"
	-@erase "$(INTDIR)\ModShape.obj"
	-@erase "$(INTDIR)\Parameters.obj"
	-@erase "$(INTDIR)\Shape.pch"
	-@erase "$(INTDIR)\ShapeRes.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\shape.exp"
	-@erase "$(OUTDIR)\shape.lib"
	-@erase "$(OUTDIR)\shape.pdb"
	-@erase "..\plugins\shape.dll"
	-@erase "..\plugins\shape.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Shape.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\ShapeRes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Shape.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib aglMFC.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\shape.pdb" /debug /machine:I386 /out:"../plugins/shape.dll" /implib:"$(OUTDIR)\shape.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\MainEdit.obj" \
	"$(INTDIR)\MainFrame.obj" \
	"$(INTDIR)\ModdShape.obj" \
	"$(INTDIR)\ModShape.obj" \
	"$(INTDIR)\Parameters.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\ShapeRes.res"

"..\plugins\shape.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Shape.dep")
!INCLUDE "Shape.dep"
!ELSE 
!MESSAGE Warning: cannot find "Shape.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Shape - Win32 Release" || "$(CFG)" == "Shape - Win32 Debug"
SOURCE=.\MainEdit.cpp

"$(INTDIR)\MainEdit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Shape.pch"


SOURCE=.\MainFrame.cpp

"$(INTDIR)\MainFrame.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Shape.pch"


SOURCE=.\ModdShape.cpp

"$(INTDIR)\ModdShape.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Shape.pch"


SOURCE=.\ModShape.cpp

"$(INTDIR)\ModShape.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Shape.pch"


SOURCE=.\Parameters.cpp

"$(INTDIR)\Parameters.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Shape.pch"


SOURCE=.\ShapeRes.rc

"$(INTDIR)\ShapeRes.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Shape - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Shape.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Shape.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Shape - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Shape.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Shape.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

