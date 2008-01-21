//////////////////////////////////////////////////////////
//
//	MglSprite - レイヤー
//
//////////////////////////////////////////////////////////

#ifndef __MglSprite_H__
#define __MglSprite_H__

#include "MglImage.h"

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglSprite : public CMglImage
{
private:
	BOOL m_bShow;			//	表示するか
	RECT m_rect;			//	矩形領域
	//RECT* pRect;		//	矩形領域。指定されていればrectのポインタが、指定されてなければNULLが入る
	D3DCOLOR m_color;		//	アルファ値 | カラー

	//	2008/01/20  拡張
	float m_x, m_y;				//	場所
	float m_fScaleX, m_fScaleY;	//	縮尺率
	float m_fRotationCenterX;
	float m_fRotationCenterY;
	float m_fAngle;			//	角度

public:
	//	コンストラクタ/デストラクタ
	CMglSprite();
	virtual ~CMglSprite();

	void Draw();
};


#endif//__MglSprite_H__