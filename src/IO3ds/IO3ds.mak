# Microsoft Developer Studio Generated NMAKE File, Based on IO3ds.dsp
!IF "$(CFG)" == ""
CFG=IO3ds - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IO3ds - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IO3ds - Win32 Release" && "$(CFG)" != "IO3ds - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IO3ds.mak" CFG="IO3ds - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IO3ds - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IO3ds - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "IO3ds - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\io3ds.dll"


CLEAN :
	-@erase "$(INTDIR)\IO3ds.obj"
	-@erase "$(INTDIR)\IO3ds.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\io3ds.exp"
	-@erase "$(OUTDIR)\io3ds.lib"
	-@erase "..\plugins\io3ds.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IO3ds.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IO3ds.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\io3ds.pdb" /machine:I386 /out:"../plugins/io3ds.dll" /implib:"$(OUTDIR)\io3ds.lib" 
LINK32_OBJS= \
	"$(INTDIR)\IO3ds.obj" \
	"$(INTDIR)\stdafx.obj"

"..\plugins\io3ds.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IO3ds - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\io3ds.dll"


CLEAN :
	-@erase "$(INTDIR)\IO3ds.obj"
	-@erase "$(INTDIR)\IO3ds.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\io3ds.exp"
	-@erase "$(OUTDIR)\io3ds.lib"
	-@erase "$(OUTDIR)\io3ds.pdb"
	-@erase "..\plugins\io3ds.dll"
	-@erase "..\plugins\io3ds.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IO3ds.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IO3ds.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\io3ds.pdb" /debug /machine:I386 /out:"../plugins/io3ds.dll" /implib:"$(OUTDIR)\io3ds.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\IO3ds.obj" \
	"$(INTDIR)\stdafx.obj"

"..\plugins\io3ds.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("IO3ds.dep")
!INCLUDE "IO3ds.dep"
!ELSE 
!MESSAGE Warning: cannot find "IO3ds.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IO3ds - Win32 Release" || "$(CFG)" == "IO3ds - Win32 Debug"
SOURCE=.\IO3ds.cpp

"$(INTDIR)\IO3ds.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IO3ds.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "IO3ds - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IO3ds.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\IO3ds.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IO3ds - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IO3ds.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\IO3ds.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

