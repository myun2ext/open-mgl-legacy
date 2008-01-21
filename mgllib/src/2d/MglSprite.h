//////////////////////////////////////////////////////////
//
//	MglSprite - ���C���[
//
//////////////////////////////////////////////////////////

#ifndef __MglSprite_H__
#define __MglSprite_H__

#include "MglImage.h"

//	�N���X�錾  /////////////////////////////////////////////////////////
class DLL_EXP CMglSprite : public CMglImage
{
private:
	BOOL m_bShow;			//	�\�����邩
	RECT m_rect;			//	��`�̈�
	//RECT* pRect;		//	��`�̈�B�w�肳��Ă����rect�̃|�C���^���A�w�肳��ĂȂ����NULL������
	D3DCOLOR m_color;		//	�A���t�@�l | �J���[

	//	2008/01/20  �g��
	float m_x, m_y;				//	�ꏊ
	float m_fScaleX, m_fScaleY;	//	�k�ڗ�
	float m_fRotationCenterX;
	float m_fRotationCenterY;
	float m_fAngle;			//	�p�x

public:
	//	�R���X�g���N�^/�f�X�g���N�^
	CMglSprite();
	virtual ~CMglSprite();

	void Draw();
};


#endif//__MglSprite_H__