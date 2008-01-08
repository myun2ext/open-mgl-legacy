//////////////////////////////////////////////////////////
//
//	MyuFPS
//		- FPS�Ǘ��N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyuFPS.h"

#define WAIT_TIME		(GET_WAIT_FROM_FPS(m_nFPS))

//	�R���X�g���N�^
CMyuFPS::CMyuFPS()
{
	m_nFPS = DEFAULT_FPS;
	m_fNowFps = 0;
	m_dwAdjust = 0;
	//m_timer.Init( INTERVAL_TYPE_TIME, 100 );
}

//	�f�X�g���N�^
CMyuFPS::~CMyuFPS()
{

}

//	�X���[�v����
void CMyuFPS::Sleep()
{
	//Sleep(0);	//	���ꂵ�Ȃ��Ǝ��Ԃ���肭�擾�ł��Ȃ�(ɄD`)

	int nGetTime = m_timer.Get();
	int nWaitTime = (m_dwAdjust>>16) - nGetTime;

	//	�X���[�v�B�ł�Sleep���x�͍Œ�ł�1ms�Ȃ̂�
	//	1ms���Ȃ߂�Sleep�����ŋ��
	if ( nWaitTime > 0 )
		::Sleep( nWaitTime-1 );

	//	���̐����ǂ���B��񂵁B
	while( m_timer.Get() < (m_dwAdjust>>16) );

	//	���������^�C�}�[�X�V
	m_timer.Update();

	int nFrameTime = nWaitTime+nGetTime;

	if ( nWaitTime < 0 )
		m_fNowFps = GET_FPS_FROM_TIME( nGetTime );
	else
		m_fNowFps = GET_FPS_FROM_TIME( nFrameTime );

	//	- 0x100 �� �I�[�o�[�w�b�h�Ƃ��l�����č��\��i��
	m_dwAdjust += ( WAIT_TIME - nFrameTime ) * 0x10000 - 0x100;	
}
