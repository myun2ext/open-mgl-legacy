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

//	Font Names  -- ("WIN"�Ƃ����悤���Ƃ��v�������A�悭�悭�l�����MGL��Windows�Ȃ̂ŕK�v�Ȃ��E�E�E�j
#define MGL_FONT_NAME_MS_GOTHIC			"MS Gothic"
#define MGL_FONT_NAME_MS_PGOTHIC		"MS PGothic"
#define MGL_FONT_NAME_MS_P_GOTHIC		"MS PGothic"	//	alias
#define MGL_FONT_NAME_MS_UI_GOTHIC		"MS UI Gothic"
#define MGL_FONT_NAME_MS_MINCHO			"MS Mincho"
#define MGL_FONT_NAME_MS_PMINCHO		"MS PMincho"
#define MGL_FONT_NAME_MS_P_MINCHO		"MS PMincho"	//	alias
#define MGL_FONT_NAME_DEFAULT			MGL_FONT_NAME_MS_P_GOTHIC

//	�ȍ~�͉p��t�H���g�i���{��g���ƕ����������܂��j
//	�i��MGL_FONT_NAME_LUCIDA_SANS_UNICODE�AMGL_FONT_NAME_TAHOMA�����͓��{��C�P��݂����ł��j
#define MGL_FONT_NAME_ARIAL					"Arial"					//	Win98 later
#define MGL_FONT_NAME_ARIAL_BLACK			"Arial Black"			//	Win98 later
#define MGL_FONT_NAME_ARIAL_NARROW			"Arial Narrow"			//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_CENTURY				"Century"				//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_CENTURY_GOTHIC		"Century Gothic"		//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_COMIC_SANS_MS			"Comic Sans MS"			//	Win98 later
#define MGL_FONT_NAME_COURIER_NEW			"Courier New"			//	Win98 later
#define MGL_FONT_NAME_GEORGIA				"Georgia"				//	Win2000 later

#define MGL_FONT_NAME_IMPACT				"Impact"				//	Win98 later
#define MGL_FONT_NAME_LUCIDA_SANS_UNICODE	"Lucida Sans Unicode"	//	Win2000 later / Japanese Ready
#define MGL_FONT_NAME_LUCIDA_SANS_DEMIBOLD	"Lucida Sans Demibold"	//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_PALATINO_LINOTYPE		"Palatino Linotype"		//	Win2000 later
#define MGL_FONT_NAME_RAAVI					"Raavi"					//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_SEGEO_UI				"Segeo UI"				//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_SYMBOL				"Symbol"				//	Win98 later

#define MGL_FONT_NAME_TAHOMA				"Tahoma"				//	Win98 later / Japanese Ready
#define MGL_FONT_NAME_TIMES_NEW_ROMAN		"Times New Roman"		//	Win98 later
#define MGL_FONT_NAME_TUNGA					"Tunga"					//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_VERDANA				"Verdana"				//	Win98 later
#define MGL_FONT_NAME_VRINDA				"Vrinda"				//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_WEBDINGS				"Webdings"				//	Win98 later
#define MGL_FONT_NAME_WINGDINGS				"Wingdings"				//	Win98 later
#define MGL_FONT_NAME_WINGDINGS2			"Wingdings 2"			//	? (WinXP later or MS Office Font?)
#define MGL_FONT_NAME_WINGDINGS3			"Wingdings 3"			//	? (WinXP later or MS Office Font?)

/////////////////////////////////////////////////////////////////////////

//#if _MGL_DXVER == 8
#if _MGL_D3DXVER < MGL_D3DXVER_ID3DXFONT_CHANGED

//	�N���X�錾
class DLL_EXP CMglText : public CMyuReleaseBase
{
private:
	//	�ꉞ�����ێ����Ƃ�����
	CMglGraphicManager* m_myudg;			//	DG�N���X�ւ̃|�C���^���i�[
	_MGL_IDirect3DDevice* m_d3d;			//	D3DDevice�ւ̃|�C���^

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
		ZeroMemory(&m_rect, sizeof(m_rect));
	}

