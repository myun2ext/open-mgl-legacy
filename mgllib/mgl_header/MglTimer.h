//////////////////////////////////////////////////////////
//
//	MglTimer  v0.12.00 05/02/03
//		- �^�C�}�[�Ǘ��N���X
//
//	v0.12.00 05/02/03
//	�E�F�X�Ɛ���
//
//////////////////////////////////////////////////////////

#ifndef __MglTimer_H__
#define __MglTimer_H__

//	�N���X�錾
class DLL_EXP CMglTimer
{
protected:
	DWORD m_dwStartGetTime;
	DWORD m_dwPauseTime;
	BOOL m_bPause;

public:
	CMglTimer();
	virtual ~CMglTimer();

	void Reset();
	void Start( DWORD nStartTime=0 );
	void Stop(){ Reset(); }
	DWORD Get();
	void Pause();
	void Pause( BOOL bPauseValue );
	void UnpauseOrStart( DWORD nStartTime=0 );

	DWORD GetTime();
	BOOL GetPauseStatus(){ return m_bPause; }
};


#endif//__MglTimer_H__