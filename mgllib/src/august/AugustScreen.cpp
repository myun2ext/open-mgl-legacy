//////////////////////////////////////////////////////////
//
//	AugustScreen
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustScreen.h"

using namespace agh;

class DLL_EXP agh::CScreenBase;

/*
//	コンストラクタ
CAugustScreen::CAugustScreen()
{
}

//	デストラクタ
CAugustScreen::~CAugustScreen()
{
}
*/


//////////////////////////////////////////////////

void CAugustScreen::OnDraw()
{
	g_->pGrp->Clear(m_rgbBackground);	//	2008/11/29 CAugustScreen対応

	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	{
		//m_ctrlPtrAry[i]->Draw();
		GetVCtrlPtr(i)->Draw();
	}
}


//	フレーム処理
bool CAugustScreen::DoFrame()
{
	OnFrameMouseInput();	//	なんか拾わないとfalseを返す仕様になってるっぽい・・・
	/*if ( OnFrameMouseInput() != true )
		return false;*/

	if ( OnFrameKeyboardInput() != true )
		return false;

	//	2008/11/02 ユーザイベント処理
	if ( OnFrameDoUser() != true )
		return false;

	return true;
}


/////////////////////////////////////////////////////////////

//	Eventsへ。

/////////////////////////////////////////////////////////////

void CAugustScreen::RegistControl(CMglAghImage* pImage)
{
	const char* szFilePath = pImage->m_strFilePath.c_str();
	const char* szAlias = pImage->m_strLayerName.c_str();

	//	せっとあっぷ
	pImage->_Setup(g_->pGrp, g_->pImgCache);
	
	//	きゃっしゅ
	g_->pImgCache->Cache(szFilePath);

	pImage->SetRect(0,0,g_->pImgCache->Get(szFilePath)->GetBmpWidth(),
		g_->pImgCache->Get(szFilePath)->GetBmpHeight());

	//	そして登録
	_RegistControl(pImage);
	//m_layer.RegistBegin( new CMglImageLayer(m_imgCache[szFilePath]), true );
}
void CAugustScreen::_RegistControl(agh::CControlBase* pCtrl)
{
	m_ctrlPtrAry.push_back(pCtrl);
}
