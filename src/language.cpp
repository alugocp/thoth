#include "./language.hpp"
#include<iostream>
#include<fstream>
#include<iterator>
#include<stdlib.h>
#include<time.h>
#include<math.h>
using namespace thoth;
using namespace std;

static const vector<char> consonants={'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z','{','}'};
static const vector<char> vowels={'a','e','i','o','u','y'};

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
  this->onset=0;
  if(rand()%100<75){
    this->onset=1;
    if(rand()%100<25){
      this->onset=2;
    }
  }
  int coda=rand()%100;
  if(coda<15) coda=0;
  if(coda>=85) coda=100;
  this->coda=coda;
}



// Debugging
void Language::print_model(){
  cout << "Language #" << this->seed << "\n";
  cout << "Onset: " << this->onset << "\n";
  cout << "Coda: " << this->coda << "\n";
}



// Model file I/O
void Language::save_model(string filename){
  ofstream out;
  out.open(filename);
  for(auto a=this->model.begin();a!=this->model.end();a++){
    markov_node node=a->second;
    for(auto b=node.followers.begin();b!=node.followers.end();b++){
      out << a->first << " 0 " << (*b) << "\n";
    }
    for(auto b=node.suffixes.begin();b!=node.suffixes.end();b++){
      out << a->first << " 1 " << (*b) << "\n";
    }
  }
  out.close();
}
void Language::load_model(string filename){
  char fbuffer[256],tbuffer[256];
  string line,from,to;
  ifstream in;
  int suffix;
  in.open(filename);
  while(getline(in,line)){
    const char* l=line.c_str();
    sscanf(l,"%s %i %s",fbuffer,&suffix,tbuffer);
    from=string(fbuffer);
    to=string(tbuffer);
    auto search=this->model.find(from);
    if(search==this->model.end()){
      markov_node m;
      m.followers={};
      m.suffixes={};
      this->model[from]=m;
    }
    if(suffix) this->model[from].suffixes.push_back(to);
    else this->model[from].followers.push_back(to);
  }
  in.close();
}



// Model generation
void Language::generate_model(){
  for(int a=0;a<this->syllables.size();a++){
    string s=this->syllables[a];
    if(s.size()<MAX){
      string novel=s;
      while(novel.size()<MAX){
        vector<string> nexts;
        for(int b=0;b<this->syllables.size();b++){
          if(is_legal(novel,this->syllables[b])){
            nexts.push_back(this->syllables[b]);
          }
        }
        if(nexts.size()){
          novel+=nexts[rand()%nexts.size()];
        }
      }
      this->syllables.push_back(novel);
    }
  }
  this->model.clear();
  for(int a=0;a<this->syllables.size();a++){
    string s=this->syllables[a];
    auto search=this->model.find(s);
    if(search==this->model.end()){
      markov_node m;
      m.followers={};
      m.suffixes={};
      this->model[s]=m;
    }else continue;
    for(int b=0;b<this->syllables.size();b++){
      string s1=this->syllables[b];
      if(is_legal(s,s1)){
        if(s1.size()<MAX) this->model[s].suffixes.push_back(s1);
        else this->model[s].followers.push_back(s1);
      }
    }
  }
}
void Language::novel_syllables(int n){
  for(int a=0;a<n;a++){
    string s;
    for(int b=0;b<this->onset;b++){
      if(rand()%100<70){
        s+=random_okay(s,consonants);
      }
    }
    s+=random_okay(s,vowels);
    if(rand()%100<this->coda){
      s+=random_okay(s,consonants);
    }
    this->syllables.push_back(s);
  }
}
/*void Language::clean_table(){
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
}*/



// Sample data pipeline
/*void Language::add_word(string word){
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
}*/



// Word generation
string Language::new_word(int l){
  int i=rand()%this->model.size();
  auto pair=this->model.begin();
  while(i--) pair++;
  string word=pair->first;
  markov_node node=pair->second;
  string next;
  while(word.size()<l){
    if(l-word.size()==1 || !node.followers.size()){
      if(!node.suffixes.size()) break;
      next=node.suffixes[rand()%node.suffixes.size()];
    }else{
      next=node.followers[rand()%node.followers.size()];
    }
    node=this->model[next];
    word+=next;
  }
  return word_to_string(word);
}
