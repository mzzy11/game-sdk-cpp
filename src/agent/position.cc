#include "position.h"

#include <fmt/format.h>

#include <string>


namespace thuai7_agent {

auto format_as(Position const& object) -> std::string {
  return fmt::format("Position{{x: {}, y: {}}}", object.x, object.y);
}

}  // namespace thuai7_agent
