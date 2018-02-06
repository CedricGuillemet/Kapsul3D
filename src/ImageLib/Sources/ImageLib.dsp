# Microsoft Developer Studio Project File - Name="ImageLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ImageLib - Win32 Debug MultiThread DLL
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ImageLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ImageLib.mak" CFG="ImageLib - Win32 Debug MultiThread DLL"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ImageLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageLib - Win32 Debug MultiThread" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageLib - Win32 Debug MultiThread DLL" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageLib - Win32 Release MultiThread" (based on "Win32 (x86) Static Library")
!MESSAGE "ImageLib - Win32 Release MultiThread DLL" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ImageLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Compilation\Release"
# PROP Intermediate_Dir "Compilation\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Librairies\ImageLib.lib"

!ELSEIF  "$(CFG)" == "ImageLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Compilation\Debug"
# PROP Intermediate_Dir "Compilation\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Librairies\ImageLibD.lib"

!ELSEIF  "$(CFG)" == "ImageLib - Win32 Debug MultiThread"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug MultiThread"
# PROP BASE Intermediate_Dir "Debug MultiThread"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Compilation\Debug MultiThread"
# PROP Intermediate_Dir "Compilation\Debug MultiThread"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Debug\ImageLibDbg.lib"
# ADD LIB32 /nologo /out:"..\..\Librairies\ImageLibDMT.lib"

!ELSEIF  "$(CFG)" == "ImageLib - Win32 Debug MultiThread DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug MultiThread DLL"
# PROP BASE Intermediate_Dir "Debug MultiThread DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Compilation\Debug MultiThread DLL"
# PROP Intermediate_Dir "Compilation\Debug MultiThread DLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Debug\ImageLibDbg.lib"
# ADD LIB32 /nologo /out:"..\..\Librairies\ImageLibDMTD.lib"

!ELSEIF  "$(CFG)" == "ImageLib - Win32 Release MultiThread"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release MultiThread"
# PROP BASE Intermediate_Dir "Release MultiThread"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Compilation\Release MultiThread"
# PROP Intermediate_Dir "Compilation\Release MultiThread"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Librairies\ImageLibMT.lib"

!ELSEIF  "$(CFG)" == "ImageLib - Win32 Release MultiThread DLL"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release MultiThread DLL"
# PROP BASE Intermediate_Dir "Release MultiThread DLL"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Compilation\Release MultiThread DLL"
# PROP Intermediate_Dir "Compilation\Release MultiThread DLL"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\Librairies\ImageLibMTD.lib"

!ENDIF 

# Begin Target

# Name "ImageLib - Win32 Release"
# Name "ImageLib - Win32 Debug"
# Name "ImageLib - Win32 Debug MultiThread"
# Name "ImageLib - Win32 Debug MultiThread DLL"
# Name "ImageLib - Win32 Release MultiThread"
# Name "ImageLib - Win32 Release MultiThread DLL"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Jpeg Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Sources Jpeg\jpeglib.h"
# End Source File
# End Group
# Begin Group "Tiff Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Sources Tiff\tif_msrc.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tiffiop.h"
# End Source File
# End Group
# Begin Group "Png Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Sources Png\png.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngconf.h"
# End Source File
# End Group
# Begin Group "Zlib Header"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Sources Zlib\deflate.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\infblock.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\infcodes.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\inffast.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\inffixed.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\inftrees.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\infutil.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\trees.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\zconf.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\zlib.h"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\zutil.h"
# End Source File
# End Group
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Jpeg Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Sources Jpeg\jcapimin.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcapistd.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jccoefct.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jccolor.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcdctmgr.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jchuff.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcinit.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcmainct.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcmarker.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcmaster.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcomapi.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcparam.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcphuff.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcprepct.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jcsample.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jctrans.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdapimin.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdapistd.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdatadst.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdatasrc.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdcoefct.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdcolor.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jddctmgr.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdhuff.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdinput.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdmainct.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdmarker.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdmaster.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdmerge.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdphuff.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdpostct.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdsample.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jdtrans.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jerror.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jfdctflt.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jfdctfst.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jfdctint.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jidctflt.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jidctfst.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jidctint.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jidctred.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jmemansi.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jmemmgr.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jquant1.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jquant2.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Jpeg\jutils.c"
# End Source File
# End Group
# Begin Group "Tiff Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Sources Tiff\fax3sm.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_aux.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_close.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_codec.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_compress.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_dir.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_dirinfo.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_dirread.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_dirwrite.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_dumpmode.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_error.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_fax3.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_file.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_flush.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_getimage.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_jpeg.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_lzw.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_msrc.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_next.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_open.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_packbits.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_predict.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_read.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_strip.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_swab.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_thunder.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_tile.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_warning.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Tiff\tif_write.c"
# End Source File
# End Group
# Begin Group "Png Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Sources Png\png.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngerror.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngget.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngmem.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngread.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngrio.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngrtran.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngrutil.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngset.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngtrans.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngwio.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngwrite.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngwtran.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Png\pngwutil.c"
# End Source File
# End Group
# Begin Group "Zlib Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\Sources Zlib\adler32.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\crc32.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\deflate.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\infblock.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\infcodes.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\inffast.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\inflate.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\inftrees.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\infutil.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\trees.c"
# End Source File
# Begin Source File

SOURCE=".\Sources Zlib\zutil.c"
# End Source File
# End Group
# End Group
# End Target
# End Project
