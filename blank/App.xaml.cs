﻿using System;
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
        }

        protected override void OnSleep()
        {
        }

        protected override void OnResume()
        {
        }
    }
}
