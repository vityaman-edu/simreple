#include "simreple/Machine.hpp"
#include "simreple/Shell.hpp"
#include "simreple/SuggestionService.hpp"

namespace simreple {

int main() {
  Machine machine;

  SuggestionService suggestions(&machine);

  Shell shell({
      .input_prefix = ":)",
      .output_prefix = ";O",
      .suggest = [&](auto prefix) { return suggestions.candidates(prefix); },
  });

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
