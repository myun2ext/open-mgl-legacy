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
			MyuThrow(MGLMSGNO_SHADER(201), "CMglHlsl  既に読み込み済です。");
	}
	void CreateCheck(){
		if ( m_pEffect == NULL )
			MyuThrow(MGLMSGNO_SHADER(202), "CMglHlsl  Load()されていません。");
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

	///////////////////////////////////////////////////////////

	void SetTechnique( const char* szTechniqueName );

	///////////////////////////////////////////////////////////

	const char* GetCompileErrorMsg();

	//	エフェクトのポインタ取得
	_MGL_ID3DXEffect_* GetEffectPtr(){
		InitCheck();
		CreateCheck();
		return m_pEffect;
	}
};

typedef CMglHlsl CMglHLSL, CMglEffect;

#endif//__MglHlsl_H__
