//////////////////////////////////////////////////////////
//
//	AugustMusic
//
//////////////////////////////////////////////////////////

#ifndef __SFJP_MGL__AugustMusic_H__
#define __SFJP_MGL__AugustMusic_H__

#include "agh.h"
#include "AugustCommon2.h"
#include "MyuReleaseBase.h"
#ifndef DLL_EXP
	#define DLL_EXP _AGST_DLL_EXP
#endif
#include "MglBgm.h"

#define _MGL_AUGUST_MUSIC_CORE_IMPL		CMglBgm
class _MGL_AUGUST_MUSIC_CORE_IMPL;

/////////////////////////////////////////////////////////////////////////

class _AGST_DLL_EXP agh::CControlBase;
class _AGST_DLL_EXP CMglBgm;

#define AUGUST_MUSIC_LOOP_PLAY_INFINITE		(0xffffffff)

#define _AGM_USE_INHERIT

//	�N���X�錾  /////////////////////////////////////////////////////////
//class _AGST_DLL_EXP CAugustMusic : public virtual agh::CControlBase, public CMglBgm, public CAugustControlBase
#ifdef _AGM_USE_INHERIT
	class _AGST_DLL_EXP CAugustMusic : public CAugustControlBaseT<agh::CControlBase>, public CMglBgm
#else
	class _AGST_DLL_EXP CAugustMusic : public CAugustControlBaseT<agh::CControlBase>
#endif
{
protected:
	_MGL_AUGUST_MUSIC_CORE_IMPL *m_pCore;
	typedef CAugustControlBaseT<agh::CControlBase> _BASE;


	void InitCheck(){	//	CMglBgm�̂����\�I�[�o�[���C�h�B�i��
		RegistedCheck();
		CMglBgm::InitCheck();
	}

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	virtual void OnRegist();
	//virtual bool DoFrame();

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustMusic();
	virtual ~CAugustMusic();

	///////////////////////////////////////////////////////////////

/*	void Load( const char* szAudioFile );
	void Unload();

	//	�Đ�����n
	void Play();
	void LoopPlay( int nLoopCnt=MGL_AUDIO_LOOP_MAX );
	void Stop();
	void SetLastLoop();
	void Pause();

	void SetVolume( int nVolume=MGL_VOLUME_MAX );	//	100����
	void SetBalance( int nBalance=MGL_PAN_CENTER );	//	-100�`100*/
};

typedef CAugustMusic CAugustMusic2;
typedef CAugustMusic CAugustMusicManager, CAugustMusicManager2;


#endif//__SFJP_MGL__AugustMusic_H__
