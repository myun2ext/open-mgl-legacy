//////////////////////////////////////////////////////////
//
//	AugustKeyboardInput
//
//////////////////////////////////////////////////////////

#ifndef __AugustKeyboardInput_H__
#define __AugustKeyboardInput_H__

#include "agh.h"

class CMglInput;

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CAugustKeyboardInput : public agh::CKeyboardBase
{
protected:
	CMglInput *m_pInput;			//	Alias

	/////////////////////////////////////////////////////////

_AGH_EVENT_ACCESS_MODIFIER:
	///// オーバーライド可能なイベント /////////////////////////////////////////////////

	/**
	  ここにあった OnControl, OnBackground は下に移動しといたよ。
	**/
	virtual bool DoFrame();

public:
	//	コンストラクタ
	//	コンストラクタ
	CAugustKeyboardInput(){}
	virtual ~CAugustKeyboardInput(){}

	//////////////////////////////////////////////////////

};


#endif//__AugustKeyboardInput_H__
