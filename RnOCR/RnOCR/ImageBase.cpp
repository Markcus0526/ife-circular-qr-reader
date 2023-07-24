// ImageBase.cpp: implementation of the CImageBase class.
//
//////////////////////////////////////////////////////////////////////

#include "ImageBase.h"


// #ifdef _DEBUG
// #undef THIS_FILE
// static char THIS_FILE[]=__FILE__;
// #define new DEBUG_NEW
// #endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
//#define RGB2GRAY(r,g,b) (((b)*114 + (g)*587 + (r)*299)/1000)
#define RGB2GRAY(r,g,b) (((b)*117 + (g)*601 + (r)*306) >> 10)

CImageBase::CImageBase()
{

}

CImageBase::~CImageBase()
{

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

void CImageBase::GetDibInfo(BYTE* pDib,int& w,int& h,int& bpp,int& wstep)
{
	if(pDib==NULL) return;
	LPBITMAPINFOHEADER lpBIH=(LPBITMAPINFOHEADER)pDib ;
	w=(int)lpBIH->biWidth;
	h=(int)lpBIH->biHeight;
	bpp = (int)lpBIH->biBitCount;
	wstep = (w*bpp+31)/32 * 4;
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
	bool	IsBlack = false;
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
				IsBlack = true;
				break;
			}
		}
	}

	bt = h;	IsBlack = false;
	while (!IsBlack && bt>0 ) 
	{
		bt--;
		for (j=0;j<w;j++) 
		{
			if(ResImg[bt*w+j]==1)
			{
				IsBlack = true;
				break;
			}
		}
	}

	lt=-1;	IsBlack = false;
	while (!IsBlack && lt<w-1 ) 
	{
		lt++;
		for (j=0;j<h;j++) 
		{
			if(ResImg[j*w+lt]==1)
			{
				IsBlack = true;
				break;
			}
		}
	}

	rt = w;	IsBlack = false;
	while (!IsBlack && rt>0 ) 
	{
		rt--;
		for (j=0;j<h;j++) 
		{
			if(ResImg[j*w+rt]==1)
			{
				IsBlack = true;
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
	bool	IsBlack = false;
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
				IsBlack = true;
				break;
			}
		}
	}

	bt = h;	IsBlack = false;
	while (!IsBlack && bt>0 ) 
	{
		bt--;
		for (j=0;j<w;j++) 
		{
			if(ResImg[bt*w+j]==1)
			{
				IsBlack = true;
				break;
			}
		}
	}

	lt=-1;	IsBlack = false;
	while (!IsBlack && lt<w-1 ) 
	{
		lt++;
		for (j=0;j<h;j++) 
		{
			if(ResImg[j*w+lt]==1)
			{
				IsBlack = true;
				break;
			}
		}
	}

	rt = w;	IsBlack = false;
	while (!IsBlack && rt>0 ) 
	{
		rt--;
		for (j=0;j<h;j++) 
		{
			if(ResImg[j*w+rt]==1)
			{
				IsBlack = true;
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
BYTE* CImageBase::MeanFilter(BYTE* pImg,int w,int h,int nWinSize)
{
	if (pImg==NULL || w<1 || h<1)
		return NULL;
	if(nWinSize>=w-1 || nWinSize>=h-1)
		nWinSize=min(w,h)-1;
	int i,j;
	int ww = w+1,hh=h+1;
	int *IntImg = new int[ww*hh];
	memset(IntImg,0,sizeof(int)*ww*hh);
	BYTE *NewImg = new BYTE[w*h];
	memset(NewImg,0,w*h);
	int partialsum;
	for(i=0;i<h;i++)
	{
		partialsum  = 0;
		IntImg[(i+1)*ww] = 0;
		for(j=1;j<=w;j++)
		{
			partialsum += pImg[i*w+j-1];
			IntImg[(i+1)*ww+j] = IntImg[i*ww+j] + partialsum;
		}
	}

	int rw=nWinSize,rh=nWinSize,sum;
	int rnum = (rw*2)*(rh*2);
	for(i=rh;i<h-rh;i++)
	{
		for(j=rw;j<w-rw;j++)
		{
			sum = IntImg[(i-rh)*ww + j-rw] + IntImg[(i+rh)*ww+j+rw] - IntImg[(i-rh)*ww+j+rw] - IntImg[(i+rh)*ww+j-rw];
			NewImg[i*w+j] = sum>>14;
		}
	}
	int sty,edy,stx,edx,num=0;
	sty=0;
	for(i=0;i<rh;i++)
	{
		edy = min(h,(i+rh+1));
		for(j=0;j<w;j++)
		{
			stx = max(0,j-rw);
			edx = min(w,j+rw+1);
			sum = IntImg[stx] + IntImg[edy*ww+edx] - IntImg[edx] - IntImg[edy*ww+stx];
			sum = (sum )/((edy-sty)*(edx-stx));
			NewImg[i*w+j] = sum;
		}
	}
	for(i=h-rh;i<h;i++)
	{
		sty=max(0,i-rh);
		edy = min(h,(i+rh+1));
		for(j=0;j<w;j++)
		{
			stx = max(0,j-rw);
			edx = min(w,j+rw+1);
			sum = IntImg[sty*ww+stx] + IntImg[edy*ww+edx] - IntImg[sty*ww+edx] - IntImg[edy*ww+stx];

			sum = (sum)/((edy-sty)*(edx-stx));
			NewImg[i*w+j] = sum;
		}
	}
	for(i=rh;i<h-rh;i++)
	{
		sty=max(0,i-rh);
		edy = min(h,(i+rh+1));
		for(j=0;j<rw;j++)
		{
			stx = max(0,j-rw);
			edx = min(w,j+rw+1);
			sum = IntImg[sty*ww+stx] + IntImg[edy*ww+edx] - IntImg[sty*ww+edx] - IntImg[edy*ww+stx];

			sum = (sum)/((edy-sty)*(edx-stx));
			NewImg[i*w+j] = sum;
		}
	}
	for(i=rh;i<h-rh;i++)
	{
		sty=max(0,i-rh);
		edy = min(h,(i+rh+1));
		for(j=w-rw;j<w;j++)
		{
			stx = max(0,j-rw);
			edx = min(w,j+rw+1);
			sum = IntImg[sty*ww+stx] + IntImg[edy*ww+edx] - IntImg[sty*ww+edx] - IntImg[edy*ww+stx];

			sum = (sum)/((edy-sty)*(edx-stx));
			NewImg[i*w+j] = sum;
		}
	}
	delete[] IntImg;
	return NewImg;
}
void CImageBase::MeanFilter(BYTE* pImg,int w,int h)
{
	int i,j;
	int* NewImg = new int[w*h];
	int p,pix = w*h;
	for(i=1;i<pix-1;i++){
		NewImg[i] = pImg[i-1] + pImg[i] + pImg[i+1];
	}
	for(i=1;i<h-1;i++)for(j=1;j<w-1;j++)
	{
		p = i*w+j;
		pImg[p] = BYTE((NewImg[p-w] + NewImg[p] + NewImg[p+w])/9);
	}
	delete[] NewImg;
}
