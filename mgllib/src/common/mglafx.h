//////////////////////////////////////////////////////////
//
//	Myu Game Library  05/03/10 v0.19.40
//
//////////////////////////////////////////////////////////

#ifndef __mglafx_H__
#define __mglafx_H__

/*
#define MGLVER_DATE	(0x050129)
#define MGLVER_REV	(0x02)
#define MGLVER	(MGLVER_DATE*100 + MGLVER_REV)
*/

//////////////////////
//
//	DLLエクスポート
//

#ifdef MGLLIB_EXPORTS
	#define DLL_EXP __declspec(dllexport)
#else
	#define DLL_EXP __declspec(dllimport)
#endif

/*	//	ソースで使用したい場合。あとまわし
#ifndef DLL_EXP
#define DLL_EXP
#endif
*/

/////////////////////////////////////

#pragma warning( disable : 4251 )	//	template classのエクスポートしてるのにワーニングが出てしまうので消す

//	なんで除外してあんだろ (2008/06/01)
#include <msl.h>	//	07/01/01 Add.
#include <mwl.h>	//	07/01/02 Add.

//#include "mglstd.h"

/*
// VC でのSTLの警告を取り除きます。
#pragma warning( disable : 4786 ) 
//#pragma warning( disable : 4251 )	//	template class でexportしてるのに出すなょｳｾﾞｰ(;´Д`)ゞ

#include <string>
#include <vector>
#include <map>
using namespace std;

#include <stdio.h>
#include <windows.h>*/
#include "MyuDebugLog.h"
#include "MyuCommonException.h"
#include "MglExceptionThrowerBase.h"
#include "MglExceptionCode.h"
#include "mglmsg.h"
#include "MglClassMsg.h"
#include "MyuReleaseBase.h"

extern CMyuDebugLog g_workLog;

//	timeGetTime()用
#pragma comment(lib, "winmm.lib")

//	MGLマネージャ
/*
#define _MGL_MANAGER_INSTANCE	_g_mglManager
#define _EXTERN_MGL_MANAGER		extern CMglManager _MGL_MANAGER_INSTANCE
#define _MGL_DEBUGLOG			_MGL_MANAGER_INSTANCE.g_debugLog.Print
*/


#ifndef _MGL_NOUSE_DIRECTX
/////////////////////////////////////
//
//			DirectX 関連
//

//	VC標準だとDWORD_PTR無いくせー。(´Д`;)
#include <dplay.h>	//	コイツの中にある臭いので引っ張ってくる

/*
//	Direct3D系
#pragma comment(lib, "D3d8.lib")
#pragma comment(lib, "D3dx8.lib")
#include <D3d8.h>
#include <D3dx8core.h>
*/

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

/*
//	DirectInput系
#pragma comment(lib, "dinput8.lib")
#define DIRECTINPUT_VERSION		(0x0800)
#include <dinput.h>
*/
//	DirectInput系
#ifdef _MGL_USE_DXVER9
	#pragma comment(lib, "dinput9.lib")
	#define DIRECTINPUT_VERSION		(0x0900)
	#define _MGL_IDirectInput IDirectInput9
	#define _MGL_IDirectInputDevice IDirectInputDevice9
	//#define IID_IDIRECT_INPUT	IID_IDirectInputDevice9

#elif _MGL_USE_DXVER10
	#pragma comment(lib, "dinput10.lib")
	#define DIRECTINPUT_VERSION		(0x1000)
	#define _MGL_IDirectInput IDirectInput10
	#define _MGL_IDirectInputDevice IDirectInputDevice10
	//#define IID_IDIRECT_INPUT	IID_IDirectInputDevice10
	
#else
	#pragma comment(lib, "dinput8.lib")
	#define DIRECTINPUT_VERSION		(0x0800)
	#define _MGL_IDirectInput IDirectInput8
	#define _MGL_IDirectInputDevice IDirectInputDevice8
	//#define IID_IDIRECT_INPUT	IID_IDirectInputDevice8

	/*#define _MGL_IDirect3D IDirect3D8
	#define _MGL_IDirect3DDevice IDirect3DDevice8
	#define _MGL_IDirect3DSurface IDirect3DSurface8
	#define _MGL_IDirect3DTexture IDirect3DTexture8*/
	typedef IDirect3D8 _MGL_IDirect3D;
	typedef IDirect3DDevice8 _MGL_IDirect3DDevice;
	typedef IDirect3DSurface8 _MGL_IDirect3DSurface;
	typedef IDirect3DTexture8 _MGL_IDirect3DTexture;
#endif

#include <dinput.h>

//	DirectMusic系
//#include <dsound.h>		//	dsound.lib
#pragma comment(lib, "dxguid.lib")
#include <dmusici.h>

#endif//_MGL_NOUSE_DIRECTX


/////////////////////////////////////
//
//			その他のマクロ等
//

/*
//	便利マクロくん
#define SAFE_DELETE(p)		{if( p != NULL ){ delete (p);		(p)=NULL; }}
#define SAFE_DELETE_ARY(p)	{if( p != NULL ){ delete (p)[];		(p)=NULL; }}
*/
#define SAFE_RELEASE(p)		{if( p != NULL ){ (p)->Release();	(p)=NULL; }}

//	オマケ。数学マクロ
#define MGL_PI			(3.1415926)
#define AngleToRad(V)	(V * MGL_PI / 180)
#define RadToAngle(V)	(V * 180 / MGL_PI)

#define HYPER_CLASS_TYPEDEF(FROM,TO)	class TO: public FROM{};

#endif//__mglafx_H__
