//////////////////////////////////////////////////////////
//
//	AugustGraphicsManager
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustGraphicsManager.h"
#include "MglGraphicManager.h"
#include "AugustWindow2.h"

using namespace agh;
using namespace std;

//	コンストラクタ
CAugustGraphicsManager::CAugustGraphicsManager()
{
	m_pGrp = new CMglGraphicManager();

	//m_rgbBackground = AGHCOLOR_WHITE;
}

//	デストラクタ
CAugustGraphicsManager::~CAugustGraphicsManager()
{
	SAFE_DELETE(m_pGrp);
}



//////////////////////////////////////////////////

#define grp		(*m_pGrp)
#define m_grp	(*m_pGrp)

//	初期化
void CAugustGraphicsManager::Init(bool bIsFullscreen)
{
	_MGL_DEBUGLOG("grp.Init()..." );

	//CAugustWindow2* pWindow = (CAugustWindow2*)_BASE::GetParentControl();
	//CAugustWindow2* pWindow = (CAugustWindow2*)MyuAssertNull(_BASE::GetParentControl(),
	m_pWindow = (CAugustWindow2*)MyuAssertNull(_BASE::GetParentControl(),
		"CAugustGraphicsManager: 親コントロールが見つかりません。親コントロールへの追加がされているか確認してください。");

	//HWND hWnd = (HWND)GetValPtr(MWLAGH_VALKEY_HWND);
	//HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_HWND),
	HWND hWnd = (HWND)MyuAssertNull(GetValPtr(MWLAGH_VALKEY_ROOT_WINDOW_HWND),
		"CAugustGraphicsManager::Init()  ウインドウハンドルの取得に失敗");

	m_pGrp->Init( hWnd, m_pWindow->GetWidth(), m_pWindow->GetHeight(), bIsFullscreen );

	Clear();
}

//	開放
void CAugustGraphicsManager::Release()
{
	m_grp.Release();
}

//	クリア
void CAugustGraphicsManager::Clear(){
	//m_grp.Clear(m_rgbBackground);	//	2008/11/29 CAugustGraphicsManager対応
	m_grp.Clear(m_pWindow->GetColor());
}
void CAugustGraphicsManager::Clear(agh::AGHCOLOR color){
	m_grp.Clear(color);	//	2008/11/29 CAugustGraphicsManager対応
}

//	描画
void CAugustGraphicsManager::OnDraw()
{
	Clear();

	/*
	for(int i=0; i<m_ctrlPtrAry.size(); _vcpp(i))
	{
		GetVCtrlPtr(i)->Draw();
	}
	*/
	for(int i=0; i<m_ctrlPtrAry.size(); i++)
	{
		agh::CControlBase *pCtrl = m_ctrlPtrAry[i];
		if ( pCtrl->IsVisual() )
			((agh::CVisualControlBase*)pCtrl)->Draw();
	}
}

//	フレーム処理
bool CAugustGraphicsManager::DoFrame()
{
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

//	フレームの開始
void CAugustGraphicsManager::FrameStart()
{
	//	スプライト開始
	m_pGrp->SpriteBegin();
}

//	フレームの終了
void CAugustGraphicsManager::FrameEnd()
{
	//	スプライト終了
	m_pGrp->SpriteEnd();

	//	スクリーンのアップデート
	m_pGrp->UpdateScreen();
}
