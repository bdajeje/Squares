#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "managers/fontmanager.hpp"
#include "game/game.hpp"

int main(int /*argc*/, char **/*argv*/)
{
  const unsigned int window_width {800};
  const unsigned int window_height {800};

  // Create window
  std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_width, window_height), "Squares");
  window->setFramerateLimit(60);

  // Init random
  srand(time(NULL));

  // Init managers
  font::FontManager::init("resources/fonts/");

  // Game loop
  game::Game game {window};
  game.restart();

  return EXIT_SUCCESS;
}
