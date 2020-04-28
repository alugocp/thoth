#include <unordered_map>
#include <vector>
#include <string>
#define THOTH_TYPES

using namespace std;

namespace thoth{

  // Structs
  struct symbol_data{
    vector<string> after;
    int n;
  };
  struct symbol_prob{
    string symbol;
    float prob;
  };

  // Type definitions
  typedef unordered_map<string,symbol_data> Enrichment;
  typedef unordered_map<string,vector<symbol_prob>> Model;
}
