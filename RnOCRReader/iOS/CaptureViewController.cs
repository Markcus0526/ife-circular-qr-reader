using System;
using System.Drawing;
using System.Timers;
using AVFoundation;
using CoreAnimation;
using CoreFoundation;
using CoreGraphics;
using CoreMedia;
using CoreVideo;
using Foundation;
using RnOCRBinding;
using UIKit;

namespace RnOCRReader.iOS
{
	public partial class CaptureViewController : UIViewController
	{
		#region Private Variables
		//private NSError Error;
		#endregion

		#region Computed Properties
		public UILabel lblResult;

		AVCaptureDeviceInput input;
		AVCaptureVideoDataOutput output;
		//AVCaptureConnection captureConnection;
		DispatchQueue queue;
		OutputRecorder recorder;
		#endregion

		public CaptureViewController(IntPtr handle) : base (handle)
		{
		}

		public override void DidReceiveMemoryWarning()
		{
			// Releases the view if it doesn't have a superview.
			base.DidReceiveMemoryWarning();

			// Release any cached data, images, etc that aren't in use.
		}

		#region View lifecycle

		public override void ViewDidLoad()
		{

			CALayer _layer = new CALayer();
			base.ViewDidLoad();
			var captureSession = new AVCaptureSession();
			var previewLayer = new AVCaptureVideoPreviewLayer(captureSession)
			{
				VideoGravity = AVLayerVideoGravity.ResizeAspectFill,
				Frame = this.View.Bounds
			};

			NSError error;

			var device = AVCaptureDevice.DefaultDeviceWithMediaType(AVMediaType.Video);
			if (device.IsFocusModeSupported(AVCaptureFocusMode.AutoFocus))
			{
				//device.FocusMode = AVCaptureFocusMode.AutoFocus;

				device.LockForConfiguration(out error);

				device.FocusMode = AVCaptureFocusMode.ContinuousAutoFocus;

				// Configure stream for 15 frames per second (fps)
				device.ActiveVideoMinFrameDuration = new CMTime(1, 2);

				device.UnlockForConfiguration();
			}

			//lblResult.Text = device.FocusMode.ToString();
			//device.FocusMode = AVCaptureFocusMode.AutoFocus;



			input = new AVCaptureDeviceInput(device, out error);

			captureSession.AddInput(input);

			this.View.Layer.AddSublayer(previewLayer);

			//output = new AVCaptureStillImageOutput();
			//output.OutputSettings = NSDictionary.FromObjectAndKey(new NSString("AVVideoCodecKey"), new NSString("AVVideoCodecJPEG"));
			// Configure and attach to the output to the session
			output = new AVCaptureVideoDataOutput();
			var settings = new AVVideoSettingsUncompressed();
			settings.PixelFormatType = CVPixelFormatType.CV32BGRA;
			output.WeakVideoSettings = settings.Dictionary;

			queue = new DispatchQueue("ManCamQueue");
			recorder = new OutputRecorder(this);
			output.SetSampleBufferDelegate(recorder, queue);

			captureSession.AddOutput(output);

			lblResult = new UILabel(new CGRect((this.View.Frame.Width - 200) / 2, this.View.Frame.Height - 150, 200, 50));
			lblResult.Lines = 0;
			lblResult.LineBreakMode = UILineBreakMode.CharacterWrap;
			lblResult.TextColor = UIColor.White;
			lblResult.Text = "";

			var btnClear = new UIButton(new CGRect((this.View.Frame.Width - 200) / 2, this.View.Frame.Height - 200, 200, 50));
			btnClear.SetTitle("Clear", UIControlState.Normal);
			btnClear.TouchUpInside += HandleButtClearResultTouchUpInside;

			this.View.Add(lblResult);
			this.View.Add(btnClear);

			_layer.Frame = this.View.Bounds;

			_layer.Delegate = new CustomLayerDelegate();
			_layer.SetNeedsDisplay();
			this.View.Layer.AddSublayer(_layer);

			captureSession.StartRunning();
		}

