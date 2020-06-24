using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Essentials;
using Xamarin.Forms;
using Xamarin.Forms.Internals;
using Xamarin.Forms.Xaml;

namespace blank
{
    public partial class ArchivePage : ContentPage
    {
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
                string name=seeds.stringify(t.Item1,t.Item2);
                var del = new Button { Text = "Delete", BackgroundColor = Color.FromHex("#40996a") };
                del.Clicked += async (s, e) =>
                {
                    seeds.removeSeed(t.Item1,t.Item2);
                    loadData();
                };

                archived.Children.Add(new StackLayout
                {
                    Orientation = StackOrientation.Horizontal,
                    Children = {
                        new Label { HorizontalOptions = LayoutOptions.CenterAndExpand, FontSize = 15, Text = name },
                         del
                    }
                });
            });

            /*String[] ArchivedNames = Preferences.Get("Archive", "").Split(',').Where(i => i != "").ToArray();
            ArchivedNames.ForEach(name =>
            {
                var del = new Button { Text = "Delete", BackgroundColor = Color.FromHex("#40996a") };
                del.Clicked += async (s, e) =>
                {
                    String newData = String.Join("," , ArchivedNames.Where(_name => name != _name).ToList());
                    Preferences.Set("Archive", newData);
                    loadData();
                };

                archived.Children.Add(new StackLayout
                {
                    Orientation = StackOrientation.Horizontal,
                    Children = {
                        new Label { HorizontalOptions = LayoutOptions.CenterAndExpand, FontSize = 15, Text = name },
                         del
                    }
                });
            });*/
        }

            void SwapToGenerate(object sender, EventArgs e)
        {
            Application.Current.MainPage = new NavigationPage(new GeneratePage());
        }
    }
}