///////////////////////////////////////////////////////////////////////
//
//	MglMatrixManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __MglMatrixManager_H__
#define __MglMatrixManager_H__

#include "MglGraphicManager.h"
#include "MglCameraMatrixManager.h"
#include "MglWorldMatrixManager.h"

//	�N���X�錾
class DLL_EXP CMglMatrixManager : public CMglCameraMatrixManager //public virtual CMglDgBase
{
protected:
	CMglWorldMatrixManager *m_pWorldMgr;

	void WorldCheck(){
		if ( m_pWorldMgr == NULL )
			MyuThrow(MGLMSGNO_MATRIX(1), "CMglMatrixManager  SetWorld()�ɂă��[���h��ݒ肵�Ă��������B");
	}

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

	void SetWorld(CMglWorldMatrixManager *pWorldMgr){ m_pWorldMgr = pWorldMgr; }

	void ReTransform();

	/////////////////////////////////////////////////////////////////

	void ConvertToScreenVector(D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pInVector);
};

#endif//__MglMatrixManager_H__
