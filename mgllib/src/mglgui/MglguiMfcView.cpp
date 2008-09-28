// CMglguiMfcView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "MglguiMfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMglguiMfcView

IMPLEMENT_DYNCREATE(CMglguiMfcView, CView)

CMglguiMfcView::CMglguiMfcView()
{
}

CMglguiMfcView::~CMglguiMfcView()
{
}

/*
const AFX_MSGMAP* PASCAL theClass::_GetBaseMessageMap(){ return &baseClass::messageMap; }
const AFX_MSGMAP* theClass::GetMessageMap() const { return &theClass::messageMap; }

AFX_COMDAT AFX_DATADEF const AFX_MSGMAP theClass::messageMap = {
	&theClass::_GetBaseMessageMap, &theClass::_messageEntries[0]
};
AFX_COMDAT const AFX_MSGMAP_ENTRY theClass::_messageEntries[] = {

	//	Mapping
}
*/

BEGIN_MESSAGE_MAP(CMglguiMfcView, CView)
	//{{AFX_MSG_MAP(CMglguiMfcView)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMglguiMfcView 描画

void CMglguiMfcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: この位置に描画用のコードを追加してください
}

/////////////////////////////////////////////////////////////////////////////
// CMglguiMfcView 診断

#ifdef _DEBUG
void CMglguiMfcView::AssertValid() const
{
	CView::AssertValid();
}

void CMglguiMfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMglguiMfcView メッセージ ハンドラ

void CMglguiMfcView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	CView::OnPrint(pDC, pInfo);
}
