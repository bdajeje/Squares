#include "mathematics.hpp"

#include <stdlib.h>

namespace utils {
namespace maths {

int random(int min, int max)
{
  return rand() % (max - min) + min;
}

}
}
