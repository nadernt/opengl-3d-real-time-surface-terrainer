//{{AFX_INCLUDES()
//}}AFX_INCLUDES

#if !defined(AFX_OPENGLDIALOGDLG_H__920A32A4_A76B_48E8_AE75_0942A4B378C2__INCLUDED_)
#define AFX_OPENGLDIALOGDLG_H__920A32A4_A76B_48E8_AE75_0942A4B378C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenGLControl.h"
#include "afxwin.h"
#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////

class COpenGLDialogDlg : public CDialog
{

public:
	COpenGLDialogDlg(CWnd* pParent = NULL);	
	void InitialSetUp();

	//{{AFX_DATA(COpenGLDialogDlg)
	enum { IDD = IDD_OPENGLDIALOG_DIALOG };

	//}}AFX_DATA

	//{{AFX_VIRTUAL(COpenGLDialogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;
	COpenGLControl openGLControl;
	
	//{{AFX_MSG(COpenGLDialogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAboutClick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtnconnect();
	afx_msg void OnBnClickedbtndisconnect();

	CButton m_Connect;
	CButton m_DisConnect;
	CEdit m_ResultWin;
	CEdit m_Cap;
	CSliderCtrl m_Red;
	CSliderCtrl m_Green;
	CSliderCtrl m_Blue;
	CSliderCtrl m_Zoom;
	CSliderCtrl m_UpDown;
	CSliderCtrl m_LeftRight;
	CSliderCtrl m_Rotate;
	
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnNMCustomdrawslzoom(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawsltopdown(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlleftright(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSlrotate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawslred(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawslgreen(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawslblue(NMHDR *pNMHDR, LRESULT *pResult);
	bool m_Toggle;
	afx_msg void OnBnClickedCheck1();
	CButton m_Freez;
	CButton m_Previwe;
	bool m_PreviewToggle;
	afx_msg void OnBnClickedCheck2();
	CButton m_Preview;
	afx_msg void OnBnClickedbtnconnectofvideo();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	CSliderCtrl m_DC;
	CSliderCtrl m_Step;
	afx_msg void OnNMCustomdrawsldcoffset(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawslstep(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadio5();
	int rRotation;
	bool m_play;
	afx_msg void OnBnClickedChecktimer();
	afx_msg void OnNMCustomdrawslnseesaw(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_SeeSaw;

public:
	
	afx_msg void OnBnClickedbtnsavevertex();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedbtnsavepicture();
	afx_msg void OnBnClickedRadio9();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);

	CStatic DrawingSurface;
private:
	BOOL  PreTranslateMessage(MSG* pMsg);
	float RotationCoordinate;

public:
	float roStep;
	CSpinButtonCtrl m_Rotat;
	CEdit m_TexBoxRotate;
		CSpinButtonCtrl m_SpRotat;
	int ZoomZoom;
	bool isConnect;
};

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_OPENGLDIALOGDLG_H__920A32A4_A76B_48E8_AE75_0942A4B378C2__INCLUDED_)
