#include<unordered_map>
#include<vector>
#include<string>

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

  class Language{
    public:
      Language();
      Language(long seed);
      void add_word(string word);
      string new_word(int l);
      void generate_model();
      void print_model();
      void load_words_file(string filename);
      void save_model(string filename);
      void load_model(string filename);
      void test();

    private:
      long seed;
      Model model;
      Enrichment enrich;
      void set_seed(long seed);
      vector<string> vocab;
      void analyze_words();
      void enrich_table();
      void clean_table();
      void dump_table();
  };
}
