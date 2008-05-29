#ifndef __MglFadeLayer_H__
#define __MglFadeLayer_H__

#include "MglLayerBase4.h"

//	�N���X�錾
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
	/*int m_a2;
	int m_r2;
	int m_g2;
	int m_b2;*/
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

	//void _ARGPASplit(D3DCOLOR& color, BYTE& a, BYTE& r, BYTE& g, BYTE& b){
	void _ARGPASplit(D3DCOLOR& color, int& a, int& r, int& g, int& b){
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

		//	2008/05/25  float�͒x���̂Ŏg�������Ȃ��ł��ˁ[
		//		-> �v���Ă݂��炠��ܕς��Ȃ����ۂ��E�E�E�܂��܊p������̂ł������B�i��
		int x = m_nCounter*256 / m_nEndFrame;
		if ( x == 0 )
			return D3DCOLOR_ARGB(m_a1, m_r1, m_g1, m_b1);
		else
			return D3DCOLOR_ARGB(
				m_a1 + (m_a3*256) / x,
				m_r1 + (m_r3*256) / x,
				m_g1 + (m_g3*256) / x,
				m_b1 + (m_b3*256) / x
			);
	}

public:
	//	�R���X�g���N�^
	CMglFadeLayer(){ _Init(); }
	CMglFadeLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }
	//CMglImageLayer(CMglImage* pImage, bool isShouldDeletePtr):CMglLayerBase4(isShouldDeletePtr){ _Init(pImage); }

	//	�t�F�[�h�p�����[�^�w����R���X�g���N�^
	CMglFadeLayer(	D3DCOLOR bStartColor,
					D3DCOLOR bEndColor,
					int nEndFrame)
	{
		EffectInit(bStartColor,bEndColor,nEndFrame);
	}
	CMglFadeLayer(	D3DCOLOR bStartColor,
					D3DCOLOR bEndColor,
					int nEndFrame,
					bool isShouldDeletePtr)
	{
		EffectInit(bStartColor,bEndColor,nEndFrame);
		m_isShouldDeletePtr=isShouldDeletePtr;
	}

	//	������
	void EffectInit(	D3DCOLOR bStartColor,
						D3DCOLOR bEndColor,
						int nEndFrame)
	{
		if ( nEndFrame < 2 )
			MyuThrow( 0, "CMglFadeLayer nEndFrame�ɂ�2�ȏ�̒l���w�肵�Ă��������B" );

		int m_a2;
		int m_r2;
		int m_g2;
		int m_b2;

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
		color = GetNowColor();

		TBase::Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
	virtual BOOL DoFrame(){
		m_nCounter++;
		if ( m_nCounter > m_nEndFrame ){
			m_nCounter = m_nEndFrame;
			return FALSE;
		}
		return TRUE;
	}

	//	�t�F�[�h�C���E�t�F�[�h�A�E�g
	void FadeIn(int nFrameCount)
	{
		Init(0x00ffffff,0xffffffff,nFrameCount);
	}
	void FadeOut(int nFrameCount)
	{
		Init(0xffffffff,0x00ffffff,nFrameCount);
	}
};


template <typename TBase> class CMglFadeInLayer : public CMglFadeLayer<TBase>
{
public:
	//	�R���X�g���N�^
	CMglFadeInLayer(){ _Init(); }
	CMglFadeInLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }
	
	//	�t�F�[�h�p�����[�^�w����R���X�g���N�^
	CMglFadeInLayer(int nFrameCount)
	{
		FadeIn(nFrameCount);
	}
	CMglFadeInLayer(int nFrameCount,
					bool isShouldDeletePtr)
	{
		FadeIn(nFrameCount);
		m_isShouldDeletePtr=isShouldDeletePtr;
	}
};

template <typename TBase> class CMglFadeOutLayer : public CMglFadeLayer<TBase>
{
public:
	//	�R���X�g���N�^
	CMglFadeOutLayer(){ _Init(); }
	CMglFadeOutLayer(bool isShouldDeletePtr){ _Init(); m_isShouldDeletePtr=isShouldDeletePtr; }
	
	//	�t�F�[�h�p�����[�^�w����R���X�g���N�^
	CMglFadeOutLayer(int nFrameCount)
	{
		FadeOut(nFrameCount);
	}
	CMglFadeOutLayer(	int nFrameCount,
						bool isShouldDeletePtr)
	{
		FadeOut(nFrameCount);
		m_isShouldDeletePtr=isShouldDeletePtr;
	}
};


#endif//__MglFadeLayer_H__
