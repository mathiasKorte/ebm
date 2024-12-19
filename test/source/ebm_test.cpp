#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "ebm" ? 0 : 1;
}
