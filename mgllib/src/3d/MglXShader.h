//////////////////////////////////////////////////////////
//
//	CMglXShader - シェーダー
//
//////////////////////////////////////////////////////////

#ifndef __MglXShader_H__
#define __MglXShader_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//	クラス宣言
class DLL_EXP CMglXShader : public CMglDgBase
{
protected:
	ID3DXBuffer *m_pBufShader;
	ID3DXBuffer *m_pBufErrorInfo;

	void CreatedCheck(){
		if ( m_pBufShader != NULL )
			MyuThrow(MGLMSGNO_SHADER(1), "CMglXShader  既にバッファは作成済です。");
	}
	void CreateCheck(){
		if ( m_pBufShader == NULL )
			MyuThrow(MGLMSGNO_SHADER(2), "CMglXShader  バッファが作成されていません。");
	}

public:
	//	コンストラクタ・デストラクタ
	CMglXShader();
	virtual ~CMglXShader(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	void LoadFromString( const char* szAssembleString );
	void CreateFromString( const char* szAssembleString ){ LoadFromString(szAssembleString); }

	/*void LoadFromResource( const char* szAssembleString ); <- DirectX8 未サポート・・・
	void CreateFromResource( const char* szAssembleString ){ LoadFromString(szAssembleString); }*/

	const char* GetCompileErrorMsg();

	CONST DWORD* GetBuffer();
};
//typedef CMglXShader CMglShaderBase;
typedef CMglXShader CMglShaderLoader;

#endif//__MglXShader_H__
