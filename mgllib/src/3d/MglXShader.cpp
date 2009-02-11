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

//	Xファイル読み込み
void CMglXShader::Load(const char* szShaderScriptFile)
{
	InitCheck();
	CreatedCheck();

	//	ファイルが本当にあるかどうか？
	if ( !msl::IsExistFile(szShaderScriptFile) )
		MyuThrow(MGLMSGNO_SHADER(2), "CMglXShader::Load()  ファイル \"%s\" は見つかりません。", szShaderScriptFile);

	//	アセンブラファイル読み込みー
	MyuAssert2( D3DXAssembleShaderFromFile( szShaderScriptFile, 0, NULL, &m_pBufShader, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(12), "CMglXShader::Load()  D3DXAssembleShaderFromFile()に失敗\r\n\r\n%s", GetCompileErrorMsg() );
}

//	Xファイル読み込み
void CMglXShader::LoadFromString(const char* szAssembleString)
{
	InitCheck();
	CreatedCheck();

	//	アセンブラファイル読み込みー
	MyuAssert2( D3DXAssembleShader( szAssembleString, strlen(szAssembleString),
		0, NULL, &m_pBufShader, &m_pBufErrorInfo ), D3D_OK,
		MGLMSGNO_SHADER(13), "CMglXShader::LoadFromString()  D3DXAssembleShader()に失敗\r\n\r\n%s", GetCompileErrorMsg() );
}

//	エラーメッセージ取得
const char* CMglXShader::GetCompileErrorMsg()
{
	if ( m_pBufErrorInfo == NULL )
		return "";

	return (const char*) m_pBufErrorInfo->GetBufferPointer();
}

//	バッファ取得
CONST DWORD* CMglXShader::GetBuffer()
{
	InitCheck();
	CreateCheck();

	return (CONST DWORD*) m_pBufShader->GetBufferPointer();
}

