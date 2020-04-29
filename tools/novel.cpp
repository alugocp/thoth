#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct piece{
  vector<int> groups;
  string symbol;
};
class Group{
  public:
    vector<string> symbols;
    int restriction;
    Group(int restriction,vector<string> symbols){
      this->restriction=restriction;
      this->symbols=symbols;
    }
};

typedef vector<struct piece> Syllable;

vector<Group*> groups;

struct piece get_piece(string symbol){
  struct piece s;
  s.symbol=symbol;
  s.groups={};
  for(int a=0;a<groups.size();a++){
    for(int b=0;b<groups[a]->symbols.size();b++){
      if(groups[a]->symbols[b]==symbol){
        s.groups.push_back(a);
        break;
      }
    }
  }
  return s;
}

bool okay(Syllable s,piece c){
  for(int a=0;a<c.groups.size();a++){
    int res=groups[c.groups[a]]->restriction;
    if(s.size()>=res){
      int consec=0;
      for(int b=0;b<res;b++){
        piece p1=s[s.size()-b-1];
        for(int d=0;d<p1.groups.size();d++){
          if(p1.groups[d]==c.groups[a]){
            consec++;
            break;
          }
        }
      }
      if(consec==res) return false;
    }
  }
  return true;
}

int main(int argc,char** argv){

  // Populate groups
  groups.push_back(new Group(2,{"i","e"}));
  groups.push_back(new Group(2,{"o","u"}));
  groups.push_back(new Group(3,{"a","e","i","o","u"}));
  groups.push_back(new Group(1,{"g","q","j","z","ch","sh","v","f","x"}));
  groups.push_back(new Group(2,{"n","m"}));
  groups.push_back(new Group(2,{"b","d"}));
  groups.push_back(new Group(1,{"q","k"}));
  groups.push_back(new Group(2,{"c","k"}));
  groups.push_back(new Group(1,{"b","p"}));
  groups.push_back(new Group(1,{"j","y"}));
  groups.push_back(new Group(1,{"w","x","q"}));
  groups.push_back(new Group(1,{"h"}));

  // Pick and display random seed
  long seed=time(NULL);
  cout << "Seed: " << seed << "\n";
  srand(seed);

  // Setup language parameters
  int onset=0;
  if(rand()%100<75){
    onset=1;
    if(rand()%100<25){
      onset=2;
    }
  }
  int coda=rand()%100;
  if(coda<15) coda=0;
  if(coda>=85) coda=100;
  cout << "Onset: " << onset << "\n";
  cout << "Coda: " << coda << "\n\n";

  // Letters dictionary
  vector<string> consonants={"b","c","d","f","g","h","j","k","l","m","n","p","q","r","s","t","v","w","x","y","z","ch","sh"};
  vector<string> vowels={"a","e","i","o","u","y"};

  // Make syllables
  vector<Syllable> syllables;
  for(int a=0;a<100;a++){
    Syllable s;
    for(int b=0;b<onset;b++){
      if(rand()%100<70){
        if(s.size()){
          vector<struct piece> next;
          for(int c=0;c<consonants.size();c++){
            piece p=get_piece(consonants[c]);
            if(okay(s,p)){
              next.push_back(p);
            }
          }
          if(!next.size()){
            cout << "Uh oh\n";
            exit(1);
          }
          piece p=next[rand()%next.size()];
          s.push_back(p);
        }else{
          string consonant=consonants[rand()%consonants.size()];
          s.push_back(get_piece(consonant));
        }
      }
    }
    string vowel=vowels[rand()%vowels.size()];
    s.push_back(get_piece(vowel));
    if(rand()%100<coda){
      string consonant=consonants[rand()%consonants.size()];
      s.push_back(get_piece(consonant));
    }
    syllables.push_back(s);

    // Print syllable
    for(int b=0;b<s.size();b++) cout << s[b].symbol;
    cout << "\n";
  }

  cout << "\n";

  // Create words (unsafe)
  for(int a=0;a<25;a++){
    int max=(rand()%6)+4;
    cout << max << " -> ";
    int l=0;
    while(l<max){
      int i=rand()%syllables.size();
      for(int b=0;b<syllables[i].size();b++){
        string str=syllables[i][b].symbol;
        l+=str.size();
        cout << str;
      }
    }
    cout << "\n";
  }

  return 0;
}
