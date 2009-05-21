//////////////////////////////////////////////////////////
//
//	AugustText2
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustText2.h"
#include "MglImage.h"

using namespace agh;

#define _P m_pBaseControl

//	�R���X�g���N�^
/*CAugustText2::CAugustText2()
{
}

//	�f�X�g���N�^
CAugustText2::~CAugustText2()
{
}*/


bool CAugustText2::Load(const char* szImageFilePath)
{
	m_strFilePath = szImageFilePath;
	
	//CAugustImageLoader* pImgLoader = (CAugustImageLoader*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_IMAGE_LOADER),
	//	"CAugustText2:  AUGUST_VALKEY_IMAGE_LOADER �̎擾�Ɏ��s�B");
	//m_pImg = pImgLoader->Load(szImageFilePath);	//	��{�I�ɗ�O�Ŕ�Ԃ͂��[
	CAugustGraphicsManager* pAGrpMgr = (CAugustGraphicsManager*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_AGRPM),
		"CAugustText2:  AUGUST_VALKEY_IMAGE_LOADER �̎擾�Ɏ��s�B");

	//	�ǂݍ���
	m_pImg = pAGrpMgr->LoadImageA(szImageFilePath);	//	��{�I�ɗ�O�Ŕ�Ԃ͂��[

	SetRect(0,0, m_pImg->GetBmpWidth(), m_pImg->GetBmpHeight());

	return true;
}

void CAugustText2::OnDraw()
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