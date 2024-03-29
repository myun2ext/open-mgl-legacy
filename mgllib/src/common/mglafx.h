//////////////////////////////////////////////////////////
//
//	Myu Game Library  05/03/10 v0.19.40
//
//////////////////////////////////////////////////////////

#ifndef __mglafx_H__
#define __mglafx_H__

#include <windows.h>

#ifndef __int3264
    typedef long LONG_PTR;
#endif

//DWORD_PTR だっけ

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
	#define DLL_TMPL_EXP template class DLL_EXP			//	C4275対応
	//#define DLL_TMPL_EXTERN
	//#define DLL_TMPL_EXTERN template
#else
	#define DLL_EXP __declspec(dllimport)
	#define DLL_TMPL_EXP /*extern*/ template class DLL_EXP	//	C4275対応
	//#define DLL_TMPL_EXTERN extern
	//#define DLL_TMPL_EXTERN extern template
#endif
/*
  DLL_TMPL_EXP: テンプレートのエクスポート
    http://support.microsoft.com/default.aspx?scid=kb;ja-jp;168958
*/

/*	//	ソースで使用したい場合。あとまわし
#ifndef DLL_EXP
#define DLL_EXP
#endif
*/

/////////////////////////////////////

#pragma warning( disable : 4251 )	//	template classのエクスポートしてるのにワーニングが出てしまうので消す

//	for VC++2008 Warning disable
#pragma warning( disable : 4018 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4995 )
#pragma warning( disable : 4996 )

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
//#include "MyuDebugLog.h"	//	2008/06/30  mgl_common.h に移動
//#include "MglException.h"	//	2009/11/14  DirectXヘッダ読み込み後に移動
#include "MyuCommonException.h"
#include "MglExceptionThrowerBase.h"
#include "MglExceptionCode.h"
#include "mglmsg.h"
//#include "MglClassMsg.h"	//	2008/06/30  mgl_common.h に移動
#include "MyuReleaseBase.h"

//	2008/06/30  mgl_common.h に移動
//extern CMyuDebugLog g_workLog;

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

#ifndef _MGL_DXVER
	//#define _MGL_DXVER 8
	#define _MGL_DXVER 9
	//#define _MGL_DXVER 10
#endif

/*
#ifndef D3DX_VERSION
	#define _MGL_D3DXVER 0x0800
	#define _MGL_DXXVER 0x0800
#else
	#define _MGL_D3DXVER D3DX_VERSION
	#define _MGL_DXXVER D3DX_VERSION
#endif
*/

//	DirectX 9
//#ifdef _MGL_USE_DXVER9
#if _MGL_DXVER == 9
	#pragma comment(lib, "D3d9.lib")
	#pragma comment(lib, "D3dx9.lib")
	#include <D3d9.h>
	#include <D3dx9core.h>
	#include <D3dx9effect.h>

	#pragma comment(lib, "dinput8.lib")
	#define DIRECTINPUT_VERSION		(0x0800)
	#define _MGL_IDirectInput IDirectInput8
	#define _MGL_IDirectInputDevice IDirectInputDevice8
	//#define IID_IDIRECT_INPUT	IID_IDirectInputDevice8

	typedef IDirect3D9 _MGL_IDirect3D;
	typedef IDirect3DDevice9 _MGL_IDirect3DDevice;
	typedef IDirect3DSurface9 _MGL_IDirect3DSurface;
	typedef IDirect3DTexture9 _MGL_IDirect3DTexture;
	typedef IDirect3DVertexBuffer9 _MGL_IDirect3DVertexBuffer;
	typedef IDirect3D9 _IDirect3DX;
	typedef IDirect3DDevice9 _IDirect3DDeviceX;
	typedef IDirect3DSurface9 _IDirect3DSurfaceX;
	typedef IDirect3DTexture9 _IDirect3DTextureX;
	typedef IDirect3DVertexBuffer9 _IDirect3DVertexBufferX;
	typedef IDirect3DPixelShader9 _IDirect3DPixelShaderX;
	typedef IDirect3DVertexShader9 _IDirect3DVertexShaderX;
	typedef D3DVIEWPORT9 _D3DVIEWPORTx;
	typedef D3DCAPS9 _D3DCAPSx;
	typedef D3DADAPTER_IDENTIFIER9 _D3DADAPTER_IDENTIFIERx;
	typedef D3DMATERIAL9 _D3DMATERIALx;
	typedef D3DLIGHT9 _D3DLIGHTx;

//	DirectX10
//#elif _MGL_USE_DXVER10
#elif _MGL_DXVER == 10
	#pragma comment(lib, "D3d10.lib")
	#pragma comment(lib, "D3dx10.lib")
	#include <D3d10.h>
	#include <D3dx10core.h>

	#pragma comment(lib, "dinput10.lib")
	#define DIRECTINPUT_VERSION		(0x1000)
	#define _MGL_IDirectInput IDirectInput10
	#define _MGL_IDirectInputDevice IDirectInputDevice10
	//#define IID_IDIRECT_INPUT	IID_IDirectInputDevice10

	typedef IDirect3D10 _MGL_IDirect3D;
	typedef IDirect3DDevice10 _MGL_IDirect3DDevice;
	typedef IDirect3DSurface10 _MGL_IDirect3DSurface;
	typedef IDirect3DTexture10 _MGL_IDirect3DTexture;
	typedef IDirect3D10 _IDirect3DX;
	typedef IDirect3DDevice10 _IDirect3DDeviceX;
	typedef IDirect3DSurface10 _IDirect3DSurfaceX;
	typedef IDirect3DTexture10 _IDirect3DTextureX;
	typedef D3DVIEWPORT10 _D3DVIEWPORTx;
	typedef D3DCAPS10 _D3DCAPSx;
	typedef D3DADAPTER_IDENTIFIER10 _D3DADAPTER_IDENTIFIERx;
	
