#ifndef THUAI7_AGENT_PLAYER_INFO_H_
#define THUAI7_AGENT_PLAYER_INFO_H_

#include <vector>

#include "position.h"

namespace thuai7_agent {

enum class ArmorKind {
  kNone,
  kPrimary,
  kPremium,
};

enum class FirearmKind {
  kAwm,
  kM16,
  kS686,
  kVector,
};

struct Item {
  enum class Kind {
    kBandage,
    kBullet,
    kFirstAid,
    kGrenade,
  };

  Kind kind;
  int count;
};

struct PlayerInfo {
  int id;
  ArmorKind armor;
  int health;
  float speed;
  FirearmKind firearm;
  float range;
  Position position;
  std::vector<Item> inventory;
};

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_PLAYER_INFO_H_
