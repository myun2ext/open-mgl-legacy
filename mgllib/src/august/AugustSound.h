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

//	�N���X�錾  /////////////////////////////////////////////////////////
class _AGST_DLL_EXP CAugustSound : public agh::CControlBase
{
protected:
	_MGL_AUGUST_SOUND_CORE_IMPL *m_pCore;

	/////////////////////////////////////////////////////////

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	virtual void OnRegist();
	//virtual bool DoFrame();

protected:


public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustSound();
	virtual ~CAugustSound();

};


#endif//__SFJP_MGL__AugustSound_H__
