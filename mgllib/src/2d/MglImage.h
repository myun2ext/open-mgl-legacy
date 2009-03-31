//////////////////////////////////////////////////////////
//
//	MglImage - 画像イメージ管理クラス
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
//	・基本機能がCMglImagePrimitiveへ分離
//
//	v0.40.00 06/11/25
//	・CMglImageへ名称変更。
//
//	v0.60.00 07/02/12
//	・CMglTextureを使う形式に
//
//////////////////////////////////////////////////////////

#ifndef __MglImage_H__
#define __MglImage_H__

#include "MglGraphicManager.h"
#include "MglTexture.h"
#include "MglLayerBase4.h"

//	クラス宣言
//class DLL_EXP CMglImage : public CMglTexture
class DLL_EXP CMglImage : public CMglTexture//, public CMglLayerBase4
{
protected:
	int m_nSfcID;
	string m_sfcName;		//	関連付けられた名前

	//IDirect3DSurface8* m_pSurface;//	サーフェス（CopyRect用）

	BOOL m_bCenterDraw;		//	センター絵画有効/無効フラグ

public:
	//	コンストラクタ・デストラクタ
	CMglImage();
	CMglImage( LPCSTR szFileName ){
		m_nSfcID = g_nSfcCount;
		g_nSfcCount++;
		Create( szFileName );
	}
	virtual ~CMglImage();

	//	Create
	void CreateFromFile( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CMglTexture::CreateTextureFromFile( szFileName, bRenderTarget, colorKey ); }
	void Create( BOOL bRenderTarget=RENDER_TARGET_DEFAULT ){ CMglTexture::Create(0,0,bRenderTarget); }
	void Create( int x, int y, BOOL bRenderTarget=RENDER_TARGET_DEFAULT ){ CMglTexture::Create(x,y,bRenderTarget); }
	void Create( LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CreateFromFile( szFileName, bRenderTarget, colorKey ); }

	//	Create - CMglGraphicManager* in_myudg 有り版
	void CreateFromFile( CMglGraphicManager* in_myudg,
		LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY )
	{
		CMglTexture::Init(in_myudg);
		CMglTexture::CreateTextureFromFile( szFileName, bRenderTarget, colorKey );
	}
	void Create( CMglGraphicManager* in_myudg, BOOL bRenderTarget=RENDER_TARGET_DEFAULT ){
		CMglTexture::Init(in_myudg); CMglTexture::Create(0,0,bRenderTarget); }
	void Create( CMglGraphicManager* in_myudg, int x, int y, BOOL bRenderTarget=RENDER_TARGET_DEFAULT ){
		CMglTexture::Init(in_myudg); CMglTexture::Create(x,y,bRenderTarget); }
	void Create( CMglGraphicManager* in_myudg,
		LPCSTR szFileName, BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY ){
		CMglTexture::Init(in_myudg); CreateFromFile( szFileName, bRenderTarget, colorKey ); }

	/////////////////////////////////////////////////////////////////////////////////////////////

	void Draw(){ Draw(0,0); }
	void Draw(
		float x, float y, CONST RECT *pSrcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f );
	void Draw( CMglImage* destSurface,
		float x, float y, CONST RECT *pSrcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		destSurface->SetRender();
		Draw( x, y, pSrcRect, color, fScaleX, fScaleY, fRotationCenterX, fRotationCenterY, fAngle );
		m_myudg->SetRenderBackBuffer(); // 2007/02/12 多分これも必要
	}

	/*
	//	Draw
	void Draw( CMglImage* destSurface, float x, float y, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
		{ destSurface->SetRender(); Draw( x, y, srcRect, color );
			m_myudg->SetRenderBackBuffer(); // 2007/02/12 多分これも必要
		}
	void Draw( float x=0, float y=0, RECT *srcRect=NULL, D3DCOLOR color=0xffffffff )
	{ CMglImage::DrawEx( 1.0f, 1.0f, 0.5f, 0.5f, 0, x, y, srcRect, color ); }

	//	DrawEx - スプライトを使うバージョン
	void DrawEx( CMglImage* destSurface, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
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

	/*
	//	DrawEx - スプライトを使うバージョン
	void DrawEx( CMglImage* destSurface, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
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
	void CopyRectToOther( CMglImage* destSurface, RECT *srcRect=NULL, int x=0, int y=0 );
	void CopyRectToThis( CMglImage* srcSurface, RECT *srcRect=NULL, int x=0, int y=0 );
	//void CopyRect( int x=0, int y=0, RECT *srcRect=NULL );

	//	センター絵画
	void EnableCenterDraw() {	m_bCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bCenterDraw = FALSE; }

	//	グラデーション
	//void SetGradation() { SetGradation(0xffffffff,0xffffffff,0xffffffff,0xffffffff); }
	//void SetGradation( D3DCOLOR colorLeftTop, D3DCOLOR colorRightTop, D3DCOLOR colorLeftBottom, D3DCOLOR colorRightBottom );


	//	プロパティ系メソッド
	//IDirect3DTexture8* GetTexturePtr() { CreateCheck(); return m_pTexture; }
	//IDirect3DSurface8* GetSurfacePtr() { CreateCheck(); return m_pSurface; }
	//ID3DXSprite* GetSpritePtr() { CreateCheck(); return m_pSprite; }
	//MYU_VERTEX* GetVerticesPtr() { CreateCheck(); return m_vertices; }

	//	デバッグ用に名前を付ける
	void SetName( const char* szName ){ m_sfcName = szName; }
};

typedef CMglImage CMglBitmap;
//typedef CMglImage CMglSprite;

#endif//__MglImage_H__
