#include "../include/core/prompt_engine.h"
#include "../include/utils/logger.h"
#include "core/extension_manager.h"
#include "sol/error.hpp"
#include "sol/forward.hpp"
#include "sol/protected_function_result.hpp"
#include "sol/types.hpp"
#include <string>

namespace core {
using namespace utils;
PromptEngine::PromptEngine(ExtensionManager &ext_mgr) : ext_mgr(ext_mgr) {};
PromptEngine::~PromptEngine() {};

std::string PromptEngine::process_prompt(std::string &prompt) {
  if (!ext_mgr.get_current_extension().has_value()) {
    return "No extension selected. Please select one first.";
  }

  auto &ext = ext_mgr.get_extensions()[ext_mgr.get_current_extension().value()];
  sol::object result =
      ext_mgr.get_binding().run_function(ext.script, "response", prompt);
  if (result == sol::nil) {
    return "Error processing prompt: ";
  }

  return result.as<std::string>();
}

std::vector<std::string> PromptEngine::suggest_extensions(std::string &input) {
  Logger::info("Generating suggestions...");
  std::vector<std::string> suggestions;
  for (auto &[name, ext] : ext_mgr.get_extensions()) {
    if (name.find(input) != std::string::npos) {
      suggestions.push_back(name);
    }
  }

  return suggestions;
}
} // namespace core
