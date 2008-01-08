//////////////////////////////////////////////////////////
//
//	MyuFPS  v0.20.00 05/02/03
//		- FPS�Ǘ��N���X
//
//	v0.20.00 05/02/03
//	�E���񂰁[��J������
//
//////////////////////////////////////////////////////////

#ifndef __MyuFPS_H__
#define __MyuFPS_H__

#include "MyuIntervalTimer.h"

#define DEFAULT_FPS	(60)

#define GET_WAIT_FROM_FPS(V1)	(1000.0f/V1)
#define GET_FPS_FROM_TIME(V1)	(1000.0f/V1)

//	�N���X�錾
class DLL_EXP CMyuFPS
{
private:
	CMyuIntervalTimer m_timer;

	DWORD m_dwAdjust;
	DWORD m_nFPS;		//	FPS�l��ێ�
	float m_fNowFps;

public:
	CMyuFPS();
	virtual ~CMyuFPS();

	void Sleep();

	//	FPS��ݒ�
	void SetFPS( DWORD nFPS )
	{
		m_nFPS = nFPS;
		if ( nFPS <= 0 )
			m_nFPS = DEFAULT_FPS;
			//m_nFPS = 1000; //  �E�E�E�H
	}

	//	FPS�擾
	float GetFps() { return m_fNowFps; }

	//	����FPS�擾
	float GetAveFps()
	{
		float t = m_timer.GetAveTime();

		//	0���Z�`�F�b�N
		if ( (int)t == 0 )
			return 0;
		else
			return GET_FPS_FROM_TIME( t );
	}
};


#endif//__MyuFPS_H__