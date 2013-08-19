#if !defined(AFX_ABOUTDLG_H__7FDD28B9_753A_4E89_A309_36EBE69A0EE0__INCLUDED_)
#define AFX_ABOUTDLG_H__7FDD28B9_753A_4E89_A309_36EBE69A0EE0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////

class CAboutDlg : public CDialog
{

public:
	CAboutDlg(CWnd* pParent = NULL);   // Standardkonstruktor


	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTDLG_DIALOG };
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV
	//}}AFX_VIRTUAL

protected:

	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif // AFX_ABOUTDLG_H__7FDD28B9_753A_4E89_A309_36EBE69A0EE0__INCLUDED_
