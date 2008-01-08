#ifndef __MglImageFader_H__
#define __MglImageFader_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MglImageManager.h"

//	�N���X�錾
class DLL_EXP CMglImageFader
{
protected:
	/*CMglImageManager* m_pImgMgr;
	string m_strName;*/
	int m_nFadeSpeed;
	int m_x, m_y;
	D3DCOLOR m_color;
	RECT m_rect;
	int m_nFrameCounter;
	//int m_nFadeInStart;
	int m_nFadeOutStart;

	CMglImage *m_pImage;	// �����������
	//	�� Cacher�Ǘ��ɂ����������T�Q����

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		//if ( m_pImgMgr == NULL )
		if ( m_pImage == NULL )
			MyuThrow( 0, "CMglImageFader::Setup()���Ă΂�Ă��܂���B" );
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglImageFader();
	virtual ~CMglImageFader();

	/*void Setup( CMglImageManager* pImageManager, const char* szName, int nFadeSpeed,
		int x=0, int y=0, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_WHITE );*/
	void Setup( CMglImage* pImage, int nFadeSpeed,
		int x=0, int y=0, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_WHITE );
	/*void FadeIn( int nFadeSpeed=0 );
	void FadeOut( int nFadeSpeed=0 );*/
	void FadeIn(){ m_nFrameCounter = 0; }
	void FadeOut(){ m_nFadeOutStart = m_nFrameCounter; }
	void DoDraw();
};

#endif//__MglImageFader_H__
