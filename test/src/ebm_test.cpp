#include "lib.h"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "ebm" ? 0 : 1;
}
