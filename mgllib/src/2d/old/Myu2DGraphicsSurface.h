//////////////////////////////////////////////////////////
//
//	Myu2DGraphicsSurface - 画像イメージ管理クラス
//
//	v0.10.20 04/11/19
//	・Createのチェックが入っていなかった！！_|￣|○
//	・CopyRect系を修正。
//
//	v0.10.21 04/11/22
//	・Get～系メソッドにチェック追加。
//
//	v0.10.25 04/12/14
//	・中心基点絵画機能追加。
//
//	v0.10.26 04/12/16
//	・中心基点絵画機能、RECTを使用した場合ちゃんと
//	　表示されないバグを修正。
//
//	v0.10.32 04/12/17
//	・DrawEx()にアルファオプションを追加
//	・GetBmpSizeX(), GetBmpSizeY()追加
//
//	v0.20.00 05/03/03
//	・基本機能がCMyu2DGraphicsSurfacePrimitiveへ分離
//
//	v0.40.00 06/11/25
//	・CMyu2DGraphicsSurfaceへ名称変更。
//
//////////////////////////////////////////////////////////

#ifndef __Myu2DGraphicsSurface_H__
#define __Myu2DGraphicsSurface_H__

//#include <D3dx8tex.h>		stdafxへ

#include "MglGraphicManager.h"
#include "MglTexture.h"	//	2007/01/10  MglTexture と二重定義になるので…

#define X_ADJ (-0.66f)
#define Y_ADJ (-0.96f)
/*	2007/01/10  MglTexture と二重定義になるので…
//#define X_ADJ (0)
//#define Y_ADJ (0)
#define DEF_COLORKEY	D3DCOLOR_PINK

#define VERTEXNO_LT		(0)
#define VERTEXNO_RT		(1)
#define VERTEXNO_LB		(3)
#define VERTEXNO_RB		(2)

//	頂点色
typedef struct
{
	D3DCOLOR leftTop;
	D3DCOLOR leftBottom;
	D3DCOLOR rightTop;
	D3DCOLOR rightBottom;
}
VERTEX_COLORS;
*/

//	クラス宣言
class DLL_EXP CMyu2DGraphicsSurface : public CMyuReleaseBase	//	CMglDirect3dTexture
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	IDirect3DDevice8* d3d;			//	D3DDeviceへのポインタ
	BOOL m_bRenderTarget;			//	bRenderTargetのコピー

	int m_nBmpSizeX, m_nBmpSizeY;	//	BMPのサイズ
	int nRealSizeX, nRealSizeY;		//	実サイズ(テクスチャ上のサイズ)
	float fRealTexTu, fRealTexTv;	//	テクスチャ上で実際に使用されるtu,uv
	D3DCOLOR m_colorKey;			//	カラーキー
	BOOL m_bCenterDraw;				//	センター絵画有効/無効フラグ

	MYU_VERTEX m_vertices[4];		//	頂点

	IDirect3DTexture8* m_pTexture;	//	テクスチャ
	IDirect3DSurface8* m_pSurface;	//	サーフェス
	ID3DXSprite* m_pSprite;			//	スプライト

	int m_nSfcID;

	string m_sfcName;				//	関連付けられた名前

	//	Init/Createチェック
	BOOL initFlg;					//	初期化フラグ
	BOOL createFlg;					//	Createフラグ

	void InitCheck() {
		/*
		if ( initFlg == FALSE ){
			if ( m_sfcName != "" )
				MyuThrow( 0, "MglSurface[%s]::Init()を一番最初に呼んでください。", m_sfcName.c_str() );
			else
				MyuThrow( 0, "MglSurface::Init()を一番最初に呼んでください。" );
		}
		*/

		//	2007/01/09
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}
	void CreateCheck() {
		if ( createFlg == FALSE ){
			if ( m_sfcName != "" )
				MyuThrow( 0, "MglSurface[%s]::Create()を呼んでください。", m_sfcName.c_str() );
			else
				MyuThrow( 0, "MglSurface::Create()を呼んでください。" );
		}
	}
