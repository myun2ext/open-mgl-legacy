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
	D3DXVECTOR3 m_vecCamera;
	D3DXVECTOR3 m_vecRotateTarget;
	D3DXVECTOR3 m_vecRotateCamera;
	//float m_fRotate; <- m_vecRotatePos.z でいい気がする・・・？

	//	↓いるんかなこれ・・・？（キャッシュとかか・・・？
	D3DXMATRIX m_matTarget;
	D3DXMATRIX m_matPos;

	//////////////////////////////////

	//void CameraLockAt(float fPosX, float fPosY, float fPosZ, float fTargetX, float fTargetY, float fTargetZ, float fRotate);
	void ReCreateViewMatrix();
	void ReCreateMatrixLookAt(D3DXVECTOR3 &vecPos, D3DXVECTOR3 &vecTarget, D3DXVECTOR3 &vecUp);

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
	/*void SetCamera(float fTargetX, float fTargetY, float fTargetZ, float fPosX, float fPosY, float fPosZ, float fRotate=0.0f){
		SetCamera( D3DXVECTOR3(fTargetX,fTargetY,fTargetZ), D3DXVECTOR3(fPosX,fPosY,fPosZ), fRotate); }
	//void SetCamera(D3DXMATRIX &matTarget, D3DXMATRIX& matPos, float fRotate=0.0f);
	void SetCamera(D3DXVECTOR3 &vecTarget, D3DXVECTOR3 &vecPos, float fRotate=0.0f);*/
	/*void SetCamera(float fTargetX, float fTargetY, float fTargetZ,
		float fPosX, float fPosY, float fPosZ){
		SetCamera( D3DXVECTOR3(fTargetX,fTargetY,fTargetZ), D3DXVECTOR3(fPosX,fPosY,fPosZ)); }
	//void SetCamera(D3DXMATRIX &matTarget, D3DXMATRIX& matPos);
	void SetCamera(D3DXVECTOR3 &vecTarget, D3DXVECTOR3 &vecPos);*/
	void SetCamera(float fTargetX, float fTargetY, float fTargetZ, float fPosX, float fPosY, float fPosZ)
	{
		SetCamera(D3DXVECTOR3(fTargetX,fTargetY,fTargetZ), D3DXVECTOR3(fPosX,fPosY,fPosZ));
	}
	void SetCamera(D3DXVECTOR3 &vecTarget, D3DXVECTOR3 &vecPos){
		SetTargetPos(vecTarget);
		SetCameraPos(vecPos);
	}

	//////////////////////////////////////////////////////////////////////////////

	//	カメラの位置を設定
	void SetCameraPos(float x, float y, float z){ SetCameraPos(D3DXVECTOR3(x,y,z)); }
	void SetCameraPos(D3DXVECTOR3 &vec){ m_vecCamera = vec; }
	
	//	対象の位置を設定
	void SetTargetPos(float x, float y, float z){ SetTargetPos(D3DXVECTOR3(x,y,z)); }
	void SetTargetPos(D3DXVECTOR3 &vec){ m_vecTarget = vec; }

	//	カメラを指定距離移動
	void MoveCamera(float x, float y, float z){ MoveCamera(D3DXVECTOR3(x,y,z)); }
	void MoveCamera(D3DXVECTOR3 &vec){ m_vecCamera += vec; }

	//	対象を指定距離移動
	void MoveTarget(float x, float y, float z){ MoveTarget(D3DXVECTOR3(x,y,z)); }
	void MoveTarget(D3DXVECTOR3 &vec){ m_vecTarget += vec; }

	//	画面全体を移動（対象とカメラを移動）
	void Shift(float x, float y, float z){ Shift(D3DXVECTOR3(x,y,z)); }
	void Shift(D3DXVECTOR3 &vec){ MoveCamera(vec); MoveTarget(vec); }

	//////////////////////////////////////////////////////////////////////////////

	//	カメラを（対象を軸に）回転移動
	void RotateCamera(float fAngleX, float fAngleY, float fAngleZ){ RotateCamera(D3DXVECTOR3(fAngleX,fAngleY,fAngleZ)); }
	void RotateCamera(D3DXVECTOR3 &vecAngles){ m_vecRotateCamera += vecAngles; }

	//	対象を（カメラを軸に）回転移動
	void RotateTarget(float fAngleX, float fAngleY, float fAngleZ){ RotateTarget(D3DXVECTOR3(fAngleX,fAngleY,fAngleZ)); }
	void RotateTarget(D3DXVECTOR3 &vecAngles){ m_vecRotateTarget += vecAngles; }

	//	カメラの（対象を軸にした）絶対角度を設定
	void SetRotateAngleCamera(float fAngleX, float fAngleY, float fAngleZ){ SetRotateAngleCamera(D3DXVECTOR3(fAngleX,fAngleY,fAngleZ)); }
	void SetRotateAngleCamera(D3DXVECTOR3 &vecAngles){ m_vecRotateCamera = vecAngles; }

	//	対象の（カメラを軸にした）絶対角度を設定
	void SetRotateAngleTarget(float fAngleX, float fAngleY, float fAngleZ){ SetRotateAngleTarget(D3DXVECTOR3(fAngleX,fAngleY,fAngleZ)); }
	void SetRotateAngleTarget(D3DXVECTOR3 &vecAngles){ m_vecRotateTarget = vecAngles; }
	
	//	ズームインとズームアウト
	void ZoomIn(float fDistance);
	void ZoomOut(float fDistance);

	/////////////////////////////////////////////////////////

	void SetViewMatrix(D3DXMATRIX &matView);
	D3DXMATRIX& GetViewMatrix(){ return m_matView; }
};

#endif//__MglCameraMatrixManager_H__
