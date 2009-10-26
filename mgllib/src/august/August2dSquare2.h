//////////////////////////////////////////////////////////
//
//	August2dSquare2
//
//////////////////////////////////////////////////////////

#ifndef __August2dSquare2_H__
#define __August2dSquare2_H__

#include "agh.h"
#include "AugustGraphicsManager.h"

#pragma warning( disable : 4660 ) 
//class DLL_EXP agh::CImageBase;

class CMglImage;

class _AGST_DLL_EXP agh::CVisualControlBase;

//	クラス宣言  /////////////////////////////////////////////////////////

class _AGST_DLL_EXP CAugust2dSquare2 : public CAugustVisualControlBaseT<agh::CVisualControlBase>
{
public:
	static const char* CLASS_NAME;
private:
	//typedef agh::CTextBase _BASE;
	typedef CAugustVisualControlBaseT<agh::CVisualControlBase> _BASE;

protected:
	CMglImage* m_pMglImg;

_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnDraw();
	virtual void OnRegist();

public:
	//	コンストラクタ
	CAugust2dSquare2();
	virtual ~CAugust2dSquare2();

	//	2009/09/29  コピーコンストラクタ対応（STL向け）
	CAugust2dSquare2(const CAugust2dSquare2& from);
};

typedef CAugust2dSquare2 CAugust2dSquare, CAugustSquare2, CAugustSquare, CAugustRect2, CAugustRect;

#endif//__August2dSquare2_H__
