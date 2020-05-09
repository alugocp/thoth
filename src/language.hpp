#define THOTH_LANGUAGE
#ifndef THOTH
  #include "./thoth.hpp"
#endif
#include <vector>
#include <string>

using namespace std;

namespace thoth{

  class Language{
    public:
      Language();
      Language(long seed);
      void print_model();
      void print_syllables();
      string new_word(int l);
      void generate_model();
      void novel_syllables(int n);
      //void process_words();
      void save_model(string filename);
      void load_model(string filename);
      /*void load_words_file(string filename);
      void add_word(string word);*/
      void clear_model();

    private:
      int coda;
      int onset;
      Rand* rand;
      //Trie vocab;
      Model model;
      bool modeled;
      vector<string> syllables;
      void initialize();
      void distribute_chars();
      vector<char_prob> consonants;
      vector<char_prob> vowels;
  };
}
