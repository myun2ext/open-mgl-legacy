//////////////////////////////////////////////////////////
//
//	MglImageManager  v0.20.00 07/03/18
//		- バッファ統括クラス
//
//	v0.10.02 04/11/14
//	・InitCheck()使って無いし…。
//	・レイヤーぢゃないょ。サーフェスだょ…。
//
//	v0.10.50 04/11/19
//	・STLのメモリ問題解決
//
//	v0.12.00 04/12/12
//	・CMyuStringNameMapを使用するように修正
//
//	v0.12.10 04/12/22
//	・Delete(), Clear()実装

//07/03/18
//
//////////////////////////////////////////////////////////

#ifndef __MglImageManager_H__
#define __MglImageManager_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MyuStringNameMap.h"

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglImageManager
{
protected:
	//	サーフェスマップ
	CMyuStringNameMap<CMglImage> m_buffers;

	//	保護メンバ変数
	//BOOL m_bInit;
	CMglGraphicManager* m_myudg;	//	CMglGraphicManagerへのポインタを格納
	_MGL_IDirect3DDevice* d3d;			//	D3DDeviceへのポインタ
	string m_strRootDir;

	//	保護メソッド
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}
	/*void InitCheck() {
		if ( initFlg == FALSE )
			MyuThrow( 0, "CMglImageManager Init()を一番最初に呼んでください。" );
	}*/

public:
	//	初期化・開放系メソッド
	CMglImageManager();
	virtual ~CMglImageManager();
	void Init( CMglGraphicManager *in_myudg );
	void Release();	//	開放
	void DeleteAll();	//	全てのサーフェスを削除（現時点ではRelease()と同じ）

	//void SetRootDirectory( const char* szRootDir ){ m_strRootDir = szRootDir; PathLastYenedString(m_strRootDir); }
	void SetRootDirectory( const char* szRootDir );
	CMglImage* Add( const char *szBufferName );
	CMglImage* AddFile( const char *szBufferName ){
		return Add(szBufferName, szBufferName);	}
	CMglImage* Add( const char *szImageFileName, const char *szBufferName,
		BOOL bRenderTarget=RENDER_TARGET_DEFAULT, D3DCOLOR colorKey=DEF_COLORKEY );
	CMglImage* Get( const char *szBufferName );
	BOOL IsExist( const char *szBufferName );
	void Delete( const char *szBufferName );

	//	オペレータ[]
	CMglImage* operator[]( const char *szBufferName ) { return Get(szBufferName); };
};

typedef CMglImageManager CMglImageBuffer;
typedef CMglImageManager CMglImagePool;
typedef CMglImageManager CMglImageLoader;

#endif//__MglImageManager_H__