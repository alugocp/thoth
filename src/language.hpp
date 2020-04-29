#define THOTH_LANGUAGE
#ifndef THOTH
  #include "./thoth.hpp"
#endif
#ifndef THOTH_TYPES
  #include "./types.hpp"
#endif
#include <vector>
#include <string>

using namespace std;

namespace thoth{

  class Language{
    public:
      Language();
      Language(long seed);
      //void add_word(string word);
      void novel_syllables(int n);
      string new_word(int l);
      void generate_model();
      void print_model();
      void print_syllables();
      //void load_words_file(string filename);
      void save_model(string filename);
      void load_model(string filename);

    private:
      int coda;
      int onset;
      long seed;
      Model model;
      vector<string> syllables;
      void initialize(long seed);
      vector<char_prob> consonants;
      vector<char_prob> vowels;
      //vector<string> vocab;
      //void analyze_words();
      //void enrich_table();
      //void clean_table();
      //void dump_table();
  };
}
