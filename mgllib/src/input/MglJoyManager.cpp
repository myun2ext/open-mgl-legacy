#include "stdafx.h"
#include "MglJoyManager.h"


//	�񋓃R�[���o�b�N�֘A
typedef struct
{
	_MGL_IDirectInput *pDi;
	vector<_MGL_IDirectInputDevice*> *pJoystkDevAry;
}
ENUM_JOYSTICKS_CALLBACK_IO;
BOOL CALLBACK EnumJoystickScaleback(const DIDEVICEINSTANCE* pdidInstance, void* pContext);


//	�R���X�g���N�^
CMglJoyManager::CMglJoyManager()
{
	//bInitFlg = FALSE;
}

//	�f�X�g���N�^
CMglJoyManager::~CMglJoyManager()
{
	Release();
}

//	�������[��
void CMglJoyManager::ExInit( DWORD dwCooperativeFlag )
{
	extern HWND g_hWndDefault;
	if ( g_hWndDefault == NULL )
		MyuThrow( 00, "g_hWndDefault �� NULL �ł��B" );

	ExInit( g_hWndDefault, dwCooperativeFlag );
}

//	����������Ȃ�[�B�Ȃ�[�B�Ȃ�[��B�Ȃ�[�[�[��H�H�H�H�H�i�N
void CMglJoyManager::ExInit( HWND hWnd, DWORD dwCooperativeFlag )
{
	//	�`�F�b�N
	//if ( bInitFlg == TRUE )
	if ( GetJoyCount() > 0 )
		MyuThrow( 200, "CMglJoyManager::ExInit()  ���ɂ��̃��\�b�h�͎��s����Ă��܂��B" );

	//	�ꉞ���ǂ��ׁB�Ȃ�ƂȂ�
	m_joystkDevAry.clear();
	//m_devCapsAry.clear();

	/*
	//	DirectInput8��������
	MyuAssert( DirectInput8Create(
		GetModuleHandle(NULL), /*DIRECTINPUT_VERSION*//* 0x0800, IID_IDirectInput8, (void**)&m_pDi, NULL ),
		DI_OK, "CMglJoyManager::ExInit()  DirectInput8Create()�Ɏ��s" );
	*/
	InitBase();

	//	�W���C�X�e�B�b�N�f�o�C�X�̗�
	ENUM_JOYSTICKS_CALLBACK_IO callbackIo;
	callbackIo.pDi = m_pDi;
	callbackIo.pJoystkDevAry = &m_joystkDevAry;

	MyuAssert( m_pDi->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoystickScaleback, (void*)&callbackIo, DIEDFL_ATTACHEDONLY),
		DI_OK, "CMglJoyManager::ExInit()  EnumDevices()�Ɏ��s" );

	//	�e�f�o�C�X���Ƃ̐ݒ�Ȃ̂Ń��[�v
	for( int i=0; i<m_joystkDevAry.size(); i++ )
	{
		_MGL_IDirectInputDevice* pDev = m_joystkDevAry[i];

		//	�f�[�^�`�������傢�ςǂɐݒ�
		MyuAssert( pDev->SetDataFormat( &c_dfDIJoystick2 ), DI_OK,
			"CMglJoyManager::ExInit()  pDev[%d]->SetDataFormat()�Ɏ��s", i );

		//	�������[�h
		MyuAssert( pDev->SetCooperativeLevel( hWnd, dwCooperativeFlag ), DI_OK,
			"CMglJoyManager::ExInit()  pDev[%d]->SetCooperativeLevel()�Ɏ��s", i );

		/*	//	�g���ĂȂ��Ǝv��
		//	CAPS�̎擾
		DIDEVCAPS capsWork;
		ZeroMemory( &capsWork, sizeof(capsWork) );
		capsWork.dwSize = sizeof(capsWork);

		MyuAssert( pDev->GetCapabilities( &capsWork ), DI_OK,
			"CMglJoyManager::ExInit()  pDev[%d]->GetCapabilities()�Ɏ��s", i );
		m_devCapsAry.push_back( capsWork );
		*/

		//	�A�N�Z�X���̎擾
		//Acquire(i);
	}

	//bInitFlg = TRUE;
}


//	�J��
void CMglJoyManager::Release()
{
	//	�e�W���C�X�e�B�b�N�f�o�C�X
	for( int i=0; i<m_joystkDevAry.size(); i++ )
	{
		_MGL_IDirectInputDevice* pDev = m_joystkDevAry[i];
		if( pDev )
		   pDev->Unacquire();

		SAFE_RELEASE( pDev );
	}
	m_joystkDevAry.clear();
	//bInitFlg = FALSE;
    
	//SAFE_RELEASE( m_pDi );
}


//	�񋓂̃R�[���o�b�N�Ȃ̂ł���[
BOOL CALLBACK EnumJoystickScaleback(const DIDEVICEINSTANCE* pdidInstance, void* pContext)
{
	ENUM_JOYSTICKS_CALLBACK_IO *pCallbackIo = (ENUM_JOYSTICKS_CALLBACK_IO*)pContext;
	_MGL_IDirectInput *pIoDi = pCallbackIo->pDi;
	vector<_MGL_IDirectInputDevice*> *pIoJoystkDevAry = pCallbackIo->pJoystkDevAry;

	_MGL_IDirectInputDevice* pJoystkDeviceWork=NULL;

	// �񋓂��ꂽ�W���C�X�e�B�b�N�ւ̃C���^�[�t�F�C�X���擾����B
	HRESULT hr = pIoDi->CreateDevice(pdidInstance->guidInstance, &pJoystkDeviceWork, NULL);
	if(FAILED(hr)) 
		return DIENUM_CONTINUE;

	pIoJoystkDevAry->push_back( pJoystkDeviceWork );

	return DIENUM_STOP;
}

