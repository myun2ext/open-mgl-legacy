#ifndef __MglBgm_H__
#define __MglBgm_H__

#include "MglBgmBase.h"
//#include "MglMp3Dshow.h"
//#include "MglOgg.h"

//	�N���X�錾
class DLL_EXP CMglBgm : public IMglBgmBase, public CMyuReleaseBase
{
private:
	IMglBgmBase *m_pBgm;
	IMglBgmBase *m_pMp3Dshow;	//	���ꗼ���p�ӂ��Ă�Ӗ����ĂȂ񂩂����������E�E�E
	IMglBgmBase *m_pOgg;		//	���ꗼ���p�ӂ��Ă�Ӗ����ĂȂ񂩂����������E�E�E
								//	���[�A��������Init()�̓s���ゾ�������ȁB�ł�hWnd�ۑ����Ƃ��΁E�E�E�܂��������B
	HWND m_hWnd;

	void InitCheck(){
		if ( m_hWnd == NULL )
			MyuThrow(MGLMSGNO_BGM(1), "CMglBgm::Init()���\�b�h���Ăяo���Ă��������B");
	}
	void LoadCheck(){
		if ( m_pBgm == NULL )
			MyuThrow(MGLMSGNO_BGM(2), "CMglBgm::Load()���\�b�h���Ăяo���Ă��������B");
	}

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMglBgm();
	virtual ~CMglBgm();

	//	������/�I�[�n
	void Init( HWND hWnd = NULL );
	void Release();

	void Load( const char* szAudioFile );
	void Unload(){ InitCheck(); m_pBgm->Unload(); m_pBgm = NULL; }
	//void Unload(){ Release(); }	//	�������ł����񂶂�Ȃ��́E�E�E�H�Ⴄ���E�E�E

	//	�Đ�����n
	void Play(){ LoadCheck(); m_pBgm->Play(); }
	void LoopPlay( int nLoopCnt=MGL_AUDIO_LOOP_MAX ){ LoadCheck(); m_pBgm->LoopPlay(nLoopCnt); }
	void Stop(){ LoadCheck(); m_pBgm->Stop(); }
	void SetLastLoop(){ LoadCheck(); m_pBgm->SetLastLoop(); }
	void Pause(){ LoadCheck(); m_pBgm->Pause(); }

	void SetVolume( int nVolume=MGL_VOLUME_MAX ){ LoadCheck(); m_pBgm->SetVolume(nVolume); }	//	100����
	void SetBalance( int nBalance=MGL_PAN_CENTER ){ LoadCheck(); m_pBgm->SetBalance(nBalance); }	//	-100�`100
};

#endif//__MglBgm_H__
