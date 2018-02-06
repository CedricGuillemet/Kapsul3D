# Microsoft Developer Studio Generated NMAKE File, Based on window.dsp
!IF "$(CFG)" == ""
CFG=window - Win32 Debug
!MESSAGE No configuration specified. Defaulting to window - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "window - Win32 Release" && "$(CFG)" != "window - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "window.mak" CFG="window - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "window - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "window - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "window - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\window.lib"

!ELSE 

ALL : "util - Win32 Release" "$(OUTDIR)\window.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"util - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\GLWindow.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Window.obj"
	-@erase "$(INTDIR)\WindowClass.obj"
	-@erase "$(OUTDIR)\window.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\window.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\window.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\window.lib" 
LIB32_OBJS= \
	"$(INTDIR)\GLWindow.obj" \
	"$(INTDIR)\Window.obj" \
	"$(INTDIR)\WindowClass.obj" \
	"..\util\Release\util.lib"

"$(OUTDIR)\window.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "window - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\window.lib"

!ELSE 

ALL : "util - Win32 Debug" "$(OUTDIR)\window.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"util - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\GLWindow.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Window.obj"
	-@erase "$(INTDIR)\WindowClass.obj"
	-@erase "$(OUTDIR)\window.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\window.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\window.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\window.lib" 
LIB32_OBJS= \
	"$(INTDIR)\GLWindow.obj" \
	"$(INTDIR)\Window.obj" \
	"$(INTDIR)\WindowClass.obj" \
	"..\util\Debug\util.lib"

"$(OUTDIR)\window.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
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
!IF EXISTS("window.dep")
!INCLUDE "window.dep"
!ELSE 
!MESSAGE Warning: cannot find "window.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "window - Win32 Release" || "$(CFG)" == "window - Win32 Debug"
SOURCE=..\..\lib\window\GLWindow.cpp

"$(INTDIR)\GLWindow.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\lib\window\Window.cpp

"$(INTDIR)\Window.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=..\..\lib\window\WindowClass.cpp

"$(INTDIR)\WindowClass.obj" : $(SOURCE) "$(INTDIR)"


!IF  "$(CFG)" == "window - Win32 Release"

"util - Win32 Release" : 
   cd "\WINNT\Profiles\thant\dev\lib\util"
   $(MAKE) /$(MAKEFLAGS) /F .\util.mak CFG="util - Win32 Release" 
   cd "..\window"

"util - Win32 ReleaseCLEAN" : 
   cd "\WINNT\Profiles\thant\dev\lib\util"
   $(MAKE) /$(MAKEFLAGS) /F .\util.mak CFG="util - Win32 Release" RECURSE=1 CLEAN 
   cd "..\window"

!ELSEIF  "$(CFG)" == "window - Win32 Debug"

"util - Win32 Debug" : 
   cd "\WINNT\Profiles\thant\dev\lib\util"
   $(MAKE) /$(MAKEFLAGS) /F .\util.mak CFG="util - Win32 Debug" 
   cd "..\window"

"util - Win32 DebugCLEAN" : 
   cd "\WINNT\Profiles\thant\dev\lib\util"
   $(MAKE) /$(MAKEFLAGS) /F .\util.mak CFG="util - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\window"

!ENDIF 


!ENDIF 

