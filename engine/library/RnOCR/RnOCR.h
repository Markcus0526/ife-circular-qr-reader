//
//  RnOCR.h
//  RnOCR
//
//  Created by albert on 6/14/13.
//  Copyright (c) 2013 albert. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIImage.h>

@interface RnOCR : NSObject

+(NSString*) recog:(UIImage*)img rstName:(NSString*)rst;

@end

