#pragma once

#include <replxx.hxx>
#include <string_view>
#include <vector>

namespace simreple {

void syntaxHighlight(std::string_view text, std::vector<replxx::Replxx::Color>& colors);

}