		void HandleButtClearResultTouchUpInside(object sender, EventArgs e)
		{
			lblResult.Text = "";
			recorder.captureing = true;
		}

		public override void ViewWillAppear(bool animated)
		{
			base.ViewWillAppear(animated);
		}

		public override void ViewDidAppear(bool animated)
		{
			base.ViewDidAppear(animated);
		}

		public override void ViewWillDisappear(bool animated)
		{
			base.ViewWillDisappear(animated);
		}

		public override void ViewDidDisappear(bool animated)
		{
			base.ViewDidDisappear(animated);
		}

		#endregion
	}

	public class CustomLayerDelegate : CALayerDelegate
	{
		public override void DrawLayer(CALayer layer, CGContext context)
		{
			//layer.Frame = new CGRect(0,0,ImageView.Image.Size.Width,ImageView.Image.Size.Height);
			//var context=UIGraphics.GetCurrentContext();
			CGRect layerFrame = layer.Frame;

			GlobalVar.captureWidth = layer.Frame.Width * 3 / 4;

			nfloat kEdgeInset = (layerFrame.Width - GlobalVar.captureWidth) / 2;
			nfloat kLineLength = 20;
			nfloat kTopOffset = GlobalVar.catureTop;

			context.BeginPath();
			context.SetLineWidth(3);
			context.MoveTo(kEdgeInset + kLineLength, kTopOffset);
			context.AddLineToPoint(kEdgeInset, kTopOffset);
			context.AddLineToPoint(kEdgeInset, kTopOffset + kLineLength);
			//context.ClosePath ();

			//UIColor.White.SetStroke ();
			context.SetStrokeColor(UIColor.Black.CGColor);
			context.DrawPath(CGPathDrawingMode.Stroke);

			context.BeginPath();
			context.SetLineWidth(3);
			context.MoveTo(kEdgeInset, kTopOffset + GlobalVar.captureWidth - kLineLength);
			context.AddLineToPoint(kEdgeInset, kTopOffset + GlobalVar.captureWidth);
			context.AddLineToPoint(kEdgeInset + kLineLength, kTopOffset + GlobalVar.captureWidth);
			context.DrawPath(CGPathDrawingMode.Stroke);
			//context.ClosePath ();

			//UIColor.White.SetStroke ();
			//context.SetStrokeColorWithColor (UIColor.White.CGColor);
			//context.DrawPath(CGPathDrawingMode.Stroke);

			//context.SetStrokeColorWithColor (UIColor.White.CGColor);
			//context.DrawPath(CGPathDrawingMode.Stroke);

			context.BeginPath();
			context.SetLineWidth(3);
			context.MoveTo(layerFrame.Width - kEdgeInset - kLineLength, kTopOffset + GlobalVar.captureWidth);
			context.AddLineToPoint(layerFrame.Width - kEdgeInset, kTopOffset + GlobalVar.captureWidth);
			context.AddLineToPoint(layerFrame.Width - kEdgeInset, kTopOffset + GlobalVar.captureWidth - kLineLength);
			context.DrawPath(CGPathDrawingMode.Stroke);

			context.BeginPath();
			context.SetLineWidth(3);
			context.MoveTo(layerFrame.Width - kEdgeInset - kLineLength, kTopOffset);
			context.AddLineToPoint(layerFrame.Width - kEdgeInset, kTopOffset);
			context.AddLineToPoint(layerFrame.Width - kEdgeInset, kTopOffset + kLineLength);
			context.DrawPath(CGPathDrawingMode.Stroke);

			//layer.BackgroundColor = UIColor.Green.CGColor;
			layer.BorderWidth = 2.0f;
			//layer.BorderColor = UIColor.White.CGColor;
		}
	}

	public class OutputRecorder : AVCaptureVideoDataOutputSampleBufferDelegate
	{
		#region Computed Properties
		public bool captureing = true;

		private CaptureViewController parent;
		private int tickCount = 0;
		#endregion

		#region Constructors
		public OutputRecorder(CaptureViewController parent)
		{
			this.parent = parent;

			tickCount = 0;
		}
		#endregion

