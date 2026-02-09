// ImageIO.cpp: implementation of the CImageIO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageIO.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImageIO::CImageIO()
{

}

CImageIO::~CImageIO()
{

}
CString CImageIO::FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString("");
}
int CImageIO::FindType(const CString& ext)
{
	int type = 0;
	if (ext == "bmp")					type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (ext=="jpg"||ext=="jpeg")	type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (ext == "gif")				type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (ext == "png")				type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (ext=="mng"||ext=="jng")	type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (ext == "ico")				type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (ext=="tiff"||ext=="tif")	type = CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (ext=="tga")				type = CXIMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
	else if (ext=="pcx")				type = CXIMAGE_FORMAT_PCX;
#endif
#if CXIMAGE_SUPPORT_WBMP
	else if (ext=="wbmp")				type = CXIMAGE_FORMAT_WBMP;
#endif
#if CXIMAGE_SUPPORT_WMF
	else if (ext=="wmf"||ext=="emf")	type = CXIMAGE_FORMAT_WMF;
#endif
#if CXIMAGE_SUPPORT_J2K
	else if (ext=="j2k"||ext=="jp2")	type = CXIMAGE_FORMAT_J2K;
#endif
#if CXIMAGE_SUPPORT_JBG
	else if (ext=="jbg")				type = CXIMAGE_FORMAT_JBG;
#endif
#if CXIMAGE_SUPPORT_JP2
	else if (ext=="jp2"||ext=="j2k")	type = CXIMAGE_FORMAT_JP2;
#endif
#if CXIMAGE_SUPPORT_JPC
	else if (ext=="jpc"||ext=="j2c")	type = CXIMAGE_FORMAT_JPC;
#endif
#if CXIMAGE_SUPPORT_PGX
	else if (ext=="pgx")				type = CXIMAGE_FORMAT_PGX;
#endif
#if CXIMAGE_SUPPORT_RAS
	else if (ext=="ras")				type = CXIMAGE_FORMAT_RAS;
#endif
#if CXIMAGE_SUPPORT_PNM
	else if (ext=="pnm"||ext=="pgm"||ext=="ppm") type = CXIMAGE_FORMAT_PNM;
#endif
	else type = CXIMAGE_FORMAT_UNKNOWN;

	return type;
}

void CImageIO::ModifyBinDibRGBQUAD(BYTE* pDib)
{
	if(!pDib) return;
	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;
	if(lpBIH->biBitCount != 1)	return;
	RGBQUAD* ppal = (RGBQUAD*)(pDib + sizeof(BITMAPINFOHEADER));
	if(ppal[0].rgbGreen == 0 && ppal[1].rgbGreen == 255) return;
	
	ppal[0].rgbRed      = 0;
	ppal[0].rgbGreen    = 0;
	ppal[0].rgbBlue     = 0;
	ppal[0].rgbReserved = 0;
	
	ppal[1].rgbRed      = 255;
	ppal[1].rgbGreen    = 255;
	ppal[1].rgbBlue     = 255;
	ppal[1].rgbReserved = 0;

	BYTE* pBits = pDib + sizeof(BITMAPINFOHEADER) + 2 * sizeof(RGBQUAD);
	for(DWORD i=0;i<lpBIH->biSizeImage;++i) pBits[i] = ~pBits[i];

}


