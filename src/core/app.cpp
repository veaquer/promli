#include "../include/core/app.h"
#include "../include/utils/logger.h"
#include "core/extension_manager.h"
#include "core/suggestion_engine.h"
#include <curl/curl.h>

namespace core {
using namespace std;

App::App() { curl_global_init(CURL_GLOBAL_DEFAULT); }

App::~App() { curl_global_cleanup(); }

void App::run() {
  utils::Logger::info("Application is running...");
  ExtensionManager ext_mgr;
  ext_mgr.load_extensions("extensions");

  SuggestionEngine engine;
  engine.generate_suggestions();
}
} // namespace core
