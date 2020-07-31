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

#define NO_EXCEPTIONS 1
#include "../../src/thoth.hpp"
#include <stdlib.h>
#include <string.h>
using namespace thoth;
#define MAX_WORDS 80

Language* lang=NULL;
char* words[MAX_WORDS];

extern "C"{
  void thothAPI_start(){
    for(int a=0;a<MAX_WORDS;a++) words[a]=NULL;
    init();
  }
  void thothAPI_new_language(){
    if(lang) delete lang;
    lang=new Language();
    lang->novel_syllables(100);
    lang->generate_model();
  }
  void thothAPI_load_language(unsigned long lseed,unsigned long wseed){
    if(lang) delete lang;
    lang=new Language(lseed);
    lang->set_seed(wseed);
    lang->novel_syllables(100);
    lang->generate_model();
  }
  unsigned long thothAPI_get_word_seed(){
    if(!lang) return 0;
    return lang->get_word_seed();
  }
  unsigned long thothAPI_get_lang_seed(){
    if(!lang) return 0;
    return lang->get_lang_seed();
  }
  char** thothAPI_new_words(int n,int l){
    if(n>MAX_WORDS){
      if(words[0]){
        free(words[0]);
        words[0]=NULL;
      }
      words[0]=new char[8];
      strcpy(words[0],"Error 2");
      return words;
    }
    for(int a=0;a<n;a++){
      if(words[a]){
        free(words[a]);
        words[a]=NULL;
      }
      string word=lang?lang->new_word(l):"Error 1";
      words[a]=new char[word.size()+1];
      strcpy(words[a],word.c_str());
    }
    return words;
  }
  void thothAPI_free(){
    for(int a=0;a<MAX_WORDS;a++){
      if(words[a]) free(words[a]);
    }
    if(lang) delete lang;
    lang=NULL;
  }
}
