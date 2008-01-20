//////////////////////////////////////////////////////////
//
//	MglDrawLine - ���G��N���X
//
//////////////////////////////////////////////////////////

#ifndef __MglDrawLine_H__
#define __MglDrawLine_H__

#include "MglGraphicManager.h"
//#include "MglTexture.h"

//	�N���X�錾
class DLL_EXP CMglDrawLine
{
protected:
	CMglGraphicManager* m_myudg;	//	DG�N���X�ւ̃|�C���^���i�[
	IDirect3DDevice8* m_d3d;			//	D3DDevice�ւ̃|�C���^

	//static CMglTexture* m_pLineTex;

	//	�������\�b�h�i�`�F�b�N�p�j
	void InitCheck() {
		if ( m_myudg == NULL )
			Init( GetDefaultGd() );
	}

public:
	//	�R���X�g���N�^�E�f�X�g���N�^
	CMglDrawLine();
	virtual ~CMglDrawLine(){}

	void Init( CMglGraphicManager* in_myudg=g_pDefaultGd );

	void Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR color=D3DCOLOR_WHITE, float width=1.0f){
		Draw( fStartX,fStartY,fEndX,fEndY, color,color,width ); }
	//void Draw(float x, float y, D3DCOLOR startColor=D3DCOLOR_WHITE, D3DCOLOR endColor=D3DCOLOR_BLACK, float width=1.0f);
	void Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width=1.0f);
	void Draw2(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width=1.0f);

	//CMglTexture* GetInternalTexture(){ return m_pLineTex; }
};

#endif//__MglDrawLine_H__
