#if !defined(AFX_MglguiMfcView_H__9E7218F1_6905_4A28_B836_5FB0A0186AB2__INCLUDED_)
#define AFX_MglguiMfcView_H__9E7218F1_6905_4A28_B836_5FB0A0186AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MglguiMfcView.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CMglguiMfcView ビュー

class CMglguiMfcView : public CView, public CMglguiScreen
{
protected:
	CMglguiMfcView();           // 動的生成に使用されるプロテクト コンストラクタ
	DECLARE_DYNCREATE(CMglguiMfcView)

// アトリビュート
public:

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CMglguiMfcView)
	protected:
	virtual void OnDraw(CDC* pDC);      // このビューを描画するためにオーバーライドしました。
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	virtual ~CMglguiMfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CMglguiMfcView)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
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
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_MglguiMfcView_H__9E7218F1_6905_4A28_B836_5FB0A0186AB2__INCLUDED_)
