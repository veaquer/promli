#include "../include/lua/binding.h"
#include "../include/utils/logger.h"
#include "sol/protected_function_result.hpp"
#include "utils/net.h"
#include <exception>
#include <string>

namespace lua {
Binding::Binding() {};
Binding::~Binding() { shutdown(); };

void Binding::initialize() {
  utils::Logger::info("Initializing Lua bindings...");
  lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string,
                     sol::lib::table);
  lua.set_function("http_get", &utils::net::http_get, utils::net());
}

sol::table Binding::load_script(const std::string &path) {

  try {
    sol::object script = lua.script_file(path);
    utils::Logger::info("Extension loaded: " + path);
    return script;
  } catch (const sol::error &e) {
    utils::Logger::err("Error loading extension: " + path + ": " + e.what());
    return sol::nil;
  }
}

sol::object Binding::run_function(sol::table &script,
                                  const std::string &func_name,
                                  const std::string &arg) {
  try {
    if (!script.is<sol::table>()) {
      utils::Logger::err("Loaded script is not a table.");
      return sol::nil;
    }
    sol::table table = script.as<sol::table>();
    sol::function func = table[func_name];
    if (!func.valid()) {
      utils::Logger::err("Function " + func_name + " not found in script.");
      return sol::nil;
    }

    sol::protected_function_result result = func(arg);
    if (!result.valid()) {
      utils::Logger::err(std::string("Error running function: ") +
                         result.get<sol::error>().what());
      return sol::nil;
    }
    return result;
  } catch (const sol::error &e) {
    utils::Logger::err("Exception running function:");
    utils::Logger::err(e.what());
    return sol::nil;
  }
}

void Binding::shutdown() {
  utils::Logger::info("Shutting down Lua bindings...");
  lua = sol::state();

  utils::Logger::info("Lua bindings successfuly shut down.");
}
} // namespace lua
