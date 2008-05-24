#ifndef __MglBitmapTextLayer_H__
#define __MglBitmapTextLayer_H__

#include "MglLayerBase4.h"
#include "MglImage.h"

//	クラス宣言
class DLL_EXP CMglBitmapTextLayer : public CMglLayerBase4
{
private:
	//CMglImage m_img;
	CMglImage* m_pImage;
public:
	//	コンストラクタとしてCMglImageのポインタを渡す
	CMglBitmapTextLayer(CMglImage* pImage){ m_pImage=pImage; }

	//	implement
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		m_pImage->Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
};

#endif//__MglBitmapTextLayer_H__
