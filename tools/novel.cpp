#include <unordered_map>
#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

unordered_map<string,vector<string>> groups;

bool okay(string s,string s1){
  vector<string> prohibited=groups[s1.substr(0,1)];
  if(s1.size()>=2){
    string sub=s1.substr(0,2);
    if(sub=="ch" || sub=="sh"){
      prohibited=groups[sub];
    }
  }
  for(auto a=prohibited.begin();a!=prohibited.end();a++){
    int l=(*a).size();
    if(s.size()>=l && s.substr(s.size()-l,l)==*a){
      return false;
    }
  }
  return true;
}

int num_chars(string s){
  int i=0;
  int n=0;
  while(i<s.size()){
    if(s[i]=='c' || s[i]=='s'){
      if(s.size()>i+1 && s[i+1]=='h') i++;
    }
    i++;
    n++;
  }
  return n;
}
string get_char(int n,string s,int* index){
  int i=0;
  while(n){
    if(s[i]=='c' || s[i]=='s'){
      if(s.size()>i+1 && s[i+1]=='h') i++;
    }
    i++;
    n--;
  }
  int l=1;
  *index=i;
  if(s.size()>i+1 && (s[i]=='s' || s[i]=='c') && s[i+1]=='h') l=2;
  return s.substr(i,l);
}

void populate_groups(){
	groups["w"]={"w","x","q"};
	groups["q"]={"g","q","j","z","ch","sh","v","f","x","q","k","j","y","q","w","x","q"};
	groups["p"]={"b","p"};
	groups["c"]={"cc","ck","kc","kk"};
	groups["k"]={"q","k","cc","ck","kc","kk"};
	groups["d"]={"bb","bd","db","dd"};
	groups["g"]={"g","q","j","z","ch","sh","v","f","x"};
	groups["x"]={"g","q","j","z","ch","sh","v","f","x","w","x","q"};
	groups["f"]={"g","q","j","z","ch","sh","v","f","x"};
	groups["a"]={"aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
	groups["m"]={"nn","nm","mn","mm"};
	groups["v"]={"g","q","j","z","ch","sh","v","f","x"};
	groups["h"]={"h"};
	groups["y"]={"j","y","q"};
	groups["z"]={"g","q","j","z","ch","sh","v","f","x"};
	groups["o"]={"oo","ou","uo","uu","aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
	groups["e"]={"ii","ie","ei","ee","aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
	groups["n"]={"nn","nm","mn","mm"};
	groups["b"]={"bb","bd","db","dd","b","p"};
	groups["sh"]={"g","q","j","z","ch","sh","v","f","x"};
	groups["u"]={"oo","ou","uo","uu","aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
	groups["i"]={"ii","ie","ei","ee","aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
	groups["j"]={"g","q","j","z","ch","sh","v","f","x","j","y","q"};
	groups["ch"]={"g","q","j","z","ch","sh","v","f","x"};
}

string random_okay(string s,vector<string> set){
  vector<string> ok;
  for(auto s1=set.begin();s1!=set.end();s1++){
    if(!s.size() || okay(s,*s1)) ok.push_back(*s1);
  }
  if(!ok.size()){
    cout << "Uh oh\n";
    exit(1);
  }
  return ok[rand()%ok.size()];
}

bool syllabic_okay(string s,string s1){
  if(!s.size()) return true;
  int i=0;
  int n=num_chars(s1);
  if(n>3) n=3;
  for(int a=0;a<n;a++){
    string current=get_char(a,s1,&i);
    string prefix=s;
    if(i) prefix+=s1.substr(0,i);
    if(!okay(prefix,current)) return false;
  }
  return true;
}

int main(int argc,char** argv){

  populate_groups();

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
  vector<string> syllables;
  for(int a=0;a<100;a++){
    string s;
    for(int b=0;b<onset;b++){
      if(rand()%100<70){
        s+=random_okay(s,consonants);
      }
    }
    s+=random_okay(s,vowels);
    if(rand()%100<coda){
      s+=random_okay(s,consonants);
    }
    syllables.push_back(s);
    cout << s << "\n";
  }

  cout << "\n";

  // Create words (safe)
  for(int a=0;a<25;a++){
    string word;
    int max=(rand()%5)+2;
    cout << max << " -> ";
    while(word.size()<max){
      vector<string> next;
      for(int a=0;a<syllables.size();a++){
        if(syllabic_okay(word,syllables[a])){
          next.push_back(syllables[a]);
        }
      }
      int i=rand()%next.size();
      word+=next[i];
    }
    cout << word << "\n";
  }

  return 0;
}