		#region Private Methods
		private UIImage GetImageFromSampleBuffer(CMSampleBuffer sampleBuffer)
		{

			// Get a pixel buffer from the sample buffer
			using (var pixelBuffer = sampleBuffer.GetImageBuffer() as CVPixelBuffer)
			{
				// Lock the base address

				pixelBuffer.Lock(CVPixelBufferLock.None);

				// Prepare to decode buffer
				var flags = CGBitmapFlags.PremultipliedFirst | CGBitmapFlags.ByteOrder32Little;

				// Decode buffer - Create a new colorspace
				using (var cs = CGColorSpace.CreateDeviceRGB())
				{

					// Create new context from buffer
					using (var context = new CGBitmapContext(pixelBuffer.BaseAddress,
						pixelBuffer.Width,
						pixelBuffer.Height,
						8,
						pixelBuffer.BytesPerRow,
						cs,
						(CGImageAlphaInfo)flags))
					{

						// Get the image from the context
						using (var cgImage = context.ToImage())
						{
							UIImage image = UIImage.FromImage(cgImage, 1, UIImageOrientation.Right);
							// Unlock and return image
							pixelBuffer.Unlock(CVPixelBufferLock.ReadOnly);
							//return null;
							return image;
						}
					}
				}
			}
		}

		private UIImage CropImage(UIImage originalImage, nfloat x, nfloat y, nfloat width, nfloat height)
		{
			// Use smallest side length as crop square length
			nfloat rate = originalImage.Size.Width / parent.View.Frame.Size.Width;

			//nfloat x, y;
			//x = (nfloat)((originalImage.Size.Width - squareLength) / 2.0);
			//y = (nfloat)((originalImage.Size.Height - squareLength) / 2.0);

			//This Rect defines the coordinates to be used for the crop
			CGRect croppedRect = CGRect.FromLTRB(x * rate, y * rate, (x + width) * rate, (y + height) * rate);

			// Center-Crop the image
			UIGraphics.BeginImageContextWithOptions(croppedRect.Size, false, originalImage.CurrentScale);
			originalImage.Draw(new CGPoint(-croppedRect.X, -croppedRect.Y));
			UIImage croppedImage = UIGraphics.GetImageFromCurrentImageContext();
			UIGraphics.EndImageContext();

			return croppedImage;
		}

		#endregion

		#region Override Methods
		public override void DidOutputSampleBuffer(AVCaptureOutput captureOutput, CMSampleBuffer sampleBuffer, AVCaptureConnection connection)
		{
			// Trap all errors
			try
			{
				InvokeOnMainThread(delegate
				{
					if (!captureing)
						return;

					if (tickCount < 15)
					{
						tickCount++;
						return;
					}
					else
						tickCount = 0;

					using (var image = GetImageFromSampleBuffer(sampleBuffer))
					{
						nfloat edgeInset = (parent.View.Frame.Size.Width - GlobalVar.captureWidth) / 2;
						var imageView = new UIImageView(
							new CGRect(edgeInset,
									   GlobalVar.catureTop,
									   GlobalVar.captureWidth,
									   GlobalVar.captureWidth));


						UIImage cropImage = CropImage(image,
													  edgeInset,
													  GlobalVar.catureTop,
													  GlobalVar.captureWidth,
													  GlobalVar.captureWidth);
						imageView.Image = cropImage;

						//cropImage.SaveToPhotosAlbum((img, err) =>
						//{
						//});

						string state = "";
						string uuid = RnOCR.Recog(cropImage, rst: state);

						if (uuid.Length > 2)
						{
							captureing = false;
							parent.lblResult.Text = uuid;
						}
						else
						{
							captureing = true;
							parent.lblResult.Text = "";
						}
					}
				});

				// IMPORTANT: You must release the buffer because AVFoundation has a fixed number
				// of buffers and will stop delivering frames if it runs out.
				sampleBuffer.Dispose();
			}
			catch (Exception e)
			{
				// Report error
				Console.WriteLine("Error sampling buffer: {0}", e.Message);
			}
		}
		#endregion

	}
}

