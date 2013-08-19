
#include "stdafx.h"
#include "OpenGLDialog.h"
#include "OpenGLControl.h"
#include "cDIB.h"

#include <windows.h>
#include <vfw.h>
#include <fstream>

HWND		Videohwnd;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#pragma comment ( lib, "vfw32.lib")
using namespace std;
/////////////////////////////////////////////////////////////////////////////

COpenGLControl::COpenGLControl()
{
	dc = NULL;
	rotation = 0.0f;
	nStepInRender=1;
}

COpenGLControl::~COpenGLControl()
{
	if (dc)
	{
		delete dc;
	}
}


BEGIN_MESSAGE_MAP(COpenGLControl, CWnd)
	//{{AFX_MSG_MAP(COpenGLControl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COpenGLControl::InitGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);							
	glDepthFunc(GL_LEQUAL);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	initlights();
}

void COpenGLControl::DrawGLScene()
{
	int Step= nStepInRender;
	int r=0;
	int Xloc,Zloc,size,MaxLenthX,MaxLenthZ,XStep,ZStep;
	bool IamEnter=false;
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	gluLookAt(0.0f,nSeesaw/1000.0f,0.0f,0.8,0.0f,0.0f,0.0f,1.0f,0.0f);
	glRotatef(nRotate,0.0f,1.0f,0.0f);
	
		
if (nFreez != TRUE)
{
	
 if (nRandomBrightness==0)
 {
		for (Zloc=0 ;Zloc<240;Zloc +=1)	
			for(Xloc=0 ;Xloc<320;Xloc +=1)
			{	
			  bMatrix [Xloc][0][Zloc] = (GLfloat) (rand() % 20);
			}
				
 }
   else
 {
	n_GrabFrame(); 
 }
	
  if ( ::OpenClipboard(0) && nRandomBrightness !=0) 
  {
    	HGLOBAL hglb = ::GetClipboardData(CF_BITMAP);
    if (hglb ) 
	{
	  IamEnter=true;
      CBitmap *bmp = CBitmap::FromHandle((HBITMAP)hglb);
      BITMAP b;
      bmp->GetBitmap(&b);
      size = (b.bmBitsPixel/8)*b.bmHeight*b.bmWidth;    
      lpBits = new BYTE[size];
      bmp->GetBitmapBits(size,lpBits);
      
			for(Zloc=0 ;Zloc<240;Zloc +=1)
			{
				for(Xloc=0 ;Xloc<320;Xloc +=1)
					{
							Red1 = lpBits[r+2];
							Green1 = lpBits[r+1];
							Blue1 = lpBits[r];
							MaxColor = Red1;

						if (Green1 > MaxColor) MaxColor = Green1;
						if (Blue1 > MaxColor) MaxColor = Blue1;
							MinColor = Red1;

						if (Green1 < MinColor) MinColor = Green1;
						if (Blue1 < MinColor) MinColor = Blue1;
							Color1 = (BYTE)((MaxColor + MinColor) / 2);

							bMatrix [Xloc][0][Zloc] = (GLfloat) (Color1/nOfssetOfBrightness) ;
								r+=4;
					}
			}
     
	}
    ::CloseClipboard();
  }	
}
		r=0;
		glScalef(nZoom,1.0f , nZoom);
		MaxLenthX=nTilt+320;
		MaxLenthZ=nPan+240;

	if (MaxLenthZ<=-1)
		MaxLenthZ+=Step;
	else
		MaxLenthZ-=Step;

	if (MaxLenthX<=-1)
		MaxLenthX-=Step;
	else
		MaxLenthX-=Step;

int tmpX=nTilt,tmpZ=nPan;

for (Zloc=0,ZStep=tmpZ;ZStep<MaxLenthZ;Zloc++,ZStep+=Step)	
{	
	if(nRenderMode==0)
		glBegin(GL_POINTS);
	else if(nRenderMode==1)
		glBegin(GL_LINES);
	else if(nRenderMode==2)
		glBegin(GL_LINE_STRIP);
	else
		glBegin(GL_QUADS);
	for(Xloc=0,XStep=tmpX ;XStep<MaxLenthX;Xloc++,XStep+=Step)
		{
			if (nRandomBrightness==0)
				glColor3ub(rgbR,rgbG,rgbB);
			if (nRandomBrightness ==1)	
				glColor3ub(bMatrix [Xloc][0][Zloc]+rgbR,bMatrix [Xloc][0][Zloc]+rgbG,bMatrix [Xloc][0][Zloc]+rgbB);
			else if (nRandomBrightness ==2)	
				glColor3ub(lpBits[r+2],lpBits[r+1],lpBits[r]);
		glVertex3f((GLfloat)XStep,bMatrix [Xloc][0][Zloc],(GLfloat)ZStep);
			if (nRandomBrightness ==1)	
				glColor3ub(bMatrix [Xloc+1][0][Zloc]+rgbR,bMatrix [Xloc+1][0][Zloc]+rgbG,bMatrix [Xloc+1][0][Zloc]+rgbB);
			else if (nRandomBrightness ==2)	
				glColor3ub(lpBits[r+2],lpBits[r+1],lpBits[r]);
		glVertex3f((GLfloat)(XStep+Step),bMatrix [Xloc+1][0][Zloc],(GLfloat)ZStep);
			if (nRandomBrightness ==1)	
				glColor3ub(bMatrix [Xloc+1][0][Zloc+1]+rgbR,bMatrix [Xloc+1][0][Zloc+1]+rgbG,bMatrix [Xloc+1][0][Zloc+1]+rgbB);
			else if (nRandomBrightness ==2)	
				glColor3ub(lpBits[r+2],lpBits[r+1],lpBits[r]);
		glVertex3f((GLfloat)(XStep+Step),bMatrix [Xloc+1][0][Zloc+1],(GLfloat)(ZStep+Step));
			if (nRandomBrightness ==1)	
				glColor3ub(bMatrix [Xloc][0][Zloc+1]+rgbR,bMatrix [Xloc][0][Zloc+1]+rgbG,bMatrix [Xloc][0][Zloc+1]+rgbB);
			else if (nRandomBrightness ==2)	
				glColor3ub(lpBits[r+2],lpBits[r+1],lpBits[r]);
		glVertex3f((GLfloat)XStep,bMatrix [Xloc][0][Zloc+1],(GLfloat)(ZStep+Step));
		
		r+=4;
		}
		r+=4;
		glEnd();
}
		if (IamEnter==TRUE)
			delete []lpBits;		
		glPopMatrix();
		SwapBuffers(dc->m_hDC);
		glFlush();
		
		

}

