#ifndef EVENTHANDLER_HPP
#define EVENTHANDLER_HPP

#include <SFML/Window/Event.hpp>

#include "utils/key_limitor.hpp"

namespace game {

enum class EventAction {
  Continue,
  ShowGame,
  ShowMenu,
  Exit
};

class EventHandler
{
  public:

    virtual EventAction handleEvents(const sf::Event& event) = 0;
    virtual void focus() = 0;
    virtual void unfocus() = 0;

    static bool isKeyPressed(sf::Keyboard::Key key);

  protected:

    static utils::KeyLimitor s_key_limitor;
};

}

#endif // EVENTHANDLER_HPP
