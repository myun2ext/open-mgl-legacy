#ifndef __MglVertexManager_H__
#define __MglVertexManager_H__

#include "MglGraphicManager.h"

//	クラス宣言
//class CMglVertexManager
template <typename _VERTEX = MYUX_VERTEX>
class CMglVertexManagerT
{
protected:
	std::vector<_VERTEX> m_vertexes;
	DWORD m_dwFVF;
public:
	//	コンストラクタ・デストラクタ
	CMglVertexManagerT(){ m_dwFVF = _VERTEX::GetFVF(); }
	CMglVertexManagerT(DWORD dwFvf){ m_dwFVF = dwFvf; }
	//CMglVertexManager(){}

	void Create(int nVertexCount){
		m_vertexes.clear();
		m_vertexes.resize(nVertexCount);
	}

	void AddVertex(_VERTEX &vertex){ m_vertexes.push_back(vertex); }
	void AddPoint(float x, float y, float z, D3DCOLOR color=0 ){
		_VERTEX v;
		v.x = x;
		v.y = y;
		v.z = z;
		v.color = color;
		AddVertex(v);
	}
	void FillColor(D3DCOLOR color){ FillVertexColor(color); }
	void FillVertexColor(D3DCOLOR color){
		for(int i=0; m_vertexes.size(); i++ )
			m_vertexes[i].color = color;
	}

	_VERTEX& Get(int i){
		if ( i >= m_vertexes.size() )
			MyuThrow( 324432, "CMglVertexManagerT()::Get()  インデックスが範囲外です。" );
		return m_vertexes[i];
	}
	void Set(int i, _VERTEX& vertex){ m_vertexes[i] = vertex; }
};

/////////////////////////////////////////////////////////

template <typename _VERTEX = MYUX_VERTEX>
class DLL_EXP CMglVertexManagerXT : public CMglVertexManagerT<_VERTEX>
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	_MGL_IDirect3DDevice* d3d;		//	D3DDeviceへのポインタ

	void SetD3dTexture(_MGL_IDirect3DTexture *pTexture){ SetD3dStageTexture(pTexture, 0); }
	void SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage);

public:
	//	コンストラクタ・デストラクタ
	CMglVertexManagerXT(){
		m_myudg = NULL;
		d3d = NULL;
	}
	virtual ~CMglVertexManagerXT(){ Release(); }

	//	初期化と開放
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd ){
		m_myudg = in_myudg;
		d3d = m_myudg->GetD3dDevPtr();
	}
	void Release(){
	}

	////////////////////////////////////////////////////////

	void Draw( D3DPRIMITIVETYPE primitiveType );
	void Draw( D3DPRIMITIVETYPE primitiveType, _MGL_IDirect3DTexture *pTexture, DWORD nTextureStage=0){
		SetD3dStageTexture(pTexture, nTextureStage);
		Draw(primitiveType);
	}
};


//typedef CMglVertexManager CMglVertex;
template <typename _VERTEX>class CMglVertexT{ typedef CMglVertexManagerT<_VERTEX> type; };
template <typename _VERTEX>class CMglVertexesT{ typedef CMglVertexManagerT<_VERTEX> type; };
typedef CMglVertexManagerT<> CMglVertex, CMglVertexes, CMglVertexManager;

#endif//__MglVertexManager_H__
