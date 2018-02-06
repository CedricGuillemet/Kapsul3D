# Microsoft Developer Studio Generated NMAKE File, Based on Path.dsp
!IF "$(CFG)" == ""
CFG=Path - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Path - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Path - Win32 Release" && "$(CFG)" != "Path - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Path.mak" CFG="Path - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Path - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Path - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "Path - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\path.dll"


CLEAN :
	-@erase "$(INTDIR)\Mapping.obj"
	-@erase "$(INTDIR)\ModdPath.obj"
	-@erase "$(INTDIR)\Modify.obj"
	-@erase "$(INTDIR)\ModPath.obj"
	-@erase "$(INTDIR)\Path.pch"
	-@erase "$(INTDIR)\PathRes.res"
	-@erase "$(INTDIR)\Shapes.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\path.exp"
	-@erase "$(OUTDIR)\path.lib"
	-@erase "..\plugins\path.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Path.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\PathRes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Path.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=glu.lib Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\path.pdb" /machine:I386 /out:"../plugins/path.dll" /implib:"$(OUTDIR)\path.lib" 
LINK32_OBJS= \
	"$(INTDIR)\ModdPath.obj" \
	"$(INTDIR)\ModPath.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\PathRes.res" \
	"$(INTDIR)\Mapping.obj" \
	"$(INTDIR)\Modify.obj" \
	"$(INTDIR)\Shapes.obj"

"..\plugins\path.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Path - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\path.dll"


CLEAN :
	-@erase "$(INTDIR)\Mapping.obj"
	-@erase "$(INTDIR)\ModdPath.obj"
	-@erase "$(INTDIR)\Modify.obj"
	-@erase "$(INTDIR)\ModPath.obj"
	-@erase "$(INTDIR)\Path.pch"
	-@erase "$(INTDIR)\PathRes.res"
	-@erase "$(INTDIR)\Shapes.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\path.exp"
	-@erase "$(OUTDIR)\path.lib"
	-@erase "$(OUTDIR)\path.pdb"
	-@erase "..\plugins\path.dll"
	-@erase "..\plugins\path.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Path.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\PathRes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Path.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=glu32.lib Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\path.pdb" /debug /machine:I386 /out:"../plugins/path.dll" /implib:"$(OUTDIR)\path.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ModdPath.obj" \
	"$(INTDIR)\ModPath.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\PathRes.res" \
	"$(INTDIR)\Mapping.obj" \
	"$(INTDIR)\Modify.obj" \
	"$(INTDIR)\Shapes.obj"

"..\plugins\path.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Path.dep")
!INCLUDE "Path.dep"
!ELSE 
!MESSAGE Warning: cannot find "Path.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Path - Win32 Release" || "$(CFG)" == "Path - Win32 Debug"
SOURCE=.\Mapping.cpp

"$(INTDIR)\Mapping.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Path.pch"


SOURCE=.\ModdPath.cpp

"$(INTDIR)\ModdPath.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Path.pch"


SOURCE=.\Modify.cpp

"$(INTDIR)\Modify.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Path.pch"


SOURCE=.\ModPath.cpp

"$(INTDIR)\ModPath.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Path.pch"


SOURCE=.\PathRes.rc

"$(INTDIR)\PathRes.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\Shapes.cpp

"$(INTDIR)\Shapes.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Path.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Path - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Path.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Path.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Path - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Path.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Path.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

