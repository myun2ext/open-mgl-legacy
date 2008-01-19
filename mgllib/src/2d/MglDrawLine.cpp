//////////////////////////////////////////////////////////
//
//	MglDrawLine
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglDrawLine.h"

CMglTexture* CMglDrawLine::m_pLineTex;

//	�R���X�g���N�^
CMglDrawLine::CMglDrawLine(){
	//	�����񂾂�
	if ( m_pLineTex == NULL ){
		m_pLineTex = new CMglTexture();

		//m_pLineTex->Create(1,1,FALSE);
		m_pLineTex->Create(2,2,FALSE);
	}
}

//	�`��
void CMglDrawLine::Draw(float fStartX, float fStartY, float fEndX, float fEndY, D3DCOLOR startColor, D3DCOLOR endColor, float width)
{
	m_pLineTex->CreateCheck();	//	Create�`�F�b�N

	MYU_VERTEX vertices[4];		//	���_
	ZeroMemory( vertices, sizeof(vertices) );

	//	�]�����ݒ�
	vertices[VERTEXNO_LT].tu = vertices[VERTEXNO_LB].tu = 0.0f;
	vertices[VERTEXNO_LT].tv = vertices[VERTEXNO_RT].tv = 0.0f;
	vertices[VERTEXNO_RB].tu = vertices[VERTEXNO_RT].tu = 1.0f;
	vertices[VERTEXNO_RB].tv = vertices[VERTEXNO_LB].tv = 1.0f;

	//	�n�_
	vertices[VERTEXNO_LT].x = fStartX;
	vertices[VERTEXNO_LT].y = fStartY;
	vertices[VERTEXNO_RT].y = fStartX;
	vertices[VERTEXNO_RT].x = fStartY;
	vertices[VERTEXNO_LT].color = startColor;
	vertices[VERTEXNO_RT].color = startColor;
	
	//	�I�_
	vertices[VERTEXNO_LB].x = fEndX;
	vertices[VERTEXNO_LB].y = fEndY;
	vertices[VERTEXNO_RB].x = fEndX;
	vertices[VERTEXNO_RB].y = fEndY;
	vertices[VERTEXNO_LB].color = endColor;
	vertices[VERTEXNO_RB].color = endColor;

	//	�A���t�@�I�v�V����
	m_myudg->SetAlphaMode( MGL_ALPHA_OPT_DEFAULT );

	//	�`��
	Draw( vertices );
}

