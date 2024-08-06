#include <ANTLRInputStream.h>
#include <BufferedTokenStream.h>

#include <replxx.hxx>
#include <string_view>
#include <vector>

#include "antlr/SimpLaLexer.h"

namespace simreple {

namespace {

replxx::Replxx::Color colorOf(const antlr4::Token* token) {
  switch (token->getType()) {
    case SimpLaLexer::PLUS:
      return replxx::Replxx::Color::YELLOW;
    case SimpLaLexer::ID:
      return replxx::Replxx::Color::MAGENTA;
    case SimpLaLexer::INTEGER:
      return replxx::Replxx::Color::GREEN;
    case SimpLaLexer::EQUAL:
    case SimpLaLexer::LET:
      return replxx::Replxx::Color::BLUE;
    default:
      return replxx::Replxx::Color::DEFAULT;
  }
}

}  // namespace

void syntaxHighlight(std::string_view text, std::vector<replxx::Replxx::Color>& colors) {
  antlr4::ANTLRInputStream chars(text);
  SimpLaLexer lexer(&chars);
  antlr4::BufferedTokenStream tokens(&lexer);
  tokens.fill();
  for (std::size_t i = 0; i < tokens.size(); ++i) {
    const auto* token = tokens.get(i);
    std::fill(
        std::next(std::begin(colors), static_cast<std::ptrdiff_t>(token->getStartIndex())),
        std::next(std::begin(colors), static_cast<std::ptrdiff_t>(token->getStopIndex()) + 1),
        colorOf(token)
    );
  }
}

}  // namespace simreple