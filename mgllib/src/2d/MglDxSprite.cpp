//////////////////////////////////////////////////////////
//
//	MglDxSprite
//		- DirectX Graphics 管理クラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDxSprite.h"

//	コンストラクタ
CMglDxSprite::CMglDxSprite()
{
	m_bSpriteBegun = FALSE;
}

//	デストラクタ
CMglDxSprite::~CMglDxSprite()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

#define m_pSprite m_pI

void CMglDxSprite::InitSprite()
{
	if ( m_pD3dDev == NULL )
		MyuThrow( MGLMSGNO_GRPMGR(80), "CMglDxSprite::InitSprite()  m_pD3dDevがNULL" );
	if ( m_pSprite != NULL )	//	既にあればスキップ
		return;

	MyuAssert2( D3DXCreateSprite( m_pD3dDev, &m_pSprite ), D3D_OK,
		MGLMSGNO_GRPMGR(81), "CMglDxSprite::Init()  D3DXCreateSprite()に失敗" );
}

//	スプライト描画
void CMglDxSprite::SpriteDraw( _TEX *pTexture, float x, float y, CONST RECT* pSrcRect, D3DCOLOR color,
		float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle )
{
	//	チェック
	if ( m_pSprite == NULL )
		MyuThrow( MGLMSGNO_GRPMGR(83), "CMglGraphicManage::SpriteDraw()  スプライトが無効になっているか、スプライトの初期化に失敗しました。" );
	if ( pTexture->GetDirect3dTexturePtr() == NULL )
		MyuThrow( MGLMSGNO_GRPMGR(84), "CMglGraphicManage::SpriteDraw()  IDirect3DTexture8 がNULLです。テクスチャが初期化されていない可能性があります。" );

	//	2009/01/07
	SpriteBegin();

	////// 計算処理 /////////////////////////////////

	/*	2009/03/31  CMglImage 側でやった方がいいんではないかなぁ
	//	srcRectにNULLを指定された場合はBMP全てをRECTに指定
	RECT texFullRect;
	if ( pSrcRect == NULL ||
		pSrcRect->left == pSrcRect->right || pSrcRect->top == pSrcRect->bottom ) // 2009/03/31
	{
		ZeroMemory(&texFullRect,sizeof(texFullRect));

		//	サイズ設定
		texFullRect.left = 0;
		texFullRect.top = 0;
		texFullRect.right = pTexture->GetBmpWidth();
		texFullRect.bottom = pTexture->GetBmpHeight();

		//	pSrcRect にポインタを設定
		pSrcRect = &texFullRect;
	}
	*/

	//	中心基点絵画機能
	/*if ( m_bSpriteCenterDraw == TRUE )
	{
		int nSizeX = pSrcRect->right - pSrcRect->left;
		int nSizeY = pSrcRect->bottom - pSrcRect->top;
		x -= (nSizeX/2) * fScaleX;
		y -= (nSizeY/2) * fScaleY;
	}*/

	/* 2007/02/12 これは多分要らない（0.5f指定すればいい）
	//	中心基点絵画機能
	if ( fRotationCenterX == -1 )	{
		int nSizeX = pSrcRect->right - pSrcRect->left;
		x -= (nSizeX/2) * fScaleX;
	}
	if ( fRotationCenterY == -1 )	{
		int nSizeY = pSrcRect->bottom - pSrcRect->top;
		y -= (nSizeY/2) * fScaleY;
	}
	*/


	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
	//	DirectX 9
	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
//#if _MGL_DXVER == 9
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXSPRITE_CHANGED
	//	DirectX9の場合はこーんな感じらしい。

	//	拡大・縮小
	D3DXMATRIX matScale;
	D3DXMatrixScaling(&matScale, fScaleX, fScaleY, 0.0f);

	//	回転の中心
	//float fCenterX = (pSrcRect->right - pSrcRect->left) * fRotationCenterX * fScaleX;
	//float fCenterY = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY * fScaleY;
	/*float fCenterX = (pSrcRect->right - pSrcRect->left) * fRotationCenterX; // 2009/03/31 CMglImage 側へ移動
	float fCenterY = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY;*/
	float fCenterX = fRotationCenterX; // 2009/03/31 CMglImage 側へ移動
	float fCenterY = fRotationCenterY; // 2009/03/31 CMglImage 側へ移動

	D3DXMATRIX matTrans1;
	D3DXMATRIX matTrans2;
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans1, fCenterX, fCenterY, 0);
	D3DXMatrixTranslation(&matTrans2, -fCenterX, -fCenterY, 0);
	D3DXMatrixTranslation(&matTrans, x, y, 0);

	//	角度
	D3DXMATRIX matRotation;
	D3DXMatrixRotationZ(&matRotation, D3DXToRadian(fAngle));

	//	結合
	/*D3DXMATRIX matrix1;
	D3DXMATRIX matrix;
	D3DXMatrixMultiply(&matrix1, &matRotation, &matTrans);
	D3DXMatrixMultiply(&matrix, &matrix1, &matScale);*/
