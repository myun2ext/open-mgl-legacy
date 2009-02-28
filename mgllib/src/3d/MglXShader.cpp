#include "stdafx.h"
#include "MglXShader.h"

//	コンストラクタ
CMglXShader::CMglXShader()
{
	m_pBufShader = NULL;
	m_pBufErrorInfo = NULL;
}

//	開放
void CMglXShader::Release()
{
	SAFE_RELEASE(m_pBufShader);
	SAFE_RELEASE(m_pBufErrorInfo);
}

//	シェーダーファイル読み込み
void CMglXShader::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	//	ファイルが本当にあるかどうか？
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(2), "CMglXShader::Load()  ファイル \"%s\" は見つかりません。", szShaderScriptFile);

	//	アセンブラファイル読み込みー
	/*MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pBufShader, &m_pBufErrorInfo ), D3D_OK, <- なんかGetCompileErrorMsg()が先に実行されてしまうらしい・・・まぁ最適化とかでかね・・・
		MGLMSGNO_SHADER(12), "CMglXShader::Load()  D3DXAssembleShaderFromFile()に失敗\r\n\r\n%s", GetCompileErrorMsg() );*/
#if _MGL_DXVER == 8
	HRESULT hr = D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pBufShader, &m_pBufErrorInfo );
#else
	HRESULT hr = D3DXAssembleShaderFromFile( szShaderScriptFile, NULL, NULL, 0, &m_pBufShader, &m_pBufErrorInfo );
#endif
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(13), "CMglXShader::Load()  次のエラーのため D3DXAssembleShaderFromFile() は失敗しました。\r\n\r\n%s", GetCompileErrorMsg() );
}

//	文字列から読み込み
void CMglXShader::LoadFromString(const char* szAssembleString)
{
	InitCheck();
	CreatedCheck();

	//	アセンブラファイル読み込みー
	/*MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString), <- なんかGetCompileErrorMsg()が先に実行されてしまうらしい・・・まぁ最適化とかでかね・・・
		0, NULL, &m_pBufShader, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglXShader::LoadFromString()  D3DXAssembleShader()に失敗\r\n\r\n%s", GetCompileErrorMsg() );*/
	//	アセンブラファイル読み込みー
#if _MGL_DXVER == 8
	HRESULT hr = D3DXAssembleShader( szAssembleString, strlen(szAssembleString),
		0, NULL, &m_pBufShader, &m_pBufErrorInfo );
#else
	HRESULT hr = D3DXAssembleShader( szAssembleString, strlen(szAssembleString),
		NULL, NULL, 0, &m_pBufShader, &m_pBufErrorInfo );
#endif
	if ( hr != D3D_OK )
		MyuThrow2( hr, MGLMSGNO_SHADER(13), "CMglXShader::LoadFromString()  次のエラーのため D3DXAssembleShader() は失敗しました。\r\n\r\n%s", GetCompileErrorMsg() );
}

//	エラーメッセージ取得
const char* CMglXShader::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "(No Error Buffer.)";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

//	バッファ取得
CONST DWORD* CMglXShader::GetBuffer()
{
	InitCheck();
	CreateCheck();

	return (CONST DWORD*) m_pBufShader->GetBufferPointer();
}

