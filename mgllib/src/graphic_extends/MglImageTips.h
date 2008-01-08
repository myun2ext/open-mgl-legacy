//////////////////////////////////////////////////////////
//
//	MglImageTips

#ifndef __MglImageTips_H__
#define __MglImageTips_H__

#include "MglGraphicManager.h"
//#include "MglTexture.h"
#include "MglImage.h"

//	�N���X�錾
class DLL_EXP CMglImageTips// : protected CMglTexture // �p���ɂ��Ă�񂾂��ǂ��񂩂Ȃ��E�E�E
{
protected:
	CMglImage m_image;	//	2007/03/21 �p����߂Ă݂�
	//	�� Cacher�Ǘ��ɂ����������T�Q����
	map<string,RECT> m_rectTable;

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglImageTips(){}
	virtual ~CMglImageTips(){}

	//	�ǂݍ���
	void Load( const char* szFileName );
	//void Load( LPCSTR szImageFile, LPCSTR szTableFile, D3DCOLOR colorKey=DEF_COLORKEY );
	//void Load( LPCSTR szImageFile, map<string,RECT> &rectTable, D3DCOLOR colorKey=DEF_COLORKEY );
	//void Load( LPCSTR szImageFile, map<string,string> &rectTable, D3DCOLOR colorKey=DEF_COLORKEY );

	//	�`��i��fSacle���T�|�[�g�j<- ���Ă��łȂ��c�H�i2007/02/12�j
	void Draw( const char* szRectName, float x, float y, float fScaleX=1.0f, float fScaleY=1.0f, D3DCOLOR color=D3DCOLOR_WHITE );
	int GetTipWidth( const char* szRectName );
	int GetTipHeight( const char* szRectName );
};

typedef CMglImageTips CMglBitmapTips;

#endif//__MglImageTips_H__
