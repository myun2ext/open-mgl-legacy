///////////////////////////////////////////////////////////////////////
//
//	Mgl3dManager
//
///////////////////////////////////////////////////////////////////////

#ifndef __Mgl3dManager_H__
#define __Mgl3dManager_H__

#include "MglGraphicManager.h"
#include "MglMatrixManager.h"

//	�N���X�錾
class DLL_EXP CMgl3dManager : public CMglMatrixManager //public virtual CMglDgBase
{
private:
	//	�������\�b�h�i�`�F�b�N�p�j
	/*void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}*/

protected:

public:

	//////////////////////////
	//
	//		���J���\�b�h
	//

	//	�R���X�g���N�^/�f�X�g���N�^
	CMgl3dManager();
	virtual ~CMgl3dManager();

	//	������/�J��
	virtual void Init( CMglGraphicManager* in_myudg=GetDefaultGd() );
	virtual void Release();

	/////////////////////////////////////////////////////////////////

	void OnFrame(){}

	CMglGraphicManager* GetDg(){ return m_myudg; }
	CMglGraphicManager* GetMyuDg(){ return m_myudg; }
};
typedef CMgl3dManager CMgl3DManager;

//////////////////////////////////////////////////////////

template <typename T> class CMglWorldMatrixHolder : public T, public CMglMatrixManager
{
protected:
	CMgl3dManager *m_3d;

public:
	virtual void Init( CMgl3dManager* in_3dMgr )
	{
		m_3d = in_3dMgr;

		CMglGraphicManager* pDg = m_3d->GetMyuDg();
		T::Init(pDg);
		CMglMatrixManager::Init(pDg);
	}
};

#endif//__Mgl3dManager_H__
