# Microsoft Developer Studio Generated NMAKE File, Based on Skeletton.dsp
!IF "$(CFG)" == ""
CFG=Skeletton - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Skeletton - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Skeletton - Win32 Release" && "$(CFG)" != "Skeletton - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Skeletton.mak" CFG="Skeletton - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Skeletton - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Skeletton - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Skeletton - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\skeletton.dll"


CLEAN :
	-@erase "$(INTDIR)\AnimSkel.obj"
	-@erase "$(INTDIR)\BuildSkel.obj"
	-@erase "$(INTDIR)\Mainframe.obj"
	-@erase "$(INTDIR)\ModdSkeletton.obj"
	-@erase "$(INTDIR)\ModSkeletton.obj"
	-@erase "$(INTDIR)\Skeletton.pch"
	-@erase "$(INTDIR)\SkelettonRes.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\ThirdPart.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\WeightSkel.obj"
	-@erase "$(OUTDIR)\skeletton.exp"
	-@erase "$(OUTDIR)\skeletton.lib"
	-@erase "..\plugins\skeletton.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Skeletton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\SkelettonRes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Skeletton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\skeletton.pdb" /machine:I386 /out:"../plugins/skeletton.dll" /implib:"$(OUTDIR)\skeletton.lib" 
LINK32_OBJS= \
	"$(INTDIR)\AnimSkel.obj" \
	"$(INTDIR)\BuildSkel.obj" \
	"$(INTDIR)\Mainframe.obj" \
	"$(INTDIR)\ModdSkeletton.obj" \
	"$(INTDIR)\ModSkeletton.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\ThirdPart.obj" \
	"$(INTDIR)\WeightSkel.obj" \
	"$(INTDIR)\SkelettonRes.res"

"..\plugins\skeletton.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Skeletton - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\skeletton.dll"


CLEAN :
	-@erase "$(INTDIR)\AnimSkel.obj"
	-@erase "$(INTDIR)\BuildSkel.obj"
	-@erase "$(INTDIR)\Mainframe.obj"
	-@erase "$(INTDIR)\ModdSkeletton.obj"
	-@erase "$(INTDIR)\ModSkeletton.obj"
	-@erase "$(INTDIR)\Skeletton.pch"
	-@erase "$(INTDIR)\SkelettonRes.res"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\ThirdPart.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\WeightSkel.obj"
	-@erase "$(OUTDIR)\skeletton.exp"
	-@erase "$(OUTDIR)\skeletton.lib"
	-@erase "$(OUTDIR)\skeletton.pdb"
	-@erase "..\plugins\skeletton.dll"
	-@erase "..\plugins\skeletton.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "F:\projets\Kapsul\Prim3D\tree\lib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Skeletton.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\SkelettonRes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Skeletton.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\skeletton.pdb" /debug /machine:I386 /out:"../plugins/skeletton.dll" /implib:"$(OUTDIR)\skeletton.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AnimSkel.obj" \
	"$(INTDIR)\BuildSkel.obj" \
	"$(INTDIR)\Mainframe.obj" \
	"$(INTDIR)\ModdSkeletton.obj" \
	"$(INTDIR)\ModSkeletton.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\ThirdPart.obj" \
	"$(INTDIR)\WeightSkel.obj" \
	"$(INTDIR)\SkelettonRes.res"

"..\plugins\skeletton.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Skeletton.dep")
!INCLUDE "Skeletton.dep"
!ELSE 
!MESSAGE Warning: cannot find "Skeletton.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Skeletton - Win32 Release" || "$(CFG)" == "Skeletton - Win32 Debug"
SOURCE=.\AnimSkel.cpp

"$(INTDIR)\AnimSkel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Skeletton.pch"


SOURCE=.\BuildSkel.cpp

"$(INTDIR)\BuildSkel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Skeletton.pch"


SOURCE=.\Mainframe.cpp

"$(INTDIR)\Mainframe.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Skeletton.pch"


SOURCE=.\ModdSkeletton.cpp

"$(INTDIR)\ModdSkeletton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Skeletton.pch"


SOURCE=.\ModSkeletton.cpp

"$(INTDIR)\ModSkeletton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Skeletton.pch"


SOURCE=.\SkelettonRes.rc

"$(INTDIR)\SkelettonRes.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Skeletton - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Skeletton.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Skeletton.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Skeletton - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "F:\projets\Kapsul\Prim3D\tree\lib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Skeletton.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Skeletton.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\ThirdPart.cpp

"$(INTDIR)\ThirdPart.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Skeletton.pch"


SOURCE=.\WeightSkel.cpp

"$(INTDIR)\WeightSkel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Skeletton.pch"



!ENDIF 

