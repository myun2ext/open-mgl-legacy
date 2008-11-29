//////////////////////////////////////////////////////////
//
//	AugustScreen
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustScreen.h"

using namespace agh;

//	マウス入力
bool CAugustScreen::OnFrameMouseInput()
{
	/*int x = g_->mouse->GetCursorPosX();
	int y = g_->mouse->GetCursorPosY();*/
	//POINT point = g_->mouse->GetCursorPos();
	m_nCachedCurPos = g_->mouse->GetCursorPos();
	int x = m_nCachedCurPos.x;
	int y = m_nCachedCurPos.y;
	m_nCachedCurPosX = x;
	m_nCachedCurPosY = y;
	int nMoveX = g_->mouse->GetXMoveCount();
	int nMoveY = g_->mouse->GetYMoveCount();

//#define _P this
#define _P pControl
	agh::CVisualControlBase *pControl = GetPosControl(x,y);
	if ( pControl == NULL )
		pControl = this;

	/*	例えばドラッグで画面外の時に対応出来ないのでここではチェックしない事とする
	//	ウインドウの範囲外ならイベント範囲外とする
	if ( x < 0 || y < 0 ||
		 x > )
		return false;
	*/

	//	割り込み処理
	OnMouseEventInterrupt(pControl, x, y, nMoveX, nMoveY);

	bool ret = false;

	//	マウス移動
	if ( nMoveX != 0 || nMoveY != 0 ){
		//CScreenBase::OnMouseMove(x, y, nMoveX, nMoveY); <- これじゃあ継承した方が呼ばれないぢゃない・・・
		_P->OnMouseMove(x, y, nMoveX, nMoveY);
		ret = true;
	}

	//	真中ボタンを押した
	if ( g_->mouse->IsOnDownCenterButton() ){
		//	ウインドウの範囲外ならイベント範囲外とする
		if ( x < 0 || y < 0 ||
			 x >= g_->nWindowWidth || y >= g_->nWindowHeight )
		{
			//	何もしない。（if文条件反転にすべきだったね...）
		}
		else
		{
			//CScreenBase::OnCButtonDown(x,y);
			_P->OnCButtonDown(x,y);
			ret = true;
		}
	}

	//	左ボタンを押した
	if ( g_->mouse->IsOnDownLeftButton() ){

		//	ウインドウの範囲外ならイベント範囲外とする
		if ( x < 0 || y < 0 ||
			 x >= g_->nWindowWidth || y >= g_->nWindowHeight )
		{
			//	何もしない。（if文条件反転にすべきだったね...）
		}
		else
		{
			//CScreenBase::OnLButtonDown(x,y);
			_P->OnLButtonDown(x,y);
			ret = true;
		}
	}

	//	右ボタンを押した
	if ( g_->mouse->IsOnDownRightButton() ){

		//	ウインドウの範囲外ならイベント範囲外とする
		if ( x < 0 || y < 0 ||
			 x >= g_->nWindowWidth || y >= g_->nWindowHeight )
		{
			//	何もしない。（if文条件反転にすべきだったね...）
		}
		else
		{
			//CScreenBase::OnRButtonDown(x,y);
			_P->OnRButtonDown(x,y);
			ret = true;
		}
	}

	//// 離した ////////////////////////////

	//	真中ボタンを離した
	if ( g_->mouse->IsOnUpCenterButton() ){
		//CScreenBase::OnCButtonUp(x,y);
		_P->OnCButtonUp(x,y);
		ret = true;
	}

	//	左ボタンを離した
	if ( g_->mouse->IsOnUpLeftButton() ){
		//CScreenBase::OnLButtonUp(x,y);
		_P->OnLButtonUp(x,y);
		ret = true;
	}

	//	右ボタンを離した
	if ( g_->mouse->IsOnUpRightButton() ){
		//CScreenBase::OnRButtonUp(x,y);
		_P->OnRButtonUp(x,y);
		ret = true;
	}

	return ret;
}

////////////////////////////////////////////////////////////

bool CAugustScreen::OnFrameKeyboardInput()
{
	t_AUGUST_KB_EVT_HANDLERS::iterator it=m_kbEventHandlers.begin();
	for(; it!=m_kbEventHandlers.end(); it++)
	{
		AUGUST_KB_EVT_HANDLER &r = *it;

		switch(r.evtType)
		{
		case AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_PRESS:
			if ( g_->input->IsPressKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;

		case AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYDOWN:
			if ( g_->input->IsOnDownKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;

		case AUGUST_KB_EVT_HANDLER_EVTTYPE_ON_KEYUP:
			if ( g_->input->IsOnUpKey(r.keyCode) )
				if ( (this->*r.pCallbackFunc)() != true )
					return false;
			break;
		}
	}

	return true;
}


/*
//	左ボタンが押された
void CAugustScreen::OnLButtonDown(int x, int y)
{
	agh::CControlBase *pControl = GetPosControl(x,y);
	if ( pControl == NULL )
		pControl->OnLButtonDown(x,y);
	else
		OnBackgroundLButtonDown(x,y);
}
*/

/*
//	左ボタンが押された
void CAugustScreen::OnLButtonDown(int x, int y)
{
	//	コントロールで該当するものがあるか？
	for(int i=0; i<m_controlPtrAry.size(); i++)
	{
		CControlBase *p = m_controlPtrAry[i];
		_AGH_RECT& rect = p->GetRect();

		if ( IsRectInternal((_MSL_RECT*)&rect, x, y) ){
			OnControlLButtonDown(p,x,y);
			return;
		}
	}

	//	どのコントロールにも一致しない場合はバックグラウンド
	OnBackgroundLButtonDown(x,y);
}
*/
