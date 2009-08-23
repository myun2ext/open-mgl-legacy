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

class _AGST_DLL_EXP agh::CMouseBase;

class _AGST_DLL_EXP CAugustMouseInput : public agh::CMouseBase
{
	//	イベントハンドラの実装
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist();

	virtual bool OnFrame();	//	override

public:
	//	コンストラクタ・デストラクタ
	CAugustMouseInput();
	virtual ~CAugustMouseInput();

	agh::_AGH_POINT GetCursorPos();

	/*	純粋なマウス移動量を取得。ウインドウにフォーカスがある時のみ	*/
	agh::CPoint GetPrimitiveMoveCount();
};

typedef CAugustMouseInput CAugustMouseInput2;

#endif//__AugustMouseInput_H__
