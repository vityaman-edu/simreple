#include "Shell.hpp"

#include <iostream>
#include <ranges>
#include <vector>

#include "replxx.hxx"

namespace simreple {

Shell::Shell(Config config)
    : input_prefix_(std::move(config.input_prefix))
    , output_prefix_(std::move(config.output_prefix))
    , suggest_(std::move(config.suggest))
    , highlight_(std::move(config.highlight)) {
  using replxx::Replxx;

  input_prefix_ += ' ';
  output_prefix_ += ' ';

  replxx_.set_completion_callback([this](const auto& text, int& /* length */) {
    return              //
        suggest_(text)  //
        | std::views::transform([](const auto& candidate) {
            return Replxx::Completion(candidate, Replxx::Color::BLUE);
          })  //
        | std::ranges::to<std::vector>();
  });

  replxx_.set_hint_callback([this](const auto& text, int& /* length */, Replxx::Color& color) {
    color = Replxx::Color::YELLOW;
    return suggest_(text);
  });

  replxx_.set_highlighter_callback([this](const auto& text, auto& colors) {
    highlight_(text, colors);
  });
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
