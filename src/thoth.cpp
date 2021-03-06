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

#include "./thoth.hpp"
#include <string.h>

static unordered_map<char,vector<string>> banned;
static bool initialized=false;

// Language generation
bool thoth::is_okay(string s,char c){
  auto search=banned.find(c);
  if(search!=banned.end()){
    for(int a=0;a<banned[c].size();a++){
      string check=banned[c][a];
      if(check.size()<=s.size()){
        int l=check.size();
        if(s.substr(s.size()-l,l)==check) return false;
      }
    }
  }
  return true;
}
bool thoth::is_legal(string s,string s1){
  string total=s+s1;
  int end=s.size()+MAX;
  if(end>total.size()) end=total.size();
  for(int a=s.size();a<end;a++){
    if(!thoth::is_okay(total.substr(0,a),total[a])) return false;
  }
  return true;
}
char thoth::random_okay(string s,vector<char_prob> set){
  int n=0;
  vector<char_prob> ok;
  for(int a=0;a<set.size();a++){
    if(thoth::is_okay(s,set[a].symbol)){
      ok.push_back(set[a]);
      n+=set[a].prob;
    }
  }
  int i=0;
  int a=rand()%n;
  while(a>0){
    a-=ok[i].prob;
    if(a>0) i++;
  }
  return ok[i].symbol;
}
string thoth::word_to_string(string word){
  string real;
  for(int a=0;a<word.size();a++){
    if(word[a]=='{') real+="ch";
    else if(word[a]=='}') real+="sh";
    else real.push_back(word[a]);
  }
  return real;
}



// Initialization
static void populate_banned(){
  banned['q']={"g","q","j","z","{","}","v","f","x","q","k","j","y","q","w","x","q"};
	banned['a']={"aa","ae","ai","ao","au","ea","ee","ei","eo","eu","ia","ie","ii","io","iu","oa","oe","oi","oo","ou","ua","ue","ui","uo","uu"};
	banned['g']={"g","q","j","z","{","}","v","f","x"};
	banned['u']={"aa","ae","ai","ao","au","ea","ee","ei","eo","eu","ia","ie","ii","io","iu","oa","oe","oi","oo","ou","ua","ue","ui","uo","uu"};
	banned['w']={"w","x","q"};
	banned['k']={"q","k"};
	banned['}']={"g","q","j","z","{","}","v","f","x"};
	banned['x']={"g","q","j","z","{","}","v","f","x","w","x","q"};
	banned['b']={"b","p"};
	banned['{']={"g","q","j","z","{","}","v","f","x"};
	banned['f']={"g","q","j","z","{","}","v","f","x"};
	banned['e']={"aa","ae","ai","ao","au","ea","ee","ei","eo","eu","ia","ie","ii","io","iu","oa","oe","oi","oo","ou","ua","ue","ui","uo","uu"};
	banned['y']={"j","y","q"};
	banned['j']={"g","q","j","z","{","}","v","f","x","j","y","q"};
	banned['v']={"g","q","j","z","{","}","v","f","x"};
	banned['z']={"g","q","j","z","{","}","v","f","x"};
	banned['h']={"h"};
	banned['p']={"b","p"};
	banned['i']={"aa","ae","ai","ao","au","ea","ee","ei","eo","eu","ia","ie","ii","io","iu","oa","oe","oi","oo","ou","ua","ue","ui","uo","uu"};
	banned['o']={"aa","ae","ai","ao","au","ea","ee","ei","eo","eu","ia","ie","ii","io","iu","oa","oe","oi","oo","ou","ua","ue","ui","uo","uu"};
}
bool thoth::is_init(){
  return initialized;
}
void thoth::init(){
  populate_banned();
  initialized=true;
}
