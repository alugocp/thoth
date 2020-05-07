#include "./rand.hpp"
#include <time.h>

using namespace thoth;

Rand::Rand(unsigned long seed){
  this->value=seed;
  this->seed=seed;
}
Rand::Rand(){
  unsigned long seed=time(NULL);
  seed+=(seed%1000000)*10000;
  this->value=seed;
  this->seed=seed;
}

unsigned long Rand::get_seed(){
  return seed;
}

unsigned long Rand::next(){
  this->value=((this->value*1103515245U)+12345U) & 0x7fffffff;
  return this->value;
}
