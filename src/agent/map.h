#ifndef THUAI7_AGENT_MAP_H_
#define THUAI7_AGENT_MAP_H_

#include <vector>

#include "position.h"

namespace thuai7_agent {

struct Map {
  int width;
  int height;
  std::vector<Position> obstacles;
};

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_MAP_H_
