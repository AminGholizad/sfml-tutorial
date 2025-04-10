#pragma once
#include <SFML/Graphics.hpp>

class Platform {
 public:
  Platform(const sf::Texture* texture, const sf::Vector2f& size,
           const sf::Vector2f& position, const float push = 1.0F) noexcept;
  void draw(sf::RenderWindow& window) const;
  void onCollision(const sf::Vector2f& direction) noexcept;
  void reset() noexcept;
  [[nodiscard]] sf::Vector2f getPosition() const noexcept;
  [[nodiscard]] sf::Vector2f getSize() const noexcept;
  [[nodiscard]] constexpr float getPush() const noexcept { return push; };

 private:
  sf::RectangleShape body;
  float push;
  sf::Vector2f init_position;
};
