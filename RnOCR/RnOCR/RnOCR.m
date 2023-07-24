//
//  RnOCR.m
//  RnOCR
//
//  Created by albert on 6/14/13.
//  Copyright (c) 2013 albert. All rights reserved.
//
#import "Include/myType.h"
#import "RnOCR.h"
#import "uiimage2DIB.h"
#import "FindRecogDigit.h"
#import "ImageBase.h"

@implementation RnOCR {    
}

+(NSString*) recog:(UIImage*)img rstName:(NSString*)rst
{
    NSString* retcode = @"";
    
    BYTE* pDib = [uiimage2DIB uiimage2DIB24:img];
    if (pDib == NULL)
        return @"-1";
    
    int w,h;
    BYTE* grayImg = CImageBase::MakeGrayImgFromAnyDib(pDib,w,h);
    if (grayImg == NULL)
        return @"-2";
    
    char uuid[40];
    int nret = CFindRecogDigit::Find_RecogGrayImg(grayImg,w,h,uuid);
    
    if (nret == 2)
        retcode = @"2";
    else if (nret == 1)
        retcode = [NSString stringWithFormat:@"%s", uuid];
    else
        retcode = [NSString stringWithFormat:@"%i", nret];
        
    return retcode;
    //return 0;
}

//+(NSInteger) recog(UIImage* img,char* rst)
//{
//    //NSString *filepath=[[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:[NSString stringWithUTF8String:path]];
//    //UIImage* img = [UIImage imageWithContentsOfFile:filepath];
//
//    BYTE* pDib = [uiimage2DIB uiimage2DIB24:img];
//    if (pDib == NULL)
//        return 0;
//    CFindRecogDigit digit;
//    int w,h;
//    BYTE* grayImg = CImageBase::MakeGrayImgFromAnyDib(pDib,w,h);
//    int nret = digit.Find_RecogGrayImg(grayImg,w,h,rst);
//    return nret;
//}

@end
