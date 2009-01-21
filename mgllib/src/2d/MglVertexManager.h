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

	_VERTEX* GetVertexPtr(){ return &m_vertexes[0]; }
};

/////////////////////////////////////////////////////////

class DLL_EXP _CMglVertexManagerXT_Realize
{
private:
	UINT m_nVertexSizeof;
	DWORD m_dwFVF;
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	_MGL_IDirect3DDevice* d3d;		//	D3DDeviceへのポインタ
	_MGL_IDirect3DVertexBuffer *m_pVB; // 頂点バッファ

	void SetD3dTexture(_MGL_IDirect3DTexture *pTexture){ SetD3dStageTexture(pTexture, 0); }
	void SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage);

public:
	//	コンストラクタ・デストラクタ
	_CMglVertexManagerXT_Realize(DWORD dwFvf, UINT nVertexSizeof){
		m_myudg = NULL;
		d3d = NULL;
		m_pVB = NULL;
		m_dwFVF = dwFvf;
		m_nVertexSizeof = nVertexSizeof;
	}
	virtual ~_CMglVertexManagerXT_Realize(){ Release(); }

	//	初期化と開放
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){
		m_myudg = in_myudg;
		d3d = m_myudg->GetD3dDevPtr();
	}
	void Release(){
		SAFE_RELEASE(m_pVB);
	}

	////////////////////////////////////////////////////////

	void CopyToFastMem(D3DPOOL pool=D3DPOOL_DEFAULT, DWORD dwUsage=0){ CompileToFastMem(pool,dwUsage); }
	void CompileToFastMem(D3DPOOL pool=D3DPOOL_DEFAULT, DWORD dwUsage=0);

	//	描画
	void Draw( D3DPRIMITIVETYPE primitiveType );
	void Draw( D3DPRIMITIVETYPE primitiveType, _MGL_IDirect3DTexture *pTexture, DWORD nTextureStage=0){
		SetD3dStageTexture(pTexture, nTextureStage);
		Draw(primitiveType);
	}

private:
	virtual const void* _GetVertexPtr()=0;
	virtual int _GetVertexCount()=0;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
template <typename _VERTEX = MYUX_VERTEX>
class /*DLL_EXP*/ CMglVertexManagerXT : public CMglVertexManagerT<_VERTEX>, public _CMglVertexManagerXT_Realize
{
private:
	const void* _GetVertexPtr(){ return GetVertexPtr(); }
	int _GetVertexCount(){ return m_vertexes.size(); }

public:
	//	コンストラクタ
	CMglVertexManagerXT() : _CMglVertexManagerXT_Realize(
		CMglVertexManagerT<_VERTEX>::m_dwFVF, sizeof(_VERTEX)){}
};


//typedef CMglVertexManager CMglVertex;
template <typename _VERTEX> class CMglVertexT{ typedef CMglVertexManagerT<_VERTEX> type; };
template <typename _VERTEX> class CMglVertexesT{ typedef CMglVertexManagerT<_VERTEX> type; };
typedef CMglVertexManagerT<> CMglVertex, CMglVertexes, CMglVertexManager;

#endif//__MglVertexManager_H__
