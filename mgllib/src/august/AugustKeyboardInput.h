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

class _AGST_DLL_EXP agh::CKeyboardBase;

class _AGST_DLL_EXP CAugustKeyboardInput : public agh::CKeyboardBase
{
	//	�C�x���g�n���h���̎���
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist();

	virtual bool OnFrame();	//	override

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustKeyboardInput();
	virtual ~CAugustKeyboardInput();
};

typedef CAugustKeyboardInput CAugustKeyboardInput2;
typedef CAugustKeyboardInput CAugustKeyboard, CAugustKeyboard2;

#endif//__AugustKeyboardInput_H__
