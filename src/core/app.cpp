#include "../include/core/app.h"
#include "../include/utils/logger.h"
#include "core/extension_manager.h"
#include "core/suggestion_engine.h"

namespace core {
using namespace std;

App::App() {}

App::~App() {}

void App::run() {
  utils::Logger::info("Application is running...");
  ExtensionManager ext_mgr;
  ext_mgr.load_extensions("extensions");

  SuggestionEngine engine;
  engine.generate_suggestions();
}
} // namespace core
