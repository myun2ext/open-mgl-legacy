#ifndef __mgl2d_H__
#define __mgl2d_H__

#include "mglafx.h"

/*
//////////////////////
//
//	DLLエクスポート
//

#ifdef MGLLIB_EXPORTS
	#define DLL_EXP __declspec(dllexport)
#else
	#define DLL_EXP __declspec(dllimport)
#endif

/////////////////////////////////////

/*#include <msl.h>	//	07/01/01 Add.
#include <mwl.h>	//	07/01/02 Add.*//*

//#include "mglstd.h"

// VC でのSTLの警告を取り除きます。
#pragma warning( disable : 4786 ) 
#pragma warning( disable : 4251 )	//	template class でexportしてるのに出すなょｳｾﾞｰ(;´Д`)ゞ

#include <string>
#include <vector>
#include <map>
using namespace std;

#include <stdio.h>
#include <windows.h>
//#include "MyuDebugLog.h"
#include "MyuCommonException.h"
#include "MglExceptionThrowerBase.h"
#include "mglmsg.h"

//extern CMyuDebugLog g_workLog;

*/

//	MGLマネージャ
/*
#define _MGL_MANAGER_INSTANCE	_g_mglManager
#define _EXTERN_MGL_MANAGER		extern CMglManager _MGL_MANAGER_INSTANCE
#define _MGL_DEBUGLOG			_MGL_MANAGER_INSTANCE.g_debugLog.Print
*/

/*
//	Direct3D系
#ifdef _MGL_USE_DXVER9
	#pragma comment(lib, "D3d9.lib")
	#pragma comment(lib, "D3dx9.lib")
	#include <D3d9.h>
	#include <D3dx9core.h>

#elif _MGL_USE_DXVER10
	#pragma comment(lib, "D3d10.lib")
	#pragma comment(lib, "D3dx10.lib")
	#include <D3d10.h>
	#include <D3dx10core.h>

#else
	#pragma comment(lib, "D3d8.lib")
	#pragma comment(lib, "D3dx8.lib")
	#include <D3d8.h>
	#include <D3dx8core.h>
#endif
*/

#include "MglGraphicManager.h"
#include "MglGraphicUtil.h"

#include "MglVertex.h"
#include "MglTexture.h"
#include "MglImage.h"
#include "MglSprite.h"

#include "MglImageTips.h"
#include "MglImageCacher.h"
#include "MglImageManager.h"
#include "MglImageFader.h"
#include "MglImageAnimator.h"

#include "MglLayer.h"
#include "MglLayers4.h"
#include "MglBitmapText.h"
#include "MglText.h"
#include "MglDrawLine.h"

#include "MglImageLayer.h"
#include "MglTextLayer.h"
#include "MglBitmapTextLayer.h"
#include "MglAnimationLayer.h"
#include "MglFadeLayer.h"
#include "MglBlinkLayer.h"


typedef CMglLayers4 CMglLayers;

#endif//__mgl2d_H__
