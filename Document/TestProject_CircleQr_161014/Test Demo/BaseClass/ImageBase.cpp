// ImageBase.cpp: implementation of the CImageBase class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ImageBase.h"
#include "ImageIO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//#define RGB2GRAY(r,g,b) (((b)*114 + (g)*587 + (r)*299)/1000)
#define RGB2GRAY(r,g,b) (((b)*117 + (g)*601 + (r)*306) >> 10)

CImageBase::CImageBase()
{

}

CImageBase::~CImageBase()
{

}
BOOL CImageBase::IsValid(BYTE* lpBits,int w,int h)
{
	if (lpBits == NULL) return FALSE;
	if (w <0 || h<0) return FALSE;
	return TRUE;
}
BYTE* CImageBase::Get_lpBits(BYTE *pDib)
{
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	int QuadSize;
	if(lpBIH->biBitCount == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(lpBIH->biBitCount == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(lpBIH->biBitCount == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(lpBIH->biBitCount == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else							QuadSize = 0;//16,24,32
	BYTE* lpBits = (BYTE*) (pDib + sizeof(BITMAPINFOHEADER)+ QuadSize);
	return lpBits;
}

int	CImageBase::GetDibSize(BYTE *pDib)
{
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	int w = (int)lpBIH->biWidth;
	int h = (int)lpBIH->biHeight;
	int QuadSize;
	if(lpBIH->biBitCount == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(lpBIH->biBitCount == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(lpBIH->biBitCount == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(lpBIH->biBitCount == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else							QuadSize = 0;//16,24

	int WidByte = (lpBIH->biBitCount*w+31)/32*4;
	int DibSize = sizeof(BITMAPINFOHEADER)+QuadSize+WidByte*h;
	return DibSize;
}

int	CImageBase::GetDibSize(int w,int h,int bitcount)
{
	int QuadSize;
	if(bitcount == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(bitcount == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(bitcount == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(bitcount == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else if(bitcount == 16)	QuadSize = 0;//164
	else if(bitcount == 24)	QuadSize = 0;//24
	else if(bitcount == 32)	QuadSize = 0;//32
	else return 0;

	int WidByte = (bitcount*w+31)/32*4;
	int DibSize = sizeof(BITMAPINFOHEADER)+QuadSize+WidByte*h;
	return DibSize;
}
int	CImageBase::GetBitsSize(BYTE *pDib)
{
	if(pDib == NULL) return 0;
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	return lpBIH->biSizeImage;
}
void CImageBase::GetWidthHeight(BYTE *pDib,int& w, int& h)
{
	if(pDib==NULL) return;
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	w=(int)lpBIH->biWidth;
	h=(int)lpBIH->biHeight;
}
int CImageBase::GetBitCount(BYTE *pDib)
{
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	return (int)lpBIH->biBitCount;
}
void CImageBase::GetDibInfo(BYTE* pDib,int& w,int& h,int& bpp,int& wstep)
{
	if(pDib==NULL) return;
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	w=(int)lpBIH->biWidth;
	h=(int)lpBIH->biHeight;
	bpp = (int)lpBIH->biBitCount;
	wstep = (w*bpp+31)/32 * 4;
}
int CImageBase::GetDPI(BYTE *pDib)
{
	int dpi;
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	dpi = min(lpBIH->biXPelsPerMeter, lpBIH->biYPelsPerMeter);
	dpi = (int)(dpi*2.54f/100.0f+0.5f);
	return dpi;
	
}

void CImageBase::DrawDib(CDC *pDC,CRect Rt,BYTE *pDib)
{
	if(pDib==NULL) return;

	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	int w=(int)lpBIH->biWidth;
	int h=(int)lpBIH->biHeight;
	BYTE *lpBits= Get_lpBits(pDib);

	::StretchDIBits( pDC->GetSafeHdc(),
			Rt.left,Rt.top, Rt.Width(),Rt.Height(),0,0, w,h,
			(BYTE*)lpBits,
            (LPBITMAPINFO)lpBIH,DIB_RGB_COLORS,
				SRCCOPY);

}
void CImageBase::DrawInvertDib(CDC *pDC,CRect Rt,BYTE *pDib)
{
	if(pDib==NULL) return;
	
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	int w=(int)lpBIH->biWidth;
	int h=(int)lpBIH->biHeight;
	
	BYTE *lpBits= Get_lpBits(pDib);
	
	::StretchDIBits( pDC->GetSafeHdc(),
		Rt.left,Rt.top, Rt.Width(),Rt.Height(),0,0, w,h,
		(BYTE*)lpBits,
		(LPBITMAPINFO)lpBIH,DIB_RGB_COLORS,
				SRCCOPY);

}
void CImageBase::DrawDib(CDC *pDC,BYTE *pDib,int sx,int sy)
{
	if(pDib==NULL) return;
	
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	int w=(int)lpBIH->biWidth;
	int h=(int)lpBIH->biHeight;
	BYTE *lpBits= Get_lpBits(pDib);
	
	::StretchDIBits( pDC->GetSafeHdc(),
		sx,sy, w,h,0,0, w,h,
		(BYTE*)lpBits,
		(LPBITMAPINFO)lpBIH,DIB_RGB_COLORS,
				SRCCOPY);

}
void CImageBase::DrawDib(CDC *pDC,BYTE *pDib)
{
	if(pDib==NULL) return;

	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	int w=(int)lpBIH->biWidth;
	int h=(int)lpBIH->biHeight;
	BYTE *lpBits= Get_lpBits(pDib);

	::StretchDIBits( pDC->GetSafeHdc(),
			0,0, w,h,0,0, w,h,
			(BYTE*)lpBits,
            (LPBITMAPINFO)lpBIH,DIB_RGB_COLORS,
				SRCCOPY);

}

BYTE* CImageBase::MakeImgFromBinBits(BYTE *lpBits,int w,int h)
{
	int k,k1,i,j,fg;
	BYTE cc;
	BYTE* pImg = new BYTE[w*h];
	memset(pImg,0,w*h);
	int WidByte = (w+31)/32 * 4;
	for(i=0;i<h;++i){
		k1=0;fg=0;
		for(j=0;j<WidByte;++j){
			cc=lpBits[i*WidByte+j];
			for(k=0;k<8;++k){
				if((cc&0x80)==0x80)  pImg[(h-1-i)*w+k1]=(BYTE)0;
				else 		     	 pImg[(h-1-i)*w+k1]=(BYTE)1;
				cc=cc<<1;
				k1++;
				if(k1 == w){ 
					fg=1;
					break;
				}
			}
			if(fg==1)break;
		}
	}
	return pImg;
}
BYTE* CImageBase::MakeGrayImgFromBinBits(BYTE *lpBits,int w,int h)
{
	int k,k1,i,j,fg;
	BYTE cc;
	BYTE* pImg = new BYTE[w*h];
	memset(pImg,0,w*h);
	int WidByte = (w+31)/32 * 4;
	for(i=0;i<h;++i){
		k1=0;fg=0;
		for(j=0;j<WidByte;++j){
			cc=lpBits[i*WidByte+j];
			for(k=0;k<8;++k){
				if((cc&0x80)==0x80)  pImg[(h-1-i)*w+k1]=(BYTE)255;
				else 		     	 pImg[(h-1-i)*w+k1]=(BYTE)0;
				cc=cc<<1;
				k1++;
				if(k1 == w){ 
					fg=1;
					break;
				}
			}
			if(fg==1)break;
		}
	}
	return pImg;
}
BYTE* CImageBase::MakeBinBitsFromImg(BYTE *pImg, int w, int h)
{
	if(pImg==NULL) return NULL;
	BYTE reg = 0;
	int	 i,j,i1,j1;

	// Black=1;White =0; Rem=0;
	int WidByte = (w+31)/32*4;
	BYTE* lpBits = new BYTE[WidByte*h];
	int rem = w % 8;
	
	i1=0;
	for(i=h-1;i>=0;i--){
		j1=0;
		for(j=0;j<w;j++){
			if(pImg[i*w+j] != 0)	reg |= 0;
			else					reg |= 1;		  
		    if(((j+1) % 8) == 0){
			  lpBits[i1*WidByte+j1] = reg;
			  j1++;
			  reg = 0;
			}
			else{ reg<<=1;}
		}
		if(rem != 0){
			reg <<= 8 - rem-1;
			lpBits[i1*WidByte+j1] = reg;
		}
		reg=0;
		i1++;
	}
	return lpBits;
}

BYTE* CImageBase::MakeImgFromBinDib(BYTE *pDib,int& w,int& h)
{
 	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;
	if(lpBIH->biBitCount!=1) return NULL;

	w = (int)lpBIH->biWidth;
	h = (int)lpBIH->biHeight;
	BYTE* lpBits = Get_lpBits(pDib);
	BYTE* pImg = MakeImgFromBinBits(lpBits,w,h);
	return pImg;
}

BYTE* CImageBase::MakeGrayImgFromBinDib(BYTE *pDib,int& w,int& h)
{
 	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;
	if(lpBIH->biBitCount!=1) return NULL;

	w = (int)lpBIH->biWidth;
	h = (int)lpBIH->biHeight;
	BYTE* lpBits = Get_lpBits(pDib);
	BYTE* pImg = MakeGrayImgFromBinBits(lpBits,w,h);
	return pImg;
}

BYTE* CImageBase::MakeBinDibFromBits(BYTE *lpBits, int w, int h)
{
	int WidByte = (w+31)/32*4;
	int	ImgSize = WidByte*h;
	int HeadSize=sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
	int DibSize=HeadSize+ImgSize;
	BYTE *pDib=new BYTE[DibSize];
	
			
	BITMAPINFOHEADER* pBIH  = (BITMAPINFOHEADER*)pDib;
	pBIH->biSize			= sizeof(BITMAPINFOHEADER);
	pBIH->biWidth			= w; 
	pBIH->biHeight			= h; 
	pBIH->biPlanes			= 1; 
	pBIH->biBitCount		= 1; 
	pBIH->biCompression		= 0; 
	pBIH->biSizeImage		= ImgSize; 
	pBIH->biXPelsPerMeter	= 0; 
	pBIH->biYPelsPerMeter	= 0; 
	pBIH->biClrUsed			= 2; 
	pBIH->biClrImportant	= 0;

	BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pBIH;
	pInfoH->bmiColors[0].rgbRed      = 0;
	pInfoH->bmiColors[0].rgbGreen    = 0;
	pInfoH->bmiColors[0].rgbBlue     = 0;
	pInfoH->bmiColors[0].rgbReserved = 0;
	
	pInfoH->bmiColors[1].rgbRed      = 255;
	pInfoH->bmiColors[1].rgbGreen    = 255;
	pInfoH->bmiColors[1].rgbBlue     = 255;
	pInfoH->bmiColors[1].rgbReserved = 0;

	BYTE* pBits = Get_lpBits(pDib);
	memcpy(pBits,lpBits,ImgSize);
	return pDib;
}
BYTE* CImageBase::MakeBinDibFromImg(BYTE *pImg, int w, int h)
{
	if(pImg==NULL) return NULL;
	int WidByte = (w+31)/32*4;
	int	ImgSize = WidByte*h;
	int HeadSize=sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*2;
	int DibSize=HeadSize+ImgSize;
	BYTE *pDib=new BYTE[DibSize];
	BITMAPINFOHEADER* pBIH  = (BITMAPINFOHEADER*)pDib;
	pBIH->biSize			= sizeof(BITMAPINFOHEADER);
	pBIH->biWidth			= w; 
	pBIH->biHeight			= h; 
	pBIH->biPlanes			= 1; 
	pBIH->biBitCount		= 1; 
	pBIH->biCompression		= 0; 
	pBIH->biSizeImage		= ImgSize; 
	pBIH->biXPelsPerMeter	= 0; 
	pBIH->biYPelsPerMeter	= 0; 
	pBIH->biClrUsed			= 2; 
	pBIH->biClrImportant	= 0;

	BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pBIH;
	pInfoH->bmiColors[0].rgbRed      = 0;
	pInfoH->bmiColors[0].rgbGreen    = 0;
	pInfoH->bmiColors[0].rgbBlue     = 0;
	pInfoH->bmiColors[0].rgbReserved = 0;
	
	pInfoH->bmiColors[1].rgbRed      = 255;
	pInfoH->bmiColors[1].rgbGreen    = 255;
	pInfoH->bmiColors[1].rgbBlue     = 255;
	pInfoH->bmiColors[1].rgbReserved = 0;

	BYTE* lpBits = Get_lpBits(pDib);	
	BYTE reg = 0;
	int	 i,j,i1,j1;
	int rem = w % 8;
	
	i1=0;
	for(i=h-1;i>=0;i--){
		j1=0;
		for(j=0;j<w;j++){
			if(pImg[i*w+j] != 0)	reg |= 0;
			else					reg |= 1;		  
		    if(((j+1) % 8) == 0){
			  lpBits[i1*WidByte+j1] = reg;
			  j1++;
			  reg = 0;
			}
			else{ reg<<=1;}
		}
		if(rem != 0){
			reg <<= 8 - rem-1;
			lpBits[i1*WidByte+j1] = reg;
		}
		reg=0;
		i1++;
	}

	return pDib;
}
BYTE* CImageBase::MakeImgFromGrayDib(BYTE *pDib,int& w,int& h)
{
 	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;
	if(lpBIH->biBitCount!=8) return NULL;

	w = (int)lpBIH->biWidth;
	h = (int)lpBIH->biHeight;
	BYTE* lpBits = Get_lpBits(pDib);
	int WidthByte = (w*8+31)/32*4;
	BYTE *pImg=new BYTE[w*h];
	int i,j;
	//Copy Image
	for(i=0;i<h;i++)for(j=0;j<w;j++)
		*(pImg+i*w+j)=*(lpBits+(h-i-1)*WidthByte+j);
	return pImg;
}
BYTE* CImageBase::MakeDib(int w,int h,int nBitCount)
{
	if(nBitCount!=1 && nBitCount != 8 && nBitCount != 16  &&  
		nBitCount != 24  && nBitCount != 32)  return NULL;
	
	int DibSize = GetDibSize(w, h, nBitCount);
	BYTE* pDib = new BYTE[DibSize];
	
	int WidByte = (nBitCount*w+31)/32*4;
	int	ImgSize = WidByte*h;
	int nClrUsed;
	if(nBitCount==1)       nClrUsed = 2;
	else if(nBitCount==8)  nClrUsed = 256;
	else if(nBitCount==16) nClrUsed = 0;
	else if(nBitCount==24) nClrUsed = 0;
	else if(nBitCount==32) nClrUsed = 0;
	BITMAPINFOHEADER* pBIH  = (BITMAPINFOHEADER*)pDib;
	pBIH->biSize			= sizeof(BITMAPINFOHEADER);
	pBIH->biWidth			= w; 
	pBIH->biHeight			= h; 
	pBIH->biPlanes			= 1; 
	pBIH->biBitCount		= nBitCount; 
	pBIH->biCompression		= 0;
	pBIH->biSizeImage		= ImgSize; 
	pBIH->biXPelsPerMeter	= 0; 
	pBIH->biYPelsPerMeter	= 0; 
	pBIH->biClrUsed			= nClrUsed; 
	pBIH->biClrImportant	= 0;
	if(nBitCount<16)
	{
		int i;
		BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pBIH;
		for(i=0;i<nClrUsed;i++)
		{
			pInfoH->bmiColors[i].rgbRed      = i;
			pInfoH->bmiColors[i].rgbGreen    = i;
			pInfoH->bmiColors[i].rgbBlue     = i;
			pInfoH->bmiColors[i].rgbReserved = 0;
		}
		pInfoH->bmiColors[nClrUsed-1].rgbRed      = 255;
		pInfoH->bmiColors[nClrUsed-1].rgbGreen    = 255;
		pInfoH->bmiColors[nClrUsed-1].rgbBlue     = 255;
		pInfoH->bmiColors[nClrUsed-1].rgbReserved = 0;
	}
	return pDib;
}
BYTE* CImageBase::MakeGrayDibFromImg(BYTE *pImg,int w,int h)
{
	int i,j;
	if(pImg == NULL ) return NULL;
	int widByte = (8*w+31)/32*4;
	int ImgSize = widByte * h;
	int HeadSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256;
	int DibSize=HeadSize+ImgSize;
	BYTE *pDib=new BYTE[DibSize];
	
	//Create InfoHeader
	BITMAPINFOHEADER* pBIH  = (BITMAPINFOHEADER*)pDib;
	pBIH->biSize			= sizeof(BITMAPINFOHEADER);
	pBIH->biWidth			= w; 
	pBIH->biHeight			= h; 
	pBIH->biPlanes			= 1; 
	pBIH->biBitCount		= 8; 
	pBIH->biCompression		= 0;
	pBIH->biSizeImage		= ImgSize; 
	pBIH->biXPelsPerMeter	= 0; 
	pBIH->biYPelsPerMeter	= 0; 
	pBIH->biClrUsed			= 256; 
	pBIH->biClrImportant	= 0;

	//Create Palette
	BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pBIH;
	for(i=0; i<256; i++)
	{
		pInfoH->bmiColors[i].rgbRed      = i;
		pInfoH->bmiColors[i].rgbGreen    = i;
		pInfoH->bmiColors[i].rgbBlue     = i;
		pInfoH->bmiColors[i].rgbReserved = 0;
	}

	//Copy Image
	BYTE *pBits = pDib + HeadSize;
	for(i=0; i<h; i++) for(j=0; j<w; j++)
	     pBits[widByte*(h-i-1)+j] = pImg[i*w+j];

	return pDib;
}
BYTE* CImageBase::MakeGrayDibFromBits(BYTE *lpBits,int w,int h)
{
	if(lpBits == NULL ) return NULL;
	int widByte = (8*w+31)/32*4;
	int ImgSize = widByte * h;
	int HeadSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256;
	int DibSize=HeadSize+ImgSize;
	BYTE *pDib=new BYTE[DibSize];
	
	//Create InfoHeader
	BITMAPINFOHEADER* pBIH  = (BITMAPINFOHEADER*)pDib;
	pBIH->biSize			= sizeof(BITMAPINFOHEADER);
	pBIH->biWidth			= w; 
	pBIH->biHeight			= h; 
	pBIH->biPlanes			= 1; 
	pBIH->biBitCount		= 8; 
	pBIH->biCompression		= 0;
	pBIH->biSizeImage		= ImgSize; 
	pBIH->biXPelsPerMeter	= 0; 
	pBIH->biYPelsPerMeter	= 0; 
	pBIH->biClrUsed			= 256; 
	pBIH->biClrImportant	= 0;
	
	//Create Palette
	int i;
	BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pBIH;
	for(i=0; i<256; i++)
	{
		pInfoH->bmiColors[i].rgbRed      = i;
		pInfoH->bmiColors[i].rgbGreen    = i;
		pInfoH->bmiColors[i].rgbBlue     = i;
		pInfoH->bmiColors[i].rgbReserved = 0;
	}
	//Copy Image
	BYTE *pBits = pDib + HeadSize;
	memcpy(pBits,lpBits,ImgSize);
	return pDib;
}
BYTE* CImageBase::MakeGrayDibFrom24Dib(BYTE* pDib24)
{
	if(pDib24==NULL) return NULL;
    BITMAPINFOHEADER* pBIH24= (BITMAPINFOHEADER*)pDib24;
	if(pBIH24->biBitCount != 24)return NULL;
	BYTE* pBits24 = pDib24 + sizeof(BITMAPINFOHEADER);
	int w = pBIH24->biWidth;
	int h = pBIH24->biHeight;
	int widByte24 = (w*24+31)/32*4;
	
	//Create GrayDib
	int widByte8 = (w*8+31)/32*4;
	int ImgSize8 = widByte8 * h;
	int HeadSize8 = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*256;
	int DibSize8=HeadSize8+ImgSize8;
	BYTE *pDib8=new BYTE[DibSize8];
	BYTE *pBits8 = pDib8 + HeadSize8;

	//Create InfoHeader
	BITMAPINFOHEADER* pBIH8 = (BITMAPINFOHEADER*)pDib8;
	pBIH8->biSize			= sizeof(BITMAPINFOHEADER);
	pBIH8->biWidth			= w; 
	pBIH8->biHeight			= h; 
	pBIH8->biPlanes			= 1; 
	pBIH8->biBitCount		= 8; 
	pBIH8->biCompression	= 0;
	pBIH8->biSizeImage		= ImgSize8; 
	pBIH8->biXPelsPerMeter	= 0; 
	pBIH8->biYPelsPerMeter	= 0; 
	pBIH8->biClrUsed		= 256; 
	pBIH8->biClrImportant	= 0;

	//CreatePalette;
	int i,j;
	BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pBIH8;
	for(i=0; i<256; i++)
	{
		pInfoH->bmiColors[i].rgbRed      = i;
		pInfoH->bmiColors[i].rgbGreen    = i;
		pInfoH->bmiColors[i].rgbBlue     = i;
		pInfoH->bmiColors[i].rgbReserved = 0;
	}
	for(i=0;i<h;i++) for(j=0;j<w;j++)
	{
		BYTE b = pBits24[widByte24*i + j*3];
		BYTE g = pBits24[widByte24*i + j*3+1];
		BYTE r = pBits24[widByte24*i + j*3+2];
		pBits8[widByte8*i + j] = (BYTE) RGB2GRAY(r,g,b);
	}
	return pDib8;
}
BYTE* CImageBase::MakeGrayImgFrom24Dib(BYTE* pDib,int& w,int& h)
{
	if(pDib==NULL) return NULL;
    BITMAPINFOHEADER* pBIH= (BITMAPINFOHEADER*)pDib;
	if(pBIH->biBitCount != 24)return NULL;
	BYTE* pBits = pDib + sizeof(BITMAPINFOHEADER);
	w = pBIH->biWidth;
	h = pBIH->biHeight;
	int widByte = (w*24+31)/32*4;
	BYTE* GrayImg = new BYTE[w*h];
	int gray;
	double a = 0.8;
	int i,j;
	for(i=0;i<h;i++) for(j=0;j<w;j++)
	{
		BYTE b = pBits[widByte*i + j*3];
		BYTE g = pBits[widByte*i + j*3+1];
		BYTE r = pBits[widByte*i + j*3+2];
		gray = (BYTE) RGB2GRAY(r,g,b);
		GrayImg[w*(h-1-i) + j] = gray;//min(255,(int)(gray*a +(255-r)*(1-a)));
	}
	return GrayImg;
}

BYTE* CImageBase::MakeGrayImgFrom16Dib(BYTE* pDib,int& w,int& h)
{
	if(pDib==NULL) return NULL;
    BITMAPINFOHEADER* pBIH= (BITMAPINFOHEADER*)pDib;
	if(pBIH->biBitCount != 16)return NULL;
	BYTE* pBits = pDib + sizeof(BITMAPINFOHEADER);
	w = pBIH->biWidth;
	h = pBIH->biHeight;
	int widByte = w*2;//(w*16+31)/32*4;
	BYTE* GrayImg = new BYTE[w*h];
	int i,j;
	for(i=0;i<h;i++) for(j=0;j<w;j++)
	{
		WORD val = MAKEWORD(pBits[widByte*i+j*2],pBits[widByte*i+j*2+1]);
		BYTE b = (val & 0x001F)<<3;
		BYTE g = (val & 0x03E0)>>2;
		BYTE r = (val & 0xFC00)>>8;
		GrayImg[w*(h-1-i) + j] = (BYTE) RGB2GRAY(r,g,b);
	}
	return GrayImg;
}
BYTE* CImageBase::MakeGrayImgFrom32Dib(BYTE* pDib,int& w,int& h)
{
	if(pDib==NULL) return NULL;
	BITMAPINFOHEADER* pBIH= (BITMAPINFOHEADER*)pDib;
	if(pBIH->biBitCount != 32)return NULL;
	BYTE* pBits = pDib + sizeof(BITMAPINFOHEADER);
	w = pBIH->biWidth;
	h = pBIH->biHeight;
	int widByte = w*4;
	BYTE* GrayImg = new BYTE[w*h];
	int i,j;
	for(i=0;i<h;i++) for(j=0;j<w;j++)
	{
		BYTE b = pBits[widByte*i + j*4];
		BYTE g = pBits[widByte*i + j*4+1];
		BYTE r = pBits[widByte*i + j*4+2];
		GrayImg[w*(h-1-i) + j] = (BYTE) RGB2GRAY(r,g,b);
	}
	return GrayImg;
}

/*
Name   Make24DIBFromRGBImg
Author Kim M.I.
Date   2008/3/22
*/
BYTE* CImageBase::Make24DibFromRGBImg(BYTE* pImgR, BYTE* pImgG, BYTE* pImgB, int w, int h)
{
	if(pImgR==NULL || pImgG==NULL || pImgB==NULL) return NULL;
	
	BYTE *pDib,*pBits;
	int i,j;
	int ByteW = (w*24+31)/32*4;
	int ImgSize  = ByteW * h;
	int HeadSize=sizeof(BITMAPINFOHEADER);
	int DibSize=HeadSize+ImgSize;
	
	pDib=new BYTE[DibSize];

	BITMAPINFOHEADER* lpBIH;
		

	lpBIH =	(BITMAPINFOHEADER*)pDib;
	lpBIH->biSize				= sizeof(BITMAPINFOHEADER);
	lpBIH->biWidth			= w; 
	lpBIH->biHeight			= h; 
	lpBIH->biPlanes			= 1; 
	lpBIH->biBitCount		= 24; 
	lpBIH->biCompression	= 0; 
	lpBIH->biSizeImage		= ImgSize; 
	lpBIH->biXPelsPerMeter	= 0; 
	lpBIH->biYPelsPerMeter	= 0; 
	lpBIH->biClrUsed		= 0; 
	lpBIH->biClrImportant	= 0;

	pBits = pDib + HeadSize;

	for(i=0;i<h;i++)for(j=0;j<w;j++)
	{
		pBits[i*ByteW+j*3]   = pImgB[(h-1-i)*w+j];
		pBits[i*ByteW+j*3+1] = pImgG[(h-1-i)*w+j];
		pBits[i*ByteW+j*3+2] = pImgR[(h-1-i)*w+j];
	}
	return pDib;
}

/*
Name   MakeGrayDib
Author Kim M.I.
Date   2009/1/15
*/
BYTE* CImageBase::MakeGrayImgFromAnyDib(BYTE* pDib,int& w,int& h)
{
	if(pDib == NULL) return NULL;
	LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER) pDib;
	BYTE* pNewImg = NULL;
	if(pBIH->biBitCount == 32)
	{
		pNewImg = MakeGrayImgFrom32Dib(pDib,w,h);
	}
	if(pBIH->biBitCount == 24)
	{
		pNewImg = MakeGrayImgFrom24Dib(pDib,w,h);
	}
	else if(pBIH->biBitCount == 8)
	{
		pNewImg = MakeImgFromGrayDib(pDib,w,h);
	}
	else if(pBIH->biBitCount == 1)
	{
		pNewImg = MakeGrayImgFromBinDib(pDib,w,h);
	}
	return pNewImg;
}
/*
Name   MakeGrayDib
Author Kim M.I.
Date   2009/1/15
*/
BYTE* CImageBase::MakeGrayDib(BYTE* pDib)
{
	if(pDib == NULL) return NULL;
	LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER) pDib;
	BYTE* pNewDib = NULL;
	int w,h;
	if(pBIH->biBitCount == 32)
	{
		//pNewDib = MakeGrayDibFrom32Dib(pDib);
	}
	if(pBIH->biBitCount == 24)
	{
		pNewDib = MakeGrayDibFrom24Dib(pDib);
	}
	else if(pBIH->biBitCount == 8)
	{
		int DibSize = GetDibSize(pDib);
		pNewDib = new BYTE[DibSize];
		memcpy(pNewDib,pDib,DibSize);
	}
	else if(pBIH->biBitCount == 1)
	{
		BYTE* pImg = MakeGrayImgFromBinDib(pDib,w,h);
		pNewDib = MakeGrayDibFromImg(pImg,w,h);
		delete[] pImg;
	}
	return pNewDib;
}
/*
Name   Make24Dib
Author Kim M.I.
Date   2009/1/11
*/
BYTE* CImageBase::Make24Dib(BYTE* pDib)
{
	if(pDib == NULL) return NULL;
	LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER) pDib;
	BYTE* pNewDib = NULL;
	int w,h;
	if(pBIH->biBitCount == 24)
	{
		int DibSize = GetDibSize(pDib);
		pNewDib = new BYTE[DibSize];
		memcpy(pNewDib,pDib,DibSize);
	}
	else if(pBIH->biBitCount == 8)
	{
		BYTE* pImg = MakeImgFromGrayDib(pDib,w,h);
		pNewDib = Make24DibFromRGBImg(pImg,pImg,pImg,w,h);
		delete[] pImg;
	}
	else if(pBIH->biBitCount == 1)
	{
		BYTE* pImg = MakeGrayImgFromBinDib(pDib,w,h);
		pNewDib = Make24DibFromRGBImg(pImg,pImg,pImg,w,h);
		delete[] pImg;
	}
	return pNewDib;
}
/*
Name   Make32DibFrom24Dib
Author Kim M.I.
Date   2009/6/25
*/
BYTE* CImageBase::Make32DibFrom24Dib(BYTE* pDib)
{
	if(pDib == NULL) return NULL;
	LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER) pDib;
	if(pBIH->biBitCount != 24) return NULL;
	int w,h;
	GetWidthHeight(pDib,w,h);
	BYTE* pNewDib = MakeDib(w,h,32);

	BYTE* pBits = Get_lpBits(pDib);
	BYTE* pNewBits = Get_lpBits(pNewDib);
	int ByteWid,newByteWid;
	ByteWid = (w*24+31)/32*4;
	newByteWid = w*4;
	int i,j;
	for(i=0;i<h;i++)for(j=0;j<w;j++)
	{
		pNewBits[i*newByteWid+j*4] = pBits[i*ByteWid+j*3];
		pNewBits[i*newByteWid+j*4+1] = pBits[i*ByteWid+j*3+1];
		pNewBits[i*newByteWid+j*4+2] = pBits[i*ByteWid+j*3+2];
		pNewBits[i*newByteWid+j*4+3] = 0;
	}
	return pNewDib;
}
/*
Name   InvertDib
Author Kim M.I.
Date   2009/1/11
*/
void CImageBase::InvertDib(BYTE* pDib,BOOL bAuto)
{
	if(pDib == NULL) return;
	BOOL bDo=!bAuto;
	int i,j;
	LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER) pDib;
	BYTE* pBits = Get_lpBits(pDib);
	int imgSize = pBIH->biSizeImage;
	if(bAuto==TRUE && GetBitCount(pDib)==1)
	{
		int w,h,s=0;
		BYTE* pImg = MakeImgFromBinDib(pDib,w,h);		
		for(i=0;i<h;i++)
			for(j=0;j<w;j++)
				if(pImg[i*w+j]==1)
					s++;
		if(s>w*h*3/5)
			bDo=TRUE;
		else
			bDo=FALSE;
		delete []pImg;
	}
	if(bDo)
	for(i=0; i<imgSize; i++)
		pBits[i] = ~pBits[i];
}
/*
Name   MakeRGBImgFrom24Bits
Author Kim M.I.
Date   2008/3/22
*/
BOOL CImageBase::MakeRGBImgFrom24Bits(BYTE* lpBits,BYTE*& pImgR, BYTE*& pImgG, BYTE*& pImgB, int w, int h)
{
	if(lpBits==NULL) return FALSE;

	int i,j;
	int ByteW = (w*24+31)/32*4;
	
	pImgR=new BYTE[w * h];
	pImgG=new BYTE[w * h];
	pImgB=new BYTE[w * h];

	for(i=0;i<h;i++)for(j=0;j<w;j++)
	{
		pImgB[(h-1-i)*w+j] = lpBits[i*ByteW+j*3];
		pImgG[(h-1-i)*w+j] = lpBits[i*ByteW+j*3+1];
		pImgR[(h-1-i)*w+j] = lpBits[i*ByteW+j*3+2];
	}
	return TRUE;
}
/*
Name   MakeRGBImgFrom24Dib
Author Kim M.I.
Date   2008/3/22
*/
BOOL CImageBase::MakeRGBImgFrom24Dib(BYTE* pDib,BYTE*& pImgR, BYTE*& pImgG, BYTE*& pImgB, int& w, int& h)
{
	if(pDib==NULL) return FALSE;

 	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;

	if(lpBIH->biBitCount!=24)return FALSE;
	
	w = (int)lpBIH->biWidth;
	h = (int)lpBIH->biHeight;
	BYTE* lpBits = Get_lpBits(pDib);

	return MakeRGBImgFrom24Bits(lpBits, pImgR, pImgG, pImgB, w, h);
}
BYTE* CImageBase::MakeGrayImgFrom24Img(BYTE* pImgR, BYTE* pImgG, BYTE* pImgB, int w, int h)
{
	if(pImgR==NULL || pImgG==NULL || pImgB==NULL) return NULL;

	BYTE *pImg=new BYTE[w*h];
	int i,j;
	for(i=0;i<h;i++)for(j=0;j<w;j++)
	{
		pImg[i*w+j] = (BYTE) RGB2GRAY(pImgR[i*w+j], pImgG[i*w+j], pImgB[i*w+j]);
	}
	return pImg;
}

BYTE* CImageBase::Make256ColorDibFrom24Dib(BYTE* pDib)
{
	if(pDib==NULL) return NULL;
    BITMAPINFO* pInfo  = (BITMAPINFO*)((LPSTR)pDib);
    BITMAPINFOHEADER* pInfHd= (BITMAPINFOHEADER*)((LPSTR)pInfo);
    WORD Head   = (WORD)(sizeof(BITMAPINFOHEADER));
	WORD bit  = (WORD)(pInfHd->biBitCount);
	if(bit <24) return NULL;

	int w = pInfHd->biWidth;
	int h = pInfHd->biHeight;
	int EffWd24,EffWd8;
   	EffWd24 = ((((24 * w) + 31) / 32) * 4);
	EffWd8 =  ((((8 * w) + 31) / 32) * 4);
	
	int ImgSize  = EffWd8 * pInfHd->biHeight;
	int HeadSize=sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*256;
	int DibSize=HeadSize+ImgSize;

	int i,j,k,nQ=0;
	BYTE* p24Bits = pDib+Head;
	RGBQUAD qQ;
	int*		pQNum= new int[w*h];
	RGBQUAD*	pQ   = new RGBQUAD[w*h];
	memset(pQ,   0, sizeof(RGBQUAD)*w*h);
	memset(pQNum,0, sizeof(int)*w*h);

	for(i=0;i<h;++i)for(j=0;j<w;++j){
		qQ.rgbBlue	= p24Bits[i*EffWd24+j*3];
		qQ.rgbGreen = p24Bits[i*EffWd24+j*3+1];
		qQ.rgbRed	= p24Bits[i*EffWd24+j*3+2];
		qQ.rgbReserved = 0;
		for(k=0;k<nQ;++k){
			if( qQ.rgbBlue  == pQ[k].rgbBlue  && 
				qQ.rgbGreen == pQ[k].rgbGreen && 
				qQ.rgbRed   == pQ[k].rgbRed)   { pQNum[k]++; break;	}
		}
		if(k == nQ){
			pQ[k].rgbBlue = qQ.rgbBlue;
			pQ[k].rgbGreen= qQ.rgbGreen;
			pQ[k].rgbRed  = qQ.rgbRed;
			nQ++;
		}
	}
	
	BYTE* pNewDib=new BYTE[DibSize];//8BitColorDib
	
	BITMAPINFOHEADER* pIh;
	BYTE *pImg;
	pIh =	(BITMAPINFOHEADER*)(pNewDib);
	pIh->biSize				= sizeof(BITMAPINFOHEADER);
	pIh->biWidth			= pInfHd->biWidth; 
	pIh->biHeight			= pInfHd->biHeight; 
	pIh->biPlanes			= 1; 
	pIh->biBitCount			= 8; 
	pIh->biCompression		= 0; 
	pIh->biSizeImage		= ImgSize; 
	pIh->biXPelsPerMeter	= 0; 
	pIh->biYPelsPerMeter	= 0; 
	pIh->biClrUsed			= 256; 
	pIh->biClrImportant		= 0;

	BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pIh;

	pImg = pNewDib+HeadSize;//new BYTE[len1];

	/////CreatePalette();
	
	if(nQ>255){
	
//		AfxMessageBox("Color Number is big than 256!");
		int m;
		int* ord = new int[nQ];
	  	for(i=0;i<nQ;i++)	ord[i]=i;	//distance  number
	  	for(i=0;i<nQ;i++)
		{
			k = pQNum[ord[i]];
			for (j = i+1; j <nQ; j++)
	 			if ( k < pQNum[ord[j]] )
	   			{ 
	    			m = ord[j];	ord[j] = ord[i]; ord[i] = m;    
	  				k=pQNum[ord[i]];   
	  			} 
		}
		for(i=0;i<256;i++){
			pInfoH->bmiColors[i].rgbRed      = pQ[ord[i]].rgbRed;
			pInfoH->bmiColors[i].rgbGreen    = pQ[ord[i]].rgbGreen;
			pInfoH->bmiColors[i].rgbBlue     = pQ[ord[i]].rgbBlue;
			pInfoH->bmiColors[i].rgbReserved = 0;
		}
		nQ = 256;
		delete[]ord; ord=NULL;  
	}
	else{
		for(i = 0; i < 256; i++)
		{
			pInfoH->bmiColors[i].rgbRed      = pQ[i].rgbRed;
			pInfoH->bmiColors[i].rgbGreen    = pQ[i].rgbGreen;
			pInfoH->bmiColors[i].rgbBlue     = pQ[i].rgbBlue;
			pInfoH->bmiColors[i].rgbReserved = 0;
		}
	}
	for(i=0;i<h;++i)for(j=0;j<w;++j){
		qQ.rgbBlue	= p24Bits[i*EffWd24+j*3];
		qQ.rgbGreen = p24Bits[i*EffWd24+j*3+1];
		qQ.rgbRed	= p24Bits[i*EffWd24+j*3+2];
		pImg[i*EffWd8+j]=GetMostCloseColor(pInfoH->bmiColors,nQ,qQ);
	}
	delete	pQNum;	pQNum=NULL;
	delete	pQ;		pQ=NULL;
	return pNewDib;
}
int CImageBase::GetMostCloseColor(RGBQUAD *Ary,int n,RGBQUAD qQ)
{
	if(n<=1) return 0; 
	int i;
	int minNo=0;
	int b,g,r,dis,mindis;
	b = Ary[0].rgbBlue  - qQ.rgbBlue;
	g = Ary[0].rgbGreen - qQ.rgbGreen;
	r = Ary[0].rgbRed   - qQ.rgbRed;
	mindis = b*b+g*g+r*r;
	for(i=1;i<n;i++)
	{
		b = Ary[i].rgbBlue  - qQ.rgbBlue;
		g = Ary[i].rgbGreen - qQ.rgbGreen;
		r = Ary[i].rgbRed   - qQ.rgbRed;
		dis = b*b+g*g+r*r;
		if(mindis>dis){ mindis = dis; minNo = i; }
	}
	return minNo;
}

BYTE* CImageBase::CopyDib(BYTE* srcDib)
{
	if(srcDib == NULL)return NULL;
	BYTE* dstDib;
	int nSize = GetDibSize(srcDib);
	dstDib = new BYTE[nSize];
	memcpy(dstDib,srcDib,nSize);
	return dstDib;
}

BYTE* CImageBase::CropDib(BYTE* pDib,CRect& r)
{
	
	if(pDib == NULL) return NULL;

	BYTE* pBits = Get_lpBits(pDib);

	int w, h, bitCount, w1, h1,wB,wB1;
	int i,j;
	int s, ds, e, de, rem;

	bitCount = GetBitCount(pDib);
	GetWidthHeight(pDib,w,h);
	wB = (w*bitCount+31)/32*4;

	CRect r0(0,0,w,h);
	r &= r0;
	w1 = r.Width();
	h1 = r.Height();
	BYTE* pNewDib = MakeDib(w1,h1,bitCount);
	BYTE* pNewBits = Get_lpBits(pNewDib);
	wB1 = (w1*bitCount+31)/32*4;

	switch(bitCount) {
	case 24:
		for(i=r.top;i<r.bottom;i++)for(j=r.left;j<r.right;j++){
			pNewBits[(h1-1-(i-r.top))*wB1+3*(j-r.left)]   = pBits[(h-1-i)*wB+3*j];
			pNewBits[(h1-1-(i-r.top))*wB1+3*(j-r.left)+1] = pBits[(h-1-i)*wB+3*j+1];
			pNewBits[(h1-1-(i-r.top))*wB1+3*(j-r.left)+2] = pBits[(h-1-i)*wB+3*j+2];
		}
		break;
	case 8:
		for(i=r.top;i<r.bottom;++i)for(j=r.left;j<r.right;++j){
			pNewBits[(h1-1-(i-r.top))*wB1+j-r.left] = pBits[(h-1-i)*wB+j];
		}
		break;
	case 1:
		s = r.left/8;
		ds = r.left-s*8;
		e = r.right/8;
		de = r.right-e*8;
		rem = w1 % 8;

		for(i=r.top;i<r.bottom;++i)
		{
			int k,k1=0,k2=0;
			BYTE V = pBits[(h-1-i)*wB+s];
			BYTE V1 = 0;
			V = V<<ds;
			for(k=ds;k<8;k++)
			{
				if(V & 0x80) V1 |= 1;
				if(((k1+1) % 8) != 0)
					V1<<=1;
				else
				{
					pNewBits[(h1-1-(i-r.top))*wB1+k2] = V1;
					k2++;	V1 = 0;
				}

				V = V<<1;
				k1++;
			}
			for(j=s+1;j<e;j++)
			{
				V = pBits[(h-1-i)*wB+j];
				for(k=0;k<8;k++)
				{
					if(V & 0x80) V1 |= 1;
					if(((k1+1) % 8) != 0)
						V1<<=1;
					else
					{
						pNewBits[(h1-1-(i-r.top))*wB1+k2] = V1;
						k2++;	V1 = 0;
					}
					
					V = V<<1;
					k1++;
				}
			}
			V = pBits[(h-1-i)*wB+e];
			for(k=0;k<de;k++)
			{
				if(V & 0x80) V1 |= 1;
				if(((k1+1) % 8) != 0)
					V1<<=1;
				else
				{
					pNewBits[(h1-1-(i-r.top))*wB1+k2] = V1;
					k2++;	V1 = 0;
				}

				V = V<<1;
				k1++;
			}
			if(rem != 0)
			{
				V1 <<= 8 - rem-1;
				pNewBits[(h1-1-(i-r.top))*wB1+k2] = V1;
			}

		}
	}
	return pNewDib;
}
BYTE* CImageBase::CropImg(BYTE* pImg,int w,int h,CRect& r)
{
	if(pImg==NULL)return NULL;
	int i,j;
	CRect r0(0,0,w,h);
	r &= r0;
	int w1 = r.Width();
	int h1 = r.Height();
	if(w1*h1==0) return NULL;
	BYTE* pCropImg = new BYTE[w1*h1];
	for(i=r.top;i<r.bottom;++i)for(j=r.left;j<r.right;++j){
		pCropImg[(i-r.top)*w1+j-r.left] = pImg[i*w+j];
	}
	return pCropImg;
}
BOOL CImageBase::MergeCopyImgB2A(BYTE* pImgA,int wa,int ha,BYTE* pImgB,int wb,int hb,CPoint pos)
{
	if(pos.x+wb<0 || pos.x>=wa || pos.y+hb<0 || pos.y>=ha) return FALSE;
	if(pImgA==NULL || pImgB==NULL)  return FALSE;
	CRect realRect = CRect(0,0,wb,hb);
	CRect RectA = CRect(0,0,wa,ha);
	realRect += pos;
	realRect &= RectA;
	int i;
	int w = realRect.Width();
	int l = realRect.left;
	int t = realRect.top;
	int b = realRect.bottom;
	int dt = (pos.y<0) ? -pos.y: 0;
	int dl = (pos.x<0) ? -pos.x: 0;
	for(i=t;i<b;i++)
		memcpy(pImgA+i*wa+l,pImgB+(i-t+dt)*wb+dl,w);
	return TRUE;
}

BYTE* CImageBase::ZoomDib(BYTE* pDib, double zoomScale)
{
	if(pDib==NULL) return NULL;
	int new_w, new_h;
	LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER) pDib;
	int w = pBIH->biWidth;
	int h = pBIH->biHeight;
	new_w = (int)(w*zoomScale+0.5);
	new_h = (int)(h*zoomScale+0.5);
	return ZoomDib(pDib, new_w, new_h);
}
BYTE* CImageBase::ZoomDib(BYTE* pDib, int new_w, int new_h)
{
	if(pDib==NULL) return NULL;
	BYTE* pNewDib = NULL;
	LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER) pDib;
	int w,h;
	int i,j;
	BYTE *pImg=NULL,*pNewImg=NULL;
	BYTE *pImgR=NULL,*pImgG=NULL,*pImgB=NULL; 
	BYTE *pNewImgR=NULL,*pNewImgG=NULL,*pNewImgB=NULL; 

	switch(pBIH->biBitCount) {
	case 24:
		MakeRGBImgFrom24Dib(pDib, pImgR, pImgG, pImgB, w, h);
		pNewImgR = ZoomImg(pImgR, w, h, new_w, new_h);
		pNewImgG = ZoomImg(pImgG, w, h, new_w, new_h);
		pNewImgB = ZoomImg(pImgB, w, h, new_w, new_h);
		pNewDib = Make24DibFromRGBImg(pNewImgR, pNewImgG, pNewImgB, new_w, new_h);
		delete[]pImgR;     delete[]pImgG;     delete[]pImgB;
		delete[]pNewImgR; delete[]pNewImgG; delete[]pNewImgB;
		break;
	case 8:
		pImg = MakeImgFromGrayDib(pDib,w, h);
		pNewImg = ZoomImg(pImg, w, h, new_w, new_h);
		pNewDib = MakeGrayDibFromImg(pNewImg, new_w, new_h);
		delete[]pImg;     delete[]pNewImg;
		break;
	case 1:
		pImg = MakeGrayImgFromBinDib(pDib,w,h);
		pNewImg = ZoomImg(pImg, w, h, new_w, new_h);
		for(i=0;i<new_h;i++)for(j=0;j<new_w;j++)
			if(pNewImg[i*new_w+j]>128)
				pNewImg[i*new_w+j] = 0;
			else
				pNewImg[i*new_w+j] = 1;
		pNewDib = MakeBinDibFromImg(pNewImg, new_w, new_h);
		delete[]pImg;     delete[]pNewImg;
		break;
	}
	return pNewDib;
}
BYTE* CImageBase::ZoomOut24Dib(BYTE* pDib,int new_w,int new_h)
{
	if(pDib==NULL) return NULL;
	int nBitCount = GetBitCount(pDib);
	if(nBitCount!=24) return NULL;
	int w,h;
	GetWidthHeight(pDib,w,h);

	BYTE* pBits = Get_lpBits(pDib);
	int ByteW = (w*nBitCount+31)/32*4;

	BYTE* pNewDib = MakeDib(new_w, new_h, nBitCount);
	BYTE* pNewBits = Get_lpBits(pNewDib);
	int NewByteW = (new_w*24+31)/32*4;

	int i,j,ii,jj;
	int i_x,i_y,y,x;
	
	int xscale = 1000*w/new_w;
	int yscale = 1000*h/new_h;
	
	int win_w = (xscale+500)/1000;
	win_w = max(win_w,1);
	int win_h = (yscale+500)/1000;
	win_h = max(win_h,1);

	int stepX = win_w / 3;
	stepX = max(stepX,1);
	int stepY = win_h / 3;
	stepY = max(stepY,1);
	
	int valR,valG,valB;
	int num;
	for(i=0;i<new_h;i++)
	{
		i_y = (yscale * i)/1000;
		for(j=0; j<new_w; j++)
		{
			i_x = (xscale * j)/1000;
			valR = valG = valB = 0;
			num=0;
			for(ii=0;ii<win_h;ii+=stepY)	
			{
				y = i_y+ii;
				if(y>h-1) continue;
				for(jj=0;jj<win_w;jj+=stepX)
				{
					x = (i_x+jj);
					if(x>w-1) continue;
					valB += pBits[y*ByteW + 3*x];
					valG += pBits[y*ByteW + 3*x+1];
					valR += pBits[y*ByteW + 3*x+2];
					num++;
				}
			}
			if(num>0)
			{
				valR = valR/num;
				valG = valG/num;
				valB = valB/num;
			}
			valR = min(255,valR);
			valG = min(255,valG);
			valB = min(255,valB);
			pNewBits[i*NewByteW+3*j] = valB;
			pNewBits[i*NewByteW+3*j+1] = valG;
			pNewBits[i*NewByteW+3*j+2] = valR;
		}
	}
	return pNewDib;
}
BYTE* CImageBase::ZoomOutGrayDib(BYTE* pDib,int new_w,int new_h)
{
	if(pDib==NULL) return NULL;
	int nBitCount = GetBitCount(pDib);
	if(nBitCount!=8) return NULL;
	int w,h;
	GetWidthHeight(pDib,w,h);
	
	BYTE* pBits = Get_lpBits(pDib);
	int ByteW = (w*nBitCount+31)/32*4;
	
	BYTE* pNewDib = MakeDib(new_w, new_h, nBitCount);
	BYTE* pNewBits = Get_lpBits(pNewDib);
	int NewByteW = (new_w*nBitCount+31)/32*4;
	
	int i,j,ii,jj;
	int i_x,i_y,y,x;
	
	int xscale = 1000*w/new_w;
	int yscale = 1000*h/new_h;
	
	int win_w = (xscale+500)/1000;
	win_w = max(win_w,1);
	int win_h = (yscale+500)/1000;
	win_h = max(win_h,1);

	int stepX = win_w / 3;
	stepX = max(stepX,1);
	int stepY = win_h / 3;
	stepY = max(stepY,1);
	
	int val;
	int num;
	for(i=0;i<new_h;i++)
	{
		i_y = (yscale * i)/1000;
		for(j=0; j<new_w; j++)
		{
			i_x = (xscale * j)/1000;
			val = 0;
			num=0;
			for(ii=0;ii<win_h;ii+=stepY)	
			{
				y = i_y+ii;
				if(y>h-1) continue;
				for(jj=0;jj<win_w;jj+=stepX)
				{
					x = (i_x+jj);
					if(x>w-1) continue;
					val += pBits[y*ByteW + x];
					num++;
				}
			}
			if(num>0)
			{
				val = val*1000/num/1000;
			}
			val = min(255,val);
			pNewBits[i*NewByteW+j] = val;
		}
	}
	return pNewDib;
}
BYTE* CImageBase::ThumbnailBinDib(BYTE* pDib,int new_w,int new_h)
{
	if(pDib==NULL) return NULL;
	if(GetBitCount(pDib)!=1) return NULL;
	int w,h;
	GetWidthHeight(pDib,w,h);
	
	BYTE* pBits = Get_lpBits(pDib);
	int ByteW = (w+31)/32*4;
	
	BYTE* pNewDib = MakeDib(new_w, new_h, 8);
	BYTE* pNewBits = Get_lpBits(pNewDib);
	int NewByteW = (new_w*8+31)/32*4;
	
	int i,j,ii,jj;
	int i_x,i_y,y,x;
	
	int xscale = 1000*w/new_w;
	int yscale = 1000*h/new_h;
	
	int win_w = (xscale+500)/1000;
	win_w = max(win_w,1);
	int win_h = (yscale+500)/1000;
	win_h = max(win_h,1);
	
	int stepX = win_w / 3;
	stepX = max(stepX,1);
	int stepY = win_h / 3;
	stepY = max(stepY,1);
	
	int val;
	int num;
	for(i=0;i<new_h;i++)
	{
		i_y = (yscale * i)/1000;
		for(j=0; j<new_w; j++)
		{
			i_x = (xscale * j)/1000;
			val = 0;
			num=0;
			for(ii=0;ii<win_h;ii+=stepY)	
			{
				y = i_y+ii;
				if(y>h-1) continue;
				for(jj=0;jj<win_w;jj+=stepX)
				{
					x = (i_x+jj);
					if(x>w-1) continue;
					val += GetPx(pBits,ByteW, x, y);
					num++;
				}
			}
			if(num>0)
			{
				val = val*255/num;
			}
			val = min(255,val);
			pNewBits[i*NewByteW+j] = val;
		}
	}
	return pNewDib;
}
BYTE* CImageBase::Thumbnail(BYTE* pDib,int new_w,int new_h)
{
	if(pDib==NULL) return NULL;
	BYTE* pNewDib = NULL;
	LPBITMAPINFOHEADER pBIH = (LPBITMAPINFOHEADER) pDib;
	int w = pBIH->biWidth;
	int h = pBIH->biHeight;
	float xscale = (float)new_w/w;
	float yscale = (float)new_h/h;
	if(xscale<yscale)
		new_h =(int)(xscale*h);
	else
		new_w =(int)(yscale*w);
	new_h = max(new_h,1);
	new_w = max(new_w,1);


	switch(pBIH->biBitCount) {
	case 24:
		pNewDib = ZoomOut24Dib(pDib, new_w, new_h);
		break;
	case 8:
		pNewDib = ZoomOutGrayDib(pDib, new_w, new_h);
		break;
	case 1:
		pNewDib = ThumbnailBinDib(pDib, new_w, new_h);
		break;
	}
	return pNewDib;
}
BYTE* CImageBase::ZoomImg(BYTE* pImg,int& w,int& h,double zoomScale)
{
	if(pImg==NULL) return NULL;
	int new_w, new_h;
	new_w = (int)(w*zoomScale+0.5);
	new_h = (int)(h*zoomScale+0.5);
	BYTE* newImg = ZoomImg(pImg, w, h, new_w, new_h);
	w = new_w; h = new_h;
	return newImg;
}
/*
Name:ZoomImg
Function; Zoom binary and gray image
Input:
	pImg: Image pointer;
	w,h : width and height of original image 
	new_w,new_h : width and height of new image
Return:
	New image pointer(Gray Image)
Author: Kim M.I.
Date   2007/09/26
Update 2008/03/30
Update 2009/01/03
Update 2009/05/25
*/
BYTE* CImageBase::ZoomImg(BYTE *pImg,int w,int h,int new_w, int new_h)
{
	if(pImg == NULL) return NULL;
	
	///////X� ��Zoom嶮///////////////////////////////////////////////////////////////////
	BYTE *pNewImg_X = NULL;
	float xscale = (float)w/new_w;
	float yscale = (float)h/new_h;
	float scaleTh = 3.5;
	if(new_w == w && new_h == h)  //X,Y� ���1:1� �
	{
		BYTE* pNewImg = new BYTE[new_w*new_h];
		memcpy(pNewImg,pImg,new_w*new_h);
		return pNewImg;
	}
	else if(xscale<scaleTh && yscale<scaleTh)//X,Y� ������˼ � ��ײ��
	{
		return ZoomInImg(pImg, w, h, new_w,  new_h);
	}
	else if(xscale>=scaleTh && yscale>=scaleTh)//X,Y� ���ͱ��ײ��
	{
		return ZoomOutImg(pImg, w, h, new_w,  new_h);
	}
	else if(xscale>=scaleTh && yscale<scaleTh)//X� ���ͱ��װ�Y� ������˼ � ��ײ��
	{
		return ZoomXOutYInImg(pImg, w, h, new_w,  new_h);
	}
	else //if(xscale<scaleTh && yscale>=scaleTh)//Y� ���ͱ��װ�X� ������˼ � ��ײ��
	{
		return ZoomYOutXInImg(pImg, w, h, new_w,  new_h);
	}
}
BYTE* CImageBase::ZoomOutImg(BYTE *pImg,int w,int h,int new_w, int new_h) 
{
	if(pImg == NULL) return NULL;
	int i,j,ii,jj;
	int i_x,i_y,y,x;

	int xscale = 1000*w/new_w;
	int yscale = 1000*h/new_h;

	int win_w = (xscale+500)/1000;
	win_w = max(win_w,1);
	int win_h = (yscale+500)/1000;
	win_h = max(win_h,1);

	int stepX = win_w / 3;
	stepX = max(stepX,1);
	int stepY = win_h / 3;
	stepY = max(stepY,1);
	
	BYTE *pNewImg = new BYTE[new_w*new_h];
	if(pNewImg == NULL) return NULL;

	for(i=0;i<new_h;i++)
	{
		i_y = (yscale * i)/1000;
		for(j=0; j<new_w; j++)
		{ 
			i_x = (xscale * j)/1000;
			int newval = 0;
			int num=0;
			for(ii=0;ii<win_h;ii+=stepY)
			{
				y = i_y+ii;
				if(y>h-1) continue;
				for(jj=0;jj<win_w;jj+=stepX)
				{
					x = i_x+jj;
					if(x>w-1) continue;
					newval += pImg[y*w + x];
					num++;
				}
			}
			if(num>0)
				newval = newval/num;
			else
				newval = 0;
			newval = min(255,newval);
			pNewImg[i*new_w+j] = newval;
		}
	}

	return pNewImg;
}

BYTE* CImageBase::ZoomInImg(BYTE *pImg,int w,int h,int new_w, int new_h) 
{
	if(pImg == NULL) return NULL;

	BYTE *pNewImg = new BYTE[new_w*new_h];
	if(pNewImg == NULL) return NULL;

	int i,j;
	int i_x,i_y;
	int f_x,f_y,d_x,d_y;
	int val00,val01,val10,val11;

	int xscale = 1000*w/new_w;
	int yscale = 1000*h/new_h;

	BYTE *pOrgPlusImg = new BYTE[(w+2)*(h+2)];
	memset(pOrgPlusImg,0,(w+2)*(h+2));
	for(i=1;i<=h;i++)
	{
		memcpy(pOrgPlusImg+i*(w+2)+1, pImg+(i-1)*w, w);
	}

	for(i=0;i<new_h;i++)
	{
		f_y = yscale * i + yscale / 2 + 500;
		i_y = f_y/1000;
		d_y = f_y - i_y*1000; 
		for(j=0; j<new_w; j++)
		{
			f_x = xscale * j + xscale / 2 + 500;
			i_x = f_x/1000;
			d_x = f_x - i_x*1000; 

			val00 = pOrgPlusImg[i_y*(w+2) + i_x];
			val01 = pOrgPlusImg[i_y*(w+2) + (i_x+1)];
			val10 = pOrgPlusImg[(i_y+1)*(w+2) + i_x];
			val11 = pOrgPlusImg[(i_y+1)*(w+2) + (i_x+1)];

			int newval = (int)((val00 * (1000-d_y) *  (1000-d_x) +
					 	        val01 * (1000-d_y) *      d_x    +
						        val10 *     d_y    *  (1000-d_x) +
						        val11 *     d_y    *      d_x  ));
			newval /=1000000; 
			if(newval > 255) newval = 255;
			pNewImg[i*new_w+j] = newval;
		}
	}
	delete[] pOrgPlusImg;
	return pNewImg;
}
BYTE* CImageBase::ZoomYOutXInImg(BYTE *pImg,int w,int h,int new_w, int new_h) 
{
	int i,j,k;
	int win_h , newval, num;
	int i_x, i_y, y;
	float f_x, d_x;
	int val1,val2;
	
	if(pImg == NULL) return NULL;
	
	///////X� ��Zoom嶮///////////////////////////////////////////////////////////////////
	BYTE *pNewImg_X = NULL;
	float xscale = (float)w/new_w;
	float yscale = (float)h/new_h;
	
	BYTE* pNewImg = NULL;
	pNewImg = new BYTE[new_w*new_h];
	win_h = (int)(yscale+0.5);
	for(i=0; i<new_w; i++)
	{
		f_x = xscale * i + xscale / 2 + 0.5f;
		i_x = (int)f_x;    d_x = f_x - i_x;
		if(i_x<=0)
		{
			for(j=0; j<new_h; j++)
			{
				i_y = (int)(yscale * j);
				newval = 0; num = 0;
				for(k=0;k<win_h;k++)
				{
					y = i_y+k;
					if(y>h-1) continue;
					newval += pImg[y*w];
					num++;
				}
				if(num>0)
					newval =(int)((float)newval/num);
				else
					newval = 0;
				newval = min(255,newval);
				pNewImg[j*new_w+i] = newval;
			}
		}
		else if(i_x>=w)
		{
			for(j=0; j<new_h; j++)
			{
				i_y = (int)(yscale * j);
				newval = 0; num = 0;
				for(k=0;k<win_h;k++)
				{
					y = i_y+k;
					if(y>h-1) continue;
					newval += pImg[y*w+w-1];
					num++;
				}
				if(num>0)
					newval =(int)((float)newval/num);
				else
					newval = 0;
				newval = min(255,newval);
				pNewImg[j*new_w+i] = newval;
			}
		}
		else
		{
			for(j=0; j<new_h; j++)
			{
				i_y = (int)(yscale * j);
				newval = 0; num = 0;
				for(k=0;k<win_h;k++)
				{
					y = i_y+k;
					if(y>h-1) continue;
					val1 = pImg[y*w + i_x-1];
					val2 = pImg[y*w + i_x];
					newval += (int)(val1 * (1.0f-d_x) + val2 * d_x);
					num++;
				}
				if(num>0)
					newval =(int)((float)newval/num);
				else
					newval = 0;
				newval = min(255,newval);
				pNewImg[j*new_w+i] = newval;
			}
		}
	}
	return pNewImg;
}

BYTE* CImageBase::ZoomXOutYInImg(BYTE *pImg,int w,int h,int new_w, int new_h) 
{
	int i,j,k;
	int win_w, newval, num;
	int i_x, i_y, x;
	float f_y, d_y;
	int val1,val2;
	float xscale = (float)w/new_w;
	float yscale = (float)h/new_h;


	BYTE* pNewImg = new BYTE[new_w*new_h];
	win_w = (int)(xscale+0.5);

	for(i=0; i<new_h; i++)
	{
		f_y = yscale * i + yscale / 2 + 0.5f;
		i_y = (int)f_y;    d_y = f_y - i_y;
		if(i_y<=0)
		{
			for(j=0; j<new_w; j++)
			{
				i_x = (int)(xscale * j);
				newval = 0; num = 0;
				for(k=0;k<win_w;k++)
				{
					x = i_x+k;
					if(x>w-1) continue;
					newval += pImg[x];
					num++;
				}
				if(num>0)
					newval =(int)((float)newval/num);
				else
					newval = 0;
				newval = min(255,newval);
				pNewImg[i*new_w+j] = newval;
			}
		}
		else if(i_y>=h)
		{
			for(j=0; j<new_w; j++)
			{
				i_x = (int)(xscale * j);
				newval = 0; num = 0;
				for(k=0;k<win_w;k++)
				{
					x = i_x+k;
					if(x>w-1) continue;
					newval += pImg[(h-1)*w+x];
					num++;
				}
				if(num>0)
					newval =(int)((float)newval/num);
				else
					newval = 0;
				newval = min(255,newval);
				pNewImg[i*new_w+j] = newval;
			}
		}
		else
		{
			for(j=0; j<new_w; j++)
			{
				i_x = (int)(xscale * j );
				newval = 0; num = 0;
				for(k=0;k<win_w;k++)
				{
					x = i_x+k;
					if(x>w-1) continue;
					val1 = pImg[(i_y-1)*w + x];
					val2 = pImg[i_y*w + x];
					newval += (int)(val1 * (1.0f-d_y) + val2 * d_y);
					num++;
				}
				if(num>0)
					newval =(int)((float)newval/num);
				else
					newval = 0;
				newval = min(255,newval);
				pNewImg[i*new_w+j] = newval;
			}
		}
	}
	return pNewImg;
}

void CImageBase::RGBtoYIQ(BYTE R,BYTE G,BYTE B,BYTE& Y,BYTE& I,BYTE& Q)
{
	Y = (int)( 0.2992f * R + 0.5868f * G + 0.1140f * B);
	I = (int)( 0.5960f * R - 0.2742f * G - 0.3219f * B + 128);
	Q = (int)( 0.2109f * R - 0.5229f * G + 0.3120f * B + 128);


}
void CImageBase::ConvertRGBImgToYIQImg(BYTE *pImgR,BYTE *pImgG,BYTE *pImgB, int w, int h, BYTE*& pImgY,BYTE*& pImgI,BYTE*& pImgQ)
{
	int i;
	pImgY = new BYTE[w*h];
	pImgI = new BYTE[w*h];
	pImgQ = new BYTE[w*h];
	BYTE R,G,B,Y,I,Q;
	for (i=0 ;i<w*h ; i++)
	{
		R = pImgR[i];
		G = pImgG[i];
		B = pImgB[i];
		RGBtoYIQ(R,G,B,Y,I,Q);
		pImgY[i] = Y;
		pImgI[i] = I;
		pImgQ[i] = Q;
	}
}

BYTE* CImageBase::ZipBinBits(BYTE *pBits, int len, int *Ziplen)
{
	BYTE* pZipBits;
	pZipBits = new BYTE[len];
	int a=0;
	int b = 0;
	int c=0;
	int d=0;

	int i;
	int ziplen = 0;
	BYTE FFlen=0;
	BYTE OOlen =0;
	int e=0;
	BOOL memoryExtend = FALSE;
	for(i=0; i<len; i++)
	{
		if(ziplen+10>=len && !memoryExtend)
		{
			BYTE* tempBits = new BYTE[len];
			memcpy(tempBits,pZipBits,ziplen*sizeof(BYTE));
			delete pZipBits;
			pZipBits = new BYTE[int(len*1.5)];
			memcpy(pZipBits,tempBits,ziplen);
			delete tempBits;
			memoryExtend = TRUE;
			//continue;
		}
		if(pBits[i]==0x00)
		{
			if(FFlen!=0)
			{
				pZipBits[ziplen++] = FFlen;
				FFlen = 0;
			}
			if( OOlen==0 )
			{
				pZipBits[ziplen++] = 0x00;
				e=1;
				OOlen++;
				a++;
				d++;
				continue;
			}
			if(OOlen>0 && OOlen<253)
			{
				OOlen++;
				a++;
				continue;
			}
			if(OOlen==253)
			{
				OOlen++;
				if(e==1)
					e=0;
				else
					e=0;

				pZipBits[ziplen++] = OOlen;
				
				OOlen = 0;
				a++;
				b+=OOlen;
				c++;
				continue;
			}
		}
		else
		{
			if( OOlen!=0)
			{
				pZipBits[ziplen++] = OOlen;
				if(e==1)
					e=0;
				else
					e=0;
				b+=OOlen;
				c++;
				OOlen = 0;
			}
			if(pBits[i]==0xff && FFlen==0)
			{
				pZipBits[ziplen++] = 0xff;
				FFlen++;
				continue;
			}
			if(pBits[i]==0xff && FFlen>0 && FFlen<254)
			{
				FFlen++;
				continue;
			}
			if(pBits[i]==0xff && FFlen==254)
			{
				FFlen++;
				pZipBits[ziplen++] = FFlen;
				FFlen = 0;
				continue;
			}

			if(pBits[i]!=0xff && FFlen!=0)
			{
				pZipBits[ziplen++] = FFlen;
				FFlen = 0;
				pZipBits[ziplen++] = pBits[i];
				continue;
			}

			if(pBits[i]!=0xff && FFlen==0)
			{
				pZipBits[ziplen++] = pBits[i];
				continue;
			}
		}

	}
	if(FFlen!=0)
	{
			pZipBits[ziplen++] = FFlen;
	}
	if(OOlen!=0)
	{
			pZipBits[ziplen++] = OOlen;
			b+=OOlen;
	}

	(*Ziplen) = ziplen;

	return pZipBits;
}
int CImageBase::GetZipLen(BYTE *pBits, int len)
{

	int ziplen = 0;
	BYTE FFlen=0;
	BYTE OOlen = 0;
	int i;
	for(i=0; i<len; i++)
	{
		if(pBits[i]==0x00)
		{
			if(FFlen!=0)
			{
				ziplen++;
				FFlen = 0;
			}
			if( OOlen==0 )
			{
				ziplen++;
				OOlen++;
				continue;
			}
			if(OOlen>0 && OOlen<253)
			{
				OOlen++;
				continue;
			}
			if(OOlen==253)
			{
				OOlen++;
				ziplen++;
				OOlen = 0;
				continue;
			}
		}
		else
		{
			if( OOlen!=0)
			{
				ziplen++;
				OOlen = 0;
			}
			if(pBits[i]==0xff && FFlen==0)
			{
				ziplen++;
				FFlen++;
				continue;
			}
			if(pBits[i]==0xff && FFlen>0 && FFlen<254)
			{
				FFlen++;
				continue;
			}
			if(pBits[i]==0xff && FFlen==254)
			{
				FFlen++;
				ziplen++;
				FFlen = 0;
				continue;
			}

			if(pBits[i]!=0xff && FFlen!=0)
			{
				ziplen++;
				FFlen = 0;
				ziplen++;
				continue;
			}

			if(pBits[i]!=0xff && FFlen==0)
			{
				ziplen++;
				continue;
			}
		}

	}
	if(FFlen!=0)
	{
			ziplen++;
	}
	if(OOlen!=0)
	{
			ziplen++;
	}

	return ziplen;
}

BYTE* CImageBase::UnZipBinBits(BYTE *pZipBits, int Ziplen,int len)
{
	int Bitslen = 0;
	BYTE* pBits;
	int a = 0;
	int b=0;
	pBits = new BYTE[len];

	BYTE FFlen = 0;
	BYTE OOlen = 0;
	int i;
	BYTE j;
	for(i=0;i<Ziplen;i++)
	{
		if(pZipBits[i]==0x00)
		{
			b++;
			i=i+1;
			OOlen = pZipBits[i];
			for(j=0;j<OOlen;j++)
			{
				pBits[Bitslen++] = 0x00;
				a++;
			}
			continue;
		}
		if(pZipBits[i]==0xff)
		{
			i=i+1;
			FFlen = pZipBits[i];
			for(j=0;j<FFlen;j++)
			{
				pBits[Bitslen++] = 0xff;
			}
			continue;
		}
		if(pZipBits[i]!=0xff)
		{
			pBits[Bitslen++] = pZipBits[i];
			continue;
		}
	}
	return pBits;
}
int CImageBase::GetUnZipLen(BYTE *pZipBits, int Ziplen)
{
	int Bitslen = 0;
	BYTE FFlen = 0;
	BYTE OOlen = 0;
	int i;
	for(i=0;i<Ziplen;i++)
	{
		if(pZipBits[i]==0x00)
		{
			i=i+1;
			OOlen = pZipBits[i];
			Bitslen += OOlen;
			continue;
		}
		if(pZipBits[i]==0xff)
		{
			i=i+1;
			FFlen = pZipBits[i];
			Bitslen += FFlen;
			continue;
		}
		if(pZipBits[i]!=0xff)
		{
			Bitslen++;
			continue;
		}
	}
	return Bitslen;
}

/*BYTE* CImageBase::MakeDibFromBitmap(CBitmap* pBitmap)
{
	BITMAP bmp;
	pBitmap->GetBitmap(&bmp);
	int w = bmp.bmWidth;
	int h = bmp.bmHeight;
	int nSizeImage=h*bmp.bmWidthBytes;
	BYTE* pBits = new BYTE[nSizeImage];
	pBitmap->GetBitmapBits(nSizeImage, pBits);

	int biClrUsed ;
	if(bmp.bmBitsPixel == 1)		biClrUsed	= 2; 
	else if(bmp.bmBitsPixel == 8)	biClrUsed	= 256; 
	else							biClrUsed	= 0; 

	int nWidByte = (w*bmp.bmBitsPixel+31)/32*4;
	int	ImgSize=nWidByte*h;
	int HeadSize= sizeof(BITMAPINFOHEADER) +	sizeof(RGBQUAD) * biClrUsed;
	int DibSize=HeadSize+ImgSize;
	BYTE *NewDIB=new BYTE[DibSize];
	
	BITMAPINFOHEADER* pBIH;
			

	pBIH =	(BITMAPINFOHEADER*)NewDIB;
	pBIH->biSize				= sizeof(BITMAPINFOHEADER);
	pBIH->biWidth			= w; 
	pBIH->biHeight			= h; 
	pBIH->biPlanes			= 1; 
	pBIH->biBitCount		= bmp.bmBitsPixel; 
	pBIH->biCompression		= 0; 
	pBIH->biSizeImage		= ImgSize; 
	pBIH->biXPelsPerMeter	= 0; 
	pBIH->biYPelsPerMeter	= 0; 
	pBIH->biClrUsed			= biClrUsed;
	pBIH->biClrImportant	= 0;

	BYTE* pNewBits = NewDIB+HeadSize;
	int i,j;
	for(i = 0; i < h; i++)for(j = 0; j < bmp.bmWidthBytes; j++)
	     pNewBits[nWidByte*(h-i-1)+j] = ~pBits[i*bmp.bmWidthBytes+j];

	delete[] pBits;pBits = NULL;

	BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pBIH;
	
	if(biClrUsed == 256){
		for(i=0;i<biClrUsed;++i){
			pInfoH->bmiColors[0].rgbRed      = i;
			pInfoH->bmiColors[0].rgbGreen    = i;
			pInfoH->bmiColors[0].rgbBlue     = i;
			pInfoH->bmiColors[0].rgbReserved = 0;
		}
	}
	else if(biClrUsed == 2){
		pInfoH->bmiColors[0].rgbRed      = 0;
		pInfoH->bmiColors[0].rgbGreen    = 0;
		pInfoH->bmiColors[0].rgbBlue     = 0;
		pInfoH->bmiColors[0].rgbReserved = 0;
		
		pInfoH->bmiColors[1].rgbRed      = 255;
		pInfoH->bmiColors[1].rgbGreen    = 255;
		pInfoH->bmiColors[1].rgbBlue     = 255;
		pInfoH->bmiColors[1].rgbReserved = 0;
	}

	return NewDIB;
}
*/
BOOL CImageBase::RemoveRect24Dib(BYTE* pDib, CRect rect,RGBQUAD rgbquad)
{
	if(pDib == NULL) return FALSE;
	int nBitCount = GetBitCount(pDib);
	if(nBitCount != 24) return FALSE;
	int w,h;
	GetWidthHeight(pDib,w,h);
	int bw = (w*nBitCount+31)/32*4;
	BYTE* pBits = Get_lpBits(pDib);
	
	int i,j;
	rect &= CRect(0,0,w,h);
	int l = rect.left;
	int r = rect.right;
	int t = rect.top;
	int b = rect.bottom;
	

	for(i=t;i<b;i++) for(j=l;j<r;j++)
	{
		pBits[(h-1-i)*bw+3*j]   = rgbquad.rgbBlue;
		pBits[(h-1-i)*bw+3*j+1] = rgbquad.rgbGreen;
		pBits[(h-1-i)*bw+3*j+2] = rgbquad.rgbRed;
	}
	return TRUE;
}
BOOL CImageBase::RemoveRectGrayDib(BYTE* pDib, CRect rect, BYTE val)
{
	if(pDib == NULL) return FALSE;
	int nBitCount = GetBitCount(pDib);
	if(nBitCount != 8) return FALSE;
	int w,h;
	GetWidthHeight(pDib,w,h);
	int bw = (w*nBitCount+31)/32*4;
	BYTE* pBits = Get_lpBits(pDib);
	
	int i,j;
	rect &= CRect(0,0,w,h);
	int l = rect.left;
	int r = rect.right;
	int t = rect.top;
	int b = rect.bottom;
	
	for(i=t;i<b;i++) for(j=l;j<r;j++)
		pBits[(h-1-i)*bw+j]   = val;

	return TRUE;
}
BOOL CImageBase::RemoveRectBinDib(BYTE* pDib, CRect rect)
{
	static BYTE Mask[] = {0xFF,0x7F,0x3F,0x1F,0x0F,0x07,0x03,0x01};

	if(pDib == NULL) return FALSE;
	int nBitCount = GetBitCount(pDib);
	if(nBitCount != 1) return FALSE;
	int w,h;
	GetWidthHeight(pDib,w,h);
	int bw = (w*nBitCount+31)/32*4;
	BYTE* pBits = Get_lpBits(pDib);
	
	int i,j;
	rect &= CRect(0,0,w,h);
	int l = rect.left;
	int r = rect.right;
	int t = rect.top;
	int b = rect.bottom;
	
	int s = l/8;
	int ds = l-s*8;
	int e = r/8;
	int de = r-e*8;

	BYTE M1 = Mask[ds];
	BYTE M2 = 255-Mask[de];
	for(i=t;i<b;i++)
	{
		pBits[(h-1-i)*bw+s] |= M1;
		pBits[(h-1-i)*bw+e] |= M2;
		for(j=s+1;j<e;j++)
			pBits[(h-1-i)*bw+j] = 0xff;
	}
	return TRUE;
}
RGBQUAD CImageBase::GetBkClrInRect24Dib(BYTE* pDib, CRect rect)
{
	RGBQUAD rgbquad;
	rgbquad.rgbRed = rgbquad.rgbBlue = rgbquad.rgbGreen = 255;
	if(pDib == NULL) return rgbquad;
	int nBitCount = GetBitCount(pDib);
	if(nBitCount != 24) return rgbquad;
	int w,h;
	GetWidthHeight(pDib,w,h);
	int bw = (w*nBitCount+31)/32*4;
	BYTE* pBits = Get_lpBits(pDib);
	
	int i,j;
	rect = CRect(0,0,w,h);
	int l = rect.left;
	int r = rect.right;
	int t = rect.top;
	int b = rect.bottom;
	__int64 num = (r-l)*(b-t);
	if(num == 0) return rgbquad;
	int HistR[256],HistG[256],HistB[256];
	memset(HistR, 0, sizeof(int)*256);
	memset(HistG, 0, sizeof(int)*256);
	memset(HistB, 0, sizeof(int)*256);
	
	for(i=t;i<b;i++) for(j=l;j<r;j++)
	{
		HistB[pBits[(h-1-i)*bw+3*j]]++;
		HistG[pBits[(h-1-i)*bw+3*j+1]]++;
		HistR[pBits[(h-1-i)*bw+3*j+2]]++;
	}
	
	int meanvalR, meanvalG, meanvalB;
	double sumR, sumG, sumB;
	sumR = sumG = sumB = 0;

	const double c_fDivBuffer = 100000.f;

	for(i=0;i<256;i++)
	{
		sumR += i * (HistR[i] / c_fDivBuffer);
		sumG += i * (HistG[i] / c_fDivBuffer);
		sumB += i * (HistB[i] / c_fDivBuffer);
	}
	meanvalR = (int)(sumR / num * c_fDivBuffer);
	meanvalG = (int)(sumG / num * c_fDivBuffer);
	meanvalB = (int)(sumB / num * c_fDivBuffer);
	
	num = 0;
	sumR = sumG = sumB = 0;
	for(i=255;i>=meanvalR;i--)
	{
		sumR += i * (HistR[i] / c_fDivBuffer);
		num += HistR[i];
	}
	if(num == 0)
	{
		sumR = 255 / c_fDivBuffer;
		num = 1;
	}
	rgbquad.rgbRed = BYTE(max(0,min(255,sumR / num * c_fDivBuffer)));
	
	num = 0;
	for(i=255;i>=meanvalG;i--)
	{
		sumG += i * (HistG[i] / c_fDivBuffer);
		num += HistG[i];
	}
	if(num == 0)
	{
		num = 1;
		sumG = 255 / c_fDivBuffer;
	}
	rgbquad.rgbGreen = BYTE(max(0,min(255,sumG / num * c_fDivBuffer)));
	
	num = 0;
	for(i=255;i>=meanvalB;i--)
	{
		sumB += i * (HistB[i] / c_fDivBuffer);
		num += HistB[i];
	}
	if(num == 0)
	{
		sumB = 255 / c_fDivBuffer;
		num = 1;
	}
	rgbquad.rgbBlue = BYTE(max(0,min(255,sumB / num * c_fDivBuffer)));
	
	return rgbquad;
}
BYTE CImageBase::GetBkClrInRectGrayDib(BYTE* pDib, CRect rect)
{
	BYTE BkVal = 255;
	if(pDib == NULL) return BkVal;
	int nBitCount = GetBitCount(pDib);
	if(nBitCount != 8) return BkVal;
	int w,h;
	GetWidthHeight(pDib,w,h);
	int bw = (w*nBitCount+31)/32*4;
	BYTE* pBits = Get_lpBits(pDib);

	int i,j;
	rect = CRect(0,0,w,h);
	int l = rect.left;
	int r = rect.right;
	int t = rect.top;
	int b = rect.bottom;
	int num = (r-l)*(b-t);
	if(num == 0) return BkVal;
	int Hist[256];
	memset(Hist, 0, sizeof(int)*256);

	for(i=t;i<b;i++) for(j=l;j<r;j++)
		Hist[pBits[(h-1-i)*bw+j]]++;
	

	const double c_fDivBuffer = 100000.f;

	int meanval;
	double sum = 0;
	for(i=0;i<256;i++)
		sum += i * (Hist[i] / c_fDivBuffer);
	meanval = (int)(sum / num * c_fDivBuffer);
	sum = 0; num = 0;
	for(i=255;i>=meanval;i--)
	{
		sum += i * (Hist[i] / c_fDivBuffer);
		num += Hist[i];
	}
	if(num == 0)
	{
		sum = 255 / c_fDivBuffer;
		num = 1;
	}
	BkVal = max(0,min(255,(int)(sum / num * c_fDivBuffer)));
	
	return BkVal;
}
BYTE CImageBase::GetBkClrInRectImg(BYTE* pImg,int w,int h, CRect rect)
{
	int i,j;
	if(pImg == NULL) return FALSE;
	rect &= CRect(0,0,w,h);
	int l = rect.left;
	int r = rect.right;
	int t = rect.top;
	int b = rect.bottom;
	int num = (r-l)*(b-t);
	if(num == 0) return 0;
	int Hist[256];
	memset(Hist, 0, sizeof(int)*256);
	for(i=t;i<b;i++) for(j=l;j<r;j++)
		Hist[pImg[i*w+j]]++;

	int meanval, sum = 0;
	for(i=0;i<256;i++)
		sum += i*Hist[i];
	meanval = sum/num;

	num = 0;
	sum = 0;
	for(i=255;i>=meanval;i--)
	{
		sum += i*Hist[i];
		num += Hist[i];
	}
	meanval = sum/num;
	return meanval;
}

BOOL CImageBase::RegionRemoveBinImg(BYTE* pImg,int w,int h, CRect rect)
{
	int i,j;
	if(pImg == NULL) return FALSE;
	rect &= CRect(0,0,w,h);
	int l = rect.left;
	int r = rect.right;
	int t = rect.top;
	int b = rect.bottom;
	for(i=t;i<b;i++) for(j=l;j<r;j++)
		pImg[i*w+j] = 0;
	return TRUE;
}
BOOL CImageBase::RegionRemoveImg(BYTE* pImg,int w,int h, CRect rect)
{
	int i,j;
	if(pImg == NULL) return FALSE;
	rect &= CRect(0,0,w,h);
	BYTE BkVal = GetBkClrInRectImg(pImg, w, h, rect);
	int l = rect.left;
	int r = rect.right;
	int t = rect.top;
	int b = rect.bottom;
	for(i=t;i<b;i++) for(j=l;j<r;j++)
		pImg[i*w+j] = BkVal;

	return TRUE;
}
BOOL CImageBase::RemoveRectDib(BYTE* pDib, CRect rect)
{
	if(pDib == NULL) return FALSE;
	int nBitCount = GetBitCount(pDib);
	if(nBitCount == 24)
	{
		RGBQUAD rgbquad = GetBkClrInRect24Dib(pDib,rect);
		return RemoveRect24Dib(pDib,rect,rgbquad);	
	}
	else if(nBitCount == 8)
	{
		BYTE BkVal = GetBkClrInRectGrayDib(pDib,rect);
		return RemoveRectGrayDib(pDib,rect,BkVal);	
	}
	else if(nBitCount == 1)
	{
		return RemoveRectBinDib(pDib,rect);	
	}
	else 
		return FALSE;

	return TRUE;
}

BOOL CImageBase::GetWeightCenter(BYTE* pDib,int& x,int& y)
{
	if(pDib == NULL) return FALSE;
	int nBitCount = GetBitCount(pDib);
	int w,h,i,j;
	long sum=0, sumx=0, sumy=0;

	GetWidthHeight(pDib,w,h);
	int bw = (w*nBitCount+31)/32*4;
	BYTE* pBits = Get_lpBits(pDib);
	if(nBitCount == 24)
	{
		for(i=0;i<h;i++) for(j=0;j<w;j++)
		{
			int val = RGB2GRAY(pBits[(h-1-i)*bw+3*j+2],pBits[(h-1-i)*bw+3*j+1],pBits[(h-1-i)*bw+3*j]);
			val = 255-min(255,max(0,val));
			sum += val;
			sumx += val*j;
			sumy += val*i;
		}
	}
	else if(nBitCount == 8)
	{
		for(i=0;i<h;i++) for(j=0;j<w;j++)
		{
			int val = pBits[(h-1-i)*bw+j];
			val = 255-min(255,max(0,val));
			sum += val;
			sumx += val*j;
			sumy += val*i;
		}
	}
	else if(nBitCount == 1)
	{
		BYTE* pImg = MakeImgFromBinBits(pBits,w,h);
		for(i=0;i<h;i++) for(j=0;j<w;j++)
		{
			int val = pImg[i*w+j];
			val = min(1,max(0,val));
			sum += val;
			sumx += val*j;
			sumy += val*i;
		}
		delete[] pImg;
	}
	else 
		return FALSE;
	
	x = (int)(sumx / sum);
	y = (int)(sumy / sum);
	return TRUE;
}
BOOL CImageBase::TranslateDib(BYTE* pDib,int dx,int dy)
{
	if(pDib == NULL) return FALSE;
	int nBitCount = GetBitCount(pDib);
	int w,h,i,j,ii,jj;
	
	
	GetWidthHeight(pDib,w,h);
	int bw = (w*nBitCount+31)/32*4;
	BYTE* pBits = Get_lpBits(pDib);
	BYTE* pNewDib = NULL;
	if(nBitCount == 24)
	{
		pNewDib = MakeDib(w,h,nBitCount);
		BYTE* pNewBits = Get_lpBits(pNewDib);
		RGBQUAD rgbquad = GetBkClrInRect24Dib(pDib,CRect(0,0,w,h));
		for(i=0;i<h;i++)for(j=0;j<w;j++)
		{
			ii = i - dy; jj = j - dx;
			if(ii<0 || ii>=h || jj<0 || jj>=w)
			{
				pNewBits[(h-1-i)*bw+3*j]   = rgbquad.rgbBlue;
				pNewBits[(h-1-i)*bw+3*j+1] = rgbquad.rgbGreen;
				pNewBits[(h-1-i)*bw+3*j+2] = rgbquad.rgbRed;
			}
			else
			{
				pNewBits[(h-1-i)*bw+3*j]   = pBits[(h-1-ii)*bw+3*jj];
				pNewBits[(h-1-i)*bw+3*j+1] = pBits[(h-1-ii)*bw+3*jj+1];
				pNewBits[(h-1-i)*bw+3*j+2] = pBits[(h-1-ii)*bw+3*jj+2];
			}

		}
	}
	else if(nBitCount == 8)
	{
		pNewDib = MakeDib(w,h,nBitCount);
		BYTE* pNewBits = Get_lpBits(pNewDib);
		BYTE BkVal = GetBkClrInRectGrayDib(pDib,CRect(0,0,w,h));
		for(i=0;i<h;i++)for(j=0;j<w;j++)
		{
			ii = i - dy; jj = j - dx;
			if(ii<0 || ii>=h || jj<0 || jj>=w)
				pNewBits[(h-1-i)*bw+j] = BkVal;
			else
				pNewBits[(h-1-i)*bw+j] = pBits[(h-1-ii)*bw+jj];
		}
	}
	else if(nBitCount == 1)
	{
		BYTE* pImg = MakeImgFromBinBits(pBits,w,h);
		BYTE* pNewImg = new BYTE[w*h];
		for(i=0;i<h;i++)for(j=0;j<w;j++)
		{
			ii = i - dy; jj = j - dx;
			if(ii<0 || ii>=h || jj<0 || jj>=w)
				pNewImg[i*w+j] = 0;
			else
				pNewImg[i*w+j] = pImg[ii*w+jj];
		}
		pNewDib = MakeBinDibFromImg(pNewImg,w,h);
		delete[] pImg;
		delete[] pNewImg;
	}
	else
		return FALSE;

	memcpy(pDib,pNewDib,GetDibSize(pNewDib));
	delete[] pNewDib;

	return TRUE;
}
BOOL CImageBase::OptimizeContrastImg(BYTE* pImg,int w,int h)
{
	if(pImg == NULL) return FALSE;
	BYTE MaxV=0,MinV=255;
	int i,j;
	for(i=0;i<h;i++)for(j=0;j<w;j++)
	{
		MaxV = max(pImg[i*w+j], MaxV);
		MinV = min(pImg[i*w+j], MinV);
	}
	if(MaxV<=MinV) return FALSE;
	for(i=0;i<h;i++)for(j=0;j<w;j++)
		pImg[i*w+j] = (pImg[i*w+j] - MinV) * 255 / (MaxV-MinV);

	return TRUE;

}
