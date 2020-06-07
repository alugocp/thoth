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
        public ArchivePage()
        {
            InitializeComponent();
            NavigationPage.SetHasNavigationBar(this, false);
        }
        void SwapToGenearte(object sender, EventArgs e)
        {
            Application.Current.MainPage = new NavigationPage(new GeneratePage());
        }
    }
}