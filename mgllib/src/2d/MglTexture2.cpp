//////////////////////////////////////////////////////////
//
//	MglTexture2
//		- MglGraphicManager サーフェスクラス
//
//////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MglTexture2.h"

////////////////////////////////////////////////////////////////////

//	コンストラクタ
CMglTexture2::CMglTexture2()
{
	m_myudg = NULL;
	d3d = NULL;
}


//	初期化
void CMglTexture2::Init( CMglGraphicManager* in_myudg )
{
	m_myudg = in_myudg;
	d3d = m_myudg->GetD3dDevPtr();
}

//	開放
void CMglTexture2::Release()
{
}
