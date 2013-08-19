
#include "stdafx.h"
#include "OpenGLDialog.h"
#include "OpenGLDialogDlg.h"
#include "AboutDlg.h"
#include "OpenGLControl.h"
#include <fstream>
#include ".\opengldialogdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

COpenGLDialogDlg::COpenGLDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COpenGLDialogDlg::IDD, pParent)
		
	, m_Toggle(false)
	, m_PreviewToggle(false)
	, RotationCoordinate(0)
	, roStep(0)
	, ZoomZoom(100)
	, isConnect(false)
{
	//{{AFX_DATA_INIT(COpenGLDialogDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenGLDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COpenGLDialogDlg)

	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_btnConnect, m_Connect);
	DDX_Control(pDX, IDC_btnDisConnect, m_DisConnect);
	DDX_Control(pDX, IDC_EDIT1, m_ResultWin);
	DDX_Control(pDX, IDC_EDIT2, m_Cap);
	DDX_Control(pDX, IDC_slRed, m_Red);
	DDX_Control(pDX, IDC_slGreen, m_Green);
	DDX_Control(pDX, IDC_slBlue, m_Blue);
	DDX_Control(pDX, IDC_slZoom, m_Zoom);
	DDX_Control(pDX, IDC_slTopDown, m_UpDown);
	DDX_Control(pDX, IDC_SlLeftRight, m_LeftRight);
	DDX_Control(pDX, IDC_SlRotate, m_Rotate);
	DDX_Control(pDX, IDC_CHECK1, m_Freez);
	DDX_Control(pDX, IDC_CHECK2, m_Preview);
	DDX_Control(pDX, IDC_CHECK2, m_Preview);
	DDX_Control(pDX, IDC_slDcOffset, m_DC);
	DDX_Control(pDX, IDC_slStep, m_Step);
	DDX_Control(pDX, IDC_slnSeesaw, m_SeeSaw);
	DDX_Control(pDX, IDC_OPENGL_WINDOW, DrawingSurface);
	DDX_Control(pDX, IDC_EDIT3, m_TexBoxRotate);
	DDX_Control(pDX, IDC_SPIN2, m_SpRotat);
}

BEGIN_MESSAGE_MAP(COpenGLDialogDlg, CDialog)
	//{{AFX_MSG_MAP(COpenGLDialogDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnAboutClick)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_btnConnect, OnBnClickedbtnconnect)
	ON_BN_CLICKED(IDC_btnDisConnect, OnBnClickedbtndisconnect)
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_slZoom, OnNMCustomdrawslzoom)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_slTopDown, OnNMCustomdrawsltopdown)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SlLeftRight, OnNMCustomdrawSlleftright)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SlRotate, OnNMCustomdrawSlrotate)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_slRed, OnNMCustomdrawslred)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_slGreen, OnNMCustomdrawslgreen)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_slBlue, OnNMCustomdrawslblue)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_RADIO6, OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_btnConnectofVideo, OnBnClickedbtnconnectofvideo)
	ON_BN_CLICKED(IDC_RADIO3, OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnBnClickedRadio5)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_slDcOffset, OnNMCustomdrawsldcoffset)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_slStep, OnNMCustomdrawslstep)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_slnSeesaw, OnNMCustomdrawslnseesaw)
	ON_BN_CLICKED(IDC_btnSaveVertex, OnBnClickedbtnsavevertex)

	ON_BN_CLICKED(IDC_RADIO9, OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO8, OnBnClickedRadio8)

	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, OnDeltaposSpin2)
//	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
ON_BN_CLICKED(IDC_btnSavePicture, OnBnClickedbtnsavepicture)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

BOOL COpenGLDialogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	CRect rect;
	GetDlgItem(IDC_OPENGL_WINDOW)->GetWindowRect(rect);
	ScreenToClient(rect);
	
	InitialSetUp();
	openGLControl.Create(rect,this);
	return TRUE; 
}

void COpenGLDialogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR COpenGLDialogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COpenGLDialogDlg::OnAboutClick() 
{
	CAboutDlg aboutBox;

	aboutBox.DoModal();
}

