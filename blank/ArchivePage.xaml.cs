using System;
using System.Collections.Generic;
using Xamarin.Forms;

namespace blank
{
    public partial class ArchivePage : ContentPage
    {

        bool originalStyle = true;
        private Seeds seeds;

        public ArchivePage()
        {
            InitializeComponent();
            NavigationPage.SetHasNavigationBar(this, false);
            seeds=new Seeds();
            loadData();

        }

        void loadData()
        {

            archived.Children.Clear();
            seeds.getSeeds().ForEach(t => {
                string name=t.name;
                var del = new Button { FontSize=14, Text = "Delete", BackgroundColor = Color.FromHex("#40996a") };
                del.Clicked += async (s, e) =>
                {
                    seeds.removeSeed(t.l,t.w);
                    loadData();
                };

                archived.Children.Add(new StackLayout
                {
                    Orientation = StackOrientation.Horizontal,
                    Children = {
                        new Label { HorizontalOptions = LayoutOptions.StartAndExpand, FontSize = 15, Text = name },
                         del
                    }
                });
            });
            if(archived.Children.Count==0){
                archived.Children.Add(new Label {FontSize=15,Text="You have no saved seeds",VerticalTextAlignment=TextAlignment.Center,HorizontalOptions = LayoutOptions.CenterAndExpand});
            }
        }


            void SwapToGenerate(object sender, EventArgs e)
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