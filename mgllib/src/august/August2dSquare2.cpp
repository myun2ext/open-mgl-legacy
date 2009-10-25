//////////////////////////////////////////////////////////
//
//	August2dSquare2
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "August2dSquare2.h"
#include "MglImage.h"

const char* CAugust2dSquare2::CLASS_NAME = "sf/jp/open-mgl/CAugust2dSquare2";

using namespace agh;

#define _P m_pBaseControl

//	コンストラクタ
CAugust2dSquare2::CAugust2dSquare2()
: _BASE(CLASS_NAME)
{
	m_pMglImg = new CMglImage();
}

//	デストラクタ
CAugust2dSquare2::~CAugust2dSquare2()
{
	SAFE_DELETE( m_pMglImg );
}

//	コピーコンストラクタ
CAugust2dSquare2::CAugust2dSquare2(const CAugust2dSquare2 &from)
: _BASE(CLASS_NAME)
{
	//*this = from;

	m_pMglImg = new CMglImage();
}

////////////////////////////////////

//	登録時にInitを呼び出す
void CAugust2dSquare2::OnRegist()
{
	_BASE::OnRegist();

	m_pMglImg->Init(m_pMglGrp);
	m_pMglImg->Create(1,1,TRUE);
	m_pMglImg->Clear(D3DCOLOR_WHITE);
}

//	描画
void CAugust2dSquare2::OnDraw()
{
	agh::CRect absRect = GetAbsoluteRect();

	m_pMglImg->Draw( absRect.left, absRect.top, NULL, GetColor(), absRect.right - absRect.left, absRect.bottom - absRect.top );

	//m_pGrp->Paint((::RECT*)&(agh::CRect(GetRect())+5), bgColor);
}
