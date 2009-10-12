#include "mglaugust2.h"


//	アイテムクラス
class CFileItem : public CAugustText2
{
public:
	CFileItem(){}
	
_AGH_EVENT_ACCESS_MODIFIER:
	virtual void OnRegist()
	{
		SetText("dsfd");
	}
};


//	アレイクラス
class CFileItemArray : public agh::CControlList<CFileItem>
{
private:
	typedef agh::CControlList<CFileItem> _BASE;
protected:
public:
	void Add(){
		CFileItem *pAddedItem = &(_BASE::Add( CFileItem() ));

		pAddedItem->SetPos(8, m_ctrlAry.size()*17);
	}

_AGH_EVENT_ACCESS_MODIFIER:
};


//	メインクラス
//class CMyWindow : public CMwlAghWindow
class CMyWindow : public CAugustScreen2//, public agh::_CKeyboardBase_CDummyBase
{
private:
	CFileItemArray m_itemAry;

public:
	//	コンストラクタ・デストラクタ
	CMyWindow(){}
	virtual ~CMyWindow(){}
	
	virtual bool OnGraphicInitEnded()
	{
		RegistSubControl(&m_itemAry);

		//CAugustText2 m_text3 = m_text2;

		//m_textAry.Add().SetText("ZZZZZZZZZZZZZZZZ");
		//m_textAry.Add().SetText("YYYYYYYYYYYYYY");
		m_itemAry.Add();
		m_itemAry.Add();

		return true;
	}
};


int _MWL_APIENTRY WinMain(
					_MWL_HINSTANCE hInstance,
                    _MWL_HINSTANCE hPrevInstance,
                    char*     lpCmdLine,
                    int       nCmdShow )
{

	CMyWindow myWindow;
	myWindow.Start();

	return 0;
}