void COpenGLDialogDlg::InitialSetUp()
{
	m_Red.SetRange(0, 255, TRUE );
	m_Red.SetPos((int)(128.0f));
	m_Red.SetTicFreq(1);
	m_Red.SetPageSize(5);

	m_Green.SetRange(0, 255, TRUE );
	m_Green.SetPos((int)(128.0f));
	m_Green.SetTicFreq(1);
	m_Green.SetPageSize(5);

	m_Blue.SetRange(0, 255, TRUE );
	m_Blue.SetPos((int)(128.0f));
	m_Blue.SetTicFreq(1);
	m_Blue.SetPageSize(5);
	
	m_Zoom.SetRange(1, 5000, TRUE );
	m_Zoom.SetPos((int)(100.0f));
	m_Zoom.SetTicFreq(1);
	m_Zoom.SetPageSize(100);
	
	m_UpDown.SetRange(1, 10000, TRUE );
	m_UpDown.SetPos((int)(5000.0f));
	m_UpDown.SetTicFreq(1);
	m_UpDown.SetPageSize(100);
	
	
	m_LeftRight.SetRange(0, 10000, TRUE );
	m_LeftRight.SetPos((int)(5000.0f));
	m_LeftRight.SetTicFreq(1);
	m_LeftRight.SetPageSize(100);

	m_Rotate.SetRange(0, 360, TRUE );
	m_Rotate.SetPos((int)(45.0f));
	m_Rotate.SetTicFreq(1);
	m_Rotate.SetPageSize(30);

	m_DC.SetRange(1, 20, TRUE );
	m_DC.SetPos((int)(10.0f));
	m_DC.SetTicFreq(1);
	m_DC.SetPageSize(5);
	
	m_Step.SetRange(1, 10, TRUE );
	m_Step.SetPos((int)(1.0f));
	m_Step.SetTicFreq(1);
	m_Step.SetPageSize(2);
	
	m_SeeSaw.SetRange(1, 15000, TRUE );
	m_SeeSaw.SetPos((int)(500.0f));
	m_SeeSaw.SetTicFreq(1);
	m_SeeSaw.SetPageSize(100);
	
	m_Red.SetPos(255);
	m_Green.SetPos(127);
	m_Blue.SetPos(0);
	m_Rotate.SetPos(190);
	
	openGLControl.n_SetPanTilt(m_LeftRight.GetPos(),m_UpDown.GetPos()) ;
	openGLControl.n_SetColor((BYTE)(m_Red.GetPos()),(BYTE)(m_Green.GetPos()),(BYTE)(m_Blue.GetPos()));
	
	openGLControl.n_SetSeesaw(m_SeeSaw.GetPos()); 

	openGLControl.n_SetDcOffset(10);
	openGLControl.n_SetStepInRender(1); 
    
	openGLControl.n_SetZoom(100.0f);  
	openGLControl.n_SetRenderMode(0); 
	openGLControl.n_SetRotation(190.0f); 
	RotationCoordinate=45;
	
	
	openGLControl.n_SetRandomBright(0); 
	
	CheckDlgButton(IDC_RADIO1, BST_CHECKED);   
	CheckDlgButton(IDC_RADIO2, BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO7, BST_UNCHECKED);   
	CheckDlgButton(IDC_RADIO6, BST_UNCHECKED);
	
	CheckDlgButton(IDC_RADIO3, BST_CHECKED);   
	CheckDlgButton(IDC_RADIO4, BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO5, BST_UNCHECKED);
	
	CheckDlgButton(IDC_RADIO9, BST_CHECKED);   
	CheckDlgButton(IDC_RADIO8, BST_UNCHECKED);
	
	openGLControl.n_Freez(FALSE); 
	roStep=3;
	m_SpRotat.SetRange32(0,20); 
	m_SpRotat.SetPos32(roStep);
	m_TexBoxRotate.SetWindowText("3");
	ZoomZoom=100;

}

void COpenGLDialogDlg::OnNMCustomdrawslzoom(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		openGLControl.n_SetZoom((float)(m_Zoom.GetPos())); 
		ZoomZoom=m_Zoom.GetPos();
	*pResult = 0;
}

void COpenGLDialogDlg::OnNMCustomdrawsltopdown(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	
	openGLControl.n_SetPanTilt(m_LeftRight.GetPos(),m_UpDown.GetPos());
	*pResult = 0;
}

void COpenGLDialogDlg::OnNMCustomdrawSlleftright(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		openGLControl.n_SetPanTilt(m_LeftRight.GetPos(),m_UpDown.GetPos());
	*pResult = 0;
}

void COpenGLDialogDlg::OnNMCustomdrawSlrotate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
		openGLControl.n_SetRotation((float)(m_Rotate.GetPos()));  
		RotationCoordinate=m_Rotate.GetPos();
	*pResult = 0;
}

