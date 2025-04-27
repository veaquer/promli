#pragma once

#include <sol/sol.hpp>
#include <string>
#include <unordered_map>
namespace lua {
class Binding {
private:
  sol::state lua;
  std::unordered_map<std::string, sol::table> loaded_scripts;

public:
  Binding();
  ~Binding();

  void initialize();
  bool load_script(const std::string &path);

  sol::object run_function(const std::string &script_path,
                           const std::string &func_name);
  void shutdown();
};
} // namespace lua
