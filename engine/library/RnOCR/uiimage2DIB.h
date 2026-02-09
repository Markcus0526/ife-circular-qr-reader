//
//  uiimage2DIB.h
//  TestOCR
//
//  Created by cch on 7/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>

@interface uiimage2DIB : NSObject
{
}
+ (UIImage *)fixrotation:(UIImage *)image;
+(unsigned char* )uiimage2DIB24:(UIImage*)anImage;
@end
