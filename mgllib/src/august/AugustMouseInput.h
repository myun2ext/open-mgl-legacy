//////////////////////////////////////////////////////////
//
//	AugustMouseInput
//
//////////////////////////////////////////////////////////

#ifndef __AugustMouseInput_H__
#define __AugustMouseInput_H__

#include "agh.h"
#include "AugustCommon2.h"

//	�N���X�錾  /////////////////////////////////////////////////////////

class _AGST_DLL_EXP CAugustMouseInput : public agh::CMouseBase
{
	//	�C�x���g�n���h���̎���
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist();

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustMouseInput();
	virtual ~CAugustMouseInput();
};


#endif//__AugustMouseInput_H__
