// ImageBase.h: interface for the CImageBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_)
#define AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_
#include "Include/myType.h"

class CImageBase  
{
public:
	CImageBase();
	virtual ~CImageBase();

	static  BYTE*   Get_lpBits(BYTE *pDib);
	static  int	    GetDibSize(BYTE *pDib);
	static  int	    GetDibSize(int w,int h,int bitcount);
	static  void	GetDibInfo(BYTE* pDib,int& w,int& h,int& bpp,int& wstep);
	
	static  BYTE*   MakeImgFromGrayDib(BYTE *pDib,int& w,int& h);
	static  BYTE*   MakeGrayImgFromBinBits(BYTE *lpBits,int w,int h);
	static  BYTE*   MakeGrayImgFromBinDib(BYTE *pDib,int& w,int& h);

	static  BYTE*   MakeGrayImgFrom32Dib(BYTE* pDib,int& w,int& h);
	static  BYTE*   MakeGrayImgFrom24Dib(BYTE* pDib,int& w,int& h);
	static	BYTE*	MakeGrayImgFromAnyDib(BYTE* pDib,int& w,int& h);

public:

	static  BYTE*   CropImg(BYTE* pImg,int w,int h,CRect& r);

	static  BYTE*   ZoomOutImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*   ZoomInImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*   ZoomXOutYInImg(BYTE *pImg,int w,int h,int new_w, int new_h); 
	static  BYTE*   ZoomYOutXInImg(BYTE *pImg,int w,int h,int new_w, int new_h); 
	static  BYTE*   ZoomImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*	ZoomImg(BYTE* pImg,int& w,int& h,double zoomScale);
	
	static	BYTE*	GetCutImage(BYTE* ResImg,int &w,int &h,CRect& inRect);
	static	void	GetCutRect(BYTE* ResImg,int w,int h,CRect& inRect);
	static	BYTE*	MeanFilter(BYTE* pImg,int w,int h,int nWinSize);
	static	void	MeanFilter(BYTE* pImg,int w,int h);

};

#endif // !defined(AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_)
