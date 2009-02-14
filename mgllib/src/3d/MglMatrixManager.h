///////////////////////////////////////////////////////////////////////
//
//	MglMatrixManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglMatrixManager_H__
#define __MglMatrixManager_H__

#include "Mgl3dManager.h"

//	クラス宣言
class DLL_EXP CMglMatrixManager
{
private:
	//	内部メソッド（チェック用）
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

protected:
	CMglGraphicManager* m_myudg;	//	DGクラスへのポインタを格納
	_MGL_IDirect3DDevice* m_pD3dDev;	//	D3Dデバイス
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_projection;

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

	float m_fRotateX;
	float m_fRotateY;
	float m_fRotateZ;
	float m_fMoveX;
	float m_fMoveY;
	float m_fMoveZ;

	void CameraLockAt(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ);

	//	とりあえず制限に・・・
	void CameraRotation(int direction, float fAngle);

public:

	//////////////////////////
	//
	//		公開メソッド
	//

	//	コンストラクタ/デストラクタ
	CMglMatrixManager();
	virtual ~CMglMatrixManager();

	//	初期化/開放
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	void Release();

	/////////////////////////////////////////////////////////////////

	void ReTransform();
	void OnFrame(){}

	//	Projection
	void SetupProjection( float fAspectRatio, float fViewingAngle=30.0f, float fClipNear=0.01f, float fClipFar=100.0f );
	
	//	カメラ
	void SetCameraCenter(float x, float y, float z){ SetCameraViewTarget(x,y,z); }
	void SetCameraViewTarget(float x, float y, float z);
	void MoveCamera(float x, float y, float z);
	void SetCameraAngle(float fAngleX, float fAngleY, float fAngleZ);
	void SetCameraAngle2(float fAngleX, float fAngleY, float fAngleZ);
	void SetCamera(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ);
	void SetCameraPos(float x, float y, float z);
	void SetCameraPosition(float x, float y, float z){ SetCameraPos(x,y,z); }

	//	ワールド
	void SetWorld(
		float fRotateX, float fRotateY=0.0f, float fRotateZ=0.0f,
		float fMoveX=0.0f, float fMoveY=0.0f, float fMoveZ=0.0f );
	void RotateX(float fAngle){ Rotate(fAngle,0,0); }
	void RotateY(float fAngle){ Rotate(0,fAngle,0); }
	void RotateZ(float fAngle){ Rotate(0,0,fAngle); }
	void Rotate(float fAngleX, float fAngleY, float fAngleZ);

	//	各Matrixの設定
	/*void SetWorldMatrix(D3DXMATRIX &matWorld){ m_matWorld = matWorld; }
	void SetViewMatrix(D3DXMATRIX &matView){ m_matView = matView; }
	void SetProjectionMatrix(D3DXMATRIX &matProjection){ m_projection = matProjection; }*/
	void SetWorldMatrix(D3DXMATRIX &matWorld);
	void SetViewMatrix(D3DXMATRIX &matView);
	void SetProjectionMatrix(D3DXMATRIX &matProjection);

	D3DXMATRIX& GetWorldMatrix(){ return m_matWorld; }
	D3DXMATRIX& GetViewMatrix(){ return m_matView; }
	D3DXMATRIX& GetProjectionMatrix(){ return m_projection; }

	void ConvertToScreenVector(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pInVector);
};

#endif//__MglMatrixManager_H__
