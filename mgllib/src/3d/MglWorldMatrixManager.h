///////////////////////////////////////////////////////////////////////
//
//	MglWorldMatrixManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglWorldMatrixManager_H__
#define __MglWorldMatrixManager_H__

#include "MglGraphicManager.h"

#define _MGL3D_COORDINATE_LEFT_HAND		(0)	//	������W�n
#define _MGL3D_COORDINATE_RIGHT_HAND	(1)	//	�E����W�n
#define _MGL3D_COORDINATE_USE			_MGL3D_COORDINATE_LEFT_HAND

#define MGL3D_X	(0)
#define MGL3D_Y	(1)
#define MGL3D_Z	(2)

//	�N���X�錾
class DLL_EXP CMglWorldMatrixManager : public virtual CMglDgBase
{
private:

protected:
	D3DXMATRIX m_matWorld;

	float m_fRotateX;
	float m_fRotateY;
	float m_fRotateZ;
	float m_fMoveX;
	float m_fMoveY;
	float m_fMoveZ;

public:

	//////////////////////////
	//
	//		���J���\�b�h
	//

	//	�R���X�g���N�^/�f�X�g���N�^
	CMglWorldMatrixManager();
	virtual ~CMglWorldMatrixManager();

	//	������/�J��
	virtual void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	virtual void Release();

	/////////////////////////////////////////////////////////////////

	void SetsTransform();
	void ReTransform(){ SetsTransform(); }

	//	���[���h
	void SetWorld(
		float fRotateX, float fRotateY=0.0f, float fRotateZ=0.0f,
		float fMoveX=0.0f, float fMoveY=0.0f, float fMoveZ=0.0f );
	void RotateX(float fAngle){ Rotate(fAngle,0,0); }
	void RotateY(float fAngle){ Rotate(0,fAngle,0); }
	void RotateZ(float fAngle){ Rotate(0,0,fAngle); }
	void Rotate(float fAngleX, float fAngleY, float fAngleZ);

	//	�eMatrix�̐ݒ�
	/*void SetWorldMatrix(D3DXMATRIX &matWorld){ m_matWorld = matWorld; }
	void SetViewMatrix(D3DXMATRIX &matView){ m_matView = matView; }
	void SetProjectionMatrix(D3DXMATRIX &matProjection){ m_projection = matProjection; }*/
	void SetWorldMatrix(D3DXMATRIX &matWorld);

	D3DXMATRIX& GetWorldMatrix(){ return m_matWorld; }
	D3DXMATRIX& GetMatrix(){ return m_matWorld; }
};

#endif//__MglWorldMatrixManager_H__
