//////////////////////////////////////////////////////////
//
//	MglMouseInput - マウス入力クラス
//
//////////////////////////////////////////////////////////

#ifndef __MglMouseInput_H__
#define __MglMouseInput_H__

#include "MglMouseInputBase.h"

#define STATEBUF_SIZE	(256)

//	クラス宣言
class DLL_EXP CMglMouseInput : public CMglMouseInputBase
{
protected:

public:
	//	コンストラクタ・デストラクタ
	CMglMouseInput();
	virtual ~CMglMouseInput();
};


#endif//__MglMouseInput_H__