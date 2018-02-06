# Microsoft Developer Studio Generated NMAKE File, Based on Light.dsp
!IF "$(CFG)" == ""
CFG=Light - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Light - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Light - Win32 Release" && "$(CFG)" != "Light - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Light.mak" CFG="Light - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Light - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Light - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Light - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\light.dll"


CLEAN :
	-@erase "$(INTDIR)\Light.pch"
	-@erase "$(INTDIR)\LightBuild.obj"
	-@erase "$(INTDIR)\LightMod.obj"
	-@erase "$(INTDIR)\LightParam.obj"
	-@erase "$(INTDIR)\LightRes.res"
	-@erase "$(INTDIR)\ModLight.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\light.exp"
	-@erase "$(OUTDIR)\light.lib"
	-@erase "..\plugins\light.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Light.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\LightRes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Light.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\light.pdb" /machine:I386 /out:"../plugins/light.dll" /implib:"$(OUTDIR)\light.lib" 
LINK32_OBJS= \
	"$(INTDIR)\LightBuild.obj" \
	"$(INTDIR)\LightMod.obj" \
	"$(INTDIR)\LightParam.obj" \
	"$(INTDIR)\ModLight.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\LightRes.res"

"..\plugins\light.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Light - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\light.dll"


CLEAN :
	-@erase "$(INTDIR)\Light.pch"
	-@erase "$(INTDIR)\LightBuild.obj"
	-@erase "$(INTDIR)\LightMod.obj"
	-@erase "$(INTDIR)\LightParam.obj"
	-@erase "$(INTDIR)\LightRes.res"
	-@erase "$(INTDIR)\ModLight.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\light.exp"
	-@erase "$(OUTDIR)\light.lib"
	-@erase "$(OUTDIR)\light.pdb"
	-@erase "..\plugins\light.dll"
	-@erase "..\plugins\light.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Light.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\LightRes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Light.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=opengl32.lib Kore.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\light.pdb" /debug /machine:I386 /out:"../plugins/light.dll" /implib:"$(OUTDIR)\light.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\LightBuild.obj" \
	"$(INTDIR)\LightMod.obj" \
	"$(INTDIR)\LightParam.obj" \
	"$(INTDIR)\ModLight.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\LightRes.res"

"..\plugins\light.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Light.dep")
!INCLUDE "Light.dep"
!ELSE 
!MESSAGE Warning: cannot find "Light.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Light - Win32 Release" || "$(CFG)" == "Light - Win32 Debug"
SOURCE=.\LightBuild.cpp

"$(INTDIR)\LightBuild.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Light.pch"


SOURCE=.\LightMod.cpp

"$(INTDIR)\LightMod.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Light.pch"


SOURCE=.\LightParam.cpp

"$(INTDIR)\LightParam.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Light.pch"


SOURCE=.\LightRes.rc

"$(INTDIR)\LightRes.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ModLight.cpp

"$(INTDIR)\ModLight.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Light.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Light - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Light.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Light.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Light - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Light.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Light.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

