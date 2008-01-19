#include "stdafx.h"
#include "MglMouseInputBase.h"

#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	�R���X�g���N�^
CMglMouseInputBase::CMglMouseInputBase()
{
	m_pDevice = NULL;
	ZeroMemory( m_stateBuf, sizeof(m_stateBuf) );
}

//	�f�X�g���N�^
CMglMouseInputBase::~CMglMouseInputBase()
{
	Release();
}

//	������
void CMglMouseInputBase::Init( HWND hWnd, DWORD dwCooperativeFlag )
{
	//	��ꏉ����
	InitBase();

	//	�f�t�H���g��hWnd�擾
	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	MyuAssert( m_pDi->CreateDevice( GUID_SysMouse, &m_pDevice, NULL ), DI_OK,
		"CMglMouseInputBase::Init  m_pDi->CreateDevice()�Ɏ��s" );

	MyuAssert( m_pDevice->SetDataFormat( &c_dfDIMouse ), DI_OK,
		"CMglMouseInputBase::Init  m_pDevice->SetDataFormat()�Ɏ��s" );
    
	MyuAssert( m_pDevice->SetCooperativeLevel( hWnd, dwCooperativeFlag ), DI_OK,
		"CMglMouseInputBase::Init  m_pDevice->SetCooperativeLevel()�Ɏ��s" );

	Acquire();
}

//	�J��
void CMglMouseInputBase::Release()
{
	if( m_pDevice )
        Unacquire();
    
    // Release any DirectInput objects.
    SAFE_RELEASE( m_pDevice );
}


//	�f�o�C�X�ւ̃A�N�Z�X�������擾
void CMglMouseInputBase::Acquire()
{
	InitCheck();
	//	�E�C���h�E�t�H�[�J�X���O��Ă��鎞�̓G���[��Ԃ�
	m_pDevice->Acquire();
/*
	MyuAssert( m_pDevice->Acquire(), DI_OK,
		"CMglMouseInputBase::Acquire()  m_pDevice->Acquire()�Ɏ��s" );
*/
}

//	�f�o�C�X�ւ̃A�N�Z�X������j��
void CMglMouseInputBase::Unacquire()
{
	InitCheck();
	m_pDevice->Unacquire();
}

//	�X�e�[�g�����擾
void CMglMouseInputBase::UpdateStateBuf()
{
	InitCheck();
	ZeroMemory( m_stateBuf, sizeof(m_stateBuf) );
	if ( m_pDevice->GetDeviceState( sizeof(m_stateBuf), &m_stateBuf ) != DI_OK )
	{
		//	���s������Acquire()�����s���Ă�����񎎂��Ă݂�
		Acquire();
		m_pDevice->GetDeviceState( sizeof(m_stateBuf), &m_stateBuf );

		/*
			�P�ɃE�C���h�E�t�H�[�J�X���O��Ă��邾����������Ȃ��̂ŉ������Ȃ�
		*/

		//	�ǂ����擾�Ɏ��s�������A���g�����������Ă��܂��Ă���悤���B
		ZeroMemory( m_stateBuf, sizeof(m_stateBuf) );
	}
}

BOOL CMglMouseInputBase::IsPressKey( BYTE keyCode )
{
	if( PRESSKEY(m_stateBuf[keyCode]) ) 
		return TRUE;
	else
		return FALSE;
}