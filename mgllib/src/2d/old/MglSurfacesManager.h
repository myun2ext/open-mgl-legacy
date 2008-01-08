//////////////////////////////////////////////////////////
//
//	MglSurfacesManager

#ifndef __MglSurfacesManager_H__
#define __MglSurfacesManager_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MyuStringNameMap.h"

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglSurfacesManager
{
protected:
	//	サーフェスマップ
	CMyuStringNameMap<CMglImage> m_buffers;

	//	保護メンバ変数
	BOOL initFlg;
	CMglGraphicManager* myudg;	//	CMglGraphicManagerへのポインタを格納
	IDirect3DDevice8* d3d;	//	D3DDeviceへのポインタ
	string m_strMgrName;

	//	保護メソッド
	void InitCheck() {
		if ( initFlg == FALSE )
			MyuThrow( 0, "CMglSurfacesManager Init()を一番最初に呼んでください。" );
	}

public:
	//	初期化・開放系メソッド
	CMglSurfacesManager();
	virtual ~CMglSurfacesManager();
	void Init( CMglGraphicManager *in_myudg, const char* szMgrName="" );
	void Release();	//	開放
	void DeleteAll();	//	全てのサーフェスを削除（現時点ではRelease()と同じ）

	CMglImage* Add( const char *szBufferName );
	CMglImage* Get( const char *szBufferName );
	void Delete( const char *szBufferName );
	BOOL IsExist( const char* szBufferName ){ return m_buffers.IsExist(szBufferName); }

	//	オペレータ[]
	CMglImage* operator[]( const char *szBufferName ) { return Get(szBufferName); };
};


#endif//__MglSurfacesManager_H__