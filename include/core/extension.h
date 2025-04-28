

#include "sol/table.hpp"
#include <string>

namespace core {

struct Extension {
  std::string name;
  sol::table script;
};
} // namespace core
