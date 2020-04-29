#include <unordered_map>
#include <vector>
#include <string>
#define THOTH_TYPES

using namespace std;

namespace thoth{

  // Structs
  /*struct symbol_data{
    vector<string> after;
    int n;
  };
  struct symbol_prob{
    string symbol;
    float prob;
  };*/
  struct markov_node{
    vector<string> followers;
    vector<string> suffixes;
  };

  // Type definitions
  //typedef unordered_map<string,symbol_data> Enrichment;
  typedef unordered_map<string,markov_node> Model;
}
