// ImageIO.h: interface for the CImageIO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_IMAGEIO_H__)
#define _IMAGEIO_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ximage.h"
#include "ximatif.h"

/*Ãùº¬Âô»¥Ëæ ´ÝÂÙ ¼³Ì©*/
#define IMAGETYPE_BMP        CXIMAGE_FORMAT_BMP
#define IMAGETYPE_JPG        CXIMAGE_FORMAT_JPG
#define IMAGETYPE_GIF        CXIMAGE_FORMAT_GIF
#define IMAGETYPE_PNG        CXIMAGE_FORMAT_PNG
#define IMAGETYPE_MNG        CXIMAGE_FORMAT_MNG
#define IMAGETYPE_ICO        CXIMAGE_FORMAT_ICO
#define IMAGETYPE_TIF        CXIMAGE_FORMAT_TIF
#define IMAGETYPE_TGA        CXIMAGE_FORMAT_TGA
#define IMAGETYPE_PCX        CXIMAGE_FORMAT_PCX
#define IMAGETYPE_WBMP       CXIMAGE_FORMAT_WBMP
#define IMAGETYPE_WMF        CXIMAGE_FORMAT_WMF
#define IMAGETYPE_J2K        CXIMAGE_FORMAT_J2K
#define IMAGETYPE_JBG        CXIMAGE_FORMAT_JBG
#define IMAGETYPE_JP2        CXIMAGE_FORMAT_JP2
#define IMAGETYPE_JPC        CXIMAGE_FORMAT_JPC
#define IMAGETYPE_PGX        CXIMAGE_FORMAT_PGX
#define IMAGETYPE_RAS        CXIMAGE_FORMAT_RAS
#define IMAGETYPE_PNM        CXIMAGE_FORMAT_PNM
#define IMAGETYPE_UNKNOWN    CXIMAGE_FORMAT_UNKNOWN


/*
¿Ðµ¹º÷ËË¶§: CImageIO
±¨²þ: Ãùº¬»ôµê¶¦ ÁÄËÎµá ¹¢À¾ ¼¬¼õ, ÁÄËÎËæµáÌ© ¸ó±ã,
		Ì°¾©±¨Ëæµá Encoding, Ì°¾©±¨Ëæº·¹¢À¾Ì© Decoding
»õºÂ»ô: Kim M.I.
»õºÂ²¤»ô:2008/12/15

½Ø°Ö pDib²÷ BITMAPINFOHEADER + RGBQUAD + Bits
*/

class CImageIO  
{
public:
	CImageIO();
	virtual ~CImageIO(); 
//private:
	static CString FindExtension(const CString& name);
	static int     FindType(const CString& ext);

public:
	static void  ModifyBinDibRGBQUAD(BYTE* pDib);
	static BYTE* LoadBmpFile(LPCTSTR lpszPathName);
	static BOOL  SaveBmpFile(LPCTSTR lpszPathName, BYTE* lpDib);

	static BYTE* LoadImageFromFile(LPCTSTR lpszPathName);
	static BOOL  SaveImageToFile(LPCTSTR lpszPathName, BYTE* lpDib);

	static BYTE* LoadImageFromBuffer(BYTE* pBuf,int size,int nType = IMAGETYPE_UNKNOWN); 
	static BYTE* SaveImageToBuffer(BYTE* pDib, long &buffersize, DWORD nType = IMAGETYPE_JPG,int nJpgQuality = 50);
	static BOOL  SaveImgToFile(LPCTSTR lpszPathName, BYTE* pImg, int w, int h,int nBitCount=8);
	static BOOL	 SaveDibCompress(FILE* fp,BYTE* pDib);
	static BYTE* LoadDibCompress(FILE* fp);
	static BOOL  IsValidImageFile(LPCTSTR lpszPathName);

	static int	 GetImageTypeForCompressSave(BYTE* pDib);
};

#endif // !defined(_IMAGEIO_H__)
