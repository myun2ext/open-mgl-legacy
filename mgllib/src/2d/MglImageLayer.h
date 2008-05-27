#ifndef __MglImageLayer_H__
#define __MglImageLayer_H__

#include "MglLayerBase4.h"
#include "MglImage.h"

//	クラス宣言
class DLL_EXP CMglImageLayer : public CMglLayerBase4
{
private:
	//CMglImage m_img;
	CMglImage* m_pImage;
	RECT m_rectWork;
public:
	//	コンストラクタとしてCMglImageのポインタを渡す
	CMglImageLayer(){}
	CMglImageLayer(CMglImage* pImage){ Init(pImage); }
	CMglImageLayer(CMglImage* pImage, bool isShouldDeletePtr){ Init(pImage); m_isShouldDeletePtr=isShouldDeletePtr; }
	//CMglImageLayer(CMglImage* pImage, bool isShouldDeletePtr):CMglLayerBase4(isShouldDeletePtr){ _Init(pImage); }

	void Init(CMglImage* pImage){
		ZeroMemory(&m_rectWork, sizeof(RECT));
		m_pImage=pImage;
	}

	//	implement
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		m_pImage->Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
	void Release(){
		if ( m_isShouldDeletePtr )
			delete m_pImage;
	}
	RECT GetRect(){
		if ( m_rectWork.left == 0 && m_rectWork.right == 0 && m_rectWork.top == 0 && m_rectWork.bottom == 0 ){
			m_rectWork.left = 0;
			m_rectWork.right = m_pImage->GetBmpWidth();
			m_rectWork.top = 0;
			m_rectWork.bottom = m_pImage->GetBmpHeight();
		}
		return m_rectWork;
	}
};

#endif//__MglImageLayer_H__
