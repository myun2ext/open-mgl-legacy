//////////////////////////////////////////////////////////
//
//	MglSurfacesManager
//		- バッファ統括クラス
//
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MglSurfacesManager.h"

//	コンストラクタ
CMglSurfacesManager::CMglSurfacesManager()
{
	initFlg = FALSE;

	//	CMyuStringNameMapのメッセージ
	m_buffers.SetMessage(
		"CMglSurfacesManager::Add()  既に\"%s\"の名前のサーフェスは存在します。",
		"CMglSurfacesManager::Get()  \"%s\"の名前のサーフェスは存在しません。" );
}

//	デストラクタ
CMglSurfacesManager::~CMglSurfacesManager()
{
	Release();
}


//	初期化
void CMglSurfacesManager::Init( CMglGraphicManager *in_myudg, const char* szMgrName )
{
	//	Direct3D系
	myudg = in_myudg;
	d3d = myudg->GetD3dDevPtr();
	m_strMgrName = szMgrName;

	initFlg = TRUE;
}

//	開放
void CMglSurfacesManager::Release()
{
	DeleteAll();
}

//	全てのサーフェスを削除（現時点ではRelease()と同じ）
void CMglSurfacesManager::DeleteAll()
{
	//_MGL_DEBUGLOG( "+ CMglSurfacesManager::DeleteAll()" );
	m_buffers.DeleteAll();
	//_MGL_DEBUGLOG( "- CMglSurfacesManager::DeleteAll()" );
}

//	追加
CMglImage* CMglSurfacesManager::Add( const char *szBufferName )
{
	_MGL_DEBUGLOG( "+ CMglSurfacesManager::Add( \"%s\" )", szBufferName );
	InitCheck();

	CMglImage surface;
	surface.Init( myudg );

	//	サーフェス名称生成
	if ( m_strMgrName != "" ){
		char szSurfaceName[256];
		snprintf( szSurfaceName, sizeof(szSurfaceName),
			"%s[\"%s\"]", m_strMgrName.c_str(), szBufferName );
		surface.SetName( szSurfaceName );
	}
	else
		surface.SetName( szBufferName );

	m_buffers.Add( szBufferName, surface );

	_MGL_DEBUGLOG( "- CMglSurfacesManager::Add( \"%s\" )", szBufferName );

	return Get( szBufferName );
}

//	取得
CMglImage* CMglSurfacesManager::Get( const char *szBufferName )
{
	return m_buffers.Get( szBufferName );
}

//	削除
void CMglSurfacesManager::Delete( const char *szBufferName )
{
	m_buffers.Delete( szBufferName );
}
