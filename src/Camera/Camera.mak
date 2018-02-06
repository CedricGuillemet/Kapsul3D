# Microsoft Developer Studio Generated NMAKE File, Based on Camera.dsp
!IF "$(CFG)" == ""
CFG=Camera - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Camera - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Camera - Win32 Release" && "$(CFG)" != "Camera - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Camera.mak" CFG="Camera - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Camera - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Camera - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Camera - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\camera.dll"


CLEAN :
	-@erase "$(INTDIR)\BuildDiag.obj"
	-@erase "$(INTDIR)\Camera.pch"
	-@erase "$(INTDIR)\CameraRes.res"
	-@erase "$(INTDIR)\ModCamera.obj"
	-@erase "$(INTDIR)\ModDiag.obj"
	-@erase "$(INTDIR)\ParamDiag.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\camera.exp"
	-@erase "$(OUTDIR)\camera.lib"
	-@erase "..\plugins\camera.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Camera.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\CameraRes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Camera.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\camera.pdb" /machine:I386 /out:"../plugins/camera.dll" /implib:"$(OUTDIR)\camera.lib" 
LINK32_OBJS= \
	"$(INTDIR)\BuildDiag.obj" \
	"$(INTDIR)\ModCamera.obj" \
	"$(INTDIR)\ModDiag.obj" \
	"$(INTDIR)\ParamDiag.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\CameraRes.res"

"..\plugins\camera.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Camera - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\camera.dll"


CLEAN :
	-@erase "$(INTDIR)\BuildDiag.obj"
	-@erase "$(INTDIR)\Camera.pch"
	-@erase "$(INTDIR)\CameraRes.res"
	-@erase "$(INTDIR)\ModCamera.obj"
	-@erase "$(INTDIR)\ModDiag.obj"
	-@erase "$(INTDIR)\ParamDiag.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\camera.exp"
	-@erase "$(OUTDIR)\camera.lib"
	-@erase "$(OUTDIR)\camera.pdb"
	-@erase "..\plugins\camera.dll"
	-@erase "..\plugins\camera.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Camera.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\CameraRes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Camera.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=Kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\camera.pdb" /debug /machine:I386 /out:"../plugins/camera.dll" /implib:"$(OUTDIR)\camera.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\BuildDiag.obj" \
	"$(INTDIR)\ModCamera.obj" \
	"$(INTDIR)\ModDiag.obj" \
	"$(INTDIR)\ParamDiag.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\CameraRes.res"

"..\plugins\camera.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Camera.dep")
!INCLUDE "Camera.dep"
!ELSE 
!MESSAGE Warning: cannot find "Camera.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Camera - Win32 Release" || "$(CFG)" == "Camera - Win32 Debug"
SOURCE=.\BuildDiag.cpp

"$(INTDIR)\BuildDiag.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Camera.pch"


SOURCE=.\CameraRes.rc

"$(INTDIR)\CameraRes.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ModCamera.cpp

"$(INTDIR)\ModCamera.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Camera.pch"


SOURCE=.\ModDiag.cpp

"$(INTDIR)\ModDiag.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Camera.pch"


SOURCE=.\ParamDiag.cpp

"$(INTDIR)\ParamDiag.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Camera.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Camera - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Camera.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Camera.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Camera - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Camera.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Camera.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