void COpenGLControl::Create(CRect rect, CWnd *parent)
{
	CString className = AfxRegisterWndClass(
		CS_HREDRAW | CS_VREDRAW | CS_OWNDC,
		NULL,
		(HBRUSH)GetStockObject(BLACK_BRUSH),
		NULL);

	CreateEx(
		0,
		className,
		"OpenGL",
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		rect,
		parent,
		0);

}

void COpenGLControl::OnPaint() 
{
	rotation += 0.01f;

	if (rotation >= 360.0f)
	{
		rotation -= 360.0f;
	}

	openGLDevice.makeCurrent();

	DrawGLScene();
}

void COpenGLControl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
ncy=cy;
ncx=cx;

if (cy == 0)								
	{
		cy = 1;						
	}

	
	GLfloat range=100.0f;

	glViewport(0,0,cx,cy);

    glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();

	if(cx<=cy)
	
		glOrtho(-range,range,-range*cy/cx,range*cy/cx,-range-100,range+100);
	else
		glOrtho(-range*cx/cy,range*cx/cy,-range,range,-range-100,range+100);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

}
void COpenGLControl::SetOnPaint() 
{
}

int COpenGLControl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	dc = new CClientDC(this);

	openGLDevice.create(dc->m_hDC);
	InitGL();

	return 0;
}

BOOL COpenGLControl::OnEraseBkgnd(CDC* pDC) 
{

	return TRUE;
}

void COpenGLControl::n_ExportVertex(CString FileName)
{
			ofstream fout(FileName);
			fout <<"Header Example	@";
			for (int i=0 ;i<240;i+=1)	
				for(int j=0 ;j<320;j +=1)
					{	
		    		 fout <<bMatrix [j][0][i]<<"`";
					 
     				}
			fout.close();

}

