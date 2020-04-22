#include "../src/thoth.hpp"
#include<iostream>
using namespace Thoth;
using namespace std;

int main(int argc,char** argv){
  Language lang(158217114);
  lang.add_word("xochitl");
  lang.add_word("nantlitl");
  lang.add_word("tonali");
  lang.add_word("quetzalcoatl");
  lang.add_word("xocolatl");
  lang.add_word("huitzilpochtli");
  lang.add_word("axolotl");
  lang.generate_model();
  //lang.print_model();
  printf("\n");
  for(int a=0;a<10;a++){
    cout << lang.new_word(12) << "\n";
  }
}
