# Microsoft Developer Studio Project File - Name="mgl_test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=mgl_test - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "mgl_test.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "mgl_test.mak" CFG="mgl_test - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "mgl_test - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "mgl_test - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mgl_test - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\include\mgl_header" /I "..\msl\include" /I "..\mwl\include" /I "..\agh\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mgllib.lib /nologo /subsystem:windows /machine:I386 /out:"bin/mgl_test.exe" /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "mgl_test - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\include\mgl_header" /I "..\msl\include" /I "..\mwl\include" /I "..\agh\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mgllib.lib /nologo /subsystem:windows /debug /machine:I386 /out:"bin/mgl_test.exe" /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "mgl_test - Win32 Release"
# Name "mgl_test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mgl_test.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\AGH\include\agh.h
# End Source File
# Begin Source File

SOURCE=..\AGH\include\agh_ScreenBase.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "IS Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\AGH\include\agh_ControlBase.h
# End Source File
# Begin Source File

SOURCE=..\AGH\include\agh_Events.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\AugustEzGameFrame.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\AugustScreen.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\AugustWindow.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\auto_fp.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\BaseTsd.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8caps.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8types.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8core.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8effect.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8math.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8math.inl"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8mesh.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8shape.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8tex.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dls1.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmdls.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmerror.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmplugin.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusbuff.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusicc.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusici.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dxfile.h"
# End Source File
# Begin Source File

SOURCE=..\MWL\include\FileUtil.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\Guiddef.h"
# End Source File
# Begin Source File

SOURCE=..\MSL\include\int_string.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\mgl.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\mgl2d.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\mgl_common.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\mgl_global.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\mglafx.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglAghImage.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglAnimationLayer.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglAudio.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglBitmapData.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglBitmapText.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglBitmapTextLayer.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglBlinkLayer.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglClassMsg.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglDirectInputBase.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglDirectInputDeviceBase.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglDirectMusicBase.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglDrawLine.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglExceptionCode.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglExceptionThrowerBase.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglEzGameFrame.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglFadeLayer.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\mglframe.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglGraphicManager.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglGraphicUtil.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglguiScreen.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglguiWindow.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglImage.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglImageAnimator.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglImageCacher.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglImageFader.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglImageLayer.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglImageManager.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglImageTips.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglInput.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglJoyInput.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglJoyManager.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglKeyboardInput.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglKeyboardInputBase.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglLayerBase4.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglLayers4.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglManager.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglMouseInput.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglMouseInputBase.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\mglmsg.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglSprite.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglStandardTypes.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglText.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglTextLayer.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglTexture.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglTimer.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MglVertex.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\msl.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\msl_ra_list.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\msl_stlcommon.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslcharset.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslcommon.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslfile.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslfile2.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslnet.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslrand.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslstd.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslstl.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslstr.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\mslstr2.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\msltime.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwl.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwl_filedlg.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlcommon.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlfile.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MwlFileUtil.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlmsg.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlstd.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\mwlstd_ofn.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\myu_dynamic_string.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\myu_super_stream.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\MyuCharbuf.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuCharCnv.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MyuCommonException.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MyuDebugLog.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\MyuDynamicArray.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuDynamicDll.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MyuEzWindow.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\MyuFgets.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MyuFPS.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuIniReader.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuIniWriter.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MyuIntervalTimer.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuProcessManager.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuRegReader.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MyuReleaseBase.h
# End Source File
# Begin Source File

SOURCE=..\MSL\include\MyuSimpleStackTrace.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuSpecialIniReader.h
# End Source File
# Begin Source File

SOURCE=..\include\mgl_header\MyuStringNameMap.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuThreadBase.h
# End Source File
# Begin Source File

SOURCE=..\MWL\include\MyuThreadManager.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\PropIdl.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\Reason.h"
# End Source File
# Begin Source File

SOURCE=..\MSL\include\StlSerializer.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\StrAlign.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\Program Files\Microsoft SDK\include\Tvout.h"
# End Source File
# End Group
# End Target
# End Project
