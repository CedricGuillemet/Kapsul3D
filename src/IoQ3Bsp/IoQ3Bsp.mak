# Microsoft Developer Studio Generated NMAKE File, Based on IoQ3Bsp.dsp
!IF "$(CFG)" == ""
CFG=IoQ3Bsp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to IoQ3Bsp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "IoQ3Bsp - Win32 Release" && "$(CFG)" != "IoQ3Bsp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "IoQ3Bsp.mak" CFG="IoQ3Bsp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "IoQ3Bsp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "IoQ3Bsp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "IoQ3Bsp - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\plugins\IoQ3Bsp.dll"


CLEAN :
	-@erase "$(INTDIR)\arglist.obj"
	-@erase "$(INTDIR)\fload.obj"
	-@erase "$(INTDIR)\ioQ3Bsp.obj"
	-@erase "$(INTDIR)\loadbmp.obj"
	-@erase "$(INTDIR)\patch.obj"
	-@erase "$(INTDIR)\q3bsp.obj"
	-@erase "$(INTDIR)\q3shader.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stringdict.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vformat.obj"
	-@erase "$(OUTDIR)\IoQ3Bsp.exp"
	-@erase "$(OUTDIR)\IoQ3Bsp.lib"
	-@erase "..\plugins\IoQ3Bsp.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IOQ3BSP_EXPORTS" /Fp"$(INTDIR)\IoQ3Bsp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IoQ3Bsp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib core.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\IoQ3Bsp.pdb" /machine:I386 /out:"../plugins/IoQ3Bsp.dll" /implib:"$(OUTDIR)\IoQ3Bsp.lib" 
LINK32_OBJS= \
	"$(INTDIR)\arglist.obj" \
	"$(INTDIR)\fload.obj" \
	"$(INTDIR)\ioQ3Bsp.obj" \
	"$(INTDIR)\loadbmp.obj" \
	"$(INTDIR)\patch.obj" \
	"$(INTDIR)\q3bsp.obj" \
	"$(INTDIR)\q3shader.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stringdict.obj" \
	"$(INTDIR)\vformat.obj"

"..\plugins\IoQ3Bsp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "IoQ3Bsp - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\plugins\IoQ3Bsp.dll"


CLEAN :
	-@erase "$(INTDIR)\arglist.obj"
	-@erase "$(INTDIR)\fload.obj"
	-@erase "$(INTDIR)\ioQ3Bsp.obj"
	-@erase "$(INTDIR)\loadbmp.obj"
	-@erase "$(INTDIR)\patch.obj"
	-@erase "$(INTDIR)\q3bsp.obj"
	-@erase "$(INTDIR)\q3shader.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\stringdict.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vformat.obj"
	-@erase "$(OUTDIR)\IoQ3Bsp.exp"
	-@erase "$(OUTDIR)\IoQ3Bsp.lib"
	-@erase "$(OUTDIR)\IoQ3Bsp.pdb"
	-@erase "..\plugins\IoQ3Bsp.dll"
	-@erase "..\plugins\IoQ3Bsp.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

F90=fl32.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "IOQ3BSP_EXPORTS" /Fp"$(INTDIR)\IoQ3Bsp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\IoQ3Bsp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib core.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\IoQ3Bsp.pdb" /debug /machine:I386 /out:"../plugins/IoQ3Bsp.dll" /implib:"$(OUTDIR)\IoQ3Bsp.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\arglist.obj" \
	"$(INTDIR)\fload.obj" \
	"$(INTDIR)\ioQ3Bsp.obj" \
	"$(INTDIR)\loadbmp.obj" \
	"$(INTDIR)\patch.obj" \
	"$(INTDIR)\q3bsp.obj" \
	"$(INTDIR)\q3shader.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\stringdict.obj" \
	"$(INTDIR)\vformat.obj"

"..\plugins\IoQ3Bsp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("IoQ3Bsp.dep")
!INCLUDE "IoQ3Bsp.dep"
!ELSE 
!MESSAGE Warning: cannot find "IoQ3Bsp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "IoQ3Bsp - Win32 Release" || "$(CFG)" == "IoQ3Bsp - Win32 Debug"
SOURCE=.\arglist.cpp

"$(INTDIR)\arglist.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\fload.cpp

"$(INTDIR)\fload.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\ioQ3Bsp.cpp

"$(INTDIR)\ioQ3Bsp.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\loadbmp.cpp

"$(INTDIR)\loadbmp.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\patch.cpp

"$(INTDIR)\patch.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\q3bsp.cpp

"$(INTDIR)\q3bsp.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\q3shader.cpp

"$(INTDIR)\q3shader.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\stringdict.cpp

"$(INTDIR)\stringdict.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\vformat.cpp

"$(INTDIR)\vformat.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

