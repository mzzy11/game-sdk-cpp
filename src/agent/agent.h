#ifndef THUAI7_AGENT_AGENT_H_
#define THUAI7_AGENT_AGENT_H_

#include <hv/EventLoop.h>
#include <hv/WebSocketClient.h>

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "hv/Event.h"
#include "map.h"
#include "player_info.h"
#include "position.h"
#include "safe_zone.h"
#include "supply.h"

namespace thuai7_agent {

class Agent {
 public:
  explicit Agent(std::string_view token, hv::EventLoopPtr const& event_loop,
                 int loop_interval);

  Agent(Agent const&) = delete;
  Agent(Agent&&) = default;
  auto operator=(Agent const&) -> Agent& = delete;
  auto operator=(Agent&&) -> Agent& = default;
  ~Agent();

  // Methods for interacting with the server.

  [[nodiscard]] auto token() const -> std::string { return token_; }

  [[nodiscard]] auto IsConnected() const -> bool;

  void Connect(std::string_view server_address);

  void Disconnect();

  // Methods for interacting with the game.

  [[nodiscard]] auto all_player_info() const
      -> std::optional<std::reference_wrapper<std::vector<PlayerInfo> const>> {
    return all_player_info_;
  }

  [[nodiscard]] auto map() const
      -> std::optional<std::reference_wrapper<Map const>> {
    return map_;
  }

  [[nodiscard]] auto supplies() const
      -> std::optional<std::reference_wrapper<std::vector<Supply> const>> {
    return supplies_;
  }

  [[nodiscard]] auto safe_zone() const
      -> std::optional<std::reference_wrapper<SafeZone const>>;

  [[nodiscard]] auto self_id() const -> std::optional<int> { return self_id_; }

  [[nodiscard]] auto IsGameReady() const -> bool;

  void Abandon(SupplyKind item_kind, int count);

  void PickUp(SupplyKind item_kind, int count, Position<float> const& position);

  void SwitchArm(SupplyKind item_kind);

  void UseMedicine(SupplyKind item_kind);

  void UseGrenade(Position<float> const& position);

  void Move(Position<float> const& position);

  void Stop();

  void Attack(Position<float> const& position);

  void ChooseOrigin(Position<float> const& position);

 private:
  void Loop();
  void OnMessage(std::string_view message);

  hv::EventLoopPtr event_loop_;
  hv::TimerID loop_timer_id_;
  std::unique_ptr<hv::WebSocketClient> ws_client_;

  std::optional<std::vector<PlayerInfo>> all_player_info_;
  std::optional<Map> map_;
  std::optional<std::vector<Supply>> supplies_;
  std::optional<SafeZone> safe_zone_;
  std::optional<int> self_id_;
  std::string token_;
};

auto format_as(Agent const& object) -> std::string;

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_AGENT_H_
