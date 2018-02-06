# Microsoft Developer Studio Generated NMAKE File, Based on IOLwo.dsp
!IF "$(CFG)" == ""
CFG=IOLwo - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IOLwo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IOLwo - Win32 Release" && "$(CFG)" != "IOLwo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IOLwo.mak" CFG="IOLwo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IOLwo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IOLwo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "IOLwo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\ioLwo.dll"


CLEAN :
	-@erase "$(INTDIR)\IOLwo.obj"
	-@erase "$(INTDIR)\IOLwo.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\ioLwo.exp"
	-@erase "$(OUTDIR)\ioLwo.lib"
	-@erase "..\plugins\ioLwo.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOLwo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IOLwo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\ioLwo.pdb" /machine:I386 /out:"../plugins/ioLwo.dll" /implib:"$(OUTDIR)\ioLwo.lib" 
LINK32_OBJS= \
	"$(INTDIR)\IOLwo.obj" \
	"$(INTDIR)\stdafx.obj"

"..\plugins\ioLwo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IOLwo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\ioLwo.dll"


CLEAN :
	-@erase "$(INTDIR)\IOLwo.obj"
	-@erase "$(INTDIR)\IOLwo.pch"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\ioLwo.exp"
	-@erase "$(OUTDIR)\ioLwo.lib"
	-@erase "$(OUTDIR)\ioLwo.pdb"
	-@erase "..\plugins\ioLwo.dll"
	-@erase "..\plugins\ioLwo.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOLwo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IOLwo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\ioLwo.pdb" /debug /machine:I386 /out:"../plugins/ioLwo.dll" /implib:"$(OUTDIR)\ioLwo.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\IOLwo.obj" \
	"$(INTDIR)\stdafx.obj"

"..\plugins\ioLwo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("IOLwo.dep")
!INCLUDE "IOLwo.dep"
!ELSE 
!MESSAGE Warning: cannot find "IOLwo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IOLwo - Win32 Release" || "$(CFG)" == "IOLwo - Win32 Debug"
SOURCE=.\IOLwo.cpp

"$(INTDIR)\IOLwo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\IOLwo.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "IOLwo - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOLwo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\IOLwo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "IOLwo - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\IOLwo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\IOLwo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

