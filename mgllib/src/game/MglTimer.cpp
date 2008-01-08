//////////////////////////////////////////////////////////
//
//	MglTimer
//		- �^�C�}�[�Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglTimer.h"

//	�R���X�g���N�^
CMglTimer::CMglTimer()
{
	//	�ŏ����x���グ��
	timeBeginPeriod(1);

	//	������
	Reset();
	//Start();
}

//	�f�X�g���N�^
CMglTimer::~CMglTimer()
{
	//	���x�����ɖ߂�
	timeEndPeriod(1);
}

//	������
void CMglTimer::Reset()
{
	m_dwPauseTime = 0;
	m_bPause = TRUE;
}

//	�^�C�}�[�J�n
void CMglTimer::Start( DWORD nStartTime )
{
	//	���ώ��ԑ���
	m_dwStartGetTime = GetTime();
	m_bPause = FALSE;
}

//	�܂����Ԏ擾�A���ƁB
DWORD CMglTimer::GetTime()
{
	//timeBeginPeriod(1);
	DWORD t = timeGetTime();
	//timeEndPeriod(1);

	return t;
}

//	�|�[�Y��ԂȂ�Unpause�B�����łȂ��Ȃ�Start
void CMglTimer::UnpauseOrStart( DWORD nStartTime )
{
	if ( m_bPause == TRUE )
		Pause();
	else
		Start( nStartTime );
}

//	�o�ߎ��Ԏ擾
DWORD CMglTimer::Get()
{
	if ( m_bPause == FALSE )
	{
		DWORD r = GetTime() - m_dwStartGetTime;

		//	�j�]�p����
		if ( r < 0 )
		{
			r += 0x7FFFFFFF;
		}
		return r;
	}
	else
		return m_dwPauseTime;
}

//	�^�C�}�[�ꎞ��~
void CMglTimer::Pause()
{
	if ( m_bPause == FALSE )
		Pause( TRUE );
	else
		Pause( FALSE );
}

//	�^�C�}�[�ꎞ��~
void CMglTimer::Pause( BOOL bPauseValue )
{
	if ( bPauseValue == TRUE )
	{
		//	����
		m_dwPauseTime = Get();
		m_bPause = TRUE;
	}
	else
	{
		//	��
		m_bPause = FALSE;
		m_dwStartGetTime = timeGetTime() + m_dwPauseTime;
	}
}
