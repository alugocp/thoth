#include "./thoth.hpp"
#include<iostream>
#include<fstream>
#include<iterator>
#include<stdlib.h>
#include<time.h>
using namespace Thoth;
using namespace std;
static const int PRECISION=10000;

// Constructors
Language::Language(long seed){
  srand(seed);
}
Language::Language(){
  srand(time(NULL));
}



// Debugging
void Language::print_model(){
  for(auto a=this->model.begin();a!=this->model.end();a++){
    cout << a->first << ":";
    for(auto b=a->second.begin();b!=a->second.end();b++){
      symbol_prob ls=*b;
      cout << " ("  << ls.symbol << " " << (int)(ls.prob*100) << "%)";
    }
    cout << "\n";
  }
}



// Model file I/O
void Language::save_model(string filename){
  ofstream out;
  out.open(filename);
  for(auto a=this->model.begin();a!=this->model.end();a++){
    for(auto b=a->second.begin();b!=a->second.end();b++){
      symbol_prob p=*b;
      out << a->first << " " << p.symbol << " " << (int)(p.prob*PRECISION) << "\n";
    }
  }
  out.close();
}
void Language::load_model(string filename){
  char fbuffer[256],tbuffer[256];
  string line,from,to;
  ifstream in;
  int weight;
  in.open(filename);
  while(getline(in,line)){
    const char* l=line.c_str();
    sscanf(l,"%s %s %i",fbuffer,tbuffer,&weight);
    from=string(fbuffer);
    to=string(tbuffer);
    auto search=this->model.find(from);
    if(search==this->model.end()) this->model[from]={};
    symbol_prob sp;
    sp.symbol=to;
    sp.prob=weight/(float)PRECISION;
    this->model[from].push_back(sp);
  }
  in.close();
}



// Model generation
void Language::generate_model(){
  this->analyze_words();
  this->enrich_table();
  this->clean_table();
  this->dump_table();
}
void Language::clean_table(){
  bool removed=true;
  while(removed){
    removed=false;
    auto a=this->enrich.begin();
    while(a!=this->enrich.end()){
      auto b=a->second.after.begin();
      while(b!=a->second.after.end()){
        string key=*b;
        if(key==a->first) b=a->second.after.erase(b);
        else{
          auto search=this->enrich.find(key);
          if(search==this->enrich.end()) b=a->second.after.erase(b);
          else b++;
        }
      }
      if(!a->second.after.size()){
        a=this->enrich.erase(a);
        removed=true;
      }else a++;
    }
  }
}
void Language::dump_table(){
  this->model.clear();
  for(auto a=this->enrich.begin();a!=this->enrich.end();a++){
    float p=1.0/a->second.after.size();
    vector<symbol_prob> v;
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
        symbol_prob ls;
        ls.symbol=a->second.after[b];
        ls.prob=p;
        v.push_back(ls);
      }
    }
    this->model[a->first]=v;
  }
}



// Sample data pipeline
void Language::add_word(string word){
  this->vocab.push_back(word);
}
void Language::analyze_words(){
  this->enrich.clear();
  unordered_map<string,vector<string>> substrs;
  for(auto w=this->vocab.begin();w!=this->vocab.end();w++){
    string word=*w;
    substrs.clear();
    substrs["$"]={};

    // Get substrings
    for(int l=1;l<word.size()-2;l++){
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

    // Dump into enrichment table
    for(auto i=substrs.begin();i!=substrs.end();i++){
      string s=i->first;
      vector<string> followers=substrs[s];
      auto search=this->enrich.find(s);
      if(search==this->enrich.end()){
        symbol_data data;
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
}
void Language::enrich_table(){
  auto a=this->enrich.begin();
  while(a!=enrich.end()){
    if(a->first.size()>1 && a->second.n==1) a=this->enrich.erase(a);
    else a++;
  }
}



// Word generation
string Language::new_word(int l){
  string word;
  string s="$";
  while(l>0){
    vector<symbol_prob> v=model[s];
    float p=(rand()%1000)/1000.0;
    auto i=v.begin();
    while(i!=v.end()){
      p-=(*i).prob;
      if(p<=0 || i+1==v.end()) break;
      i++;
    }
    s=(*i).symbol;
    if(s=="$") break;
    word+=s;
    l-=s.size();
  }
  return word;
}
