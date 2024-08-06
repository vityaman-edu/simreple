#include "simreple/Machine.hpp"
#include "simreple/Shell.hpp"

namespace simreple {

int main() {
  Shell shell({
      .input_prefix = ":)",
      .output_prefix = ";O",
  });

  Machine machine;

  while (const auto maybeInput = shell.readLine()) {
    const auto& input = maybeInput.value();
    const auto output = machine.evaluate(input);
    shell.writeLine(output);
  }

  return 0;
}

}  // namespace simreple

int main() {
  return simreple::main();
}
