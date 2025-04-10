#include "Animation.hpp"

#include <cmath>

void Animation::update(const unsigned int row, const float delta_time,
                       const bool face_right) noexcept {
  current_image.y = row;
  total_time += delta_time;
  if (total_time >= switch_time) {
    total_time -= switch_time;
    current_image.x += 1U;
    if (current_image.x >= image_count.x) {
      current_image.x = 0U;
    }
  }
  uv_rect.position.y = static_cast<int>(current_image.y) * uv_rect.size.y;
  if (face_right) {
    uv_rect.size.x = std::abs(uv_rect.size.x);
    uv_rect.position.x = static_cast<int>(current_image.x) * uv_rect.size.x;
  } else {
    uv_rect.position.x =
        static_cast<int>(current_image.x) + 1 * std::abs(uv_rect.size.x);
    uv_rect.size.x = -std::abs(uv_rect.size.x);
  }
}
