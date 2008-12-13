#include  "stdafx.h"
#include  <DShow.h>

void  main()
{
	// DirectShow�̃C���X�^���X�錾
	IGraphBuilder *p_graph=NULL;
	IMediaControl *p_control=NULL;
	IMediaEvent   *p_event=NULL;

	HRESULT hr;   // ��������

	long event_code;   // �C�x���g�R�[�h

	// COM���C�u�����̏�����
	hr=CoInitialize(NULL);

	// �t�B���^�O���t�̃C���X�^���X�𐶐�
	hr=CoCreateInstance(
			CLSID_FilterGraph,	  // �t�B���^�O���t�̃N���XID
			NULL,				// ��A�O���Q�[�g�I�u�W�F�N�g
			CLSCTX_INPROC_SERVER,   // �Ăяo�����Ɠ����v���Z�X�Ŏ��s
			IID_IGraphBuilder,	  // �O���t�r���_�ŃI�u�W�F�N�g�ԒʐM����
			(void **)&p_graph);	 // �C���X�^���X������|�C���^

	// �t�B���^�O���t����IMediaControl���擾����
	hr=p_graph->QueryInterface(
			IID_IMediaControl,	  //IMediaControl�̃C���^�[�t�F�[�X�w��
			(void **)&p_control);   //IMediaControl������|�C���^

	// �t�B���^�O���t����IMediaEvent���擾����
	hr=p_graph->QueryInterface(
			IID_IMediaEvent,		//IMediaEvent�̃C���^�[�t�F�[�X�w��
			(void **)&p_event);	 //IMediaEvent������|�C���^

	// �Đ�����t�@�C�����w�肷��
	hr=p_graph->RenderFile(
			L"C:\\workdir\\testh.mp3",  // ���f�B�A�t�@�C����
			NULL);								// �\��(NULL�Œ�)

	// �t�@�C���̃����_�����O�ɐ���������O���t�����s����
	if(SUCCEEDED(hr))
	{
	  // �O���t�����s����
	  hr=p_control->Run();

	 if( hr == S_OK )
	  {
		// �O���t�̎��s�ɐ��������犮������܂ŃC�x���g��҂�
		p_event->WaitForCompletion(
			INFINITE,				 // �C�x���g�^�C�}�[(������)
			&event_code);			 // �C�x���g���ʃR�[�h
	  }
	}

	// IMediaControl���J������
	p_control->Release();

	// IMediaEvent���J������
	p_event->Release();

	// �t�B���^�O���t���J������
	p_graph->Release();

	// COM���C�u�������J������
	CoUninitialize();
}
