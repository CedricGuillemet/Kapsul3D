# Microsoft Developer Studio Generated NMAKE File, Based on IOkdk.dsp
!IF "$(CFG)" == ""
CFG=IOkdk - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IOkdk - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IOkdk - Win32 Release" && "$(CFG)" != "IOkdk - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IOkdk.mak" CFG="IOkdk - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IOkdk - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IOkdk - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "IOkdk - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\iokdk.dll"


CLEAN :
	-@erase "$(INTDIR)\IOkdk.obj"
	-@erase "$(INTDIR)\IOkdk.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\iokdk.exp"
	-@erase "$(OUTDIR)\iokdk.lib"
	-@erase "..\plugins\iokdk.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOkdk.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IOkdk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\iokdk.pdb" /machine:I386 /out:"../plugins/iokdk.dll" /implib:"$(OUTDIR)\iokdk.lib" 
LINK32_OBJS= \
	"$(INTDIR)\IOkdk.obj" \
	"$(INTDIR)\stdafx.obj"

"..\plugins\iokdk.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IOkdk - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\iokdk.dll"


CLEAN :
	-@erase "$(INTDIR)\IOkdk.obj"
	-@erase "$(INTDIR)\IOkdk.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\iokdk.exp"
	-@erase "$(OUTDIR)\iokdk.lib"
	-@erase "$(OUTDIR)\iokdk.pdb"
	-@erase "..\plugins\iokdk.dll"
	-@erase "..\plugins\iokdk.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOkdk.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IOkdk.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\iokdk.pdb" /debug /machine:I386 /out:"../plugins/iokdk.dll" /implib:"$(OUTDIR)\iokdk.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\IOkdk.obj" \
	"$(INTDIR)\stdafx.obj"

"..\plugins\iokdk.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("IOkdk.dep")
!INCLUDE "IOkdk.dep"
!ELSE 
!MESSAGE Warning: cannot find "IOkdk.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IOkdk - Win32 Release" || "$(CFG)" == "IOkdk - Win32 Debug"
SOURCE=.\IOkdk.cpp

"$(INTDIR)\IOkdk.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IOkdk.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "IOkdk - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOkdk.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\IOkdk.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IOkdk - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOkdk.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\IOkdk.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

