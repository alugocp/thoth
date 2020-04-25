#include<vector>
#include<string>

using namespace std;

namespace thoth{

  class Trie{
    public:
      Trie(string symbol);
      vector<Trie*> children;
      void add(string symbol);
      string walk();
      void print();
      void condense();

    private:
      string symbol;
  };

}
