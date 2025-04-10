#include "Score.hpp"

void Score::update(const float delta_time, Player& player) noexcept {
  float player_height = -player.getPosition().y;
  if (player.isAlive()) {
    time += delta_time;
    max_height = std::max(player_height, max_height);
  }
  if (auto score = getScore(); 0.0F < score && score < 100.0F) {
    player.die();
  }
}
