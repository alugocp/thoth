using System;
using System.Collections.Generic;
using Xamarin.Essentials;

namespace blank{

public class Seeds
{
    private static string KEY = "seeds";
    private List<Seed> seeds = new List<Seed>();

	public Seeds(){
        string[] s = Preferences.Get(KEY, "").Split(';');
        foreach (string a in s)
        {
            if (!a.Contains(".")) continue;
            string[] b = a.Split('.');
            if(b.Length!=3) continue;
            Seed t = new Seed(b[0],uint.Parse(b[1]), uint.Parse(b[2]));
            seeds.Add(t);
            Console.WriteLine(t);
        }
    }

    private string stringify() {
        string str = "";
        for (int a = 0; a < seeds.Count; a++) {
            if (a > 0) str += ";";
            str +=stringify(seeds[a]);
        }
        return str;
    }

    // Public interface functions
    public string stringify(Seed s){
        return s.name+"."+s.l.ToString()+"."+s.w.ToString();
    }
    public List<Seed> getSeeds(){
        return seeds;
    }
    public void addSeed(string name,uint l,uint w) {
        addSeed(new Seed(name,l,w));
    }
    public void addSeed(Seed s){
        seeds.Add(s);
        Preferences.Set(KEY, stringify());
    }
    public void removeSeed(uint l,uint w) {
        for (int a = 0; a < seeds.Count; a++) {
            if(seeds[a].l==l && seeds[a].w==w){
                seeds.RemoveAt(a);
                break;
            }
        }
        Preferences.Set(KEY, stringify());
    }
}

}