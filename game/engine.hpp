#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "graphics/window.hpp"
#include "utils/settings.hpp"
#include "game/game.hpp"
#include "game/welcome_screen.hpp"

namespace game {

class Engine final
{
  public:

    Engine(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<utils::Settings>& settings);

    void start();

  private:

    void focusWindow(size_t index);

  private:

    utils::time::Timer _timer;
    std::shared_ptr<sf::RenderWindow> _window;
    std::shared_ptr<game::Game> _game;
    std::shared_ptr<game::WelcomeScreen> _welcome_screen;
    std::vector<std::shared_ptr<graphics::Window>> _windows;
    std::shared_ptr<graphics::Window> _focused_window;
};

}

#endif // ENGINE_HPP