public:
	CMglText(){
		_Init();
		/*if ( CheckDefaultGd() )
			Create();	//	�f�t�H���g�t�H���g*/
	}
	CMglText(CMglGraphicManager* in_myudg){
		_Init();
		InitAndCreate(in_myudg,MGL_TEXT_DEFAULT_FONT_SIZE);	//	�f�t�H���g�t�H���g
	}
	virtual ~CMglText();

	//	�������y�э쐬
	void Init( CMglGraphicManager* in_myudg=GetDefaultGd() ){
		m_myudg = in_myudg;
		m_d3d = m_myudg->GetD3dDevPtr();
	}
	void InitAndCreate( CMglGraphicManager* in_myudg, HFONT hFont );
	void InitAndCreate( CMglGraphicManager* in_myudg, int nHeight );
	void InitAndEzCreate( CMglGraphicManager* in_myudg, int nHeight ){ InitAndCreate(in_myudg, nHeight); }	//	�Â�

	//	in_myudg�ȗ��`�B�֐�������Ă����e����
	void Create( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	void Create( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }
	//void Init( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	//void Init( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }
	void Setup( HFONT hFont ){ InitAndCreate( GetDefaultGd(), hFont ); }
	void Setup( int nHeight ){ InitAndCreate( GetDefaultGd(), nHeight ); }

	//	��t�w��
	void Create( CMglGraphicManager* in_myudg, int nHeight, const char* szFontName,
		BOOL bItalic=FALSE, BOOL bBold=FALSE, BOOL bUnderLine=FALSE, BOOL bStrikeOut=FALSE, float fAngle=0.0f );
	void Create( int nHeight, const char* szFontName,
		BOOL bItalic=FALSE, BOOL bBold=FALSE, BOOL bUnderLine=FALSE, BOOL bStrikeOut=FALSE, float fAngle=0.0f )
	{	Create( GetDefaultGd(), nHeight, szFontName, bItalic, bBold, bUnderLine, bStrikeOut, fAngle); }

	//	�S�����ȗ�
	//void Create(){ Init(MGL_TEXT_DEFAULT_FONT_SIZE); }
	//void Init(){ Init(MGL_TEXT_DEFAULT_FONT_SIZE); }

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

#else

#include "MglImage.h"

DLL_TMPL_EXP CMglDgIBase<ID3DXFont>;

//	�N���X�錾 - Direct9
class DLL_EXP CMglText : public CMglDgIBase<ID3DXFont> //: public CMglDgBase
{
protected:
	//	�C���^�[�t�F�[�X
	//ID3DXFont *m_text;

	//	�t�H���g�ݒ�
	BOOL bSetParamFlg;
	int m_nX;
	int m_nY;
	DWORD m_dwOption;
	D3DCOLOR m_color;

	std::string m_str;
	CMglImage m_workImg;
	::RECT m_rect;

	void SetParamCheck() {
		if ( bSetParamFlg != TRUE )
			MyuThrow( 0, "CMglText::Draw(),fDraw()  SetDrawParam()���ݒ肳��Ă��Ȃ��̂Ɉ������ȗ����܂����B" );
	}
	void _Init(){
		//m_text = NULL;
		m_nX = 0;
		m_nY = 0;
		m_dwOption = 0;
		m_color = 0;
		ZeroMemory(&m_rect, sizeof(m_rect));
	}

public:
	CMglText();
	virtual ~CMglText();

	//	�쐬
	void Create( int nHeight=MGL_TEXT_DEFAULT_FONT_SIZE, const char* szFontName=NULL,
		BOOL bItalic=FALSE, BOOL bBold=FALSE );

	//	�J��
	//void Release();

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

	void SetRect( ::RECT *pRect ){ m_rect = *pRect; }
	::RECT GetRect(){ return m_rect; }

//	std::vector<std::string> EnumFontNames();

	virtual int MsgNoBase(){ return MGLMSGNO_TEXT(0); }
	virtual const char* ClassName(){ return "CMglText"; }
};

#endif

typedef CMglText CMglGraphicText;

#endif//__MglText_H__
