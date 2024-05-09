#include "shot_check.h"

#include <cmath>

#include "agent/map.h"
#include "agent/position.h"

constexpr float kSearchStep = 0.1F;

static auto CheckPointAndUnitSquareIntersection(
    thuai7_agent::Position<float> const& point_position,
    thuai7_agent::Position<float> const& unit_square_min_position) -> bool;

auto CheckShotFeasible(thuai7_agent::Map const& map,
                       thuai7_agent::Position<float> const& shooter_position,
                       thuai7_agent::Position<float> const& target_position,
                       float shot_range) -> bool {
  auto const delta_x = target_position.x - shooter_position.x;
  auto const delta_y = target_position.y - shooter_position.y;
  auto const distance = std::sqrt(delta_x * delta_x + delta_y * delta_y);

  if (distance > shot_range) {
    return false;
  }

  for (float delta_distance = 0.0F; delta_distance < distance;
       delta_distance += kSearchStep) {
    auto const current_position = thuai7_agent::Position<float>{
        shooter_position.x + delta_x * delta_distance / distance,
        shooter_position.y + delta_y * delta_distance / distance};

    for (auto const& obstacle : map.obstacles) {
      auto const obstacle_position_float = thuai7_agent::Position<float>{
          static_cast<float>(obstacle.x), static_cast<float>(obstacle.y)};
      if (CheckPointAndUnitSquareIntersection(current_position,
                                              obstacle_position_float)) {
        return false;
      }
    }
  }

  return true;
}

static auto CheckPointAndUnitSquareIntersection(
    thuai7_agent::Position<float> const& point_position,
    thuai7_agent::Position<float> const& unit_square_min_position) -> bool {
  float x_min = unit_square_min_position.x;
  float y_min = unit_square_min_position.y;
  float x_max = x_min + 1.0F;
  float y_max = y_min + 1.0F;

  return point_position.x >= x_min && point_position.x <= x_max &&
         point_position.y >= y_min && point_position.y <= y_max;
}