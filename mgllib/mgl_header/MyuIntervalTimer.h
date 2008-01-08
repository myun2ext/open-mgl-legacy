//////////////////////////////////////////////////////////
//
//	MyuIntervalTimer  v0.10.00 05/02/03
//		- �Ԋu�^�C�}�[�Ǘ��N���X�i���ώ��Ԍv�����j
//
//	v0.10.00 05/02/03
//	�ECMyuTimer���番��
//
//////////////////////////////////////////////////////////

#ifndef __MyuIntervalTimer_H__
#define __MyuIntervalTimer_H__

#include "MglTimer.h"

//	AVE�`
#define INTERVAL_TYPE_TIME		(0)
#define INTERVAL_TYPE_COUNT		(1)

//	�N���X�錾
class DLL_EXP CMyuIntervalTimer
{
private:
	CMglTimer m_timer;

	int m_nAveIntervalType;
	int m_nAveIntervalVal;

	int m_nAveCnt;
	int m_nAveTtlTime;
	float m_fAveTime;

	BOOL m_bInitFlg;

public:
	CMyuIntervalTimer();
	virtual ~CMyuIntervalTimer();

	void Setup( int in_nAveIntervalType, int in_nAveIntervalVal );
	void Update();
	//void Pause();	���邩�ȁc�H

	DWORD Get() { return m_timer.Get(); }
	float GetAveTime() { return m_fAveTime; }
};


#endif//__MyuIntervalTimer_H__