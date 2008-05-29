#ifndef __MglEffectLayer_H__
#define __MglEffectLayer_H__

#include "MglLayerBase4.h"

//	クラス宣言
//template <typename TBase> class CMglBlinkLayer : public TBase
template <typename TBase> class CMglChangeScaleLayer : public CMgEffectLayerBase<TBase>
{
private:
	int m_nCounter;
	float m_fStartScaleX;
	float m_fStartScaleY;
	float m_fEndScaleX;
	float m_fEndScaleY;

	void _Init(){
		m_nCounter = 0;
		m_fStartScaleX = 0.0f;
		m_fStartScaleY = 0.0f;
		m_fEndScaleX = 0.0f;
		m_fEndScaleY = 0.0f;
	}

public:
	//	コンストラクタ
	CMglChangeScaleLayer(){ _Init(); }
	CMglChangeScaleLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }

	//	パラメータ指定つきコンストラクタ
	CMglChangeScaleLayer(	float fStartScale,
							float fStartScale)
	{
		Init(fStartScale,fStartScale);
	}
	CMglChangeScaleLayer(	int m_nShowFrame,
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


//	回転するレイヤー
template <typename TBase> class CMglSpinLayer : public CMgEffectLayerBase<TBase>
{
private:
	int m_nCounter;
	float m_fAngle;
	float m_fOneFrameSpin;
	//int m_nFrame;

	void _Init(){
		m_nCounter = 0;
		m_fAngle = 0;
		m_fOneFrameSpin = 0.0f;
	}

public:
	//	コンストラクタ
	CMglSpinLayer(){ _Init(); }
	CMglSpinLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }

	//	パラメータ指定つきコンストラクタ
	CMglSpinLayer(float fOneFrameSpin)
	{
		Init(fOneFrameSpin);
	}
	CMglSpinLayer(float fOneFrameSpin, bool isShouldDeletePtr)
	{
		Init(fOneFrameSpin);
		m_isShouldDeletePtr=isShouldDeletePtr;
	}

	//	初期化
	void Init(float fOneFrameSpin)
	{
		m_nCounter = 0;
		m_fAngle = 0;
		m_fOneFrameSpin = fOneFrameSpin;
	}

	//	implement
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		TBase::Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,m_fAngle);
	}
	virtual BOOL OnFrame(){
		//m_nCounter++;
		m_fAngle += m_fOneFrameSpin;
		return TRUE;
	}
};
#endif//__MglEffectLayer_H__
