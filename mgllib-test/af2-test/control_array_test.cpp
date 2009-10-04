#include "mglaugust2.h"



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

class CFileItemArray1 : public agh::CVisualControlBase
{
protected:
	std::vector<CFileItem> m_items;
public:
	void Add(){
		m_items.push_back( CFileItem() );

		CFileItem *pAddedItem = m_items.rbegin().operator ->();
		RegistControl(pAddedItem);

		pAddedItem->SetPos(7, m_items.size()*17);
	}
};




//class CMyWindow : public CMwlAghWindow
class CMyWindow : public CAugustScreen2//, public agh::_CKeyboardBase_CDummyBase
{
private:
	agh::CControlVector<CAugustText2> m_textAry;
	CFileItemArray1 m_textAry1;
	CFileItemArray m_itemAry;

	//std::vector::iterator it;

public:
	//	コンストラクタ・デストラクタ
	CMyWindow(){}
	virtual ~CMyWindow(){}
	
	virtual bool OnGraphicInitEnded()
	{
		RegistSubControl(&m_textAry);
		RegistSubControl(&m_textAry1);
		RegistSubControl(&m_itemAry);

		CAugustText2 m_text3 = m_text2;

		//m_textAry.Add().SetText("ZZZZZZZZZZZZZZZZ");
		//m_textAry.Add().SetText("YYYYYYYYYYYYYY");
		m_textAry1.Add();
		m_textAry1.Add();
		//m_itemAry.Add();
		//m_itemAry.Add();

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
