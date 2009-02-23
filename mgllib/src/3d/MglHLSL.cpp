#include "stdafx.h"
#include "MglHLSL.h"

//	コンストラクタ
CMglHlsl::CMglHlsl()
{
	m_pEffect = NULL;
	m_pBufErrorInfo = NULL;
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
	InitCheck();
	CreatedCheck();

	//	ファイルが本当にあるかどうか？
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(202), "CMglHlsl::Load()  ファイル \"%s\" は見つかりません。", szShaderScriptFile);

	//	アセンブラファイル読み込みー
	/*MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK, <- なんかGetCompileErrorMsg()が先に実行されてしまうらしい・・・まぁ最適化とかでかね・・・
		MGLMSGNO_SHADER(12), "CMglHlsl::Load()  D3DXAssembleShaderFromFile()に失敗\r\n\r\n%s", GetCompileErrorMsg() );*/
	HRESULT hr = D3DXCreateEffectFromFile( m_d3d, szShaderScriptFile, &m_pEffect, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(213), "CMglHlsl::Load()  次のエラーのため D3DXCreateEffectFromFile() は失敗しました。\r\n\r\n%s", GetCompileErrorMsg() );
}

//	文字列から読み込み
void CMglHlsl::LoadFromString(const char* szAssembleString)
{
	InitCheck();
	CreatedCheck();

	//	アセンブラファイル読み込みー
	/*MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString), <- なんかGetCompileErrorMsg()が先に実行されてしまうらしい・・・まぁ最適化とかでかね・・・
		0, NULL, &m_pEffect, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglHlsl::LoadFromString()  D3DXAssembleShader()に失敗\r\n\r\n%s", GetCompileErrorMsg() );*/
	//	アセンブラファイル読み込みー
	HRESULT hr = D3DXCreateEffect( m_d3d, szAssembleString, strlen(szAssembleString), &m_pEffect, &m_pBufErrorInfo );
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(213), "CMglHlsl::LoadFromString()  次のエラーのため D3DXCreateEffect() は失敗しました。\r\n\r\n%s", GetCompileErrorMsg() );
}

//	エラーメッセージ取得
const char* CMglHlsl::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "(No Error Buffer.)";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

//	バッファ取得
_MGL_ID3DXEffect_* CMglHlsl::GetBuffer()
{
	InitCheck();
	CreateCheck();

	return m_pEffect;
}

