//////////////////////////////////////////////////////////
//
//	MglDrawLine - ���G��N���X
//
//////////////////////////////////////////////////////////

#ifndef __MglDrawLine_H__
#define __MglDrawLine_H__

#include "MglGraphicManager.h"
#include "MglTexture.h"

//	�N���X�錾
class DLL_EXP CMglDrawLine
{
protected:
	static CMglTexture* m_pLineTex;

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglDrawLine();
	virtual ~CMglDrawLine(){}

	void Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR color=D3DCOLOR_WHITE, float width=1.0f){
		Draw( fStartX,fStartY,fEndX,fEndY, color,color,width ); }
	//void Draw(float x, float y, D3DCOLOR startColor=D3DCOLOR_WHITE, D3DCOLOR endColor=D3DCOLOR_BLACK, float width=1.0f);
	void Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width=1.0f);
};

#endif//__MglDrawLine_H__
