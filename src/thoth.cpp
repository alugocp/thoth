#include "./thoth.hpp"
#include <string.h>

static unordered_map<char,vector<string>> banned;

// Language generation
bool thoth::is_okay(string s,char c){
  for(int a=0;a<banned[c].size();a++){
    string check=banned[c][a];
    if(check.size()<=s.size()){
      int l=check.size();
      if(s.substr(s.size()-l,l)==check) return false;
    }
  }
  return true;
}
bool thoth::is_legal(string s,string s1){
  int l=MAX;
  if(l>s.size()) l=s.size();
  string prefix=s.substr(s.size()-l,l);
  for(int a=0;a<MAX;a++){
    if(!thoth::is_okay(prefix,s1[a])) return false;
    prefix.push_back(s1[a]);
    prefix.erase(0,1);
  }
  return true;
}
char thoth::random_okay(string s,vector<char_prob> set){
  int n=0;
  vector<char_prob> ok;
  for(int a=0;a<set.size();a++){
    if(thoth::is_okay(s,set[a].symbol)){
      ok.push_back(set[a]);
      n+=set[a].prob;
    }
  }
  int i=0;
  int a=rand()%n;
  while(a>0){
    a-=ok[i].prob;
    if(a>0) i++;
  }
  return ok[i].symbol;
}
string thoth::word_to_string(string word){
  string real;
  for(int a=0;a<word.size();a++){
    if(word[a]=='{') real+="ch";
    else if(word[a]=='}') real+="sh";
    else real.push_back(word[a]);
  }
  return real;
}



// Exceptions
thoth::ThothException::ThothException(const char* msg){
  size_t l=strlen(msg);
  const char* prefix="Thoth exception (";
  size_t pl=strlen(prefix);
  this->msg=new char[l+pl+2];
  strcpy(this->msg,prefix);
  strcat(this->msg,msg);
  strcat(this->msg,")");
}
const char* thoth::ThothException::what() const throw(){
  return msg;
}



// Initialization
void thoth::populate_banned(){
  banned['i']={"ii","ie","ei","ee","aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
  banned['z']={"g","q","j","z","{","}","v","f","x"};
  banned['x']={"g","q","j","z","{","}","v","f","x","w","x","q"};
  banned['g']={"g","q","j","z","{","}","v","f","x"};
  banned['o']={"oo","ou","uo","uu","aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
  banned['j']={"g","q","j","z","{","}","v","f","x","j","y","q"};
  banned['q']={"g","q","j","z","{","}","v","f","x","q","k","j","y","q","w","x","q"};
  banned['p']={"b","p"};
  banned['v']={"g","q","j","z","{","}","v","f","x"};
  banned['a']={"aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
  banned['d']={"bb","bd","db","dd"};
  banned['u']={"oo","ou","uo","uu","aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
  banned['w']={"w","x","q"};
  banned['{']={"g","q","j","z","{","}","v","f","x"};
  banned['m']={"nn","nm","mn","mm"};
  banned['b']={"bb","bd","db","dd","b","p"};
  banned['n']={"nn","nm","mn","mm"};
  banned['e']={"ii","ie","ei","ee","aaa","aae","aai","aao","aau","aea","aee","aei","aeo","aeu","aia","aie","aii","aio","aiu","aoa","aoe","aoi","aoo","aou","aua","aue","aui","auo","auu","eaa","eae","eai","eao","eau","eea","eee","eei","eeo","eeu","eia","eie","eii","eio","eiu","eoa","eoe","eoi","eoo","eou","eua","eue","eui","euo","euu","iaa","iae","iai","iao","iau","iea","iee","iei","ieo","ieu","iia","iie","iii","iio","iiu","ioa","ioe","ioi","ioo","iou","iua","iue","iui","iuo","iuu","oaa","oae","oai","oao","oau","oea","oee","oei","oeo","oeu","oia","oie","oii","oio","oiu","ooa","ooe","ooi","ooo","oou","oua","oue","oui","ouo","ouu","uaa","uae","uai","uao","uau","uea","uee","uei","ueo","ueu","uia","uie","uii","uio","uiu","uoa","uoe","uoi","uoo","uou","uua","uue","uui","uuo","uuu"};
  banned['h']={"h"};
  banned['k']={"q","k","cc","ck","kc","kk"};
  banned['f']={"g","q","j","z","{","}","v","f","x"};
  banned['}']={"g","q","j","z","{","}","v","f","x"};
  banned['y']={"j","y","q"};
  banned['c']={"cc","ck","kc","kk"};
}
void thoth::init(){
  thoth::populate_banned();
}
