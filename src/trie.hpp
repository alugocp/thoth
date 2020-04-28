#include "./types.hpp"
#include <vector>
#include <string>

using namespace std;

namespace thoth{

  class Trie{
    public:
      Trie(string symbol);
      void add(string symbol);
      string walk();
      void print();
      void condense();
      void collapse(Model* m);

    private:
      vector<Trie*> children;
      string symbol;
  };

}
