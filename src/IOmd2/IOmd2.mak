# Microsoft Developer Studio Generated NMAKE File, Based on IOmd2.dsp
!IF "$(CFG)" == ""
CFG=IOmd2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IOmd2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IOmd2 - Win32 Release" && "$(CFG)" != "IOmd2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IOmd2.mak" CFG="IOmd2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IOmd2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IOmd2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "IOmd2 - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\iomd2.dll"


CLEAN :
	-@erase "$(INTDIR)\IOmd2.obj"
	-@erase "$(INTDIR)\IOmd2.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\iomd2.exp"
	-@erase "$(OUTDIR)\iomd2.lib"
	-@erase "..\plugins\iomd2.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOmd2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IOmd2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\iomd2.pdb" /machine:I386 /out:"../plugins/iomd2.dll" /implib:"$(OUTDIR)\iomd2.lib" 
LINK32_OBJS= \
	"$(INTDIR)\IOmd2.obj" \
	"$(INTDIR)\stdafx.obj"

"..\plugins\iomd2.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IOmd2 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\iomd2.dll"


CLEAN :
	-@erase "$(INTDIR)\IOmd2.obj"
	-@erase "$(INTDIR)\IOmd2.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\iomd2.exp"
	-@erase "$(OUTDIR)\iomd2.lib"
	-@erase "$(OUTDIR)\iomd2.pdb"
	-@erase "..\plugins\iomd2.dll"
	-@erase "..\plugins\iomd2.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOmd2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IOmd2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=core.lib opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\iomd2.pdb" /debug /machine:I386 /out:"../plugins/iomd2.dll" /implib:"$(OUTDIR)\iomd2.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\IOmd2.obj" \
	"$(INTDIR)\stdafx.obj"

"..\plugins\iomd2.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("IOmd2.dep")
!INCLUDE "IOmd2.dep"
!ELSE 
!MESSAGE Warning: cannot find "IOmd2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IOmd2 - Win32 Release" || "$(CFG)" == "IOmd2 - Win32 Debug"
SOURCE=.\IOmd2.cpp

"$(INTDIR)\IOmd2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IOmd2.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "IOmd2 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOmd2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\IOmd2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IOmd2 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOmd2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\IOmd2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

