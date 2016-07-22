#include "engine.hpp"

#include <iostream>

#include "models/menu.hpp"

namespace game {

Engine::Engine(std::shared_ptr<sf::RenderWindow>& window, std::shared_ptr<utils::Settings>& settings)
  : _window {window}
  , _game { new Game{_window, settings} }
  , _welcome_screen { new WelcomeScreen{_window, settings} }
{
  // Init random
  srand(time(NULL));

  _windows.reserve(3);
  _windows.emplace_back( _welcome_screen );
  _windows.emplace_back( _game );
  _windows.emplace_back( new model::Menu{_window, settings} );

  focusWindow(0);
}

void Engine::start()
{
  static const sf::Color background_color {0, 0, 0};

  while(_window->isOpen())
  {
    const sf::Time elapsed_time = _timer.restart();

    // Handle events
    sf::Event event;
    while(_window->pollEvent(event))
    {
      // Close program
      if( event.type == sf::Event::Closed )
        return;

      const EventAction event_action = _focused_window->handleEvents(event);
      switch(event_action)
      {
        case EventAction::Continue: break;
        case EventAction::CreateGame:
        {
          _game->start(_welcome_screen->getPlayerName());
          focusWindow(1);
          break;
        }
        case EventAction::ShowGame: focusWindow(1); break;
        case EventAction::ShowMenu: focusWindow(2); break;
        case EventAction::Exit:     return;
      }
    }

    // Update
    _focused_window->update(elapsed_time);

    // Draw
    _window->clear(background_color);
    _window->draw(*_focused_window);
    _window->display();
  }
}

void Engine::focusWindow(size_t index)
{
  if(_focused_window)
    _focused_window->unfocus();

  _focused_window = _windows.at(index);
  _focused_window->focus();
}

}
