#include "simreple/Machine.hpp"
#include "simreple/Shell.hpp"
#include "simreple/SuggestionService.hpp"
#include "simreple/SyntaxHighlighting.hpp"

namespace simreple {

int main() {
  Machine machine;

  SuggestionService suggestions(&machine);

  Shell shell({
      .input_prefix = ":)",
      .output_prefix = ";O",
      .suggest = [&](auto prefix) { return suggestions.candidates(prefix); },
      .highlight = [](const auto& text, auto& colors) { syntaxHighlight(text, colors); },
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
