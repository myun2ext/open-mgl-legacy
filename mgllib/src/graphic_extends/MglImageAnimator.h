//////////////////////////////////////////////////////////
//
//	MglImageAnimator

#ifndef __MglImageAnimator_H__
#define __MglImageAnimator_H__

//#include "MglGraphicManager.h"
#include "MglImageCacher.h"

//	クラス宣言
class DLL_EXP CMglImageAnimator
{
protected:
	//CMglImage m_image;	//	2007/03/21 継承やめてみた
	CMglImage* m_pImage;		//	キャッシュへのポインタ
	int m_nTipWidth;
	int m_nTipHeight;
	int m_nCounter;
	BOOL m_bAutoCountUp;

	//	予め計算しておく
	int m_nTipCountX;
	int m_nTipCountY;
	int m_nTipCount;

public:
	//	コンストラクタ・デストラクタ
	CMglImageAnimator();
	virtual ~CMglImageAnimator();

	//	読み込み
	void Load( const char* szImageFileName, int nTipWidth, int nTipHeight, D3DCOLOR colorKey=DEF_COLORKEY );

	//	描画（※fSacle未サポート）<- してるんでない…？（2007/02/12）
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
