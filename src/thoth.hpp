#define THOTH
#ifndef THOTH_TYPES
  #include "./types.hpp"
#endif
#ifndef THOTH_LANGUAGE
  #include "./language.hpp"
#endif

#define MAX 3

namespace thoth{

  // Language generation
  bool is_okay(string s,char c);
  bool is_legal(string s,string s1);
  char random_okay(string s,vector<char> set);
  string word_to_string(string word);

  // Initialization
  void populate_banned();
  void init();

}
