//////////////////////////////////////////////////////////
//
//	MglMouseInput - �}�E�X���̓N���X
//
//////////////////////////////////////////////////////////

#ifndef __MglMouseInput_H__
#define __MglMouseInput_H__

#include "MglMouseInputBase.h"

#define STATEBUF_SIZE	(256)

//	�N���X�錾
class DLL_EXP CMglMouseInput : public CMglMouseInputBase
{
protected:

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglMouseInput();
	virtual ~CMglMouseInput();
};


#endif//__MglMouseInput_H__