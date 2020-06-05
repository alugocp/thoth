using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;

namespace blank
{
    // Learn more about making custom code visible in the Xamarin.Forms previewer
    // by visiting https://aka.ms/xamarinforms-previewer
    [DesignTimeVisible(false)]
    public partial class MainPage : ContentPage
    {
        int count = 8;

        public MainPage()
        {
            InitializeComponent();
            picker.TextColor = new Color(204, 204, 204);
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

        String generateWord ()
        {
            return "skjdfs";
        }

        void Generate(object sender, EventArgs e)
        {
            results.Children.Clear();
            for ( int i = 0; i < count; i += 2)
                results.Children.Add(
                    new StackLayout
                    {
                        Orientation=StackOrientation.Horizontal,
                        Children =
                        {
                            new Label{ Text=generateWord(), FontSize=15, HorizontalOptions=LayoutOptions.CenterAndExpand },
                            new Label{ Text=generateWord(), FontSize=15, HorizontalOptions=LayoutOptions.CenterAndExpand }
                        }
                    });

        }
    }
}
