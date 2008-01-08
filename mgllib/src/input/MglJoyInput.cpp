#include "stdafx.h"
#include "MglJoyInput.h"


//	コンストラクタ
CMglJoyInput::CMglJoyInput()
{
	m_pDevice = NULL;

	m_nNeutralX=-1;
	m_nNeutralY=-1;
	m_nMargin=-1;
	m_bJoySetupFlg=FALSE;
}

//	デストラクタ
CMglJoyInput::~CMglJoyInput()
{

}

//	デバイスへのアクセス権限を取得
void CMglJoyInput::Acquire()
{
	m_pDevice->Acquire();

/*	//	ウインドウフォーカスが外れている時はエラーを返す
	MyuAssert( pDev->Acquire(), DI_OK,
		"CMyuKeyboardInput::Acquire()  pDev->Acquire()に失敗" );
*/
}

//	ステート情報を取得する。エラーの場合はNULL
DIJOYSTATE2* CMglJoyInput::GetState( DIJOYSTATE2* pStateBuf )
{
	CHKINIT();

	ZeroMemory( pStateBuf, sizeof(DIJOYSTATE2) );

    //	現在の状態を読み取るデバイスをポーリングする。
    HRESULT hr = m_pDevice->Poll(); 
    if ( hr != DI_OK && hr != DI_NOEFFECT )  
    {
		//	ウインドウフォーカス外れたりするとなる
		if ( hr == DIERR_NOTACQUIRED || hr == DIERR_INPUTLOST )
		{
			Acquire();

			//	もっかい
			hr = m_pDevice->Poll(); 
			if ( hr != DI_OK && hr != DI_NOEFFECT )  
			{
				if ( hr == DIERR_NOTACQUIRED || hr == DIERR_INPUTLOST )
				{
					/*	//	ウインドウフォーカスが外れている時はエラーを返す
					//	だめっすね。
					//MyuThrow( 99, "CMglJoyInput::GetState()  デバイスへのアクセス権の取得に失敗。" );
					*/
					return NULL;
				}
			}
		}
    }

    MyuAssert( m_pDevice->GetDeviceState( sizeof(DIJOYSTATE2), pStateBuf ), DI_OK,
		"CMglJoyInput::GetState()  GetDeviceState()に失敗" );

	return pStateBuf;
}

//	指定されたボタンが押されているか
BOOL CMglJoyInput::IsPushBotton( int nBottomNo )
{
	DIJOYSTATE2 buf;
	if ( GetState( &buf ) == NULL )
		return FALSE;

	if ( buf.rgbButtons[nBottomNo] != 0 )
		return TRUE;
	else
		return FALSE;
}


//	直接軸値取得
BOOL CMglJoyInput::GetX( long* pnX )
{
	DIJOYSTATE2 buf;
	if ( GetState( &buf ) == NULL )
		return FALSE;;

	*pnX = buf.lX;
	return TRUE;
}
BOOL CMglJoyInput::GetY( long* pnY )
{
	DIJOYSTATE2 buf;
	if ( GetState( &buf ) == NULL )
		return FALSE;;

	*pnY = buf.lY;
	return TRUE;
}


//	軸方向取得 (左)
BOOL CMglJoyInput::IsLeft()
{
	CHKINFOSET();	
	long nX = -1;
	if ( GetX( &nX ) != TRUE )
		return FALSE;

	if ( nX < (m_nNeutralX-m_nMargin) )
		return TRUE;
	else
		return FALSE;
}

//	軸方向取得 (右)
BOOL CMglJoyInput::IsRight()
{
	CHKINFOSET();
	long nX = -1;
	if ( GetX( &nX ) != TRUE )
		return FALSE;

	if ( nX > (m_nNeutralX+m_nMargin) )
		return TRUE;
	else
		return FALSE;
}

//	軸方向取得 (上)
BOOL CMglJoyInput::IsUp()
{
	CHKINFOSET();	
	long nY = -1;
	if ( GetY( &nY ) != TRUE )
		return FALSE;

	if ( nY < (m_nNeutralY-m_nMargin) )
		return TRUE;
	else
		return FALSE;
}

//	軸方向取得 (下)
BOOL CMglJoyInput::IsDown()
{
	CHKINFOSET();	
	long nY = -1;
	if ( GetY( &nY ) != TRUE )
		return FALSE;

	if ( nY > (m_nNeutralY+m_nMargin) )
		return TRUE;
	else
		return FALSE;
}