BYTE* CImageIO::LoadImageFromFile(LPCTSTR lpszPathName)
{
	CxImage xImage;
	xImage.Load(lpszPathName);

	if (!xImage.IsValid()){
		//AfxMessageBox(xImage.GetLastError());
		return NULL;
	}

	BYTE* pDib = (BYTE*) xImage.GetDIB();
	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;
	int QuadSize;
	if(lpBIH->biBitCount == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(lpBIH->biBitCount == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(lpBIH->biBitCount == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(lpBIH->biBitCount == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else							QuadSize = 0;//24
	int DibSize =  sizeof(BITMAPINFOHEADER) + QuadSize + lpBIH->biSizeImage;
	BYTE* pRetDib = new BYTE[DibSize];
	memcpy(pRetDib,pDib,DibSize);
	if(lpBIH->biBitCount == 1)
		ModifyBinDibRGBQUAD(pRetDib);

	return pRetDib;
}

BYTE* CImageIO::LoadBmpFile(LPCTSTR lpszPathName)
{
	FILE* file = _tfopen(lpszPathName,_T("rb"));
	if(file==NULL)
		return NULL;
	BITMAPFILEHEADER bmpFileHeader;
	unsigned int size = sizeof(BITMAPFILEHEADER);
	if(fread(&bmpFileHeader,1,size,file) != size)
	{
		fclose(file);
		return NULL;
	}
	if(bmpFileHeader.bfType != 0x4d42)
	{
		fclose(file);
		return NULL;
	}
	size = bmpFileHeader.bfSize - size;
	BYTE* pDib = new BYTE[size];
	if(fread(pDib,1,size,file) != size)
	{
		delete[] pDib;
		fclose(file);
		return NULL;
	}
	fclose(file);
	return pDib;
}
BYTE* CImageIO::LoadImageFromBuffer(BYTE* pBuf,int size,int nType)
{
	if(pBuf == NULL) return NULL;
	CxImage xImage(pBuf,size,nType);
	if (!xImage.IsValid()){
//		AfxMessageBox(xImage.GetLastError());
		return NULL;
	}
	BYTE* pDib = (BYTE*) xImage.GetDIB();
	LPBITMAPINFOHEADER lpBIH = (LPBITMAPINFOHEADER)pDib;
	int QuadSize;
	if(lpBIH->biBitCount == 1)		QuadSize = sizeof(RGBQUAD)*2;
	else if(lpBIH->biBitCount == 2)	QuadSize = sizeof(RGBQUAD)*4;
	else if(lpBIH->biBitCount == 4)	QuadSize = sizeof(RGBQUAD)*16;
	else if(lpBIH->biBitCount == 8)	QuadSize = sizeof(RGBQUAD)*256;
	else							QuadSize = 0;//24
	int DibSize =  sizeof(BITMAPINFOHEADER) + QuadSize + lpBIH->biSizeImage;
	BYTE* pRetDib = new BYTE[DibSize];
	
	memcpy(pRetDib,pDib,DibSize);
	if(lpBIH->biBitCount == 1)
		ModifyBinDibRGBQUAD(pRetDib);
	
	return pRetDib;
}
BYTE* CImageIO::SaveImageToBuffer(BYTE* pDib, long &buffersize, DWORD nType/*= IMAGETYPE_JPG*/,int nJpgQuality/*= 50*/)
{
	if(pDib == NULL) return NULL;

	CxImage xImage;
	HANDLE hDIB = (HANDLE)pDib;
	xImage.MyCreateFromHANDLE(hDIB);

	buffersize=0;
	BYTE* buffer = NULL;
	if(nType == IMAGETYPE_UNKNOWN)
		nType = IMAGETYPE_BMP;
	if(nType == IMAGETYPE_JPG)
	{
		if(nJpgQuality == 0 ) nJpgQuality = 50;//Inserted by KSD
		xImage.SetJpegQuality(BYTE(nJpgQuality));
	}
	xImage.Encode(buffer,buffersize,nType);
	return buffer;
}

BOOL CImageIO::SaveBmpFile(LPCTSTR lpszPathName, BYTE* pDib)
{
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
	HeadSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)+QuadSize;
	FileSize = HeadSize+ImgSize;
	int DibSize = sizeof(BITMAPINFOHEADER)+QuadSize+ImgSize;

	FilehHeader.bfType = 0x4d42;     //unsigned short    bfType;
	FilehHeader.bfSize = FileSize;   //unsigned int	     bfSize;
	FilehHeader.bfReserved1 = 0;     //unsigned short    bfReserved1;
	FilehHeader.bfReserved2 = 0;     //unsigned short    bfReserved2;
	FilehHeader.bfOffBits = HeadSize;//unsigned int      bfOffBits;

	FILE* file = _tfopen(lpszPathName,_T("wb"));
	if(file==NULL)
		return FALSE;

	fwrite(&FilehHeader,sizeof(BITMAPFILEHEADER),1,file);
	fwrite(pDib,DibSize,1,file);
	fclose(file);

	return TRUE;
}


BOOL CImageIO::SaveImgToFile(LPCTSTR lpszPathName, BYTE* pImg, int w, int h,int nBitCount/*=8*/)
{

	int i,j;
	if(pImg == NULL ) return FALSE;
	if(nBitCount!=8 && nBitCount!=1) return FALSE;

	int widByte = (nBitCount*w+31)/32*4;
	int ImgSize = widByte * h;
	int nColror;
	if(nBitCount == 8)
		nColror = 256;
	else
		nColror = 2;
	int HeadSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*nColror;

	int DibSize=HeadSize+ImgSize;
	BYTE *pDib=new BYTE[DibSize];
	
	//Create InfoHeader
	BITMAPINFOHEADER* pBIH  = (BITMAPINFOHEADER*)pDib;
	pBIH->biSize			= sizeof(BITMAPINFOHEADER);
	pBIH->biWidth			= w; 
	pBIH->biHeight			= h; 
	pBIH->biPlanes			= 1; 
	pBIH->biBitCount		= (WORD)nBitCount; 
	pBIH->biCompression		= 0;
	pBIH->biSizeImage		= ImgSize; 
	pBIH->biXPelsPerMeter	= 0; 
	pBIH->biYPelsPerMeter	= 0; 
	pBIH->biClrUsed			= nColror; 
	pBIH->biClrImportant	= 0;

	//Create Palette
	BITMAPINFO* pInfoH  = (BITMAPINFO*)(LPSTR)pBIH;
	for(i=0; i<nColror-1; i++)
	{
		pInfoH->bmiColors[i].rgbRed      = BYTE(i);
		pInfoH->bmiColors[i].rgbGreen    = BYTE(i);
		pInfoH->bmiColors[i].rgbBlue     = BYTE(i);
		pInfoH->bmiColors[i].rgbReserved = 0;
	}
	pInfoH->bmiColors[nColror-1].rgbRed      = 255;
	pInfoH->bmiColors[nColror-1].rgbGreen    = 255;
	pInfoH->bmiColors[nColror-1].rgbBlue     = 255;
	pInfoH->bmiColors[nColror-1].rgbReserved = 0;

	//Copy Image
	BYTE *lpBits = pDib + HeadSize;
	if(nBitCount == 8)
	{
		for(i=0; i<h; i++) for(j=0; j<w; j++)
			 lpBits[widByte*(h-i-1)+j] = pImg[i*w+j];
	}
	else
	{
		BYTE reg = 0;
		int rem = w % 8;
		int i1=0;
		for(i=h-1;i>=0;i--){
			int j1=0;
			for(j=0;j<w;j++){
				if(pImg[i*w+j] != 0)	reg |= 0;
				else					reg |= 1;		  
				if(((j+1) % 8) == 0){
					lpBits[i1*widByte+j1] = reg;
					j1++;
					reg = 0;
				}
				else{ reg<<=1;}
			}
			if(rem != 0){
				reg <<= 8 - rem-1;
				lpBits[i1*widByte+j1] = reg;
			}
			reg=0;
			i1++;
		}
	}
	BOOL bRet = SaveImageToFile(lpszPathName, pDib);
	delete[] pDib;
	return bRet;
}


BOOL CImageIO::SaveImageToFile(LPCTSTR lpszPathName, BYTE* lpDib )
{
	CxImage xImage;

	if( lpDib == NULL) return FALSE;
	HANDLE hDIB = (HANDLE)lpDib;
	xImage.MyCreateFromHANDLE(hDIB);

	CString filename(lpszPathName);
	CString ext(FindExtension(filename));
	ext.MakeLower();
	if (ext == "") return FALSE;

	int type = 0;
	if (ext == "bmp")					type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (ext=="jpg"||ext=="jpeg")	type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (ext == "gif")				type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (ext == "png")				type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (ext == "mng")				type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (ext == "ico")				type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (ext=="tiff"||ext=="tif")	type = CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (ext=="tga")				type = CXIMAGE_FORMAT_TGA;
#endif
	else return FALSE;

	bool retval;
	retval = xImage.Save(filename, type);
	if (retval) return TRUE;
	
//	AfxMessageBox(xImage.GetLastError());
	return FALSE;
}

BOOL CImageIO::IsValidImageFile(LPCTSTR lpszPathName)
{
	CString filename(lpszPathName);
	CString ext(FindExtension(filename));
	int type = FindType(ext);
	if(type == CXIMAGE_FORMAT_UNKNOWN) return FALSE;
	CxImage xImage(type);
	BOOL b = xImage.Load(filename,type);
	xImage.Destroy();
	return b;
}
int CImageIO::GetImageTypeForCompressSave(BYTE* pDib)
{
	int nType = IMAGETYPE_UNKNOWN;
	int BitCount = ((LPBITMAPINFOHEADER)(pDib))->biBitCount;
	if(BitCount == 1) nType = IMAGETYPE_TIF;
	else nType = IMAGETYPE_JPG;
	return nType;
}
BOOL CImageIO::SaveDibCompress(FILE* fp,BYTE* pDib)
{
	int nType = GetImageTypeForCompressSave(pDib);
	long nSize;
	BYTE* pBuffer = SaveImageToBuffer(pDib,nSize,nType);
	if(pBuffer == NULL)
		return FALSE;
	fwrite(&nType,sizeof(nType),1,fp);
	fwrite(&nSize,sizeof(nSize),1,fp);
	fwrite(pBuffer,nSize,1,fp);
	delete []pBuffer;
	return TRUE;
}
BYTE* CImageIO::LoadDibCompress(FILE* fp)
{
	if(fp == NULL) return NULL;
	int nType;
	long nSize;
	fread(&nType,sizeof(nType),1,fp);
	fread(&nSize,sizeof(nSize),1,fp);
	BYTE* pBuf = new BYTE[nSize];
	fread(pBuf,nSize,1,fp);
	BYTE* pDib = LoadImageFromBuffer(pBuf,nSize,nType);
	delete []pBuf;
	return pDib;
}