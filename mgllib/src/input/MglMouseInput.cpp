#include "stdafx.h"
#include "MglMouseInput.h"

#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	コンストラクタ
CMglMouseInput::CMglMouseInput()
{
	m_pDevice = NULL;
	ZeroMemory( m_stateBuf, sizeof(m_stateBuf) );
}

//	デストラクタ
CMglMouseInput::~CMglMouseInput()
{
	Release();
}

//	初期化
void CMglMouseInput::Init( HWND hWnd, DWORD dwCooperativeFlag )
{
	//	基底初期化
	InitBase();

	//	デフォルトのhWnd取得
	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	MyuAssert( m_pDi->CreateDevice( GUID_SysMouse, &m_pDevice, NULL ), DI_OK,
		"CMglMouseInput::Init  m_pDi->CreateDevice()に失敗" );

	MyuAssert( m_pDevice->SetDataFormat( &c_dfDIMouse ), DI_OK,
		"CMglMouseInput::Init  m_pDevice->SetDataFormat()に失敗" );
    
	MyuAssert( m_pDevice->SetCooperativeLevel( hWnd, dwCooperativeFlag ), DI_OK,
		"CMglMouseInput::Init  m_pDevice->SetCooperativeLevel()に失敗" );

	Acquire();
}

//	開放
void CMglMouseInput::Release()
{
	if( m_pDevice )
        Unacquire();
    
    // Release any DirectInput objects.
    SAFE_RELEASE( m_pDevice );
}


//	デバイスへのアクセス権限を取得
void CMglMouseInput::Acquire()
{
	InitCheck();
	//	ウインドウフォーカスが外れている時はエラーを返す
	m_pDevice->Acquire();
/*
	MyuAssert( m_pDevice->Acquire(), DI_OK,
		"CMglMouseInput::Acquire()  m_pDevice->Acquire()に失敗" );
*/
}

//	デバイスへのアクセス権限を破棄
void CMglMouseInput::Unacquire()
{
	InitCheck();
	m_pDevice->Unacquire();
}

//	ステート情報を取得
void CMglMouseInput::UpdateStateBuf()
{
	InitCheck();
	ZeroMemory( m_stateBuf, sizeof(m_stateBuf) );
	if ( m_pDevice->GetDeviceState( sizeof(m_stateBuf), &m_stateBuf ) != DI_OK )
	{
		//	失敗したらAcquire()を実行してもう一回試してみる
		Acquire();
		m_pDevice->GetDeviceState( sizeof(m_stateBuf), &m_stateBuf );

		/*
			単にウインドウフォーカスが外れているだけかもしれないので何もしない
		*/

		//	どうも取得に失敗した時、中身が何か入ってしまっているようだ。
		ZeroMemory( m_stateBuf, sizeof(m_stateBuf) );
	}
}

BOOL CMglMouseInput::IsPressKey( BYTE keyCode )
{
	if( PRESSKEY(m_stateBuf[keyCode]) ) 
		return TRUE;
	else
		return FALSE;
}
