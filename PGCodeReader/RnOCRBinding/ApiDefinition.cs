using System;
using Foundation;
using UIKit;

namespace RnOCRBinding
{
	// @interface RnOCR : NSObject
	[BaseType(typeof(NSObject))]
	interface RnOCR
	{
		// +(NSInteger)recog:(UIImage *)img rstName:(NSString *)rst;
		[Static]
		[Export("recog:rstName:")]
		string Recog(UIImage img, string rst);
	}
}
