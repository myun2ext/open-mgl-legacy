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

//	クラス宣言
class DLL_EXP CMglMatrixManager : public CMglCameraMatrixManager //public virtual CMglDgBase
{
protected:
	CMglWorldMatrixManager *m_pWorldMgr;
	CMglWorldMatrixManager m_initWorld;	//	初期状態のワールドマトリックス（デフォルト）
	CMglProjectionMatrixManager m_matMgrProjection;

	/*void WorldCheck(){
		if ( m_pWorldMgr == NULL )
			MyuThrow(MGLMSGNO_MATRIX(1), "CMglMatrixManager  SetWorld()にてワールドを設定してください。");
	}*/

public:

	//////////////////////////
	//
	//		公開メソッド
	//

	//	コンストラクタ/デストラクタ
	CMglMatrixManager();
	virtual ~CMglMatrixManager();

	//	初期化/開放
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
