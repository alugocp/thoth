#include "./language.hpp"
#include<iostream>
#include<fstream>
#include<iterator>
#include<stdlib.h>
#include<math.h>
using namespace thoth;
using namespace std;

static const vector<char> all_consonants={'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z','{','}'};
static const vector<char> all_vowels={'a','e','i','o','u','y'};

// Constructors
Language::Language(long seed){
  this->rand=new Rand(seed);
  initialize();
  distribute_chars();
}
Language::Language(){
  this->rand=new Rand();
  initialize();
  distribute_chars();
}
void Language::initialize(){
  this->onset=0;
  this->modeled=false;
  if((this->rand->next())%100<75){
    if((this->rand->next())%100<25) this->onset=2;
    else this->onset=1;
  }
  int coda=(this->rand->next())%100;
  this->coda=(coda<15?0:(coda>=85?100:coda));
}
void Language::distribute_chars(){
  this->vowels={};
  this->consonants={};
  for(int a=0;a<all_consonants.size();a++){
    char c=all_consonants[a];
    char_prob p;
    p.symbol=c;
    p.prob=8;
    if(c=='v' || c=='w' || c=='y' || c=='j' || c=='{' || c=='}') p.prob=4;
    if(c=='x' || c=='z' || c=='q') p.prob=2;
    if((this->rand->next())%100<13) p.prob*=2;
    else if((this->rand->next())%100<17) p.prob/=2;
    this->consonants.push_back(p);
  }
  for(int a=0;a<all_vowels.size();a++){
    char_prob p;
    p.symbol=all_vowels[a];
    p.prob=1;
    this->vowels.push_back(p);
  }
}



// Debugging
void Language::print_model(){
  cout << "Language #" << this->rand->get_seed() << "\n";
  cout << "Onset: " << this->onset << "\n";
  cout << "Coda: " << this->coda << "\n";
}
void Language::print_syllables(){
  for(int a=0;a<syllables.size();a++){
    cout << syllables[a] << "\n";
  }
}



// Model file I/O
void Language::save_model(string filename){
  if(!modeled) throw ThothException("Cannot save an unmodeled language");
  ofstream out;
  out.open(filename);
  if(!out.is_open()) throw ThothException("Could not write to file");
  for(auto a=this->model.begin();a!=this->model.end();a++){
    markov_node node=a->second;
    out << "s " << a->first;
    for(auto b=node.suffixes.begin();b!=node.suffixes.end();b++){
      out << " " << (*b);
    }
    out << "\nf " << a->first;
    for(auto b=node.followers.begin();b!=node.followers.end();b++){
      out << " " << (*b);
    }
    out << "\n";
  }

  out.close();
}
void Language::load_model(string filename){
  string line,from;
  char buffer[50];
  ifstream in;
  char type;
  if(this->modeled) this->clear_model();
  in.open(filename);
  if(!in.is_open()) throw ThothException("Could not read from file");
  while(getline(in,line)){
    const char* l=line.c_str();
    sscanf(l,"%c %s",&type,buffer);
    from=string(buffer);
    auto search=this->model.find(from);
    if(search==this->model.end()){
      markov_node m;
      m.followers={};
      m.suffixes={};
      this->model[from]=m;
    }

    int i=from.size()+2;
    while(i<line.size() && sscanf(l+i," %s",buffer)){
      string next=string(buffer);
      if(type=='s') this->model[from].suffixes.push_back(next);
      else this->model[from].followers.push_back(next);
      i+=next.size()+1;
    }
  }
  in.close();
}



// Model generation
void Language::generate_model(){
  if(this->modeled) throw ThothException("Language is already modeled");
  if(!this->syllables.size()) throw ThothException("Cannot model a language without syllables");
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
          novel+=nexts[(this->rand->next())%nexts.size()];
        }
      }
      this->syllables.push_back(novel);
    }
  }
  // Calculate syllable followers and add to markov model
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
  this->modeled=true;
}
void Language::clear_model(){
  this->modeled=false;
  this->model.clear();
  this->syllables.clear();
}



// Novel generation pipeline
void Language::novel_syllables(int n){
  for(int a=0;a<n;a++){
    string s;
    for(int b=0;b<this->onset;b++){
      if((this->rand->next())%100<70){
        s+=random_okay(s,this->consonants);
      }
    }
    s+=random_okay(s,this->vowels);
    if((this->rand->next())%100<this->coda){
      s+=random_okay(s,this->consonants);
    }
    this->syllables.push_back(s);
  }
}



// Sample data pipeline
/*void Language::add_word(string word){
  vocab.add(word);
}
void Language::process_words(){
  //vocab.print();
  vocab.condense();
  vocab.get_nodes(&syllables);
}
void Language::load_words_file(string filename){
  string line;
  ifstream in;
  in.open(filename);
  if(!in.is_open()){
    cout << "Uh oh\n";
    exit(1);
  }
  while(getline(in,line)){
    add_word(line);
  }
  process_words();
  in.close();
}*/



// Word generation
string Language::new_word(int l){
  if(!this->modeled) throw ThothException("Unmodeled languages cannot generate words");
  int i=(this->rand->next())%this->model.size();
  auto pair=this->model.begin();
  while(i--) pair++;
  string word=pair->first;
  markov_node node=pair->second;
  string next;
  while(word.size()<l){
    if(l-word.size()==1 || !node.followers.size()){
      if(!node.suffixes.size()) break;
      next=node.suffixes[(this->rand->next())%node.suffixes.size()];
    }else{
      next=node.followers[(this->rand->next())%node.followers.size()];
    }
    node=this->model[next];
    word+=next;
  }
  return word_to_string(word);
}
