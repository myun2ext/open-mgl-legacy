//////////////////////////////////////////////////////////
//
//	CMglCustomMesh - �J�X�^�����b�V��
//
//////////////////////////////////////////////////////////

#ifndef __MglCustomMesh_H__
#define __MglCustomMesh_H__

#include "MglMesh.h"

//	�N���X�錾
class DLL_EXP CMglCustomMesh : public CMglMesh
{
protected:

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglCustomMesh();
	virtual ~CMglCustomMesh(){}

};

typedef CMglCustomMesh CMglUserMesh, CMglUserModel;

#endif//__MglCustomMesh_H__
