#include "../src/thoth.hpp"
#include<iostream>
using namespace thoth;
using namespace std;

int main(int argc,char** argv){
  Language lang;
  lang.load_words_file("data/latin.txt");
  lang.rigid_test();
}
