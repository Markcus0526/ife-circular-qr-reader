// ImageBase.h: interface for the CImageBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_)
#define AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_


static BYTE BIT[] = {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
static BYTE BIT1[] = {0x7F,0xBF,0xDF,0xEF,0xF7,0xFB,0xFD,0xFE};

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
	
	static	inline  BYTE	GetPx(BYTE* pBinBits,int ByteW, int x, int y)
	{
		return (pBinBits[ByteW*y+(x/8)] & BIT[x%8])>0 ? 1:0;
	};
	static	inline  void	SetPx(BYTE* pBinBits,int ByteW, int x, int y,BYTE Px)
	{
		if(Px)
			pBinBits[ByteW*y+(x/8)] |= BIT[x%8];
		else
			pBinBits[ByteW*y+(x/8)] &= BIT1[x%8];
	};

	static  void    InvertDib(BYTE* pDib,BOOL bAuto=FALSE);

	static  void	DrawDib(CDC *pDC,CRect Rt,BYTE *pDib);
	static	void	DrawDib(CDC *pDC,BYTE *pDib,int sx,int sy);
	static  void	DrawDib(CDC *pDC,BYTE *pDib);
	static  void	DrawInvertDib(CDC *pDC,CRect Rt,BYTE *pDib);

	static  BYTE*   MakeDib(int w,int h,int nBitCount);
	static  BYTE*   MakeImgFromBinBits(BYTE *lpBits,int w,int h);
	static  BYTE*   MakeImgFromBinDib(BYTE *pDib,int& w,int& h);
	static  BYTE*   MakeImgFromGrayDib(BYTE *pDib,int& w,int& h);
	static  BYTE*   MakeGrayImgFromBinBits(BYTE *lpBits,int w,int h);
	static  BYTE*   MakeGrayImgFromBinDib(BYTE *pDib,int& w,int& h);

	static  BOOL    MakeRGBImgFrom24Dib(BYTE* pDib, BYTE*& pImgR, BYTE*& pImgG, BYTE*& pImgB, int& w, int& h);
	static  BOOL    MakeRGBImgFrom24Bits(BYTE* lpBits,BYTE*& pImgR, BYTE*& pImgG, BYTE*& pImgB, int w, int h);

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
	static  BYTE*   MakeBinDib(BYTE* pDib);
	static  BYTE*   Make32DibFrom24Dib(BYTE* pDib);

	static  BYTE*	Make256ColorDibFrom24Dib(BYTE* pDib);

	static  BOOL    GetWeightCenter(BYTE* pDib,int& x,int& y);
	static  BOOL    TranslateDib(BYTE* pDib,int dx,int dy);

	static  BYTE*	MakePrintedDib(BYTE* pDib,int nw,int nh,int dpi,
								CPoint docPt,CRect imgRect,float zoom,char* ext);


private:
	static int		GetMostCloseColor(RGBQUAD *Ary,int n,RGBQUAD qQ);
	
	
	//Crop,Zoom Functions
public:
	static  BYTE*	CopyDib(BYTE* srcDib);
	static  BYTE*   CropDib(BYTE* pDib,CRect& r);
	static  BYTE*   CropImg(BYTE* pImg,int w,int h,CRect& r);
	static  BOOL    MergeCopyImgB2A(BYTE* pImgA,int wa,int ha,BYTE* pImgB,int wb,int hb,CPoint pos);

	static  BOOL    RemoveRectDib(BYTE* pDib, CRect rect);
	static  BOOL    RemoveRectBinDib(BYTE* pDib, CRect rect);
	static  BOOL    RemoveRectGrayDib(BYTE* pDib, CRect rect, BYTE val);
	static  BOOL	RemoveRect24Dib(BYTE* pDib, CRect rect,RGBQUAD rgbquad);

	static  BOOL    RegionRemoveBinImg(BYTE* pImg,int w,int h, CRect rect);
	static  BOOL    RegionRemoveImg(BYTE* pImg,int w,int h, CRect rect);
	static  RGBQUAD GetBkClrInRect24Dib(BYTE* pDib, CRect rect);
	static  BYTE    GetBkClrInRectGrayDib(BYTE* pDib, CRect rect);
	static  BYTE    GetBkClrInRectImg(BYTE* pImg,int w,int h, CRect rect);

	static  BOOL	OptimizeContrastImg(BYTE* pImg,int w,int h);

	static  BYTE*   ZoomOutImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*   ZoomInImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*   ZoomXOutYInImg(BYTE *pImg,int w,int h,int new_w, int new_h); 
	static  BYTE*   ZoomYOutXInImg(BYTE *pImg,int w,int h,int new_w, int new_h); 
	static  BYTE*   ZoomImg(BYTE *pImg,int w,int h,int new_w, int new_h);
	static  BYTE*	ZoomImg(BYTE* pImg,int& w,int& h,double zoomScale);
	static  BYTE*   ZoomDib(BYTE *pDib,int new_w, int new_h);
	static  BYTE*   ZoomDib(BYTE* pDib, double zoomScale);
	static  BYTE*   ThumbnailBinDib(BYTE *pDib,int new_w, int new_h);
	static  BYTE*   ZoomOutGrayDib(BYTE *pDib,int new_w, int new_h);
	static  BYTE*   ZoomOut24Dib(BYTE *pDib,int new_w, int new_h);
	static  BYTE*   Thumbnail(BYTE* pDib,int new_w,int new_h);

	//Color Space Functions
	static  void    RGBtoYIQ(BYTE R, BYTE G, BYTE B, BYTE &Y, BYTE &I, BYTE &Q);
	static  void    ConvertRGBImgToYIQImg(BYTE *pImgR,BYTE *pImgG,BYTE *pImgB, int w, int h, BYTE*& pImgY,BYTE*& pImgI,BYTE*& pImgQ);

	static  BYTE*   ZipBinBits(BYTE *pBits, int len, int *Ziplen);
	static  int     GetZipLen(BYTE *pBits, int len);
	static  BYTE*   UnZipBinBits(BYTE *pZipBits, int Ziplen,int len);
	static  int     GetUnZipLen(BYTE *pZipBits, int Ziplen);

	//static  BYTE*   MakeDibFromBitmap(CBitmap* pBitmap);
};

#endif // !defined(AFX_IMAGEBASE_H__35D175DD_5EEF_4C08_9E41_E1AF109ED272__INCLUDED_)
