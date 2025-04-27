#include "../include/core/suggestion_engine.h"
#include "../include/utils/logger.h"

namespace core {
using namespace utils;
SuggestionEngine::SuggestionEngine() {};
SuggestionEngine::~SuggestionEngine() {};

void SuggestionEngine::generate_suggestions() {
  Logger::info("Generating suggestions...");
}
} // namespace core
