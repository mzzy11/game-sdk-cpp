#include "agent.h"

#include <hv/EventLoop.h>

#include <string>
#include <string_view>
#include <utility>

namespace thuai7_agent {

Agent::Agent(std::string token) : token_(std::move(token)) {
  ws_client_ = std::make_unique<hv::WebSocketClient>();

  ws_client_->onmessage = [this](const std::string& msg) { OnMessage(msg); };
}

void Agent::Connect(std::string_view server_address) {
  ws_client_->open(server_address.data());

  using namespace std::chrono_literals;

  while (!ws_client_->isConnected()) {
  }
}

void Agent::Disconnect() { ws_client_->close(); }

void Agent::OnMessage(std::string_view message) {
  // TODO(mzzy11): Parse message.
}

}  // namespace thuai7_agent
