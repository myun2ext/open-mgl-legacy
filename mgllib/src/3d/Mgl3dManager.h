///////////////////////////////////////////////////////////////////////
//
//	Mgl3DManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __Mgl3DManager_H__
#define __Mgl3DManager_H__

#include "MglGraphicManager.h"

#define _MGL3D_COORDINATE_LEFT_HAND		(0)	//	左手座標系
#define _MGL3D_COORDINATE_RIGHT_HAND	(1)	//	右手座標系
#define _MGL3D_COORDINATE_USE			_MGL3D_COORDINATE_LEFT_HAND

#define MGL3D_X	(0)
#define MGL3D_Y	(1)
#define MGL3D_Z	(2)

//	クラス宣言
class DLL_EXP CMgl3DManager
{
protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	_MGL_IDirect3DDevice* m_pD3dDev;	//	D3Dデバイス
	D3DXMATRIX m_projection;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matWorld;

	float m_fAspectRatio;
	float m_fViewingAngle;
	float m_fClipNear;
	float m_fClipFar;

	float m_fCameraPosX;
	float m_fCameraPosY;
	float m_fCameraPosZ;
	float m_fCameraTargetX;
	float m_fCameraTargetY;
	float m_fCameraTargetZ;

	float m_fCameraRotationMemX;
	float m_fCameraRotationMemY;
	float m_fCameraRotationMemZ;

	void CameraLockAt(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ);
	void SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ);
	void SetCameraPos(float x, float y, float z);

public:

	//////////////////////////
	//
	//		公開メソッド
	//

	//	コンストラクタ/デストラクタ
	CMgl3DManager();
	virtual ~CMgl3DManager();

	//	初期化/開放
	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd );
	void Release();

	/////////////////////////////////////////////////////////////////

	//	Projection
	void SetupProjection( float fAspectRatio, float fViewingAngle=45.0f, float fClipNear=0.01f, float fClipFar=100.0f );
	
	//	カメラ
	void SetCameraViewTarget(float x, float y, float z);
	void MoveCamera(float x, float y, float z);
	void SetCameraAngle(float fAngleX, float fAngleY, float fAngleZ);
	void SetCameraAngle2(float fAngleX, float fAngleY, float fAngleZ);
	void CameraRotation(int direction, float fAngle);

	void ConvertToScreenVector(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pInVector);
};

#endif//__Mgl3DManager_H__
