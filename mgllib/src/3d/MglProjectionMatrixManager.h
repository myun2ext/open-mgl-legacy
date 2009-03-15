///////////////////////////////////////////////////////////////////////
//
//	MglProjectionMatrixManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglProjectionMatrixManager_H__
#define __MglProjectionMatrixManager_H__

#include "MglGraphicManager.h"

#define _MGL3D_COORDINATE_LEFT_HAND		(0)	//	������W�n
#define _MGL3D_COORDINATE_RIGHT_HAND	(1)	//	�E����W�n
#define _MGL3D_COORDINATE_USE			_MGL3D_COORDINATE_LEFT_HAND

#define MGL3D_X	(0)
#define MGL3D_Y	(1)
#define MGL3D_Z	(2)

//	�N���X�錾
class DLL_EXP CMglProjectionMatrixManager : public virtual CMglDgBase
{
private:

protected:
	D3DXMATRIX m_projection;

	float m_fAspectRatio;
	float m_fViewingAngle;
	float m_fClipNear;
	float m_fClipFar;
public:

	//////////////////////////
	//
	//		���J���\�b�h
	//

	//	�R���X�g���N�^/�f�X�g���N�^
	CMglProjectionMatrixManager();
	virtual ~CMglProjectionMatrixManager();

	//	������/�J��
	virtual void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	virtual void Release();

	/////////////////////////////////////////////////////////////////

	void ReTransform();

	//	Projection
	void SetupProjection( float fAspectRatio, float fViewingAngle=30.0f, float fClipNear=0.01f, float fClipFar=100.0f );
	void SetProjectionMatrix(D3DXMATRIX &matProjection);

	D3DXMATRIX& GetProjectionMatrix(){ return m_projection; }
};

typedef CMglProjectionMatrixManager CMglPerspectiveMatrixManager;

#endif//__MglProjectionMatrixManager_H__
