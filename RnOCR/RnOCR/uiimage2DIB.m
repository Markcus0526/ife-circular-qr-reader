//
//  uiimage2DIB.m
//  TestOCR
//
//  Created by cch on 7/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "Include/myType.h"
#import "uiimage2DIB.h"

typedef enum {
    ALPHA = 0,
    BLUE = 1,
    GREEN = 2,
    RED = 3
} PIXELS;

@implementation uiimage2DIB
BYTE* Make24DibFromRGBAImg(unsigned int* pImgRGBA,int w, int h)
{
	if(pImgRGBA==NULL) return NULL;
    
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
        BYTE* rgbaPixel = (BYTE*) &pImgRGBA[(h-1-i)*w+j];
		pBits[i*ByteW+j*3]   = rgbaPixel[1];
		pBits[i*ByteW+j*3+1] = rgbaPixel[2];
		pBits[i*ByteW+j*3+2] = rgbaPixel[3];
	}
	return pDib;
}
+ (UIImage *)fixrotation:(UIImage *)image
{
    
    if (image.imageOrientation == UIImageOrientationUp) return image;
    CGAffineTransform transform = CGAffineTransformIdentity;
    
    switch (image.imageOrientation) {
        case UIImageOrientationDown:
        case UIImageOrientationDownMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width, image.size.height);
            transform = CGAffineTransformRotate(transform, M_PI);
            break;
            
        case UIImageOrientationLeft:
        case UIImageOrientationLeftMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width, 0);
            transform = CGAffineTransformRotate(transform, M_PI_2);
            break;
            
        case UIImageOrientationRight:
        case UIImageOrientationRightMirrored:
            transform = CGAffineTransformTranslate(transform, 0, image.size.height);
            transform = CGAffineTransformRotate(transform, -M_PI_2);
            break;
        case UIImageOrientationUp:
        case UIImageOrientationUpMirrored:
            break;
    }
    
    switch (image.imageOrientation) {
        case UIImageOrientationUpMirrored:
        case UIImageOrientationDownMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.width, 0);
            transform = CGAffineTransformScale(transform, -1, 1);
            break;
            
        case UIImageOrientationLeftMirrored:
        case UIImageOrientationRightMirrored:
            transform = CGAffineTransformTranslate(transform, image.size.height, 0);
            transform = CGAffineTransformScale(transform, -1, 1);
            break;
        case UIImageOrientationUp:
        case UIImageOrientationDown:
        case UIImageOrientationLeft:
        case UIImageOrientationRight:
            break;
    }
    
    // Now we draw the underlying CGImage into a new context, applying the transform
    // calculated above.
    CGContextRef ctx = CGBitmapContextCreate(NULL, image.size.width, image.size.height,
                                             CGImageGetBitsPerComponent(image.CGImage), 0,
                                             CGImageGetColorSpace(image.CGImage),
                                             CGImageGetBitmapInfo(image.CGImage));
    CGContextConcatCTM(ctx, transform);
    switch (image.imageOrientation) {
        case UIImageOrientationLeft:
        case UIImageOrientationLeftMirrored:
        case UIImageOrientationRight:
        case UIImageOrientationRightMirrored:
            // Grr...
            CGContextDrawImage(ctx, CGRectMake(0,0,image.size.height,image.size.width), image.CGImage);
            break;
            
        default:
            CGContextDrawImage(ctx, CGRectMake(0,0,image.size.width,image.size.height), image.CGImage);
            break;
    }
    
    // And now we just create a new UIImage from the drawing context
    CGImageRef cgimg = CGBitmapContextCreateImage(ctx);
    UIImage *img = [UIImage imageWithCGImage:cgimg];
    CGContextRelease(ctx);
    CGImageRelease(cgimg);
    return img;
}
+(unsigned char* )uiimage2DIB24:(UIImage*)anImage {
	if( anImage == nil ) {
		return nil;
	}
    UIImage* image = [uiimage2DIB fixrotation: anImage];
 
    // Now we draw the underlying CGImage into a new context, applying the transform
    // calculated above.
    
    uint32_t* pixels=nil;
	CGContextRef context=nil;
	int width;
	int height;
	CGSize size = image.size;
    width = size.width;
    height = size.height;
	
    pixels = (uint32_t *) malloc(width * height * sizeof(uint32_t));
	
    memset(pixels, 0, width * height * sizeof(uint32_t));
	
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	
    // create a context with RGBA pixels
    context = CGBitmapContextCreate(pixels, width, height, 8, width * sizeof(uint32_t), colorSpace, kCGBitmapByteOrder32Little | kCGImageAlphaPremultipliedLast);
	
    // paint the bitmap to our context which will fill in the pixels array
    CGContextDrawImage(context, CGRectMake(0, 0, width, height), [image CGImage]);
	
	CGColorSpaceRelease( colorSpace ); 
    unsigned char* pDIB24 = Make24DibFromRGBAImg( pixels,width, height);
    if( context ) {
		CGContextRelease(context);
        context = nil;
	}
	if( pixels ) {
		free(pixels);
        pixels = nil;
	}
	
	return pDIB24;
}

@end
