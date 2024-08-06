#pragma once

#include <optional>
#include <replxx.hxx>
#include <string>
#include <string_view>

namespace simreple {

class Shell {
public:
  struct Config {
    std::string input_prefix;
    std::string output_prefix;
  };

  explicit Shell(Config config);

  std::optional<std::string> readLine();
  void writeLine(std::string_view line);

private:
  std::string input_prefix_;
  std::string output_prefix_;
  replxx::Replxx replxx_;
};

}  // namespace simreple