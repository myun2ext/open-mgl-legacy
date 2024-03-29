//////////////////////////////////////////////////////////
//
//	AugustSound
//
//////////////////////////////////////////////////////////

#ifndef __SFJP_MGL__AugustSound_H__
#define __SFJP_MGL__AugustSound_H__

#include "agh.h"
#include "AugustCommon2.h"

#define _MGL_AUGUST_SOUND_CORE_IMPL		CMglDirectMusicBase
class _MGL_AUGUST_SOUND_CORE_IMPL;

/////////////////////////////////////////////////////////////////////////

class _AGST_DLL_EXP agh::CControlBase;

#define AUGUST_SOUND_LOOP_PLAY_INFINITE		(0xffffffff)
#define AUGUST_SOUND_LOOP_PLAY_UNLIMITED	(AUGUST_SOUND_LOOP_PLAY_INFINITE)

//	クラス宣言  /////////////////////////////////////////////////////////
class _AGST_DLL_EXP CAugustSoundManager : public agh::CControlBase
{
protected:
	_MGL_AUGUST_SOUND_CORE_IMPL *m_pCore;

_AGH_EVENT_ACCESS_MODIFIER:
	///// オーバーライド可能なイベント /////////////////////////////////////////////////

	virtual void OnRegist();
	//virtual bool DoFrame();

public:
	//	コンストラクタ・デストラクタ
	CAugustSoundManager();
	virtual ~CAugustSoundManager();

	///////////////////////////////////////////////////////////////

	void Load( const char* szAudioFile, const char* szAlias=NULL );
	void Play( const char* szName );
	void LoopPlay( const char* szName, unsigned long nLoopCount=AUGUST_SOUND_LOOP_PLAY_INFINITE );
	void Stop( const char* szName );

	bool IsAlreadyUsedAlias( const char* szName );

	void SetVolume( float fVolume=100.0f );	/*  200.0f〜0.0f  */
	//SetBalance() 未実装

	void Disable();
	void Enable();

	enum {
		LOOP_INFINITE = AUGUST_SOUND_LOOP_PLAY_INFINITE,
		LOOP_UNLIMITED = AUGUST_SOUND_LOOP_PLAY_UNLIMITED
	};
};

//typedef CAugustSound CAugustSound2;
//typedef CAugustSound CAugustSoundManager, CAugustSoundManager2;
typedef CAugustSoundManager CAugustSoundManager2;


/******************************************************************************************/

//class _AGST_DLL_EXP CAugustSound : public agh::CControlBase
class _AGST_DLL_EXP CAugustSound : public CAugustControlBase
{
protected:
	CAugustSoundManager* m_pMgr;
	std::string m_name;
	bool m_bMultiplePlay;

private:
	void SelectUniqueName( /*const char* szName*/ );

_AGH_EVENT_ACCESS_MODIFIER:
	///// オーバーライド可能なイベント /////////////////////////////////////////////////

	virtual void OnRegist();

public:
	//	コンストラクタ・デストラクタ
	CAugustSound();
	virtual ~CAugustSound(){}

	///////////////////////////////////////////////////////////////

	void Load( const char* szAudioFile );
	void Play();
	void LoopPlay( unsigned long nLoopCount=AUGUST_SOUND_LOOP_PLAY_INFINITE );
	void Stop();

	//void SetVolume( float fVolume=100.0f );	/*  200.0f〜0.0f  */
	//SetBalance() 未実装

	//void Disable();	いる？いらないと思うからとりあえず廃止
	//void Enable();	いる？いらないと思うからとりあえず廃止

	void EnableMultiplePlay(){ m_bMultiplePlay = true; }
	void DisableMultiplePlay(){ m_bMultiplePlay = false; }
};

#endif//__SFJP_MGL__AugustSound_H__
