//////////////////////////////////////////////////////////
//
//	Mgl3dSquare
//		- MglGraphicManager �T�[�t�F�X�N���X
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Mgl3dSquare.h"

//	�R���X�g���N�^
CMgl3dSquare::CMgl3dSquare()
{
	m_myudg = NULL;
	m_d3d = NULL;
}

//	������
void CMgl3dSquare::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	m_d3d = m_myudg->GetD3dDevPtr();
}

//	�쐬
void CMgl3dSquare::SimpleCreate(float fWidth, float fHeight, D3DCOLOR color)
{
	MYUX_VERTEX v;
	v.color = color;
	v.x = 0;
	//v.SetTuTv(

	v.x = 0; v.y = 0; 
	AddVertex(v);
	v.x = fWidth; v.y = 0; 
	AddVertex(v);
	v.x = 0; v.y = fHeight; 
	AddVertex(v);
	v.x = fWidth; v.y = fHeight; 
	AddVertex(v);
}
