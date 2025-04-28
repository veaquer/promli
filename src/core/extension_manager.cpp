#include "../include/core/extension_manager.h"
#include "../include/utils/logger.h"
#include "lua/binding.h"
#include "sol/table.hpp"
#include <filesystem>
#include <optional>
#include <string>
#include <unordered_map>

namespace core {
using namespace utils;
using namespace std;
namespace fs = filesystem;
ExtensionManager::ExtensionManager() { binding.initialize(); };

ExtensionManager::~ExtensionManager() { binding.shutdown(); };

std::string ExtensionManager::get_extension_name(const std::string &path) {
  auto filename = path.substr(path.find_last_of("/\\") + 1);
  auto no_ext = filename.substr(0, filename.find_last_of('.'));
  return no_ext;
}

std::unordered_map<std::string, core::Extension> &
ExtensionManager::get_extensions() {
  return this->extensions;
}

bool ExtensionManager::switch_extension(const std::string &name) {
  if (extensions.find(name) != extensions.end()) {
    current_extension = name;
    utils::Logger::info("Switched to extension: " + name);
    return true;
  } else {
    utils::Logger::err("Extension not found: " + name);
    return false;
  }
}

std::optional<std::string> &ExtensionManager::get_current_extension() {
  return this->current_extension;
}

lua::Binding &ExtensionManager::get_binding() { return this->binding; }

void ExtensionManager::load_extensions(
    const string &folder_path = "extensions") {
  Logger::info("Loading extensions from '" + folder_path + "' ...");
  // load folder
  try {
    if (fs::exists(folder_path) && fs::is_directory(folder_path)) {
      for (const auto &entry : fs::directory_iterator(folder_path)) {
        const auto &path = entry.path().string();
        const auto ext_name = get_extension_name(path);
        Logger::info(string("Reading lua extension:") + ext_name);
        sol::table script = binding.load_script(path);
        extensions[ext_name] = {ext_name, script};
        utils::Logger::info("Extension loaded and registered: " + ext_name);
      }
    }
  } catch (const exception &e) {
    Logger::err("While load extensions: ");
    Logger::err(e.what());
  }
}
} // namespace core
