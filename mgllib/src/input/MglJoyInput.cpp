#include "stdafx.h"
#include "MglJoyInput.h"


//	�R���X�g���N�^
CMglJoyInput::CMglJoyInput()
{
	m_pDevice = NULL;

	m_nNeutralX=-1;
	m_nNeutralY=-1;
	m_nMargin=-1;
	m_bJoySetupFlg=FALSE;
}

//	�f�X�g���N�^
CMglJoyInput::~CMglJoyInput()
{

}

//	�f�o�C�X�ւ̃A�N�Z�X�������擾
void CMglJoyInput::Acquire()
{
	m_pDevice->Acquire();

/*	//	�E�C���h�E�t�H�[�J�X���O��Ă��鎞�̓G���[��Ԃ�
	MyuAssert( pDev->Acquire(), DI_OK,
		"CMyuKeyboardInput::Acquire()  pDev->Acquire()�Ɏ��s" );
*/
}

//	�X�e�[�g�����擾����B�G���[�̏ꍇ��NULL
DIJOYSTATE2* CMglJoyInput::GetState( DIJOYSTATE2* pStateBuf )
{
	CHKINIT();

	ZeroMemory( pStateBuf, sizeof(DIJOYSTATE2) );

    //	���݂̏�Ԃ�ǂݎ��f�o�C�X���|�[�����O����B
    HRESULT hr = m_pDevice->Poll(); 
    if ( hr != DI_OK && hr != DI_NOEFFECT )  
    {
		//	�E�C���h�E�t�H�[�J�X�O�ꂽ�肷��ƂȂ�
		if ( hr == DIERR_NOTACQUIRED || hr == DIERR_INPUTLOST )
		{
			Acquire();

			//	��������
			hr = m_pDevice->Poll(); 
			if ( hr != DI_OK && hr != DI_NOEFFECT )  
			{
				if ( hr == DIERR_NOTACQUIRED || hr == DIERR_INPUTLOST )
				{
					/*	//	�E�C���h�E�t�H�[�J�X���O��Ă��鎞�̓G���[��Ԃ�
					//	���߂����ˁB
					//MyuThrow( 99, "CMglJoyInput::GetState()  �f�o�C�X�ւ̃A�N�Z�X���̎擾�Ɏ��s�B" );
					*/
					return NULL;
				}
			}
		}
    }

    MyuAssert( m_pDevice->GetDeviceState( sizeof(DIJOYSTATE2), pStateBuf ), DI_OK,
		"CMglJoyInput::GetState()  GetDeviceState()�Ɏ��s" );

	return pStateBuf;
}

//	�w�肳�ꂽ�{�^����������Ă��邩
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


//	���ڎ��l�擾
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


//	�������擾 (��)
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

//	�������擾 (�E)
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

//	�������擾 (��)
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

//	�������擾 (��)
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