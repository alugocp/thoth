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

#define THOTH
#ifndef THOTH_TYPES
  #include "./types.hpp"
#endif
#ifndef THOTH_RAND
  #include "./rand.hpp"
#endif
/*#ifndef THOTH_TRIE
  #include "./trie.hpp"
#endif*/
#ifndef THOTH_LANGUAGE
  #include "./language.hpp"
#endif
#include <exception>

#define MAX 3

namespace thoth{

  // Language generation
  bool is_okay(string s,char c);
  bool is_legal(string s,string s1);
  char random_okay(string s,vector<char_prob> set);
  string word_to_string(string word);

  // Initialization
  bool is_init();
  void init();
}
