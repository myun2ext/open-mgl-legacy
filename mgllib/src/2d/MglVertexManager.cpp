#include "stdafx.h"
#include "MglVertexManager.h"

//	マクロ化
//#define CMglVertexManagerXT_CPP(_RETTYPE)	template <typename _VERTEX> _RETTYPE CMglVertexManagerXT<_VERTEX>

//template class DLL_EXP CMglVertexManagerXT<_VERTEX>;

/*template class DLL_EXP CMglVertexManagerT<>;
template class DLL_EXP CMglVertexManagerXT<>;*/

//	テクスチャの設定
void _CMglVertexManagerXT_Realize::SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage)
{
	InitCheck();
	//	テクスチャの設定
	MyuAssert( d3d->SetTexture(nStage, pTexture), D3D_OK,
		"CMglVertexManagerXT::SetD3dStageTexture()  d3d->SetTexture()に失敗" );
}

//	頂点バッファ方式に変換する
void _CMglVertexManagerXT_Realize::CompileToFastMem(D3DPOOL pool, DWORD dwUsage)
{
	InitCheck();
	/*
	//	前のが残ってるとアレなのでRelease -> 同じの使うので要らないんだよ!?
	SAFE_RELEASE(m_pVB);
	*/
	UINT nSize = _GetVertexCount()*m_nVertexSizeof;

	//	2009/01/18 前のが残ってたらそのまま流用するんだわさ。
	if ( m_pVB == NULL ){
		//	頂点バッファの作成
#if _MGL_DXVER == 8
		MyuAssert( d3d->CreateVertexBuffer( nSize, dwUsage, m_dwFVF, pool, &m_pVB), D3D_OK,
#else
		MyuAssert( d3d->CreateVertexBuffer( nSize, dwUsage, m_dwFVF, pool, &m_pVB, NULL/* Reserved in DX9 */), D3D_OK,
#endif
			"CMglVertexManagerXT::CompileToFastMem()  d3d->CreateVertexBuffer()に失敗" );
	}

	//	ロック
	/*
#if _MGL_DXVER == 8
	BYTE* pLocked;
#elif _MGL_DXVER == 9
	void* pLocked;
#endif*/
	MGL_LOCKED_VERTEX_BUFFER_t* pLocked;

	MyuAssert( m_pVB->Lock( 0, nSize, &pLocked, 0), D3D_OK,
		"CMglVertexManagerXT::CompileToFastMem()  m_pVB->Lock()に失敗" );

	//	コピー
    memcpy( pLocked, _GetVertexPtr(), nSize );

	//	アンロック
    MyuAssert( m_pVB->Unlock(), D3D_OK,
		"CMglVertexManagerXT::CompileToFastMem()  m_pVB->Unlock()に失敗" );
}

//	描画
void _CMglVertexManagerXT_Realize::Draw( D3DPRIMITIVETYPE primitiveType )
{
	InitCheck();
	if ( m_pVB == NULL )
	{
		//MyuThrow(456198, "CMglVertexManagerXT::Draw()  このメソッドを実行する前にCompile()メソッドを呼び出してください。");
		/*
		//	頂点バッファを使わない方式
		MyuAssert( d3d->DrawPrimitiveUP(
			primitiveType, _GetVertexCount(), _GetVertexPtr(), m_nVertexSizeof ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->DrawPrimitiveUP()に失敗" );
		*/

		CompileToFastMem();
	}
	else
	{
		//	頂点バッファを使う方式

		//	TODO: CompileToFastMem()しないと駄目な気がする（pool, dwUsage覚えとかないとね・・・）

		//	設定するです
#if _MGL_DXVER == 8
		MyuAssert( d3d->SetStreamSource( 0, m_pVB, m_nVertexSizeof ), D3D_OK,
#else
		MyuAssert( d3d->SetStreamSource( 0, m_pVB, 0/* offset support in D3DDEVCAPS2 only*/, m_nVertexSizeof ), D3D_OK,
#endif
			"CMglVertexManagerXT::Draw()  d3d->SetStreamSource()に失敗" );
		/*MyuAssert( d3d->SetVertexShader( m_dwFVF ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->SetVertexShader()に失敗" );*/
		m_myudg->SetFVF( m_dwFVF );

		//	プリミティブ数はプリミティブ種別により異なる・・・
		int nPrimitiveCount = -1;
		switch(primitiveType)
		{
		case D3DPT_POINTLIST:
			nPrimitiveCount = _GetVertexCount();
			break;
		case D3DPT_LINELIST:
			nPrimitiveCount = _GetVertexCount()/2;
			break;
		case D3DPT_LINESTRIP:
			nPrimitiveCount = _GetVertexCount()-1;
			break;
		case D3DPT_TRIANGLELIST:
			nPrimitiveCount = _GetVertexCount()/3;
			break;
		case D3DPT_TRIANGLESTRIP:
		case D3DPT_TRIANGLEFAN:
			nPrimitiveCount = _GetVertexCount()/2;
			break;
		}

		//MyuAssert( d3d->DrawPrimitive( primitiveType, 0, _GetVertexCount()-2 ), D3D_OK,
		MyuAssert( d3d->DrawPrimitive( primitiveType, 0, nPrimitiveCount ), D3D_OK,
			"CMglVertexManagerXT::Draw()  d3d->DrawPrimitive()に失敗" );
	}
}

/*
//	テクスチャの設定
CMglVertexManagerXT_CPP(void)::SetD3dStageTexture(_MGL_IDirect3DTexture *pTexture, DWORD nStage)
{
	//	テクスチャの設定
	MyuAssert( d3d->SetTexture(nStage, pTexture), D3D_OK,
		"CMglVertexManagerXT::SetD3dStageTexture()  d3d->SetTexture()に失敗" );
}

//	頂点バッファ方式に変換する
CMglVertexManagerXT_CPP(void)::CompileToFastMem(D3DPOOL pool, DWORD dwUsage)
{
	/*
	//	前のが残ってるとアレなのでRelease -> 同じの使うので要らないんだよ!?
	SAFE_RELEASE(m_pVB);
	*//*
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
CMglVertexManagerXT_CPP(void)::Draw( D3DPRIMITIVETYPE primitiveType )
{
	if ( m_pVP == NULL )
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
*/

////////////////////////////////////////////////
//
//	コンパイルテスト

CMglVertexManager g__CMglVertexManager_test;
CMglVertexManagerXT<> g__CMglVertexManagerX_test;
