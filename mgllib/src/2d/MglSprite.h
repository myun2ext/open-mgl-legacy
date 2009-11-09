//////////////////////////////////////////////////////////
//
//	MglSprite - レイヤー
//
//////////////////////////////////////////////////////////

#ifndef __MglSprite_H__
#define __MglSprite_H__

#include "MglD3dTexture.h"

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglSprite
{
private:
	CMglDxTexture* m_pTex;

public:
	//	コンストラクタ/デストラクタ
	CMglSprite();
	virtual ~CMglSprite();

	void Draw();
};


#endif//__MglSprite_H__