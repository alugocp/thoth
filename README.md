# Thoth
<img src="thoth-icon.svg" width="250" height="250"/>
<br>
<br>

Thoth is [LugoCorp](http://lugocorp.net)'s procedural word generator library. Use it as a library to generate new words in your own programs or make use of the built-in CLI tool.

You can find documentation [here](http://lugocorp.net/thoth).

## Access
#### Installation
Run `./INSTALL` from this directory to install Thoth. This script builds the library and CLI, copies the header and shared object files, and even adds Thoth to pkg-config automatically. You may need root permissions. Once you've done this you can use Thoth code in your own programs and run the thoth command from your terminal.

#### Building
If you'd rather just build Thoth then run `make`. This will generate a shared object file at `bin/libthoth.so` as well as the Thoth CLI tool at `bin/thoth`.

## Getting started
This is all the boilerplate you'll need to initialize and use Thoth in your own C++ programs:

```cpp
#include <thoth/thoth.hpp>;
#include <iostream>;

int main(int argc,char** argv){

  // Initialize the Thoth library
  thoth::init();

  // Create a new procedural language
  thoth::Language lang;
  lang.novel_syllables(100);
  lang.generate_model();

  // Generate a word
  string word=lang.new_word(6);
  std::cout << word << "\n";
}
```

**Hint** compile the example above with `g++ -std=c++11 file.cpp -lthoth` (assuming you've installed Thoth with the provided INSTALL script)

## CLI usage
`thoth [-n #][-s #]`

The thoth command can be used with `--help` to view all options or with any combination of the parameters listed above. `-n` sets how many words will be generated and `-s` sets the seed. A pseudorandom seed will be chosen if it is not specified in this way.

## Todo
- [ ] Create binary file format and I/O
- [ ] Sample data pipeline
