#include "../src/thoth.hpp"
#include<iostream>
using namespace thoth;
using namespace std;

int main(int argc,char** argv){
  init();
  Language lang;
  lang.novel_syllables(50);
  lang.generate_model();
  //lang.save_model("models/choyoro.thoth");
  //lang.load_model("models/choyoro.thoth");
  lang.print_model();
  //lang.print_syllables();
  cout << "\n";
  for(int a=0;a<20;a++){
    cout << lang.new_word(5) << "\n";
  }
}
