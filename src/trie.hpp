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
