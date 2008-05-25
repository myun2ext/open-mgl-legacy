#ifndef __MglFadeLayer_H__
#define __MglFadeLayer_H__

#include "MglLayerBase4.h"

//	クラス宣言
template <typename TBase> class CMglFadeLayer : public TBase
{
private:
	D3DCOLOR m_bStartColor;
	D3DCOLOR m_bEndColor;
	int m_nCounter;
	int m_nEndFrame;

	BYTE m_a1;
	BYTE m_r1;
	BYTE m_g1;
	BYTE m_b1;
	BYTE m_a2;
	BYTE m_r2;
	BYTE m_g2;
	BYTE m_b2;

	void _Init(){
		m_bStartColor = 0;
		m_bEndColor = 0;
		m_nCounter = 0;
		m_nEndFrame = 0;
	}

	D3DCOLOR GetNowColor(){
	}

public:
	//	コンストラクタ
	CMglFadeLayer(){ _Init(); }
	CMglFadeLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }
	//CMglImageLayer(CMglImage* pImage, bool isShouldDeletePtr):CMglLayerBase4(isShouldDeletePtr){ _Init(pImage); }

	//	フェードパラメータ指定つきコンストラクタ
	CMglFadeLayer(	D3DCOLOR bStartColor,
					D3DCOLOR bEndColor,
					int nCounter,
					int nEndFrame)
	{
		Init(bStartColor,bEndColor,nCounter,nEndFrame);
	}
	CMglFadeLayer(	D3DCOLOR bStartColor,
					D3DCOLOR bEndColor,
					int nCounter,
					int nEndFrame,
					bool isShouldDeletePtr)
	{
		Init(bStartColor,bEndColor,nCounter,nEndFrame);
		m_isShouldDeletePtr=isShouldDeletePtr;
	}

	//	初期化
	void Init(	D3DCOLOR bStartColor,
				D3DCOLOR bEndColor,
				int nCounter,
				int nEndFrame)
	{
		m_bStartColor = bStartColor;
		m_bEndColor = bEndColor;
		m_nCounter = nCounter;
		m_nEndFrame = nEndFrame;
	}

	//	implement
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		//color = D3DCOLOR_AMASK(color);
		color = D3DCOLOR_AMASK(color);

		TBase::Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
};

#endif//__MglFadeLayer_H__
