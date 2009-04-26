///////////////////////////////////////////////////////////////////////
//
//	MglDxSprite
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglDxSprite_H__
#define __MglDxSprite_H__

#include "MglGraphicManager.h"
#include "MglD3dTexture.h"

DLL_TMPL_EXP CMglDgIBase<ID3DXSprite>;

//	クラス宣言
class DLL_EXP CMglDxSprite : public CMglDgIBase<ID3DXSprite> //CMglDgBase
{
public:
	typedef CMglD3dTexture _TEX;
protected:
	BOOL m_bSpriteBegun;

public:
	//	コンストラクタ/デストラクタ
	CMglDxSprite();
	virtual ~CMglDxSprite();

	//	2007/01/11  スプライト描画
	void InitSprite();
	void SpriteDraw( _TEX *pTexture, float x=0, float y=0, CONST RECT* pSrcRect=NULL, D3DCOLOR color=D3DCOLOR_WHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f );
	//	float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=-1, float fRotationCenterY=-1, float fAngle=0.0f );
	/*void EnableCenterDraw() {	m_bSpriteCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bSpriteCenterDraw = FALSE; }*/
	/*void SpriteBegin(){ if( m_pSprite != NULL ) m_pSprite->Begin(); }
	void SpriteEnd(){ if( m_pSprite != NULL ) m_pSprite->End(); }*/
	void SpriteBegin();
	void SpriteEnd();
};

#endif//__MglDxSprite_H__
