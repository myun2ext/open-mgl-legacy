//////////////////////////////////////////////////////////
//
//	MglSprite
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglSprite.h"

//	コンストラクタ
CMglSprite::CMglSprite()
{
	m_pTex = new CMglD3dTexture();
}

//	デストラクタ
CMglSprite::~CMglSprite()
{
	SAFE_DELETE( m_pTex );
}

//	描画
void CMglSprite::Draw()
{
	
}

