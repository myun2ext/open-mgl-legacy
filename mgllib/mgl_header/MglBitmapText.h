//////////////////////////////////////////////////////////
//
//	MglBitmapText  v0.11.00 04/03/01
//		- �r�b�g�}�b�v�e�L�X�g�\���N���X
//
//	v0.10.00 04/12/18
//	�E�V�K�쐬
//
//	v0.11.00 04/03/01
//	�EDrawEx2()�̎d�l��ύX�B�i�h�L�������g�ɂ��킹��j
//
//////////////////////////////////////////////////////////

#ifndef __MglBitmapText_H__
#define __MglBitmapText_H__

#include "MglGraphicManager.h"
#include "MglImage.h"

//	�N���X�錾
class DLL_EXP CMglBitmapText
{
private:
	CMglGraphicManager *m_myudg;

	CMglImage sfcBitmapFont;
	string m_stringSequence;
	int m_nOneCharWidth;
	int m_nOneCharHeight;
	BOOL initFlg;

	//	Init�`�F�b�N
	void InitCheck() {
		if ( initFlg == FALSE )
			MyuThrow( 0, "CMglBitmapText  Init()����ԍŏ��ɌĂ�ł��������B" );
	}

public:
	CMglBitmapText();
	virtual ~CMglBitmapText();

	void Init( CMglGraphicManager *in_myudg, const char* szBitmapFile,
		int nOneCharWidth, int nOneCharHeight, const char* szStringSequence );

	void Draw( const char* szDrawString, float x, float y, D3DCOLOR color=0xffffffff );
	void Draw( int nDrawNum, float x, float y, D3DCOLOR color=0xffffffff );

	void DrawEx( const char* szDrawString, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_TRANSLUCENCE );
	void DrawEx( int nDrawNum, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_TRANSLUCENCE );

	void DrawEx2( const char* szDrawString, int nCharSpace, int nLineSpace, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_TRANSLUCENCE );
	void DrawEx2( int nDrawNum, int nCharSpace, int nLineSpace, float fScaleX, float fScaleY, float fRotationCenterX, float fRotationCenterY, float fAngle,
		float x, float y, D3DCOLOR color=0xffffffff, DWORD dwAlphaOption=MGL_ALPHA_OPT_TRANSLUCENCE );
};

#endif//__MglBitmapText_H__