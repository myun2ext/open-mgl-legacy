//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

using namespace agh;

bool CMglguiScreen::OnFrameMouseInput()
{
	int x = m_mouse.GetCursorPosX();
	int y = m_mouse.GetCursorPosY();
	int nMoveX = m_mouse.GetXMoveCount();
	int nMoveY = m_mouse.GetYMoveCount();

	agh::CControlBase *pControl = GetPosControl(x,y);
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
		pControl->OnMouseMove(x, y, nMoveX, nMoveY);
		ret = true;
	}

	//	真中ボタンを押した
	if ( m_mouse.IsOnDownCenterButton() ){
		//CScreenBase::OnCButtonDown(x,y);
		pControl->OnCButtonDown(x,y);
		ret = true;
	}

	//	左ボタンを押した
	if ( m_mouse.IsOnDownLeftButton() ){

		//	ウインドウの範囲外ならイベント範囲外とする
		if ( x < 0 || y < 0 ||
			 x >= CMglEzGameFrame::m_nWidth || y >= CMglEzGameFrame::m_nHeight )
		{
			//	何もしない。（if文条件反転にすべきだったね...）
		}
		else
		{
			//CScreenBase::OnLButtonDown(x,y);
			pControl->OnLButtonDown(x,y);
			ret = true;
		}
	}

	//	右ボタンを押した
	if ( m_mouse.IsOnDownRightButton() ){
		//CScreenBase::OnRButtonDown(x,y);
		pControl->OnRButtonDown(x,y);
		ret = true;
	}

	return ret;
}

/*
//	左ボタンが押された
void CMglguiScreen::OnLButtonDown(int x, int y)
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
