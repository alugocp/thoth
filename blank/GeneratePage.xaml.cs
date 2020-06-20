using System;
using System.ComponentModel;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Essentials;
using System.Linq;
using Xamarin.Forms.Internals;

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

            // Load archive

            String[] ArchivedNames = Preferences.Get("Archive", "").Split(',');
            ArchivedNames.ForEach(name =>{
                if (name != "")
                    picker.Items.Add(name);
            });

            api =new ThothAPI();
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
            Random rand = new Random();
            String key = (picker.SelectedItem == null ? "" : picker.SelectedItem).ToString();
            uint[] langSeeds = Preferences.Get("_" + key, "").Split(',').Select( i => Convert.ToUInt32(i)).ToArray();

            Task.Run(() => {

                if (key != "") api.load_lang(langSeeds[0], langSeeds[1]);

                // Call API
                string[] words = api.new_words(count, 6 );

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

        async void SaveSeedAsync(object sender, EventArgs e)
        {
            Tuple<uint, uint> seeds = api.save_lang();
            String saveData = seeds.Item1.ToString() + ',' + seeds.Item2.ToString();
            String getName = await InputBox(this.Navigation);

            Preferences.Set('_' + getName, saveData);
            Preferences.Set("Archive", Preferences.Get("Archive", "") + getName + ",");

            String[] ArchivedNames = Preferences.Get("Archive", "").Split(',');
            picker.Items.Clear();
            ArchivedNames.ForEach(name => {
                if (name != "")
                    picker.Items.Add(name);
            });
        }

        void SwapToArchive ( object sender, EventArgs e)
        {
            Application.Current.MainPage = new NavigationPage(new ArchivePage());
        }

        // If it works it works https://forums.xamarin.com/discussion/comment/110002/#Comment_110002
        public static Task<string> InputBox(INavigation navigation)
        {
            // wait in this proc, until user did his input 
            var tcs = new TaskCompletionSource<string>();

            var lblTitle = new Label { Text = "Name seed:", HorizontalOptions = LayoutOptions.Center, FontAttributes = FontAttributes.Bold };
            var txtInput = new Entry { Text = "" };

            var btnOk = new Button
            {
                Text = "Ok",
                WidthRequest = 100,
                BackgroundColor = Color.FromHex("#40996a")
            };
            btnOk.Clicked += async (s, e) =>
            {
                // close page
                var result = txtInput.Text;
                await navigation.PopModalAsync();
                // pass result
                tcs.SetResult(result);
            };

            var btnCancel = new Button
            {
                Text = "Cancel",
                WidthRequest = 100,
                BackgroundColor = Color.FromHex("#40996a")
            };
            btnCancel.Clicked += async (s, e) =>
            {
                // close page
                await navigation.PopModalAsync();
                // pass empty result
                tcs.SetResult(null);
            };

            var slButtons = new StackLayout
            {
                Orientation = StackOrientation.Horizontal,
                Children = { btnOk, btnCancel },
            };

            var layout = new StackLayout
            {
                Padding = new Thickness(0, 40, 0, 0),
                VerticalOptions = LayoutOptions.StartAndExpand,
                HorizontalOptions = LayoutOptions.CenterAndExpand,
                Orientation = StackOrientation.Vertical,
                Children = { lblTitle, txtInput, slButtons },
                BackgroundColor = Color.FromHex("#33333F")
            };

            // create and show page
            var page = new ContentPage
            {
                BackgroundColor = Color.FromHex("#33333F")
            };
            page.Content = layout;
            navigation.PushModalAsync(page);
            // open keyboard
            txtInput.Focus();

            // code is waiting her, until result is passed with tcs.SetResult() in btn-Clicked
            // then proc returns the result
            return tcs.Task;
        }
    }
}
