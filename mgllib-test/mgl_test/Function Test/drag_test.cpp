#include "stdafx.h"
#include "AugustImage1.h"

LPD3DXFONT pFont;	//�t�H���g

HRESULT InitFont(IDirect3DDevice9* pDevice)
{
    //������t�H���g�̐ݒ�
    if(FAILED(D3DXCreateFont(pDevice,
        14,                     //��������
        7,                      //������
        FW_BOLD,                //�t�H���g�X�^�C��
        NULL,                   //�~�b�v�}�b�v���f���̐�
        FALSE,                  //�Α̂ɂ��邩�ǂ���
        SHIFTJIS_CHARSET,       //�����Z�b�g
        OUT_DEFAULT_PRECIS,
        PROOF_QUALITY,
        FIXED_PITCH | FF_MODERN,
        "tahoma",               //�t�H���g�̎��
        &pFont)))
    {
        return E_FAIL;
    }
    return TRUE;
}

//�����񃌃��_�����O�֐�
VOID RenderString(LPSTR szStr,    //�\�����镶����
            INT iX,         //�\��X���W
            INT iY)         //�\��Y���W
{
    RECT rect = {iX, iY, 0, 0}; //�\���̈�
    //RECT rect = {iX, iY, 200, 200}; //�\���̈�

    //������T�C�Y���v�Z
    pFont->DrawText(
        NULL,
        szStr,
        -1,             //�\���T�C�Y(-1�őS��)
        &rect,          //�\���͈�
        DT_CALCRECT,    //�\���͈͂ɒ���
        NULL);

    //���̃T�C�Y�Ń����_�����O
    pFont->DrawText(
        NULL,
        szStr,
        -1,                     //�\���T�C�Y(-1�őS��)
        &rect,                  //�\���͈�
        DT_LEFT | DT_BOTTOM,    //���l�߂ŗ��[����
        0xff00ff00);            //�F
}

//////////////////////////////////////////

//	���C���t���[���N���X
class CTestScreem : public CAugustScreen
{
private:
	CAugustImage m_img;
	CAugustText m_text;
	float m_f;

public:
	void OnInit(){
		RegistControl(&m_img);
		RegistControl(&m_text);

		m_img.Load("test.jpg");
		//m_img.Load("pilot.dds");
		m_img.SetAngle(45);
		m_img.SetScale(0.8f);
		//m_img.SetSrcRect(10,10,200,200);
		m_img.Move(150,150);

		m_text.SetText("hogeaa��������aaaaa\nddd����111llk");
		m_text.SetFontSize(320);
		//m_text.SetFontName("MS PGothic");
		m_text.SetFontName(MGL_FONT_NAME_TAHOMA);
		m_text.SetColor(0x99000022);

		m_img.EnableCentering();
		m_img.EnableDrag();
		m_text.EnableDrag();

		InitFont(CAugustScreen::g_->grp.GetD3dDevPtr());

		m_f = 0.0f;
	}

/*	void OnDraw(){
		m_text.Draw();
		//RenderString("hoge",0,0);
	}*/

	bool OnFrameDoUser(){
		//m_img.SetAngle(80);
		m_f += 0.005f;
		m_img.SetScale(m_f);
		m_img.SetAngle(m_f*200);

		return true;
	}
};

class CTestFrame : public CAugustWindow
{
private:
	CTestScreem m_screen;
public:
	void OnInit(){
		this->SetActiveScreen(&m_screen);
		this->EnableEscEnd();
	}

	bool OnFrame(){
		return true;
	}
};
CTestFrame g_frame;

//	WinMain
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	g_frame.Start();
	return 0;
}
