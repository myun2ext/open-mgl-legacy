///////////////////////////////////////////////////////////////////////
//
//	MglGraphicManager  v0.10.62 05/03/10
//		- DirectX Graphics 管理クラス
//
//	v0.10.01 04/11/15
//	・ClearBackBuffer()追加
//
//	v0.10.02 04/12/09
//	・Release()にて落ちるバグ修正（m_pD3dDevのNULLチェック）
//
//	v0.10.20 04/12/13
//	・Direct3D CreateDevice() 時のフラグを指定できるように拡張
//
//	v0.10.21 04/12/13
//	・Paint()実装
//
//	v0.10.25 04/12/17
//	・SetAlphaBlendSetting() 等を廃止し、SetAlphaMode() を実装
//	・GetAlphaMode() を実装
//
//	v0.10.26 04/12/22
//	・DDS用のアルファオプションを実装してみる。
//
//	v0.10.30 05/01/04
//	・デバイス情報をダンプするように
//
//	v0.10.31 05/02/28
//	・バックバッファをクリアしておく
//
//	v0.10.60 05/02/28
//	・InitEx()、Direct3DCreate()の実装
//
//	v0.10.61 05/03/02
//	・m_format→m_formatTextureに。
//	　m_formatTextureの元がおかしかったので修正。
//
//	v0.10.62 05/03/10
//	・MGL_ALPHA_OPT_DEFAULT追加
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglGraphicManager_H__
#define __MglGraphicManager_H__

//#include "MyuDebugLog.h"
#include "MglManager.h"

#include "MglGraphicUtil.h"
#include "MyuReleaseBase.h"
#include "MglVertex.h"

/*
//	頂点構造体
#define	FVF_MYU_VERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
typedef struct
{
	float		x,y,z;				//位置情報
	float		rhw;				//頂点変換値
	D3DCOLOR	color;				//ポリゴンカラー
	float		tu,tv;				//テクスチャ座標
}MYU_VERTEX;
*/

//	Direct3D CreateDevice() 時の独自フラグ
#define D3D_DEVICE_FLG_T_AND_L_HAL	(0x00000001)
#define D3D_DEVICE_FLG_HAL			(0x00000002)
#define D3D_DEVICE_FLG_HW_SW_MIX	(0x00000004)
#define D3D_DEVICE_FLG_REF			(0x00000008)
#define D3D_DEVICE_MODE_DEFAULT		( D3D_DEVICE_FLG_T_AND_L_HAL | D3D_DEVICE_FLG_HAL )
#define D3D_DEVICE_MODE_AUTO		(0xffffffff)

//	アルファオプション
#define MGL_ALPHA_OPT_NOTUSE		(0)		//	なし
#define MGL_ALPHA_OPT_TRANSLUCENCE	(1)		//	半透明
#define MGL_ALPHA_OPT_ADD			(2)		//	加算
#define MGL_ALPHA_OPT_SUBTRACT		(3)		//	減算
#define MGL_ALPHA_OPT_HALFADD		(4)		//	半加算
#define MGL_ALPHA_OPT_DDS			(9)		//	DDS
#define MGL_ALPHA_OPT_NOCHANGE		(0xffffffff)	//	変更なし
#define MGL_ALPHA_OPT_DEFAULT		(MGL_ALPHA_OPT_TRANSLUCENCE)

//#define CAPS_DUMP_LOG				"MglDXGlphCaps.log"

extern int g_nSfcCount;
extern int g_2dgCount;

#define DELREF()	if( m_myudg != NULL && g_2dgCount > 0 ){ m_myudg->RmRefOfAutoRelease( this ); }else{}

class CMglTexture;
///////////////////////////////////////
//
//		クラス宣言
//
class DLL_EXP CMglGraphicManager
{
protected:
	//	DirectX系宣言
	_MGL_IDirect3D* m_pD3d;			//	D3D
	_MGL_IDirect3DDevice* m_pD3dDev;	//	D3Dデバイス

	int m_nDispX, m_nDispY;		//	画面サイズ
	D3DFORMAT m_formatTexture;	//	フォーマット
	DWORD m_dwD3dDeviceFlg;		//	Direct3Dデバイスのモード(T&L等)
	DWORD m_dwAlphaOption;		//	アルファオプション。GetAlphaMode()用に保持

	//	デバイス情報
	UINT m_nTexMem;				//	残りテクスチャメモリ
	DWORD m_dwMaxTextureHeight;	//	最大テクスチャ高さ
	DWORD m_dwMaxTextureWidth;	//	最大テクスチャ幅

	//	自動開放用配列
	map<CMyuReleaseBase*,CMyuReleaseBase*> m_autoReleaseAry;
	typedef map<CMyuReleaseBase*,CMyuReleaseBase*>::iterator AUTO_RELESE_ITR;

	//	2007/01/11  なんかスプライトとかSurfaceごとにいちいち作んなくてもインデネ
	ID3DXSprite* m_pSprite;			//	スプライト
	BOOL m_bUseSprite;
	//BOOL m_bSpriteCenterDraw;

	//////////////////////////////////////////////////////////////////////////

