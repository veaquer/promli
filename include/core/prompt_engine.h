#pragma once

#include "core/extension_manager.h"
#include <string>
#include <vector>
namespace core {
class PromptEngine {
private:
  ExtensionManager &ext_mgr;

public:
  PromptEngine(ExtensionManager &ext_mgr);
  ~PromptEngine();
  std::string process_prompt(std::string &prompt);
  std::vector<std::string> suggest_extensions(std::string &input);
};
} // namespace core
