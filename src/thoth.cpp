#include "./thoth.hpp"
#include<iostream>
#include<fstream>
#include<iterator>
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace thoth;
using namespace std;
static const int PRECISION=10000;

// Constructors
Language::Language(long seed){
  this->set_seed(seed);
}
Language::Language(){
  this->set_seed(time(NULL));
}
void Language::set_seed(long seed){
  this->seed=seed;
  srand(seed);
}



// Debugging
void Language::print_model(){
  cout << "Seed #" << this->seed << "\n";
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
  vector<string> targets=enrich["$"].after;
  for(auto a=targets.begin();a!=targets.end();a++){
    auto b=enrich[*a].after.begin();
    while(b!=enrich[*a].after.end()){
      if(*b=="$") b=enrich[*a].after.erase(b);
      else b++;
    }
  }

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
void Language::load_words_file(string filename){
  string line;
  ifstream in;
  in.open(filename);
  while(getline(in,line)){
    this->add_word(line);
  }
  in.close();
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


static bool is_vowel(char c){
  return c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='y';
}
static bool is_consonant(char c){
  return c=='y' || !is_vowel(c);
}
static bool approved(string a,string b){
  if(b=="$") return true;
  if(a=="$") return !(b.size()>1 && b[0]==b[1]);
  int la=a.size();
  bool vowel=is_vowel(a[la-1]);
  if((la==1 || b.size()==1) && vowel==is_vowel(b[0])) return false;
  int consecutive=(la>1 && is_vowel(a[la-2])==vowel)?2:1;
  for(int i=0;i<b.size();i++){
    if(is_vowel(b[i])==vowel) consecutive++;
    else break;
  }
  return consecutive<3;
}

// testing lol
void Language::test(){
  char buffer[2];
  buffer[1]=0;
  Enrichment enrich;

  // Initial population
  for(char a='a';a<='z';a++){
    symbol_data data;
    data.after={};
    data.n=1;
    buffer[0]=a;
    enrich[string(buffer)]=data;
  }

  // Random appends
  for(int a=0;a<50;a++){
    auto i=next(enrich.begin(),rand()%enrich.size());
    int c='a'+(rand()%('z'-'a'+1));
    buffer[0]=c;
    if(approved(i->first,string(buffer))){
      string s;
      s.append(i->first);
      s.push_back(c);
      auto search=enrich.find(s);
      if(search==enrich.end()){
        symbol_data data;
        data.after={};
        data.n=1;
        enrich[s]=data;
      }
    }
  }

  // Add random edges
  int n=pow(enrich.size(),1.35);
  for(int a=0;a<n;a++){
    auto i=next(enrich.begin(),rand()%enrich.size());
    auto j=next(enrich.begin(),rand()%enrich.size());
    if(approved(i->first,j->first)){
      i->second.after.push_back(j->first);
    }
  }

  // Add begin and end
  symbol_data joint;
  joint.after={};
  joint.n=1;
  for(int a=0;a<20;a++){
    auto i=next(enrich.begin(),rand()%enrich.size());
    if(approved("$",i->first)){
      joint.after.push_back(i->first);
    }
    i=next(enrich.begin(),rand()%enrich.size());
    if(approved(i->first,"$")){
      i->second.after.push_back("$");
    }
  }
  enrich["$"]=joint;

  // Finalize into model
  this->enrich=enrich;
  this->clean_table();
  this->dump_table();
}
void Language::rigid_test(){
  Trie t("$");
  for(auto a=this->vocab.begin();a!=this->vocab.end();a++){
    t.add(*a);
  }
  //t.print();
  for(int a=0;a<20;a++){
    cout << t.walk() << "\n";
  }
}
