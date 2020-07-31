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

#define THOTH_TRIE
#include <vector>
#include <string>

using namespace std;

namespace thoth{

  class Trie{
    public:
      Trie();
      Trie(string symbol);
      void get_nodes(vector<string>* nodes);
      void add(string symbol);
      void condense();
      void print();

    private:
      vector<Trie*> children;
      string symbol;
      bool last;
  };

}
