using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;

namespace blank
{
    // Learn more about making custom code visible in the Xamarin.Forms previewer
    // by visiting https://aka.ms/xamarinforms-previewer
    [DesignTimeVisible(false)]
    public partial class GeneratePage : ContentPage
    {
        private ThothAPI api;
        int count = 8;

        public GeneratePage()
        {
            InitializeComponent();
            NavigationPage.SetHasNavigationBar(this, false);
            picker.TextColor = new Color(204, 204, 204);
            api=new ThothAPI();
            api.new_lang();
        }
        void IncrementCount(object sender, EventArgs e)
        {
            count += 4;
            if (count > 40) count = 40;
            countLabel.Text = "" + count;
        }
        void DecrementCount(object sender, EventArgs e)
        {
            count -= 4;
            if (count < 4) count = 4;
            countLabel.Text = "" + count;
        }

        void Generate(object sender, EventArgs e)
        {
            results.Children.Clear();
            for (int i = 0; i < count; i += 2)
            {
                Label first = new Label{HorizontalOptions = LayoutOptions.CenterAndExpand,FontSize = 15};
                Label second = new Label { HorizontalOptions = LayoutOptions.CenterAndExpand, FontSize = 15 };
                results.Children.Add(new StackLayout { Orientation = StackOrientation.Horizontal, Children = { first, second } });
                //api.new_word(6,word => first.Text=word);
                //api.new_word(6,word => second.Text=word);
                first.Text = "Teehee";
                second.Text = "Toohoo";
            }

        }

        void SwapToArchive ( object sender, EventArgs e)
        {
            Application.Current.MainPage = new NavigationPage(new ArchivePage());
        }
    }
}
