#if !defined(AFX_OPENGLCONTROL_H__52A6B63B_01A2_449D_8691_1FF59EECAB71__INCLUDED_)
#define AFX_OPENGLCONTROL_H__52A6B63B_01A2_449D_8691_1FF59EECAB71__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OpenGLDevice.h"
//#include <GL\gl.h>
//#include <GL\glu.h>
#include <GL\glut.h>

/////////////////////////////////////////////////////////////////////////////

class COpenGLControl : public CWnd
{

public:
	COpenGLControl();


public:
	//{{AFX_VIRTUAL(COpenGLControl)
	public:
	//}}AFX_VIRTUAL

public:
	
	void Create(CRect rect,CWnd* parent);
	
	void n_SetRotation(GLfloat RotateArg);
	void n_SetZoom(GLfloat gZoom);
	void n_SetColor(GLfloat Red,GLfloat Green,GLfloat Blue);
	void n_SetPanTilt(GLfloat Tilt,GLfloat Pan);
	void n_SetRenderMode(int ModeofRender);
	void n_SetRandomBright(int nRandomBright);
	void n_SetStepInRender(int StepofRender);
	void n_SetDcOffset(int nOffset);
	void n_Freez(BOOL StartStop);
	void n_Scale(GLfloat ScaleX,GLfloat ScaleY);
	void n_CapConnectDisConnect(BOOL nVisible,HWND nhWnd,BOOL Preview);
	void n_CapPreviewOnOff(BOOL Preview);
	void n_SetSeesaw(int Seesaw);
	void n_ExportVertex(CString FileName);
	BOOL n_ExportPic(CString FileName);
	void n_GrabFrame();
	int n_GetRandomBright();
	
	virtual ~COpenGLControl();
private:
	bool IsSave;
	GLubyte rgbR;
	GLubyte rgbG;
	GLubyte rgbB;
	GLfloat nRotate;
	GLfloat nSeesaw;
	GLfloat nZoom;
	GLfloat nTilt;
	GLfloat nPan;
	GLfloat nScaleX;
	GLfloat nScaleY;
	BOOL nFreez;
	BYTE *lpBits;
	GLfloat bMatrix [320][1][240];
	int nRenderMode;
	int nRandomBrightness;
	int nStepInRender;
	int nOfssetOfBrightness;
	int ncx;
	int ncy;
	void SetOnPaint();

protected:
	void InitGL();
	void DrawGLScene();
	void initlights();
	CClientDC* dc;
	OpenGLDevice openGLDevice;
	float rotation;
	BYTE Red1,Green1,Blue1,MaxColor,MinColor,Color1;
	
	//{{AFX_MSG(COpenGLControl)
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}

#endif // AFX_OPENGLCONTROL_H__52A6B63B_01A2_449D_8691_1FF59EECAB71__INCLUDED_
