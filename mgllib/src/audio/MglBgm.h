#ifndef __MglBgm_H__
#define __MglBgm_H__

#include "MglBgmBase.h"
//#include "MglMp3Dshow.h"
//#include "MglOgg.h"

//	クラス宣言
class DLL_EXP CMglBgm : public IMglBgmBase, public CMyuReleaseBase
{
private:
	IMglBgmBase *m_pBgm;
	IMglBgmBase *m_pMp3Dshow;	//	これ両方用意してる意味ってなんかあったっけ・・・
	IMglBgmBase *m_pOgg;		//	これ両方用意してる意味ってなんかあったっけ・・・
								//	あー、もしくはInit()の都合上だったかな。でもhWnd保存しとけば・・・まぁいいか。
	HWND m_hWnd;

	void InitCheck(){
		if ( m_hWnd == NULL )
			MyuThrow(MGLMSGNO_BGM(1), "CMglBgm::Init()メソッドを呼び出してください。");
	}
	void LoadCheck(){
		if ( m_pBgm == NULL )
			MyuThrow(MGLMSGNO_BGM(2), "CMglBgm::Load()メソッドを呼び出してください。");
	}

public:
	//	コンストラクタ/デストラクタ
	CMglBgm();
	virtual ~CMglBgm();

	//	初期化/終端系
	void Init( HWND hWnd = NULL );
	void Release();

	void Load( const char* szAudioFile );
	void Unload(){ InitCheck(); m_pBgm->Unload(); m_pBgm = NULL; }
	//void Unload(){ Release(); }	//	こっちでいいんじゃないの・・・？違うか・・・

	//	再生操作系
	void Play(){ LoadCheck(); m_pBgm->Play(); }
	void LoopPlay( int nLoopCnt=MGL_AUDIO_LOOP_MAX ){ LoadCheck(); m_pBgm->LoopPlay(nLoopCnt); }
	void Stop(){ LoadCheck(); m_pBgm->Stop(); }
	void SetLastLoop(){ LoadCheck(); m_pBgm->SetLastLoop(); }
	void Pause(){ LoadCheck(); m_pBgm->Pause(); }

	void SetVolume( int nVolume=MGL_VOLUME_MAX ){ LoadCheck(); m_pBgm->SetVolume(nVolume); }	//	100分率
	void SetBalance( int nBalance=MGL_PAN_CENTER ){ LoadCheck(); m_pBgm->SetBalance(nBalance); }	//	-100～100
};

#endif//__MglBgm_H__
