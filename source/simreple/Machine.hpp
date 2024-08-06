#pragma once

#include <string>

namespace simreple {

class Machine {
public:
  std::string evaluate(std::string_view input);
};

}  // namespace simreple
