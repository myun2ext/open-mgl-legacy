//////////////////////////////////////////////////////////
//
//	MglTimer  v0.12.00 05/02/03
//		- タイマー管理クラス
//
//	v0.12.00 05/02/03
//	・色々と整理
//
//////////////////////////////////////////////////////////

#ifndef __MglTimer_H__
#define __MglTimer_H__

//	クラス宣言
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