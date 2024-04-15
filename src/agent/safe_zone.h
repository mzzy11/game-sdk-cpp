#ifndef THUAI7_AGENT_SAFE_ZONE_H_
#define THUAI7_AGENT_SAFE_ZONE_H_

#include "position.h"

namespace thuai7_agent {

struct SafeZone {
  Position center;
  int radius;
};

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_SAFE_ZONE_H_
