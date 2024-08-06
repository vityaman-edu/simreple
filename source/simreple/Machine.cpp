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

  auto* expression = parser.statement();
  const auto result = this->visit(expression);

  return std::any_cast<std::string>(result);
}

const std::unordered_map<std::string, std::int64_t>& Machine::variables() const {
  return variables_;
}

std::any Machine::visitStatement(SimpLaParser::StatementContext* ctx) {
  return ctx->toStringTree();
}

std::any Machine::visitAssignment(SimpLaParser::AssignmentContext* ctx) {
  return ctx->toStringTree();
}

std::any Machine::visitExpression(SimpLaParser::ExpressionContext* ctx) {
  return ctx->toStringTree();
}

std::any Machine::visitSum(SimpLaParser::SumContext* ctx) {
  return ctx->toStringTree();
}

std::any Machine::visitLiteral(SimpLaParser::LiteralContext* ctx) {
  return ctx->toStringTree();
}

std::any Machine::visitVariableRef(SimpLaParser::VariableRefContext* ctx) {
  return ctx->toStringTree();
}

}  // namespace simreple
