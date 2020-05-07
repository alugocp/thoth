#define THOTH_LANGUAGE
#ifndef THOTH
  #include "./thoth.hpp"
#endif
#ifndef THOTH_TRIE
  #include "./trie.hpp"
#endif
#ifndef THOTH_TYPES
  #include "./types.hpp"
#endif
#ifndef THOTH_RAND
  #include "./rand.hpp"
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
      void process_words();
      void save_model(string filename);
      void load_model(string filename);
      void load_words_file(string filename);
      void add_word(string word);

    private:
      int coda;
      int onset;
      Rand* rand;
      Trie vocab;
      Model model;
      vector<string> syllables;
      void initialize();
      void distribute_chars();
      vector<char_prob> consonants;
      vector<char_prob> vowels;
  };
}
