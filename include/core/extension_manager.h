#pragma once
#include "lua/binding.h"
#include <optional>
#include <string>
#include <unordered_map>

namespace core {

class ExtensionManager {
public:
  ExtensionManager();
  ~ExtensionManager();
  void load_extensions(const std::string &folder_path);
  std::unordered_map<std::string, core::Extension> &get_extensions();
  std::optional<std::string> &get_current_extension();
  std::string get_extension_name(const std::string &path);
  lua::Binding &get_binding();
  bool switch_extension(const std::string &name);

private:
  lua::Binding binding;
  std::unordered_map<std::string, core::Extension> extensions;
  std::optional<std::string> current_extension;
};
} // namespace core