//	DirectX8
#else
	#pragma comment(lib, "D3d8.lib")
	#pragma comment(lib, "D3dx8.lib")
	#include <D3d8.h>
	#include <D3dx8core.h>
	#include <D3dx8effect.h>

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
	typedef IDirect3DVertexBuffer8 _MGL_IDirect3DVertexBuffer;
	typedef IDirect3D8 _IDirect3DX;
	typedef IDirect3DDevice8 _IDirect3DDeviceX;
	typedef IDirect3DSurface8 _IDirect3DSurfaceX;
	typedef IDirect3DTexture8 _IDirect3DTextureX;
	typedef IDirect3DVertexBuffer8 _IDirect3DVertexBufferX;
	//typedef IDirect3DPixelShader8 _IDirect3DPixelShaderX;
	//typedef DWORD _IDirect3DPixelShaderX;
	typedef D3DVIEWPORT8 _D3DVIEWPORTx;
	typedef D3DCAPS8 _D3DCAPSx;
	typedef D3DADAPTER_IDENTIFIER8 _D3DADAPTER_IDENTIFIERx;
	typedef D3DMATERIAL8 _D3DMATERIALx;
	typedef D3DLIGHT8 _D3DLIGHTx;

	#define _MGL_D3DXVER 0x0800
	#define _MGL_DXXVER 0x0800
#endif
	
#ifndef _MGL_D3DXVER
	#define _MGL_D3DXVER D3DX_VERSION
	#define _MGL_DXXVER D3DX_VERSION
#endif

#define MGL_D3DXVER_ID3DXFONT_CHANGED	0x0902
#define MGL_D3DXVER_ID3DXSPRITE_CHANGED	0x0902
#define MGL_D3DXVER_ID3DXEFFECT_CHANGED	0x0902


//	2009/11/14  DirectX読み込み後に移動
#include "MglException.h"


#include <dinput.h>

//	DirectMusic系
//#include <dsound.h>		//	dsound.lib
#include <dmusici.h>
#pragma comment(lib, "dxguid.lib")


//	DirectShow
#include <DShow.h>

//	Strmbase.lib / strmiids.lib
#if _MGL_DXVER == 8

	//	DirectX8 はSDK内に普通に Strmbase.lib / Strmbasd.lib が入ってた。（ハズ
	#ifdef _DEBUG
		#pragma comment(lib, "Strmbasd.lib")
	#else
		#pragma comment(lib, "Strmbase.lib")
	#endif//_DEBUG

#else

	//	DirectX9 以降はPlatformSDKのを使う事になる。
	//	ネットで検索すると「Strmbase.lib・Strmbasd.lib を自前でSampleより生成」とか書かれてたりするが、
	//	「なんでSample・・・？おかしいなぁ・・・」と思って調べてみたところ、PlatformSDK Lib内、「strmiids.lib」
	//	だけがあれば良いみたい。


	//	…でも（PlatformSDKを）インストールとかメンドイんで、
	//	USE_MGLSTRMIIDS が定義されてたら自前の MglStrmiids.lib を使っちゃうよ

	#ifdef USE_MGLSTRMIIDS
		#pragma comment(lib, "MglStrmiids.lib")
	#else
		#pragma comment(lib, "strmiids.lib")
	#endif

#endif


////////////////////////////////////////////////////////////

#endif//_MGL_NOUSE_DIRECTX


/////////////////////////////////////
//
//			その他のマクロ等
//

#define NSMGLEX_START	namespace mglex {
#define NSMGLEX_END		}
#define NSMGLX_START	namespace mglex {
#define NSMGLX_END		}

/*
//	便利マクロくん
#define SAFE_DELETE(p)		{if( p != NULL ){ delete (p);		(p)=NULL; }}
#define SAFE_DELETE_ARY(p)	{if( p != NULL ){ delete (p)[];		(p)=NULL; }}
*/
#define SAFE_RELEASE(p)		{if( p != NULL ){ (p)->Release();	(p)=NULL; }}

template <typename T> class auto_release
{
protected:
	typename T m_ptr;
public:
	auto_release(){ m_ptr = NULL; }
	auto_release(typename T p){ m_ptr = p; }
	virtual ~auto_release(){ Release(); }

	void Release(){ m_ptr->Release(); }

	operator typename T(){ return m_ptr; }
	T* operator &(){ return &m_ptr; }
	T operator ->(){ return m_ptr; }
};

//	オマケ。数学マクロ
/*#define MGL_PI		(3.1415926)
#define AngleToRad(V)	(V * MGL_PI / 180)
#define RadToAngle(V)	(V * 180 / MGL_PI)*/
#define MGL_PI			D3DX_PI
#ifndef AngleToRad
	#define AngleToRad(V)	D3DXToRadian(V)
#endif
#ifndef RadToAngle
	#define RadToAngle(V)	D3DXToDegree(V)
#endif

#define HYPER_CLASS_TYPEDEF(FROM,TO)	class TO: public FROM{};

typedef struct {
	float f1;
	float f2;
	/*union _uf1{
		float f1;
		float tu;
	} _f1;
	union _uf2{
		float f2;
		float tv;
	} _f2;*/
} MGLFLOAT2;

typedef struct {
	float tu;
	float tv;
} MGLTUTV;

#endif//__mglafx_H__
