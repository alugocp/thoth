#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<vector>
#include<string>
#include<unordered_map>
#include<iostream>
#include<iterator>

using namespace std;

//namespace Thoth{

/*class Language{
public:
  Language();
  ~Language();
  void addWord(const char* word);
  bool isMutable();
  void setMutable(bool m);


private:
  bool mutable;

};*/

//}

struct SymbolData{
  vector<string> after;
  int n;
};
struct LikelySymbol{
  string symbol;
  float prob;
};

// Main
int main(int argc,char** argv){

  srand(time(NULL));

  // Variables
  unordered_map<string,vector<LikelySymbol>> model;
  vector<string> vocab;

  // Add words
  vocab.push_back("xochitl");
  vocab.push_back("nantlitl");
  vocab.push_back("tonali");
  vocab.push_back("quetzalcoatl");
  vocab.push_back("xocolatl");
  vocab.push_back("huitzilpochtli");

  // Generate model
  unordered_map<string,SymbolData> enrich;
  unordered_map<string,vector<string>> substrs;
  for(auto w=vocab.begin();w!=vocab.end();w++){// Analysis pass
    string word=*w;
    substrs.clear();
    substrs["$"]={};
    for(int l=1;l<word.size()-2;l++){// Get all substrings
      for(int a=0;a<=word.size()-l;a++){
        string sub=word.substr(a,l);
        auto search=substrs.find(sub);
        if(search==substrs.end()) substrs[sub]={};
        if(!a) substrs["$"].push_back(sub);
        if(a+l+l<word.size()-1) substrs[sub].push_back(word.substr(a+l,l));
        else if(a+l==word.size()) substrs[sub].push_back("$");
        else substrs[sub].push_back(word.substr(a+l));
      }
    }
    for(auto i=substrs.begin();i!=substrs.end();i++){// Dump into enrichment set
      string s=i->first;
      vector<string> followers=substrs[s];
      auto search=enrich.find(s);
      if(search==enrich.end()){
        SymbolData data;
        data.after=followers;
        data.n=1;
        enrich[s]=data;
      }else{
        vector<string> *dest=&(search->second.after);
        dest->insert(dest->end(),make_move_iterator(followers.begin()),make_move_iterator(followers.end()));
        search->second.n++;
      }
    }
  }

  auto iter=enrich.begin();
  while(iter!=enrich.end()){// Enrichment pass
    string key=iter->first;
    if(key.size()>1 && iter->second.n==1){
      iter=enrich.erase(iter);
    }else{
      iter++;
    }
  }

  bool removed=true;
  while(removed){
    removed=false;
    auto a=enrich.begin();
    while(a!=enrich.end()){// Cleaning pass
      auto b=a->second.after.begin();
      while(b!=a->second.after.end()){
        string key=*b;
        if(key==a->first){
          b=a->second.after.erase(b);
        }else{
          auto search=enrich.find(key);
          if(search==enrich.end()){
            b=a->second.after.erase(b);
          }else{
            b++;
          }
        }
      }
      if(!a->second.after.size()){
        a=enrich.erase(a);
        removed=true;
      }else{
        a++;
      }
    }
  }

  // Populate model
  for(auto a=enrich.begin();a!=enrich.end();a++){
    float p=1.0/a->second.after.size();
    vector<LikelySymbol> v;
    for(int b=0;b<a->second.after.size();b++){
      bool added=false;
      for(int c=0;c<v.size();c++){
        if(v[c].symbol==a->second.after[b]){
          v[c].prob+=p;
          added=true;
          break;
        }
      }
      if(!added){
        LikelySymbol ls;
        ls.symbol=a->second.after[b];
        ls.prob=p;
        v.push_back(ls);
      }
    }
    model[a->first]=v;
  }

  // Logging purposes
  for(auto a=model.begin();a!=model.end();a++){
    cout << a->first << ":";
    for(auto b=a->second.begin();b!=a->second.end();b++){
      LikelySymbol ls=*b;
      cout << " (" << ls.prob*100 << "% " << ls.symbol << ")";
    }
    cout << "\n";
  }

  // Generate new words
  cout << "\n";
  for(int a=0;a<10;a++){
    string s="$";
    int len=0;
    while(len<12){
      vector<LikelySymbol> v=model[s];
      float p=(rand()%1000)/1000.0;
      auto i=v.begin();
      while(i!=v.end()){
        p-=(*i).prob;
        if(p<=0 || i+1==v.end()) break;
        i++;
      }
      s=(*i).symbol;
      if(s=="$") break;
      cout << s;
      len+=s.size();
    }
    cout << "\n";
  }
}
