#pragma once

#include <functional>
#include <optional>
#include <replxx.hxx>
#include <string>
#include <string_view>
#include <vector>

namespace simreple {

class Shell final {
public:
  using Suggest = std::function<std::vector<std::string>(std::string_view)>;

  struct Config {
    std::string input_prefix;
    std::string output_prefix;
    Suggest suggest;
  };

  explicit Shell(Config config);

  std::optional<std::string> readLine();
  void writeLine(std::string_view line);

private:
  std::string input_prefix_;
  std::string output_prefix_;
  Suggest suggest_;
  replxx::Replxx replxx_;
};

}  // namespace simreple