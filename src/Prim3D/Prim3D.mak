# Microsoft Developer Studio Generated NMAKE File, Based on Prim3D.dsp
!IF "$(CFG)" == ""
CFG=Prim3D - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Prim3D - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Prim3D - Win32 Release" && "$(CFG)" != "Prim3D - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Prim3D.mak" CFG="Prim3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Prim3D - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Prim3D - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Prim3D - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\Prim3D.dll"


CLEAN :
	-@erase "$(INTDIR)\Branch.obj"
	-@erase "$(INTDIR)\Branches.obj"
	-@erase "$(INTDIR)\BranchNoise.obj"
	-@erase "$(INTDIR)\Leaves.obj"
	-@erase "$(INTDIR)\Mapping.obj"
	-@erase "$(INTDIR)\ModPrim3D.obj"
	-@erase "$(INTDIR)\Parameters.obj"
	-@erase "$(INTDIR)\Prim3D.pch"
	-@erase "$(INTDIR)\Prim3DRes.res"
	-@erase "$(INTDIR)\PrimDiag.obj"
	-@erase "$(INTDIR)\Primitive.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\Tree.obj"
	-@erase "$(INTDIR)\TreeParam.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "..\plugins\Prim3D.dll"
	-@erase "..\plugins\Prim3D.ilk"
	-@erase ".\Debug\Prim3D.exp"
	-@erase ".\Debug\Prim3D.lib"
	-@erase ".\Debug\Prim3D.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PRIM3D_EXPORTS" /D "_AFXDLL" /Fp"$(INTDIR)\Prim3D.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\Prim3DRes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Prim3D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"Debug/Prim3D.pdb" /debug /machine:I386 /out:"../plugins/Prim3D.dll" /implib:"Debug/Prim3D.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Mapping.obj" \
	"$(INTDIR)\ModPrim3D.obj" \
	"$(INTDIR)\Parameters.obj" \
	"$(INTDIR)\PrimDiag.obj" \
	"$(INTDIR)\Primitive.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\TreeParam.obj" \
	"$(INTDIR)\Branch.obj" \
	"$(INTDIR)\Branches.obj" \
	"$(INTDIR)\BranchNoise.obj" \
	"$(INTDIR)\Leaves.obj" \
	"$(INTDIR)\Tree.obj" \
	"$(INTDIR)\Prim3DRes.res"

"..\plugins\Prim3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Prim3D - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\Prim3D.dll"


CLEAN :
	-@erase "$(INTDIR)\Branch.obj"
	-@erase "$(INTDIR)\Branches.obj"
	-@erase "$(INTDIR)\BranchNoise.obj"
	-@erase "$(INTDIR)\Leaves.obj"
	-@erase "$(INTDIR)\Mapping.obj"
	-@erase "$(INTDIR)\ModPrim3D.obj"
	-@erase "$(INTDIR)\Parameters.obj"
	-@erase "$(INTDIR)\Prim3D.pch"
	-@erase "$(INTDIR)\Prim3DRes.res"
	-@erase "$(INTDIR)\PrimDiag.obj"
	-@erase "$(INTDIR)\Primitive.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\Tree.obj"
	-@erase "$(INTDIR)\TreeParam.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Prim3D.exp"
	-@erase "$(OUTDIR)\Prim3D.lib"
	-@erase "$(OUTDIR)\Prim3D.pdb"
	-@erase "..\plugins\Prim3D.dll"
	-@erase "..\plugins\Prim3D.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PRIM3D_EXPORTS" /D "_AFXDLL" /Fp"$(INTDIR)\Prim3D.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\Prim3DRes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Prim3D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Prim3D.pdb" /debug /machine:I386 /out:"../plugins/Prim3D.dll" /implib:"$(OUTDIR)\Prim3D.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Mapping.obj" \
	"$(INTDIR)\ModPrim3D.obj" \
	"$(INTDIR)\Parameters.obj" \
	"$(INTDIR)\PrimDiag.obj" \
	"$(INTDIR)\Primitive.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\TreeParam.obj" \
	"$(INTDIR)\Branch.obj" \
	"$(INTDIR)\Branches.obj" \
	"$(INTDIR)\BranchNoise.obj" \
	"$(INTDIR)\Leaves.obj" \
	"$(INTDIR)\Tree.obj" \
	"$(INTDIR)\Prim3DRes.res"

"..\plugins\Prim3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Prim3D.dep")
!INCLUDE "Prim3D.dep"
!ELSE 
!MESSAGE Warning: cannot find "Prim3D.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Prim3D - Win32 Release" || "$(CFG)" == "Prim3D - Win32 Debug"
SOURCE=.\Mapping.cpp

"$(INTDIR)\Mapping.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"


SOURCE=.\ModPrim3D.cpp

"$(INTDIR)\ModPrim3D.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"


SOURCE=.\Parameters.cpp

"$(INTDIR)\Parameters.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"


SOURCE=.\Prim3DRes.rc

"$(INTDIR)\Prim3DRes.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\PrimDiag.cpp

"$(INTDIR)\PrimDiag.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"


SOURCE=.\Primitive.cpp

"$(INTDIR)\Primitive.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Prim3D - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PRIM3D_EXPORTS" /D "_AFXDLL" /Fp"$(INTDIR)\Prim3D.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Prim3D.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Prim3D - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "PRIM3D_EXPORTS" /D "_AFXDLL" /Fp"$(INTDIR)\Prim3D.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Prim3D.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TreeParam.cpp

"$(INTDIR)\TreeParam.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"


SOURCE=.\tree\tree\Branch.cpp

"$(INTDIR)\Branch.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\tree\tree\Branches.cpp

"$(INTDIR)\Branches.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\tree\tree\BranchNoise.cpp

"$(INTDIR)\BranchNoise.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\tree\tree\Leaves.cpp

"$(INTDIR)\Leaves.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\tree\tree\Tree.cpp

"$(INTDIR)\Tree.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Prim3D.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

