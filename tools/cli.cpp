#include "../src/thoth.hpp"
#include <iostream>
#include <string.h>
using namespace std;

struct ArgBox{
  unsigned long seed;
  bool has_seed;
  int n;
};

static bool argv_parse(int argc,char** argv,ArgBox* box){
  box->n=20;
  box->has_seed=false;
  for(int a=1;a<argc;a++){
    if(!strcmp(argv[a],"--help")) return false;
    if(!strcmp(argv[a],"-s")){
      char* ptr;
      if(a+1==argc) return false;
      unsigned long seed=strtoul(argv[a+1],&ptr,10);
      box->has_seed=true;
      box->seed=seed;
    }
    if(!strcmp(argv[a],"-n")){
      if(a+1==argc) return false;
      int n=atoi(argv[a+1]);
      if(n<0) return false;
      box->n=n;
    }
  }
  return true;
}

static int help(){
  cout << "Thoth command line tool\n";
  cout << "-n num   generate num words\n";
  cout << "-s num   Use num as the seed\n";
  cout << "--help   view options\n";
  return 0;
}

int main(int argc,char** argv){
  ArgBox box;
  bool valid=argv_parse(argc,argv,&box);
  if(!valid) return help();
  thoth::init();
  thoth::Language* lang;
  if(box.has_seed) lang=new thoth::Language(box.seed);
  else lang=new thoth::Language();
  lang->novel_syllables(50);
  lang->generate_model();
  lang->print_model();
  cout << "\n";
  for(int a=0;a<box.n;a++){
    cout << lang->new_word(5) << "\n";
  }
  return 0;
}
