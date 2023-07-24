using Xamarin.Forms;

namespace PGCodeReader
{
	public partial class App : Application
	{
		public App()
		{
			InitializeComponent();

			MainPage = new CameraView();
		}

		protected override void OnStart()
		{
			// Handle when your app starts
		}

		protected override void OnSleep()
		{
			// Handle when your app sleeps
		}

		protected override void OnResume()
		{
			// Handle when your app resumes
		}
	}
}
