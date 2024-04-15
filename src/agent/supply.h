#ifndef THUAI7_AGENT_SUPPLY_H_
#define THUAI7_AGENT_SUPPLY_H_

#include "position.h"

namespace thuai7_agent {

struct Supply {
  enum class Kind {
    kS686,
    kVectory,
    kAwm,
    kM16,
    kBullet,
    kBandage,
    kPrimaryArmor,
    kPremiumArmor,
    kFirstAid,
    kGrenade,
  };

  Kind kind;
  int count;
  Position position;
};

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_SUPPLY_H_
