﻿using System;
using System.ComponentModel;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Essentials;
using System.Collections.Generic;

namespace blank
{
    // Learn more about making custom code visible in the Xamarin.Forms previewer
    // by visiting https://aka.ms/xamarinforms-previewer
    [DesignTimeVisible(false)]
    public partial class GeneratePage : ContentPage
    {

        bool originalStyle=true;
        private ThothAPI api;
        private Seeds seeds;
        int count = 8;

        public GeneratePage()
        {
            InitializeComponent();
            NavigationPage.SetHasNavigationBar(this, false);
            picker.TextColor = new Color(204, 204, 204);

            seeds = new Seeds();
            api =new ThothAPI();
            api.new_lang();

            List<String> options=new List<String>();
            foreach(Seed s in seeds.getSeeds()){
                options.Add(s.name);
            }
            picker.ItemsSource=options;

            Generate();
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

        void GenerateAction(object sender, EventArgs e){
            if(picker.SelectedIndex<0){
                api.new_lang();
            }
            Generate();
        }
        void Generate()
        {

            Task.Run(() => {

                if(picker.SelectedIndex>-1){
                    Seed s=seeds.getSeeds()[picker.SelectedIndex];
                    api.load_lang(s.l,s.w);
                }

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

        void SaveSeed(object sender, EventArgs e)
        {
            Seed seed = api.save_lang();
            seeds.addSeed(seed);
            List<String> options=new List<String>();
            foreach(String s in picker.ItemsSource){
                options.Add(s);
            }
            options.Add(seed.name);
            picker.ItemsSource=options;
        }

        void SwapToArchive ( object sender, EventArgs e)
        {
            Application.Current.MainPage = new NavigationPage(new ArchivePage());
            
        }

        private async void ButtonTheme(object sender, EventArgs e){
            

            ICollection<ResourceDictionary> mergedDictionaries = Application.Current.Resources.MergedDictionaries;
            if (mergedDictionaries != null)
            {
            mergedDictionaries.Clear();

            if(originalStyle){
                    mergedDictionaries.Add(new DarkTheme());
                    originalStyle=false;

            }
            else{
                    mergedDictionaries.Add(new LightTheme());
                    originalStyle=true;
            }

            }
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
