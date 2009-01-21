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

template <typename _VERTEX = MYUX_VERTEX>
class /*DLL_EXP*/ CMglVertexManagerXT : public CMglVertexManagerT<_VERTEX>
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	_MGL_IDirect3DDevice* d3d;		//	D3DDeviceへのポインタ
	_MGL_IDirect3DVertexBuffer *m_pVB; // 頂点バッファ

	void SetD3dTexture(_MGL_IDirect3DTexture *pTexture){ SetD3dStageTexture(pTexture, 0); }
	void SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage);

public:
	//	コンストラクタ・デストラクタ
	CMglVertexManagerXT(){
		m_myudg = NULL;
		d3d = NULL;
		m_pVB = NULL;
	}
	virtual ~CMglVertexManagerXT(){ Release(); }

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
	void CompileToFastMem(D3DPOOL pool=D3DPOOL_DEFAULT, DWORD dwUsage=0)
	{
		/*
		//	前のが残ってるとアレなのでRelease -> 同じの使うので要らないんだよ!?
		SAFE_RELEASE(m_pVB);
		*/
		UINT nSize = m_vertexes.size()*sizeof(_VERTEX);

		//	2009/01/18 前のが残ってたらそのまま流用するんだわさ。
		if ( m_pVB == NULL ){
			//	頂点バッファの作成
			MyuAssert( d3d->CreateVertexBuffer( nSize, dwUsage, m_dwFVF, pool, &m_pVB), D3D_OK,
				"CMglVertexManagerXT::CompileToFastMem()  d3d->CreateVertexBuffer()に失敗" );
		}

		//	ロック
		BYTE* pLocked;
		MyuAssert( m_pVB->Lock( 0, nSize, (BYTE**)&pLocked, 0), D3D_OK,
			"CMglVertexManagerXT::CompileToFastMem()  m_pVB->Lock()に失敗" );

		//	コピー
		memcpy( pLocked, GetVertexPtr(), nSize );

		//	アンロック
		MyuAssert( m_pVB->Unlock(), D3D_OK,
			"CMglVertexManagerXT::CompileToFastMem()  m_pVB->Unlock()に失敗" );
	}

	//	描画
	void Draw( D3DPRIMITIVETYPE primitiveType )
	{
		if ( m_pVB == NULL )
		{
			//	頂点バッファを使わない方式
			MyuAssert( d3d->DrawPrimitiveUP(
				primitiveType, m_vertexes.size(), GetVertexPtr(), sizeof(_VERTEX) ), D3D_OK,
				"CMglVertexManagerXT::Draw()  d3d->DrawPrimitiveUP()に失敗" );
		}
		else
		{
			//	頂点バッファを使う方式

			//	TODO: CompileToFastMem()しないと駄目な気がする（pool, dwUsage覚えとかないとね・・・）

			//	設定するです
			MyuAssert( d3d->SetStreamSource( 0, m_pVB, sizeof(_VERTEX) ), D3D_OK,
				"CMglVertexManagerXT::Draw()  d3d->SetStreamSource()に失敗" );
			MyuAssert( d3d->SetVertexShader( m_dwFVF ), D3D_OK,
				"CMglVertexManagerXT::Draw()  d3d->SetVertexShader()に失敗" );

			MyuAssert( d3d->DrawPrimitive( primitiveType, 0, m_vertexes.size() ), D3D_OK,
				"CMglVertexManagerXT::Draw()  d3d->DrawPrimitive()に失敗" );
		}
	}
	void Draw( D3DPRIMITIVETYPE primitiveType, _MGL_IDirect3DTexture *pTexture, DWORD nTextureStage=0){
		SetD3dStageTexture(pTexture, nTextureStage);
		Draw(primitiveType);
	}
};


//typedef CMglVertexManager CMglVertex;
template <typename _VERTEX> class CMglVertexT{ typedef CMglVertexManagerT<_VERTEX> type; };
template <typename _VERTEX> class CMglVertexesT{ typedef CMglVertexManagerT<_VERTEX> type; };
typedef CMglVertexManagerT<> CMglVertex, CMglVertexes, CMglVertexManager;

#endif//__MglVertexManager_H__
