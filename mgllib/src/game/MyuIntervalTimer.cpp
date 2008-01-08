//////////////////////////////////////////////////////////
//
//	MyuIntervalTimer  v0.10.00 05/02/03
//		- �Ԋu�^�C�}�[�Ǘ��N���X�i���ώ��Ԍv�����j
//
//	v0.10.00 05/02/03
//	�ECMyuTimer���番��
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyuIntervalTimer.h"

//	�R���X�g���N�^
CMyuIntervalTimer::CMyuIntervalTimer()
{
	//	���ώ���
	m_bInitFlg = FALSE;

	//	�f�t�H���g������
	Setup( INTERVAL_TYPE_TIME, 1000 );
}

//	�f�X�g���N�^
CMyuIntervalTimer::~CMyuIntervalTimer()
{

}

//	������
void CMyuIntervalTimer::Setup( int in_nAveIntervalType, int in_nAveIntervalVal )
{
	m_nAveCnt = 0;
	m_fAveTime = 0;
	m_nAveTtlTime = 0;

	m_nAveIntervalType = in_nAveIntervalType;
	m_nAveIntervalVal = in_nAveIntervalVal;

	m_bInitFlg = TRUE;
	m_timer.Start();	//	����Ȃ��E�E�E�H
}

//	�X�V
void CMyuIntervalTimer::Update()
{
	//	���ώ��ԑ���
	m_nAveTtlTime += m_timer.Get();
	m_nAveCnt++;

	BOOL bSum=FALSE;

	//	�J�E���g����
	if ( m_nAveIntervalType == INTERVAL_TYPE_COUNT )
	{
		if ( m_nAveCnt > m_nAveIntervalVal )
			bSum = TRUE;
	}

	//	���ԕ���
	else
	{
		if ( m_nAveTtlTime >= m_nAveIntervalVal )
			bSum = TRUE;
	}

	//	���v����[�H
	if ( bSum == TRUE )
	{
		if ( m_nAveTtlTime >= m_nAveIntervalVal ) {
			m_fAveTime = (float)m_nAveTtlTime / (float)m_nAveCnt;
			m_nAveCnt = 0;
			m_nAveTtlTime = 0;
		}
	}
	
	//	���Z�b�g�͂���܁[��
	m_timer.Start();
}

