# Microsoft Developer Studio Generated NMAKE File, Based on Modifier.dsp
!IF "$(CFG)" == ""
CFG=Modifier - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Modifier - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Modifier - Win32 Release" && "$(CFG)" != "Modifier - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Modifier.mak" CFG="Modifier - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Modifier - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Modifier - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Modifier - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\Modifier.dll"


CLEAN :
	-@erase "$(INTDIR)\ModDiag.obj"
	-@erase "$(INTDIR)\Modifier.obj"
	-@erase "$(INTDIR)\Modifier.pch"
	-@erase "$(INTDIR)\ModifierRes.res"
	-@erase "$(INTDIR)\ModModifier.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Modifier.exp"
	-@erase "$(OUTDIR)\Modifier.lib"
	-@erase "..\plugins\Modifier.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Modifier.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\ModifierRes.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Modifier.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:no /pdb:"$(OUTDIR)\Modifier.pdb" /machine:I386 /out:"../plugins/Modifier.dll" /implib:"$(OUTDIR)\Modifier.lib" 
LINK32_OBJS= \
	"$(INTDIR)\ModDiag.obj" \
	"$(INTDIR)\Modifier.obj" \
	"$(INTDIR)\ModModifier.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\ModifierRes.res"

"..\plugins\Modifier.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Modifier - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\Modifier.dll"


CLEAN :
	-@erase "$(INTDIR)\ModDiag.obj"
	-@erase "$(INTDIR)\Modifier.obj"
	-@erase "$(INTDIR)\Modifier.pch"
	-@erase "$(INTDIR)\ModifierRes.res"
	-@erase "$(INTDIR)\ModModifier.obj"
	-@erase "$(INTDIR)\stdafx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Modifier.exp"
	-@erase "$(OUTDIR)\Modifier.lib"
	-@erase "$(OUTDIR)\Modifier.pdb"
	-@erase "..\plugins\Modifier.dll"
	-@erase "..\plugins\Modifier.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Modifier.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\ModifierRes.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Modifier.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kore.lib opengl32.lib /nologo /subsystem:windows /dll /incremental:yes /pdb:"$(OUTDIR)\Modifier.pdb" /debug /machine:I386 /out:"../plugins/Modifier.dll" /implib:"$(OUTDIR)\Modifier.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ModDiag.obj" \
	"$(INTDIR)\Modifier.obj" \
	"$(INTDIR)\ModModifier.obj" \
	"$(INTDIR)\stdafx.obj" \
	"$(INTDIR)\ModifierRes.res"

"..\plugins\Modifier.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Modifier.dep")
!INCLUDE "Modifier.dep"
!ELSE 
!MESSAGE Warning: cannot find "Modifier.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Modifier - Win32 Release" || "$(CFG)" == "Modifier - Win32 Debug"
SOURCE=.\ModDiag.cpp

"$(INTDIR)\ModDiag.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Modifier.pch"


SOURCE=.\Modifier.cpp

"$(INTDIR)\Modifier.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Modifier.pch"


SOURCE=.\ModifierRes.rc

"$(INTDIR)\ModifierRes.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\ModModifier.cpp

"$(INTDIR)\ModModifier.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Modifier.pch"


SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "Modifier - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Modifier.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Modifier.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Modifier - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\Modifier.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\stdafx.obj"	"$(INTDIR)\Modifier.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

