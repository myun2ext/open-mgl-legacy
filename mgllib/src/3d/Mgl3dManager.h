///////////////////////////////////////////////////////////////////////
//
//	Mgl3DManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __Mgl3DManager_H__
#define __Mgl3DManager_H__

#include "MglGraphicManager.h"

class DLL_EXP CMgl3DManager
{
protected:
	CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[
	_MGL_IDirect3DDevice* m_pD3dDev;	//	D3D�f�o�C�X

public:

	//////////////////////////
	//
	//		���J���\�b�h
	//

	//	�R���X�g���N�^/�f�X�g���N�^
	CMgl3DManager();
	virtual ~CMgl3DManager();

	//	������/�J��
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd );
	void Release();

	void SetupProjection( float fAspectRatio, float fViewingAngle=45.0f, float fClipNear=0.01f, float fClipFar=100.0f );

	void SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ);
	/*void SetCameraPos(float x, float y, float z);
	void SetCameraViewTarget(float x, float y, float z);*/
};

#endif//__Mgl3DManager_H__
