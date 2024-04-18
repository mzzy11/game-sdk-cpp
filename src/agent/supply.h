#ifndef THUAI7_AGENT_SUPPLY_H_
#define THUAI7_AGENT_SUPPLY_H_

#include <string>

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
  Position<float> position;
};

auto format_as(Supply::Kind object) -> std::string;
auto format_as(Supply const& object) -> std::string;

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_SUPPLY_H_
