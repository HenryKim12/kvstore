#include "../include/protocol.h"
#include <algorithm>
#include <cassert>
#include <cctype>
#include <ranges>
#include <string_view>

ParsedCommand parseInput(std::string_view input) {
  while (!input.empty() &&
         (input.back() == '\n' || input.back() == '\r' || input.back() == ' '))
    input.remove_suffix(1);
  auto view = input | std::views::split(' ');
  auto numOfParts = std::ranges::distance(view);

  auto to_sv = [](auto subrange) {
    return std::string_view(subrange.begin(), subrange.end());
  };

  auto it = view.begin();
  std::string cmd(to_sv(*it));
  std::ranges::transform(cmd, cmd.begin(), ::toupper);

  ParsedCommand command{CommandType::UNKOWN, "", std::nullopt};
  if (cmd == "SET") {
    assert(numOfParts == 3);
    command.type = CommandType::SET;
    command.key = to_sv(*std::next(it, 1));
    command.value = to_sv(*std::next(it, 2));
  } else if (cmd == "GET") {
    assert(numOfParts == 2);
    command.type = CommandType::GET;
    command.key = to_sv(*std::next(it, 1));
    command.value = std::nullopt;
  } else if (cmd == "DEL") {
    assert(numOfParts == 2);
    command.type = CommandType::DEL;
    command.key = to_sv(*std::next(it, 1));
    command.value = std::nullopt;
  }
  return command;
}
