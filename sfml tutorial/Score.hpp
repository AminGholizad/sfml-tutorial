#pragma once
#include <SFML/Graphics.hpp>

#include "Player.hpp"

class Score {
 public:
  void update(const float delta_time, Player& play_position) noexcept;
  constexpr void reset() noexcept {
    time = 0.0F;
    max_height = 0.0F;
  }
  [[nodiscard]] constexpr float getScore() const noexcept {
    return max_height - time;
  }

 private:
  float time{};
  float max_height{};
};
