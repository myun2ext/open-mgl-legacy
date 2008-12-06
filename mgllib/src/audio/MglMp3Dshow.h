//////////////////////////////////////////////////////////
//
//	CMglMp3Dshow
//		- �G���[�����t��
//
//////////////////////////////////////////////////////////

#ifndef __MglMp3Dshow_H__
#define __MglMp3Dshow_H__

#include "MglDirectShowBase.h"
#include "MglBgmBase.h"

//	�N���X�錾
class DLL_EXP CMglMp3Dshow : public CMglDirectShowBase, public CMglBgmBase
{
private:
	

public:
	CMglMp3Dshow();
	virtual ~CMglMp3Dshow();

	//	������/�I�[�n
	void Init();
	void Release();
	void Load( const char* szOggFile );
	void UnLoad();
	void Unload(){ UnLoad(); }

	//	�Đ�����n
	void Play( int nLoopCnt=VOX_LOOP_MAX );
	void StopLoop();
	void Pause();
	void SetVolume( float fVolume=VOX_DEFAULT_VOLUME );
	void Fade( float fTargetVolume, int nFadeTimeMs );
	void FadeIn( int nFadeTimeMs ) { SetVolume(0); Fade( 1.0f, nFadeTimeMs ); }
	void FadeOut( int nFadeTimeMs ) { Fade( 0, nFadeTimeMs ); }

	void Enable() { m_useFlg = TRUE; }
	void Disable() { m_useFlg = FALSE; }
};

//typedef CMglMp3Dshow CMglMp3Dshow;
//class CMglMp3Dshow : public CMglMp3Dshow{};
//typedef CMglMp3Dshow CMglMusic;

#endif//__MglMp3Dshow_H__
