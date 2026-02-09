// ImageBase.h: interface for the CImageBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_)
#define AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_

class CImageBase  
{
public:
	CImageBase();
	virtual ~CImageBase();

	static	BOOL	IsValid(BYTE* lpBits,int w,int h);

	static  BYTE*   Get_lpBits(BYTE *pDib);
	static  int	    GetDibSize(BYTE *pDib);
	static  int	    GetDibSize(int w,int h,int bitcount);
	static  int	    GetBitsSize(BYTE *pDib);
	static  void	GetWidthHeight(BYTE *pDib,int& w, int& h);
	static  int 	GetBitCount(BYTE *pDib);
	static  void	GetDibInfo(BYTE* pDib,int& w,int& h,int& bpp,int& wstep);
	static	int		GetDPI(BYTE *pDib);
	static  void    InvertDib(BYTE* pDib,BOOL bAuto=FALSE);

	static  void	DrawDib(CDC *pDC,CRect Rt,BYTE *pDib);
	static	void	DrawDib(CDC *pDC,BYTE *pDib,int sx,int sy);
	static  void	DrawDib(CDC *pDC,BYTE *pDib);
	static  void	DrawInvertDib(CDC *pDC,CRect Rt,BYTE *pDib);

	static  BYTE*	MakeDIBFromDib(BYTE* pDib);
	static  BYTE*   MakeDib(int w,int h,int nBitCount);
	static  BYTE*   MakeImgFromBinBits(BYTE *lpBits,int w,int h);
	static  BYTE*   MakeImgFromBinDib(BYTE *pDib,int& w,int& h);
	static  BYTE*   MakeImgFromGrayDib(BYTE *pDib,int& w,int& h);
	static  BYTE*   MakeGrayImgFromBinBits(BYTE *lpBits,int w,int h);
	static  BYTE*   MakeGrayImgFromBinDib(BYTE *pDib,int& w,int& h);

	static  BYTE*	MakeBinBitsFromImg(BYTE *pImg, int w, int h);
	static  BYTE*	MakeBinDibFromBits(BYTE *lpBits,int w,int h);
	static  BYTE*	MakeBinDibFromImg(BYTE *pImg, int w, int h);

	static  BYTE*	MakeGrayDibFromImg(BYTE *pImg,int w,int h);
	static  BYTE*	MakeGrayDibFromBits(BYTE *lpBits,int w,int h);

	static  BYTE*   MakeGrayImgFrom32Dib(BYTE* pDib,int& w,int& h);
	static  BYTE*	MakeGrayDibFrom24Dib(BYTE* pDib);
	static  BYTE*   MakeGrayImgFrom24Dib(BYTE* pDib,int& w,int& h);
	static  BYTE*   MakeGrayImgFrom16Dib(BYTE* pDib,int& w,int& h);
	static  BYTE*   MakeGrayImgFrom24Img(BYTE* pImgR, BYTE* pImgG, BYTE* pImgB, int w, int h);
	static  BYTE*   Make24DibFromRGBImg(BYTE* pImgR, BYTE* pImgG, BYTE* pImgB, int w, int h);
	static  BYTE*   Make24Dib(BYTE* pDib);
	static	BYTE*	MakeGrayImgFromAnyDib(BYTE* pDib,int& w,int& h);
	static  BYTE*   MakeGrayDib(BYTE* pDib);
	static  BYTE*   Make32DibFrom24Dib(BYTE* pDib);

public:
	static  BYTE*	CopyDib(BYTE* srcDib);
	static  BYTE*   CropDib(BYTE* pDib,CRect& r);
	static  BYTE*   CropImg(BYTE* pImg,int w,int h,CRect& r);

	static  BYTE*   ZoomOutImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*   ZoomInImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*   ZoomXOutYInImg(BYTE *pImg,int w,int h,int new_w, int new_h); 
	static  BYTE*   ZoomYOutXInImg(BYTE *pImg,int w,int h,int new_w, int new_h); 
	static  BYTE*   ZoomImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*	ZoomImg(BYTE* pImg,int& w,int& h,double zoomScale);
	static  BYTE*   ZoomDib(BYTE *pDib,int new_w, int new_h);
	static  BYTE*   ZoomDib(BYTE* pDib, double zoomScale);
	static  BYTE*   ZoomOutGrayDib(BYTE *pDib,int new_w, int new_h);
	static  BYTE*   ZoomOut24Dib(BYTE *pDib,int new_w, int new_h);
	
	static	BYTE*	GetCutImage(BYTE* ResImg,int &w,int &h,CRect& inRect);
	static	void	GetCutRect(BYTE* ResImg,int w,int h,CRect& inRect);

	static	BOOL	SaveDibFile(LPCTSTR lpszPathName, BYTE* pDib);
	static	BOOL	SaveDibFileByOption(LPCTSTR lpszPathName, BYTE* pDib,bool bSaveAble);
	static	BOOL	SaveImgFile(LPCTSTR lpszPathName, BYTE* pImg,CSize Sz,int nBits);
	static	BOOL	SaveImgToFile(LPCTSTR lpszPathName, BYTE* pImg,int w,int h,int nBits);
	static	BOOL	SaveSubImgFile(LPCTSTR lpszPathName, BYTE* pImg,CSize Sz,CRect subRt,int nBits);
};

#endif // !defined(AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_)
