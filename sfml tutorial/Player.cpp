#include "Player.hpp"

Player::Player(const sf::Texture* texture, const sf::Vector2u& image_count,
               const float switch_time, const float speed,
               const float jumpHeight) noexcept
    : animation{texture, image_count, switch_time},
      speed{speed},
      jumpHeight{jumpHeight} {
  body.setPosition({0.0F, 0.0F});
  body.setTexture(texture);
  body.setOrigin(body.getSize() / 2.0F);
}

void Player::update(const float delta_time) noexcept {
  if (is_alive) {
    velocity.x *= 0.1f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
      velocity.x -= speed;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
      velocity.x += speed;
    }
    if (can_jump && (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) ||
                     sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))) {
      can_jump = false;
      velocity.y = -sqrt(2.0F * gravity * jumpHeight);
    }
    velocity.y += gravity * delta_time;
  }

  if (velocity.x == 0.0F) {
    row = 0U;
  } else {
    row = 1U;
    if (velocity.x > 0.0F) {
      face_right = true;
    } else if (velocity.x < 0.0F) {
      face_right = false;
    }
  }
  if (velocity.y < 0.0F) {
    row = 2U;
  }
  if (!is_alive) {
    row = 8U;
  }
  animation.update(row, delta_time, face_right);
  body.setTextureRect(animation.uv_rect);
  body.move(velocity * delta_time);
}
void Player::onCollision(const sf::Vector2f& direction,
                         const float push) noexcept {
  if (direction.x != 0.0F) {
    velocity.x = 0;
  } else if (direction.y > 0.0F) {
    if (velocity.y > gravity * 2.0F) {
      is_alive = false;
    } else {
      velocity.y = 0;
      can_jump = true;
    }
  } else if (direction.y < 0.0F) {
    velocity.y = 0;
  }
  body.move({-direction.x * push, -direction.y * push});
}

void Player::reset() noexcept {
  is_alive = true;
  can_jump = true;
  face_right = true;
  velocity = {0.0F, 0.0F};
  body.setPosition({0.0F, 0.0F});
}

const float Player::gravity = 981.0F;
