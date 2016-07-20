#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "managers/fontmanager.hpp"
#include "managers/sound_manager.hpp"
#include "game/engine.hpp"
#include "utils/settings.hpp"

int main(int /*argc*/, char **/*argv*/)
{
  // Read settings
  std::shared_ptr<utils::Settings> settings = std::make_shared<utils::Settings>("resources/settings");

  // Create window
  std::shared_ptr<sf::RenderWindow> window = std::make_shared<sf::RenderWindow>(sf::VideoMode(settings->get<int>(utils::Settings::WindowWidth, 800),
                                                                                              settings->get<int>(utils::Settings::WindowHeight, 800)),
                                                                                "Squares");
  window->setFramerateLimit(60);  

  // Init managers
  font::FontManager::init("resources/fonts/");
  sound::SoundManager::init("resources/sounds/");  

  // Game loop  
  game::Engine engine{window, settings};
  engine.start();

  return EXIT_SUCCESS;
}
