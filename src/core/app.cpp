#include "../include/core/app.h"
#include "../include/utils/logger.h"
#include "core/extension_manager.h"
#include "core/prompt_engine.h"
#include <curl/curl.h>

namespace core {
using namespace std;

App::App() { curl_global_init(CURL_GLOBAL_DEFAULT); }

App::~App() { curl_global_cleanup(); }

void App::run() {
  utils::Logger::info("Application is running...");
  ExtensionManager ext_mgr;
  ext_mgr.load_extensions("extensions");

  PromptEngine engine(ext_mgr);

  std::string input;
  bool running = true;
  bool in_extension_mode = false;

  while (running) {
    if (!in_extension_mode) {
      std::cout << "Type extension name (or 'exit')> ";
      std::getline(std::cin, input);

      if (input == "exit") {
        running = false;
        break;
      }

      auto suggestions = engine.suggest_extensions(input);
      if (suggestions.empty()) {
        std::cout << "No matching extensions found.\n";
      } else {
        std::cout << "Suggestions:\n";
        for (auto &s : suggestions) {
          std::cout << "- " << s << "\n";
        }

        std::cout << "Select extension> ";
        std::getline(std::cin, input);

        if (ext_mgr.switch_extension(input)) {
          in_extension_mode = true;
        } else {
          std::cout << "Failed to switch extension.\n";
        }
      }
    } else {
      std::cout << ext_mgr.get_current_extension().value() << " > ";
      std::getline(std::cin, input);

      if (input == "/exit") {
        in_extension_mode = false;
        ext_mgr.get_current_extension().reset();
        continue;
      }

      auto output = engine.process_prompt(input);
      std::cout << output << "\n";
    }
  }

  utils::Logger::info("Exiting application...");
}

} // namespace core
