#include <SFML/Graphics.hpp>
#include <print>
#include <span>
#include <vector>

#include "Collider.hpp"
#include "Platform.hpp"
#include "Player.hpp"
#include "Score.hpp"

namespace {
const float VIEW_HIGHT_F = 512.0F;
const auto VIEW_HIGHT_UI = static_cast<unsigned int>(VIEW_HIGHT_F);
const auto VIEW_HIGHT_I = static_cast<int>(VIEW_HIGHT_F);
void end_game(Player& player, std::span<Platform> platforms,
              Score& score) noexcept {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
    player.reset();
    for (auto& platform : platforms) {
      platform.reset();
    }
    std::println("Your score is {}", score.getScore());
    score.reset();
  }
}

void check_collisions(Player& player, std::span<Platform> platforms) noexcept {
  for (auto& platform : platforms) {
    if (const auto directoin = Collider::checkCollision(platform, player);
        directoin != sf::Vector2f{0.0F, 0.0F}) {
      player.onCollision(directoin, platform.getPush());
      platform.onCollision(directoin);
    }
  }
}

void resizeView(const sf::RenderWindow& window, sf::View& view) noexcept {
  const sf::Vector2f windowSize{window.getSize()};
  const float aspectRatio = windowSize.x / windowSize.y;
  view.setSize({VIEW_HIGHT_F * aspectRatio, VIEW_HIGHT_F});
}

std::vector<Platform> generate_level() noexcept {
  static sf::Texture ground_texture("ground.png");
  static sf::Texture floating_texture("floating.png");
  ground_texture.setRepeated(true);
  ground_texture.setSmooth(true);
  floating_texture.setSmooth(true);
  std::vector<Platform> platforms;
  // boundary
  platforms.emplace_back(Platform{&ground_texture,
                                  {6.0F * VIEW_HIGHT_F, 300.0F},
                                  {0.0F, 100.0F},
                                  1.0F});  // ground
  platforms.emplace_back(Platform{&ground_texture,
                                  {VIEW_HIGHT_F, 4.0F * VIEW_HIGHT_F},
                                  {-3.0F * VIEW_HIGHT_F, 100.0F},
                                  1.0F});  // left wall
  platforms.emplace_back(Platform{&ground_texture,
                                  {VIEW_HIGHT_F, 4.0F * VIEW_HIGHT_F},
                                  {3.0F * VIEW_HIGHT_F, 100.0F},
                                  1.0F});  // right wall

  const float gap = 150.0F;
  // movable
  const sf::Vector2f movable_size{100.0F, 100.0F};
  const float movable_push = 0.5F;
  // not movable
  sf::Vector2f not_movable_size{600.0F, 100.0F};
  const sf::Vector2f shrink_rate{0.85F, 1.0F};
  for (auto i = 1; i < 100; ++i) {
    platforms.emplace_back(
        Platform{&floating_texture,
                 movable_size,
                 {50.0F, gap - (2.0F * gap * static_cast<float>(i))},
                 movable_push});
    platforms.emplace_back(
        Platform{&floating_texture,
                 not_movable_size,
                 {50.0F, -2.0F * gap * static_cast<float>(i)}});
    if (not_movable_size.x > 2 * not_movable_size.y) {
      not_movable_size = not_movable_size.componentWiseMul(shrink_rate);
    }
  }

  return platforms;
}

sf::RectangleShape create_background() {
  static sf::Texture background_texture("background.jpg");
  background_texture.setRepeated(true);
  sf::RectangleShape background{{VIEW_HIGHT_F * 100.0F, VIEW_HIGHT_F * 100.0F}};
  background.setTexture(&background_texture);
  background.setOrigin(background.getSize() / 2.0F);

  background.setTextureRect({{0, 0}, {VIEW_HIGHT_I * 100, VIEW_HIGHT_I * 100}});
  return background;
}
void redraw(sf::RenderWindow& window, sf::View& view,
            const sf::RectangleShape& background, const Player& player,
            std::span<const Platform> platforms) {
  view.setCenter(player.getPosition());
  window.clear();
  window.setView(view);
  window.draw(background);
  for (const auto& platform : platforms) {
    platform.draw(window);
  }
  player.draw(window);
  window.display();
}
}  // namespace

int main() noexcept {
  try {
    sf::RenderWindow window(sf::VideoMode({VIEW_HIGHT_UI, VIEW_HIGHT_UI}),
                            "SFML Tutorial");
    sf::View view{{0.0F, 0.0F}, {VIEW_HIGHT_F, VIEW_HIGHT_F}};
    const sf::Texture player_texture("tux.png");
    const auto background = create_background();

    Player player{&player_texture, {3U, 9U}, 0.3F, 200.0F, 250.0F};

    std::vector<Platform> platforms = generate_level();

    sf::Clock clock;
    Score score;
    while (window.isOpen()) {
      const float delta_time =
          std::min(clock.restart().asSeconds(), 1.0F / 20.0F);
      while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
          window.close();
        } else if (const auto* keyPressed =
                       event->getIf<sf::Event::KeyPressed>()) {
          if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
            window.close();
          }
        } else if (event->is<sf::Event::Resized>()) {
          resizeView(window, view);
        } else if (const auto* text = event->getIf<sf::Event::TextEntered>()) {
          if (text->unicode < 128U) {
            std::print("{}", static_cast<char>(text->unicode));
          }
        }
      }

      player.update(delta_time);

      score.update(delta_time, player);
      check_collisions(player, platforms);

      if (!player.isAlive()) {
        end_game(player, platforms, score);
      }
      redraw(window, view, background, player, platforms);
    }
    std::println("Your score is {}", score.getScore());
  } catch (const sf::Exception& e) {
    std::println("Exception: {}", e.what());
  } catch (const std::exception& e) {
    std::println("Exception: {}", e.what());
  } catch (...) {
    std::println("Unknown exception occurred.");
  }
  return 0;
}
