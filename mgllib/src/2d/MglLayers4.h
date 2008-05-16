//////////////////////////////////////////////////////////
//
//	MglLayers4 - レイヤー
//
//////////////////////////////////////////////////////////

#ifndef __MglLayers4_H__
#define __MglLayers4_H__

#include "MglGraphicManager.h"
//#include "MglImage.h"
#include "MglImageManager.h"
#include "MglLayerBase4.h"

//	内部的マクロ
//#define iLayerInfos(V1)	layerInfos[indexs[V1]]
//#define iBuffers(V1)		buffers[indexs[V1]]
/*#define iLayerInfos(V1)		p_layerInfos->find( p_indexs->find(V1)->second )->second
#define iBuffers(V1)		m_buffers.Get( p_indexs->find(V1)->second.c_str() )*/

/*
class DLL_EXP CMglLayerBase4
{
public:
	virtual void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )=0;
};

class DLL_EXP layer_tLayer4 : public CMglLayerBase4
{
private:
	CMglImage m_img;
public:
	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		m_img.Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
};

typedef CMglLayerBase4 CMglLayerBase;
typedef layer_tLayer4 layer_tLayer;
*/

/*	2008/05/15  ヘッダ作ってそこに定義
class DLL_EXP CMglImageLayer : public CMglLayerBase4
{
private:
	//CMglImage m_img;
	CMglImage* m_pImage;
public:
	//	コンストラクタとしてCMglImageのポインタを渡す
	CMglImageLayer(CMglImage* pImage){ m_pImage=pImage; }

	void Draw(
		float x, float y, CONST RECT *srcRect=NULL, D3DCOLOR color=D3DCOLOR_FULLWHITE,
		float fScaleX=1.0f, float fScaleY=1.0f, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f, float fAngle=0.0f )
	{
		m_pImage->Draw(x,y,srcRect,color,fScaleX,fScaleY,fRotationCenterX,fRotationCenterY,fAngle);
	}
};
*/

//	クラス宣言  /////////////////////////////////////////////////////////
class DLL_EXP CMglLayers4
{
private:
	typedef CMglLayerBase4 layer_t;
	CMglGraphicManager* m_myudg;	//	CMglGraphicManagerへのポインタを格納
	IDirect3DDevice8* m_d3d;		//	D3DDeviceへのポインタ

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

		layer_t* pLayer;	//	レイヤーへのポインタ
		bool isShuoldDeleteLayerPtr;//	レイヤーのポインタをdeleteすべきか
	} LAYERINFO;

	/*
	//map<string,LAYERINFO> layerInfos;
	//map<int,string> indexs;
	typedef map<string,LAYERINFO> LAYERINFOS_MAP;
	LAYERINFOS_MAP *p_layerInfos;
	INDEXS_MAP *p_indexs;
	*/

	//	リスト
	//typedef list<LAYERINFO> LAYER_LIST;
	//typedef map<int,LAYERINFO> LAYER_LIST;
	typedef ra_list<LAYERINFO> LAYER_LIST;
	LAYER_LIST m_list;
	//map<layer_t*,int> m_imagePtrMap;	//	layer_tより高速に検索するためのマップ
	typedef LAYER_LIST::iterator LIST_ITR;
	typedef LAYER_LIST::reverse_iterator LIST_RITR;

	/*
	//	レンダリング用サーフェス
	layer_t m_renderingSurface;

	//	前回はどのサーフェスにレンダリングしようとしたか
	layer_t* m_pPrevTargetSurface;

	//	前回のレンダリングを適用する
	void AdaptRenderingSurface();
	*/

	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

	LAYERINFO& ExistChk(LIST_ITR it){
		return m_list[it];
	}

public:
	typedef LAYER_LIST::iterator LAYER_ITR;
	typedef LAYER_LIST::iterator id_t;

public:
	//	コンストラクタ/デストラクタ
	CMglLayers4();
	virtual ~CMglLayers4();

	//	初期化
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd ){
		m_myudg = in_myudg;
		m_d3d = m_myudg->GetD3dDevPtr();
	}

	//	登録/削除
	//void Regist( layer_t *pLayer, const char *szIdentifierName );
	//void Regist( layer_t *pLayer, LIST_ITR it );
	/*
	
	void Regist( layer_t *pLayer, LIST_ITR it,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f );
	void RegistBegin( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void RegistTail( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void RegistLast( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void PushFront( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void PushBack( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void push_front( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void push_back( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	*/
	void Regist( layer_t *pLayer, LIST_ITR it, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f );

	void PushFront( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), false, x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void PushFront( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), isShouldDeleteLayer, x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void RegistBegin( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void push_front( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }

	void PushBack( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), false, x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void PushBack( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void RegistTail( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void RegistLast( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void push_back( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	/*
	void PushFront( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
	{
		LAYERINFO t;
		ZeroMemory(&t,sizeof(t));
		t.pLayer = pLayer;
		m_list.push_front(
		SetParam(it,x,y,bShow,color,fScaleX,fScaleY,fAngle);
	}
	void push_front( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void RegistBegin( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }

	void Regist( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
	{	PushBack( pLayer, m_list.begin(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void RegistTail( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void RegistLast( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void PushBack( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	void push_back( layer_t *pLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	*/

	void SetParam( LIST_ITR it,
		float x, float y, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f );
	void Move( LIST_ITR it, float x, float y );
	void SetPos( LIST_ITR it, float x, float y );
	void SetColor( LIST_ITR it, D3DCOLOR color );
	void SetScale( LIST_ITR it, float fScale ){
		SetScale(it,fScale,fScale); }
	void SetScale( LIST_ITR it, float fScaleX, float fScaleY );
	void SetAngle( LIST_ITR it, float fAngle );
	void SetRect( LIST_ITR it, RECT rect );
	void SetCenter( LIST_ITR it, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f ){
		SetRotationCenter(it,fRotationCenterX,fRotationCenterY); }
	void SetRotationCenter( LIST_ITR it, float fRotationCenterX=0.5f, float fRotationCenterY=0.5f );

	//void MoveDepth( int oldDepth, int newDepth );	//	未実装

	//	取得
	layer_t* Get( LIST_ITR it ){
		return m_list[it].pLayer;
	}

	/*
	//	取得
	int Find( layer_t *pLayer ){
		if ( m_imagePtrMap.find(pLayer) == m_imagePtrMap.end() )
			return NULL;
		return m_imagePtrMap[pLayer];
	}
	*/

	//	クリアする
	//void Clear(){ ReleaseAll(); m_list.clear(); /*m_imagePtrMap.clear();*/ }
	void Delete(LIST_ITR it);
	void Remove(LIST_ITR it){Delete(it);}
	void DeleteAll(){Clear();}
	void RemoveAll(){Clear();}
	void Clear();

	//	描画
	void Draw(){ Rendering(); }
	void DrawAll(){ Rendering(); }
	void AllDraw(){ Rendering(); }
	void Rendering();

	//	プロパティ系メソッド
	/*void Show( const char* szIdentifierName ) { iLayerInfos(i).bShow = TRUE; };
	void Hide( const char* szIdentifierName ) { iLayerInfos(i).bShow = TRUE; };*/
	void Show( LIST_ITR it ) { ExistChk(it).bShow = TRUE; }
	void Hide( LIST_ITR it ) { ExistChk(it).bShow = FALSE; }

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


#endif//__MglLayers4_H__
