#ifndef __MglLight_H__
#define __MglLight_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//	クラス宣言
class DLL_EXP CMglLight : public CMglDgBase
{
private:
	void _CMglLight(); // 内部コンストラクタ

protected:
	_D3DLIGHTx m_light;
	DWORD m_dwLightIndex;

public:
	//	コンストラクタ・デストラクタ
	CMglLight(){ _CMglLight(); }
	CMglLight(DWORD dwLightIndex){
		_CMglLight();
		m_dwLightIndex = dwLightIndex;
	}
	virtual ~CMglLight(){ Release(); }
	virtual void Release();

	//	初期化/開放
	//void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){ CMglDgBase::Init(in_myudg); }
	/*void Init( D3DLIGHTTYPE lightType,
		CMglGraphicManager* in_myudg=GetDefaultGd() );*/

	void Setup( _D3DLIGHTx &lightSetting );
	void Setup( D3DLIGHTTYPE lightType,
		float fPosX, float fPosY, float fPosZ, float fDirectionX, float fDirectionY, float fDirectionZ,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK, D3DXCOLOR specular=D3DCOLOR_WHITE, float fRange=1000.0f );

	void SetupDirectionalLight( float fDirectionX, float fDirectionY, float fDirectionZ,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK, D3DXCOLOR specular=D3DCOLOR_WHITE, float fRange=1000.0f )
	{
		Setup(D3DLIGHT_DIRECTIONAL, 0,0,0, fDirectionX, fDirectionY, fDirectionZ, color, ambient, specular, fRange);
	}

	void SetupPointLight( float fPosX, float fPosY, float fPosZ,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK, D3DXCOLOR specular=D3DCOLOR_WHITE, float fRange=1000.0f )
	{
		Setup(D3DLIGHT_POINT, fPosX, fPosY, fPosZ, 0,0,0, color, ambient, specular, fRange);
	}
	void SetupPointingLight( float fPosX, float fPosY, float fPosZ,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DXCOLOR ambient=D3DCOLOR_BLACK, D3DXCOLOR specular=D3DCOLOR_WHITE, float fRange=1000.0f )
	{
		SetupPointLight(fPosX, fPosY, fPosZ, color, ambient, specular, fRange);
	}

	void SetLightIndex(DWORD dwLightIndex){ m_dwLightIndex = dwLightIndex; }
	void Enable();
	void Disable();
	void AllLightDisable();
	void DisableAllLight(){ AllLightDisable(); }
	void DisableLighting(){ AllLightDisable(); }
	//--------------------------------------------------------

	_D3DLIGHTx* GetD3dLightPtr(){ return &m_light; }
	void CommitD3dLight();
	void Commit(){ CommitD3dLight(); }
	void CommitLight(){ CommitD3dLight(); }
};

#endif//__MglLight_H__
