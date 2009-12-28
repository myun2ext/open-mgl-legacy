//////////////////////////////////////////////////////////
//
//	August3dCamera
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "August3dCamera.h"
#include "MglImage.h"

using namespace agh;

#define _P m_pBaseControl

//	�R���X�g���N�^
/*CAugust3dCamera::CAugust3dCamera()
{
}

//	�f�X�g���N�^
CAugust3dCamera::~CAugust3dCamera()
{
}*/


bool CAugust3dCamera::LoadEx(const char* szImageFilePath, agh::COLOR transparentColor)
{
	RegistedCheck();
	////////////////////////////////////////

	m_strFilePath = szImageFilePath;
	
	//CAugustImageLoader* pImgLoader = (CAugustImageLoader*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_IMAGE_LOADER),
	//	"CAugust3dCamera:  AUGUST_VALKEY_IMAGE_LOADER �̎擾�Ɏ��s�B");
	//m_pImg = pImgLoader->Load(szImageFilePath);	//	��{�I�ɗ�O�Ŕ�Ԃ͂��[
	CAugustGraphicsManager* pAGrpMgr = (CAugustGraphicsManager*)MyuAssertNull(_BASE::GetValPtr(AUGUST_VALKEY_AGRPM),
		"CAugust3dCamera:  AUGUST_VALKEY_IMAGE_LOADER �̎擾�Ɏ��s�B");

	//	�ǂݍ���
	//m_pImg = pAGrpMgr->LoadImageA(szImageFilePath);	//	��{�I�ɗ�O�Ŕ�Ԃ͂��[
	m_pImg = pAGrpMgr->LoadImage(szImageFilePath, transparentColor);	//	��{�I�ɗ�O�Ŕ�Ԃ͂��[

//	if ( GetRect() != 0 )	�Ȃ񂩐ݒ肳��Ă��SetRect���Ȃ���̑Ή��BCRect��V�����o�[�W�����ɂ��Ȃ��Ɩ������E�E�E
	SetRect(0,0, m_pImg->GetBmpWidth(), m_pImg->GetBmpHeight());

	return true;
}

void CAugust3dCamera::OnDraw()
{
	RegistedCheck();
	if ( m_pImg == NULL )	//	2009/10/25
		return;

	////////////////////////////////////////

	//_Img()->Draw( GetRect().left, GetRect().top,
	int x = GetRect().left;
	int y = GetRect().top;

	if ( m_bCentering == true )	//	�I�[�o�[���[�h�ł�낤���Ƃ��v�������E�E�E�܂��������̕������S��...
		m_pImg->EnableCenterDraw();
	else
		m_pImg->DisableCenterDraw();

/*	char work[1024];
	sprintf(work, "%d, %d, (%d, %d, %d, %d), color=%08X, %f, %f, %f", x, y,
		m_srcRect.left, m_srcRect.top, m_srcRect.right, m_srcRect.bottom,
		m_color, m_fScaleX, m_fScaleY, m_fAngle);*/

	agh::CRect posRect = GetAbsoluteRect();

	m_pImg->Draw( posRect.left, posRect.top,
		(::RECT*)&m_srcRect, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle); // 2009/03/31 �Ή�
	//	NULL, m_color, m_fScaleX, m_fScaleY, 0.5f, 0.5f, m_fAngle);

//	MessageBox(NULL,work,NULL,NULL);
}