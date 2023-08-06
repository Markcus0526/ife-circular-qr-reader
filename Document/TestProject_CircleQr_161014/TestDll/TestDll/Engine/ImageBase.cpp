// ImageBase.cpp: implementation of the CImageBase class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "ImageBase.h"


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
BYTE* CImageBase::MakeDIBFromDib(BYTE* pDib)
{
	int w,h,bpp,wstep;
	CImageBase::GetDibInfo(pDib,w,h,bpp,wstep);
	int DibSize = GetDibSize(w, h, bpp);
	int DIBSize = sizeof(BITMAPFILEHEADER)+DibSize;
	BYTE* pDIB = new BYTE[DIBSize];
	
	int FileSize,ImgSize;
	int HeadSize;
	int QuadSize;
	BITMAPFILEHEADER* pBFH = (BITMAPFILEHEADER*)pDIB;
	BITMAPINFOHEADER* pBIH  = (BITMAPINFOHEADER*)pDib;
	ImgSize = pBIH->biSizeImage;//GetBmpSize(w,h,lpBIH->biBitCount);
	if(bpp == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(bpp == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(bpp == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(bpp == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else				QuadSize = 0;//24
	HeadSize = min(14,sizeof(BITMAPFILEHEADER)) + sizeof(BITMAPINFOHEADER)+QuadSize;
	FileSize = HeadSize+ImgSize;
	pBFH->bfType = 0x4d42;     //unsigned short    bfType;
	pBFH->bfSize = FileSize;   //unsigned int	     bfSize;
	pBFH->bfReserved1 = 0;     //unsigned short    bfReserved1;
	pBFH->bfReserved2 = 0;     //unsigned short    bfReserved2;
	pBFH->bfOffBits = HeadSize;//unsigned int      bfOffBits;
	BYTE* pDib1 = pDIB+sizeof(BITMAPFILEHEADER);
	memcpy(pDib1,pDib,DibSize);
	return pDIB;
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
	int i,j;
	for(i=0;i<h;i++) for(j=0;j<w;j++)
	{
		BYTE b = pBits[widByte*i + j*3];
		BYTE g = pBits[widByte*i + j*3+1];
		BYTE r = pBits[widByte*i + j*3+2];
		GrayImg[w*(h-1-i) + j] = (BYTE) RGB2GRAY(r,g,b);
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
	BYTE* pCropImg = new BYTE[w1*h1];
	for(i=r.top;i<r.bottom;++i)for(j=r.left;j<r.right;++j){
		pCropImg[(i-r.top)*w1+j-r.left] = pImg[i*w+j];
	}
	return pCropImg;
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
// 		MakeRGBImgFrom24Dib(pDib, pImgR, pImgG, pImgB, w, h);
// 		pNewImgR = ZoomImg(pImgR, w, h, new_w, new_h);
// 		pNewImgG = ZoomImg(pImgG, w, h, new_w, new_h);
// 		pNewImgB = ZoomImg(pImgB, w, h, new_w, new_h);
// 		pNewDib = Make24DibFromRGBImg(pNewImgR, pNewImgG, pNewImgB, new_w, new_h);
// 		delete[]pImgR;     delete[]pImgG;     delete[]pImgB;
// 		delete[]pNewImgR; delete[]pNewImgG; delete[]pNewImgB;
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
BYTE* CImageBase::ZoomImg(BYTE *pImg,int w,int h,int new_w, int new_h)
{
	if(pImg == NULL) return NULL;
	
	BYTE *pNewImg_X = NULL;
	float xscale = (float)w/new_w;
	float yscale = (float)h/new_h;
	float scaleTh = 3.5;
	if(new_w == w && new_h == h)  
	{
		BYTE* pNewImg = new BYTE[new_w*new_h];
		memcpy(pNewImg,pImg,new_w*new_h);
		return pNewImg;
	}
	else if(xscale<scaleTh && yscale<scaleTh)
	{
		return ZoomInImg(pImg, w, h, new_w,  new_h);
	}
	else if(xscale>=scaleTh && yscale>=scaleTh)
	{
		return ZoomOutImg(pImg, w, h, new_w,  new_h);
	}
	else if(xscale>=scaleTh && yscale<scaleTh)
	{
		return ZoomXOutYInImg(pImg, w, h, new_w,  new_h);
	}
	else //if(xscale<scaleTh && yscale>=scaleTh)
	{
		return ZoomYOutXInImg(pImg, w, h, new_w,  new_h);
	}
}
BYTE* CImageBase::ZoomOutImg(BYTE *pImg,int w,int h,int new_w, int new_h) 
{
	if(pImg == NULL) return NULL;
	int i,j,ii,jj;
	int i_x,i_y,y,x;

	int xscale = 1024*w/new_w;
	int yscale = 1024*h/new_h;

	int win_w = ((xscale+512)>>10);
	win_w = max(win_w,1);
	int win_h = ((yscale+512)>>10);
	win_h = max(win_h,1);

	int stepX = win_w / 3;
	stepX = max(stepX,1);
	int stepY = win_h / 3;
	stepY = max(stepY,1);
	
	BYTE *pNewImg = new BYTE[new_w*new_h];
	if(pNewImg == NULL) return NULL;

	for(i=0;i<new_h;i++)
	{
		i_y = ((yscale * i)>>10);
		for(j=0; j<new_w; j++)
		{ 
			i_x = ((xscale * j)>>10);
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

	int xscale = 1024*w/new_w;
	int yscale = 1024*h/new_h;

	BYTE *pOrgPlusImg = new BYTE[(w+2)*(h+2)];
	memset(pOrgPlusImg,0,(w+2)*(h+2));
	for(i=1;i<=h;i++)
	{
		memcpy(pOrgPlusImg+i*(w+2)+1, pImg+(i-1)*w, w);
	}

	for(i=0;i<new_h;i++)
	{
		f_y = yscale * i + (yscale >>1) + 512;
		i_y = (f_y>>10);
		d_y = f_y - (i_y<<10); 
		for(j=0; j<new_w; j++)
		{
			f_x = xscale * j + (xscale >>1) + 512;
			i_x = (f_x>>10);
			d_x = f_x - (i_x<<10); 

			val00 = pOrgPlusImg[i_y*(w+2) + i_x];
			val01 = pOrgPlusImg[i_y*(w+2) + (i_x+1)];
			val10 = pOrgPlusImg[(i_y+1)*(w+2) + i_x];
			val11 = pOrgPlusImg[(i_y+1)*(w+2) + (i_x+1)];

			int newval = (int)((val00 * (1024-d_y) *  (1024-d_x) +
					 	        val01 * (1024-d_y) *      d_x    +
						        val10 *     d_y    *  (1024-d_x) +
						        val11 *     d_y    *      d_x  ));
			newval =(newval>>20); 
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
BYTE* CImageBase::GetCutImage(BYTE* ResImg,int &w,int &h,CRect& inRect)
{
	int		w1=0,h1=0;
	int		i = 0 , j = 0 , k = 0 ;
	int		lt = 0 , tp = 0 , bt = 0 , rt = 0 ;
	BOOL	IsBlack = FALSE;
	inRect = CRect(0,0,0,0);
	tp=-1;
	if(w==0 || h==0){
		return NULL;
		//AfxMessageBox(_T("w or h == 0")); 
	}
	while (!IsBlack && tp<h-1 ) 
	{
		tp++;
		for (j=0;j<w;j++) 
		{
			if(ResImg[tp*w+j]==1)
			{
				IsBlack = TRUE;
				break;
			}
		}
	}

	bt = h;	IsBlack = FALSE;
	while (!IsBlack && bt>0 ) 
	{
		bt--;
		for (j=0;j<w;j++) 
		{
			if(ResImg[bt*w+j]==1)
			{
				IsBlack = TRUE;
				break;
			}
		}
	}

	lt=-1;	IsBlack = FALSE;
	while (!IsBlack && lt<w-1 ) 
	{
		lt++;
		for (j=0;j<h;j++) 
		{
			if(ResImg[j*w+lt]==1)
			{
				IsBlack = TRUE;
				break;
			}
		}
	}

	rt = w;	IsBlack = FALSE;
	while (!IsBlack && rt>0 ) 
	{
		rt--;
		for (j=0;j<h;j++) 
		{
			if(ResImg[j*w+rt]==1)
			{
				IsBlack = TRUE;
				break;
			}
		}
	}


	w1 = rt-lt+1,h1 = bt-tp+1;
	if(w1<0 || w1>w) w1=0;
	if(h1<0 || h1>h) h1=0;
	if(w1==0 || h1==0){
		w = 0; h = 0;
		return NULL;
	}
	inRect = CRect(lt,tp,rt+1,bt+1);
	BYTE* outImg = new BYTE[w1*h1];	memset(outImg,0,w1*h1);

	for (i=tp;i<=bt;i++)
		memcpy(&outImg[(i-tp)*w1],&ResImg[i*w+lt],w1 );
	w = w1; h = h1;
	return outImg;
}

void CImageBase::GetCutRect(BYTE* ResImg,int w,int h,CRect& inRect)
{
	int		w1=0,h1=0;
	int		i = 0 , j = 0 , k = 0 ;
	int		lt = 0 , tp = 0 , bt = 0 , rt = 0 ;
	BOOL	IsBlack = FALSE;
	inRect = CRect(0,0,0,0);
	tp=-1;
	if(w==0 || h==0){
		return ;
		//AfxMessageBox(_T("w or h == 0")); 
	}
	while (!IsBlack && tp<h-1 ) 
	{
		tp++;
		for (j=0;j<w;j++) 
		{
			if(ResImg[tp*w+j]==1)
			{
				IsBlack = TRUE;
				break;
			}
		}
	}

	bt = h;	IsBlack = FALSE;
	while (!IsBlack && bt>0 ) 
	{
		bt--;
		for (j=0;j<w;j++) 
		{
			if(ResImg[bt*w+j]==1)
			{
				IsBlack = TRUE;
				break;
			}
		}
	}

	lt=-1;	IsBlack = FALSE;
	while (!IsBlack && lt<w-1 ) 
	{
		lt++;
		for (j=0;j<h;j++) 
		{
			if(ResImg[j*w+lt]==1)
			{
				IsBlack = TRUE;
				break;
			}
		}
	}

	rt = w;	IsBlack = FALSE;
	while (!IsBlack && rt>0 ) 
	{
		rt--;
		for (j=0;j<h;j++) 
		{
			if(ResImg[j*w+rt]==1)
			{
				IsBlack = TRUE;
				break;
			}
		}
	}


	w1 = rt-lt+1,h1 = bt-tp+1;
	if(w1<0 || w1>w) w1=0;
	if(h1<0 || h1>h) h1=0;
	if(w1==0 || h1==0){
		return ;
	}
	inRect = CRect(lt,tp,rt+1,bt+1);
}
BOOL CImageBase::SaveDibFileByOption(LPCTSTR lpszPathName, BYTE* pDib,bool bSaveAble)
{
	if(bSaveAble == false)	return FALSE;

	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;
	int FileSize,ImgSize;
	int HeadSize;
	int QuadSize;
	BITMAPFILEHEADER FilehHeader;
	ImgSize = lpBIH->biSizeImage;//GetBmpSize(w,h,lpBIH->biBitCount);
	if(lpBIH->biBitCount == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(lpBIH->biBitCount == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(lpBIH->biBitCount == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(lpBIH->biBitCount == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else							QuadSize = 0;//24
	HeadSize = min(14,sizeof(BITMAPFILEHEADER)) + sizeof(BITMAPINFOHEADER)+QuadSize;
	FileSize = HeadSize+ImgSize;
	int DibSize = sizeof(BITMAPINFOHEADER)+QuadSize+ImgSize;

	FilehHeader.bfType = 0x4d42;     //unsigned short    bfType;
	FilehHeader.bfSize = FileSize;   //unsigned int	     bfSize;
	FilehHeader.bfReserved1 = 0;     //unsigned short    bfReserved1;
	FilehHeader.bfReserved2 = 0;     //unsigned short    bfReserved2;
	FilehHeader.bfOffBits = HeadSize;//unsigned int      bfOffBits;

	FILE* file;

#ifdef UNICODE
	file = _wfopen(lpszPathName,_T("wb"));
#else
	file = fopen(lpszPathName,_T("wb"));
#endif
	if(file==NULL)
		return FALSE;
	fwrite(&FilehHeader.bfType,2,1,file);
	fwrite(&FilehHeader.bfSize,12,1,file);
	fwrite(pDib,DibSize,1,file);
	fclose(file);

	return TRUE;
}
BOOL CImageBase::SaveDibFile(LPCTSTR lpszPathName, BYTE* pDib)
{
	//#ifndef SAVE_IMAGE_ENABLE
	//	return FALSE;
	//#endif
	//
	//#ifndef _DEBUG
	//	return FALSE;
	//#endif

	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;
	int FileSize,ImgSize;
	int HeadSize;
	int QuadSize;
	BITMAPFILEHEADER FilehHeader;
	ImgSize = lpBIH->biSizeImage;//GetBmpSize(w,h,lpBIH->biBitCount);
	if(lpBIH->biBitCount == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(lpBIH->biBitCount == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(lpBIH->biBitCount == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(lpBIH->biBitCount == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else							QuadSize = 0;//24
	HeadSize = min(14,sizeof(BITMAPFILEHEADER)) + sizeof(BITMAPINFOHEADER)+QuadSize;
	FileSize = HeadSize+ImgSize;
	int DibSize = sizeof(BITMAPINFOHEADER)+QuadSize+ImgSize;

	FilehHeader.bfType = 0x4d42;     //unsigned short    bfType;
	FilehHeader.bfSize = FileSize;   //unsigned int	     bfSize;
	FilehHeader.bfReserved1 = 0;     //unsigned short    bfReserved1;
	FilehHeader.bfReserved2 = 0;     //unsigned short    bfReserved2;
	FilehHeader.bfOffBits = HeadSize;//unsigned int      bfOffBits;

	FILE* file;

#ifdef UNICODE
	file = _wfopen(lpszPathName,_T("wb"));
#else
	file = fopen(lpszPathName,_T("wb"));
#endif
	if(file==NULL)
		return FALSE;
	fwrite(&FilehHeader.bfType,2,1,file);
	fwrite(&FilehHeader.bfSize,12,1,file);
	fwrite(pDib,DibSize,1,file);
	fclose(file);

	return TRUE;
}

BOOL CImageBase::SaveImgToFile(LPCTSTR lpszPathName, BYTE* pImg,int w,int h,int nBits)
{
	return SaveImgFile(lpszPathName, pImg,CSize(w,h),nBits);
}
BOOL CImageBase::SaveImgFile(LPCTSTR lpszPathName, BYTE* pImg,CSize Sz,int nBits)
{
	//#ifndef SAVE_IMAGE_ENABLE
	//	return FALSE;
	//#endif
	//
	//#ifndef _DEBUG
	//	return FALSE;
	//#endif
	BOOL rc;
	int wd = Sz.cx;
	int hi = Sz.cy;
	BYTE *pDib = NULL;
	if(nBits == 1)	pDib = MakeBinDibFromImg(pImg,wd,hi);
	else			pDib = MakeGrayDibFromImg(pImg,wd,hi);
	rc = SaveDibFile(lpszPathName,pDib);
	delete[] pDib;pDib = NULL;
	return rc;
}
BOOL CImageBase::SaveSubImgFile(LPCTSTR lpszPathName, BYTE* pImg,CSize Sz,CRect subRt,int nBits)
{
#ifndef SAVE_IMAGE_ENABLE
	return FALSE;
#endif

#ifndef _DEBUG
	return FALSE;
#endif
	BOOL rc;
	int w,h,wd,hi;
	w = Sz.cx;			h = Sz.cy;

	BYTE *pDib = NULL;
	BYTE *pSubImg = CropImg(pImg,w,h,subRt);
	wd = subRt.Width();	hi = subRt.Height();
	if(nBits == 1)	pDib = MakeBinDibFromImg(pSubImg,wd,hi);
	else			pDib = MakeGrayDibFromImg(pSubImg,wd,hi);
	rc = SaveDibFile(lpszPathName,pDib);
	delete[] pDib;pDib = NULL;
	delete[] pSubImg;pSubImg = NULL;
	return rc;
}

