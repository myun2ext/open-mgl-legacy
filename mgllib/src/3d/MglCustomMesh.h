//////////////////////////////////////////////////////////
//
//	CMglCustomMesh - カスタムメッシュ
//
//////////////////////////////////////////////////////////

#ifndef __MglCustomMesh_H__
#define __MglCustomMesh_H__

#include "MglMesh.h"

//	クラス宣言
class DLL_EXP CMglCustomMesh : public CMglMesh
{
protected:

public:
	//	コンストラクタ・デストラクタ
	CMglCustomMesh();
	virtual ~CMglCustomMesh(){}

};

typedef CMglCustomMesh CMglUserMesh, CMglUserModel;

#endif//__MglCustomMesh_H__
