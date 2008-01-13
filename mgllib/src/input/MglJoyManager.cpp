#include "stdafx.h"
#include "MglJoyManager.h"


//	列挙コールバック関連
typedef struct
{
	_MGL_IDirectInput *pDi;
	vector<_MGL_IDirectInputDevice*> *pJoystkDevAry;
}
ENUM_JOYSTICKS_CALLBACK_IO;
BOOL CALLBACK EnumJoystickScaleback(const DIDEVICEINSTANCE* pdidInstance, void* pContext);


//	コンストラクタ
CMglJoyManager::CMglJoyManager()
{
	//bInitFlg = FALSE;
}

//	デストラクタ
CMglJoyManager::~CMglJoyManager()
{
	Release();
}

//	初期化ーん
void CMglJoyManager::ExInit( DWORD dwCooperativeFlag )
{
	extern HWND g_hWndDefault;
	if ( g_hWndDefault == NULL )
		MyuThrow( 00, "g_hWndDefault が NULL です。" );

	ExInit( g_hWndDefault, dwCooperativeFlag );
}

//	初期化するならー。ならー。ならーん。ならーーーん？？？？？（誰
void CMglJoyManager::ExInit( HWND hWnd, DWORD dwCooperativeFlag )
{
	//	チェック
	//if ( bInitFlg == TRUE )
	if ( GetJoyCount() > 0 )
		MyuThrow( 200, "CMglJoyManager::ExInit()  既にこのメソッドは実行されています。" );

	//	一応よんどくべ。なんとなく
	m_joystkDevAry.clear();
	//m_devCapsAry.clear();

	/*
	//	DirectInput8を初期化
	MyuAssert( DirectInput8Create(
		GetModuleHandle(NULL), /*DIRECTINPUT_VERSION*//* 0x0800, IID_IDirectInput8, (void**)&m_pDi, NULL ),
		DI_OK, "CMglJoyManager::ExInit()  DirectInput8Create()に失敗" );
	*/
	InitBase();

	//	ジョイスティックデバイスの列挙
	ENUM_JOYSTICKS_CALLBACK_IO callbackIo;
	callbackIo.pDi = m_pDi;
	callbackIo.pJoystkDevAry = &m_joystkDevAry;

	MyuAssert( m_pDi->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoystickScaleback, (void*)&callbackIo, DIEDFL_ATTACHEDONLY),
		DI_OK, "CMglJoyManager::ExInit()  EnumDevices()に失敗" );

	//	各デバイスごとの設定なのでループ
	for( int i=0; i<m_joystkDevAry.size(); i++ )
	{
		_MGL_IDirectInputDevice* pDev = m_joystkDevAry[i];

		//	データ形式をじょいぱどに設定
		MyuAssert( pDev->SetDataFormat( &c_dfDIJoystick2 ), DI_OK,
			"CMglJoyManager::ExInit()  pDev[%d]->SetDataFormat()に失敗", i );

		//	強調モード
		MyuAssert( pDev->SetCooperativeLevel( hWnd, dwCooperativeFlag ), DI_OK,
			"CMglJoyManager::ExInit()  pDev[%d]->SetCooperativeLevel()に失敗", i );

		/*	//	使ってないと思う
		//	CAPSの取得
		DIDEVCAPS capsWork;
		ZeroMemory( &capsWork, sizeof(capsWork) );
		capsWork.dwSize = sizeof(capsWork);

		MyuAssert( pDev->GetCapabilities( &capsWork ), DI_OK,
			"CMglJoyManager::ExInit()  pDev[%d]->GetCapabilities()に失敗", i );
		m_devCapsAry.push_back( capsWork );
		*/

		//	アクセス権の取得
		//Acquire(i);
	}

	//bInitFlg = TRUE;
}


//	開放
void CMglJoyManager::Release()
{
	//	各ジョイスティックデバイス
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


//	列挙のコールバックなのですよー
BOOL CALLBACK EnumJoystickScaleback(const DIDEVICEINSTANCE* pdidInstance, void* pContext)
{
	ENUM_JOYSTICKS_CALLBACK_IO *pCallbackIo = (ENUM_JOYSTICKS_CALLBACK_IO*)pContext;
	_MGL_IDirectInput *pIoDi = pCallbackIo->pDi;
	vector<_MGL_IDirectInputDevice*> *pIoJoystkDevAry = pCallbackIo->pJoystkDevAry;

	_MGL_IDirectInputDevice* pJoystkDeviceWork=NULL;

	// 列挙されたジョイスティックへのインターフェイスを取得する。
	HRESULT hr = pIoDi->CreateDevice(pdidInstance->guidInstance, &pJoystkDeviceWork, NULL);
	if(FAILED(hr)) 
		return DIENUM_CONTINUE;

	pIoJoystkDevAry->push_back( pJoystkDeviceWork );

	return DIENUM_STOP;
}

