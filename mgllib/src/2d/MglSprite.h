//////////////////////////////////////////////////////////
//
//	MglSprite - ���C���[
//
//////////////////////////////////////////////////////////

#ifndef __MglSprite_H__
#define __MglSprite_H__

#include "MglD3dTexture.h"

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CMglSprite
{
private:
	CMglDxTexture* m_pTex;

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMglSprite();
	virtual ~CMglSprite();

	void Draw();
};


#endif//__MglSprite_H__