BOOL COpenGLControl::n_ExportPic(CString FileName)
{

	RECT rcClient;
	int cxImage, cyImage;
	cDIB DIB;
	GLubyte *pImageBits;

	FILE *fs;
	BITMAPFILEHEADER bmFileHeader;
	BITMAPINFOHEADER *pBmInfoHeader;

	::GetClientRect( this->m_hWnd, &rcClient );
	cxImage = rcClient.right;
	cyImage = rcClient.bottom;
	if ( FALSE == DIB.Create( cxImage, cyImage ) )
		return FALSE;

	pBmInfoHeader = &((DIB.BitmapInfoPointer())->bmiHeader);

	pImageBits = DIB.ImageBitsPointer();
	glReadPixels( 0, 0, cxImage, cyImage,
			GL_RGB, GL_UNSIGNED_BYTE,
			pImageBits );

	fs = fopen( FileName, "wb" );
	if ( NULL == fs )
		return FALSE;

	memset( &bmFileHeader, 0, sizeof(BITMAPFILEHEADER) );
	bmFileHeader.bfType = 0x4D42;
	bmFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmFileHeader.bfSize = bmFileHeader.bfOffBits
				+ pBmInfoHeader->biSizeImage;

	fwrite( &bmFileHeader, 1, sizeof(BITMAPFILEHEADER), fs );
	fwrite( pBmInfoHeader, 1, sizeof(BITMAPINFOHEADER), fs );

	fwrite( pImageBits, 1, pBmInfoHeader->biSizeImage, fs );

	fclose( fs );

	DIB.Destroy();

	return TRUE;
}

void COpenGLControl::initlights()
{
	GLfloat ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
	GLfloat position[] = {0.0f,0.0f ,150.0f, 1.0f};
	GLfloat mat_diffuse[] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat mat_specular[] = {0.1f, 0.1f, 0.1f, 1.0f};
	GLfloat mat_shininess[] = {50.5f};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL) ;
	glColorMaterial(GL_FRONT, GL_DIFFUSE) ;

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

}
void COpenGLControl::n_SetSeesaw(int Seesaw)
{
	nSeesaw=(GLfloat) Seesaw;
}
void COpenGLControl::n_SetRotation(GLfloat RotateArg)
{
	nRotate=RotateArg;
}
void COpenGLControl::n_SetZoom(GLfloat gZoom)
{
	nZoom= gZoom/1000.f;
}
void COpenGLControl::n_SetColor(GLfloat Red,GLfloat Green,GLfloat Blue)
{
	rgbR=Red;
	rgbG=Green;
	rgbB=Blue;
}

void COpenGLControl::n_SetDcOffset(int nOffset)
{
	nOfssetOfBrightness=nOffset;
}
void COpenGLControl::n_Freez(BOOL StartStop)
{
	nFreez=StartStop;
}
void COpenGLControl::n_SetPanTilt(GLfloat Tilt,GLfloat Pan)
{
	nTilt=Tilt-5000;
	nPan=Pan-5000;
}
void COpenGLControl::n_CapPreviewOnOff(BOOL Preview)
{
	capPreview(Videohwnd, Preview); 
}
void COpenGLControl::n_CapConnectDisConnect(BOOL nVisible,HWND nhWnd,BOOL Preview)
{
	if (nVisible==TRUE)
	{
		if (Preview == TRUE)
	Videohwnd = capCreateCaptureWindow(	NULL, WS_CHILD | WS_VISIBLE, 
										0, 0, 
										320, 240, 
										nhWnd , 
										(int)0);
		else
	Videohwnd = capCreateCaptureWindow(	NULL, WS_CHILD , 
										0, 0, 
										320, 240, 
										nhWnd , 
										(int)0);
	
	capDriverConnect(Videohwnd, 0);
	capPreviewRate(Videohwnd, 66);
	capOverlay(Videohwnd,true); 
	capPreview(Videohwnd, TRUE);
	}
	else
	{
		capDriverDisconnect(Videohwnd);
	}

}
void COpenGLControl::n_GrabFrame()
{
	capGrabFrame(Videohwnd);
	capEditCopy(Videohwnd);
}
void COpenGLControl::n_SetRandomBright(int nRandomBright)
{
nRandomBrightness=nRandomBright;
}
void COpenGLControl::n_SetRenderMode(int ModeofRender)
{
	nRenderMode=ModeofRender;
}
void COpenGLControl::n_SetStepInRender(int StepofRender)
{
nStepInRender=StepofRender;
}
int COpenGLControl::n_GetRandomBright()
{
return nRandomBrightness;
}