//////////////////////////////////////////////////////////
//
//	AugustGraphicsManager
//		- MglGraphicManager レイヤークラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AugustGraphicsManager.h"
#include "MglGraphicManager.h"
#include "MglImage.h"
#include "AugustWindow2.h"


////////////////////////////////////////////////////////

class CMglImage;
class CMglGraphicManager;

//class _AGST_DLL_EXP CAugustImageLoader : public agh::util::CLoaderBase<CAugustImage2_2>
class _AGST_DLL_EXP CAugustImageLoader : public agh::util::CLoaderBase<CMglImage>
{
private:
	//typedef CAugustImage2_2 _IMG;
	typedef CMglImage _IMG;
	typedef agh::util::CLoaderBase<_IMG> _BASE;

	D3DCOLOR m_colorKey;

protected:
	CMglGraphicManager *m_pGrp;

public:
	//	コンストラクタ・デストラクタ
	CAugustImageLoader(){
		m_pGrp = NULL;
	}
	virtual ~CAugustImageLoader(){}

	/*virtual _IMG* Load(const char* szName){

	}*/

	void SetColorKey(D3DCOLOR colorKey){ m_colorKey = colorKey; }

//	イベントハンドラの実装
_AGH_EVENT_ACCESS_MODIFIER:

	virtual void OnRegist(){
		m_pGrp = (CMglGraphicManager*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_GRP),
			"CAugustImageLoader: GetValPtr(AUGUST_VALKEY_GRP) の取得に失敗。");
	}

	virtual bool OnNewLoaderAppend(const char* szName, _IMG* pItem);
};

/*
//class _AGST_DLL_EXP CAugustImageLoader : public agh::util::CLoaderBase<CAugustImage2_2>
class _AGST_DLL_EXP CAugustImageLoader : public agh::util::CLoaderBase<CMglImage>
{
private:
	//typedef CAugustImage2_2 _IMG;
	typedef CMglImage _IMG;
	typedef agh::util::CLoaderBase<_IMG> _BASE;

protected:
	CMglGraphicManager *m_pGrp;

public:
	//	コンストラクタ・デストラクタ
	CAugustImageLoader(){
		m_pGrp = NULL;
	}
	virtual ~CAugustImageLoader(){}

	/*virtual _IMG* Load(const char* szName){

	}*//*

//	イベントハンドラの実装
_AGH_EVENT_ACCESS_MODIFIER:

	virtual void OnRegist(){
		m_pGrp = (CMglGraphicManager*)MyuAssertNull(GetValPtr(AUGUST_VALKEY_GRP),
			"CAugustImageLoader: GetValPtr(AUGUST_VALKEY_GRP) の取得に失敗。");
	}

	virtual bool OnNewLoaderAppend(const char* szName, _IMG* pItem){
		pItem->Init(m_pGrp);
		pItem->Create(szName);
		return true;
	}
};*/

bool CAugustImageLoader::OnNewLoaderAppend(const char* szName, _IMG* pItem)
{
	pItem->Init(m_pGrp);

	if ( m_colorKey == 0 )
		pItem->Create(szName);
	else
		pItem->Create(szName, FALSE, m_colorKey);

	return true;
}


////////////////////////////////////////////////

using namespace agh;
using namespace std;

//	コンストラクタ
CAugustGraphicsManager::CAugustGraphicsManager()
{
	m_pGrp = new CMglGraphicManager();
	m_pImageLoader = new CAugustImageLoader();	//	どっちでも行けるようにnewのままにしてるのかな・・・？

	/*	2009/05/16  後でやらないと属性のコピーが行われないっち・・・
	//m_rgbBackground = AGHCOLOR_WHITE;

	//	2009/05/13
	SetValPtr(AUGUST_VALKEY_GRP, m_pGrp);
	SetValPtr(AUGUST_VALKEY_AGRPM, this);
	SetValPtr(AUGUST_VALKEY_IMAGE_LOADER, m_pImageLoader);

	//	2009/05/13
	RegistSubControl(m_pImageLoader);
	//RegistSubControl(m_imageLoader);
	*/
}

//	デストラクタ
CAugustGraphicsManager::~CAugustGraphicsManager()
{
	SAFE_DELETE(m_pImageLoader);
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

	/////////////////////////////////////////////////////////////
	//
	//	2009/05/16  ここでやらないと属性のコピーが行われないっち・・・
	
	//	2009/05/13
	SetValPtr(AUGUST_VALKEY_GRP, m_pGrp);
	SetValPtr(AUGUST_VALKEY_AGRPM, this);
	m_pWindow->SetValPtr(AUGUST_VALKEY_GRP, m_pGrp);	//	2009/05/18
	m_pWindow->SetValPtr(AUGUST_VALKEY_AGRPM, this);	//	2009/05/18

	//	2009/05/13
	RegistSubControl(m_pImageLoader);
	SetValPtr(AUGUST_VALKEY_IMAGE_LOADER, m_pImageLoader);
	m_pWindow->SetValPtr(AUGUST_VALKEY_IMAGE_LOADER, m_pImageLoader);	//	2009/05/18

	////////////////////////////////////////////////

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
void CAugustGraphicsManager::Clear(agh::COLOR color){
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
			((agh::CVisualControlBase*)pCtrl)->OnDraw();
			//((agh::CVisualControlBase*)pCtrl)->Draw();
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

CMglImage* CAugustGraphicsManager::LoadImage(const char* szImageFilepath, D3DCOLOR colorKey)
{
	m_pImageLoader->SetColorKey(colorKey);
	return m_pImageLoader->Load(szImageFilepath);
}