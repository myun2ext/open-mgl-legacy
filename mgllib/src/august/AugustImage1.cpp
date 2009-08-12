//////////////////////////////////////////////////////////
//
//	AugustImage1
//		- MglGraphicManager ���C���[�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustImage1.h"

using namespace agh;

#define _P m_pBaseControl

/*
//	�R���X�g���N�^
CAugustImage1::CAugustImage1()
{
}

//	�f�X�g���N�^
CAugustImage1::~CAugustImage1()
{
}
*/

void CAugustImage1::OnRegist(CAugustGlobalCommon *pGlobal)
{
	_BASE::OnRegist(pGlobal);

	m_pCacher = &(pGlobal->imgCache);
}

bool CAugustImage1::Load(const char* szImageFilePath)
{
	m_strFilePath = szImageFilePath;
	
	if ( m_pCacher == NULL ){
		MyuThrow(993243, "CAugustImage1::Load()  �e�R���g���[��������܂���B(CAugustScreen::RegistControl() �ɂ��o�^���s���Ă��܂���B)");
	}

	//	�ǂݍ���
	m_pCacher->Cache(szImageFilePath);
	m_pImg = m_pCacher->Get(szImageFilePath);

	SetRect(0,0, m_pImg->GetBmpWidth(), m_pImg->GetBmpHeight());

	return true;
}

void CAugustImage1::OnDraw()
{
	//_Img()->Draw( GetRect().left, GetRect().top,
	int x = GetRect().left;
	int y = GetRect().top;

	if ( m_bCentering == true )	//	�I�[�o�[���[�h�ł�낤���Ƃ��v�������E�E�E�܂��������̕������S��...
		m_pImg->EnableCenterDraw();
	else
		m_pImg->DisableCenterDraw();

	m_pImg->Draw( x, y,
		(::RECT*)&m_srcRect, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle); // 2009/03/31 �Ή�
	//	NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle);
}
