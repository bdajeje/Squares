#include "game.hpp"

namespace game {

Game::Game(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<utils::Settings>& settings)
  : _window {window}
  , _jukebox {"./resources/musics"}
{
  // Play music
  _jukebox.setVolume(settings->get<float>(utils::Settings::MusicVolume, 50.f));
  _jukebox.play();

  const sf::Vector2u window_size = _window->getSize();
  const float sound_volume = settings->get<float>(utils::Settings::SoundVolume, 50.f);

  _map.reset( new model::Map(window_size.x, window_size.y, sound_volume) );
  _player.reset( new model::Player("Nani", sf::Vector2f{window_size.x / 2.0f, window_size.y / 2.0f}) );
  _hud.reset( new model::HUD(_player, window_size.x, window_size.y) );

  _timer.restart();
}

EventAction Game::handleEvents(const sf::Event& event)
{
  // Remove compiler warnings about some enumeration values not handled in switch
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wswitch"
  switch(event.type)
  {
    case sf::Event::KeyPressed:
    {
      if(EventHandler::isKeyPressed(sf::Keyboard::Escape))
        return EventAction::ShowMenu;

      break;
    }
    case sf::Event::MouseMoved:
    {
      if(_state == State::Running)
      {
        const sf::Vector2i mouse_position = sf::Mouse::getPosition(*_window);
        _player->setPosition( sf::Vector2f{static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y)} );
      }
      break;
    }
  }

  return EventAction::Continue;
}

void Game::update(const sf::Time& /*elapsed_time*/)
{
  // Let's ignore given elapsed time, and focus and our game timer

  // Get elapsed time since last update
  const sf::Time elapsed_time = _timer.restart();

  // Is there collision
  _map->applyCollision(_player);

  // Update models
  if(_state == State::Running)
  {
    _map->update(elapsed_time);
    _player->update(elapsed_time);
    _hud->update(elapsed_time);
  }

  // Is player dead after this collision?
  if(_player->isDead())
  {
    _state = State::GameOver;
    _hud->showGameOver();
  }
}

void Game::focus()
{
  _timer.start();
  _window->setMouseCursorVisible(false);
}

void Game::unfocus()
{
  _timer.pause();
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  target.draw(*_map, states);
  target.draw(*_player, states);
  target.draw(*_hud, states);
}

}
