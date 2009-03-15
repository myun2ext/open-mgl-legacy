///////////////////////////////////////////////////////////////////////
//
//	MglCameraMatrixManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglCameraMatrixManager_H__
#define __MglCameraMatrixManager_H__

#include "MglGraphicManager.h"

#define _MGL3D_COORDINATE_LEFT_HAND		(0)	//	左手座標系
#define _MGL3D_COORDINATE_RIGHT_HAND	(1)	//	右手座標系
#define _MGL3D_COORDINATE_USE			_MGL3D_COORDINATE_LEFT_HAND

#define MGL3D_X	(0)
#define MGL3D_Y	(1)
#define MGL3D_Z	(2)

//	クラス宣言
class DLL_EXP CMglCameraMatrixManager : public virtual CMglDgBase
{
private:

protected:
	D3DXMATRIX m_matView;

	//	記憶
	D3DXVECTOR3 m_vecTarget;
	D3DXVECTOR3 m_vecPos;
	D3DXVECTOR3 m_vecRotateTarget;
	D3DXVECTOR3 m_vecRotatePos;
	//float m_fRotate; <- m_vecRotatePos.z でいい気がする・・・？

	//	↓いるんかなこれ・・・？（キャッシュとかか・・・？
	D3DXMATRIX m_matTarget;
	D3DXMATRIX m_matPos;

	//////////////////////////////////

	//void CameraLockAt(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ, float fRotate);
	void ReCreateViewMatrix(D3DXVECTOR3 &vecEye, D3DXVECTOR3 &vecAt, D3DXVECTOR3 &vecUp);

public:

	//////////////////////////
	//
	//		公開メソッド
	//

	//	コンストラクタ/デストラクタ
	CMglCameraMatrixManager();
	virtual ~CMglCameraMatrixManager();

	//	初期化/開放
	virtual void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	virtual void Release();

	/////////////////////////////////////////////////////////////////

	void ReTransform();
	
	//	カメラ
	void SetCamera(float fTargetX, float fTargetY, float fTargetZ, float fPosX, float fPosY, float fPosZ, float fRotate=0.0f){
		SetCamera( D3DXVECTOR3(fTargetX,fTargetY,fTargetZ), D3DXVECTOR3(fPosX,fPosY,fPosZ), fRotate); }
	void SetCamera(D3DXMATRIX &matTarget, D3DXMATRIX& matPos, float fRotate=0.0f);
	void SetCamera(D3DXVECTOR3 &vecTarget, D3DXVECTOR3 &vecPos, float fRotate=0.0f);

	void SetTargetPos(float x, float y, float z){ SetTargetPos(D3DXVECTOR3(x,y,z)); }
	void SetTargetPos(D3DXVECTOR3 &vec);
	void SetCameraPos(float x, float y, float z){ SetCameraPos(D3DXVECTOR3(x,y,z)); }
	void SetCameraPos(D3DXVECTOR3 &vec);
	void MoveTarget(float x, float y, float z){ MoveTarget(D3DXVECTOR3(x,y,z)); }
	void MoveTarget(D3DXVECTOR3 &vec);
	void MoveCamera(float x, float y, float z){ MoveCamera(D3DXVECTOR3(x,y,z)); }
	void MoveCamera(D3DXVECTOR3 &vec);

	void SetCameraAngle(float fAngleX, float fAngleY, float fAngleZ){ SetCameraAngle(D3DXVECTOR3(fAngleX,fAngleY,fAngleZ)); }
	void SetCameraAngle(D3DXVECTOR3 &vecAngles);
	void RotateX(float fAngle){ Rotate(fAngle,0,0); }
	void RotateY(float fAngle){ Rotate(0,fAngle,0); }
	void RotateZ(float fAngle){ Rotate(0,0,fAngle); }
	void Rotate(float fAngleX, float fAngleY, float fAngleZ);

	/////////////////////////////////////////////////////////

	void SetViewMatrix(D3DXMATRIX &matView);
	D3DXMATRIX& GetViewMatrix(){ return m_matView; }
};

#endif//__MglCameraMatrixManager_H__
