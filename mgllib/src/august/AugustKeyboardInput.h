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

class _AGST_DLL_EXP agh::CKeyboardBase;

class _AGST_DLL_EXP CAugustKeyboardInput : public agh::CKeyboardBase
{
	//	イベントハンドラの実装
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist();

	virtual bool OnFrame();	//	override

public:
	//	コンストラクタ・デストラクタ
	CAugustKeyboardInput();
	virtual ~CAugustKeyboardInput();
};

typedef CAugustKeyboardInput CAugustKeyboardInput2;
typedef CAugustKeyboardInput CAugustKeyboard, CAugustKeyboard2;

#endif//__AugustKeyboardInput_H__
