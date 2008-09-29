#include "stdafx.h"
#include "MglDirectInputDeviceBase.h"

#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	�R���X�g���N�^
CMglDirectInputDeviceBase::CMglDirectInputDeviceBase()
{
	m_pDevice = NULL;
	//ZeroMemory( m_stateBuf, sizeof(m_stateBuf) );
	m_pStateBuf = NULL;
	m_pOldStateBuf = NULL;
	m_nStateBufSize = 0;
	m_hWnd = NULL;
}

//	�f�X�g���N�^
CMglDirectInputDeviceBase::~CMglDirectInputDeviceBase()
{
	SAFE_DELETE_ARY(m_pStateBuf);
	SAFE_DELETE_ARY(m_pOldStateBuf);
	Release();
}

//	������
void CMglDirectInputDeviceBase::Init( REFGUID rguid, LPCDIDATAFORMAT dataFormat, int nStateBufSize, HWND hWnd, DWORD dwCooperativeFlag )
{
	//	��ꏉ����
	InitBase();

	//	�f�t�H���g��hWnd�擾
	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	MyuAssert( m_pDi->CreateDevice( rguid, &m_pDevice, NULL ), DI_OK,
		"CMglDirectInputDeviceBase::Init  m_pDi->CreateDevice()�Ɏ��s" );

	MyuAssert( m_pDevice->SetDataFormat( dataFormat ), DI_OK,
		"CMglDirectInputDeviceBase::Init  m_pDevice->SetDataFormat()�Ɏ��s" );
    
	MyuAssert( m_pDevice->SetCooperativeLevel( hWnd, dwCooperativeFlag ), DI_OK,
		"CMglDirectInputDeviceBase::Init  m_pDevice->SetCooperativeLevel()�Ɏ��s" );

	//	�X�e�[�g�o�b�t�@�m��
	m_pStateBuf = new BYTE[nStateBufSize];
	m_pOldStateBuf = new BYTE[nStateBufSize];
	m_nStateBufSize = nStateBufSize;
	ZeroMemory(m_pStateBuf,nStateBufSize);		//	2008/06/29  ���������ĂȂ�������ł����ǁI�I
	ZeroMemory(m_pOldStateBuf,nStateBufSize);	//	2008/06/29  ���������ĂȂ�������ł����ǁI�I

	Acquire();

	m_hWnd = hWnd;
}

//	�J��
void CMglDirectInputDeviceBase::Release()
{
	if( m_pDevice )
        Unacquire();
    
    // Release any DirectInput objects.
    SAFE_RELEASE( m_pDevice );
}


//	�f�o�C�X�ւ̃A�N�Z�X�������擾
void CMglDirectInputDeviceBase::Acquire()
{
	InitCheck();
	//	�E�C���h�E�t�H�[�J�X���O��Ă��鎞�̓G���[��Ԃ�
	m_pDevice->Acquire();
/*
	MyuAssert( m_pDevice->Acquire(), DI_OK,
		"CMglDirectInputDeviceBase::Acquire()  m_pDevice->Acquire()�Ɏ��s" );
*/
}

//	�f�o�C�X�ւ̃A�N�Z�X������j��
void CMglDirectInputDeviceBase::Unacquire()
{
	InitCheck();
	m_pDevice->Unacquire();
}

//	�X�e�[�g�����擾
BYTE* CMglDirectInputDeviceBase::UpdateStateBuf()
{
	//	2008/09/29  �Â��o�b�t�@���L��
	m_pOldStateBuf = m_pStateBuf;

	InitCheck();
	ZeroMemory( m_pStateBuf, m_nStateBufSize );
	if ( m_pDevice->GetDeviceState( m_nStateBufSize, m_pStateBuf ) != DI_OK )
	{
		//	���s������Acquire()�����s���Ă�����񎎂��Ă݂�
		Acquire();
		if ( m_pDevice->GetDeviceState( m_nStateBufSize, m_pStateBuf ) != DI_OK ){
			ZeroMemory( m_pStateBuf, m_nStateBufSize );
			return NULL;
		}

		/*
			�P�ɃE�C���h�E�t�H�[�J�X���O��Ă��邾����������Ȃ��̂ŉ������Ȃ�
		*/

		//	�ǂ����擾�Ɏ��s�������A���g�����������Ă��܂��Ă���悤���B
		//ZeroMemory( m_pStateBuf, m_nStateBufSize );
		//	��-- 2008/01/19 GetDeviceState()�Ő������Ă���ꍇ��ZeroMemory���Ă͂����Ȃ��悤�ȁE�E�E�H
	}

	return m_pStateBuf;
}

//	0:�ω��Ȃ�  ���̒l:�����ꂽ  ���̒l:�����ꂽ
int CMglDirectInputDeviceBase::GetStateChanged(int nIndex)
{
	return m_pStateBuf[nIndex] - m_pOldStateBuf[nIndex];
}