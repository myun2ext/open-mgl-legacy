//////////////////////////////////////////////////////////
//
//	MglImageManager
//		- バッファ統括クラス
//
//////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MglImageManager.h"

//	コンストラクタ
CMglImageManager::CMglImageManager()
{
	//m_bInit = FALSE;
	m_myudg = NULL;
	d3d = NULL;

	//	CMyuStringNameMapのメッセージ
	m_buffers.SetMessage(
		"CMglImageManager::Add()  既に\"%s\"の名前のサーフェスは存在します。",
		"CMglImageManager::Get()  \"%s\"の名前のサーフェスは存在しません。" );
}

//	デストラクタ
CMglImageManager::~CMglImageManager()
{
	Release();
}


//	初期化
void CMglImageManager::Init( CMglGraphicManager *in_myudg )
{
	//	Direct3D系
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();

	//initFlg = TRUE;
}

//	開放
void CMglImageManager::Release()
{
	DeleteAll();
}

//	全てのサーフェスを削除（現時点ではRelease()と同じ）
void CMglImageManager::DeleteAll()
{
	//_MGL_DEBUGLOG( "+ CMglImageManager::DeleteAll()" );
	m_buffers.DeleteAll();
	//_MGL_DEBUGLOG( "- CMglImageManager::DeleteAll()" );
}

//	追加
CMglImage* CMglImageManager::Add( const char *szImageFileName, const char *szBufferName,
			    BOOL bRenderTarget, D3DCOLOR colorKey)
{
	CMglImage* pImage = CMglImageManager::Add( szBufferName );
	//pImage->Create( szImageFileName, bRenderTarget, colorKey );
	pImage->Create( (m_strRootDir + szImageFileName).c_str(), bRenderTarget, colorKey );
	return pImage;
}

//	追加
CMglImage* CMglImageManager::Add( const char *szBufferName )
{
	_MGL_DEBUGLOG( "+ CMglImageManager::Add( \"%s\" )", szBufferName );
	InitCheck();

	CMglImage surface;
	surface.Init( m_myudg );
	m_buffers.Add( szBufferName, surface );

	_MGL_DEBUGLOG( "- CMglImageManager::Add( \"%s\" )", szBufferName );

	return Get( szBufferName );
}

//	取得
CMglImage* CMglImageManager::Get( const char *szBufferName )
{
	return m_buffers.Get( szBufferName );
}

//	取得
BOOL CMglImageManager::IsExist( const char *szBufferName )
{
	return m_buffers.IsExist( szBufferName );
}

//	削除
void CMglImageManager::Delete( const char *szBufferName )
{
	m_buffers.Delete( szBufferName );
}


void CMglImageManager::SetRootDirectory( const char* szRootDir ){
	m_strRootDir = szRootDir;
	PathLastYenedString(m_strRootDir);
}
