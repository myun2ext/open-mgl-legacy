//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//
//////////////////////////////////////////////////////////

#ifndef __AugustKeyboardInput_H__
#define __AugustKeyboardInput_H__

#include "agh.h"

class CMglInput;

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CAugustKeyboardInput : public agh::CKeyboardBase
{
protected:
	CMglInput *m_pInput;			//	Alias

	/////////////////////////////////////////////////////////

_AGH_EVENT_ACCESS_MODIFIER:
	///// �I�[�o�[���C�h�\�ȃC�x���g /////////////////////////////////////////////////

	/**
	  �����ɂ����� OnControl, OnBackground �͉��Ɉړ����Ƃ�����B
	**/
	virtual bool DoFrame();

public:
	//	�R���X�g���N�^
	//	�R���X�g���N�^
	CAugustKeyboardInput(){}
	virtual ~CAugustKeyboardInput(){}

	//////////////////////////////////////////////////////

};


#endif//__AugustKeyboardInput_H__
