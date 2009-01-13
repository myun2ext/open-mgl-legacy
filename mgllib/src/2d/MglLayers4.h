//////////////////////////////////////////////////////////
//
//	MglLayers4 - ���C���[
//
//////////////////////////////////////////////////////////

#ifndef __MglLayers4_H__
#define __MglLayers4_H__

#include "MglGraphicManager.h"
//#include "MglImage.h"
#include "MglImageManager.h"
#include "MglLayerBase4.h"

//	�����I�}�N��
//#define iLayerInfos(V1)	layerInfos[indexs[V1]]
//#define iBuffers(V1)		buffers[indexs[V1]]
/*#define iLayerInfos(V1)		p_layerInfos->find( p_indexs->find(V1)->second )->second
#define iBuffers(V1)		m_buffers.Get( p_indexs->find(V1)->second.c_str() )*/

class CMglLayers4HitTest;

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CMglLayers4
{
private:
	typedef CMglLayerBase4 layer_t;
	CMglGraphicManager* m_myudg;	//	CMglGraphicManager�ւ̃|�C���^���i�[
	_MGL_IDirect3DDevice* m_d3d;		//	D3DDevice�ւ̃|�C���^
	CMglLayers4HitTest *m_pHitTestMap;

	typedef struct {
		BOOL bShow;			//	�\�����邩
		RECT rect;			//	��`�̈�
		//RECT* pRect;		//	��`�̈�B�w�肳��Ă����rect�̃|�C���^���A�w�肳��ĂȂ����NULL������
		D3DCOLOR color;		//	�A���t�@�l | �J���[

		//	2008/01/20  �g��
		float x, y;				//	�ꏊ
		float fScaleX, fScaleY;	//	�k�ڗ�
		float fRotationCenterX;
		float fRotationCenterY;
		float fAngle;			//	�p�x

		layer_t* pLayer;	//	���C���[�ւ̃|�C���^
		bool isShuoldDeleteLayerPtr;//	���C���[�̃|�C���^��delete���ׂ���

		DWORD dwUser;		//	���[�U���o�^�o����p�����[�^
	} LAYERINFO;

	/*
	//map<string,LAYERINFO> layerInfos;
	//map<int,string> indexs;
	typedef map<string,LAYERINFO> LAYERINFOS_MAP;
	LAYERINFOS_MAP *p_layerInfos;
	INDEXS_MAP *p_indexs;
	*/

	//	���X�g
	//typedef list<LAYERINFO> LAYER_LIST;
	//typedef map<int,LAYERINFO> LAYER_LIST;
	typedef ra_list<LAYERINFO> LAYER_LIST;
	LAYER_LIST m_list;
	//map<layer_t*,int> m_imagePtrMap;	//	layer_t��荂���Ɍ������邽�߂̃}�b�v
	typedef LAYER_LIST::iterator id_t;
public:
	typedef LAYER_LIST::iterator LAYER_ITR;
	typedef LAYER_LIST::iterator LIST_ITR;
	typedef LAYER_LIST::reverse_iterator LIST_RITR;
private:

	/*
	//	�����_�����O�p�T�[�t�F�X
	layer_t m_renderingSurface;

	//	�O��͂ǂ̃T�[�t�F�X�Ƀ����_�����O���悤�Ƃ�����
	layer_t* m_pPrevTargetSurface;

	//	�O��̃����_�����O��K�p����
	void AdaptRenderingSurface();
	*/

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

	LAYERINFO& ExistChk(LIST_ITR it){
		return m_list[it];
	}

	void LayerSingleDraw(LAYERINFO& t);

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMglLayers4();
	virtual ~CMglLayers4();

	//	������
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd ){
		m_myudg = in_myudg;
		m_d3d = m_myudg->GetD3dDevPtr();
		m_pHitTestMap = NULL;
	}
	void Release(){ Clear(); }

	//	�o�^/�폜
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
	LIST_ITR Regist( layer_t *pLayer, LIST_ITR it, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f );

	/*void PushFront( layer_t *pLayer,
		float x, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.begin(), false, x,y, bShow, color, fScaleX, fScaleY, fAngle); }*/
	LIST_ITR PushFront( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
	{
		return Regist( pLayer, m_list.begin(), isShouldDeleteLayer, x,y, bShow, color, fScaleX, fScaleY, fAngle);
		/*LAYERINFO t;
		ZeroMemory(&t,sizeof(t));	//	�܂��Ԃ����Ⴏ����Ȃ����ǂˁB�i�ނ���STL�����o����Ɗ댯���H
		t.pLayer = pLayer;
		t.isShuoldDeleteLayerPtr = isShouldDeleteLayer;
		m_list.push_front(t);
		SetParam(m_list.begin(),x,y,bShow,color,fScaleX,fScaleY,fAngle);*/
	}
	LIST_ITR RegistBegin( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ return Regist( pLayer, m_list.begin(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	LIST_ITR push_front( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ return Regist( pLayer, m_list.begin(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }

	/*void PushBack( layer_t *pLayer,
		float x, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ Regist( pLayer, m_list.tail(), false, x,y, bShow, color, fScaleX, fScaleY, fAngle); }*/
	LIST_ITR PushBack( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
	{
		return Regist( pLayer, m_list.end(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle);
		//Regist( pLayer, m_list.begin(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle);
		//Regist( pLayer, m_list.tail(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle);
		/*LAYERINFO t;
		ZeroMemory(&t,sizeof(t));	//	�܂��Ԃ����Ⴏ����Ȃ����ǂˁB�i�ނ���STL�����o����Ɗ댯���H
		t.pLayer = pLayer;
		t.isShuoldDeleteLayerPtr = isShouldDeleteLayer;
		m_list.push_back(t);
		//SetParam(m_list.rbegin().base(),x,y,bShow,color,fScaleX,fScaleY,fAngle);
		SetParam(m_list.back(),x,y,bShow,color,fScaleX,fScaleY,fAngle);
		if ( m_list.rbegin().base()->pLayer != pLayer )
			MyuThrow(3255, "m_list.rbegin().base()->pLayer != pLayer" );*/
	}
	LIST_ITR RegistTail( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ return Regist( pLayer, m_list.tail(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	LIST_ITR RegistLast( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ return Regist( pLayer, m_list.tail(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
	LIST_ITR push_back( layer_t *pLayer, bool isShouldDeleteLayer,
		float x=0.0f, float y=0.0f, BOOL bShow=TRUE, D3DCOLOR color=D3DCOLOR_WHITE, 
		float fScaleX=1.0f, float fScaleY=1.0f, float fAngle=0.0f )
		{ return Regist( pLayer, m_list.tail(), isShouldDeleteLayer,x,y, bShow, color, fScaleX, fScaleY, fAngle); }
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
	LIST_ITR GetItBegin(){ return m_list.begin(); }
	LIST_ITR GetItEnd(){ return m_list.end(); }
	LIST_ITR GetItTail(){ return m_list.tail(); }
	LIST_ITR begin(){ return m_list.begin(); }
	LIST_ITR end(){ return m_list.end(); }
	LIST_ITR tail(){ return m_list.tail(); }

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
	void SetUserParam( LIST_ITR it, DWORD dwUser );
	DWORD GetUserParam( LIST_ITR it );

	//void MoveDepth( int oldDepth, int newDepth );	//	������

	//	�擾
	layer_t* Get( LIST_ITR it ){
		return m_list[it].pLayer;
	}

	/*
	//	�擾
	int Find( layer_t *pLayer ){
		if ( m_imagePtrMap.find(pLayer) == m_imagePtrMap.end() )
			return NULL;
		return m_imagePtrMap[pLayer];
	}
	*/

	//	�N���A����
	//void Clear(){ ReleaseAll(); m_list.clear(); /*m_imagePtrMap.clear();*/ }
	void Delete(LIST_ITR it);
	void Remove(LIST_ITR it){Delete(it);}
	void DeleteAll(){Clear();}
	void RemoveAll(){Clear();}
	void Clear();

	//	�`��
	void Draw(){ Rendering(); }
	void DrawAll(){ Rendering(); }
	void AllDraw(){ Rendering(); }
	void Rendering();

	//	HitTest
	LIST_ITR HitTest(int x, int y);
	LIST_ITR HitTest2(int x, int y);
	LIST_ITR HitTest3(int x, int y);

	/////////////////////////////////////////////////////////////////////////////////

	//	�v���p�e�B�n���\�b�h
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


////////////////////////////////////////////////////////////////////////////


class DLL_EXP CMglLayers4HitTest
{
private:
	CMglGraphicManager* m_myudg;	//	CMglGraphicManager�ւ̃|�C���^���i�[
	D3DCOLOR* m_pHistTestMap;
public:
	CMglLayers4HitTest(CMglGraphicManager* in_myudg=g_pDefaultGd){Init(in_myudg);}
	virtual ~CMglLayers4HitTest(){Release();}

	void Init(CMglGraphicManager* in_myudg=g_pDefaultGd){
		m_myudg = in_myudg;

		//m_pHistTestMap = NULL;
		m_pHistTestMap = new D3DCOLOR[ m_myudg->GetWidth() * m_myudg->GetHeight() ];
	}
	void Release(){
		SAFE_DELETE_ARY(m_pHistTestMap);
	}
	void Set(int x, int y, D3DCOLOR color){
		m_pHistTestMap[x,y] = color;
	}
	D3DCOLOR Get(int x, int y){
		return m_pHistTestMap[x,y];
	}
};

#endif//__MglLayers4_H__
