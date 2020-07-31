/******************************************************************/
//
// Copyright (C) 2020 LugoCorp, LLC
// Contact: http://lugocorp.net
//
// This file is part of Thoth.
//
// Thoth is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// Thoth is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Thoth.  If not, see <http://www.gnu.org/licenses/>.
//
/******************************************************************/

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
      void set_seed(unsigned long seed);
      void print_model();
      void print_syllables();
      string new_word(int l);
      void generate_model();
      void novel_syllables(int n);
      //void process_words();
      unsigned long get_lang_seed();
      unsigned long get_word_seed();
      void save_model(string filename);
      void load_model(string filename);
      /*void load_words_file(string filename);
      void add_word(string word);*/
      void clear_model();

    private:
      int coda;
      int onset;
      Rand* rand;
      Rand* word_rand;
      //Trie vocab;
      Model model;
      bool modeled;
      vector<string> syllables;
      void initialize();
      void distribute_chars();
      void ensure_syllables();
      vector<char_prob> consonants;
      vector<char_prob> vowels;
  };
}
