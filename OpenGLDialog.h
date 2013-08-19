

#if !defined(AFX_OPENGLDIALOG_H__77B6740A_D688_4CAA_AA2E_0AE536C07B5F__INCLUDED_)
#define AFX_OPENGLDIALOG_H__77B6740A_D688_4CAA_AA2E_0AE536C07B5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		

/////////////////////////////////////////////////////////////////////////////
//

class COpenGLDialogApp : public CWinApp
{
public:
	COpenGLDialogApp();

	//{{AFX_VIRTUAL(COpenGLDialogApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL


	//{{AFX_MSG(COpenGLDialogApp)

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // !defined(AFX_OPENGLDIALOG_H__77B6740A_D688_4CAA_AA2E_0AE536C07B5F__INCLUDED_)
