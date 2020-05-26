#include "../src/thoth.hpp"
#include<iostream>
using namespace thoth;
using namespace std;

int main(int argc,char** argv){
  init();
  Language lang(10386209733);
  lang.novel_syllables(100);
  lang.generate_model();
  lang.print_model();
  lang.print_syllables();
  cout << "\n";
  for(int a=0;a<20;a++){
    cout << lang.new_word(5) << "\n";
  }
}
