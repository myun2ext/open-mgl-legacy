#ifndef __MglMotionLayer_H__
#define __MglMotionLayer_H__

#include "MglLayerBase4.h"

//	クラス宣言
//template <typename TBase> class CMglStraightMoveLayer : public TBase
template <typename TBase> class CMglStraightMoveLayer : public CMgEffectLayerBase<TBase>
{
private:
	int m_nCounter;
	float m_fMoveX;
	float m_fMoveY;

	void _Init(){
		m_nCounter = 0;
		m_fMoveX = 0.0f;
		m_fMoveY = 0.0f;
	}

public:
	//	コンストラクタ
	CMglMotionLayer(){ _Init(); }
	CMglMotionLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }

	//	パラメータ指定つきコンストラクタ
	CMglMotionLayer(float fMoveX,
					float fMoveY)
	{
		Init(fMoveX,fMoveY);
	}
	CMglMotionLayer(float fMoveX,
					float fMoveY,
					bool isShouldDeletePtr)
	{
		Init(fMoveX,fMoveY);
		m_isShouldDeletePtr=isShouldDeletePtr;
	}

	//	初期化
	void Init(	float fMoveX,
				float fMoveY)
	{
		m_nCounter = 0;
		m_fMoveX = fMoveX;
		m_fMoveY = fMoveY;
		//if ( 
	}

	//	implement
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		TBase::Draw(
			x + m_fMoveX*m_nCounter,
			y + m_fMoveY*m_nCounter,
			srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
	virtual BOOL OnFrame(){
		m_nCounter++;
		//m_nCounter = m_nCounter % (m_nShowFrame+m_nHideFrame);
		return TRUE;
	}
};

#endif//__MglMotionLayer_H__
