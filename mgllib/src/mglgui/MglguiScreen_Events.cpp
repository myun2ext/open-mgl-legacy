//////////////////////////////////////////////////////////
//
//	MglguiScreen
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglguiScreen.h"

using namespace agh;

/*
//	左ボタンが押された
void CMglguiScreen::OnLButtonDown(int x, int y)
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
