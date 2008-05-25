#ifndef __MglBlinkLayer_H__
#define __MglBlinkLayer_H__

#include "MglLayerBase4.h"

//	クラス宣言
//template <typename TBase> class CMglBlinkLayer : public TBase
template <typename TBase> class CMglBlinkLayer : public CMgEffectLayerBase<TBase>
{
private:
	int m_nCounter;
	int m_nShowFrame;
	int m_nHideFrame;

	void _Init(){
		m_nCounter = 0;
		m_nShowFrame = 0;
		m_nHideFrame = 0;
	}

public:
	//	コンストラクタ
	CMglBlinkLayer(){ _Init(); }
	CMglBlinkLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }

	//	パラメータ指定つきコンストラクタ
	CMglBlinkLayer(	int nShowFrame,
					int nHideFrame)
	{
		Init(nShowFrame,nHideFrame);
	}
	CMglBlinkLayer(	int m_nShowFrame,
					int m_nHideFrame,
					bool isShouldDeletePtr)
	{
		Init(nShowFrame,nHideFrame);
		m_isShouldDeletePtr=isShouldDeletePtr;
	}

	//	初期化
	void Init(	int nShowFrame,
				int nHideFrame)
	{
		m_nCounter = 0;
		m_nShowFrame = nShowFrame;
		m_nHideFrame = nHideFrame;
		//if ( 
	}
	void SetFirstHide(){ m_nCounter = nShowFrame; }

	//	implement
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		if ( m_nShowFrame < m_nCounter )
			TBase::Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
	virtual BOOL OnFrame(){
		//m_nCounter++;
		m_nCounter = m_nCounter % (m_nShowFrame+m_nHideFrame);
		return TRUE;
	}
};

#endif//__MglBlinkLayer_H__
