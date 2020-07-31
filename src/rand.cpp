/******************************************************************/
//
// Copyright (C) 2020 LugoCorp, LLC
// Contact: http://lugocorp.net
//
// This file is part of Thoth.
//
// Thoth is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation, either version 3 of
// the License, or (at your option) any later version.
//
// Thoth is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Thoth.  If not, see <http://www.gnu.org/licenses/>.
//
/******************************************************************/

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

void Rand::set_seed(unsigned long seed){
  this->value=seed;
  this->seed=seed;
}

unsigned long Rand::next(){
  this->value=((this->value*1103515245U)+12345U) & 0x7fffffff;
  return this->value;
}
