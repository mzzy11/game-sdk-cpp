#ifndef THUAI7_AGENT_POSITION_H_
#define THUAI7_AGENT_POSITION_H_

#include <string>

namespace thuai7_agent {

struct Position {
  float x;
  float y;
};

auto format_as(Position const& object) -> std::string;

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_POSITION_H_
