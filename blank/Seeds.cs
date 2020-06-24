using System;
using System.Collections.Generic;
using Xamarin.Essentials;

public class Seeds
{
    private static string KEY = "seeds";
    private List<Tuple<uint,uint>> seeds = new List<Tuple<uint, uint>>();

	public Seeds(){
        string[] s = Preferences.Get(KEY, "").Split(';');
        foreach (string a in s)
        {
            if (!a.Contains(".")) continue;
            string[] b = a.Split('.');
            Tuple<uint, uint> t = Tuple.Create(uint.Parse(b[0]), uint.Parse(b[1]));
            seeds.Add(t);
            Console.WriteLine(t);
        }
    }

    private string stringify() {
        string str = "";
        for (int a = 0; a < seeds.Count; a++) {
            if (a > 0) str += ";";
            str +=stringify(seeds[a].Item1,seeds[a].Item2);
        }
        return str;
    }

    // Public interface functions
    public string stringify(uint l,uint w){
        return l.ToString()+"."+w.ToString();
    }
    public List<Tuple<uint,uint>> getSeeds(){
        return seeds;
    }
    public void addSeed(uint l,uint w) {
        seeds.Add(Tuple.Create(w, l));
        Preferences.Set(KEY, stringify());
    }
    public void removeSeed(uint l,uint w) {
        for (int a = 0; a < seeds.Count; a++) {
            if(seeds[a].Item1==l && seeds[a].Item2==w){
                seeds.RemoveAt(a);
                break;
            }
        }
        Preferences.Set(KEY, stringify());
    }
}
