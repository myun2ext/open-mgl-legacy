#include "stdafx.h"
#include "MglDirectInputDeviceBase.h"

#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	コンストラクタ
CMglDirectInputDeviceBase::CMglDirectInputDeviceBase()
{
	m_pDevice = NULL;
	//ZeroMemory( m_stateBuf, sizeof(m_stateBuf) );
	m_pStateBuf = NULL;
	m_nStateBufSize = 0;
}

//	デストラクタ
CMglDirectInputDeviceBase::~CMglDirectInputDeviceBase()
{
	SAFE_DELETE_ARY(m_pStateBuf);
	Release();
}

//	初期化
void CMglDirectInputDeviceBase::Init( REFGUID rguid, LPCDIDATAFORMAT dataFormat, int nStateBufSize, HWND hWnd, DWORD dwCooperativeFlag )
{
	//	基底初期化
	InitBase();

	//	デフォルトのhWnd取得
	if ( hWnd == NULL )
		hWnd = GetDefaultHwnd();

	MyuAssert( m_pDi->CreateDevice( rguid, &m_pDevice, NULL ), DI_OK,
		"CMglDirectInputDeviceBase::Init  m_pDi->CreateDevice()に失敗" );

	MyuAssert( m_pDevice->SetDataFormat( dataFormat ), DI_OK,
		"CMglDirectInputDeviceBase::Init  m_pDevice->SetDataFormat()に失敗" );
    
	MyuAssert( m_pDevice->SetCooperativeLevel( hWnd, dwCooperativeFlag ), DI_OK,
		"CMglDirectInputDeviceBase::Init  m_pDevice->SetCooperativeLevel()に失敗" );

	//	ステートバッファ確保
	m_pStateBuf = new BYTE[nStateBufSize];
	m_nStateBufSize = nStateBufSize;

	Acquire();
}

//	開放
void CMglDirectInputDeviceBase::Release()
{
	if( m_pDevice )
        Unacquire();
    
    // Release any DirectInput objects.
    SAFE_RELEASE( m_pDevice );
}


//	デバイスへのアクセス権限を取得
void CMglDirectInputDeviceBase::Acquire()
{
	InitCheck();
	//	ウインドウフォーカスが外れている時はエラーを返す
	m_pDevice->Acquire();
/*
	MyuAssert( m_pDevice->Acquire(), DI_OK,
		"CMglDirectInputDeviceBase::Acquire()  m_pDevice->Acquire()に失敗" );
*/
}

//	デバイスへのアクセス権限を破棄
void CMglDirectInputDeviceBase::Unacquire()
{
	InitCheck();
	m_pDevice->Unacquire();
}

//	ステート情報を取得
void CMglDirectInputDeviceBase::UpdateStateBuf()
{
	InitCheck();
	ZeroMemory( m_pStateBuf, m_nStateBufSize );
	if ( m_pDevice->GetDeviceState( m_nStateBufSize, m_pStateBuf ) != DI_OK )
	{
		//	失敗したらAcquire()を実行してもう一回試してみる
		Acquire();
		m_pDevice->GetDeviceState( m_nStateBufSize, m_pStateBuf );

		/*
			単にウインドウフォーカスが外れているだけかもしれないので何もしない
		*/

		//	どうも取得に失敗した時、中身が何か入ってしまっているようだ。
		ZeroMemory( m_pStateBuf, m_nStateBufSize );
	}
}
