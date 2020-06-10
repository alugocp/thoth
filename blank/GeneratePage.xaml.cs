using System;
using System.ComponentModel;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Essentials;

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
            countLabel.Text = count.ToString();
        }
        void DecrementCount(object sender, EventArgs e)
        {
            count -= 4;
            if (count < 4) count = 4;
            countLabel.Text = count.ToString();
        }

        void Generate(object sender, EventArgs e)
        {
            Task.Run(() => {

                // Call API
                string[] words = api.new_words(count,6);

                // Update UI
                MainThread.BeginInvokeOnMainThread(() =>
                {
                    results.Children.Clear();
                    for (int a = 0; a < count; a += 2)
                    {
                        results.Children.Add(new StackLayout
                        {
                            Orientation = StackOrientation.Horizontal,
                            Children = {
                                new Label { HorizontalOptions = LayoutOptions.CenterAndExpand, FontSize = 15, Text = words[a] },
                                new Label { HorizontalOptions = LayoutOptions.CenterAndExpand, FontSize = 15, Text = words[a+1] }
                            }
                        });
                    }
                });
            });

        }

        void SwapToArchive ( object sender, EventArgs e)
        {
            Application.Current.MainPage = new NavigationPage(new ArchivePage());
        }
    }
}
