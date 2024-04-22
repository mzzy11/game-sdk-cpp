#include "agent.h"

#include <fmt/format.h>
#include <hv/EventLoop.h>
#include <hv/WebSocketClient.h>
#include <hv/hloop.h>

#include <string>
#include <string_view>

#include "agent/message.h"
#include "agent/supply.h"
#include "hv/Event.h"

namespace thuai7_agent {

Agent::Agent(std::string_view token, hv::EventLoopPtr const& event_loop,
             int loop_interval)
    : event_loop_(event_loop), token_(token) {
  loop_timer_id_ =
      event_loop_->setInterval(loop_interval, [this](hv::TimerID) { Loop(); });

  ws_client_ = std::make_unique<hv::WebSocketClient>(event_loop);

  reconn_setting_t reconn_setting;
  reconn_setting.delay_policy = 0;  // Fixed delay.

  ws_client_->setReconnect(&reconn_setting);

  ws_client_->onmessage = [this](std::string const& msg) {
    OnMessage(Message(msg));
  };
}

Agent::~Agent() { event_loop_->killTimer(loop_timer_id_); }

void Agent::Connect(std::string_view server_address) {
  ws_client_->open(server_address.data());
}

auto Agent::IsConnected() const -> bool { return ws_client_->isConnected(); }

void Agent::Disconnect() { ws_client_->close(); }

auto Agent::IsGameReady() const -> bool {
  return all_player_info_.has_value() && map_.has_value() &&
         supplies_.has_value() && safe_zone_.has_value() &&
         self_id_.has_value();
}

void Agent::Abandon(SupplyKind target_supply, int count) {
  // TODO(ethkuil):
}

void Agent::PickUp(SupplyKind target_supply, int count,
                   Position<float> const& position) {
  // TODO(ethkuil):
}

void Agent::SwitchFirearm(FirearmKind target_firearm) {
  // TODO(ethkuil):
}

void Agent::UseMedicine(MedicineKind target_medicine) {
  // TODO(ethkuil):
}

void Agent::UseGrenade(Position<float> const& position) {
  // TODO(ethkuil):
}

void Agent::Move(Position<float> const& position) {
  // TODO(ethkuil):
}

void Agent::Stop() {
  // TODO(ethkuil):
}

void Agent::Attack(Position<float> const& position) {
  // TODO(ethkuil):
}

void Agent::ChooseOrigin(Position<float> const& position) {
  // TODO(ethkuil):
}

void Agent::Loop() {
  // TODO(mzzy11): Implement loop.
}

void Agent::OnMessage(Message const& message) {
  // TODO(ethkuil): Parse message.
}

auto format_as(Agent const& object) -> std::string {
  return fmt::format("Agent{{token: {}}}", object.token());
}

}  // namespace thuai7_agent
