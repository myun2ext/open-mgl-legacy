//////////////////////////////////////////////////////////
//
//	AugustMouseInput
//
//////////////////////////////////////////////////////////

#ifndef __AugustMouseInput_H__
#define __AugustMouseInput_H__

#include "agh.h"
#include "AugustCommon2.h"

//	クラス宣言  /////////////////////////////////////////////////////////

class _AGST_DLL_EXP CAugustMouseInput : public agh::CMouseBase
{
	//	イベントハンドラの実装
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist();

public:
	//	コンストラクタ・デストラクタ
	CAugustMouseInput();
	virtual ~CAugustMouseInput();
};


#endif//__AugustMouseInput_H__
