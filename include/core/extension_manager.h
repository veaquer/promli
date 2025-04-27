#pragma once
#include "lua/binding.h"
#include <string>
#include <vector>

namespace core {

class ExtensionManager {
public:
  ExtensionManager();
  ~ExtensionManager();
  void load_extensions(const std::string &folder_path);

private:
  lua::Binding binding;
  std::vector<std::string> loaded_extensions;
};
} // namespace core
