#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "graphics/window.hpp"
#include "models/player.hpp"
#include "models/map.hpp"
#include "models/hud.hpp"
#include "utils/timer.hpp"
#include "utils/settings.hpp"
#include "audio/jukebox.hpp"

namespace game {

enum class State {
  Running,
  GameOver
};

class Game final : public graphics::Window
{
  public:

    Game(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<utils::Settings>& settings);

    void start(const std::string& player_name);
    void update(const sf::Time&);
    void focus();
    void unfocus();
    EventAction handleEvents(const sf::Event& event);

  private:

    void internalDraw(sf::RenderTarget& target, sf::RenderStates states) const;
    void saveScore() const;

  private:

    std::shared_ptr<sf::RenderWindow> _window;
    audio::Jukebox _jukebox;
    std::shared_ptr<utils::Settings> _settings;

    std::shared_ptr<model::Player> _player;
    std::shared_ptr<model::Map> _map;
    std::shared_ptr<model::HUD> _hud;

    utils::time::Timer _timer;    
    State _state {State::Running};
};

}

#endif // GAME_HPP
