//////////////////////////////////////////////////////////
//
//	AugustImage2
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustImage2.h"
#include "MglImage.h"
#include "AugustGraphicsManager.h"

using namespace agh;

#define _P m_pBaseControl

/*
//	�R���X�g���N�^
CAugustImage2::CAugustImage2()
{
}

//	�f�X�g���N�^
CAugustImage2::~CAugustImage2()
{
}
*/

bool CAugustImage2::Load(const char* szImageFilePath)
{
	m_strFilePath = szImageFilePath;
	
	CAugustImageLoader* pImgLoader = (CAugustImageLoader*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_IMAGE_LOADER),
		"CAugustImage2:  AUGUST_VALKEY_IMAGE_LOADER �̎擾�Ɏ��s�B");

	//	�ǂݍ���
	m_pImg = pImgLoader->Load(szImageFilePath);	//	��{�I�ɗ�O�Ŕ�Ԃ͂��[

	SetRect(0,0, m_pImg->GetBmpWidth(), m_pImg->GetBmpHeight());

	return true;
}

void CAugustImage2::OnDraw()
{
	//_Img()->Draw( GetRect().left, GetRect().top,
	int x = GetRect().left;
	int y = GetRect().top;

	if ( m_bCentering == true )	//	�I�[�o�[���[�h�ł�낤���Ƃ��v�������E�E�E�܂��������̕������S��...
		m_pImg->EnableCenterDraw();
	else
		m_pImg->DisableCenterDraw();

	m_pImg->Draw( x, y,
		(RECT*)&m_srcRect, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle); // 2009/03/31 �Ή�
	//	NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle);
}
