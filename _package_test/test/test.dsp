# Microsoft Developer Studio Project File - Name="test" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=test - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "test.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "test.mak" CFG="test - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "test - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "test - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "test - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "..\openmgl\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mgllib.lib /nologo /subsystem:windows /machine:I386 /out:"bin/test.exe" /libpath:"..\openmgl\lib"

!ELSEIF  "$(CFG)" == "test - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\openmgl\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib mgllib.lib /nologo /subsystem:windows /debug /machine:I386 /out:"bin/test.exe" /pdbtype:sept /libpath:"..\openmgl\lib"

!ENDIF 

# Begin Target

# Name "test - Win32 Release"
# Name "test - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\test.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\openmgl\include\agh.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\agh_ControlBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\agh_Events.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\agh_ScreenBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\AugustEzGameFrame.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\AugustScreen.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\AugustWindow.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\auto_fp.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft SDK\include\BaseTsd.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8caps.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3d8types.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8core.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8effect.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8math.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8math.inl"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8mesh.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8shape.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\d3dx8tex.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dls1.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmdls.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmerror.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmplugin.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusbuff.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusicc.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dmusici.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft DirectX 9.0 SDK (October 2004)\Include\dxfile.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft SDK\include\Guiddef.h"
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\int_string.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mgl.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mgl2d.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mgl_common.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mglafx.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglAghImage.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglAnimationLayer.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglAudio.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglBitmapData.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglBitmapText.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglBitmapTextLayer.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglBlinkLayer.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglClassMsg.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglDirectInputBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglDirectInputDeviceBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglDirectMusicBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglDrawLine.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglExceptionCode.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglExceptionThrowerBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglEzGameFrame.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglFadeLayer.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mglframe.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglGraphicManager.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglGraphicUtil.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglguiScreen.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglguiWindow.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglImage.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglImageAnimator.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglImageCacher.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglImageFader.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglImageLayer.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglImageManager.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglImageTips.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglInput.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglJoyInput.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglJoyManager.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglKeyboardInput.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglKeyboardInputBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglLayerBase4.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglLayers4.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglManager.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglMouseInput.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglMouseInputBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mglmsg.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglOgg.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglSprite.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglStandardTypes.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglText.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglTextLayer.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglTexture.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglTimer.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MglVertex.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\msl.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\msl_ra_list.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\msl_stlcommon.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslcharset.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslcommon.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslfile.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslfile2.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslnet.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslrand.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslstd.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslstl.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslstr.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mslstr2.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\msltime.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mwl.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mwl_filedlg.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mwlcommon.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mwlfile.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MwlFileUtil.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mwlmsg.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mwlstd.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\mwlstd_ofn.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\myu_dynamic_string.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\myu_super_stream.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuCharbuf.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuCharCnv.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuCommonException.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuDebugLog.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuDynamicArray.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuDynamicDll.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuEzWindow.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuFgets.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuFPS.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuIniReader.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuIniWriter.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuIntervalTimer.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuProcessManager.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuRegReader.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuReleaseBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuSimpleStackTrace.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuSpecialIniReader.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuStringNameMap.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuThreadBase.h
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\MyuThreadManager.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft SDK\include\PropIdl.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft SDK\include\Reason.h"
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\StlSerializer.h
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft SDK\include\StrAlign.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\..\..\Program Files\Microsoft SDK\include\Tvout.h"
# End Source File
# Begin Source File

SOURCE=..\openmgl\include\Vox.h
# End Source File
# End Group
# End Target
# End Project
