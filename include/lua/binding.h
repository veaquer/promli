#pragma once

#include "core/extension.h"
#include <sol/sol.hpp>
#include <string>
namespace lua {
class Binding {
private:
  sol::state lua;

public:
  Binding();
  ~Binding();

  void initialize();
  sol::table load_script(const std::string &path);

  sol::object run_function(sol::table &script, const std::string &func_name,
                           const std::string &arg);
  void shutdown();
};
} // namespace lua