//	D3DXMATRIX matrix = matTrans2 * matRotation * matTrans1 * matScale * matTrans;
	//D3DXMATRIX matrix = matTrans2 * matRotation * matTrans1 * matScale * matTrans;
	D3DXMATRIX matrix = matTrans1;

/*	
D3DXMATRIX *WINAPI D3DXMatrixTransformation2D(
	&matrix,
	&D3DXVECTOR2(0.5f,0.5f),
	FLOAT ScalingRotation,
	CONST D3DXVECTOR2 * pScaling,
	CONST D3DXVECTOR2 * pRotationCenter,
	FLOAT Rotation,
	CONST D3DXVECTOR2 * pTranslation
);
*/
	//int nWidth = pSrcRect;

	D3DXMatrixTransformation2D(&matrix,
		//&D3DXVECTOR2(200,200),
		&D3DXVECTOR2(0,0),
		0,
		&D3DXVECTOR2(fScaleX,fScaleY),
		&D3DXVECTOR2(0,0),//&D3DXVECTOR2(0.5f,0.5f),
		D3DXToRadian(fAngle),
		//&D3DXVECTOR2(x,y));
		&D3DXVECTOR2(x+fCenterX*fScaleX,y+fCenterY*fScaleY));

	//	トランスフォームとして反映
	MyuAssert2( m_pSprite->SetTransform(&matrix), D3D_OK,
		MGLMSGNO_GRPMGR(85), "CMglDxSprite::SpriteDraw()  m_pSprite->SetTransform()に失敗" );

	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(), pSrcRect, 
					 &D3DXVECTOR3(fCenterX, fCenterY, 0),
//					 &D3DXVECTOR3(0.5f, 0.5f, 0),
					 NULL, color), D3D_OK,
					 //&D3DXVECTOR3(fCenterX, fCenterY, 0), color), D3D_OK,
		MGLMSGNO_GRPMGR(86), "CMglDxSprite::SpriteDraw()  m_pSprite->Draw()に失敗" );

//	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(), NULL, NULL, NULL, color), D3D_OK,
//		MGLMSGNO_GRPMGR(86), "CMglDxSprite::SpriteDraw()  m_pSprite->Draw()に失敗" );

	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
	//	DirectX 8
	//=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
#else
	//	x, yをD3DXVECTOR2構造体に格納
	D3DXVECTOR2 vctPos;
	vctPos.x = x;
	vctPos.y = y;

	//	スケール
	D3DXVECTOR2 vctScale;
	vctScale.x = fScaleX;
	vctScale.y = fScaleY;

	//	回転の中心
	D3DXVECTOR2 vctRtCenter;
	vctRtCenter.x = (pSrcRect->right - pSrcRect->left) * fRotationCenterX * fScaleX;
	vctRtCenter.y = (pSrcRect->bottom - pSrcRect->top) * fRotationCenterY * fScaleY;

	/*	スプライトはアルファオプション効かないっぽい
	//	アルファオプション
	DWORD dwAlphaOptionBkup=0;
	if ( dwAlphaOption != MGL_ALPHA_OPT_NOCHANGE )
	{
		//	戻す時のためにバックアップを取っておく
		dwAlphaOptionBkup = m_myudg->GetAlphaMode();
		m_myudg->SetAlphaMode( dwAlphaOption );
	}*/

	//	角度からRadianに。更に左回転になっているので右回転に
	float fRad = AngleToRad(-fAngle);

	//////////////////////////////////////////////////////////////////////////////

	//	絵画
	MyuAssert2( m_pSprite->Draw( pTexture->GetDirect3dTexturePtr(),
		pSrcRect, &vctScale, &vctRtCenter, fRad, &vctPos, color ), D3D_OK,
		MGLMSGNO_GRPMGR(87), "CMglDxSprite::SpriteDraw()  m_pSprite->Draw()に失敗" );
#endif
}

//	スプライトのBegin()
void CMglDxSprite::SpriteBegin()
{
	if( m_pSprite == NULL )
		MyuThrow(MGLMSGNO_GRPMGR(91), "Spriteが作成されていません。");

	if( m_pSprite != NULL && m_bSpriteBegun == FALSE ){
//#if _MGL_DXVER == 9
#if _MGL_D3DXVER >= MGL_D3DXVER_ID3DXSPRITE_CHANGED
		MyuAssert2( m_pSprite->Begin(0), D3D_OK,
		//MyuAssert2( m_pSprite->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK), D3D_OK,
#else
		MyuAssert2( m_pSprite->Begin(), D3D_OK,
#endif
			MGLMSGNO_GRPMGR(89), "CMglDxSprite::SpriteBegin()  m_pSprite->Begin()に失敗" );
		m_bSpriteBegun = TRUE;
	}
}
//	スプライトのEnd()
void CMglDxSprite::SpriteEnd()
{
	if( m_pSprite == NULL )
		MyuThrow(MGLMSGNO_GRPMGR(92), "Spriteが作成されていません。");

	if( m_pSprite != NULL && m_bSpriteBegun == TRUE ){
		MyuAssert2( m_pSprite->End(), D3D_OK,
			MGLMSGNO_GRPMGR(90), "CMglDxSprite::SpriteEnd()  m_pSprite->End()に失敗" );
		m_bSpriteBegun = FALSE;
	}
}
