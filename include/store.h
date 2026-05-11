#pragma once
#include <optional>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <unordered_map>

class Store {
public:
  Store();
  ~Store();

  void set(std::string_view key, std::string_view value);
  std::optional<std::string> get(std::string_view key);
  bool del(std::string_view key);

private:
  std::unordered_map<std::string, std::string> data_;
  mutable std::shared_mutex mutex_;

  // Caller must hold at least a shared lock on mutex_.
  bool exists(std::string_view key) const;
};
