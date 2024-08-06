#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include "antlr/SimpLaBaseVisitor.h"

namespace simreple {

class Machine final : private SimpLaBaseVisitor {
public:
  std::string evaluate(std::string_view input);

  const std::unordered_map<std::string, std::int64_t>& variables() const;

private:
  std::any visitAssignment(SimpLaParser::AssignmentContext* ctx) override;
  std::any visitSum(SimpLaParser::SumContext* ctx) override;
  std::any visitLiteral(SimpLaParser::LiteralContext* ctx) override;
  std::any visitVariableRef(SimpLaParser::VariableRefContext* ctx) override;

  std::unordered_map<std::string, std::int64_t> variables_;
};

}  // namespace simreple
