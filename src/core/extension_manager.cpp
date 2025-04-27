#include "../include/core/extension_manager.h"
#include "../include/utils/logger.h"
#include "lua/binding.h"
#include <filesystem>
#include <string>

namespace core {
using namespace utils;
using namespace std;
namespace fs = filesystem;
ExtensionManager::ExtensionManager() { binding.initialize(); };

ExtensionManager::~ExtensionManager() {};

void ExtensionManager::load_extensions(
    const string &folder_path = "extensions") {
  Logger::info("Loading extensions...");
  // load folder
  try {
    if (fs::exists(folder_path) && fs::is_directory(folder_path)) {
      for (const auto &entry : fs::directory_iterator(folder_path)) {
        const auto &path = entry.path();

        if (fs::is_regular_file(path)) {
          Logger::info(string("Reading lua extension:") +
                       path.filename().c_str());
          binding.load_script(path.relative_path());
          binding.run_function(path.relative_path(), "hello");
        }
      }
    }
  } catch (const exception &e) {
    Logger::err("While load extensions: ");
    Logger::err(e.what());
  }
}
} // namespace core
