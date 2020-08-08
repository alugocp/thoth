using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;
using Xamarin.Forms.Xaml;

namespace blank
{
    public partial class ArchivePage : ContentPage
    {
        bool originalStyle = true;

        public ArchivePage()
        {
            InitializeComponent();
            NavigationPage.SetHasNavigationBar(this, false);
        }
        void SwapToGenearte(object sender, EventArgs e)
        {
            Application.Current.MainPage = new NavigationPage(new GeneratePage());
        }

        private async void ButtonTheme(object sender, EventArgs e)
        {


            ICollection<ResourceDictionary> mergedDictionaries = Application.Current.Resources.MergedDictionaries;
            if (mergedDictionaries != null)
            {
                mergedDictionaries.Clear();

                if (originalStyle)
                {
                    mergedDictionaries.Add(new DarkTheme());
                    originalStyle = false;

                }
                else
                {
                    mergedDictionaries.Add(new LightTheme());
                    originalStyle = true;
                }

            }
        }
    }
}