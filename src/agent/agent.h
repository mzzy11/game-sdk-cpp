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

#include "map.h"
#include "player_info.h"
#include "position.h"
#include "safe_zone.h"
#include "supply.h"

namespace thuai7_agent {

class Agent {
 public:
  explicit Agent(std::string_view token, hv::EventLoopPtr const& event_loop);

  Agent(Agent const&) = delete;
  Agent(Agent&&) = default;
  auto operator=(Agent const&) -> Agent& = delete;
  auto operator=(Agent&&) -> Agent& = default;
  ~Agent() = default;

  void Connect(std::string_view server_address);

  [[nodiscard]] auto IsConnected() const -> bool;

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

  [[nodiscard]] auto token() const -> std::string { return token_; }

 private:
  void OnMessage(std::string_view message);

  std::optional<std::vector<PlayerInfo>> all_player_info_;
  std::optional<Map> map_;
  std::optional<std::vector<Supply>> supplies_;
  std::optional<SafeZone> safe_zone_;
  std::optional<int> self_id_;
  std::string token_;
  std::unique_ptr<hv::WebSocketClient> ws_client_;
};

auto format_as(Agent const& object) -> std::string;

}  // namespace thuai7_agent

#endif  // THUAI7_AGENT_AGENT_H_
