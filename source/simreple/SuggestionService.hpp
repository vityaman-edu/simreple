#pragma once

#include <string>
#include <vector>

#include "simreple/Machine.hpp"

namespace simreple {

class SuggestionService {
public:
  explicit SuggestionService(Machine* machine);

  std::vector<std::string> candidates(std::string_view prefix);

private:
  Machine* machine_;
};

}  // namespace simreple