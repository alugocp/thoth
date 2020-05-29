//#include <emscripten/emscripten.h>
#include <thoth.hpp>
#include <iostream>
#include <string.h>
using namespace thoth;
using namespace std;
#define N 10
Language* lang;
char* words[N];

extern "C" void generate(){
  for(int a=0;a<N;a++){
    string s=lang->new_word(6);
    const char* w=s.c_str();
    words[a]=new char[strlen(w)+1];
    strcpy(words[a],w);
  }
  printf("Thoth wordset generated\n");
}
extern "C" char* get_word(int a){
  return (a>=0 && a<N)?words[a]:NULL;
}

int main(int argc,char** argv){
  printf("Initializing Thoth WASM...\n");
  init();
  lang=new Language();
  lang->novel_syllables(100);
  lang->generate_model();
  printf("Thoth initialized\n");
}
