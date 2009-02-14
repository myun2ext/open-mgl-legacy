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

};
typedef CMgl3dManager CMgl3DManager;

#endif//__Mgl3dManager_H__
