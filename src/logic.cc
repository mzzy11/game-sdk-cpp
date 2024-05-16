#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#include <vector>

#include "agent/agent.h"
#include "agent/position.h"
#include "path_finding.h"
#include "shot_check.h"

constexpr auto kFloatPositionShift = 0.5;

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
static struct {
  std::vector<thuai7_agent::Position<int>> path;
} state;
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

void Setup(thuai7_agent::Agent& agent) {
  auto const& supplies = agent.supplies();
  auto supply_vector = supplies->get();
  int i=0;
  for(;i<supply_vector.size();i++){
    if(supply_vector[i].kind!=thuai7_agent::SupplyKind::kGrenade)
      continue;
    else break;
  }
  spdlog::info("{}",supply_vector[i].position);
  agent.ChooseOrigin(supply_vector[i].position);
  // Your code here.
}

int Check(thuai7_agent::Position<int> position,std::vector<thuai7_agent::Supply> supply){
  for(int i=0;i<supply.size();i++){
      auto s_position_int =
      thuai7_agent::Position<int>{static_cast<int>(supply[i].position.x),
                                  static_cast<int>(supply[i].position.y)};
      if(position==s_position_int)
        return i;
  }
  return -1;
}

void Loop(thuai7_agent::Agent& agent) {
  // Your code here.
  // Here is an example of how to use the agent.
  // Always move to the opponent's position, keep one cell away from the
  // opponent, and attack the opponent.

  auto const& player_info_list = agent.all_player_info().value().get();
  auto const self_id = agent.self_id().value();
  auto const& self_info = player_info_list.at(self_id);
  auto const& opponent_info = player_info_list.at(1 - self_info.id);

  auto const& supplies = agent.supplies();
  auto supply_vector = supplies->get();
  auto const& map = agent.map().value().get();

  auto self_position_int =
      thuai7_agent::Position<int>{static_cast<int>(self_info.position.x),
                                  static_cast<int>(self_info.position.y)};
  auto opponent_position_int =
      thuai7_agent::Position<int>{static_cast<int>(opponent_info.position.x),
                                  static_cast<int>(opponent_info.position.y)};

  if (std::find(state.path.begin(), state.path.end(), self_position_int) ==
          state.path.end() ||
      std::find(state.path.begin(), state.path.end(), opponent_position_int) ==
          state.path.end()) {
    state.path = FindPathBeFS(map, self_position_int, opponent_position_int);

    if (state.path.empty()) {
      spdlog::info("no path from {} to {}", self_position_int,
                   opponent_position_int);
      return;
    }

    spdlog::info("found path from {} to {}", self_position_int,
                 opponent_position_int);
  }

  while (state.path.front() != self_position_int) {
    state.path.erase(state.path.begin());
  }

  if (state.path.size() > 1) {
      if (state.path.size() > 1) {
    auto next_position_int = state.path.at(1);
    auto next_position = thuai7_agent::Position<float>{
        static_cast<float>(next_position_int.x + kFloatPositionShift),
        static_cast<float>(next_position_int.y + kFloatPositionShift)};
    if(Check(self_position_int,supply_vector)!=-1){
        spdlog::info("pick");
        int i=Check(self_position_int,supply_vector);
        spdlog::info("{}",i);
        agent.PickUp(supply_vector[i].kind,supply_vector[i].count);
        auto players_info = agent.all_player_info();
        spdlog::info("{}",players_info->get());
    }
    agent.UseGrenade(next_position);
    auto gre = agent.grenade_info()->get();
    spdlog::info("{}",gre);
    //spdlog::info("moving from {} to {}", self_info.position, next_position);
    return;
  }
  }

  if (CheckShotFeasible(map, self_info.position, opponent_info.position,
                        self_info.range)) {
    agent.Attack(opponent_info.position);
  }
}
