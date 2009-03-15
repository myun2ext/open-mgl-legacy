///////////////////////////////////////////////////////////////////////
//
//	MglMatrixManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglMatrixManager_H__
#define __MglMatrixManager_H__

#include "MglGraphicManager.h"
#include "MglProjectionMatrixManager.h"
#include "MglCameraMatrixManager.h"
#include "MglWorldMatrixManager.h"

//	�N���X�錾
class DLL_EXP CMglMatrixManager : public CMglCameraMatrixManager //public virtual CMglDgBase
{
protected:
	CMglWorldMatrixManager *m_pWorldMgr;
	CMglWorldMatrixManager m_initWorld;	//	������Ԃ̃��[���h�}�g���b�N�X�i�f�t�H���g�j
	CMglProjectionMatrixManager m_matMgrProjection;

	/*void WorldCheck(){
		if ( m_pWorldMgr == NULL )
			MyuThrow(MGLMSGNO_MATRIX(1), "CMglMatrixManager  SetWorld()�ɂă��[���h��ݒ肵�Ă��������B");
	}*/

public:

	//////////////////////////
	//
	//		���J���\�b�h
	//

	//	�R���X�g���N�^/�f�X�g���N�^
	CMglMatrixManager();
	virtual ~CMglMatrixManager();

	//	������/�J��
	virtual void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	virtual void Release();

	/////////////////////////////////////////////////////////////////

	void SetWorld(CMglWorldMatrixManager &worldMatrix){ m_pWorldMgr = &worldMatrix; }
	void SetWorldMatrix(CMglWorldMatrixManager &worldMatrix){ m_pWorldMgr = &worldMatrix; }
	void SetWorldMatrixMgr(CMglWorldMatrixManager &worldMatrix){ m_pWorldMgr = &worldMatrix; }
	void SetWorldMatrixManager(CMglWorldMatrixManager &worldMatrix){ m_pWorldMgr = &worldMatrix; }

	void ReTransform();

	/////////////////////////////////////////////////////////////////

	D3DXMATRIX& GetProjectionMatrix(){ return m_matMgrProjection.GetProjectionMatrix(); }

	void ConvertToScreenVector(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pInVector);
};

#endif//__MglMatrixManager_H__
