
// MFC+RS+OPENCV.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "MFC+RS+OPENCV.h"
#include "MFC+RS+OPENCVDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCRSOPENCVApp

BEGIN_MESSAGE_MAP(CMFCRSOPENCVApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMFCRSOPENCVApp 생성

CMFCRSOPENCVApp::CMFCRSOPENCVApp()
{
	// 다시 시작 관리자 지원
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CMFCRSOPENCVApp 개체입니다.

CMFCRSOPENCVApp theApp;


// CMFCRSOPENCVApp 초기화

BOOL CMFCRSOPENCVApp::InitInstance()
{
	CWinApp::InitInstance();


	AfxEnableControlContainer();
	CMFCRSOPENCVDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 애플리케이션이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}
	return FALSE;
}

