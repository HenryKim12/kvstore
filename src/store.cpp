#include "../include/store.h"

#include <format>
#include <iostream>

Store::Store() = default;

Store::~Store() = default;

void Store::set(std::string_view key, std::string_view value) {
  data_[std::string(key)] = value;
  std::cout << std::format("[Store] Set {}={}", key, value) << std::endl;
}

std::optional<std::string> Store::get(std::string_view key) {
  if (exists(key)) {
    std::cout << std::format("[Store] Get {}={}", key, data_[std::string(key)])
              << std::endl;
    return data_[std::string(key)];
  }
  std::cout << std::format("[Store] Key {} does not exist",
                           std::string_view(key))
            << std::endl;
  return std::nullopt;
}

bool Store::del(std::string_view key) {
  if (exists(key)) {
    std::cout << std::format("[Store] Deleted key {}", key) << std::endl;
    data_.erase(std::string(key));
    return true;
  }
  std::cout << std::format("[Store] Key {} does not exist", key) << std::endl;
  return false;
}

bool Store::exists(std::string_view key) const {
  if (data_.count(std::string(key))) {
    return true;
  }
  return false;
}
