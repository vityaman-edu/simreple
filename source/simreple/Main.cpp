#include "simreple/Shell.hpp"

namespace simreple {

int main() {
  Shell shell({
      .input_prefix = ":)",
      .output_prefix = ";O",
  });

  while (const auto maybeInput = shell.readLine()) {
    const auto& input = maybeInput.value();
    shell.writeLine(input);
  }

  return 0;
}

}  // namespace simreple

int main() {
  return simreple::main();
}
