#pragma once
#include <SFML/Graphics.hpp>

#include "Animation.hpp"

class Player {
 public:
  Player(const sf::Texture* texture, const sf::Vector2u& image_count,
         const float switch_time, const float speed,
         const float jumpHeight) noexcept;
  void update(const float delta_time) noexcept;
  void draw(sf::RenderWindow& window) const { window.draw(body); };
  void onCollision(const sf::Vector2f& direction, const float push) noexcept;
  void reset() noexcept;
  constexpr void die() noexcept { is_alive = false; }
  [[nodiscard]] sf::Vector2f getPosition() const noexcept {
    return body.getPosition();
  }
  [[nodiscard]] sf::Vector2f getSize() const noexcept { return body.getSize(); }
  [[nodiscard]] constexpr bool isAlive() const noexcept { return is_alive; }

 private:
  sf::RectangleShape body{{100.0F, 150.0F}};
  Animation animation;
  unsigned int row{0U};
  float speed;
  bool face_right{true};
  bool is_alive{true};
  bool can_jump{true};
  sf::Vector2f velocity;
  float jumpHeight;
  static const float gravity;
};
