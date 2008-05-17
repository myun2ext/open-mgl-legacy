//////////////////////////////////////////////////////////
//
//	MglText  v0.10.01 04/01/30
//		- �e�L�X�g
//
//	v0.10.00 04/12/13
//	�E�V�K�쐬
//
//	v0.10.01 04/01/30
//	�ESetFont()��SetDrawParam()�ɖ��̕ύX
//
//////////////////////////////////////////////////////////

#ifndef __MglText_H__
#define __MglText_H__

#include "MglGraphicManager.h"
#include <stdarg.h>

#define MGL_TEXT_DEFAULT_FONT_SIZE	(12)
//#define FONT_NAME_MS_GOTHIC			"

//	�N���X�錾
class DLL_EXP CMglText : public CMyuReleaseBase
{
private:
	//	�ꉞ�����ێ����Ƃ�����
	CMglGraphicManager* m_myudg;			//	DG�N���X�ւ̃|�C���^���i�[
	IDirect3DDevice8* m_d3d;			//	D3DDevice�ւ̃|�C���^

	//	�C���^�[�t�F�[�X
	ID3DXFont *m_text;

	//	�쐬���ꂽ���L������t���O
	BOOL bCreateFlg;

	//	�t�H���g�ݒ�
	BOOL bSetParamFlg;
	int m_nX;
	int m_nY;
	DWORD m_dwOption;
	D3DCOLOR m_color;

	void SetParamCheck() {
		if ( bSetParamFlg != TRUE )
			MyuThrow( 0, "CMglText::Draw(),fDraw()  SetDrawParam()���ݒ肳��Ă��Ȃ��̂Ɉ������ȗ����܂����B" );
	}
	void _Init(){
		m_myudg = NULL;
		m_d3d = NULL;
		m_text = NULL;
		bCreateFlg = FALSE;
		bSetParamFlg = FALSE;
	}

public:
	CMglText(){
		_Init();
		Create();	//	�f�t�H���g�t�H���g
	}
	CMglText(CMglGraphicManager* in_myudg){
		_Init();
		InitAndCreate(in_myudg,MGL_TEXT_DEFAULT_FONT_SIZE);	//	�f�t�H���g�t�H���g
	}
	virtual ~CMglText();

	//	�������y�э쐬
	void InitAndCreate( CMglGraphicManager* in_myudg, HFONT hFont );
	void InitAndCreate( CMglGraphicManager* in_myudg, int nHeight );
	void InitAndEzCreate( CMglGraphicManager* in_myudg, int nHeight ){ InitAndCreate(in_myudg, nHeight); }	//	�Â�

	//	in_myudg�ȗ��`�B�֐�������Ă����e����
	void Create( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	void Create( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }
	void Init( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	void Init( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }
	void Setup( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	void Setup( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }

	//	��t�w��
	void Create( CMglGraphicManager* in_myudg, int nHeight, const char* szFontName,
		BOOL bItalic=FALSE, BOOL bBold=FALSE, BOOL bUnderLine=FALSE, BOOL bStrikeOut=FALSE, float fAngle=0.0f );
	void Create( int nHeight, const char* szFontName,
		BOOL bItalic=FALSE, BOOL bBold=FALSE, BOOL bUnderLine=FALSE, BOOL bStrikeOut=FALSE, float fAngle=0.0f )
	{	Create( GetDefaultGd(), nHeight, szFontName, bItalic, bBold, bUnderLine, bStrikeOut, fAngle); }

	//	�S�����ȗ�
	void Create(){ Init(MGL_TEXT_DEFAULT_FONT_SIZE); }
	void Init(){ Init(MGL_TEXT_DEFAULT_FONT_SIZE); }

	//	�����I�J��
	void Release();

	//	�G��
	void Draw( const char* szString, int nX, int nY, D3DCOLOR color, DWORD dwOption=0 );
	void Draw( const char* szString, D3DCOLOR color ) {
		SetParamCheck();
		Draw( szString, m_nX, m_nY, color, m_dwOption );
	}
	void Draw( const char* szString, int nX, int nY ) {
		SetParamCheck();
		Draw( szString, nX, nY, m_color, m_dwOption );
	}
	void Draw( const char* szString ){ FDraw( szString ); }
	void FDraw( const char* szString, ... );
	void SetDrawParam( int in_nX, int in_nY, D3DCOLOR in_color, DWORD in_dwOption=0 );
};

typedef CMglText CMglGraphicText;

#endif//__MglText_H__
