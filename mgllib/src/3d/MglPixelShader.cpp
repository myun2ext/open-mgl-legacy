#include "stdafx.h"
#include "MglPixelShader.h"

//	コンストラクタ
CMglPixelShader::CMglPixelShader()
{
	m_pShader = NULL;
}

//	開放
void CMglPixelShader::Release()
{
#if _MGL_DXVER == 9	//	DirectXでは”ただのハンドル”ですので・・・
	SAFE_RELEASE(m_pShader);
#endif
}

//	アセンブルファイル読み込み
void CMglPixelShader::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.Load(szShaderScriptFile);

	LoadCommon(loader.GetBuffer());
}

//	文字列から読み込み
void CMglPixelShader::LoadFromString( const char* szAssembleString )
{
	InitCheck();
	CreatedCheck();

	CMglShaderLoader loader;
	loader.Init(m_myudg);
	loader.LoadFromString(szAssembleString);

	LoadCommon(loader.GetBuffer());
}

//	Load共通
void CMglPixelShader::LoadCommon(CONST DWORD* pFunction)
{
	//	作成ー
	MyuAssert2( m_d3d->CreatePixelShader( pFunction, &m_pShader ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglPixelShader::LoadCommon()  m_d3d->CreatePixelShader()に失敗" );
}
