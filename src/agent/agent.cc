#include "agent.h"

#include <fmt/format.h>
#include <hv/EventLoop.h>
#include <hv/WebSocketClient.h>
#include <hv/hloop.h>

#include <string>
#include <string_view>

namespace thuai7_agent {

Agent::Agent(std::string_view token, hv::EventLoopPtr const& event_loop)
    : token_(token) {
  ws_client_ = std::make_unique<hv::WebSocketClient>(event_loop);

  reconn_setting_t reconn_setting;
  reconn_setting.delay_policy = 0;  // Fixed delay.

  ws_client_->setReconnect(&reconn_setting);

  ws_client_->onmessage = [this](std::string const& msg) { OnMessage(msg); };
}

void Agent::Connect(std::string_view server_address) {
  ws_client_->open(server_address.data());
}

auto Agent::IsConnected() const -> bool { return ws_client_->isConnected(); }

void Agent::Disconnect() { ws_client_->close(); }

void Agent::OnMessage(std::string_view message) {
  // TODO(mzzy11): Parse message.
}

auto format_as(Agent const& object) -> std::string {
  return fmt::format("Agent{{token: {}}}", object.token());
}

}  // namespace thuai7_agent