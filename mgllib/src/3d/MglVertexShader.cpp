#include "stdafx.h"
#include "MglVertexShader.h"

//	コンストラクタ
CMglVertexShader::CMglVertexShader()
{
	m_pShader = NULL;
}

//	開放
void CMglVertexShader::Release()
{
#if _MGL_DXVER == 9	//	DirectXでは”ただのハンドル”ですので・・・
	SAFE_RELEASE(m_pShader);
#endif
}

//	アセンブルファイル読み込み
void CMglVertexShader::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.Load(szShaderScriptFile);

	LoadCommon(loader.GetBuffer());
}

//	文字列から読み込み
void CMglVertexShader::LoadFromString( const char* szAssembleString )
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.LoadFromString(szAssembleString);

	LoadCommon(loader.GetBuffer());
}

//	Load共通
void CMglVertexShader::LoadCommon(CONST DWORD* pFunction)
{
#if _MGL_DXVER == 9	//	DirectXでは”ただのハンドル”ですので・・・
	MyuAssert2( m_d3d->CreateVertexShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglVertexShader::LoadCommon()  m_d3d->CreateVertexShader()に失敗" );
#else
	MyuAssert2( m_d3d->CreateVertexShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(96), "CMglVertexShader::LoadCommon()  m_d3d->CreateVertexShader()に失敗" );
#endif
}

//	シェーダを設定
void CMglVertexShader::SetShader()
{
	MyuAssert2( m_d3d->SetVertexShader(m_pShader), D3D_OK, 
		MGLMSGNO_SHADER(97), "CMglVertexShader::SetShader()  m_d3d->SetVertexShader()に失敗" );
}

//	パラメータ設定
void CMglVertexShader::SetShaderParam(DWORD dwStartRegisterNo, const void* lpData, DWORD dwDataBlockCount)
{
	MyuAssert2( m_d3d->SetVertexShaderConstant( dwStartRegisterNo, (VOID*)lpData, dwDataBlockCount), D3D_OK,
		MGLMSGNO_SHADER(98), "CMglVertexShader::SetShaderParam()  m_d3d->SetVertexShaderConstant()に失敗" );
}

//	パラメータ設定
void CMglVertexShader::SetShaderParam(DWORD dwStartRegisterNo, CMglShaderParam &param)
{
	SetShaderParam( dwStartRegisterNo, param.GetHeadPtr(), param.GetCount() );
}
