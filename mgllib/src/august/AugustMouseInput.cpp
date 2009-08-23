//////////////////////////////////////////////////////////
//
//	AugustMouseInput
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustMouseInput.h"
#include "MglInput.h"

using namespace agh;
using namespace std;

class DLL_EXP agh::CControlBase;

///////////////////////////////////////////////////////////////

//#define PRESSKEY(DIK_CODE)	(DIK_CODE & 0x80)

//	コアの基底クラス
class CAugustMouseCore : public agh::CMouseCoreBase
{
protected:
	CMglMouseInput m_mouse;
	_AGH_POINT m_oldCurPos;

private:
	_AGH_POINT GetMoveCount(agh::MOUSECODE_t mouseCode)
	{
		if ( mouseCode == agh::CMouseBase::CBUTTON ){

			long z = m_mouse.GetZMoveCount();
			if ( z == 0 )
				return _AGH_POINT(INVALID_POINT, INVALID_POINT);

			return _AGH_POINT(z, INVALID_POINT);	//	xにzを入れる、yは使ってない。
		}
		else
		{
			/*	2回呼び出すのは誤差を引き起こす可能性がある（と言うか起きてるっぽい）ので辞める
			_AGH_POINT moveCount = GetCursorPos() - m_oldCurPos;
			m_oldCurPos = GetCursorPos();
			*/
			_AGH_POINT curPos = GetCursorPos();
			_AGH_POINT moveCount = curPos - m_oldCurPos;
			m_oldCurPos = curPos;

			if ( moveCount.x == 0 && moveCount.y == 0 )	//	xもyも移動量0ならコールバックを呼ばないようにする
				return _AGH_POINT(INVALID_POINT, INVALID_POINT);
			else	
				return moveCount;

			/*
			long x = m_mouse.GetXMoveCount();
			long y = m_mouse.GetYMoveCount();
			
			if ( x != 0 && y != 0 )
				return _AGH_POINT(x, y);

			else	//	xもyも移動量0ならコールバックを呼ばないようにする
				return _AGH_POINT(INVALID_POINT, INVALID_POINT);*/
		}
	}

public:
	//	コンストラクタ・デストラクタ
	CAugustMouseCore(){}
	virtual ~CAugustMouseCore(){}

	//	初期化
	void Init(HWND hWnd)
	{
		m_mouse.Init(hWnd);
		m_oldCurPos = GetCursorPos();
	}

	//////////////////////////////////////////////////////////

	/* override */
	virtual _AGH_POINT IsOnMouseEvt(agh::MOUSE_EVTTYPE_t evtType, agh::MOUSECODE_t mouseCode)
	{
		//	移動
		if ( evtType == AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_MOVE )
			return GetMoveCount(mouseCode);

		BOOL isOnEvt = FALSE;

		//	mouseCodeが有効な範囲内かどうか？
		if ( mouseCode >= AGH_MOUSECODE_LBUTTON && mouseCode <= AGH_MOUSECODE_8TH_BTN )
		{
			switch(evtType)
			{
			//	押されている間
			case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_PRESS:
				isOnEvt = m_mouse.IsPressButton(mouseCode - 0x11);
				break;

			//	押された瞬間
			case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_DOWN:
				isOnEvt = m_mouse.IsOnDownButton(mouseCode - 0x11);
				break;

			//	離された瞬間
			case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_UP:
				isOnEvt = m_mouse.IsOnUpButton(mouseCode - 0x11);
				break;

//			//	移動
//			case AGH_MOUSE_EVT_HANDLER_EVTTYPE_ON_MOVE:
//				return GetMoveCount(mouseCode);
			}
		}

		//	有効な場合は現在のカーソル位置を、無効な場合は(-9999,-9999)を返す。
		//	（ちなみに移動の場合は既にswitch文の中でreturnしている）
		if ( isOnEvt )
			return GetCursorPos();
		else
			return _AGH_POINT(INVALID_POINT, INVALID_POINT);
	}
	
	virtual _AGH_POINT GetCursorPos(){
		::POINT point = m_mouse.GetCursorPos();
		return _AGH_POINT(point.x, point.y);
	}

	agh::CPoint GetPrimitiveMoveCount()
	{
		return agh::CPoint( m_mouse.GetXMoveCount(), m_mouse.GetYMoveCount() );
	}

	//	バッファの更新
	void Update()
	{
		m_mouse.UpdateStateBuf();
	}
};

////////////////////////////////////////////////////////////////////////

//	コンストラクタ
CAugustMouseInput::CAugustMouseInput()
{
	m_pCore = new CAugustMouseCore();
}

//	デストラクタ
CAugustMouseInput::~CAugustMouseInput()
{
	delete m_pCore;
}

//	登録時にInitを呼び出す
void CAugustMouseInput::OnRegist()
{
	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustMouseInput::Init()  ウインドウハンドルの取得に失敗");

	m_pParent->SetValPtr(AUGUST_VALKEY_MOUSE, this);	//	2009/05/18

	((CAugustMouseCore*)m_pCore)->Init(hWnd);
}

//	毎フレーム毎にUpdate()呼び出すの忘れてた・・・
bool CAugustMouseInput::OnFrame()
{
	//	ステータスバッファの更新
	((CAugustMouseCore*)m_pCore)->Update();

	//	スーパークラスのOnFrame()呼び出し
	return agh::CMouseBase::OnFrame();
}

//	カーソル取得の実装
_AGH_POINT CAugustMouseInput::GetCursorPos()
{
	return ((CAugustMouseCore*)m_pCore)->GetCursorPos();
}

agh::CPoint CAugustMouseInput::GetPrimitiveMoveCount()
{
	return ((CAugustMouseCore*)m_pCore)->GetPrimitiveMoveCount();
}
