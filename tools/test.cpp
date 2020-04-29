#include "../src/thoth.hpp"
#include<iostream>
using namespace thoth;
using namespace std;

int main(int argc,char** argv){
  Language lang(1588185520);
  lang.novel_syllables(100);
  lang.generate_model();
  lang.print_model();
  cout << "\n";
  for(int a=0;a<25;a++){
    cout << lang.new_word(5) << "\n";
  }
}
