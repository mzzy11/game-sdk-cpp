#ifndef AGENT_CLIENT_H
#define AGENT_CLIENT_H

#include "hv/WebSocketClient.h"
#include "nlohmann/json.hpp"


using json = nlohmann::json;
using namespace hv;

class AgentClient : public WebSocketClient {
public:
  AgentClient(const char *url, EventLoopPtr loop = nullptr);
  ~AgentClient();

  auto connect() -> int;
  void close();
  void send(const std::string &message);

  // 其他成员函数可以在这里继续定义

private:
  std::string url_;
  // 其他私有成员可以在这里定义
};

#endif // AGENT_CLIENT_H
