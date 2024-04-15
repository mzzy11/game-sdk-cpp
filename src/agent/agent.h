#ifndef THUAI7_AGENT_AGENT_H_
#define THUAI7_AGENT_AGENT_H_

#include <hv/EventLoop.h>
#include <hv/WebSocketClient.h>

#include <memory>
#include <optional>
#include <string>
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
  explicit Agent(std::string token);

  Agent(Agent const&) = delete;
  Agent(Agent&&) = default;
  auto operator=(Agent const&) -> Agent& = delete;
  auto operator=(Agent&&) -> Agent& = default;
  ~Agent() = default;

  void Connect(std::string_view server_address);

  void Disconnect();

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

 private:
  void OnMessage(std::string_view message);

  std::optional<std::vector<PlayerInfo>> all_player_info_;
  std::optional<Map> map_;
  std::optional<std::vector<Supply>> supplies_;
  std::optional<SafeZone> safe_zone_;
  std::string token_;
  std::unique_ptr<hv::WebSocketClient> ws_client_;
};

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_AGENT_H_