public:
	//	コンストラクタ・デストラクタ
	CMyu2DGraphicsSurface();
	virtual ~CMyu2DGraphicsSurface();

	void Init( CMglGraphicManager* in_myudg, const char* szName=NULL );
	void Release();

	//	過去との互換のために存続
	void CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget=TRUE, D3DCOLOR colorKey=DEF_COLORKEY );

	void Create( int x=0, int y=0, BOOL bRenderTarget=TRUE );
	void Create( LPCSTR szFileName, BOOL bRenderTarget=TRUE, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFile( szFileName, bRenderTarget, colorKey );}
	
	//	Drawの基本
	void TextureDraw( float x, float y, RECT* srcRect, float fScaleX, float fScaleY, D3DCOLOR color, DWORD dwAlphaOption=MGL_ALPHA_OPT_DEFAULT )
	{
		VERTEX_COLORS tVertexColors;
		GenerateEqVertexColors( &tVertexColors, color );
		TextureDraw( x, y, srcRect, fScaleX, fScaleY, 0.5f, 0.5f, 0.0f, &tVertexColors, dwAlphaOption );
	}

	//	最終的に↓のようなサポートにする予定
	void TextureDraw( float x, float y, RECT* srcRect, float fScaleX, float fScaleY,
		float fRotationCenterX, float fRotationCenterY, float fAngle,
		VERTEX_COLORS* vertexColors, DWORD dwAlphaOption );

	//void TextureDraw( float x=0.0f, float y=0.0f, float fSizeX=1.0f, float fSizeY=1.0f, D3DCOLOR color=0xffffffff );
	void TextureDrawPrimitive();

	/*void TextureDraw( float x=0.0f, float y=0.0f, float fSizeX=1.0f, float fSizeY=1.0f, D3DCOLOR color=0xffffffff )
		{}*/

	/////////////////////////////////////////////////////////////////////////////////////////////

	//	Draw
	void Draw( CMyu2DGraphicsSurface* destSurface, float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		{ destSurface->SetRender(); Draw( x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 多分これも必要
		}
	void Draw( float x=0, float y=0, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
	{ CMyu2DGraphicsSurface::DrawEx( 1.0f, 1.0f, 0.5f, 0.5f, 0, x, y, srcRect, color ); }

	//	2007/02/12  DrawEx() 引数並び替え

	//	DrawEx - スプライトを使うバージョン
	void DrawEx( CMyu2DGraphicsSurface* destSurface, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE )
		//{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color, dwAlphaOption );
		{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 多分これも必要
		}
	void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff );
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE );

	/*
	//	DrawEx - スプライトを使うバージョン
	void DrawEx( CMyu2DGraphicsSurface* destSurface, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE )
		//{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color, dwAlphaOption );
		{ destSurface->SetRender(); DrawEx( fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 多分これも必要
		}
	void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff );
		//float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE );
	*/

	/*	TextureDrawを使うバージョン
	void DrawEx( float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_NOCHANGE )
	{
		VERTEX_COLORS tVertexColors;
		GenerateEqVertexColors( &tVertexColors, color );
		TextureDraw( x, y, srcRect, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle, &tVertexColors, 0 );
	}
	*/
	
	//	CopyRect系
	void CopyRectToOther( CMyu2DGraphicsSurface* destSurface, RECT *srcRect=NULL, int x=0, int y=0 );
	void CopyRectToThis( CMyu2DGraphicsSurface* srcSurface, RECT *srcRect=NULL, int x=0, int y=0 );
	//void CopyRect( int x=0, int y=0, RECT *srcRect=NULL );

	//	センター絵画
	void EnableCenterDraw() {	m_bCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bCenterDraw = FALSE; }

	//	グラデーション
	//void SetGradation() { SetGradation(0xffffffff,0xffffffff,0xffffffff,0xffffffff); }
	//void SetGradation( D3DCOLOR colorLeftTop, D3DCOLOR colorRightTop, D3DCOLOR colorLeftBottom, D3DCOLOR colorRightBottom );

	void GenerateEqVertexColors( VERTEX_COLORS* dest, D3DCOLOR color )
	{
		for( D3DCOLOR* p=(D3DCOLOR*)dest; p<((D3DCOLOR*)dest)+4; p++ )
		{
			*p = color;
		}

		/*
		dest->leftTop = color;
		dest->leftBottom = color;
		dest->rightTop = color;
		dest->rightBottom = color;
		*/
	}

	void SetRender();
	void Clear(){ Clear( m_colorKey & 0x00ffffff ); } // m_colorKeyが関連するのでデフォルト引数には出来ないのでれす
	void Clear( D3DCOLOR color );
	void Paint( RECT* rect, D3DCOLOR color );

	//	プロパティ系メソッド
	IDirect3DTexture8* GetTexturePtr() { CreateCheck(); return m_pTexture; }
	IDirect3DSurface8* GetSurfacePtr() { CreateCheck(); return m_pSurface; }
	ID3DXSprite* GetSpritePtr() { CreateCheck(); return m_pSprite; }
	MYU_VERTEX* GetVerticesPtr() { CreateCheck(); return m_vertices; }
	int GetBmpSizeX() { return m_nBmpSizeX; }
	int GetBmpSizeY() { return m_nBmpSizeY; }

	//	デバッグ用に名前を付ける
	void SetName( const char* szName ){ m_sfcName = szName; }
};

typedef CMyu2DGraphicsSurface CMglBitmap;
typedef CMyu2DGraphicsSurface CMglSprite;

#endif//__Myu2DGraphicsSurface_H__
