#include "Shell.hpp"

#include <iostream>

#include "replxx.hxx"

namespace simreple {

Shell::Shell(Config config)
    : input_prefix_(std::move(config.input_prefix))
    , output_prefix_(std::move(config.output_prefix)) {
  input_prefix_ += ' ';
  output_prefix_ += ' ';
}

std::optional<std::string> Shell::readLine() {
  const auto* input = replxx_.input(input_prefix_);
  if (input == nullptr) {
    return std::nullopt;
  }

  std::string line = input;
  replxx_.history_add(line);
  return line;
}

void Shell::writeLine(std::string_view line) {  // NOLINT
  std::cout << output_prefix_ << line << std::endl;
}

}  // namespace simreple
