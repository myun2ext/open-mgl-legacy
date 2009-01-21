//////////////////////////////////////////////////////////
//
//	MglLayer3 - レイヤー
//
//////////////////////////////////////////////////////////

#ifndef __MglLayer3_H__
#define __MglLayer3_H__

#include "MglGraphicManager.h"
#include "MglImage.h"
#include "MglImageManager.h"

//	内部的マクロ
//#define iLayerInfos(V1)	layerInfos[indexs[V1]]
//#define iBuffers(V1)		buffers[indexs[V1]]
/*#define iLayerInfos(V1)		p_layerInfos->find( p_indexs->find(V1)->second )->second
#define iBuffers(V1)		m_buffers.Get( p_indexs->find(V1)->second.c_str() )*/

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglLayer3
{
private:
	CMglGraphicManager* m_myudg;	//	CMglGraphicManagerへのポインタを格納
	_MGL_IDirect3DDevice* m_d3d;			//	D3DDeviceへのポインタ

	typedef struct {
		BOOL bShow;			//	表示するか
		RECT rect;			//	矩形領域
		//RECT* pRect;		//	矩形領域。指定されていればrectのポインタが、指定されてなければNULLが入る
		D3DCOLOR color;		//	アルファ値 | カラー

		//	2008/01/20  拡張
		float x, y;				//	場所
		float fScaleX, fScaleY;	//	縮尺率
		float fRotationCenterX;
		float fRotationCenterY;
		float fAngle;			//	角度

		CMglImage *pImage;		//	イメージへのポインタ
	} LAYERINFO;

	/*
	//map<string,LAYERINFO> layerInfos;
	//map<int,string> indexs;
	typedef map<string,LAYERINFO> LAYERINFOS_MAP;
	LAYERINFOS_MAP *p_layerInfos;
	INDEXS_MAP *p_indexs;
	*/

	//	リスト
	//list<LAYERINFO> m_list;
	map<int,LAYERINFO> m_list;
	map<CMglImage*,int> m_imagePtrMap;	//	CMglImageより高速に検索するためのマップ
	typedef map<int,LAYERINFO>::iterator LIST_ITR;
	typedef map<int,LAYERINFO>::reverse_iterator LIST_RITR;

	/*
	//	レンダリング用サーフェス
	CMglImage m_renderingSurface;

	//	前回はどのサーフェスにレンダリングしようとしたか
	CMglImage* m_pPrevTargetSurface;

	//	前回のレンダリングを適用する
	void AdaptRenderingSurface();
	*/

	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

	LAYERINFO& ExistChk(int depth){
		if ( m_list.find(depth) == m_list.end() )
			MyuThrow( 222, "CMglLayer3 : depth=%d は見つかりません。", depth );
		return m_list[depth];
	}


public:
	//	コンストラクタ/デストラクタ
	CMglLayer3();
	virtual ~CMglLayer3();

	//	初期化
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){
		m_myudg = in_myudg;
		m_d3d = m_myudg->GetD3dDevPtr();
	}

	//	登録/削除
	//void Regist( CMglImage *pImage, const char *szIdentifierName );
	//void Regist( CMglImage *pImage, int depth );
	void Regist( CMglImage *pImage, int depth,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f );
	void SetParam( int depth,
		float x, float y, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f );
	void Move( int depth, float x, float y );
	void SetPos( int depth, float x, float y );
	void SetColor( int depth, D3DCOLOR color );
	void SetScale( int depth, float fScale ){
		SetScale(depth,fScale,fScale); }
	void SetScale( int depth, float fScaleX, float fScaleY );
	void SetAngle( int depth, float fAngle );
	void SetRect( int depth, RECT rect );
	void SetCenter( int depth, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f ){
		SetRotationCenter(depth,fRotationCenterX,fRotationCenterY); }
	void SetRotationCenter( int depth, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f );

	void MoveDepth( int oldDepth, int newDepth );	//	未実装

	//	取得
	CMglImage* Get( int depth ){
		if ( m_list.find(depth) == m_list.end() )
			return NULL;
		return m_list[depth].pImage;
	}

	//	取得
	int Find( CMglImage *pImage ){
		if ( m_imagePtrMap.find(pImage) == m_imagePtrMap.end() )
			return NULL;
		return m_imagePtrMap[pImage];
	}

	//	クリアする
	void Clear(){ m_list.clear(); m_imagePtrMap.clear(); }

	//	描画
	void Draw(){ Rendering(); }
	void DrawAll(){ Rendering(); }
	void AllDraw(){ Rendering(); }
	void Rendering();

	//	プロパティ系メソッド
	/*void Show( const char* szIdentifierName ) { iLayerInfos(i).bShow = TRUE; };
	void Hide( const char* szIdentifierName ) { iLayerInfos(i).bShow = TRUE; };*/
	void Show( int depth ) { ExistChk(depth).bShow = TRUE; }
	void Hide( int depth ) { ExistChk(depth).bShow = FALSE; }

	/*
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
	*/
};


#endif//__MglLayer3_H__
