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
private:
	typedef CMglDgIBase<ID3DXSprite> _BASE;
	typedef CMglD3dTexture _TEX;

	void InitSprite();

protected:
	BOOL m_bSpriteBegun;


public:
	//	コンストラクタ/デストラクタ
	CMglDxSprite();
	virtual ~CMglDxSprite();

	//	初期化/開放
	virtual void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){
		_BASE::Init(in_myudg);

		InitSprite();
	}

	//	2007/01/11  スプライト描画
	void Draw( _TEX *pTexture, float x=0, float y=0, CONST RECT* pSrcRect=NULL, D3DCOLOR color=D3DCOLOR_WHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f );
	//	float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=-1, float fRotationCenterY=-1, float fAngle=0.0f );
	/*void EnableCenterDraw() {	m_bSpriteCenterDraw = TRUE; }
	void DisableCenterDraw() {	m_bSpriteCenterDraw = FALSE; }*/
	/*void SpriteBegin(){ if( m_pSprite != NULL ) m_pSprite->Begin(); }
	void SpriteEnd(){ if( m_pSprite != NULL ) m_pSprite->End(); }*/
	void Begin(DWORD dwFlag=D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_FRONTTOBACK);
	void End();

	ID3DXSprite* GetSpritePtr(){ return m_pI; }
};

#endif//__MglDxSprite_H__
