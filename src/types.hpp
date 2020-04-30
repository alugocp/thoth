#define THOTH_TYPES
#include <unordered_map>
#include <vector>
#include <string>

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
  struct char_prob{
    char symbol;
    int prob;
  };

  // Type definitions
  //typedef unordered_map<string,symbol_data> Enrichment;
  typedef unordered_map<string,markov_node> Model;
}
