//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//
//////////////////////////////////////////////////////////

#ifndef __AugustKeyboardInput_H__
#define __AugustKeyboardInput_H__

#include "agh.h"
#include "AugustCommon2.h"

//	�N���X�錾  /////////////////////////////////////////////////////////

class _AGST_DLL_EXP CAugustKeyboardInput : public agh::CKeyboardBase
{
	//	�C�x���g�n���h���̎���
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist();

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustKeyboardInput();
	virtual ~CAugustKeyboardInput();
};


#endif//__AugustKeyboardInput_H__
