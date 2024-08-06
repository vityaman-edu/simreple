#include "SuggestionService.hpp"

#include <antlr4-c3/CodeCompletionCore.hpp>
#include <cassert>
#include <ranges>
#include <string>

#include "antlr/SimpLaLexer.h"
#include "antlr/SimpLaParser.h"

namespace simreple {

namespace {

auto isWhitespace(char symbol) -> bool {
  return symbol == ' ';
}

auto lastWordIndex(std::string_view text) -> std::size_t {
  const auto length = static_cast<std::int64_t>(text.size());
  for (std::int64_t i = length - 1; 0 <= i; --i) {
    if (isWhitespace(text[i])) {
      return i + 1;
    }
  }
  return 0;
}

auto lastWord(std::string_view text) -> std::string {
  return std::string(text.substr(lastWordIndex(text)));
}

auto lowercase(const std::string& text) -> std::string {
  return text | std::views::transform([](auto symbol) { return std::tolower(symbol); }) |
         std::ranges::to<std::string>();
}

}  // namespace

SuggestionService::SuggestionService(Machine* machine) : machine_(machine) {
  assert(machine != nullptr);
}

std::vector<std::string> SuggestionService::candidates(std::string_view prefix) {  // NOLINT
  antlr4::ANTLRInputStream chars(prefix.substr(0, lastWordIndex(prefix)));
  SimpLaLexer lexer(&chars);
  antlr4::BufferedTokenStream tokens(&lexer);
  SimpLaParser parser(&tokens);
  c3::CodeCompletionCore completion(&parser);

  completion.ignoredTokens = {
      SimpLaLexer::INTEGER,
  };

  lexer.removeErrorListeners();
  parser.removeErrorListeners();
  tokens.fill();

  const auto caretTokenIndex = tokens.size() - 1;
  auto* context = parser.statement();
  const auto candidates = completion.collectCandidates(caretTokenIndex, context);

  const auto last = lowercase(lastWord(prefix));
  const auto isSuitable = [&](const std::string& candidate) {
    return lowercase(candidate).starts_with(last);
  };

  const auto display = [&](std::size_t token) {
    const auto& vocabulary = lexer.getVocabulary();

    auto display = vocabulary.getDisplayName(token);

    if (display.starts_with('\'')) {
      assert(display.ends_with('\''));
      display.erase(std::begin(display));
      display.erase(std::prev(std::end(display)));
    }

    return display;
  };

  std::vector<std::string> result;

  for (const auto& [token, follow] : candidates.tokens) {
    if (token == SimpLaLexer::ID) {
      for (const auto& [key, _] : machine_->variables()) {
        if (isSuitable(key)) {
          result.emplace_back(key);
        }
      }
    } else {
      auto candidate = display(token);
      if (isSuitable(candidate)) {
        result.emplace_back(std::move(candidate));
      }
    }
  }

  for (auto& candidate : result) {
    candidate += ' ';
  }

  return result;
}

}  // namespace simreple