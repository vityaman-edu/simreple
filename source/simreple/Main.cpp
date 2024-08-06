#include "simreple/Shell.hpp"

namespace simreple {

int main() {
  Shell shell({
      .prompt = ":) ",
  });

  while (const auto maybeInput = shell.readLine()) {
    const auto& input = maybeInput.value();
    shell.writeLine(";O " + input);
  }

  return 0;
}

}  // namespace simreple

int main() {
  return simreple::main();
}
