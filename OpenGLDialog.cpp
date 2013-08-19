
#include "stdafx.h"
#include "OpenGLDialog.h"
#include "OpenGLDialogDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(COpenGLDialogApp, CWinApp)
	//{{AFX_MSG_MAP(COpenGLDialogApp)
	
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

COpenGLDialogApp::COpenGLDialogApp()
{

}

/////////////////////////////////////////////////////////////////////////////

COpenGLDialogApp theApp;

BOOL COpenGLDialogApp::InitInstance()
{

#ifdef _AFXDLL
	Enable3dControls();			
#else
	Enable3dControlsStatic();	
#endif

	COpenGLDialogDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	
	return FALSE;
}