	//	内部的メソッド
	void Direct3DCreate();
	BOOL D3dCreateDevice( DWORD dwD3dDeviceFlg, D3DPRESENT_PARAMETERS* pPresentParam,
		int nAdapterNo=D3DADAPTER_DEFAULT, HWND hFocusWindow=NULL );
	void IsValidDisplayMode( int nWidth, int nHeight, D3DFORMAT Format, int nRefreshRate );
	//void GetVramInfo( DWORD *dwpTotal, DWORD *dwpFree );

public:
	//	公開メンバ変数
	D3DSURFACE_DESC backBufferDesc;		//	バックバッファ情報

	//////////////////////////
	//
	//		公開メソッド
	//

	//	コンストラクタ/デストラクタ
	CMglGraphicManager();
	virtual ~CMglGraphicManager();

	//	初期化/開放
	void Init( HWND hWnd, int nDispX, int nDispY, BOOL bFullscreen, D3DFORMAT formatTexture=D3DFMT_A8R8G8B8,
		DWORD dwD3dDeviceMode=D3D_DEVICE_MODE_AUTO, UINT nAdapterNo=D3DADAPTER_DEFAULT );
//		DWORD dwD3dDeviceMode=D3D_DEVICE_MODE_DEFAULT );
	void InitEx( D3DPRESENT_PARAMETERS* pPresentParam, DWORD dwD3dDeviceMode, D3DFORMAT formatTexture,
		int nAdapterNo, HWND hFocusWindow=NULL );

	void Release();

	//	便利系メソッド
	IDirect3DSurface8* GetBackBuffer()
	{
		IDirect3DSurface8* p;
		MyuAssert( m_pD3dDev->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &p ), D3D_OK,
			"CMglGraphicManager::GetBackBuffer()  GetBackBuffer()に失敗" );
		return p;
	}

	void SetRenderBackBuffer() {
		m_pD3dDev->SetRenderTarget( GetBackBuffer(), NULL );
	}

	/*	良く分からんので廃止、もとい SetAlphaMode() に統合
	void SetAlphaBlendSetting( DWORD alphaOp=D3DTOP_BLENDCURRENTALPHA );
	void EnabledAlphaBlend(); */
	void SetAlphaMode( DWORD dwAlphaOption=MGL_ALPHA_OPT_DEFAULT );

	void Clear( D3DCOLOR color=D3DCOLOR_BLACK );
	//void Clear( D3DCOLOR color=D3DCOLOR_NABLACK ); // 2007/02/11 NAだとマズくない…？
	void Paint( RECT* rect, D3DCOLOR color );
	void Paint( int left, int top, int right, int bottom, D3DCOLOR color ){
		RECT rect;
		rect.left = left;
		rect.top = top;
		rect.right = right;
		rect.bottom = bottom;
		Paint(&rect, color);
	}

	//	2007/01/11  スプライト描画
	void InitSprite();
	void SpriteDraw( CMglTexture *pTexture, float x=0, float y=0, CONST RECT* pSrcRect=NULL, D3DCOLOR color=D3DCOLOR_WHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f );
	//	float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=-1, float fRotationCenterY=-1, float fAngle=0.0f );
	/*void EnableCenterDraw() {	m_bSpriteCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bSpriteCenterDraw = FALSE; }*/
	void SpriteBegin(){ if( m_pSprite != NULL ) m_pSprite->Begin(); }
	void SpriteEnd(){ if( m_pSprite != NULL ) m_pSprite->End(); }

	//	シーン系メソッド
	void UpdateScreen();
	/*
	void BeginScene();
	void EndScene();
	void Present();
	*/

	//	自動開放用
	void AddRefOfAutoRelease( CMyuReleaseBase* pRef );
	void RmRefOfAutoRelease( CMyuReleaseBase* pRef );

	//	プロパティ系メソッド
	int GetDispX() { return m_nDispX; }
	int GetDispY() { return m_nDispY; }
	int GetWidth() { return m_nDispX; }
	int GetHeight() { return m_nDispY; }
	D3DFORMAT GetFormat() { return m_formatTexture; }
	_MGL_IDirect3DDevice* GetD3dDevPtr() { return m_pD3dDev; }
	_MGL_IDirect3DDevice* GetD3dDevice() { return m_pD3dDev; }
	DWORD GetD3dDeviceFlg() { return m_dwD3dDeviceFlg; }
	DWORD GetAlphaMode() { return m_dwAlphaOption; }
	void EnableSupportSprite(){ m_bUseSprite = TRUE; }
	void DisableSupportSprite(){ m_bUseSprite = FALSE; }
};

////////////////////////////////////////////////////////////
//
//	デフォルト CMglGraphicManager インスタンス関連
//
extern CMglGraphicManager *g_pDefaultGd;	//	旧世代のクラス用に残しておくだけ

//	2007/01/03  新しいインターフェース（エラーチェックつき）
DLL_EXP CMglGraphicManager* GetDefaultGd();

//	チェック
inline BOOL CheckDefaultGd()
{
	if ( g_pDefaultGd == NULL )
		return FALSE;
	return TRUE;
}

#endif//__MglGraphicManager_H__
