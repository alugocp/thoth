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

#define THOTH_RAND

namespace thoth{

  class Rand{
    public:
      Rand();
      Rand(unsigned long seed);
      unsigned long get_seed();
      void set_seed(unsigned long seed);
      unsigned long next();
    private:
      unsigned long value;
      unsigned long seed;
  };

}
