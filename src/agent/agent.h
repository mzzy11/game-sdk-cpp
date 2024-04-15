#ifndef THUAI7_AGENT_AGENT_H_
#define THUAI7_AGENT_AGENT_H_

#include <cstdint>
#include <optional>
#include <string_view>
#include <vector>

#include "map.h"
#include "player_info.h"
#include "position.h"
#include "safe_zone.h"
#include "supply.h"

namespace thuai7_agent {

class Agent {
 public:
  Agent(std::string_view host, uint16_t port, std::string_view token);

  Agent(Agent const&) = delete;
  Agent(Agent&&) = default;
  auto operator=(Agent const&) -> Agent& = delete;
  auto operator=(Agent&&) -> Agent& = default;
  ~Agent();

  void Abandon(Supply::Kind item_kind, int count);

  void PickUp(Supply::Kind item_kind, int count, Position const& position);

  void SwitchArm(Supply::Kind item_kind);

  void UseMedicine(Supply::Kind item_kind);

  void UseGrenade(Position const& position);

  void Move(Position const& position);

  void Stop();

  void Attack(Position const& position);

  void ChooseOrigin(Position const& position);

  auto GetSelfPlayerInfo() -> std::optional<PlayerInfo const&>;

  auto GetAllPlayerInfo() -> std::optional<std::vector<PlayerInfo> const&>;

  auto GetMap() -> std::optional<Map const&>;

  auto GetSupplies() -> std::optional<std::vector<Supply> const&>;

  auto GetSafeZone() -> std::optional<SafeZone const&>;
};

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_AGENT_H_
