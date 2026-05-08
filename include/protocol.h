#pragma once
#include <optional>
#include <string_view>

enum class CommandType { SET, GET, DEL, UNKOWN };

struct ParsedCommand {
  CommandType type;
  std::string_view key;
  std::optional<std::string_view> value; // only used in SET
};

ParsedCommand parseInput(std::string_view input);
