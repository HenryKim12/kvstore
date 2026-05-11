#include "../include/store.h"

#include <format>
#include <iostream>

Store::Store() = default;

Store::~Store() = default;

void Store::set(std::string_view key, std::string_view value) {
  std::unique_lock lock(mutex_);
  data_[std::string(key)] = value;
  std::cout << std::format("[Store] Set {}={}", key, value) << std::endl;
}

std::optional<std::string> Store::get(std::string_view key) {
  std::shared_lock lock(mutex_);
  auto it = data_.find(std::string(key));
  if (it != data_.end()) {
    std::cout << std::format("[Store] Get {}={}", key, it->second) << std::endl;
    return it->second;
  }
  std::cout << std::format("[Store] Key {} does not exist", key) << std::endl;
  return std::nullopt;
}

bool Store::del(std::string_view key) {
  std::unique_lock lock(mutex_);
  if (exists(key)) {
    std::cout << std::format("[Store] Deleted key {}", key) << std::endl;
    data_.erase(std::string(key));
    return true;
  }
  std::cout << std::format("[Store] Key {} does not exist", key) << std::endl;
  return false;
}

bool Store::exists(std::string_view key) const {
  return data_.count(std::string(key)) > 0;
}
