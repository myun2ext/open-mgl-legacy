//////////////////////////////////////////////////////////
//
//	MyuEzWindow  v0.21.00 05/02/21
//		- Window�������ȒP�ɍs���N���X
//
//	v0.10.00 04/11/07
//	�E�V�K�쐬
//
//	v0.10.10 04/12/14
//	�EdwWinStyle��dwExtendWinStyle�ɁB
//	�@Window�X�^�C���̓f�t�H���g�� WS_CAPTION | WS_SYSMENU
//	�@��t������悤�ɏC���B
//
//	v0.10.50 04/12/22
//	�E�X���b�h�𐳂����I��������悤�ɏC��
//
//	v0.20.00 05/02/21
//	�E�N���X��
//
//	v0.20.01 05/02/21
//	�EActive��Alive�ɁB�����J�R���N�l�H�i��
//
//	v0.20.02 05/02/21
//	�E���b�Z�[�W�ԈႦ�Ă�񂾂��ǁB_|�P|��
//
//	v0.21.00 05/02/21
//	�ECMyuEasyWin����CMyuEzWindow�ɖ��̕ύX
//
//////////////////////////////////////////////////////////

#ifndef __MyuEzWindow_H__
#define __MyuEzWindow_H__

//	�X���b�h�I���҂��̃f�t�H���g�̃^�C���A�E�g
//#define DEFAULT_THREAD_EXIT_TIMEOUT	(3000)
#define DEFAULT_THREAD_EXIT_TIMEOUT		(10000)

//	�N���X�錾
class DLL_EXP CMyuEzWindow
{
private:
	int m_nThreadExitTimeout;
	/*volatile */
	BOOL m_bAlive;
	HWND m_hWnd;

public:
	CMyuEzWindow();
	virtual ~CMyuEzWindow();

	int StartWindow( const char* szAppCaption, const char* szWinClassName,
					 int nWinXPos, int nWinYPos, int nWinWidthSize, int nWinHeightSize,
					 DWORD dwExtendWinStyle, LPTHREAD_START_ROUTINE threadFunc,
					 LPVOID threadFuncParam=NULL );
//					 DWORD dwThreadUserOption=0 );

	void SetThreadExitTimeout( int nTimeMs ) { m_nThreadExitTimeout = nTimeMs; }
	BOOL IsAlive() { return m_bAlive; }

	HWND GetWindowHandle() {
		if ( m_bAlive != TRUE )
			MyuThrow( MGLEC_WINDOW_NOT_ALIVE, "CMyuEzWindow::GetWindowHandle()  �E�C���h�E�͐�����Ԃɂ���܂���B" );
		return m_hWnd;
	}
};

#endif//__MyuEzWindow_H__