void COpenGLDialogDlg::OnNMCustomdrawslred(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
openGLControl.n_SetColor((BYTE)(m_Red.GetPos()),(BYTE)(m_Green.GetPos()),(BYTE)(m_Blue.GetPos()));
	*pResult = 0;
}

void COpenGLDialogDlg::OnNMCustomdrawslgreen(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
openGLControl.n_SetColor((BYTE)(m_Red.GetPos()),(BYTE)(m_Green.GetPos()),(BYTE)(m_Blue.GetPos()));
	*pResult = 0;
}

void COpenGLDialogDlg::OnNMCustomdrawslblue(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	openGLControl.n_SetColor((BYTE)(m_Red.GetPos()),(BYTE)(m_Green.GetPos()),(BYTE)(m_Blue.GetPos()));	*pResult = 0;
}

void COpenGLDialogDlg::OnBnClickedCheck1()
{
	if(m_Toggle==TRUE)
	{	
		m_Freez.SetWindowText("Freeze"); 
		m_Toggle=FALSE;
		openGLControl.n_Freez(FALSE); 
	}
	else
	{	
		m_Freez.SetWindowText("UnFreeze");
		m_Toggle=TRUE;
		openGLControl.n_Freez(TRUE); 
	}

}

void COpenGLDialogDlg::OnBnClickedCheck2()
{
	if(m_PreviewToggle==TRUE)
	{	
		m_Preview.SetWindowText("Preview"); 
		m_PreviewToggle=FALSE;
		openGLControl.n_CapPreviewOnOff(FALSE); 
	}
	else
	{	
		m_Preview.SetWindowText("Preview Off");
		m_PreviewToggle=TRUE;
		openGLControl.n_CapPreviewOnOff(TRUE); 
	}
}

void COpenGLDialogDlg::OnNMCustomdrawsldcoffset(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	openGLControl.n_SetDcOffset(m_DC.GetPos()); 
	*pResult = 0;
}

void COpenGLDialogDlg::OnNMCustomdrawslstep(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	openGLControl.n_SetStepInRender(m_Step.GetPos());  
	*pResult = 0;
}
void COpenGLDialogDlg::OnBnClickedChecktimer()
{

}
void COpenGLDialogDlg::OnNMCustomdrawslnseesaw(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	openGLControl.n_SetSeesaw(m_SeeSaw.GetPos());  
	*pResult = 0;
}

void COpenGLDialogDlg::OnBnClickedbtnconnect()
{
	openGLControl.n_CapConnectDisConnect(TRUE,m_Cap.m_hWnd,TRUE);
	m_ResultWin.SetWindowText("Connected to capture device.");
}

void COpenGLDialogDlg::OnBnClickedbtnconnectofvideo()
{
	openGLControl.n_CapConnectDisConnect(TRUE,m_Cap.m_hWnd,FALSE);
	m_ResultWin.SetWindowText("Connected to capture device.");
	isConnect=TRUE;
}

void COpenGLDialogDlg::OnBnClickedbtndisconnect()
{
	openGLControl.n_CapConnectDisConnect(FALSE,m_Cap.m_hWnd,FALSE);
	m_ResultWin.SetWindowText("Disconnected to capture device.");
	isConnect=FALSE;
}

void COpenGLDialogDlg::OnBnClickedRadio1()
{
	openGLControl.n_SetRenderMode(0);
}

void COpenGLDialogDlg::OnBnClickedRadio2()
{
	openGLControl.n_SetRenderMode(1); 
}

void COpenGLDialogDlg::OnBnClickedRadio6()
{
	openGLControl.n_SetRenderMode(2); 
}

void COpenGLDialogDlg::OnBnClickedRadio7()
{
	openGLControl.n_SetRenderMode(3); 
}

void COpenGLDialogDlg::OnBnClickedRadio9()
{
	m_Red.SetRange(0, 255, TRUE );
	m_Green.SetRange(0, 255, TRUE );
	m_Blue.SetRange(0, 255, TRUE );
	openGLControl.n_SetRandomBright(0); 
	CheckDlgButton(IDC_RADIO3, BST_CHECKED);   
	CheckDlgButton(IDC_RADIO4,  BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO5, BST_UNCHECKED);
}

