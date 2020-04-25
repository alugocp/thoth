#include "../src/thoth.hpp"
#include<iostream>
using namespace thoth;
using namespace std;

int main(int argc,char** argv){
  Language lang;
  lang.load_words_file("data/latin.txt");
  lang.generate_model();
  //lang.load_model("models/wucoza.thoth");
  //lang.test();
  lang.print_model();
  printf("\n");
  for(int a=0;a<25;a++){
    cout << lang.new_word(6) << "\n";
  }
}
