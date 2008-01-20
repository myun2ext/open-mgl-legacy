//////////////////////////////////////////////////////////
//
//	MglLayer - レイヤー
//
//////////////////////////////////////////////////////////

#ifndef __MglLayer_H__
#define __MglLayer_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MglImageManager.h"

//	内部的マクロ
//#define iLayerInfos(V1)	layerInfos[indexs[V1]]
//#define iBuffers(V1)		buffers[indexs[V1]]
#define iLayerInfos(V1)		p_layerInfos->find( p_indexs->find(V1)->second )->second
#define iBuffers(V1)		m_buffers.Get( p_indexs->find(V1)->second.c_str() )

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglLayer : public CMglImageManager
{
private:
	typedef struct {
		BOOL bShow;			//	表示するか
		RECT rect;			//	矩形領域
		D3DCOLOR color;		//	アルファ値 | カラー
	} LAYERINFO;

	//map<string,LAYERINFO> layerInfos;
	//map<int,string> indexs;
	typedef map<string,LAYERINFO> LAYERINFOS_MAP;
	typedef map<int,string> INDEXS_MAP;
	LAYERINFOS_MAP *p_layerInfos;
	INDEXS_MAP *p_indexs;

	//	レンダリング用サーフェス
	CMglImage m_renderingSurface;

	//	前回はどのサーフェスにレンダリングしようとしたか
	CMglImage* m_pPrevTargetSurface;

	//	CreateFromFile用に記憶
	char m_szDummyFile[MAX_PATH+1];
	D3DCOLOR m_colorKey;

	//	前回のレンダリングを適用する
	void AdaptRenderingSurface();

public:
	//	コンストラクタ/デストラクタ
	CMglLayer();
	virtual ~CMglLayer();

	//	初期化・開放系メソッド
	void Init( CMglGraphicManager *in_myudg, const char* in_szDummyFile, D3DCOLOR colorKey=DEF_COLORKEY );
	void Release();		//	開放
	void DeleteAll();	//	全てのレイヤーを削除（現時点ではRelease()と同じ）

	void Add( const char *szBufferName );
	CMglImage* AddEntry( const char *szBufferName );
	CMglImage* GetRenderingSurface( const char *szLayerName );
	//	Get()は CMglImageBuffers で実装済みなのでいらない罠ｗ
	//CMglImage* Get( const char *szLayerName );
	void SetLayerOption( const char *szLayerName, RECT *rect, D3DCOLOR color );
	void SetLayerOption( const char *szLayerName, RECT *rect );
	void SetLayerOption( const char *szLayerName, D3DCOLOR color );
	void OnDraw( D3DCOLOR baseColor=0 );

	//	便利な拡張メソッド
	void SetRender( const char *szLayerName )			{ Get( szLayerName )->SetRender(); }
	void SetRenderAndClear( const char *szLayerName )	{ SetRender( szLayerName ); Get( szLayerName )->Clear(); }

	//	プロパティ系メソッド
	void SetEnable( int i ) { iLayerInfos(i).bShow = TRUE; };
	void SetDisable( int i ) { iLayerInfos(i).bShow = FALSE; };
	void ChangeEnable( int i ) {
		if ( iLayerInfos(i).bShow == TRUE ) { iLayerInfos(i).bShow = FALSE; }
		else								{ iLayerInfos(i).bShow = TRUE;  }
	}

	void SetEnable( char *szLayerName )
		{ (*p_layerInfos)[szLayerName].bShow = TRUE; };
	void SetDisable( char *szLayerName )
		{ (*p_layerInfos)[szLayerName].bShow = FALSE; };
	void ChangeEnable( char *szLayerName ) {
		if ( (*p_layerInfos)[szLayerName].bShow == TRUE ) { (*p_layerInfos)[szLayerName].bShow = FALSE; }
		else											  { (*p_layerInfos)[szLayerName].bShow = TRUE;  }
	}
};


#endif//__MglLayer_H__