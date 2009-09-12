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

#define AUGUST_MUSIC_LOOP_PLAY_INFINITE		(0xffffffff)


//	�N���X�錾  /////////////////////////////////////////////////////////
class _AGST_DLL_EXP CAugustMusic : public agh::CControlBase, public CMglBgm, public CAugustControlBase
{
protected:
	_MGL_AUGUST_MUSIC_CORE_IMPL *m_pCore;

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	virtual void OnRegist();
	//virtual bool DoFrame();

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustMusic();
	virtual ~CAugustMusic();

	///////////////////////////////////////////////////////////////

	/*
	void Load( const char* szAudioFile, const char* szAlias=NULL );
	void Play( const char* szName );
	void LoopPlay( const char* szName, unsigned long nLoopCount=AUGUST_SOUND_LOOP_PLAY_INFINITE );
	void Stop( const char* szName );

	void SetVolume( float fVolume=100.0f );
	//SetBalance() ������

	void Disable();
	void Enable();*/
};

typedef CAugustMusic CAugustMusic2;
typedef CAugustMusic CAugustMusicManager, CAugustMusicManager2;


#endif//__SFJP_MGL__AugustMusic_H__
