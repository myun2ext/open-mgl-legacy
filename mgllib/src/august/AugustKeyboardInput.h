//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//
//////////////////////////////////////////////////////////

#ifndef __AugustKeyboardInput_H__
#define __AugustKeyboardInput_H__

#include "agh.h"
#include "AugustCommon2.h"

//	クラス宣言  /////////////////////////////////////////////////////////

class _AGST_DLL_EXP CAugustKeyboardInput : public agh::CKeyboardBase
{
	//	イベントハンドラの実装
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist();

public:
	//	コンストラクタ・デストラクタ
	CAugustKeyboardInput();
	virtual ~CAugustKeyboardInput();
};


#endif//__AugustKeyboardInput_H__
