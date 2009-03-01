#include "stdafx.h"
#include "MglHLSL.h"

//	コンストラクタ
CMglEffectCore::CMglEffectCore()
{
	m_pEffect = NULL;
	m_pBufErrorInfo = NULL;

	m_nPassCount = 0;
	m_bBegun = false;
	m_bPassBegun = false;
}

//	開放
void CMglEffectCore::Release()
{
	SAFE_RELEASE(m_pEffect);
	SAFE_RELEASE(m_pBufErrorInfo);
}

//	エフェクトファイル読み込み
void CMglEffectCore::Load(const char* szShaderScriptFile)
{
	CreatedCheck();

	//	ファイルが本当にあるかどうか？
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(202), "CMglEffectCore::Load()  ファイル \"%s\" は見つかりません。", szShaderScriptFile);

	//	エフェクトファイル読み込みー
	/*MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK, <- なんかGetCompileErrorMsg()が先に実行されてしまうらしい・・・まぁ最適化とかでかね・・・
		MGLMSGNO_SHADER(12), "CMglEffectCore::Load()  D3DXAssembleShaderFromFile()に失敗\r\n\r\n%s", GetCompileErrorMsg() );*/
#if _MGL_DXVER == 8
	HRESULT hr = D3DXCreateEffectFromFile( m_d3d, szShaderScriptFile, &m_pEffect, &m_pBufErrorInfo );
#else
	HRESULT hr = D3DXCreateEffectFromFile( m_d3d, szShaderScriptFile, NULL, NULL, 0, NULL, &m_pEffect, &m_pBufErrorInfo );
#endif
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(213), "CMglEffectCore::Load()  次のエラーのため D3DXCreateEffectFromFile() は失敗しました。\r\n\r\n%s", GetCompileErrorMsg() );
}

//	文字列から読み込み
void CMglEffectCore::LoadFromString(const char* szAssembleString)
{
	CreatedCheck();

	//	エフェクト読み込みー
	/*MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString), <- なんかGetCompileErrorMsg()が先に実行されてしまうらしい・・・まぁ最適化とかでかね・・・
		0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglEffectCore::LoadFromString()  D3DXAssembleShader()に失敗\r\n\r\n%s", GetCompileErrorMsg() );*/
#if _MGL_DXVER == 8
	HRESULT hr = D3DXCreateEffect( m_d3d, szAssembleString, strlen(szAssembleString), &m_pEffect, &m_pBufErrorInfo );
#else
	HRESULT hr = D3DXCreateEffect( m_d3d, szAssembleString, strlen(szAssembleString),
		NULL, NULL, 0, NULL, &m_pEffect, &m_pBufErrorInfo );
#endif
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(214), "CMglEffectCore::LoadFromString()  次のエラーのため D3DXCreateEffect() は失敗しました。\r\n\r\n%s", GetCompileErrorMsg() );
}

//	エラーメッセージ取得
const char* CMglEffectCore::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "(No Error Buffer.)";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

////////////////////////////////////////////////////////////////

//	テクニックを設定
void CMglEffectCore::SetTechnique( _MGL_D3DXHANDLE szTechniqueName )
{
	CreateCheck();
	MyuAssert2( m_pEffect->SetTechnique( szTechniqueName ), D3D_OK,
		MGLMSGNO_SHADER(240), "CMglEffectCore::SetTechnique()  m_pEffect->SetTechnique()に失敗" );
}

//	次のテクニックに（NULL指定で最初のテクニック）
void CMglEffectCore::NextTechnique( D3DXHANDLE hPrevTechnique )
{
	SetTechnique( FindNextValidTechnique(hPrevTechnique) );
}

//	FindNextValidTechnique
_MGL_D3DXHANDLE CMglEffectCore::FindNextValidTechnique( _MGL_D3DXHANDLE hPrevTechnique )
{
	CreateCheck();

	//	FindNextValidTechnique
	_MGL_D3DXHANDLE h=NULL;
	MyuAssert2( m_pEffect->FindNextValidTechnique( hPrevTechnique, &h ), D3D_OK,
		MGLMSGNO_SHADER(241), "CMglEffectCore::FindNextValidTechnique()  m_pEffect->FindNextValidTechnique()に失敗" );

	return h;
}

////////////////////////////////////////////////////////////////

//	Begin()
UINT CMglEffectCore::Begin( bool bRestoreCurrentRenderStates )
{
	CreateCheck();

	if ( m_bBegun )
		End();	//	パス数返さないといけないしなぁ・・・

	DWORD dwFlags = 0;
	if ( !bRestoreCurrentRenderStates )
		dwFlags = /*D3DXFX_DONOTSAVESHADERSTATE |*/ D3DXFX_DONOTSAVESTATE ;

	//	Begin
	MyuAssert2( m_pEffect->Begin( &m_nPassCount, dwFlags ), D3D_OK,
		MGLMSGNO_SHADER(280), "CMglEffectCore::Begin()  m_pEffect->Begin()に失敗" );

	m_bBegun = true;

	return m_nPassCount;
}
UINT CMglEffectCore::Begin() {
	return Begin(true);
}

//	End()
void CMglEffectCore::End()
{
	CreateCheck();

	//	2009/22/28 - DirectX9対応
	EndPass();

	MyuAssert2( m_pEffect->End(), D3D_OK,
		MGLMSGNO_SHADER(281), "CMglEffectCore::End()  m_pEffect->End()に失敗" );

	m_bBegun = false;
	m_nPassCount = 0;
}

//	Pass() -> BeginPass()
void CMglEffectCore::BeginPass(UINT nPassNo)
{
	CreateCheck();

	if ( !m_bBegun )
		Begin();

	if ( m_nPassCount < nPassNo )
		MyuThrow(MGLMSGNO_SHADER(289),
			"CMglHlsl  このテクニックでの範囲外のパス番号を指定しました。%d <--> %d", m_nPassCount, nPassNo );

#if _MGL_DXVER == 8
	MyuAssert2( m_pEffect->Pass(nPassNo), D3D_OK,
		MGLMSGNO_SHADER(284), "CMglEffectCore::BeginPass()  m_pEffect->Pass(%s)に失敗", nPassNo );
#else
	EndPass();
	MyuAssert2( m_pEffect->BeginPass(nPassNo), D3D_OK,
		MGLMSGNO_SHADER(284), "CMglEffectCore::BeginPass()  m_pEffect->BeginPass(%s)に失敗", nPassNo );

	m_bPassBegun = true;
#endif
}

//	EndPass()
void CMglEffectCore::EndPass()
{
#if _MGL_DXVER != 8
	CreateCheck();

	if ( m_bPassBegun )
		MyuAssert2( m_pEffect->EndPass(), D3D_OK,
			MGLMSGNO_SHADER(285), "CMglEffectCore::EndPass()  m_pEffect->EndPass()に失敗" );
	m_bPassBegun = false;
#endif
}

//	バッファ取得
/*_MGL_ID3DXEffect_* CMglEffectCore::GetEffectPtr()
{
	InitCheck();
	CreateCheck();

	return m_pEffect;
}
*/
