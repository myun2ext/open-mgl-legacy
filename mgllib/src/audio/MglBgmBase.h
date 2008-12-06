#ifndef __MglBgmBase_H__
#define __MglBgmBase_H__

#define MGL_BGM_LOOP_MAX		(0xffffffff)
#define _MGL_BGMBASE_ENBL_CHK()	if(m_bEnable!=true)return;

//////////////////////////////////////

class DLL_EXP CMglAudioSegment
{
protected:
	bool m_bEnable;

public:
	//	初期化/終端系
	virtual void Init()=0;
	virtual void Release()=0;
	virtual void Load( const char* szAudioFile )=0;
	virtual void UnLoad()=0;
	virtual void Unload(){ Unload(); }

	//	再生操作系
	virtual void Play()=0;
	virtual void LoopPlay( int nLoopCnt=MGL_BGM_LOOP_MAX )=0;
	virtual void Stop()=0;
	//virtual void StopLoop()=0;
	virtual void SetLastLoop()=0;
	virtual void Pause()=0;

	virtual void SetVolume( int nVolume )=0;	//	100分率
	virtual void Enable() { m_bEnable = true; }
	virtual void Disable() { m_bEnable = false; Stop(); }
};

typedef CMglAudioSegment IMglAudioSegment;
typedef CMglAudioSegment CMglAudioItem;

//////////////////////////////////////

//	クラス宣言
class DLL_EXP CMglBgmBase : public CMglAudioItem
{
public:
};

typedef CMglBgmBase IMglBgmBase;


#endif//__MglBgmBase_H__
