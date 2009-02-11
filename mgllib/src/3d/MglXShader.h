//////////////////////////////////////////////////////////
//
//	CMglXShader - メッシュ
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
			MyuThrow(MGLMSGNO_SHADER(1), "CMglXShader  既にシェーダは作成済です。");
	}
	void CreateCheck(){
		if ( m_pBufShader == NULL )
			MyuThrow(MGLMSGNO_SHADER(2), "CMglXShader  シェーダが作成されていません。");
	}

public:
	//	コンストラクタ・デストラクタ
	CMglXShader();
	virtual ~CMglXShader(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	const char* GetCompileErrorMsg();
};
//typedef CMglXShader CMglShaderBase;
typedef CMglXShader CMglShaderLoader;

#endif//__MglXShader_H__