void COpenGLDialogDlg::OnBnClickedRadio8()
{
	if (isConnect==TRUE)
		{
			m_Red.SetRange(0, 127, TRUE );
			m_Green.SetRange(0, 127, TRUE );
			m_Blue.SetRange(0, 127, TRUE );
			openGLControl.n_SetRandomBright(1);
			CheckDlgButton(IDC_RADIO3, BST_UNCHECKED);   
			CheckDlgButton(IDC_RADIO4, BST_CHECKED);
			CheckDlgButton(IDC_RADIO5, BST_UNCHECKED);
		}
		else
		{
			CheckDlgButton(IDC_RADIO9, BST_CHECKED);   
			CheckDlgButton(IDC_RADIO8, BST_UNCHECKED);
			MessageBeep(-1);
			m_ResultWin.SetWindowText("Please first connect to video source"); 
		}
}

void COpenGLDialogDlg::OnBnClickedRadio3()
{
	openGLControl.n_SetRandomBright(0); 
}

void COpenGLDialogDlg::OnBnClickedRadio4()
{
	if (isConnect==TRUE)
		{
			openGLControl.n_SetRandomBright(1); 
		}
	else
			m_ResultWin.SetWindowText("Please first connect to video source");
	
}

void COpenGLDialogDlg::OnBnClickedRadio5()
{
	if (isConnect==TRUE)
		{
			openGLControl.n_SetRandomBright(2);
		}
	else
			m_ResultWin.SetWindowText("Please first connect to video source");
}

BOOL  COpenGLDialogDlg::PreTranslateMessage(MSG* pMsg)
	{

	
		if(pMsg->message==WM_KEYDOWN)
			{
			switch (pMsg->wParam)
				{
					case VK_LEFT :
						if (RotationCoordinate <= 0)
								RotationCoordinate=360;	
							RotationCoordinate-=roStep;
							openGLControl.n_SetRotation(RotationCoordinate);  
							m_Rotate.SetPos(RotationCoordinate);
							pMsg->message=NULL;									
						break;
					case VK_RIGHT :
						if (RotationCoordinate >= 360)
								RotationCoordinate=0;	
							RotationCoordinate+=roStep;
							openGLControl.n_SetRotation(RotationCoordinate);  
							m_Rotate.SetPos(RotationCoordinate);
							pMsg->message=NULL;		
						break;
					case VK_HOME :
							openGLControl.n_SetRotation(45);  
							m_Rotate.SetPos(45);
							RotationCoordinate=45;
							pMsg->message=NULL;								
						break;
					case VK_OEM_MINUS :
						ZoomZoom-=50;
						if (ZoomZoom<0)
						{
							ZoomZoom=0;
							MessageBeep(-1);
						}
						openGLControl.n_SetZoom((float)(ZoomZoom));
						m_Zoom.SetPos(ZoomZoom);
						pMsg->message=NULL;								
						break;
					case VK_OEM_PLUS :
						ZoomZoom+=50;
						if (ZoomZoom>5000)
						{
							ZoomZoom=5000;
							MessageBeep(-1);
						}
						openGLControl.n_SetZoom((float)(ZoomZoom));
						m_Zoom.SetPos(ZoomZoom);
						pMsg->message=NULL;								
						break;
					case VK_END :
						ZoomZoom=100;
						m_Zoom.SetPos(100);
						break;
				}
			}

			return CDialog::PreTranslateMessage(pMsg);
	}

void COpenGLDialogDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString T;
	roStep= m_SpRotat.GetPos32(); 
	T.Format("%d",m_SpRotat.GetPos32()); 
	m_TexBoxRotate.SetWindowText(T);
	*pResult = 0;
}

void COpenGLDialogDlg::OnBnClickedbtnsavepicture()
{
		CString OpenFilter;
		OpenFilter = "Vertex File (*.bmp)|*.bmp|";
		OpenFilter += "All Files (*.*)|*.*||";

		CFileDialog dlgSave(FALSE, NULL,"Noname", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter, NULL);

	if(dlgSave.DoModal() == IDOK)	
		{			
			openGLControl.n_ExportPic(dlgSave.GetFileName()+".bmp");
		}
}

void COpenGLDialogDlg::OnBnClickedbtnsavevertex()
{
	CString OpenFilter;
		OpenFilter = "Vertex File (*.vrt)|*.vrt|";
		OpenFilter += "All Files (*.*)|*.*||";

		CFileDialog dlgSave(FALSE, NULL,"Noname", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, OpenFilter, NULL);

	if(dlgSave.DoModal() == IDOK)	
		{			
			openGLControl.n_ExportVertex(dlgSave.GetFileName()+".vrt");
		}
}