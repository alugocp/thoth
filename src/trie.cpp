#include "./trie.hpp"
#include<iostream>

using namespace thoth;
using namespace std;

Trie::Trie(string symbol){
  this->symbol=symbol;
}

void Trie::add(string symbol){
  for(auto a=this->children.begin();a!=this->children.end();a++){
    if(symbol[0]==(*a)->symbol[0]){
      if(symbol.size()>1) (*a)->add(symbol.substr(1));
      return;
    }
  }
    Trie* child=new Trie(symbol.substr(0,1));
  this->children.push_back(child);
  if(symbol.size()>1) child->add(symbol.substr(1));
}

void Trie::condense(){
  int n=this->children.size();
  if(!n) return;
  if(n==1){
    this->symbol+=this->children[0]->symbol;
    this->children=this->children[0]->children;
    this->condense();
  }else{
    for(auto a=this->children.begin();a!=this->children.end();a++){
      (*a)->condense();
    }
  }
}

string Trie::walk(){
  int n=this->children.size();
  if(!n) return "";
  Trie* node=this->children[rand()%n];
  string next=node->walk();
  if(!next.size()) return node->symbol;
  return node->symbol+next;
}

void Trie::print(){
  for(auto a=this->children.begin();a!=this->children.end();a++){
    cout << this->symbol << " -> " << (*a)->symbol << "\n";
  }
  for(auto a=this->children.begin();a!=this->children.end();a++){
    (*a)->print();
  }
}
