#if !defined(AFX_MglguiMfcView_H__9E7218F1_6905_4A28_B836_5FB0A0186AB2__INCLUDED_)
#define AFX_MglguiMfcView_H__9E7218F1_6905_4A28_B836_5FB0A0186AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MglguiMfcView.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMglguiMfcView �r���[

class CMglguiMfcView : public CView, public CMglguiScreen
{
protected:
	CMglguiMfcView();           // ���I�����Ɏg�p�����v���e�N�g �R���X�g���N�^
	DECLARE_DYNCREATE(CMglguiMfcView)

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CMglguiMfcView)
	protected:
	virtual void OnDraw(CDC* pDC);      // ���̃r���[��`�悷�邽�߂ɃI�[�o�[���C�h���܂����B
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	virtual ~CMglguiMfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CMglguiMfcView)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
/*private:
	static const AFX_MSGMAP_ENTRY _messageEntries[];
protected:
	static AFX_DATA const AFX_MSGMAP messageMap;
	static const AFX_MSGMAP* PASCAL _GetBaseMessageMap();
	virtual const AFX_MSGMAP* GetMessageMap() const;
*/
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MglguiMfcView_H__9E7218F1_6905_4A28_B836_5FB0A0186AB2__INCLUDED_)
