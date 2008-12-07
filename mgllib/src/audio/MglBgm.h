#ifndef __MglBgm_H__
#define __MglBgm_H__

#include "MglBgmBase.h"
#include "MglMp3Dshow.h"
#include "MglOgg.h"

//	�N���X�錾
class DLL_EXP CMglBgm : public IMglBgmBase
{
private:
	IMglBgmBase *m_pBgm;
	IMglBgmBase *m_pMp3Dshow;
	IMglBgmBase *m_pOgg;

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMglBgm();
	virtual ~CMglBgm();

	//	������/�I�[�n
	void Init();
	void Release();

	void Load( const char* szAudioFile );
	void Unload(){ m_pBgm->Unload(); }

	//	�Đ�����n
	void Play(){ m_pBgm->Play(); }
	void LoopPlay( int nLoopCnt=MGL_AUDIO_LOOP_MAX ){ m_pBgm->LoopPlay(nLoopCnt); }
	void Stop(){ m_pBgm->Stop(); }
	void SetLastLoop(){ m_pBgm->SetLastLoop(); }
	void Pause(){ m_pBgm->Pause(); }

	void SetVolume( int nVolume=MGL_VOLUME_MAX ){ m_pBgm->SetVolume(nVolume); }	//	100����
	void SetBalance( int nBalance=MGL_PAN_CENTER ){ m_pBgm->SetBalance(nBalance); }	//	-100�`100
};

#endif//__MglBgm_H__
