#include "Machine.hpp"

#include <ANTLRInputStream.h>
#include <BufferedTokenStream.h>

#include <any>

#include "antlr/SimpLaLexer.h"
#include "antlr/SimpLaParser.h"

namespace simreple {

std::string Machine::evaluate(std::string_view input) {
  antlr4::ANTLRInputStream chars(input);
  SimpLaLexer lexer(&chars);
  antlr4::BufferedTokenStream tokens(&lexer);
  SimpLaParser parser(&tokens);

  auto* statement = parser.statement();
  const auto result = visit(statement);

  return std::any_cast<std::string>(result);
}

const std::unordered_map<std::string, std::int64_t>& Machine::variables() const {
  return variables_;
}

std::any Machine::visitAssignment(SimpLaParser::AssignmentContext* ctx) {
  const auto target = ctx->ID()->getText();
  const auto value = std::any_cast<std::int64_t>(visitExpression(ctx->expression()));
  variables_[target] = value;
  return "let " + target + " = " + std::to_string(value);
}

std::any Machine::visitSum(SimpLaParser::SumContext* ctx) {
  std::int64_t sum = 0;
  for (auto* child : ctx->atom()) {
    sum += std::any_cast<std::int64_t>(visit(child));
  }
  return sum;
}

std::any Machine::visitLiteral(SimpLaParser::LiteralContext* ctx) {
  std::int64_t value = std::stoi(ctx->INTEGER()->getText());
  return value;
}

std::any Machine::visitVariableRef(SimpLaParser::VariableRefContext* ctx) {
  const auto target = ctx->ID()->getText();
  return variables_.at(target);
}

}  // namespace simreple
