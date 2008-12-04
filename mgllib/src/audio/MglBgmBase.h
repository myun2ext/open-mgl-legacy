#ifndef __MglBgmBase_H__
#define __MglBgmBase_H__

#define MGL_BGM_LOOP_MAX		(0xffffffff)

//	�N���X�錾
class DLL_EXP CMglBgmBase
{
protected:
	BOOL m_useFlg;

public:
	//	������/�I�[�n
	virtual void Init()=0;
	virtual void Release()=0;
	virtual void Load( const char* szBgmFile )=0;
	virtual void UnLoad()=0;
	virtual void Unload()=0;

	//	�Đ�����n
	virtual void Play( int nLoopCnt=MGL_BGM_LOOP_MAX )=0;
	virtual void StopLoop()=0;
	virtual void Pause()=0;

	void Enable() { m_useFlg = TRUE; }
	void Disable() { m_useFlg = FALSE; }
};

typedef CMglBgmBase IMglBgmBase;

#endif//__MglBgmBase_H__
