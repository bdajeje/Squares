#include "game.hpp"

namespace game {

Game::Game(std::shared_ptr<sf::RenderWindow> window)
  : _window {window}  
{
  // Hide mouse cursor
  _window->setMouseCursorVisible(false);
}

void Game::restart()
{
  const sf::Vector2u window_size = _window->getSize();

  _map.reset( new model::Map(window_size.x, window_size.y) );
  _player.reset( new model::Player("Nani", sf::Vector2f{window_size.x / 2.0f, window_size.y / 2.0f}) );
  _hud.reset( new model::HUD(_player, window_size.x, window_size.y) );

  _timer.restart();
  start();
}

void Game::togglePause()
{
  if(_timer.isPaused())
    _timer.start();
  else
    _timer.pause();
}

bool Game::handleEvents()
{
  sf::Event event;
  while(_window->pollEvent(event))
  {
    // Close program
    if( event.type == sf::Event::Closed )
      return false;

    // Remove compiler warnings about some enumeration values not handled in switch
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wswitch"
    switch(event.type)
    {      
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
  }

  return true;
}

void Game::updateModels()
{
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

void Game::draw()
{
  static const sf::Color background_color {0, 0, 0};

  _window->clear(background_color);
  _window->draw(*_map);
  _window->draw(*_player);
  _window->draw(*_hud);

  _window->display();
}

void Game::start()
{
  while(_window->isOpen())
  {
    if(!handleEvents())
      return;

    if(_state == State::Running)
      updateModels();

    draw();
  }
}

}
