#include "stdafx.h"
#include "MglDirectInputBase.h"

//	�ÓI�����o�ϐ��̃C���X�^���X
_MGL_IDirectInput* CMglDirectInputBase::m_pDi = NULL;
int CMglDirectInputBase::m_nRef=0;


//	�R���X�g���N�^
CMglDirectInputBase::CMglDirectInputBase()
{
	m_nRef++;	//	�Q�ƃJ�E���^
}

//	�f�X�g���N�^
CMglDirectInputBase::~CMglDirectInputBase()
{
	m_nRef--;	//	�Q�ƃJ�E���^

	//	���L�҂��N�����Ȃ��Ȃ����i�K�ŊJ��
	if ( m_nRef <= 0 )
		SAFE_RELEASE( m_pDi );
}

//	������
void CMglDirectInputBase::InitBase()
{
	if ( m_pDi != NULL )
		return;	//	���ɏ������ς݂�[��

#ifdef _MGL_USE_DXVER9
	//	DirectInput9��������
	MyuAssert( DirectInput9Create(
		GetModuleHandle(NULL), /*DIRECTINPUT_VERSION*/ 0x0900, IID_IDirectInput9, (void**)&m_pDi, NULL ),
		DI_OK, "CMglDirectInputBase::Init()  DirectInput9Create()�Ɏ��s" );
#else
	//	DirectInput8��������
	MyuAssert( DirectInput8Create(
		GetModuleHandle(NULL), /*DIRECTINPUT_VERSION*/ 0x0800, IID_IDirectInput8, (void**)&m_pDi, NULL ),
		DI_OK, "CMglDirectInputBase::Init()  DirectInput8Create()�Ɏ��s" );
#endif
}

void CMglDirectInputBase::FinalRelease()
{
	SAFE_RELEASE( m_pDi );
}
