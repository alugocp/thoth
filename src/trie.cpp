/******************************************************************/
//
// Copyright (C) 2020 LugoCorp, LLC
// Contact: http://lugocorp.net
//
// This file is part of Thoth.
//
// Thoth is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// Thoth is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Thoth.  If not, see <http://www.gnu.org/licenses/>.
//
/******************************************************************/

#include "./trie.hpp"
#include<iostream>

using namespace thoth;
using namespace std;

Trie::Trie(string symbol){
  this->symbol=symbol;
  last=false;
}
Trie::Trie(){
  symbol="$";
  last=false;
}



// Debugging
void Trie::print(){
  for(auto a=this->children.begin();a!=this->children.end();a++){
    cout << this->symbol << " -> " << (*a)->symbol << "\n";
  }
  for(auto a=this->children.begin();a!=this->children.end();a++){
    (*a)->print();
  }
}



// Data processing operations
void Trie::add(string symbol){
  for(auto a=this->children.begin();a!=this->children.end();a++){
    if(symbol[0]==(*a)->symbol[0]){
      if(symbol.size()>1) (*a)->add(symbol.substr(1));
      return;
    }
  }
  Trie* child=new Trie(symbol.substr(0,1));
  if(symbol.size()==1) child->last=true;
  this->children.push_back(child);
  if(symbol.size()>1) child->add(symbol.substr(1));
}
void Trie::condense(){
  int n=this->children.size();
  if(!n) return;
  if(n==1 && this->last && symbol!="$"){
    this->symbol+=this->children[0]->symbol;
    this->children=this->children[0]->children;
    this->condense();
  }else{
    for(auto a=this->children.begin();a!=this->children.end();a++){
      (*a)->condense();
    }
  }
}
void Trie::get_nodes(vector<string>* nodes){
  for(int a=0;a<children.size();a++){
    int add=true;
    for(auto b=nodes->begin();b!=nodes->end();b++){
      if(*b==children[a]->symbol){
        add=false;
        break;
      }
    }
    if(add) nodes->push_back(children[a]->symbol);
    children[a]->get_nodes(nodes);
  }
}
