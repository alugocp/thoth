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
