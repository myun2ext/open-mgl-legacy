// CMglguiMfcView.cpp : �C���v�������e�[�V���� �t�@�C��
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMglguiMfcView �`��

void CMglguiMfcView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���̈ʒu�ɕ`��p�̃R�[�h��ǉ����Ă�������
}

/////////////////////////////////////////////////////////////////////////////
// CMglguiMfcView �f�f

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
// CMglguiMfcView ���b�Z�[�W �n���h��

void CMglguiMfcView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
	CView::OnPrint(pDC, pInfo);
}
