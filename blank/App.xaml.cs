using System;
using Xamarin.Essentials;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace blank
{
    public partial class App : Application
    {
        public App()
        {
            InitializeComponent();
            MainPage = new GeneratePage();
        }

        protected override void OnStart()
        {
            bool hasBeenInitialized = Preferences.ContainsKey("Initialized");
            if ( ! hasBeenInitialized)
            {
                Preferences.Set("Initialized", true);
                Preferences.Set("Archive", "");
            }
            
        }

        protected override void OnSleep()
        {
        }

        protected override void OnResume()
        {
        }
    }
}
