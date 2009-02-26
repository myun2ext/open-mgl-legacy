#include "stdafx.h"
#include "MglHLSL.h"

//	コンストラクタ
CMglHlsl::CMglHlsl()
{
	m_pEffect = NULL;
	m_pBufErrorInfo = NULL;

	m_nPassCount = 0;
}

//	開放
void CMglHlsl::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pBufErrorInfo);
}

//	エフェクトファイル読み込み
void CMglHlsl::Load(const char* szShaderScriptFile)
{
	CreatedCheck();

	//	ファイルが本当にあるかどうか？
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(202), "CMglHlsl::Load()  ファイル \"%s\" は見つかりません。", szShaderScriptFile);

	//	エフェクトファイル読み込みー
	/*MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK, <- なんかGetCompileErrorMsg()が先に実行されてしまうらしい・・・まぁ最適化とかでかね・・・
		MGLMSGNO_SHADER(12), "CMglHlsl::Load()  D3DXAssembleShaderFromFile()に失敗\r\n\r\n%s", GetCompileErrorMsg() );*/
	HRESULT hr = D3DXCreateEffectFromFile( m_d3d, szShaderScriptFile, &m_pEffect, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(213), "CMglHlsl::Load()  次のエラーのため D3DXCreateEffectFromFile() は失敗しました。\r\n\r\n%s", GetCompileErrorMsg() );
}

//	文字列から読み込み
void CMglHlsl::LoadFromString(const char* szAssembleString)
{
	CreatedCheck();

	//	エフェクト読み込みー
	/*MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString), <- なんかGetCompileErrorMsg()が先に実行されてしまうらしい・・・まぁ最適化とかでかね・・・
		0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglHlsl::LoadFromString()  D3DXAssembleShader()に失敗\r\n\r\n%s", GetCompileErrorMsg() );*/
	HRESULT hr = D3DXCreateEffect( m_d3d, szAssembleString, strlen(szAssembleString), &m_pEffect, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(214), "CMglHlsl::LoadFromString()  次のエラーのため D3DXCreateEffect() は失敗しました。\r\n\r\n%s", GetCompileErrorMsg() );
}

//	エラーメッセージ取得
const char* CMglHlsl::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "(No Error Buffer.)";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

//	テクニックを設定
void CMglHlsl::SetTechnique( _MGL_D3DXHANDLE szTechniqueName )
{
	CreateCheck();

	//	アセンブラファイル読み込みー
	MyuAssert2( m_pEffect->SetTechnique( szTechniqueName ), D3D_OK,
		MGLMSGNO_SHADER(240), "CMglHlsl::SetTechnique()  m_pEffect->SetTechnique()に失敗" );
}

////////////////////////////////////////////////////////////////

//	Begin()
UINT CMglHlsl::Begin( bool bRestoreCurrentRenderStates )
{
	CreateCheck();

	DWORD dwFlags = 0;
	if ( !bRestoreCurrentRenderStates )
		dwFlags = /*D3DXFX_DONOTSAVESHADERSTATE |*/ D3DXFX_DONOTSAVESTATE ;

	//	Begin
	MyuAssert2( m_pEffect->Begin( &m_nPassCount, dwFlags ), D3D_OK,
		MGLMSGNO_SHADER(280), "CMglHlsl::Begin()  m_pEffect->Begin()に失敗" );

	return m_nPassCount;
}
UINT CMglHlsl::Begin() {
	return Begin(true);
}

//	End()
void CMglHlsl::End()
{
	CreateCheck();
	MyuAssert2( m_pEffect->End(), D3D_OK,
		MGLMSGNO_SHADER(281), "CMglHlsl::End()  m_pEffect->End()に失敗" );

	m_nPassCount = 0;
}

//	Pass()
void CMglHlsl::Pass(UINT nPassNo)
{
	CreateCheck();
	MyuAssert2( m_pEffect->Pass(nPassNo), D3D_OK,
		MGLMSGNO_SHADER(284), "CMglHlsl::Pass()  m_pEffect->Pass(%s)に失敗", nPassNo );
}

//	バッファ取得
/*_MGL_ID3DXEffect_* CMglHlsl::GetEffectPtr()
{
	InitCheck();
	CreateCheck();

	return m_pEffect;
}
*/
