#pragma once
#include <SFML/Graphics.hpp>

#include "Platform.hpp"
#include "Player.hpp"
namespace Collider {
[[nodiscard]] sf::Vector2f checkCollision(const Platform& platform,
                                          const Player& player) noexcept;
}  // namespace Collider
