//////////////////////////////////////////////////////////
//
//	AugustScreen
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustScreen.h"

using namespace agh;
using namespace std;

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
	//	2009/01/23 マウスのハンドルは無効に出来るように。
	//	（結構処理長いし、うっかりクリックとかで余計な処理走るとまずいし・・・）
	if ( m_bUseMouseHandle == true )
	{
		OnFrameMouseInput();	//	なんか拾わないとfalseを返す仕様になってるっぽい・・・
		/*if ( OnFrameMouseInput() != true )
			return false;*/
	}

	//	キーボードのハンドル処理
	if ( OnFrameKeyboardInput() != true )
		return false;

	//	2008/11/02 ユーザイベント処理
	if ( OnFrameDoUser() != true )
		return false;

	//	各コントロールのフレーム処理
	//for(int i=0; i<m_ctrlPtrAry.size(); i++)
	//for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	for(citr it=cbegin(); it != cend(); it++)
	//for(vector<CControlBase*>::iterator it=cbegin(); it != cend(); it++)
	{
		it->OnFrame();
		//(*it)->OnFrame();
		//((CControlBase*)it)->OnFrame();
		//m_ctrlPtrAry[i]->OnFrame();
		//GetVCtrlPtr(i)->Draw();
	}

	return true;
}


/////////////////////////////////////////////////////////////

//	Eventsへ。

/////////////////////////////////////////////////////////////

/*
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
*/
void CAugustScreen::RegistControl(CAugustVisualControlBase* pControl)
{
	pControl->OnRegist(g_);

	_RegistControlInternal(pControl);
}

void CAugustScreen::_RegistControlInternal(agh::CControlBase* pCtrl)
{
	m_ctrlPtrAry.push_back(pCtrl);
}
