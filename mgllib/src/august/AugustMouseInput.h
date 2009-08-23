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

class _AGST_DLL_EXP agh::CMouseBase;

class _AGST_DLL_EXP CAugustMouseInput : public agh::CMouseBase
{
	//	�C�x���g�n���h���̎���
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist();

	virtual bool OnFrame();	//	override

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CAugustMouseInput();
	virtual ~CAugustMouseInput();

	agh::_AGH_POINT GetCursorPos();
	agh::CPoint GetPrimitiveMoveCount(); 
};

typedef CAugustMouseInput CAugustMouseInput2;

#endif//__AugustMouseInput_H__
