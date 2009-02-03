#ifndef __MglLight_H__
#define __MglLight_H__

#include "mglafx.h"
#include "MglGraphicManager.h"

//	ÉNÉâÉXêÈåæ
class DLL_EXP CMglLight : public CMglDgBase
{
private:
	void _CMglLight();

protected:
	_D3DLIGHTx m_light;
	DWORD m_dwLightIndex;

public:
	CMglLight(){ _CMglLight(); }
	CMglLight(int nLightIndex){
		_CMglLight();
		m_dwLightIndex = nLightIndex;
	}
	virtual ~CMglLight(){ Release(); }
	virtual void Release();

	//	èâä˙âª/äJï˙
	//void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){ CMglDgBase::Init(in_myudg); }
	/*void Init( D3DLIGHTTYPE lightType,
		CMglGraphicManager* in_myudg=GetDefaultGd() );*/

	void Setup( _D3DLIGHTx &lightSetting );
	void Setup( D3DLIGHTTYPE lightType,
		float fPosX, float fPosY, float fPosZ, float fDirectionX, float fDirectionY, float fDirectionZ,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DCOLOR ambient=D3DCOLOR_WHITE, float fRange=1000.0f );

	void SetupDirectionalLight( float fDirectionX, float fDirectionY, float fDirectionZ,
		D3DXCOLOR color=D3DCOLOR_WHITE, D3DCOLOR ambient=D3DCOLOR_WHITE, float fRange=1000.0f )
	{
		Setup(D3DLIGHT_DIRECTIONAL, 0,0,0, fDirectionX, fDirectionY, fDirectionZ, color, ambient, fRange);
	}

	void SetLightIndex(DWORD dwLightIndex){ m_dwLightIndex = dwLightIndex; }
	void Enable();
	void Disable();
	//--------------------------------------------------------

	_D3DLIGHTx* GetD3dLightPtr(){ return &m_light; }
	void CommitD3dLight();
};

#endif//__MglLight_H__
