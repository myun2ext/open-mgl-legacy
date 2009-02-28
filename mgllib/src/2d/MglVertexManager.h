#ifndef __MglVertexManager_H__
#define __MglVertexManager_H__

#include "MglGraphicManager.h"

#if _MGL_DXVER == 8
	typedef BYTE MGL_LOCKED_VERTEX_BUFFER_t;
#else //_MGL_DXVER == 9
	typedef void MGL_LOCKED_VERTEX_BUFFER_t;
#endif

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
		Clear();
		m_vertexes.resize(nVertexCount);
	}

	void Clear(){ m_vertexes.clear(); }
	void Release(){ m_vertexes.clear(); }
	void AddVertex(_VERTEX &vertex){ m_vertexes.push_back(vertex); }
	void AddPoint(float x, float y, float z, D3DCOLOR color=0 ){
		_VERTEX v;
#ifdef _MGLVERTEX_USE_VECTOR3
		v.pos.x = x;
		v.pos.y = y;
		v.pos.z = z;
#else
		v.x = x;
		v.y = y;
		v.z = z;
#endif
		v.color = color;
		AddVertex(v);
	}
	void FillColor(D3DCOLOR color){ FillVertexColor(color); }
	void FillVertexColor(D3DCOLOR color){
		for(int i=0; m_vertexes.size(); i++ )
			m_vertexes[i].color = color;
	}
	void Resize(int nSize){ m_vertexes.resize(nSize); }
	void Alloc(int nSize){ m_vertexes.resize(nSize); }

	_VERTEX& Get(int i){
		if ( i >= m_vertexes.size() )
			MyuThrow( 324432, "CMglVertexManagerT()::Get()  インデックスが範囲外です。" );
		return m_vertexes[i];
	}
	_VERTEX* GetPtr(int i){
		if ( i >= m_vertexes.size() )
			MyuThrow( 324432, "CMglVertexManagerT()::Get()  インデックスが範囲外です。" );
		return &m_vertexes[i];
	}
	_VERTEX& operator [](int i){ return Get(i); }
	void Set(int i, _VERTEX& vertex){ m_vertexes[i] = vertex; }

	_VERTEX* GetVertexPtr(){ return &m_vertexes[0]; }
	int GetVertexCount(){ return m_vertexes.size(); }
	int GetCount(){ return m_vertexes.size(); }
	int GetSize(){ return m_vertexes.size(); }
};

/////////////////////////////////////////////////////////

//#define MGL_VERTEX_DEFAULT_POOL	D3DPOOL_MANAGED
#define MGL_VERTEX_DEFAULT_POOL		D3DPOOL_DEFAULT		//	大したサイズじゃないからVRAM上に、って事にしたんだったな！そういえば！

//	クラス宣言
class DLL_EXP _CMglVertexManagerXT_Realize : public virtual CMglDgBase
{
private:
	UINT m_nVertexSizeof;
	DWORD m_dwFVF;

	//	内部メソッド（チェック用）
	/*void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}*/
protected:
	//CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	//_MGL_IDirect3DDevice* d3d;		//	D3DDeviceへのポインタ
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
	/*void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){
		m_myudg = in_myudg;
		d3d = m_myudg->GetD3dDevPtr();
		if ( m_myudg == NULL )
			MyuThrow(49815, "CMglVertexManagerX::Init()  in_myudg はNULLです。");
		if ( d3d == NULL )
			MyuThrow(49816, "CMglVertexManagerX::Init()  m_myudg->GetD3dDevPtr() はNULLです。");
	}*/
	void Release(){
		SAFE_RELEASE(m_pVB);
	}

	////////////////////////////////////////////////////////

	void CompileToFastMem(D3DPOOL pool=MGL_VERTEX_DEFAULT_POOL, DWORD dwUsage=0);
	//void CopyToFastMem(D3DPOOL pool=D3DPOOL_DEFAULT, DWORD dwUsage=0){ CompileToFastMem(pool,dwUsage); }
	void Compile(D3DPOOL pool=MGL_VERTEX_DEFAULT_POOL, DWORD dwUsage=0){ CompileToFastMem(pool,dwUsage); };
	void ReCompile(D3DPOOL pool=MGL_VERTEX_DEFAULT_POOL, DWORD dwUsage=0){ CompileToFastMem(pool,dwUsage); };

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
class CMglVertexManagerXT : public CMglVertexManagerT<_VERTEX>, public _CMglVertexManagerXT_Realize
{
private:
	const void* _GetVertexPtr(){ return GetVertexPtr(); }
	int _GetVertexCount(){ return m_vertexes.size(); }

public:
	//	コンストラクタ
	CMglVertexManagerXT() : _CMglVertexManagerXT_Realize(
		CMglVertexManagerT<_VERTEX>::m_dwFVF, sizeof(_VERTEX)){}

	//	両方呼ぶようにせねば・・・
	void Release(){
		CMglVertexManagerT<_VERTEX>::Release();
		_CMglVertexManagerXT_Realize::Release();
	}
};


//typedef CMglVertexManager CMglVertex;
template <typename _VERTEX> class CMglVertexT{ typedef CMglVertexManagerT<_VERTEX> type; };
template <typename _VERTEX> class CMglVertexesT{ typedef CMglVertexManagerT<_VERTEX> type; };
typedef CMglVertexManagerT<> CMglVertex, CMglVertexes, CMglVertexManager;
typedef CMglVertexManagerXT<> CMglVertexX, CMglVertexesX, CMglVertexManagerX;
//typedef class DLL_EXP CMglVertexX : public CMglVertexManagerXT<> {} CMglVertexesX, CMglVertexManagerX;

//DLL_TMPL_EXTERN template class DLL_EXP CMglVertexManagerT<>;
//DLL_TMPL_EXTERN template class DLL_EXP CMglVertexManagerXT<>;
//DLL_TMPL_EXTERN class DLL_EXP CMglVertexManagerT<>;
//DLL_TMPL_EXTERN class DLL_EXP CMglVertexManagerXT<>;
DLL_TMPL_EXP CMglVertexManagerT<>;
DLL_TMPL_EXP CMglVertexManagerXT<>;

#endif//__MglVertexManager_H__
