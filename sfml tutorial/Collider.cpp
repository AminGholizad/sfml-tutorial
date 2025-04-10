#include "Collider.hpp"

#include <cmath>

namespace Collider {
constexpr sf::Vector2f getDelta(const sf::Vector2f& thisPosition,
                                const sf::Vector2f& otherPosition) noexcept {
  return {otherPosition.x - thisPosition.x, otherPosition.y - thisPosition.y};
}

constexpr sf::Vector2f getIntersect(
    const sf::Vector2f& delta, const sf::Vector2f& thisHalfSize,
    const sf::Vector2f& otherHalfSize) noexcept {
  return {std::abs(delta.x) - (thisHalfSize.x + otherHalfSize.x) / 2.0F,
          std::abs(delta.y) - (thisHalfSize.y + otherHalfSize.y) / 2.0F};
}
sf::Vector2f checkCollision(const Platform& platform,
                            const Player& player) noexcept {
  const auto delta = getDelta(platform.getPosition(), player.getPosition());

  const auto intersect =
      getIntersect(delta, platform.getSize(), player.getSize());

  if (intersect.x < 0.0F && intersect.y < 0.0F) {
    if (intersect.x > intersect.y) {
      if (delta.x > 0.0F) {
        return intersect.componentWiseMul({1.0F, 0.0F});
      } else {
        return intersect.componentWiseMul({-1.0F, 0.0F});
      }
    } else {
      if (delta.y > 0.0F) {
        return intersect.componentWiseMul({0.0F, 1.0F});
      } else {
        return intersect.componentWiseMul({0.0F, -1.0F});
      }
    }
  }
  return {0.0F, 0.0F};
}

}  // namespace Collider
