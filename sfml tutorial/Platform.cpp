#include "Platform.hpp"

Platform::Platform(const sf::Texture* texture, const sf::Vector2f& size,
                   const sf::Vector2f& position, const float push) noexcept
    : body{size}, push{push}, init_position{position} {
  body.setPosition(position);
  body.setOrigin(size / 2.0F);
  body.setTexture(texture);
}

void Platform::draw(sf::RenderWindow& window) const { window.draw(body); }

void Platform::onCollision(const sf::Vector2f& direction) noexcept {
  body.move({direction.x * (1.0F - push), direction.y * (1.0F - push)});
}

void Platform::reset() noexcept { body.setPosition(init_position); }

sf::Vector2f Platform::getPosition() const noexcept {
  return body.getPosition();
}

sf::Vector2f Platform::getSize() const noexcept { return body.getSize(); }
