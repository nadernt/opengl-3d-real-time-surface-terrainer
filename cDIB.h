#include <GL\glut.h>

#ifndef __DEF_C_DIB_H
#define __DEF_C_DIB_H


class cDIB
{
	HBITMAP m_hBitmapImage;
	int m_cxImage, m_cyImage;

	BITMAPINFO m_BitmapInfo;
	GLubyte *m_pBitmapBits;

public:
	cDIB();
	~cDIB();

	BOOL Create( int cx, int cy );
	void Destroy();

	HBITMAP hBitmap() { return m_hBitmapImage; };
	BITMAPINFO *BitmapInfoPointer() { return &m_BitmapInfo; };
	GLubyte *ImageBitsPointer() { return m_pBitmapBits; };

};

#endif //__DEF_C_DIB_H



