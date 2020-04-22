#include<unordered_map>
#include<vector>
#include<string>

using namespace std;

namespace Thoth{

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

  class Language{
    public:
    void add_word(string word);
    string new_word(int l);
    void generate_model();
    void print_model();

    private:
    Model model;
    Enrichment enrich;
    vector<string> vocab;
    void analyze_words();
    void enrich_table();
    void clean_table();
    void dump_table();
  };
}
