//////////////////////////////////////////////////////////
//
//	MglImageAnimator

#ifndef __MglImageAnimator_H__
#define __MglImageAnimator_H__

//#include "MglGraphicManager.h"
#include "MglImageCacher.h"

//	�N���X�錾
class DLL_EXP CMglImageAnimator
{
protected:
	//CMglImage m_image;	//	2007/03/21 �p����߂Ă݂�
	CMglImage* m_pImage;		//	�L���b�V���ւ̃|�C���^
	int m_nTipWidth;
	int m_nTipHeight;
	int m_nCounter;
	BOOL m_bAutoCountUp;

	//	�\�ߌv�Z���Ă���
	int m_nTipCountX;
	int m_nTipCountY;
	int m_nTipCount;

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglImageAnimator();
	virtual ~CMglImageAnimator();

	//	�ǂݍ���
	void Load( const char* szImageFileName, int nTipWidth, int nTipHeight, D3DCOLOR colorKey=DEF_COLORKEY );

	//	�`��i��fSacle���T�|�[�g�j<- ���Ă��łȂ��c�H�i2007/02/12�j
	//void Draw( float x, float y, float fScaleX=1.0f, float fScaleY=1.0f, D3DCOLOR color=D3DCOLOR_WHITE );
	void Draw( float x, float y, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f );
	void DrawEx( int nCount, float x, float y, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f );
	
	void EnableAutoCountUp(){ m_bAutoCountUp = TRUE; }
	void DisableAutoCountUp(){ m_bAutoCountUp = FALSE; }
	void CountUp();
	void SetCounter( int nCounter ){ m_nCounter = nCounter; }
};

#endif//__MglImageAnimator_H__
