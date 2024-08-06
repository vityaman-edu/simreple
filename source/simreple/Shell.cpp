#include "Shell.hpp"

#include <iostream>

#include "replxx.hxx"

namespace simreple {

Shell::Shell(Config config) : prompt_(std::move(config.prompt)) {
}

std::optional<std::string> Shell::readLine() {
  const auto* input = replxx_.input(prompt_);
  if (input == nullptr) {
    return std::nullopt;
  }

  std::string line = input;
  replxx_.history_add(line);
  return line;
}

void Shell::writeLine(std::string_view line) {  // NOLINT
  std::cout << line << std::endl;
}

}  // namespace simreple
