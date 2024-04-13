#include "AgentClient.h"

#include <iostream>

AgentClient::AgentClient(const char *url, EventLoopPtr loop)
    : WebSocketClient(loop), url_(url) {}

AgentClient::~AgentClient() { close(); }

auto AgentClient::connect() -> int {
  // Set callbacks in a similar manner as the example provided
  onopen = [this]() { std::cout << "WebSocket connected." << std::endl; };

  onmessage = [this](const std::string &msg) {
    std::cout << "Received message: " << msg << std::endl;
  };

  onclose = []() { std::cout << "WebSocket closed." << std::endl; };

  // Set other options like ping interval and reconnect policy if needed

  // Finally, attempt to open the connection with optional headers
  http_headers headers;
  headers["Origin"] = "http://example.com/";
  return open(url_.c_str(), headers);
}

void AgentClient::close() {
  if (isConnected()) {
    WebSocketClient::close();
  }
}

void AgentClient::send(const std::string &message) {
  if (isConnected()) {
    WebSocketClient::send(message);
  } else {
    std::cerr << "WebSocket is not connected, cannot send message."
              << std::endl;
  }
}
