//////////////////////////////////////////////////////////
//
//	CMglHlsl - シェーダー
//
//////////////////////////////////////////////////////////

#ifndef __MglHlsl_H__
#define __MglHlsl_H__

#include "mglafx.h"
#include "MglGraphicManager.h"
#include "D3dx8effect.h "

//typedef ID3DXBuffer _MGL_ID3DXEffect_;
typedef ID3DXEffect _MGL_ID3DXEffect_;

//	クラス宣言
class DLL_EXP CMglHlsl : public CMglDgBase
{
protected:
	_MGL_ID3DXEffect_ *m_pEffect;
	ID3DXBuffer *m_pBufErrorInfo;

	void CreatedCheck(){
		if ( m_pEffect != NULL )
			MyuThrow(MGLMSGNO_SHADER(1), "CMglHlsl  既にバッファは作成済です。");
	}
	void CreateCheck(){
		if ( m_pEffect == NULL )
			MyuThrow(MGLMSGNO_SHADER(2), "CMglHlsl  バッファが作成されていません。");
	}

public:
	//	コンストラクタ・デストラクタ
	CMglHlsl();
	virtual ~CMglHlsl(){ Release(); }
	void Release();

	void Load(const char* szShaderScriptFile);
	void LoadScript(const char* szShaderScriptFile){ Load(szShaderScriptFile); }
	void Create(const char* szShaderScriptFile){ Load(szShaderScriptFile); }

	void LoadFromString( const char* szAssembleString );
	void CreateFromString( const char* szAssembleString ){ LoadFromString(szAssembleString); }

	/*void LoadFromResource( const char* szAssembleString ); <- DirectX8 未サポート・・・
	void CreateFromResource( const char* szAssembleString ){ LoadFromString(szAssembleString); }*/

	const char* GetCompileErrorMsg();

	_MGL_ID3DXEffect_* GetBuffer();
};
//typedef CMglHlsl CMglShaderBase;
typedef CMglHlsl CMglShaderLoader;

#endif//__MglHlsl_H__
