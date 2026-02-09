using Foundation;
using UIKit;

namespace RnOCR
{
	// @interface RnOCR : NSObject
	[BaseType (typeof(NSObject))]
	interface RnOCR
	{
		// +(NSString *)recog:(UIImage *)img rstName:(NSString *)rst;
		[Static]
		[Export ("recog:rstName:")]
		string Recog (UIImage img, string rst);
	}
}
