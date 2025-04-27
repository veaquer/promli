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
  lua.open_libraries(sol::lib::base, sol::lib::package);
  lua.set_function("http_get", &utils::net::http_get, utils::net());
}

bool Binding::load_script(const std::string &path) {
  if (loaded_scripts.find(path) != loaded_scripts.end()) {
    return false;
  }

  try {
    sol::table script = lua.script_file(path);
    loaded_scripts[path] = script;
    utils::Logger::info("Extension loaded: " + path);
    return true;
  } catch (const sol::error &e) {
    utils::Logger::err("Error loading extension: " + path + ": " + e.what());
    return false;
  }
}

sol::object Binding::run_function(const std::string &path,
                                  const std::string &func_name) {
  try {
    if (loaded_scripts.find(path) == loaded_scripts.end()) {
      if (!this->load_script(path)) {
        utils::Logger::err("Failed to load script: " + path);
        return sol::nil;
      }
    }

    sol::table script = loaded_scripts[path];
    sol::function func = script[func_name];

    if (!func) {
      utils::Logger::err("Function " + func_name + " not found in script " +
                         path);
    }
    utils::Logger::info("Calling function " + func_name + " in script " + path);
    sol::protected_function_result result = func();
    if (!result.valid()) {
      utils::Logger::warn("Function " + func_name + " in script " + path +
                          " returned no value");
      return sol::nil;
    }
    return result;
  } catch (sol::error &e) {
    utils::Logger::err("While trying to run extension function:");
    utils::Logger::err(e.what());
    return sol::nil;
  }
}

void Binding::shutdown() {
  utils::Logger::info("Shutting down Lua bindings...");
  loaded_scripts.clear();
  lua = sol::state();

  utils::Logger::info("Lua bindings successfuly shut down.");
}
} // namespace lua
