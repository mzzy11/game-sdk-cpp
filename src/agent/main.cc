#include <spdlog/spdlog.h>

#include <cxxopts.hpp>
#include <thread>

#include "agent.h"

using namespace std::chrono_literals;

// You can change this value to adjust the loop interval.
constexpr auto kLoopInterval = 100ms;

void Setup(thuai7_agent::Agent& agent);
void Loop(thuai7_agent::Agent& agent);

auto main(int argc, char* argv[]) -> int {
  cxxopts::Options options("agent");
  options.add_options()(
      "server", "Server address",
      cxxopts::value<std::string>()->default_value("ws://localhost:14514"))(
      "token", "Agent token", cxxopts::value<std::string>()->default_value(""))(
      "h,help", "Print usage");
  auto result = options.parse(argc, argv);

  if (result.count("help") > 0) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  std::string host = result["server"].as<std::string>();
  std::string token = result["token"].as<std::string>();

  thuai7_agent::Agent agent(token);

  agent.Connect(host);

  Setup(agent);

  while (true) {
    std::this_thread::sleep_for(kLoopInterval);
    Loop(agent);
  }

  agent.Disconnect();

  return 0;
}

void Setup(thuai7_agent::Agent& agent) {
  // Your code here.
}

void Loop(thuai7_agent::Agent& agent) {
  // Your code here.
}
