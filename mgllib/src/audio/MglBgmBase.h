#ifndef __MglBgmBase_H__
#define __MglBgmBase_H__

#define MGL_AUDIO_LOOP_MAX		(0xffffffff)

#define MGL_VOLUME_MAX			(100)
#define MGL_VOLUME_MIN			(0)

#define MGL_PAN_FULLR			(100)
#define MGL_PAN_FULLL			(-100)
#define MGL_PAN_CENTER			(0)


#define _MGL_BGMBASE_ENBL_CHK()	if(m_bEnable!=true)return;

//////////////////////////////////////

class DLL_EXP CMglAudioSegment
{
protected:
	bool m_bEnable;

public:
	//	初期化/終端系
	virtual void Init( HWND hWnd = NULL )=0;
	virtual void Release()=0;
	virtual void Load( const char* szAudioFile )=0;
	virtual void Unload()=0;
	virtual void UnLoad(){ Unload(); }

	//	再生操作系
	virtual void Play()=0;
	virtual void LoopPlay( int nLoopCnt=MGL_AUDIO_LOOP_MAX )=0;
	virtual void Stop()=0;
	//virtual void StopLoop()=0;
	virtual void SetLastLoop()=0;
	virtual void Pause()=0;

	virtual void SetVolume( int nVolume=MGL_VOLUME_MAX )=0;	//	100分率
	virtual void SetBalance( int nBalance=MGL_PAN_CENTER )=0;	//	-100～100
	virtual void SetPan( int nBalance=MGL_PAN_CENTER ){ SetBalance(nBalance); }

	//	2009/09/18  シーク関連追加
	virtual void SeekTo( long nSeekTime, DWORD dwFlg=SEEK_SET )=0;
	void Seek( long nSeekTime, DWORD dwFlg=SEEK_SET ){ SeekTo(nSeekTime, dwFlg); }
	void SeekToHead(){ SeekTo( 0, SEEK_SET ); }

	virtual void Enable() { m_bEnable = true; }
	virtual void Disable() { m_bEnable = false; Stop(); }
};

typedef CMglAudioSegment IMglAudioSegment;
typedef CMglAudioSegment CMglAudioItem;

////////////////////////////////////////////////////////////////////

//	クラス宣言
class DLL_EXP CMglBgmBase : public CMglAudioItem
{
};

typedef CMglBgmBase IMglBgmBase;
typedef CMglBgmBase IMglBgm;

#endif//__MglBgmBase_H__
