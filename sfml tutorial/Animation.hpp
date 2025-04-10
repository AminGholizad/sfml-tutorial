#pragma once
#include <SFML/Graphics.hpp>
class Animation {
 public:
  constexpr Animation(const sf::Texture* texture,
                      const sf::Vector2u& image_count,
                      const float switch_time) noexcept
      : image_count{image_count},
        switch_time{switch_time},
        uv_rect{{0, 0},
                sf::Vector2i(
                    static_cast<int>(texture->getSize().x / image_count.x),
                    static_cast<int>(texture->getSize().y / image_count.y))} {}
  void update(const unsigned int row, const float delta_time,
              const bool face_right) noexcept;

 private:
  sf::Vector2u image_count{0U, 0U};
  sf::Vector2u current_image;
  float total_time{0.0F};
  float switch_time;

 public:
  sf::IntRect uv_rect;
};
