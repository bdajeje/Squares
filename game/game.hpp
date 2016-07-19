#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "models/player.hpp"
#include "models/map.hpp"
#include "models/hud.hpp"
#include "utils/timer.hpp"

namespace game {

enum class State {
  Running,
  Paused,
  GameOver
};

class Game final
{
  public:

    Game(std::shared_ptr<sf::RenderWindow> window);

    void restart();

  private:

    void start();
    bool handleEvents();
    void draw();
    void updateModels();
    void togglePause();

  private:

    std::shared_ptr<sf::RenderWindow> _window;

    std::shared_ptr<model::Player> _player;
    std::shared_ptr<model::Map> _map;
    std::shared_ptr<model::HUD> _hud;

    utils::time::Timer _timer;    
    State _state {State::Running};
};

}

#endif // GAME_HPP
