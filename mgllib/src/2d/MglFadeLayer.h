#ifndef __MglFadeLayer_H__
#define __MglFadeLayer_H__

#include "MglLayerBase4.h"

//	クラス宣言
//template <typename TBase> class CMglFadeLayer : public TBase
template <typename TBase> class CMglFadeLayer : public CMgEffectLayerBase<TBase>
{
private:
	D3DCOLOR m_bStartColor;
	D3DCOLOR m_bEndColor;
	int m_nCounter;
	int m_nEndFrame;

	int m_a1;
	int m_r1;
	int m_g1;
	int m_b1;
	int m_a2;
	int m_r2;
	int m_g2;
	int m_b2;
	int m_a3;
	int m_r3;
	int m_g3;
	int m_b3;

	void _Init(){
		m_bStartColor = 0;
		m_bEndColor = 0;
		m_nCounter = 0;
		m_nEndFrame = 0;
	}

	void _ARGPASplit(D3DCOLOR& color, BYTE& a, BYTE& r, BYTE& g, BYTE& b){
		a = D3DCOLOR_GETA(color);
		r = D3DCOLOR_GETR(color);
		g = D3DCOLOR_GETG(color);
		b = D3DCOLOR_GETB(color);
	}

	D3DCOLOR GetNowColor(){
		/*
		float f = (float)m_nCounter / (float)m_nEndFrame;
		return D3DCOLOR_ARGB(
			m_a1 + m_a3 * f,
			m_r1 + m_r3 * f,
			m_g1 + m_g3 * f,
			m_b1 + m_b3 * f,
			);
		*/

		//	2008/05/25  floatは遅いので使いたくないですねー
		//		-> 計ってみたらあんま変わんないっぽい・・・まぁ折角作ったのでいっか。（何
		int x = m_nCounter*256 / m_nEndFrame;
		return D3DCOLOR_ARGB(
			m_a1 + (m_a3*256) / x,
			m_r1 + (m_r3*256) / x,
			m_g1 + (m_g3*256) / x,
			m_b1 + (m_b3*256) / x
		);
	}

public:
	//	コンストラクタ
	CMglFadeLayer(){ _Init(); }
	CMglFadeLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }
	//CMglImageLayer(CMglImage* pImage, bool isShouldDeletePtr):CMglLayerBase4(isShouldDeletePtr){ _Init(pImage); }

	//	フェードパラメータ指定つきコンストラクタ
	CMglFadeLayer(	D3DCOLOR bStartColor,
					D3DCOLOR bEndColor,
					int nEndFrame)
	{
		Init(bStartColor,bEndColor,nEndFrame);
	}
	CMglFadeLayer(	D3DCOLOR bStartColor,
					D3DCOLOR bEndColor,
					int nEndFrame,
					bool isShouldDeletePtr)
	{
		Init(bStartColor,bEndColor,nEndFrame);
		m_isShouldDeletePtr=isShouldDeletePtr;
	}

	//	初期化
	void Init(	D3DCOLOR bStartColor,
				D3DCOLOR bEndColor,
				int nEndFrame)
	{
		m_nCounter = 0;
		m_bStartColor = bStartColor;
		m_bEndColor = bEndColor;
		m_nEndFrame = nEndFrame;
		_ARGPASplit(bStartColor, m_a1, m_r1, m_g1, m_b1);
		_ARGPASplit(bEndColor, m_a2, m_r2, m_g2, m_b2);
		/*a3 = (int)m_a1 - (int)m_a2;
		m_r3 = (int)m_r1 - (int)m_r2;
		m_g3 = (int)m_g1 - (int)m_g2;
		m_b3 = (int)m_b1 - (int)m_b2;*/
		m_a3 = m_a1 - m_a2;
		m_r3 = m_r1 - m_r2;
		m_g3 = m_g1 - m_g2;
		m_b3 = m_b1 - m_b2;
	}

	//	implement
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		//color = D3DCOLOR_AMASK(color);
		color = GetNowColor(color);

		TBase::Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
	virtual BOOL OnFrame(){
		m_nCounter++;
		if ( m_nCounter > m_nEndFrame ){
			m_nCounter = m_nEndFrame;
			return FALSE;
		}
		return TRUE;
	}
};

#endif//__MglFadeLayer_H__
