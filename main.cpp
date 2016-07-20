#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "managers/fontmanager.hpp"
#include "managers/sound_manager.hpp"
#include "game/engine.hpp"

int main(int /*argc*/, char **/*argv*/)
{
  const unsigned int window_width {800};
  const unsigned int window_height {800};

  // Create window
  std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(window_width, window_height), "Squares");
  window->setFramerateLimit(60);  

  // Init managers
  font::FontManager::init("resources/fonts/");
  sound::SoundManager::init("resources/sounds/");

  // Game loop  
  game::Engine engine{window};
  engine.start();

  return EXIT_SUCCESS;
}
