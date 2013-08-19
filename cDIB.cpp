#include "stdafx.h"
#include "cDIB.h"

cDIB::cDIB()
{

m_hBitmapImage = NULL;

}

cDIB::~cDIB()
{

Destroy();

}

BOOL cDIB::Create( int cx, int cy )
{
	HDC hDc;

	m_cxImage = cx;
	m_cyImage = cy;

	hDc = GetDC( NULL );
	memset( &m_BitmapInfo, 0, sizeof(BITMAPINFO) );
	m_BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_BitmapInfo.bmiHeader.biWidth = m_cxImage;
	m_BitmapInfo.bmiHeader.biHeight = m_cyImage;
	m_BitmapInfo.bmiHeader.biPlanes = 1;
	m_BitmapInfo.bmiHeader.biBitCount = 24;
	m_BitmapInfo.bmiHeader.biCompression = BI_RGB;
	m_BitmapInfo.bmiHeader.biSizeImage =
		(((m_cxImage * 24 + 31) & ~31) / 8) * m_cyImage;
	m_hBitmapImage = CreateDIBSection( hDc,
		&m_BitmapInfo, DIB_RGB_COLORS,
		(void **)(&m_pBitmapBits), NULL, 0 );
	ReleaseDC( NULL, hDc );

	return TRUE;
}

void cDIB::Destroy()
{
	if ( NULL != m_hBitmapImage ) {
		DeleteObject( m_hBitmapImage );
		m_hBitmapImage = NULL;
	}
}